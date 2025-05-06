#include <stdio.h>
#include <stdlib.h>

void printFileContent(char *fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("wcat: cannot open file\n");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);  // Print each line
    }

    fclose(file);
}


int main(int argc, char *argv[])
{
    for(int i=1 ; i<argc ; i++){
        printFileContent(argv[i]);
    }
    return 0;
}