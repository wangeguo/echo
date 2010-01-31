#ifndef _ECHO_ROUTING_TEMPLATE_ROUTE_H_
#define _ECHO_ROUTING_TEMPLATE_ROUTE_H_

#include <string>

#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/reference.h>
#include <echo/data/status.h>

#include <echo/util/logging/level.h>


namespace echo {
namespace routing {


/**
 * Filter scoring the affinity of calls with the attached Echo. The score is
 * used by an associated Router in order to determine the most appropriate
 * Echo for a given call. The routing is based on a reference template.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @see echo::routing::Template
 * @author Jerome Louvel
 */
class TemplateRoute : public echo::routing::Filter {

 public:
    
  /**
   * Constructor behaving as a simple extractor filter.
   * 
   * @param next
   *            The next Echo.
   */
  TemplateRoute(Echo::Echo next) {
    TemplateRoute(null, (Template) null, next);
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
  TemplateRoute(Router router, std::string uriTemplate, Echo::Echo next);

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
  TemplateRoute(Router router, Template template, Echo::Echo next);


  /**
   * Returns the matching mode to use on the template when parsing a formatted
   * reference.
   * 
   * @return The matching mode to use.
   */
  int getMatchingMode();

  /**
   * Indicates whether the query part should be taken into account when
   * matching a reference with the template.
   * 
   * @return True if the query part of the reference should be taken into
   *         account, false otherwise.
   * @deprecated Use {@link #isMatchingQuery()} instead.
   */
  //@Deprecated
  bool getMatchQuery() {
    return matchingQuery;
  }

  /**
   * Returns the parent router.
   * 
   * @return The parent router.
   */
  Router getRouter() {
    return router;
  }

  /**
   * Returns the reference template to match.
   * 
   * @return The reference template to match.
   */
  Template getTemplate() {
    return template;
  }

  /**
   * Indicates whether the query part should be taken into account when
   * matching a reference with the template.
   * 
   * @return True if the query part of the reference should be taken into
   *         account, false otherwise.
   */
  bool isMatchingQuery() {
    return getMatchQuery();
  }

  /**
   * Returns the score for a given call (between 0 and 1.0).
   * 
   * @param request
   *            The request to score.
   * @param response
   *            The response to score.
   * @return The score for a given call (between 0 and 1.0).
   */
  float score(echo::Request request, echo::Response response);

  /**
   * Sets the matching mode to use on the template when parsing a formatted
   * reference.
   * 
   * @param matchingMode
   *            The matching mode to use.
   */
  void setMatchingMode(int matchingMode);

  /**
   * Sets whether the matching should be done on the URI with or without query
   * string.
   * 
   * @param matchingQuery
   *            True if the matching should be done with the query string,
   *            false otherwise.
   */
  void setMatchingQuery(bool matchingQuery);

  /**
   * Sets whether the matching should be done on the URI with or without query
   * string.
   * 
   * @param matchingQuery
   *            True if the matching should be done with the query string,
   *            false otherwise.
   * @deprecated Use {@link #setMatchingQuery(bool)} instead.
   */
  //@Deprecated
  void setMatchQuery(bool matchingQuery) {
    this->matchingQuery = matchingQuery;
  }

  /**
   * Sets the parent router.
   * 
   * @param router
   *            The parent router.
   */
  void setRouter(Router router) {
    this->router = router;
  }

  /**
   * Sets the reference template to match.
   * 
   * @param template
   *            The reference template to match.
   */
  void setTemplate(Template template) {
    this->template = template;
  }

  //@Override
  std::string toString() {
    return (getTemplate() == null) ? super.toString() : getTemplate()
        .getPattern();
  }

 protected:
  /**
   * Allows filtering before its handling by the target Echo. By default it
   * parses the template variable, adjust the base reference of the target
   * resource's reference.
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
   * Indicates whether the query part should be taken into account when
   * matching a reference with the template.
   */
  volatile bool matchingQuery;

  /** The parent router. */
  volatile Router router;

  /** The reference template to match. */
  volatile Template template;

};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_TEMPLATE_ROUTE_H_
