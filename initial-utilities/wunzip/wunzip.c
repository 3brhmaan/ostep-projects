#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decompress_content(FILE *input) {
    int count;
    char character;
    
    while (fread(&count, sizeof(int), 1, input) == 1) {
        if (fread(&character, sizeof(char), 1, input) == 1) {
            for (int i = 0; i < count; i++) {
                printf("%c",character);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        decompress_content(fp);
        
        fclose(fp);
    }

    return 0;
}

// char* read_file(const char* filename) {
//     FILE* file = fopen(filename, "rb");

//     fseek(file, 0, SEEK_END);
//     long file_size = ftell(file);
//     fseek(file, 0, SEEK_SET);

//     char* file_content = malloc(file_size + 1);

//     size_t bytes_read = fread(file_content, 1, file_size, file);
//     file_content[bytes_read] = '\0';  

//     fclose(file);
//     return file_content;
// }

// int main(int argc, char *argv[])
// {
//     if(argc != 2)
//     {
//         printf("wunzip: file1 [file2 ...]\n");
//         exit(1);
//     }

//     char* file_content = read_file(argv[1]);
//     printf("%s",file_content);
    

//     return 0;
// }