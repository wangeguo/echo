#ifndef _ECHO_CONTEXT_H_
#define _ECHO_CONTEXT_h_

#include <HTTP.h>

namespace echo {

  class Context {
  public:
	echo::HTTP::Request request;
	echo::HTTP::Reponse reponse;
	echo::HTTP::Status status;
	echo::HTTP::URI::URL url;
	Context();
  };

};
#endif
