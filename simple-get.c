#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "sg_lib.h"

int main(int argc, const char **argv)
{
  CURL *curl_handle;
  CURLcode res;

  SimpleMemory chunk;

  char user_agent[] = "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36"
                      " (KHTML, like Gecko) Chrome/28.0.1500.52 Safari/537.36"
                      " OPR/15.0.1147.100";
  int exit_val;

  if (argc != 2) {
    message_warning("Invalid number of args");
    show_usage(argv[0]);

    return INVALID_ARGUMENTS;
  }

  chunk.memory = malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);

  debug("Initiating curl handler");
  curl_handle = curl_easy_init();

  debug("Setting curl opts");
  curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, user_agent);

  message_info("Starting to run curl handler...");
  res = curl_easy_perform(curl_handle);

  if(res != CURLE_OK) {
    message_error("A Curl error has occured");
    message_error(curl_easy_strerror(res));
    exit_val = CURL_ERROR;
  }
  else {
    message_info("Process has done successfully");
    printf("\n===============[BEGIN RESPONSE]===============\n\n");
    printf("\n%s\n", chunk.memory);
    printf("\n================[END RESPONSE]================\n\n");
  }

  curl_easy_cleanup(curl_handle);

  free(chunk.memory);

  curl_global_cleanup();

  return 0;
}
