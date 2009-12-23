#include <echo/response.h>

namespace echo {

Response::Response(Request request) {
  this->age = 0;
  this->allowedMethods = null;
  this->challengeRequests = null;
  this->cookieSettings = null;
  this->dimensions = null;
  this->locationRef = null;
  this->proxyChallengeRequests = null;
  this->request = request;
  this->retryAfter = null;
  this->serverInfo = null;
  this->status = Status.SUCCESS_OK;
  this->onReceived = null;
}

set<Method> Response::getAllowedMethods() {
  // Lazy initialization with double-check.
  Set<Method> a = this->allowedMethods;
  if (a == null) {
    synchronized (this) {
      a = this->allowedMethods;
      if (a == null) {
        this->allowedMethods = a = new CopyOnWriteArraySet<Method>();
      }
    }
  }
  return a;
}

list<ChallengeRequest> Response::getChallengeRequests() {
  // Lazy initialization with double-check.
  List<ChallengeRequest> cr = this->challengeRequests;
  if (cr == null) {
    synchronized (this) {
      cr = this->challengeRequests;
      if (cr == null) {
        this->challengeRequests = cr = new CopyOnWriteArrayList<ChallengeRequest>();
      }
    }
  }
  return cr;
}

Series<CookieSetting> Response::getCookieSettings() {
  // Lazy initialization with double-check.
  Series<CookieSetting> c = this->cookieSettings;
  if (c == null) {
    synchronized (this) {
      c = this->cookieSettings;
      if (c == null) {
        this->cookieSettings = c = new CookieSettingSeries();
      }
    }
  }
  return c;
}

set<Dimension> Response::getDimensions() {
  if (this->dimensions == null) {
    this->dimensions = new CopyOnWriteArraySet<Dimension>();
  }
  return this->dimensions;
}

list<ChallengeRequest> Response::getProxyChallengeRequests() {
  // Lazy initialization with double-check.
  List<ChallengeRequest> cr = this->proxyChallengeRequests;
  if (cr == null) {
    synchronized (this) {
      cr = this->proxyChallengeRequests;
      if (cr == null) {
        this->proxyChallengeRequests = cr = new CopyOnWriteArrayList<ChallengeRequest>();
      }
    }
  }
  return cr;
}

ServerInfo Response::getServerInfo() {
  // Lazy initialization with double-check.
  ServerInfo s = this->serverInfo;
  if (s == null) {
    synchronized (this) {
      s = this->serverInfo;
      if (s == null) {
        this->serverInfo = s = new ServerInfo();
      }
    }
  }
  return s;
}

//@Override
boolean Response::isConfidential() {
  return getRequest().isConfidential();
}

void Response::redirectPermanent(Reference targetRef) {
  setLocationRef(targetRef);
  setStatus(Status.REDIRECTION_PERMANENT);
}

void Response::redirectPermanent(String targetUri) {
  setLocationRef(targetUri);
  setStatus(Status.REDIRECTION_PERMANENT);
}

void Response::redirectSeeOther(Reference targetRef) {
  setLocationRef(targetRef);
  setStatus(Status.REDIRECTION_SEE_OTHER);
}

void Response::redirectSeeOther(String targetUri) {
  setLocationRef(targetUri);
  setStatus(Status.REDIRECTION_SEE_OTHER);
}

void Response::redirectTemporary(Reference targetRef) {
  setLocationRef(targetRef);
  setStatus(Status.REDIRECTION_TEMPORARY);
}

void Response::redirectTemporary(String targetUri) {
  setLocationRef(targetUri);
  setStatus(Status.REDIRECTION_TEMPORARY);
}

//@Deprecated
void Response::setChallengeRequest(ChallengeRequest request) {
  final List<ChallengeRequest> requests = new CopyOnWriteArrayList<ChallengeRequest>();
  requests.add(request);
  setChallengeRequests(requests);
}

void Response::setChallengeRequests(List<ChallengeRequest> requests) {
  this->challengeRequests = requests;
}

void Response::setLocationRef(String locationUri) {
  Reference baseRef = null;

  if (getRequest().getResourceRef() != null) {
    if (getRequest().getResourceRef().getBaseRef() != null) {
      baseRef = getRequest().getResourceRef().getBaseRef();
    } else {
      baseRef = getRequest().getResourceRef();
    }
  }

  setLocationRef(new Reference(baseRef, locationUri).getTargetRef());
}

void Response::setStatus(Status status, String message) {
  setStatus(new Status(status, message));
}

void Response::setStatus(Status status, Throwable throwable) {
  setStatus(new Status(status, throwable));
}

void Response::setStatus(Status status, Throwable throwable, String message) {
  setStatus(new Status(status, throwable, message));
}

} // namespace echo

#endif // _ECHO_RESPONSE_H_
