#include "requests.hpp"
#include <curl/curl.h>
#include <string>

namespace bookchain {
namespace requests {

size_t stringWriteCallback(char* ptr, size_t size, size_t nmemb, std::string* userdata) {
    size_t realSize = size * nmemb;
    userdata->append(ptr, realSize);

    return realSize;
}

std::string getRequest(const std::string& url) {
    CURL* curl = nullptr;
    CURLcode response;
    std::string returnString;

    curl = curl_easy_init();
    if (curl != nullptr) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, stringWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnString);

        response = curl_easy_perform(curl);
        if (response != CURLE_OK) {
            returnString = "";
        }

        curl_easy_cleanup(curl);
    }

    return (returnString.empty()) ? "{}" : returnString;
}

std::string postRequest(const std::string& url, const std::string& payload) {
    CURL* curl = nullptr;
    CURLcode response;
    std::string returnString;

    curl = curl_easy_init();
    ;
    if (curl != nullptr) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, stringWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &returnString);

        response = curl_easy_perform(curl);
        if (response != CURLE_OK) {
            returnString = "";
        }

        curl_easy_cleanup(curl);
    }

    return (returnString.empty()) ? "{}" : returnString;
}

}
}
