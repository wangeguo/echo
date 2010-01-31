#ifndef _ECHO_ROUTING_ROUTER_H_
#define _ECHO_ROUTING_ROUTER_H_

#include <string>
#include <echo/util/logging/level.h>
#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.>
#include <echo/data/status.h>
#include <echo/resource/directory.h>
#include <echo/resource/finder.h>
#include <echo/util/route-list.h>

namespace echo {
namespace routing {

/**
 * Echo routing calls to one of the attached routes. Each route can compute
 * an affinity score for each call depending on various criteria. The attach()
 * method allow the creation of routes based on URI patterns matching the
 * beginning of a the resource reference's remaining part.<br>
 * <br>
 * In addition, several routing modes are supported, implementing various
 * algorithms:
 * <ul>
 * <li>Best match</li>
 * <li>First match (default)</li>
 * <li>Last match</li>
 * <li>Random match</li>
 * <li>Round robin</li>
 * <li>Custom</li>
 * </ul>
 * <br>
 * Note that for routes using URI patterns will update the resource reference's
 * base reference during the routing if they are selected. It is also important
 * to know that the routing is very strict about path separators in your URI
 * patterns. Finally, you can modify the list of routes while handling incoming
 * calls as the delegation code is ensured to be thread-safe.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @see <a
 *      href="http://www.restlet.org/documentation/2.0/tutorial#part11">Tutorial:
 *      Routers and hierarchical URIs</a>
 * @author Jerome Louvel
 */
class Router : public echo::Echo {

 public:

  /**
   * Constructor. Note that usage of this constructor is not recommended as
   * the Router won't have a proper context set. In general you will prefer to
   * use the other constructor and pass it the parent application's context or
   * eventually the parent component's context if you don't use applications.
   */
  Router() {
    Router(null);
  }
  
  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   */
  Router(echo::Context context);

  /**
   * Attaches a target Echo to this router with an empty URI pattern. A new
   * route will be added routing to the target when any call is received.
   * 
   * @param target
   *            The target Echo to attach.
   * @return The created route.
   */
  //@SuppressWarnings("deprecation")
  Route attach(echo::Echo target) {
    return attach("", target);
  }

  /**
   * Attaches a target Resource class to this router based on a given URI
   * pattern. A new route will be added routing to the target when calls with
   * a URI matching the pattern will be received.
   * 
   * @param pathTemplate
   *            The URI path template that must match the relative part of the
   *            resource URI.
   * @param targetClass
   *            The target Resource class to attach.
   * @return The created route.
   */
  //@SuppressWarnings("deprecation")
  Route attach(std::string pathTemplate, Class<?> targetClass);

  /**
   * Attaches a target Echo to this router based on a given URI pattern. A
   * new route will be added routing to the target when calls with a URI
   * matching the pattern will be received.
   * 
   * @param pathTemplate
   *            The URI path template that must match the relative part of the
   *            resource URI.
   * @param target
   *            The target Echo to attach.
   * @return The created route.
   */
  //@SuppressWarnings("deprecation")
  Route attach(std::string pathTemplate, echo::Echo target);

  /**
   * Attaches a Resource class to this router as the default target to invoke
   * when no route matches. It actually sets a default route that scores all
   * calls to 1.0.
   * 
   * @param defaultTargetClass
   *            The target Resource class to attach.
   * @return The created route.
   */
  //@SuppressWarnings("deprecation")
  Route attachDefault(Class<?> defaultTargetClass);

  /**
   * Attaches a Echo to this router as the default target to invoke when no
   * route matches. It actually sets a default route that scores all calls to
   * 1.0.
   * 
   * @param defaultTarget
   *            The Echo to use as the default target.
   * @return The created route.
   */
  //@SuppressWarnings("deprecation")
  Route attachDefault(echo::Echo defaultTarget);

  /**
   * Creates a new finder instance based on the "targetClass" property.
   * 
   * @param targetClass
   *            The target Resource class to attach.
   * @return The new finder instance.
   */
  echo::resource::Finder createFinder(Class<?> targetClass);


