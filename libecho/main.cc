#include <iostream>
#include <echo.h>
#include <log.h>
#include <HTTP.h>
#include <context.h>
#include <application.h>

using namespace std;
using namespace echo;

int main(int argc, char **argv) 
{
  log(LOG_INFO,"Start Echo Server [v" + echo_version + "]");

  static HTTP::Request request;
  static HTTP::Reponse reponse;
  static HTTP::Status status;
  static HTTP::URI::URL url;

  static Context context;

  context.status = status;
  context.request = request;
  context.reponse = reponse;
  context.url = url;

  log(LOG_INFO, "Init request,reponse,status,url,context..");

  log(LOG_INFO, "Init Application");
  static Application echoApplication;
  echoApplication.start();

  log(LOG_INFO, "RUN!");
  
  return 0;
}
