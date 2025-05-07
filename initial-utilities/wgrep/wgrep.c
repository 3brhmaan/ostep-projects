#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



void searchFileContentWithSearchTerm( char *searchTerm, char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("wgrep: cannot open file\n");
        exit(1);
    }

    char *line = NULL;    
    size_t lineLength = 0;      

    while (getline(&line, &lineLength, file) != -1) {
        if(strstr(line, searchTerm) != NULL)
        {
            printf("%s", line); 
        }
    }

    fclose(file);
}


void searchStandardInputContentWithSearchTerm( char *searchTerm)
{
    char *line = NULL;    
        size_t lineLength = 0;      

        if (getline(&line, &lineLength, stdin) != -1) {
            while (getline(&line, &lineLength, stdin) != -1) {
                if(strstr(line, searchTerm) != NULL)
                {
                    printf("%s", line); 
                }
            }
        }
}


int main(int argc, char *argv[])
{

    if(argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    else if(argc == 2)
    {
        searchStandardInputContentWithSearchTerm(argv[1]);
        exit(0);
    }
    else
    {
        for(int i=2 ; i<argc ; i++){
            searchFileContentWithSearchTerm(argv[1] , argv[i]);
        }
        return 0;
    }
}