  /**
   * Detaches the target from this router. All routes routing to this target
   * Echo are removed from the list of routes and the default route is set
   * to null.
   * 
   * @param target
   *            The target Echo to detach.
   */
  void detach(echo::Echo target);


  /**
   * Returns the default matching mode to use when selecting routes based on
   * URIs. By default it returns {@link Template#MODE_EQUALS}.
   * 
   * @return The default matching mode.
   */
  int getDefaultMatchingMode() {
    return defaultMatchingMode;
  }

  /**
   * Returns the default setting for whether the routing should be done on
   * URIs with or without taking into account query string. By default, it
   * returns false.
   * 
   * @return the default setting for whether the routing should be done on
   *         URIs with or without taking into account query string.
   */
  bool getDefaultMatchingQuery() {
    return getDefaultMatchQuery();
  }
    
  /**
   * Returns the default setting for whether the routing should be done on
   * URIs with or without taking into account query string. By default, it
   * returns false.
   * 
   * @return the default setting for whether the routing should be done on
   *         URIs with or without taking into account query string.
   * @deprecated Use {@link #getDefaultMatchingQuery()} instead.
   */
  //@Deprecated
  bool getDefaultMatchQuery() {
    return defaultMatchingQuery;
  }

  /**
   * Returns the default route to test if no other one was available after
   * retrying the maximum number of attempts.
   * 
   * @return The default route tested if no other one was available.
   */
  //@SuppressWarnings("deprecation")
  Route getDefaultRoute() {
    return defaultRoute;
  }

  /**
   * Returns the finder class to instantiate.
   * 
   * @return the finder class to instantiate.
   */
  Class<? extends Finder> getFinderClass() {
    return finderClass;
  }

  /**
   * Returns the maximum number of attempts if no attachment could be matched
   * on the first attempt. This is useful when the attachment scoring is
   * dynamic and therefore could change on a retry. The default value is set
   * to 1.
   * 
   * @return The maximum number of attempts if no attachment could be matched
   *         on the first attempt.
   */
  int getMaxAttempts() {
    return maxAttempts;
  }

  /**
   * Returns the next Echo if available.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   * @return The next Echo if available or null.
   */
  //@SuppressWarnings("deprecation")
  echo::Echo getNext(echo::Request request, echo::Response response);

  /**
   * Returns the minimum score required to have a match. By default, it
   * returns {@code 0.5}.
   * 
   * @return The minimum score required to have a match.
   */
  float getRequiredScore() {
    return requiredScore;
  }

  /**
   * Returns the delay in milliseconds before a new attempt is made. The
   * default value is {@code 500}.
   * 
   * @return The delay in milliseconds before a new attempt is made.
   */
  long getRetryDelay() {
    return retryDelay;
  }

  /**
   * Returns the modifiable list of routes. Creates a new instance if no one
   * has been set.
   * 
   * @return The modifiable list of routes.
   */
  RouteList getRoutes() {
    return routes;
  }

  /**
   * Returns the routing mode. By default, it returns the
   * {@link #MODE_FIRST_MATCH} mode.
   * 
   * @return The routing mode.
   */
  int getRoutingMode() {
    return routingMode;
  }

  /**
   * Handles a call by invoking the next Echo if it is available.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  //@Override
  void handle(echo::Request request, echo::Response response);


  /**
   * Sets the default matching mode to use when selecting routes based on
   * URIs. By default it is set to {@link Template#MODE_EQUALS}.
   * 
   * @param defaultMatchingMode
   *            The default matching mode.
   */
  void setDefaultMatchingMode(int defaultMatchingMode) {
    this->defaultMatchingMode = defaultMatchingMode;
  }

  /**
   * Sets the default setting for whether the routing should be done on URIs
   * with or without taking into account query string. By default, it is set
   * to false.
   * 
   * @param defaultMatchingQuery
   *            The default setting for whether the routing should be done on
   *            URIs with or without taking into account query string.
   *            
   */
  void setDefaultMatchingQuery(bool defaultMatchingQuery);

