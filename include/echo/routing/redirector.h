#ifndef _ECHO_ROUTING_REDIRECTOR_H_
#define _ECHO_ROUTING_REDIRECTOR_H_

#include <string>

#include <echo/client.h>
#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/reference.h>
#include <echo/data/status.h>
#include <echo/representation/representation.h>
#include <echo/util/logging/level.h>

namespace echo {
namespace routing {

/**
 * Rewrites URIs then redirects the call or the client to a new destination.
 * There are various redirection modes that you can choose from: client-side
 * redirections ({@link #MODE_CLIENT_FOUND}, {@link #MODE_CLIENT_PERMANENT},
 * {@link #MODE_CLIENT_SEE_OTHER}, {@link #MODE_CLIENT_TEMPORARY}) or
 * server-side redirections, similar to a reverse proxy (
 * {@link #MODE_CLIENT_DISPATCHER} and {@link #MODE_SERVER_DISPATCHER}).<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @see echo::routing::Template
 * @see <a
 *      href="http://www.restlet.org/documentation/2.0/tutorial#part10">Tutorial:
 *      URI rewriting and redirection</a>
 * @author Jerome Louvel
 */
class Redirector : public echo::Echo {

 public:
  /**
   * Constructor for the client dispatcher mode.
   * 
   * @param context
   *            The context.
   * @param targetTemplate
   *            The template to build the target URI.
   * @see echo::::routing::Template
   */
  Redirector(echo::Context context, std::string targetTemplate) {
    Redirector(context, targetTemplate, MODE_CLIENT_DISPATCHER);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   * @param targetPattern
   *            The pattern to build the target URI (using std::stringTemplate
   *            syntax and the CallModel for variables).
   * @param mode
   *            The redirection mode.
   */
  Redirector(echo::Context context, std::string targetPattern, int mode);

  /**
   * Returns the redirection mode.
   * 
   * @return The redirection mode.
   */
  int getMode() {
    return mode;
  }

  /**
   * Returns the target URI pattern.
   * 
   * @return The target URI pattern.
   */
  std::string getTargetTemplate() {
    return targetTemplate;
  }

  /**
   * Handles a call by redirecting using the selected redirection mode.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  //@Override
  void handle(echo::Request request, echo::Response response);


  /**
   * Sets the redirection mode.
   * 
   * @param mode
   *            The redirection mode.
   */
  void setMode(int mode) {
    this->mode = mode;
  }

  /**
   * Sets the target URI pattern.
   * 
   * @param targetTemplate
   *            The target URI pattern.
   */
  void setTargetTemplate(std::string targetTemplate) {
    this->targetTemplate = targetTemplate;
  }

 protected:
  /**
   * Redirects a given call to a target reference. In the default
   * implementation, the request HTTP headers, stored in the request's
   * attributes, are removed before dispatching. After dispatching, the
   * response HTTP headers are also removed to prevent conflicts with the main
   * call.
   * 
   * @param targetRef
   *            The target reference with URI variables resolved.
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  void redirectClientDispatcher(Reference targetRef,
                                echo::Request request, echo::Response response);

  /**
   * Redirects a given call to a target reference. In the default
   * implementation, the request HTTP headers, stored in the request's
   * attributes, are removed before dispatching. After dispatching, the
   * response HTTP headers are also removed to prevent conflicts with the main
   * call.
   * 
   * @param targetRef
   *            The target reference with URI variables resolved.
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   * @deprecated Use
   *             {@link #redirectClientDispatcher(Reference, echo::Request, echo::Response)}
   *             instead.
   */
  //@Deprecated
  void redirectDispatcher(Reference targetRef, echo::Request request,
                          echo::Response response);

  /**
   * Redirects a given call to a target reference. In the default
   * implementation, the request HTTP headers, stored in the request's
   * attributes, are removed before dispatching. After dispatching, the
   * response HTTP headers are also removed to prevent conflicts with the main
   * call.
   * 
   * @param targetRef
   *            The target reference with URI variables resolved.
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  void redirectServerDispatcher(Reference targetRef,
                                echo::Request request, echo::Response response);

  /**
   * Optionally rewrites the response entity returned in the MODE_CONNECTOR
   * mode. By default, it just returns the initial entity without any
   * modification.
   * 
   * @param initialEntity
   *            The initial entity returned.
   * @return The rewritten entity.
   */
  Representation rewrite(Representation initialEntity) {
    return initialEntity;
  }

  
  /**
   * Returns the target reference to redirect to.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   * @return The target reference to redirect to.
   */
  Reference getTargetRef(echo::Request request, echo::Response response);

 private:


  /**
   * Redirects a given call to a target reference. In the default
   * implementation, the request HTTP headers, stored in the request's
   * attributes, are removed before dispatching. After dispatching, the
   * response HTTP headers are also removed to prevent conflicts with the main
   * call.
   * 
   * @param targetRef
   *            The target reference with URI variables resolved.
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  void redirectDispatcher(Client dispatcher, Reference targetRef,
                          echo::Request request, echo::Response response);



 public:
  /**
   * In this mode, the client is permanently redirected to the URI generated
   * from the target URI pattern.<br>
   * 
   * @see Status#REDIRECTION_PERMANENT
   */
  static const int MODE_CLIENT_PERMANENT;

  /**
   * In this mode, the client is simply redirected to the URI generated from
   * the target URI pattern.<br>
   * 
   * @see Status#REDIRECTION_FOUND
   */
  static const int MODE_CLIENT_FOUND;

  /**
   * In this mode, the client is simply redirected to the URI generated from
   * the target URI pattern.<br>
   * 
   * @see Status#REDIRECTION_SEE_OTHER
   */
  static const int MODE_CLIENT_SEE_OTHER;

  /**
   * In this mode, the client is temporarily redirected to the URI generated
   * from the target URI pattern.<br>
   * 
   * @see Status#REDIRECTION_TEMPORARY
   */
  static const int MODE_CLIENT_TEMPORARY;

  /**
   * In this mode, the call is sent to the context's dispatcher. Once the
   * selected client connector has completed the request handling, the
   * response is normally returned to the client. In this case, you can view
   * the Redirector as acting as a transparent proxy Echo.<br>
   * <br>
   * Remember to add the required connectors to the parent Component and to
   * declare them in the list of required connectors on the
   * Application.connectorService property.<br>
   * <br>
   * Note that in this mode, the headers of HTTP requests, stored in the
   * request's attributes, are removed before dispatching. Also, when a HTTP
   * response comes back the headers are also removed.
   * 
   * @deprecated Use the {@link Redirector#MODE_CLIENT_DISPATCHER} instead.
   */
  //@Deprecated
  static const int MODE_DISPATCHER;

  /**
   * In this mode, the call is sent to the context's client dispatcher. Once
   * the selected client connector has completed the request handling, the
   * response is normally returned to the client. In this case, you can view
   * the Redirector as acting as a transparent proxy Echo.<br>
   * <br>
   * Remember to add the required connectors to the parent Component and to
   * declare them in the list of required connectors on the
   * Application.connectorService property.<br>
   * <br>
   * Note that in this mode, the headers of HTTP requests, stored in the
   * request's attributes, are removed before dispatching. Also, when a HTTP
   * response comes back the headers are also removed.
   * 
   * @see Context#getClientDispatcher()
   */
  static const int MODE_CLIENT_DISPATCHER;

  /**
   * In this mode, the call is sent to the context's server dispatcher. Once
   * the selected client connector has completed the request handling, the
   * response is normally returned to the client. In this case, you can view
   * the Redirector as acting as a transparent proxy Echo.<br>
   * <br>
   * Remember to add the required connectors to the parent Component and to
   * declare them in the list of required connectors on the
   * Application.connectorService property.<br>
   * <br>
   * Note that in this mode, the headers of HTTP requests, stored in the
   * request's attributes, are removed before dispatching. Also, when a HTTP
   * response comes back the headers are also removed.
   * 
   * @see Context#getServerDispatcher()
   */
  static const int MODE_SERVER_DISPATCHER;

 protected:
  /** The target URI pattern. */
  volatile std::string targetTemplate;

  /** The redirection mode. */
  volatile int mode;


};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_REDIRECTOR_H_
