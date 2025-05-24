#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char *argv[]) {
    // if no files are provided, print usage and exit
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    // iterate through each file provided in the command line arguments
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        // check if the file was opened successfully
        if (!file) {
            fprintf(stderr, "my-unzip: cannot open file %s\n", argv[i]);
            return 1;
        }

        int count;

        // read 4-byte integer and character pairs from the file
        while (fread(&count, sizeof(int), 1, file) == 1) {
            // check if charactes is end of file
            const int character = fgetc(file);
            if (character == EOF) {
                fprintf(stderr, "my-unzip: invalid compressed file format\n");
                fclose(file);
                return 1;
            }

            // Print the character 'count' times
            for (int j = 0; j < count; j++) {
                printf("%c", character);
            }
        }
        fclose(file);
    }
    return 0;
}