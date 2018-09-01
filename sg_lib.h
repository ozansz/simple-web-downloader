#pragma once

#include <stdlib.h>

#define DEBUG 0

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  RETURN_SUCCESS = 0,
  GENERIC_ERROR = 1,
  FATAL_ERROR,
  OUT_OF_MEMORY,
  CURL_ERROR,
  ARG_URL_IS_NULL,
  ARG_UAGENT_IS_TOO_BIG
} FAST_GET_RETURN_CODE;

typedef struct {
  char *memory;
  size_t size;
} SimpleMemory;

void __debug(const char *msg);

void show_usage(const char *prog_name);

size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

int FastGet(const char *url, const char *user_agent, SimpleMemory *mem);

#ifdef __cplusplus
}
#endif
