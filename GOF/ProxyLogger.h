#pragma once

#include "InterfaseFileLogger.h"
#include "FileLoggerSingletone.h"



class ProxyLogger : public InterfaceFileLogger {
private:
	FileLoggerSingletone* log;
	int counter = 0;
	
public:
	ProxyLogger(FileLoggerSingletone* logger);
	
	FileLoggerSingletone& getLog();

	void __fastcall OpenLogFile(const std::string& FN) override;
	void CloseLogFile() override;
	void __fastcall WriteToLog(const std::string& str) override;
	void __fastcall WriteToLog(const std::string& str, int n) override;
	void __fastcall WriteToLog(const std::string& str, double d) override;

	~ProxyLogger();
};