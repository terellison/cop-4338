#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

char* lines[MAX_LINES];
int actualLines = 0;
int main()
{
    char line[MAX_LINE_LENGTH];

    while(fgets(line, MAX_LINE_LENGTH, stdin))
    {
        int lineLen = strlen(line);

        if(line[lineLen - 1] == '\n')
        {
            line[lineLen - 1] = '\0';
        }
        char* p = strdup(line);

        lines[actualLines++] = p;
    }

    fprintf(stderr, "%c", '\n');

    for(unsigned int i = 0; i < actualLines; ++i)
    {
        convertCSV(lines[i]);
        printf("%c", '\n');
    }

    fprintf(stderr, "%c", '\n');

    return 0;
}

void convertCSV(char* line)
{
    while(*line != '\0')
    {
        char* cell = 0;
        int cellLen = 0;

        while(*line != '\0' && *line != ',')
        {
            ++cellLen;
            ++line;
        }

        if(cellLen > 0)
        {
            cell = malloc(cellLen + 1);

            if(cell)
            {
                strncpy(cell, (line - cellLen), cellLen);
                cell[cellLen + 1] = '\0';
            }
        }
        
        if(cell)
        {
            if(is_int(cell))
            {
                printf("%-25e\t", atof(cell));
            }
            else
            {
                printf("%-25s\t", cell);
            }

            ++line;

            free(cell);
        }
    }
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