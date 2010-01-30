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
  void extractCookie(std::string attribute, std::string cookieName, bool first);

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
  void extractEntity(std::string attribute, std::string parameter, bool first);

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
  void extractQuery(std::string attribute, std::string parameter, bool first);

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
  int beforeHandle(echo::Request request, echo::Response response);

 private:
  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getCookieExtracts(); 

  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getEntityExtracts();

  /**
   * Returns the list of query extracts.
   * 
   * @return The list of query extracts.
   */
  std::list<ExtractInfo> getQueryExtracts();

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
