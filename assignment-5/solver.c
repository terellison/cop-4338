#include "solver.h"

hashset h;
tnode* btreeRoot;


pthread_mutex_t btreeLock;
pthread_mutex_t bufferLock;

int main(int argc, char **argv) {
    if (argc < 11)
        error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);

    int puzzle_size = 0, buf_cells = 0, i = 0, j, fd, min_len = 0, max_len = 0, sorted = 0, buf_dimension;
    char *filename = NULL;
    FILE *dictionary_file;
    char ***buffer;

    while (++i < argc) {
        if (argv[i][0] != '-')
            error("Fatal Error. Invalid CLA", 2);
        if (!strcmp(argv[i], "-size")) {
            puzzle_size = atoi(argv[++i]);
            if (puzzle_size < 15 || puzzle_size > 46340)
                error("Fatal Error. Illegal value passed after -size", 3);
        } else if (!strcmp(argv[i], "-nbuffer")) {
            buf_cells = atoi(argv[++i]);
            if (buf_cells != 1 && buf_cells != 4 && buf_cells != 16 && buf_cells != 64)
                error("Fatal Error. Illegal value passed after -nbuffer", 4);
            buf_dimension = puzzle_size / (int)sqrt(buf_cells);
        } else if (!strcmp(argv[i], "-input")) {
            filename = strdup(argv[++i]);
            fd = open(filename, O_RDONLY, 0);
            if (fd < 0)
                error("Fatal Error. Illegal value passed after -input", 5);
        } else if (!strcmp(argv[i], "-dict")) {
            dictionary_file = fopen(argv[++i], "r");
            if (!dictionary_file)
                error("Fatal Error. Illegal value passed after -dict", 6);
        } else if (!strcmp(argv[i], "-len")) {
            char *min_max = strdup(argv[++i]);
            char *max_str;
            if (strrchr(min_max, ':') != (max_str = strchr(min_max, ':')) || !strchr(min_max, ':'))
                error("Fatal Error. Illegal value passed after -len", 7);
            max_len = atoi(max_str + 1);
            min_max[max_str - min_max] = '\0';
            min_len = atoi(min_max);
            if (min_len < 3 || max_len > 14 || min_len > max_len)
                error("Fatal Error. Illegal value passed after -len", 7);
        } else if (!strcmp(argv[i], "-s"))
            sorted = 1;
        else {
            error("Fatal Error. Usage: solve -dict dict.txt -input puzzle1mb.txt -size 1000 -nbuffer 64 -len 4:7 [-s]", 1);
            break;
        }
    }

    // Read and move all words from dictionary_file to a new hash table (hashset)
    char *words[100000];
    char word[500];
    int wordCount = 0;
    while (fgets(word, 500, dictionary_file)) {
        int n = strlen(word);
        if (!n) continue;
        if (word[n - 1] == '\n')
            word[n - 1] = '\0';
        words[wordCount++] = strdup(word);
    }
    fclose(dictionary_file);
    h = set_init();
    for (int j = 0; j < wordCount; ++j) {
        insert(&h, words[j]);
    }

    // Allocate buffer in the heap
    buffer = (char ***)malloc(buf_cells * sizeof(char **));
    for (i = 0; i < buf_cells; i++) {
        buffer[i] = (char **)malloc(buf_dimension * sizeof(char *));
        for (j = 0; j < buf_dimension; j++)
            buffer[i][j] = (char *)malloc(buf_dimension);
    }

    int buf_index = 0;
    pthread_t t_id[buf_cells];
    for (i = 0; i < buf_cells; i++)
        t_id[i] = NULL;
	
	pthread_mutex_init(&btreeLock, NULL);
	pthread_mutex_init(&bufferLock, NULL);

    for (int row = 0; row < puzzle_size; row += buf_dimension) {
        int subpuzzle_rows = (row + buf_dimension <= puzzle_size) ? buf_dimension : puzzle_size - row;

        for (int column = 0; column < puzzle_size; column += buf_dimension) {
            long start = (long)row * (puzzle_size + 1) + column;
            lseek(fd, start, SEEK_SET);

            int subpuzzle_cols = (column + buf_dimension <= puzzle_size) ? buf_dimension : puzzle_size - column;

            if (t_id[buf_index]) // if there is a busy consumer/solver,
                pthread_join(t_id[buf_index], NULL); // wait for it to finish the job before manipulating the buffer[buffer_index]

            for (i = 0; i < subpuzzle_rows; i++) {
                int n_read = read(fd, buffer[buf_index][i], subpuzzle_cols);
                if (n_read < subpuzzle_cols)
                    error("Fatal Error. Bad read from input file", 10);
                if (subpuzzle_cols < buf_dimension)
                    buffer[buf_index][i][subpuzzle_cols] = '\0';
                lseek(fd, puzzle_size - subpuzzle_cols + 1, SEEK_CUR);
            }
            if (subpuzzle_rows < buf_dimension)
                buffer[buf_index][subpuzzle_rows] = NULL;

            // Create and start a solver thread after passing the right information to it
            threadData* thread_data = malloc(sizeof(threadData));
            thread_data->sub_puzzle = buffer[buf_index];
            thread_data->subpuzzle_rows = subpuzzle_rows;
            thread_data->subpuzzle_cols = subpuzzle_cols;
            thread_data->start_row = row;
            thread_data->start_col = column;
            thread_data->min_len = min_len;
            thread_data->max_len = max_len;
			thread_data->sorted = sorted;

            pthread_create(&t_id[buf_index], NULL, solve, thread_data);

            buf_index = (buf_index == buf_cells - 1) ? 0 : buf_index + 1;
        }
    }

    for (i = 0; i < buf_cells; i++)
        if (t_id[i])
            pthread_join(t_id[i], NULL);

    if (sorted) {
        // Print the binary search tree using in-order traversal...
        // Your code here...
		inorder_print(btreeRoot);
    }

    return 0;
}

