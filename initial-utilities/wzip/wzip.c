#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void compress_content(char *content)
{
    int count = 1;
    
    for(int i=1 ; ; i++)
    {
        if(content[i] == '\0')
        {
            fwrite(&count, sizeof(int), 1, stdout);
            printf("%c",content[i-1]);
            break;
        }

        if(content[i] == content[i-1])
        {
            count++;
        }
        else
        {
            fwrite(&count, sizeof(int), 1, stdout);
            printf("%c",content[i-1]);
            count = 1;
        }
    }

}


char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_content = malloc(file_size + 1);

    size_t bytes_read = fread(file_content, 1, file_size, file);
    file_content[bytes_read] = '\0';  

    fclose(file);
    return file_content;
}


char* combine_files(int count, char *filenames[]) {
    char* combined_files_content = NULL;
    size_t total_len = 1;  

    // used to get the files content length
    for (int i = 0; i < count; i++) {
        char* file_content = read_file(filenames[i]);
        if (file_content) {
            total_len += strlen(file_content);

            free(file_content);  
        }
    }

    combined_files_content = malloc(total_len);
    combined_files_content[0] = '\0';  

    // used to read the file content
    for (int i = 0; i < count; i++) {
        char* content = read_file(filenames[i]);
        if (content) {
            strcat(combined_files_content, content);

            free(content);
        }
    }

    return combined_files_content;
}


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    char* combined_file_content = combine_files(argc - 1, &argv[1]);
    compress_content(combined_file_content);
    
    return 0;
}