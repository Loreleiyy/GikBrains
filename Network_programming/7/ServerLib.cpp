#include "ServerLib.h"
#include <fstream>
#include <sstream>

using namespace httplib;

std::string ServerLib::dump_headers(const Headers& header)
{
	std::string str;
	for (const auto& [s1, s2] : header)
	{
		str += s1 + ": " + s2 + '\n';
	}
	return str;
}

std::string ServerLib::open_file(const char* name)
{
	std::string str, s1;
	std::fstream file;
	file.open(name);
	while (std::getline(file, s1))
	{
		str += s1 + '\n';
	}

	return str;
}

void ServerLib::set_GET()
{
	
	server.Get("/hi", [](const httplib::Request &, httplib::Response& res) {
		res.set_content("Hello!", "text/plain");
	});
	server.Get("/exit", [&](const Request&, Response&) {server.stop(); });
	server.Get("/file/test", [&](const Request&, Response& res) {
		res.set_content(open_file("test.png"), "image/png");
		});
	server.Get("/test", [&](const Request&, Response& res) {
		res.set_content(open_file("text.txt"), "text/plain");
		});
	server.Get("/", [](const Request&, Response& res) {
		res.set_redirect("/hi");
		});
	server.Get("/dump", [&](const Request& req, Response& res) {		// view the title
		res.set_content(dump_headers(req.headers), "text/plain");
		});
}

void ServerLib::set_POST()
{
	//server.Post();
}

void ServerLib::listening()
{
	server.listen("127.0.0.1", 1230);
}