  /**
   * Sets the default setting for whether the routing should be done on URIs
   * with or without taking into account query string. By default, it is set
   * to false.
   * 
   * @param defaultMatchingQuery
   *            The default setting for whether the routing should be done on
   *            URIs with or without taking into account query string.
   * @deprecated Use {@link #setDefaultMatchingQuery(bool)} instead.
   */
  //@Deprecated
  void setDefaultMatchQuery(bool defaultMatchingQuery) {
    this->defaultMatchingQuery = defaultMatchingQuery;
  }
    
  /**
   * Sets the default route tested if no other one was available.
   * 
   * @param defaultRoute
   *            The default route tested if no other one was available.
   */
  //@SuppressWarnings("deprecation")
  void setDefaultRoute(Route defaultRoute) {
    this->defaultRoute = defaultRoute;
  }

  /**
   * Sets the finder class to instantiate.
   * 
   * @param finderClass
   *            The finder class to instantiate.
   */
  void setFinderClass(Class<? extends Finder> finderClass) {
    this->finderClass = finderClass;
  }

  /**
   * Sets the maximum number of attempts if no attachment could be matched on
   * the first attempt. This is useful when the attachment scoring is dynamic
   * and therefore could change on a retry.
   * 
   * @param maxAttempts
   *            The maximum number of attempts.
   */
  void setMaxAttempts(int maxAttempts) {
    this->maxAttempts = maxAttempts;
  }

  /**
   * Sets the score required to have a match. By default, it is set to {@code
   * 0.5}.
   * 
   * @param score
   *            The score required to have a match.
   */
  void setRequiredScore(float score) {
    requiredScore = score;
  }

  /**
   * Sets the delay in milliseconds before a new attempt is made. By default,
   * it is set to {@code 500}.
   * 
   * @param retryDelay
   *            The delay in milliseconds before a new attempt is made.
   */
  void setRetryDelay(long retryDelay) {
    this->retryDelay = retryDelay;
  }

  /**
   * Sets the modifiable list of routes.
   * 
   * @param routes
   *            The modifiable list of routes.
   */
  void setRoutes(RouteList routes) {
    this->routes = routes;
  }

  /**
   * Sets the routing mode. By default, it is set to the
   * {@link #MODE_FIRST_MATCH} mode.
   * 
   * @param routingMode
   *            The routing mode.
   */
  void setRoutingMode(int routingMode) {
    this->routingMode = routingMode;
  }

  /**
   * Starts the filter and the attached routes.
   */
  //@SuppressWarnings("deprecation")
  //@Override
  void start() throw (std::runtime_error);

  /**
   * Stops the filter and the attached routes.
   */
  //@SuppressWarnings("deprecation")
  //@Override
  void stop() throw (std::runtime_error);

  
 protected:
  /**
   * Creates a new route for the given URI pattern and target. If the target
   * is a {@link Directory}, then the matching mode of the created
   * {@link Route} is set to {@link Template#MODE_STARTS_WITH}, otherwise it
   * uses the {@link #getDefaultMatchingMode()} result. The route will match
   * the URI query string depending on the result of
   * {@link #getDefaultMatchingQuery()}.
   * 
   * @param uriPattern
   *            The URI pattern that must match the relative part of the
   *            resource URI.
   * @param target
   *            The target Echo to attach.
   * @return The created route.
   */
  //@SuppressWarnings("deprecation")
  Route createRoute(std::string uriPattern, echo::Echo target);

  /**
   * Effectively handles the call using the selected next {@link Echo},
   * typically the selected {@link Route}. By default, it just invokes the
   * next Echo.
   * 
   * @param next
   *            The next Echo to invoke.
   * @param request
   *            The request.
   * @param response
   *            The response.
   */
  void doHandle(echo::Echo next, echo::Request request, echo::Response response);

  /**
   * Returns the matched route according to a custom algorithm. To use in
   * combination of the {@link #MODE_CUSTOM} option. The default
   * implementation (to be overridden), returns null.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   * @return The matched route if available or null.
   */
  //@SuppressWarnings("deprecation")
  Route getCustom(echo::Request request, echo::Response response) {
    return null;
  }

  /**
   * Logs the route selected.
   * 
   * @param route
   *            The route selected.
   */
  //@SuppressWarnings("deprecation")
  void logRoute(Route route) {
    if (getLogger().isLoggable(Level.FINE)) {
      if (getDefaultRoute() == route) {
        getLogger().fine("The default route was selected.");
      } else {
        getLogger().fine("This route was selected: \"" + route + "\"");
      }
    }
  }


