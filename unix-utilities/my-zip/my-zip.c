#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // if no files are provided, print usage and exit
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    // iterate through each file provided in the command line arguments
    for (int i = 1; i < argc; i++){
        FILE *fp = fopen(argv[i], "r");
        // check if the file was opened successfully
        if(fp == NULL) {
            printf("my-zip: cannot open file %s\n", argv[i]);
            exit(1);
        }

        // get the first character from the file
        // and start reading the file character by character
        int current_char = fgetc(fp);
        while (current_char != EOF) {
            int count = 1;
            int next_char;

            // count how many times the current character appears consecutively
            while((next_char = fgetc(fp)) == current_char) {
                count++;
            }
            
            // write the count as a 4-byte integer and the character to stdout
            fwrite(&count, sizeof(int), 1, stdout);
            fwrite(&current_char, sizeof(char), 1, stdout);
           
            // get the next character to continue the process
            current_char = next_char;
        }
        fclose(fp);
    }
    exit(0);
}