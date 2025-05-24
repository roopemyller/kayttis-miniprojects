#include <stdio.h>
#include <stdlib.h>

int main(const int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            fprintf(stderr, "my-unzip: cannot open file %s\n", argv[i]);
            return 1;
        }

        int count;

        // Read 4-byte integer and character pairs
        while (fread(&count, sizeof(int), 1, file) == 1) {
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
