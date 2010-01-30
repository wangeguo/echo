#include <echo/routing/extractor.h>

namespace echo {
namespace routing {

void Extractor::extractCookie(std::string attribute, std::string cookieName, bool first) {
  getCookieExtracts().add(new ExtractInfo(attribute, cookieName, first));
}

void Extractor::extractEntity(std::string attribute, std::string parameter, bool first) {
  getEntityExtracts().add(new ExtractInfo(attribute, parameter, first));
}

void Extractor::extractQuery(std::string attribute, std::string parameter, bool first) {
  getQueryExtracts().add(new ExtractInfo(attribute, parameter, first));
}

int Extractor::beforeHandle(echo::Request request, echo::Response response) {
  // Extract the query parameters
  if (!getQueryExtracts().isEmpty()) {
    const Form form = request.getResourceRef().getQueryAsForm();

    if (form != NULL) {
      for (const ExtractInfo ei : getQueryExtracts()) {
        if (ei.first) {
          request.getAttributes().put(ei.attribute,
                                      form.getFirstValue(ei.parameter));
        } else {
          request.getAttributes().put(ei.attribute,
                                      form.subList(ei.parameter));
        }
      }
    }
  }

  // Extract the request entity parameters
  if (!getEntityExtracts().isEmpty()) {
    const Form form = request.getEntityAsForm();

    if (form != NULL) {
      for (const ExtractInfo ei : getEntityExtracts()) {
        if (ei.first) {
          request.getAttributes().put(ei.attribute,
                                      form.getFirstValue(ei.parameter));
        } else {
          request.getAttributes().put(ei.attribute,
                                      form.subList(ei.parameter));
        }
      }
    }
  }

  // Extract the cookie parameters
  if (!getCookieExtracts().isEmpty()) {
    const Series<Cookie> cookies = request.getCookies();

    if (cookies != NULL) {
      for (const ExtractInfo ei : getCookieExtracts()) {
        if (ei.first) {
          request.getAttributes().put(ei.attribute,
                                      cookies.getFirstValue(ei.parameter));
        } else {
          request.getAttributes().put(ei.attribute,
                                      cookies.subList(ei.parameter));
        }
      }
    }
  }

  return CONTINUE;
}

std::list<Extractor::ExtractInfo> Extractor::getCookieExtracts() {
  // Lazy initialization with double-check.
  std::list<ExtractInfo> ce = this->cookieExtracts;
  if (ce == NULL) {
    synchronized (this) {
      ce = this->cookieExtracts;
      if (ce == NULL) {
        this->cookieExtracts = ce = new CopyOnWriteArrayList<ExtractInfo>();
      }
    }
  }
  return ce;
}

std::list<Extractor::ExtractInfo> Extractor::getEntityExtracts() {
  // Lazy initialization with double-check.
  std::list<ExtractInfo> ee = this->entityExtracts;
  if (ee == NULL) {
    synchronized (this) {
      ee = this->entityExtracts;
      if (ee == NULL) {
        this->entityExtracts = ee = new CopyOnWriteArrayList<ExtractInfo>();
      }
    }
  }
  return ee;
}

std::list<Extractor::ExtractInfo> Extractor::getQueryExtracts() {
  // Lazy initialization with double-check.
  std::list<ExtractInfo> qe = this->queryExtracts;
  if (qe == NULL) {
    synchronized (this) {
      qe = this->queryExtracts;
      if (qe == NULL) {
        this->queryExtracts = qe = new CopyOnWriteArrayList<ExtractInfo>();
      }
    }
  }
  return qe;
}

} // namespace routing
} // namespace echo

