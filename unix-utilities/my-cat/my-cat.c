#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096 // Define a reasonable buffer size for reading lines

int main(int argc, char *argv[]) {
    // If no files are specified, exit successfully
    if (argc == 1) {
        return 0;
    }

    FILE *fp; // File pointer
    char buffer[BUFFER_SIZE];

    // Process each file provided on the command line
    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");

        // Check if file opened successfully
        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        // Read and print file contents line by line
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
            printf("%s", buffer);
        }

        // Close the file
        fclose(fp);
    }

    return 0;
}
