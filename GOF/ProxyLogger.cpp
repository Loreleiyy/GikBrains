#include <iostream>
#include "ProxyLogger.h"


ProxyLogger::ProxyLogger(FileLoggerSingletone* logger) {
	
	log = logger;
}

FileLoggerSingletone& ProxyLogger::getLog() {
	return *log;
}

void __fastcall ProxyLogger::OpenLogFile(const std::string & FN) {
	
	log->OpenLogFile(FN);
}

void ProxyLogger::CloseLogFile() {
	log->CloseLogFile();
}

void __fastcall ProxyLogger::WriteToLog(const std::string& str) {
	++counter;
	log->WriteToLog(str);
}

void __fastcall ProxyLogger::WriteToLog(const std::string& str, int n) {
	++counter;
	log->WriteToLog(str, n);
}

void __fastcall ProxyLogger::WriteToLog(const std::string& str, double d) {
	++counter;
	log->WriteToLog(str, d);
}

ProxyLogger::~ProxyLogger() {
	std::cout << "counter to log " << counter << std::endl;
}