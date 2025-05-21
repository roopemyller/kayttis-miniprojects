#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("hello world, this is %s!\n", argv[1]);
  exit(0);
}
