#include "convert.h"

char* lines[MAX_LINES];
int actualLines = 0;

char* strip(char * input){
    char* rv = (char*)malloc(strlen(input)+1);
    int left, right;
    for(left = 0, right = strlen(input)-1;
        left < right && (input[left] == ' ' || input[right] == ' ');
		/*no update*/){
        if(input[left] == ' '){
            left++;
        }
        if(input[right] == ' '){
            right--;
        }
    }
    strncpy(rv, input + left, right-left+1);
    return rv;
}

int is_int(char* input){
	//checks whether input can be a string representation of an int
	if(*input == '+' || * input == '-')
		input++;
	while(*input)
		if(!isdigit(*input++))
			return 0;
	return 1;
}

char* tolower_str(char* input){
	//lowers the case of characters in a string... it's called in is_double
	char* rv = strdup(input);
	int i = 0;
	while(*input)
		rv[i++] = tolower(*input++);
	return rv[i] = '\0', rv;
}

int is_double(char* input){
	//checks whether input can be a string representation of a double
	input = tolower_str(input);
	if(!strcmp(input, "inf") || !strcmp(input, "nan") || 
	!strcmp(input, "-inf"))
		return 1;
	if(strchr(input, 'e') != strrchr(input, 'e'))
		return 0;//at-most one 'e' is allowed!
	if(*input == '+' || * input == '-')//parse the sign
		input++;
	while(*input && *input != '.' && *input != 'e')
		if(!isdigit(*input++))//parse the integer value
			return 0;
	if(*input++ == '.')
		while(*input && *input != 'e')
			if(!isdigit(*input++))//parse the fraction
				return 0;
	if(*input++ == 'e'){
		if(*input == '+' || * input == '-')
			input++;//parse the sign of exponent
		while(*input)
			if(!isdigit(*input++))//parse the exponent
				return 0;
	}
	return 1;
}

int main(int argc, char* argv[]){
	flags flag = NONE;// combination of flags
	char in_fmt[4] = "txt";
	char out_fmt[4] = "csv";
	int i = 1;
	while(argc != 1){
		char* current_arg = argv[i++];
		if(current_arg[0] != '-')
			error("fatal error: illegal CLAs", 2);
		while(*++current_arg){
			switch(*current_arg){
				case 'i':
				if(strcmp(argv[i], "txt") && strcmp(argv[i], "csv"))
					error("fatal error: illegal input format", 3);
				else if(!strcmp(argv[i], "txt"))
					strcpy(in_fmt, "txt");
				else
					strcpy(in_fmt, "csv");
				i++;argc--;
				break;
				case 'o':
				if(strcmp(argv[i], "txt") && strcmp(argv[i], "csv"))
					error("fatal error: illegal output format", 4);
				else if(!strcmp(argv[i], "txt"))
					strcpy(out_fmt, "txt");
				else
					strcpy(out_fmt, "csv");
				i++;argc--;
				break;
				case 'c':
				flag |= CLEAR;//flag is an enum XXX0 | 0001 = XXX1
				break;
				case 'x':
				flag |= HEX;
				break;
				case 'e':
				flag |= SCIENTIFIC;
				break;
				case 's':
				flag |= TRUNCATED;
				break;
				default: 
				error("fatal error: illegal option entered", 5);
			}
		}argc--;
	}
	
	fprintf(stderr, "Note: converting %s to %s with options: ", in_fmt, out_fmt);
	if(flag & CLEAR)
		fprintf(stderr, "-c ");
	if(flag & HEX)//HEX: 2 = 0010, flag: XX0X, HEX & flag = 0000
		fprintf(stderr, "-x ");
	if(flag & SCIENTIFIC)
		fprintf(stderr, "-e ");
	if(flag & TRUNCATED)
		fprintf(stderr, "-s ");
	fprintf(stderr, "\n");	

	char line[MAX_LINE_LENGTH];//placeholder for a line
	char* delimiter = strcmp(in_fmt, "csv") == 0?",": "\t";
	while(fgets(line, MAX_LINE_LENGTH, stdin)){
		int lineLen = strlen(line);

		if(line[lineLen-1] == '\n')
			line[lineLen-1] = '\0';//dropping the new line

		char* p = malloc(lineLen+1);

		if(p && actualLines < MAX_LINES)
		{
			strncpy(p, line, lineLen);
			p[lineLen+1] = '\0';
			lines[actualLines++] = p;
		}
		else
			error("Could not allocate memory for input",1); // no memory ;( or too many lines
		
	}
	fprintf(stderr, "%c", '\n');
	convert(flag, delimiter, out_fmt);
	cleanup();	
	return 0;//no error occured!
}

void cleanup()
{
	for(int i = 0; i < actualLines; ++i)
	{
		char* p = lines[i];

		if(p)
			free(p);
	}
}

void convert(flags options, char* delimiter, char* out_fmt)
{
	const char newDelim = strcmp(out_fmt, "txt") == 0 ? '\t' : ',';
	for(int i = 0; i < actualLines; i++)
	{
		char* line = lines[i];

		char* cell = getNextCell(&line, delimiter, newDelim);

		while(cell)
		{
			int cellLen = strlen(cell);
			if(cellLen > 1 || *cell != ' ')
			{
				if(options & CLEAR)
				{
					cell = strip(cell);
				}

				if(is_int(cell))
				{
					if(options & HEX)
					{
						printf("%x", atoi(cell));
					}
					else
					{
						printf("%d", atoi(cell));
					}
				}

				else if(is_double(cell))
				{
					if(options & SCIENTIFIC)
						printf("%.3e", atof(cell));
					else
						printf("%s", cell);
				}

				else
				{
					if(options & TRUNCATED)
						printf("%.5s", cell);
					else
						printf("%s", cell);
				}
			}

			if(*cell != ' ')
				free(cell);

			cell = getNextCell(&line, delimiter, newDelim);

		}

		if((i + 1) < actualLines)
			printf("%c", '\n');
	}
}

char* getNextCell(char** line, char* delimiter, char newDelim)
{
	char* result = 0;
	int len = strlen(*line), cellLen = 0;
	if(len > 0)
	{
		while(**line != '\0' && **line == *delimiter) // handle leading delimiters
		{
			printf("%c", newDelim);
			++(*line);
		}

		while(**line != '\0' && cellLen < len && **line != *delimiter)
		{
			++(*line);
			++cellLen;
		}

		if(cellLen > 0)
		{
			result = malloc(cellLen + 1);

			if(result)
			{
				strncpy(result, ((*line) - cellLen), cellLen);
				result[cellLen + 1] = '\0';
			}
			else
			{
				error("Could not allocate memory", 1);
			}
		}
	}
	
	return result;
}
