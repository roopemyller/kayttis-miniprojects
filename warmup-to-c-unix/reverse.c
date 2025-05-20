#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// Structure for linked list to store the lines
typedef struct Node {
    char *line;
    struct Node *next;
} Node;

// Function to add a new line to linked list
Node* addLine(Node *head, char *line) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    newNode->line = strdup(line); // Make a copy of the line
    if (newNode->line == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    newNode->next = head; // New node points to current head
    return newNode; // Return new head
}

// Function to free the linked list
void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->line); // Free the line
        free(temp); // Free the node
    }
}

// Function to reverse contents of a file
void reverseFile(FILE *input, FILE *output) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    Node *head = NULL;

    // Read all lines and add to linked list
    while ((read = getline(&line, &len, input)) != -1) {
        head = addLine(head, line);
    }

    // Free the line buffer from getline
    if (line) {
        free(line);
    }

    // Print all lines in reverse order
    Node *current = head;
    while (current != NULL) {
        fprintf(output, "%s", current->line);
        current = current->next;
    }

    // Free the linked list
    freeList(head);
}

int main(int argc, char *argv[]) {
    FILE *input = NULL;
    FILE *output = NULL;
    
    // Check argument count
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    
    // Handle input file
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    } else {
        input = stdin;  // No input file specified, use stdin
    }
    
    // Handle output file
    if (argc == 3) {
        // Check if input and output files are the same
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            if (input != stdin) {
                fclose(input);
            }
            exit(1);
        }
        
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            if (input != stdin) {
                fclose(input);
            }
            exit(1);
        }
    } else {
        output = stdout;  // No output file specified, use stdout
    }
    
    // Reverse the file
    reverseFile(input, output);
    
    // Clean up
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }
    
    return 0;
}
