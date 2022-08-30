#pragma once

#include "httplib.h"

class ServerLib
{
private:
	httplib::Server server;
	std::string dump_headers(const httplib::Headers& header);
	std::string open_file(const char*);
public:
	void set_GET();
	void set_POST();
	void listening();
};

