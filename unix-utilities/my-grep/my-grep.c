#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096 // Define a reasonable buffer size for reading lines

int main(int argc, char *argv[]) {
    // If no searchterm is specified, print usage and exit
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    const char *searchterm = argv[1];
    FILE *fp;
    
    char *buffer;
    size_t buffer_size = 0;
    size_t line;

    // if file is not specified, read from stdin
    if (argc == 2) {
        while ((line = getline(&buffer, &buffer_size, stdin)) != -1) {
            if (strstr(buffer, searchterm) != NULL) {
                printf("%s", buffer);
            }
        }
        free(buffer);
        exit(0);
    }

    // process each file
    for (int i = 2; i < argc; i++){
        fp = fopen(argv[i], "r");
        // check if file opened successfully
        if (fp == NULL) {
            printf("my-grep: cannot open file\n");
            exit(1);
        }
        // read and print file contents line by line
        while ((line = getline(&buffer, &buffer_size, fp)) != -1){
            if (strstr(buffer, searchterm) != NULL) {
                printf("%s", buffer);
            }
        }
        fclose(fp);
    }
    free(buffer);
    exit(0); 
}
