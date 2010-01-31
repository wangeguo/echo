#include <echo/routing/route.h>

namespace echo {
namespace routing {

Route::Route(Router router, std::string uriTemplate, echo::Echo next) {
  Route(router, new Template(uriTemplate, Template.MODE_STARTS_WITH,
                             Variable.TYPE_URI_SEGMENT, "", true, false), next);
}

Route::Route Route::extractCookie(std::string attribute, std::string cookieName,
                                  bool first) {
  getCookieExtracts().add(new ExtractInfo(attribute, cookieName, first));
  return this;
}
Route::Route Route::extractEntity(std::string attribute, std::string parameter, bool first) {
  getEntityExtracts().add(new ExtractInfo(attribute, parameter, first));
  return this;
}

Route::Route Route::extractQuery(std::string attribute, std::string parameter, bool first) {
  getQueryExtracts().add(new ExtractInfo(attribute, parameter, first));
  return this;
}

void Route::validate(std::string attribute, bool required, std::string format) {
  getValidations().add(new ValidateInfo(attribute, required, format));
}

int Route::beforeHandle(echo::Request request, echo::Response response) {
  // 1 - Parse the template variables and adjust the base reference
  if (getTemplate() != null) {
    const std::string remainingPart = request.getResourceRef()
                                      .getRemainingPart(false, isMatchingQuery());
    const int matchedLength = getTemplate().parse(remainingPart,
                                                  request);
      
    if (getLogger().isLoggable(Level.FINER)) {
      getLogger().finer(
          "Attempting to match this pattern: "
          + getTemplate().getPattern() + " >> "
          + matchedLength);
    }

    if (matchedLength != -1) {
      // Updates the context
      const std::string matchedPart = remainingPart.substring(0,
                                                              matchedLength);
      Reference baseRef = request.getResourceRef().getBaseRef();

      if (baseRef == null) {
        baseRef = new Reference(matchedPart);
      } else {
        baseRef = new Reference(baseRef.toString(false, false)
                                + matchedPart);
      }

      request.getResourceRef().setBaseRef(baseRef);

      if (getLogger().isLoggable(Level.FINE)) {
        getLogger().fine(
            "New base URI: "
            + request.getResourceRef().getBaseRef());
        getLogger().fine(
            "New remaining part: "
            + request.getResourceRef()
            .getRemainingPart(false,
                              isMatchingQuery()));
      }

      if (getLogger().isLoggable(Level.FINE)) {
        getLogger().fine(
            "Delegating the call to the target Echo");
      }
    } else {
      response.setStatus(Status.CLIENT_ERROR_NOT_FOUND);
    }
  }

  // 2 - Extract the attributes from form parameters (query, cookies,
  // entity).
  extractAttributes(request, response);

  // 3 - Validate the attributes extracted (or others)
  validateAttributes(request, response);

  return CONTINUE;
}
  
void Route::extractAttributes(echo::Request request, echo::Response response) {
  // Extract the query parameters
  if (!getQueryExtracts().isEmpty()) {
    const Form form = request.getResourceRef().getQueryAsForm();

    if (form != null) {
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

    if (form != null) {
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

    if (cookies != null) {
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
}

std::list<ExtractInfo> Route::getCookieExtracts() {
  // Lazy initialization with double-check.
  std::list<ExtractInfo> ce = cookieExtracts;
  if (ce == null) {
    synchronized (this) {
      ce = cookieExtracts;
      if (ce == null) {
        cookieExtracts = ce = new CopyOnWriteArrayList<ExtractInfo>();
      }
    }
  }
  return ce;
}

std::list<ExtractInfo> Route::getEntityExtracts() {
  // Lazy initialization with double-check.
  std::list<ExtractInfo> ee = entityExtracts;
  if (ee == null) {
    synchronized (this) {
      ee = entityExtracts;
      if (ee == null) {
        entityExtracts = ee = new CopyOnWriteArrayList<ExtractInfo>();
      }
    }
  }
  return ee;
}

std::list<ExtractInfo> Route::getQueryExtracts() {
  // Lazy initialization with double-check.
  std::list<ExtractInfo> qe = queryExtracts;
  if (qe == null) {
    synchronized (this) {
      qe = queryExtracts;
      if (qe == null) {
        queryExtracts = qe = new CopyOnWriteArrayList<ExtractInfo>();
      }
    }
  }
  return qe;
}

std::list<ValidateInfo> Route::getValidations() {
  // Lazy initialization with double-check.
  std::list<ValidateInfo> v = validations;
  if (v == null) {
    synchronized (this) {
      v = validations;
      if (v == null) {
        validations = v = new CopyOnWriteArrayList<ValidateInfo>();
      }
    }
  }
  return v;
}

void Route::validateAttributes(echo::Request request, echo::Response response) {
  if (validations != null) {
    for (const ValidateInfo validate : getValidations()) {
      if (validate.required
          && !request.getAttributes().containsKey(
              validate.attribute)) {
        response
            .setStatus(
                Status.CLIENT_ERROR_BAD_REQUEST,
                "Unable to find the \""
                + validate.attribute
                + "\" attribute in the request. Please check your request.");
      } else if (validate.format != null) {
        const Object value = request.getAttributes().get(
            validate.attribute);
        if (value == null) {
          response
              .setStatus(
                  Status.CLIENT_ERROR_BAD_REQUEST,
                  "Unable to validate the \""
                  + validate.attribute
                  + "\" attribute with a null value. Please check your request.");
        } else {
          if (!Pattern.matches(validate.format, value.toString())) {
            response
                .setStatus(
                    Status.CLIENT_ERROR_BAD_REQUEST,
                    "Unable to validate the value of the \""
                    + validate.attribute
                    + "\" attribute. The expected format is: "
                    + validate.format
                    + " (Java Regex). Please check your request.");
          }
        }
      }
    }
  }
}

} // namespace routing
} // namespace echo
