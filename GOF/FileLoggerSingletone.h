#pragma once

#include "InterfaseFileLogger.h"
#include <fstream>
//#include "ProxyLogger.h"



	class FileLoggerSingletone : public InterfaceFileLogger {
	private:
		std::ofstream logOut;			// перенос из глобальной область видимости
		FileLoggerSingletone() {}
		FileLoggerSingletone(const FileLoggerSingletone&) = delete;
		FileLoggerSingletone(FileLoggerSingletone&&) = delete;
		FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
		FileLoggerSingletone& operator=(FileLoggerSingletone&&) = delete;
	public:
		
		static FileLoggerSingletone& getInstance() {
			static FileLoggerSingletone theInstance;
			return theInstance;
		}
		
		void __fastcall OpenLogFile(const std::string& FN);				// MyTools.cpp
		void CloseLogFile();
		void __fastcall WriteToLog(const std::string& str);
		void __fastcall WriteToLog(const std::string& str, int n);
		void __fastcall WriteToLog(const std::string& str, double d);
	};
