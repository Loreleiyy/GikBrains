#pragma once
extern "C"
#include <curl/curl.h>
#include <string>
#include <iostream>

class Client
{
private:
	CURL* curl;
	CURLcode res;
	std::string message;
	std::string URL;
public:
	Client(const char* url);
	void set_write();
	void set_read();
	void client_work();
};

