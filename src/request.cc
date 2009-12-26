#include <echo/request.h>

namespace echo {

  static Request Request::getCurrent() {
	return (Response.getCurrent() == NULL) ? NULL : Response.getCurrent()
	  .getRequest();
  }

  Request::Request(Method method, Reference resourceRef, Representation entity) {
	super(entity);
	challengeResponse = NULL;
	clientInfo = NULL;
	conditions = NULL;
	cookies = NULL;
	hostRef = NULL;
	this->method = method;
	originalRef = NULL;
	proxyChallengeResponse = NULL;
	ranges = NULL;
	referrerRef = NULL;
	this->resourceRef = resourceRef;
	rootRef = NULL;
  }

  Request::Request(Method method, String resourceUri) {
	Request(method, new Reference(resourceUri));
  }

  Request::Request(Method method, String resourceUri, Representation entity) {
	Request(method, new Reference(resourceUri), entity);
  }

  ClientInfo Request::getClientInfo() {
	// Lazy initialization with double-check.
	ClientInfo c = clientInfo;
	if (c == NULL) {
	  synchronized (this) {
		c = clientInfo;
		if (c == NULL) {
		  clientInfo = c = new ClientInfo();
		}
	  }
	}
	return c;
  }

  Conditions Request::getConditions() {
	// Lazy initialization with double-check.
	Conditions c = conditions;
	if (c == NULL) {
	  synchronized (this) {
		c = conditions;
		if (c == NULL) {
		  conditions = c = new Conditions();
		}
	  }
	}
	return c;
  }

  Series<Cookie> Request::getCookies() {
	// Lazy initialization with double-check.
	Series<Cookie> c = cookies;
	if (c == NULL) {
	  synchronized (this) {
		c = cookies;
		if (c == NULL) {
		  cookies = c = new CookieSeries();
		}
	  }
	}
	return c;
  }

  Protocol Request::getProtocol() {
	Protocol result = NULL;

	if (getResourceRef() != NULL) {
	  // Attempt to guess the protocol to use
	  // from the target reference scheme
	  result = getResourceRef().getSchemeProtocol();
	  // Fallback: look at base reference scheme
	  if (result == NULL) {
		result = (getResourceRef().getBaseRef() != NULL) ? getResourceRef()
		  .getBaseRef().getSchemeProtocol()
		  : NULL;
	  }
	}

	return result;
  }

  std::list<Range> Request::getRanges() {
	// Lazy initialization with double-check.
	std::list<Range> r = ranges;
	if (r == NULL) {
	  synchronized (this) {
		r = ranges;
		if (r == NULL) {
		  ranges = r = new CopyOnWriteArrayList<Range>();
		}
	  }
	}
	return r;
  }

  bool Request::isConfidential() {
	return (getProtocol() == NULL) ? false : getProtocol().isConfidential();
  }

  bool Request::isEntityAvailable() {
	// The declaration of the "result" variable is a workaround for the GWT
	// platform.
	bool result = (Method.GET.equals(getMethod())
				   || Method.HEAD.equals(getMethod()) || Method.DELETE
				   .equals(getMethod()));
	if (result) {
	  return false;
	}

	return super.isEntityAvailable();
  }

  void Request::setChallengeResponse(ChallengeResponse challengeResponse) {
	this->challengeResponse = challengeResponse;
  }

  void Request::setClientInfo(ClientInfo clientInfo) {
	this->clientInfo = clientInfo;
  }

  void Request::setConditions(Conditions conditions) {
	this->conditions = conditions;
  }

  void Request::setCookies(Series<Cookie> cookies) {
	this->cookies = cookies;
  }

  void Request::setHostRef(Reference hostRef) {
	this->hostRef = hostRef;
  }

  void Request::setHostRef(String hostUri) {
	setHostRef(new Reference(hostUri));
  }

  void Request::setMethod(Method method) {
	this->method = method;
  }

  void Request::setOriginalRef(Reference originalRef) {
	this->originalRef = originalRef;
  }

  void Request::setProxyChallengeResponse(ChallengeResponse challengeResponse) {
	this->proxyChallengeResponse = challengeResponse;
  }

  void Request::setRanges(std::list<Range> ranges) {
	this->ranges = ranges;
  }

  void Request::setReferrerRef(Reference referrerRef) {
	this->referrerRef = referrerRef;

	// A referrer reference must not include a fragment.
	if ((this->referrerRef != NULL)
		&& (this->referrerRef.getFragment() != NULL)) {
	  this->referrerRef.setFragment(NULL);
	}
  }

  void Request::setReferrerRef(String referrerUri) {
	setReferrerRef(new Reference(referrerUri));
  }

  void Request::setResourceRef(Reference resourceRef) {
	this->resourceRef = resourceRef;
  }

  void Request::setResourceRef(String resourceUri) {
	if (getResourceRef() != NULL) {
	  // Allow usage of URIs relative to the current base reference
	  setResourceRef(new Reference(getResourceRef().getBaseRef(),
								   resourceUri));
	} else {
	  setResourceRef(new Reference(resourceUri));
	}
  }

  void Request::setRootRef(Reference rootRef) {
	this->rootRef = rootRef;
  }

} // namespace echo

