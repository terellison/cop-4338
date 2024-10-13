#include"find.h"

/*
* Program find is used to find the occurrences of a given pattern in stdin
* Assumption is that stdin is made of multiple lines (no more than 1000)
* Program tries finding the pattern in each line.
* The pattern is given to the program as the last command-line argument
* There are multiple options for running this program, all passed in CLAs
* Usage: find [-n] [-x] [-s] [-r] [-m] [-c] [-f] [-p] pattern
* -n: prints the line number in the output
* -x: prints out the lines that don't have the pattern
* -s: prints out the lines in alphabetical order
* -r: prints out the lines in reverse order (LIFO)
* -m: finds the pattern only if it matches a whole word in stdin
* -c ignore the case when finding the pattern string
* -f: prints out the index of first occurrence of pattern found in each line
* -p: partially prints out the input lines. Uses ellipsis to shorten lines.
******e.g. if we look for "apple" in "my favorite dessert is apple pie with coffee"
****** then the output is "my favorit...apple...offee"
*/

char*lineptr[MAX_LINES];
int readlines(){
	int len, nlines;
	char*p, line[MAX_LEN];
	nlines = 0;
	while(fgets(line, MAX_LEN, stdin)){
		len = strlen(line);
		if(nlines >= MAX_LINES || (p = malloc(len + 1)) == NULL)
			return -1;
		else{
			if(line[len - 1] == '\n')//droping the newline at the end...
				line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}
void error(int error_code){
	switch (error_code)
	{
	case 5:
		printf("%s", "find: Illegal usage. -s and -r can’t be used together.");
		break;
	case 6:
		printf("%s", "fatal error: can't use -p and -x in the same execution");
		break;
	default:
		printf("find: fatal error - Illegal usage. Error code: %d. Usage: \"%s\"\n",
		error_code, "find [-n] [-x] [-s] [-r] [-m] [-c] [-f] [-p] pattern");
		break;
	}
	
	exit(error_code);
}
flags set_flags(int argc, char** argv){
	flags option = 0;//By default, all flags are down!
	for(int i = 1; i < argc - 1;i++){
		if(argv[i][0] != '-')//if argument doesn't start with -
			error(2);
		for(int j = 1; argv[i][j] != '\0';j++)
			switch(argv[i][j]){
				case 'n':case 'N':
				option |= NUMBERED;
				break;
				case 'x':case 'X':
				option |= EXCEPT;
				break;
				case 's':case 'S':
				option |= SORTED;
				break;
				case 'r':case 'R':
				option |= REVERSED;
				break;
				case 'm':case 'M':
				option |= MATCHED;
				break;
				case 'c':case 'C':
				option |= CASE;
				break;
				case 'f':case 'F':
				option |= FIRST;
				break;
				case 'p':case 'P':
				option |= PARTIAL;
				break;
				default: 
				error(3);
			}
	}
	return option;
}


void printLines(char* initial, int i, char* pattern, flags option)
{
	const int patternLen = strlen(pattern);
	int allocated = 0;
	if(option & NUMBERED)
			sprintf(initial, "%d. ", i + 1);

	char* first_occurrence = strstr_w_option(lineptr[i], pattern, option);

	if(!(option & EXCEPT) && (first_occurrence != NULL))
	{
		int len = strlen(lineptr[i]), reqLen = patternLen + 15;
		int patternPos = find(lineptr[i], pattern, option);

		if(option & FIRST) // add occurrence number to initial string
		{
			if(option & NUMBERED)
				sprintf(initial, "%s @%d: ", initial, patternPos);
			else
				sprintf(initial, "@%d: ", patternPos);
		}
		
		if((option & PARTIAL) && len > reqLen)
		{
			if(patternPos >= 10 && (patternPos + patternLen) < (len - 5)) // ellipses base case
			{
				char firstTen[11], lastFive[5];

				strncpy(&firstTen, lineptr[i], 10);
				strncpy(&lastFive, (lineptr[i] + (len - 5)), 5);

				int newLen = 21 + patternLen; // space for first ten + ... + pattern + ... + last five
				char partial[newLen];

				sprintf(partial, "%s...%s...%s", firstTen, pattern, lastFive);
				partial[newLen] = '\0';
				int initialLen = strlen(initial);
				if(initialLen < newLen)
				{
					char* temp = initial;
					initial = malloc(newLen + initialLen);
					initial[newLen + initialLen] = '\0';
					strcpy(initial, temp);
					allocated = 1;
				}

				strcat(initial, partial);

			}
			else if(patternPos < 10) // Omit first ellipses
			{
				// Calculate space for pattern + ellipses + last 5
				int newLen = patternLen + 8;

				if(newLen > strlen(initial))
				{
					char* temp = initial;
					initial = malloc(newLen);
					strcpy(initial, temp);
					allocated = 1;
				}

				strcat(initial, pattern);
				strcat(initial, "...");
				strncat(initial, lineptr[i] + (len - 5), 5);
			}
			else // Omit last ellipses
			{
				// space for first ten + ... + pattern + remaining string after pattern
				int newLen = 13 + patternLen + (len - (patternPos + patternLen)); 

				if(newLen > strlen(initial))
				{
					char* temp = initial;
					initial = malloc(newLen);
					strcpy(initial, temp);
					allocated = 1;
				}

				strncat(initial, lineptr[i], 10);
				strcat(initial, "...");
				strncat(initial, (lineptr[i] + patternPos), len - patternPos);
			}

			printf("%s\n", initial);
		}
		else
		{
			printf("%s%s\n", initial, lineptr[i]);
		}
		
	}
	else if((option & EXCEPT) && first_occurrence == NULL)
	{
		printf("%s%s\n", initial, lineptr[i]);
	}
	if(allocated)
		free(initial);	
}

int main(int argc, char** argv)
{
	if(argc < 2)
		error(1);
	char* pattern = strdup(argv[argc - 1]);
	flags option = set_flags(argc, argv);

	if((option & REVERSED) && (option & SORTED))
		error(5);//cannot print the output using both sorted and reversed options...

	if((option & EXCEPT) && (option & FIRST))
		error(4); // cannot print the lines that don't include the pattern and the number the pattern appears on

	if((option & EXCEPT) && (option & PARTIAL))
		error(6); // cannot sort and used reversed order at the same time

	int nlines = readlines();

	if(option & SORTED)
		quicksort(lineptr, 0, nlines - 1);

	char initial[10] = "";

	if(option & REVERSED)
	{
		for(int i = nlines - 1; i >= 0; i--)
		{
			printLines(initial, i, pattern, option);
			initial[0] = '\0';
		}
	}
	else
	{
		for(int i = 0; i < nlines;i++)
		{
			printLines(initial, i, pattern, option);
		}
	}

    return 0;
}