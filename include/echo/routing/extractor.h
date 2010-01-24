#ifndef _ECHO_ROUTING_EXTRACTOR_H_
#define _ECHO_ROUTING_EXTRACTOR_H_

/*
  import java.util.concurrent.CopyOnWriteArrayList;
*/

#include <list>
#include <string>

#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/cookie.h>
#include <echo/data/form.h>
#include <echo/util/series.h>

namespace echo {
namespace routing {

/**
 * Filter extracting attributes from a call. Multiple extractions can be
 * defined, based on the query string of the resource reference, on the request
 * form (ex: posted from a browser) or on cookies.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @author Jerome Louvel
 */

class Extractor : public echo::routing::Filter {

 public:
  /**
   * Constructor.
   */
  Extractor() {
    Extractor(NULL);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   */
  Extractor(echo::Context context) {
    Extractor(context, NULL);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   * @param next
   *            The next Echo.
   */
  Extractor(echo::Context context, Echo::Echo next) {
    Filter(context, next);
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
   */
  void extractCookie(std::string attribute, std::string cookieName, bool first) {
    getCookieExtracts().add(new ExtractInfo(attribute, cookieName, first));
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
   */
  void extractEntity(std::string attribute, std::string parameter, bool first) {
    getEntityExtracts().add(new ExtractInfo(attribute, parameter, first));
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
   */
  void extractQuery(std::string attribute, std::string parameter, bool first) {
    getQueryExtracts().add(new ExtractInfo(attribute, parameter, first));
  }

 protected:
  /**
   * Allows filtering before its handling by the target Echo. By default it
   * extracts the attributes from form parameters (query, cookies, entity) and
   * finally puts them in the request's attributes (
   * {@link Request#getAttributes()}).
   * 
   * @param request
   *            The request to filter.
   * @param response
   *            The response to filter.
   * @return The continuation status.
   */
  //@Override
  int beforeHandle(echo::Request request, echo::Response response) {
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

 private:
  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getCookieExtracts() {
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

  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getEntityExtracts() {
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

  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getQueryExtracts() {
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
    std::string attribute;

    /** Indicates how to handle repeating values. */
    bool first;

    /** Name of the parameter to look for. */
    std::string parameter;

  };

  /** The list of cookies to extract. */
  volatile std::list<ExtractInfo> cookieExtracts;

  /** The list of request entity parameters to extract. */
  volatile std::list<ExtractInfo> entityExtracts;

  /** The list of query parameters to extract. */
  volatile std::list<ExtractInfo> queryExtracts;

};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_EXTRACTOR_H_
