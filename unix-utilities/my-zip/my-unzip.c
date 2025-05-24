#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char *argv[]) {
    // If no files are provided, print usage message and exit
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    // Iterate through each file provided in the command line arguments
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            fprintf(stderr, "my-unzip: cannot open file %s\n", argv[i]);
            return 1;
        }

        int count;

        // Read 4-byte integer and character pairs
        while (fread(&count, sizeof(int), 1, file) == 1) {
            // Read character
            const int character = fgetc(file);

            // If we reach EOF while reading the character, print an error and exit
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

        // Close file after processing
        fclose(file);
    }
    // Return success code
    return 0;
}
