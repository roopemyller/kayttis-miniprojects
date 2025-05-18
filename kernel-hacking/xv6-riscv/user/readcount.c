#include "kernel/types.h"
#include "user/user.h"

// This program prints the number of read system calls made
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Read system calls: %d\n", getreadcount(0));
        exit(0);
    }
    if (strcmp(argv[1], "reset") == 0) {
        printf("Resetting read count\n");
        getreadcount(1);
        exit(0);
    }else {
        printf("Usage: readcount [reset]\n");
        exit(1);
    }
}