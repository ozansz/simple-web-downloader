#include "sg_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define UAGENT_MAX_SIZE 255
#define DEFAULT_UAGENT "Mozilla/5.0 (Windows NT 6.1; WOW64) " \
                       "AppleWebKit/537.36 (KHTML, like Gecko) " \
                       "Chrome/28.0.1500.52 Safari/537.36 OPR/15.0.1147.100"

void __debug(const char *msg)
{
  if (DEBUG) {
    printf("\e[1;94m[DEBUG]\e[0m %s\n", msg);
  }
}

void show_usage(const char *prog_name) {
  printf("\nUsage: %s <URL>\n\n", prog_name);
}

size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  __debug("[CALL] WriteMemoryCallback");

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

int FastGet(const char *url, const char *user_agent, SimpleMemory *mem)
{
  __debug("[CALL] FastGet");

  CURL *curl_handle;
  CURLcode res;

  char uagent[UAGENT_MAX_SIZE];

  __debug("Checking if arg:url is NULL");
  if (url == NULL || strlen(url) == 0) {
    return -ARG_URL_IS_NULL;
  }

  bzero((char *) &uagent, UAGENT_MAX_SIZE);

  __debug("Checking if arg:user_agent is NULL");
  if (user_agent == NULL) {
    __debug("arg:user_agent is NULL, using DEFAULT_UAGENT instead");
    strcpy(uagent, DEFAULT_UAGENT);
  }
  else {
    __debug("Checking if arg:user_agent is too big");
    if (strlen(user_agent) >= UAGENT_MAX_SIZE) {
      return -ARG_UAGENT_IS_TOO_BIG;
    }
    __debug("arg:user_agent is not NULL");
    strcpy(uagent, user_agent);
  }

  __debug("CURL init");
  curl_global_init(CURL_GLOBAL_ALL);

  curl_handle = curl_easy_init();

  __debug("Setting CURL opts");
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) mem);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, uagent);

  __debug("CURL hnd process is starting");
  res = curl_easy_perform(curl_handle);

  __debug("Checking if CURL has returned any error");
  if(res != CURLE_OK) {
    return -CURL_ERROR;
  }

  __debug("CURL cleanup");
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  return RETURN_SUCCESS;
}
