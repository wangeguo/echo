#ifndef _ECHO_ROUTING_ROUTE_H_
#define _ECHO_ROUTING_ROUTE_H_

/*

  import java.util.concurrent.CopyOnWriteArrayList;
  import java.util.regex.Pattern;
*/

#include <string>
#include <list>

#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/cookie.h>
#include <echo/data/form.h>
#include <echo/data/reference.h>
#include <echo/data/status.h>
#include <echo/util/series.h>
#include <echo/util/logging/level.h>

namespace echo {
namespace routing {

/**
 * Filter scoring the affinity of calls with the attached Echo. The score is
 * used by an associated Router in order to determine the most appropriate
 * Echo for a given call. The routing is based on a reference template. It
 * also supports the extraction of some attributes from a call.<br>
 * <br>
 * Multiple extractions can be defined, based on the query string of the
 * resource reference, on the request form (ex: posted from a browser) or on
 * cookies.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @see echo::routing::Template
 * @author Jerome Louvel
 * @deprecated Use {@link TemplateRoute} instead.
 */
//@Deprecated
class Route : public echo::routing::TemplateRoute {

 public:

  /**
   * Constructor behaving as a simple extractor filter.
   * 
   * @param next
   *            The next Echo.
   */
  Route(echo::Echo next) {
    Route(null, (Template) null, next);
  }

  /**
   * Constructor. The URIs will be matched agains the template using the
   * {@link Template#MODE_STARTS_WITH} matching mode. This can be changed by
   * getting the template and calling {@link Template#setMatchingMode(int)}
   * with {@link Template#MODE_EQUALS} for exact matching.
   * 
   * @param router
   *            The parent router.
   * @param uriTemplate
   *            The URI template.
   * @param next
   *            The next Echo.
   */
  Route(Router router, std::string uriTemplate, Restlet next) {
    Route(router, new Template(uriTemplate, Template.MODE_STARTS_WITH,
                               Variable.TYPE_URI_SEGMENT, "", true, false), next);
  }

  /**
   * Constructor.
   * 
   * @param router
   *            The parent router.
   * @param template
   *            The URI template.
   * @param next
   *            The next Echo.
   */
  Route(Router router, Template template, Restlet next) {
    super(router, template, next);
  }



  /**
   * Extracts an attribute from the request cookies.
   * 
   * @param attribute
   *            The name of the request attribute to set.
   * @param cookieName
   *            The name of the cookies to extract.
   * @param first
   *            Indicates if only the first cookie should be set. Otherwise as
   *            a List instance might be set in the attribute value.
   * @return The current Filter.
   */
  Route extractCookie(std::string attribute, std::string cookieName,
                      bool first) {
    getCookieExtracts().add(new ExtractInfo(attribute, cookieName, first));
    return this;
  }

  /**
   * Extracts an attribute from the request entity form.
   * 
   * @param attribute
   *            The name of the request attribute to set.
   * @param parameter
   *            The name of the entity form parameter to extract.
   * @param first
   *            Indicates if only the first cookie should be set. Otherwise as
   *            a List instance might be set in the attribute value.
   * @return The current Filter.
   */
  Route extractEntity(std::string attribute, std::string parameter, bool first) {
    getEntityExtracts().add(new ExtractInfo(attribute, parameter, first));
    return this;
  }

  /**
   * Extracts an attribute from the query string of the resource reference.
   * 
   * @param attribute
   *            The name of the request attribute to set.
   * @param parameter
   *            The name of the query string parameter to extract.
   * @param first
   *            Indicates if only the first cookie should be set. Otherwise as
   *            a List instance might be set in the attribute value.
   * @return The current Filter.
   */
  Route extractQuery(std::string attribute, std::string parameter, bool first) {
    getQueryExtracts().add(new ExtractInfo(attribute, parameter, first));
    return this;
  }

  
  /**
   * Checks the request attributes for presence, format, etc. If the check
   * fails, then a response status CLIENT_ERROR_BAD_REQUEST is returned with
   * the proper status description.
   * 
   * @param attribute
   *            Name of the attribute to look for.
   * @param required
   *            Indicates if the attribute presence is required.
   * @param format
   *            Format of the attribute value, using Regex pattern syntax.
   */
  void validate(std::string attribute, bool required, std::string format) {
    getValidations().add(new ValidateInfo(attribute, required, format));
  }

 protected:
  /**
   * Allows filtering before its handling by the target Echo. By default it
   * parses the template variable, adjust the base reference, then extracts
   * the attributes from form parameters (query, cookies, entity) and finally
   * tries to validates the variables as indicated by the
   * {@link #validate(std::string, bool, std::string)} method.
   * 
   * @param request
   *            The request to filter.
   * @param response
   *            The response to filter.
   * @return The continuation status.
   */
  //@Override
  int beforeHandle(Request request, Response response) {
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
  
 private:
  /**
   * Extracts the attributes value from the request.
   * 
   * @param request
   *            The request to process.
   * @param response
   *            The response to process.
   */
  void extractAttributes(Request request, Response response) {
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


  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getCookieExtracts() {
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

  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getEntityExtracts() {
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

  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getQueryExtracts() {
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

  /**
   * Returns the list of attribute validations.
   * 
   * @return The list of attribute validations.
   */
  std::list<ValidateInfo> getValidations() {
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

  /**
   * Validates the attributes from the request.
   * 
   * @param request
   *            The request to process.
   * @param response
   *            The response to process.
   */
  void validateAttributes(Request request, Response response) {
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

    
  /** Internal class holding extraction information. */
  static const class ExtractInfo {
   public:
    /**
     * Constructor.
     * 
     * @param attribute
     *            Target attribute name.
     * @param parameter
     *            Name of the parameter to look for.
     * @param first
     *            Indicates how to handle repeating values.
     */
    ExtractInfo(std::string attribute, std::string parameter, bool first) {
      this->attribute = attribute;
      this->parameter = parameter;
      this->first = first;
    }
    
   protected:
    /** Target attribute name. */
    volatile std::string attribute;

    /** Indicates how to handle repeating values. */
    volatile bool first;

    /** Name of the parameter to look for. */
    volatile std::string parameter;

  }

    /** Internal class holding validation information. */
    static const class ValidateInfo {

     public:
      /**
       * Constructor.
       * 
       * @param attribute
       *            Name of the attribute to look for.
       * @param required
       *            Indicates if the attribute presence is required.
       * @param format
       *            Format of the attribute value, using Regex pattern syntax.
       */
      ValidateInfo(std::string attribute, bool required, std::string format) {
        this->attribute = attribute;
        this->required = required;
        this->format = format;
      }
    
     protected:
      /** Name of the attribute to look for. */
      volatile std::string attribute;

      /** Format of the attribute value, using Regex pattern syntax. */
      volatile std::string format;

      /** Indicates if the attribute presence is required. */
      volatile bool required;


    };

  /** The list of cookies to extract. */
  volatile std::list<ExtractInfo> cookieExtracts;

  /** The list of request entity parameters to extract. */
  volatile std::list<ExtractInfo> entityExtracts;

  /** The list of query parameters to extract. */
  volatile std::list<ExtractInfo> queryExtracts;

  /** The list of attribute validations. */
  volatile std::list<ValidateInfo> validations;

};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_ROUTE_H_
