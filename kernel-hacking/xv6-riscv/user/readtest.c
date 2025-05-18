#include "kernel/types.h"
#include "user/user.h"

// This program tests the read system call and prints the number of read
// system calls made by the process
int main(void) {
    int count, next_count;
    char buf[64];
    int fd;
    
    count = getreadcount(0);
    printf("Program start count: %d\n", count);
    
    // Multiple small reads to see individual operations
    fd = open("README", 0);
    next_count = getreadcount(0);
    printf("After open: %d (delta: %d)\n", next_count, next_count - count);
    count = next_count;
    
    read(fd, buf, 1);  // Read just 1 byte
    next_count = getreadcount(0);
    printf("After read 1 byte: %d (delta: %d)\n", next_count, next_count - count);
    count = next_count;
    
    read(fd, buf, sizeof(buf));  // Read full buffer
    next_count = getreadcount(0);
    printf("After read buffer: %d (delta: %d)\n", next_count, next_count - count);
    
    close(fd);
    printf("Final count: %d\n", getreadcount(0));
    exit(0);
}