void* solve(void *arg) {
    threadData *data = (threadData *)arg;
    // Implement the word search logic here using data->sub_puzzle
    fprintf(stderr, "solver thread: solving sub-puzzle of dimensions %d by %d located at index (%d,%d).\n",
            data->subpuzzle_rows, data->subpuzzle_cols, data->start_row, data->start_col);

	pthread_mutex_lock(&bufferLock);
	for(int row = 0; row < data->subpuzzle_rows; ++row)
	{
		for(int col = 0; col < data->subpuzzle_cols; ++col)
		{
			searchInDirection(data, row, col, 0, 1);   // Left to right
            searchInDirection(data, row, col, 0, -1);  // Right to left
            searchInDirection(data, row, col, 1, 0);   // Top to bottom
            searchInDirection(data, row, col, -1, 0);  // Bottom to top
            searchInDirection(data, row, col, 1, 1);   // Diagonal down-right
            searchInDirection(data, row, col, 1, -1);  // Diagonal down-left
            searchInDirection(data, row, col, -1, 1);  // Diagonal up-right
            searchInDirection(data, row, col, -1, -1); // Diagonal up-left
		}
	}
	pthread_mutex_unlock(&bufferLock);
    // Free the allocated memory for the sub-puzzle
    for (int i = 0; i < data->subpuzzle_rows; i++) {
        free(data->sub_puzzle[i]);
    }
    free(data->sub_puzzle);
    free(data);
    return NULL;
}

void print_buffer(char** sub_puzzle, int subpuzzle_rows, int subpuzzle_cols)
{
	//this function is used for printing the content of each buffer cell.
	//do NOT call this function anywhere in your final submission.
	printf("%d by %d\n", subpuzzle_rows, subpuzzle_cols);
	for(int i = 0; i < subpuzzle_rows;i++)
		for(int j = 0; j < subpuzzle_cols;j++)
			printf("%c%s", sub_puzzle[i][j], j == subpuzzle_cols - 1?"\n":"");
}

void searchInDirection(threadData* data, int startRow, int startCol, int rowStep, int colStep)
{
	char word[data->max_len + 1];
	char** puzzle = data->sub_puzzle;
	int min_len = data->min_len, max_len = data->max_len;
	int size = data->subpuzzle_rows;

	for(int i = 0; i < size; ++i)
	{
		int row = startRow + i * rowStep;
		int col = startCol + i * colStep;
		int length = 0;

		while(row >= 0 && row < size && col >= 0 && col < data->subpuzzle_cols && length < max_len)
		{
			word[length++] = puzzle[row][col];
			word[length] = '\0';

			if(length >= min_len && search(h, word))
			{
				pthread_mutex_lock(&btreeLock);
				bst_insert(&btreeRoot, word);
				pthread_mutex_unlock(&btreeLock);

				if(!data->sorted)
					printf("%s\n", word);
			}

			row += rowStep;
			col += colStep;
		}
	}
}
