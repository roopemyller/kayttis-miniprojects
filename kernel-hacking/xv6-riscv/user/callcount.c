#include "kernel/types.h"
#include "user/user.h"

#define SYS_read 5
#define SYS_write 16
#define SYS_open 15
#define SYS_close 21

void print_usage() {
    printf("Usage: callcount [syscall] [reset]\n");
    printf("Syscall options to count:\n");
    printf("5 - read (default, without any defines)\n");
    printf("16 - write\n");
    printf("15 - open\n");
    printf("21 - close\n");
    printf("Reset option: 1 to reset the count, 0 to keep it (default)\n");
}


// This program prints the number of specific system calls made by the process
int main(int argc, char *argv[]) {
    int syscall_number = SYS_read; // default to read syscall
    int reset = 0;
    char *syscall_name = "read";
    if (argc > 3) {
        print_usage();
        exit(1);
    }

    if (argc > 1){
        syscall_number = atoi(argv[1]);
        if (syscall_number == 5) {
            syscall_number = SYS_read;
            syscall_name = "read";
        } else if (syscall_number == 16) {
            syscall_number = SYS_write;
            syscall_name = "write";
        } else if (syscall_number == 15) {
            syscall_number = SYS_open;
            syscall_name = "open";
        } else if (syscall_number == 21) {
            syscall_number = SYS_close;
            syscall_name = "close";
        } else {
            print_usage();
            exit(1);
        }
    }
    if (argc > 2) {
        reset = atoi(argv[2]);
        if (reset != 0 && reset != 1) {
            print_usage();
            exit(1);
        }
    }
    int syscall_count = getreadcount(syscall_number, reset);
    if (reset) {
        printf("Resetting count for syscall %d: %s\n", syscall_number, syscall_name);
        printf("Count before reset: %d\n", syscall_count);
    } else {
        printf("Count for syscall %d, %s: %d\n", syscall_number, syscall_name, syscall_count);
    }
    exit(0);
}