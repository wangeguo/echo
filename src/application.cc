#include <application.h>
#include <fcgi_stdio.h>

using namespace echo;

// echo::Application
void Application::start() {
  while(FCGI_Accped() != 0) {
	
  }
}
