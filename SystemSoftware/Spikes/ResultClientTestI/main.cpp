#include <string.h>
#include <curl/curl.h>


int main() {
    int test[4] = {2,3,4,5};
    CURLcode initialResult = curl_global_init(CURL_GLOBAL_ALL);
    if(initialResult != CURLE_OK)
        return (int)initialResult;
    CURL *curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        const char * jsonObj = "{ \"name\" : \"Pedro\" , \"age\" : \"22\" }"; 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/upload");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonObj);
        CURLcode result = curl_easy_perform(curl);
    if(result != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(result));
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return (int)result;
    } 
} 