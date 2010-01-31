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
  Route(Router router, std::string uriTemplate, echo::Echo next);

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
  Route(Router router, Template template, echo::Echo next) {
    TemplateRoute(router, template, next);
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
                      bool first);

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
  Route extractEntity(std::string attribute, std::string parameter, bool first);

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
  Route extractQuery(std::string attribute, std::string parameter, bool first);

  
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
  void validate(std::string attribute, bool required, std::string format);

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
  int beforeHandle(echo::Request request, echo::Response response);
  
 private:
  /**
   * Extracts the attributes value from the request.
   * 
   * @param request
   *            The request to process.
   * @param response
   *            The response to process.
   */
  void extractAttributes(echo::Request request, echo::Response response);


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

  /**
   * Returns the list of attribute validations.
   * 
   * @return The list of attribute validations.
   */
  std::list<ValidateInfo> getValidations();

  /**
   * Validates the attributes from the request.
   * 
   * @param request
   *            The request to process.
   * @param response
   *            The response to process.
   */
  void validateAttributes(echo::Request request, echo::Response response);

    
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

  };

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