 public:
  
  /**
   * Each call will be routed to the route with the best score, if the
   * required score is reached.
   * 
   * @deprecated Use {@link #MODE_BEST_MATCH} instead.
   */
  //@Deprecated
  static const int BEST;

  /**
   * Each call will be routed according to a custom mode.
   * 
   * @deprecated Use {@link #MODE_CUSTOM} instead.
   */
  //@Deprecated
  static const int CUSTOM;

  /**
   * Each call is routed to the first route if the required score is reached.
   * If the required score is not reached, then the route is skipped and the
   * next one is considered.
   * 
   * @deprecated Use {@link #MODE_FIRST_MATCH} instead.
   */
  //@Deprecated
  static const int FIRST;

  /**
   * Each call will be routed to the last route if the required score is
   * reached. If the required score is not reached, then the route is skipped
   * and the previous one is considered.
   * 
   * @deprecated Use {@link #MODE_LAST_MATCH} instead.
   */
  //@Deprecated
  static const int LAST;

  /**
   * Each call will be routed to the route with the best score, if the
   * required score is reached.
   */
  static const int MODE_BEST_MATCH;

  /**
   * Each call will be routed according to a custom mode.
   */
  static const int MODE_CUSTOM;

  /**
   * Each call is routed to the first route if the required score is reached.
   * If the required score is not reached, then the route is skipped and the
   * next one is considered.
   */
  static const int MODE_FIRST_MATCH;

  /**
   * Each call will be routed to the last route if the required score is
   * reached. If the required score is not reached, then the route is skipped
   * and the previous one is considered.
   */
  static const int MODE_LAST_MATCH;

  /**
   * Each call is be routed to the next route target if the required score is
   * reached. The next route is relative to the previous call routed (round
   * robin mode). If the required score is not reached, then the route is
   * skipped and the next one is considered. If the last route is reached, the
   * first route will be considered.
   */
  static const int MODE_NEXT_MATCH;

  /**
   * Each call will be randomly routed to one of the routes that reached the
   * required score. If the random route selected is not a match then the
   * immediate next route is evaluated until one matching route is found. If
   * we get back to the initial random route selected with no match, then we
   * return null.
   */
  static const int MODE_RANDOM_MATCH;

  /**
   * Each call is be routed to the next route target if the required score is
   * reached. The next route is relative to the previous call routed (round
   * robin mode). If the required score is not reached, then the route is
   * skipped and the next one is considered. If the last route is reached, the
   * first route will be considered.
   * 
   * @deprecated Use {@link #MODE_NEXT_MATCH} instead.
   */
  //@Deprecated
  static const int NEXT;

  /**
   * Each call will be randomly routed to one of the routes that reached the
   * required score. If the random route selected is not a match then the
   * immediate next route is evaluated until one matching route is found. If
   * we get back to the initial random route selected with no match, then we
   * return null.
   * 
   * @deprecated Use {@link #MODE_RANDOM_MATCH} instead.
   */
  //@Deprecated
  static const int RANDOM;

 private:
  
  /** The default matching mode to use when selecting routes based on URIs. */
  volatile int defaultMatchingMode;

  /**
   * The default setting for whether the routing should be done on URIs with
   * or without taking into account query string.
   */
  volatile bool defaultMatchingQuery;

  /** The default route tested if no other one was available. */
  //@SuppressWarnings("deprecation")
  volatile Route defaultRoute;

  /** Finder class to instantiate. */
  volatile Class<? extends Finder> finderClass;

  /**
   * The maximum number of attempts if no attachment could be matched on the
   * first attempt.
   */
  volatile int maxAttempts;

  /** The minimum score required to have a match. */
  volatile float requiredScore;

  /** The delay (in milliseconds) before a new attempt. */
  volatile long retryDelay;

  /** The modifiable list of routes. */
  volatile RouteList routes;

  /** The routing mode. */
  volatile int routingMode;  
}; 

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_ROUTER_H_
