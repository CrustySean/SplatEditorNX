#include "downloader.hpp"

Downloader::Downloader()
{
    dir = opendir(""); // Open current-working-directory.

    socketInitializeDefault();
    curl = curl_easy_init();
}

int Downloader::DownloadFile(std::string url, std::string path)
{
    FILE *file = fopen(path.c_str(), "wb");
	if (!file) return 1;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	ret = curl_easy_perform(curl);
	fclose(file);

	curlReset();

	return 0;
}

int Downloader::DownloadFile_Append(std::string url, std::string path)
{
    FILE *file = fopen(path.c_str(), "ab");
	if (!file) return 1;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	ret = curl_easy_perform(curl);
	fclose(file);

	curlReset();

	return 0;
}

std::string Downloader::DownloadString(std::string url)
{
	struct MemoryStruct downloadedData;
	downloadedData.memory = (char*)malloc(1);
	downloadedData.size = 0;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &downloadedData);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	ret = curl_easy_perform(curl);

	curlReset();

	return downloadedData.memory;
}

Downloader::~Downloader()
{
    closedir(dir);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    socketExit();
}

void Downloader::curlReset()
{
    curl_easy_reset(curl);
}

size_t curlCallback(void *buffer, int size, int nmemb, FILE* stream)
{
    size_t written = fwrite(buffer, size, nmemb, stream);
    return written;
}

static size_t
writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL)
	{
		printf("WriteMemoryCallback: Not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}
