#include "sg_lib.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv)
{
  int res;
  SimpleMemory mem;

  if (argc != 2) {
    show_usage(argv[0]);
    return 1;
  }

  __debug("Initializing variable (SimpleMemory) mem");
  mem.memory = malloc(1);
  mem.size = 0;

  __debug("Calling FastGet");
  res = FastGet(argv[1], NULL, &mem);

  __debug("Checking if any error has returned from FastGet");
  if (res < 0) {
    printf("[!!!] ECODE: %d\n", res);
  }
  else {
    printf("%s\n", mem.memory);
  }

  __debug("Freeing mem");
  free(mem.memory);

  return 0;
}
