#include "Client.h"

size_t write_str(void *buffer, size_t size, size_t nmemb, void *userp)
{
	reinterpret_cast<std::string*>(userp)->append((char*)buffer, size* nmemb);
	return size * nmemb;
}

Client::Client(const char* url) : URL(url)
{
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, URL);
}

void Client::set_write()
{
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_str);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, message);

}

void Client::set_read()
{
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);
}

void Client::client_work()
{
	curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1l);
	res = curl_easy_perform(curl);
	if (res != CURLE_OK)
		{
		fprintf(stderr, "curl_easy_perform() failed: %s\n",	curl_easy_strerror(res));
		}
	bool run = true;
	while (run)
	{
		size_t len;
		std::getline(std::cin, message);
		curl_easy_send(curl, message.c_str(), message.size(), &len);


	}
}