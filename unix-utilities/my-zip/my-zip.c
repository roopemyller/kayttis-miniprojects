#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            fprintf(stderr, "my-zip: cannot open file %s\n", argv[i]);
            return 1;
        }
        
        int current_char = fgetc(file);
        
        while (current_char != EOF) {
            int count = 1;
            int next_char;
            
            // Count consecutive characters
            while ((next_char = fgetc(file)) == current_char) {
                count++;
            }
            
            // Write count (4-byte integer) and character to stdout
            fwrite(&count, sizeof(int), 1, stdout);
            fputc(current_char, stdout);
            
            current_char = next_char;
        }
        
        fclose(file);
    }
    
    return 0;
}
