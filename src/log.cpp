#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <log.h>

using namespace std;

void log(int log_level, const string &msg) 
{
  string message;
  ofstream fd;
  
  
  switch(log_level) 
	{
	case LOG_INFO:
	  message = "[INFO]\t" + msg + "\n";
	  break;
	case LOG_WARRING:
	  message =  "[WARRING]\t" + msg + "\n";
	  break;
	case LOG_ERROR:
	  message = "[ERROR]\t" + msg + "\n";
	  break;
	default:
	  break;
	}

  // open file and write the message into it.
  fd.open("echo.log", ios::out | ios::app);
  if(fd.is_open()) {
	fd << message;
	fd.close();
  }
  

  // if log_level == LOG_ERROR then exit.
  if(log_level == LOG_ERROR) 
	{
	  exit(1);
	}
  
}

  

