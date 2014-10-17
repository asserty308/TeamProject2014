#include "Logger.hpp"

Logger::Logger()
{
}

Logger::~Logger()
{
	textout("<br><br>End of logfile</font></body></html>");
	fclose(logfile);
}

/*
 clears the logfile and writes the header
*/
void Logger::createLogfile()
{
	time_t time;
	std::time(&time);
	char *logName = "Logfile.html";

	logfile = fopen(logName, "w");
	textout("<html><head><title>Logfile</title></head>");
	textout("<body><font face = 'courier new'>");
	writeTopic("Logfile", 3);

	//output build configuration
	#ifdef _DEBUG
		textout("BUILD: DEBUG<br>");
	#else
		textout("BUILD: RELEASE<br>");
	#endif

	textout(std::ctime(&time));
	textout("<br><br>");

	//close and reopen with append
	fclose(logfile);
	logfile = fopen(logName, "a");
}

/*
 writes the header
*/
void Logger::writeTopic(const char *topic, int size)
{
	textout("<table cellspacing='0' cellpadding='0' width='100%%'");
	textout("bgcolor='#DFDFE5'>\n<tr>\n<td>\n<font face='arial'");
	fTextout("size='+%i'>\n", size);
	textout(topic);
	textout("</font>\n</td>\n</tr>\n</table>\n<br>");
	fflush(logfile);
}

/*
 writes black text into the file
*/
void Logger::textout(const char *text)
{
	fprintf(logfile, text);
	fflush(logfile);
}

/*
 writes colored text into the file
*/
void Logger::textout(int color, const char *text)
{
	textout(color, false, text);
}

/*
 writes colored text into a list
*/
void Logger::textout(int color, bool list, const char *text)
{
	if (list == true)
	{
		textout("<li>");
	}

	//choose color
	switch (color)
	{
		case BLACK:
			textout("<font color=black>");
			break;
		case RED:
			textout("<font color=red>");
			break;
		case GREEN:
			textout("<font color=green>");
			break;
		case BLUE:
			textout("<font color=blue>");
			break;
		case PURPLE:
			textout("<font color=purple>");
			break;
	};

	textout(text);
	textout("</font>");

	if (list == false)
	{
		textout("<br>");
	}
	else
	{
		textout("</li>");
	}
}

/*
 black text with arguments
*/
void Logger::fTextout(const char *text, ...)
{
	char buffer[MAX_BUFFER];
	va_list pArgList;			//arguments

	//create a string from arguments
	va_start(pArgList, text);
	vsprintf(buffer, text, pArgList);
	va_end(pArgList);

	textout(buffer);
}

/*
 colored text with arguments
*/
void Logger::fTextout(int color, const char *text, ...)
{
	char buffer[MAX_BUFFER];
	va_list pArgList;			//arguments

	//create a string from arguments
	va_start(pArgList, text);
	vsprintf(buffer, text, pArgList);
	va_end(pArgList);

	textout(color, buffer);
}

/*
 colored and listed text with arguments 
*/
void Logger::fTextout(int color, bool list, const char *text, ...)
{
	char buffer[MAX_BUFFER];
	va_list pArgList;			//arguments

	//create a string from arguments
	va_start(pArgList, text);
	vsprintf(buffer, text, pArgList);
	va_end(pArgList);

	textout(color, list, buffer);
}

/*
 outputs OK or ERROR for a specific function-call
*/
void Logger::functionResult(const char *name, bool result)
{
	if (result)
	{
		textout("<table width='100%%' cellSpacing='1' cellPadding='5'");
		textout(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
		fTextout("'#FFFFFF' width='35%%'>%s</TD>", name);
		textout("<td bgcolor='#FFFFFF' width='30%%'><font color =");
		textout("'green'>OK</FONT></TD><td bgcolor='#FFFFFF'");
		textout("width='35%%'>-/-</TD></tr></table>");
	}
	else
	{
		textout("<table width='100%%' cellSpacing='1' cellPadding='5'");
		textout(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
		fTextout("'#FFFFFF' width='35%%'>%s</TD", name);
		textout("<td bgcolor='#FFFFFF' width='30%%'><font color =");
		textout("'red'>ERROR</FONT></TD><td bgcolor='#FFFFFF' ");
		textout("width='35%%'>./->/TD></tr></table>");
	}
}

void Logger::log(const char *text)
{
	textout(text);
	textout("<br>");
}

void Logger::log(int color, const char *text)
{
	textout(color, text);
	textout("<br>");
}

void Logger::log(int color, bool list, const char *text)
{
	textout(color, list, text);
	textout("<br>");
}