#include "sg_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  SimpleMemory *mem = (SimpleMemory *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    printf("[!] Not enough memory (code: %d)\n", OUT_OF_MEMORY);
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

void show_usage(const char *prog_name)
{
  printf("\nUsage: %s <URL>\n\n", prog_name);
}

void debug(const char *msg)
{
  if (DEBUG) {
    printf("\e[1m[DEBUG]\e[0m %s\n", msg);
  }
}

void message_info(const char *msg)
{
  printf("[+] %s\n", msg);
}

void message_warning(const char *msg)
{
  printf("\e[93m[!]\e[0m %s\n", msg);
}

void message_error(const char *msg)
{
  printf("\e[91m[ERROR]\e[0m %s\n", msg);
}
