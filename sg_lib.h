#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 1

typedef enum {
  GENERIC_ERROR = 1,
  FATAL_ERROR,
  OUT_OF_MEMORY,
  CURL_ERROR,
  INVALID_ARGUMENTS
} ERR_CODE;

typedef struct {
  char *memory;
  size_t size;
} SimpleMemory;

size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

void show_usage(const char *prog_name);

void debug(const char *msg);

void message_info(const char *msg);

void message_warning(const char *msg);

void message_error(const char *msg);
