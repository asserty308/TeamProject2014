#pragma once

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <string>
#include "Singleton.hpp"

#define MAX_BUFFER 1024				//maximum buffer size for arguments
#define g_pLogfile Logger::Get()	//simple makro to use the Logfile

//colors for the text
enum FontColors { BLACK, RED, GREEN, BLUE, PURPLE };

class Logger : public Singleton<Logger>
{
	private:
		FILE *logfile;

	public:
		Logger();
		~Logger();
		void createLogfile();

		//functions for internal use
		void writeTopic(const char *topic, int size);
		void textout(const char *text);
		void textout(int color, const char *text);
		void textout(int color, bool list, const char *text);
		void fTextout(const char *text, ...);
		void fTextout(int color, const char *text, ...);
		void fTextout(int color, bool list, const char *text, ...);

		//Use these to write logs into the file
		void log(const char *text);
		void log(int color, const char *text);
		void log(int color, bool list, const char *text);
		void functionResult(const char *name, bool result);
};