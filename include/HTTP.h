#ifndef _ECHO_HTTP_H_
#define _ECHO_HTTP_H_
namespace echo {
  namespace HTTP {

	// echo::HTTP::Request
	class Request {
	public:
	  Request();
	};

	// echo::HTTP::Reponse
	class Reponse {
	public:
	  Reponse();
	};

	// echo::HTTP::status
	class Status {
	public:
	  Status();
	};

	// echo::HTTP::URI
	namespace URI {

	  // echo::HTTP::URI::URL
	  class URL {
	public:
		URL();
	  };
	};
  };
};

#endif
