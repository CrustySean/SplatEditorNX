#pragma once

#include <string>
#include <switch.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

struct MemoryStruct
{
	char *memory;
	size_t size;
};

size_t curlCallback(void *buffer, int size, int nmemb, FILE* stream);
static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

class Downloader {
private:
    CURL* curl;
	CURLcode res;
    int ret;
    int resp;
    void curlReset();
    DIR* dir;
    struct dirent* ent;
public:
    Downloader();
    ~Downloader();
    int DownloadFile(std::string url, std::string path);
    int DownloadFile_Append(std::string url, std::string path);
    std::string DownloadString(std::string url);
};
