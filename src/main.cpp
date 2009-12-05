#include <iostream>
#include <echo.h>
#include <log.h>

int main(int argc, char **argv) 
{
  log(LOG_INFO,"Start Echo Server [v" + echo_version + "]");
  //log(LOG_ERROR,"exit()");
  log(LOG_INFO, "TEST LOG_ERROR");
  return 0;
}
