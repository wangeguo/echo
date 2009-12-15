#include <echo/echo.h>
#include <echo/log.h>
#include <echo/application.h>

using namespace echo;

int main(int argc, char **argv)
{
  log(LOG_INFO, "Start hello server, Powered by echo v" + echo_version);

  Application helloApplication(argc, argv);

  helloApplication.start();

  return 0;
}

  
