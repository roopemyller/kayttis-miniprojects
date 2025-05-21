#include "kernel/types.h"
#include "user/user.h"

#define SYS_read 5
#define SYS_write 16
#define SYS_open 15
#define SYS_close 21


// print_usage function to display usage information
// for the getcount program
// It shows the available syscalls and the reset option
void print_usage() {
    printf("Usage: getcount [syscall] [reset]\n");
    printf("Syscall options to count:\n");
    printf("5 - read\n");
    printf("16 - write\n");
    printf("15 - open\n");
    printf("21 - close\n");
    printf("22 - getcount\n");
    printf("Reset option: 1 to reset the count, 0 to keep it (default)\n");
}

// This program prints the number of specific system calls made by the process
// It takes two arguments: the syscall number and a reset flag
int main(int argc, char *argv[]) {
    // syscall number default to read
    // reset flag default to 0 (no reset)
    // syscall name default to read
    int syscall_number = SYS_read;
    int reset = 0;
    char *syscall_name = "read";

    // Check the number of arguments if more than 3 or less than 2
    // print usage and exit
    if (argc > 3 || argc < 2) {
        print_usage();
        exit(1);
    }

    // If the user provided a syscall number, set it
    // and set the syscall name based on the number
    if (argc > 1){
        syscall_number = atoi(argv[1]);
        if (syscall_number == 5) {
            syscall_name = "read";
        } else if (syscall_number == 16) {
            syscall_name = "write";
        } else if (syscall_number == 15) {
            syscall_name = "open";
        } else if (syscall_number == 21) {
            syscall_name = "close";
        } else if (syscall_number == 22){
            syscall_name = "getcount";
        } else {
            print_usage();
            exit(1);
        }
    }

    // If the user provided a reset flag, set it
    // and check if it's valid (0 or 1)
    if (argc > 2) {
        reset = atoi(argv[2]);
        if (reset != 0 && reset != 1) {
            print_usage();
            exit(1);
        }
    }

    // get the syscall count using the getreadcount function
    int syscall_count = getcount(syscall_number, reset);
    if (reset) {
        printf("Resetting count for syscall %d: %s\n", syscall_number, syscall_name);
        printf("Count before reset: %d\n", syscall_count);
    } else {
        printf("Count for syscall %d, %s: %d\n", syscall_number, syscall_name, syscall_count);
    }
    exit(0);
}