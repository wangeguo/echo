#ifndef _ECHO_ROUTING_VIRTUAL_HOST_H_
#define _ECHO_ROUTING_VIRTUAL_HOST_H_
/*
  import java.net.InetAddress;
  import java.net.UnknownHostException;
*/

#include <string>

#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/resource/finder.h>

namespace echo {
namespace routing {

/**
 * Router of calls from Server connectors to Echos. The attached Echos are
 * typically Applications.<br>
 * <br>
 * A virtual host is defined along three properties:
 * <ul>
 * <li>request's {@link Request#getHostRef()}: the URI of the host that received
 * the request. Note that the same IP address can correspond to multiple domain
 * names and therefore receive request with different "hostRef" URIs.</li>
 * <li>request's {@link Request#getResourceRef()}: the URI of the target
 * resource of the request. If this reference is relative, then it is based on
 * the "hostRef", otherwise it is maintained as received. This difference is
 * useful for resources identified by URNs or for Web proxies or Web caches.</li>
 * <li>response's {@link Response#getServerInfo()}: the information about the
 * server connector receiving the requests such as it IP address and port
 * number.</li>
 * </ul>
 * When creating a new instance, you can define Java regular expressions (
 * {@link java.util.regex.Pattern}) that must match the domain name, port,
 * scheme for references or IP address and port number for server information.
 * The default values match everything.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @see java.util.regex.Pattern
 * @see <a href="http://en.wikipedia.org/wiki/Virtual_hosting">Wikipedia -
 *      Virtual Hosting</a>
 * @see <a href="http://httpd.apache.org/docs/2.2/vhosts/">Apache - Virtual
 *      Hosting</a>
 * @author Jerome Louvel
 */
class VirtualHost : public echo::routing::Router {

 public:

  /**
   * Returns the virtual host code associated to the current thread.
   * 
   * This variable is stored internally as a thread local variable and updated
   * each time a call is routed by a virtual host.
   * 
   * @return The current context.
   */
  static Integer getCurrent() {
    return CURRENT.get();
  }

  /**
   * Returns the IP address of a given domain name.
   * 
   * @param domain
   *            The domain name.
   * @return The IP address.
   */
  static std::string getIpAddress(std::string domain) {
    std::string result = null;

    try {
      result = InetAddress.getByName(domain).getHostAddress();
    } catch (UnknownHostException e) {
    }

    return result;
  }

  /**
   * Returns the local host IP address.
   * 
   * @return The local host IP address.
   */
  static std::string getLocalHostAddress() {
    std::string result = null;

    try {
      result = InetAddress.getLocalHost().getHostAddress();
    } catch (UnknownHostException e) {
    }

    return result;
  }

  /**
   * Returns the local host name.
   * 
   * @return The local host name.
   */
  static std::string getLocalHostName() {
    std::string result = null;

    try {
      result = InetAddress.getLocalHost().getHostName();
    } catch (UnknownHostException e) {
    }

    return result;
  }

  /**
   * Sets the virtual host code associated with the current thread.
   * 
   * @param code
   *            The thread's virtual host code.
   */
  static void setCurrent(Integer code) {
    CURRENT.set(code);
  }

  /**
   * Constructor. Note that usage of this constructor is not recommended as
   * the Router won't have a proper context set. In general you will prefer to
   * use the other constructor and pass it the parent component's context.
   */
  VirtualHost() {
    VirtualHost(null);
  }

  /**
   * Constructor. Accepts all incoming requests by default, use the set
   * methods to restrict the matchable patterns.
   * 
   * @param parentContext
   *            The parent component's context.
   */
  VirtualHost(echo::Context parentContext) {
    VirtualHost(parentContext, ".*", ".*", ".*", ".*", ".*", ".*", ".*", ".*");
  }

  /**
   * Constructor.
   * 
   * @param parentContext
   *            The parent component's context.
   * @param hostDomain
   *            The hostRef host domain pattern to match.
   * @param hostPort
   *            The hostRef host port pattern to match.
   * @param hostScheme
   *            The hostRef scheme protocol pattern to match.
   * @param resourceDomain
   *            The resourceRef host domain pattern to match.
   * @param resourcePort
   *            The resourceRef host port pattern to match.
   * @param resourceScheme
   *            The resourceRef scheme protocol pattern to match.
   * @param serverAddress
   *            The listening server address pattern to match.
   * @param serverPort
   *            The listening server port pattern to match.
   */
  VirtualHost(echo::Context parentContext, std::string hostDomain,
              std::string hostPort, std::string hostScheme, std::string resourceDomain,
              std::string resourcePort, std::string resourceScheme, std::string serverAddress,
              std::string serverPort) {
    super((parentContext == null) ? null : parentContext
          .createChildContext());
        
    // Override Router's default modes 
    setDefaultMatchingMode(Template.MODE_STARTS_WITH);
    setRoutingMode(MODE_BEST_MATCH);

    this->parentContext = parentContext;

    this->hostDomain = hostDomain;
    this->hostPort = hostPort;
    this->hostScheme = hostScheme;

    this->resourceDomain = resourceDomain;
    this->resourcePort = resourcePort;
    this->resourceScheme = resourceScheme;

    this->serverAddress = serverAddress;
    this->serverPort = serverPort;
  }

  /**
   * Attaches a target Echo to this router with an empty URI pattern. A new
   * route will be added routing to the target when any call is received.
   * 
   * In addition to super class behavior, this method will set the context of
   * the target if it is empty by creating a protected context via the
   * {@link Context#createChildContext()} method.
   * 
   * @param target
   *            The target Echo to attach.
   * @return The created route.
   */
  //@Override
  //@SuppressWarnings("deprecation")
  Route attach(Echo::Echo target) {
    if ((target.getContext() == null) && (parentContext != null)) {
      target.setContext(parentContext.createChildContext());
    }

    return super.attach(target);
  }

  /**
   * Attaches a target Echo to this router based on a given URI pattern. A
   * new route will be added routing to the target when calls with a URI
   * matching the pattern will be received.
   * 
   * In addition to super class behavior, this method will set the context of
   * the target if it is empty by creating a protected context via the
   * {@link Context#createChildContext()} method.
   * 
   * @param uriPattern
   *            The URI pattern that must match the relative part of the
   *            resource URI.
   * @param target
   *            The target Echo to attach.
   * @return The created route.
   */
  //@Override
  //@SuppressWarnings("deprecation")
  Route attach(std::string uriPattern, Echo::Echo target) {
    if ((target.getContext() == null) && (parentContext != null)) {
      target.setContext(parentContext.createChildContext());
    }

    return super.attach(uriPattern, target);
  }

  /**
   * Attaches a Echo to this router as the default target to invoke when no
   * route matches. It actually sets a default route that scores all calls to
   * 1.0.
   * 
   * In addition to super class behavior, this method will set the context of
   * the target if it is empty by creating a protected context via the
   * {@link Context#createChildContext()} method.
   * 
   * @param defaultTarget
   *            The Echo to use as the default target.
   * @return The created route.
   */
  //@Override
  //@SuppressWarnings("deprecation")
  Route attachDefault(Echo::Echo defaultTarget) {
    if ((defaultTarget.getContext() == null)
        && (parentContext != null)) {
      defaultTarget.setContext(parentContext.createChildContext());
    }

    return super.attachDefault(defaultTarget);
  }

  /**
   * Creates a new finder instance based on the "targetClass" property.
   * 
   * In addition to super class behavior, this method will set the context of
   * the finder by creating a protected context via the
   * {@link Context#createChildContext()} method.
   * 
   * @param targetClass
   *            The target Resource class to attach.
   * @return The new finder instance.
   */
  //@Override
  Finder createFinder(Class<?> targetClass) {
    Finder result = super.createFinder(targetClass);
    result.setContext(getContext().createChildContext());
    return result;
  }


  /**
   * Returns the hostRef host domain to match. Uses patterns in
   * java.util.regex.
   * 
   * @return The hostRef host domain to match.
   */
  std::string getHostDomain() {
    return hostDomain;
  }

  /**
   * Returns the hostRef host port to match. Uses patterns in java.util.regex.
   * 
   * @return The hostRef host port to match.
   */
  std::string getHostPort() {
    return hostPort;
  }

  /**
   * Returns the hostRef scheme to match. Uses patterns in java.util.regex.
   * 
   * @return The hostRef scheme to match.
   */
  std::string getHostScheme() {
    return hostScheme;
  }

  /**
   * Returns the display name.
   * 
   * @return The display name.
   */
  std::string getName() {
    return name;
  }

  /**
   * Returns the resourceRef host domain to match. Uses patterns in
   * java.util.regex.
   * 
   * @return The resourceRef host domain to match.
   */
  std::string getResourceDomain() {
    return resourceDomain;
  }

  /**
   * Returns the resourceRef host port to match. Uses patterns in
   * java.util.regex.
   * 
   * @return The resourceRef host port to match.
   */
  std::string getResourcePort() {
    return resourcePort;
  }

  /**
   * Returns the resourceRef scheme to match. Uses patterns in
   * java.util.regex.
   * 
   * @return The resourceRef scheme to match.
   */
  std::string getResourceScheme() {
    return resourceScheme;
  }

  /**
   * Returns the listening server address. Uses patterns in java.util.regex.
   * 
   * @return The listening server address.
   */
  std::string getServerAddress() {
    return serverAddress;
  }

  /**
   * Returns the listening server port. Uses patterns in java.util.regex.
   * 
   * @return The listening server port.
   */
  std::string getServerPort() {
    return serverPort;
  }

  /**
   * Sets the hostRef host domain to match. Uses patterns in java.util.regex.
   * 
   * @param hostDomain
   *            The hostRef host domain to match.
   */
  void setHostDomain(std::string hostDomain) {
    this->hostDomain = hostDomain;
  }

  /**
   * Sets the hostRef host port to match. Uses patterns in java.util.regex.
   * 
   * @param hostPort
   *            The hostRef host port to match.
   */
  void setHostPort(std::string hostPort) {
    this->hostPort = hostPort;
  }

  /**
   * Sets the hostRef scheme to match. Uses patterns in java.util.regex.
   * 
   * @param hostScheme
   *            The hostRef scheme to match.
   */
  void setHostScheme(std::string hostScheme) {
    this->hostScheme = hostScheme;
  }

  /**
   * Sets the display name.
   * 
   * @param name
   *            The display name.
   */
  void setName(std::string name) {
    this->name = name;
  }

  /**
   * Sets the resourceRef host domain to match. Uses patterns in
   * java.util.regex.
   * 
   * @param resourceDomain
   *            The resourceRef host domain to match.
   */
  void setResourceDomain(std::string resourceDomain) {
    this->resourceDomain = resourceDomain;
  }

  /**
   * Sets the resourceRef host port to match. Uses patterns in
   * java.util.regex.
   * 
   * @param resourcePort
   *            The resourceRef host port to match.
   */
  void setResourcePort(std::string resourcePort) {
    this->resourcePort = resourcePort;
  }

  /**
   * Sets the resourceRef scheme to match. Uses patterns in java.util.regex.
   * 
   * @param resourceScheme
   *            The resourceRef scheme to match.
   */
  void setResourceScheme(std::string resourceScheme) {
    this->resourceScheme = resourceScheme;
  }

  /**
   * Sets the listening server address. Uses patterns in java.util.regex.
   * 
   * @param serverAddress
   *            The listening server address.
   */
  void setServerAddress(std::string serverAddress) {
    this->serverAddress = serverAddress;
  }

  /**
   * Sets the listening server port. Uses patterns in java.util.regex.
   * 
   * @param serverPort
   *            The listening server port.
   */
  void setServerPort(std::string serverPort) {
    this->serverPort = serverPort;
  }

 protected:
  //@Override
  //@SuppressWarnings("deprecation")
  Route createRoute(std::string uriPattern, Echo::Echo target) {
    return new Route(this, uriPattern, target) {
      @Override
      protected int beforeHandle(echo::Request request, echo::Response response) {
        const int result = super.beforeHandle(request, response);

        // Set the request's root reference
        request.setRootRef(request.getResourceRef().getBaseRef());

        // Save the hash code of the current host
        setCurrent(VirtualHost.this->hashCode());

        return result;
      }
    };
  }

 private:
  static const ThreadLocal<Integer> CURRENT = new ThreadLocal<Integer>();
  /** The hostRef host domain pattern to match. */
  volatile std::string hostDomain;

  /** The hostRef host port pattern to match. */
  volatile std::string hostPort;

  /** The hostRef scheme pattern to match. */
  volatile std::string hostScheme;

  /** The display name. */
  volatile std::string name;

  /** The resourceRef host domain pattern to match. */
  volatile std::string resourceDomain;

  /** The resourceRef host port pattern to match. */
  volatile std::string resourcePort;

  /** The resourceRef scheme pattern to match. */
  volatile std::string resourceScheme;

  /** The listening server address pattern to match. */
  volatile std::string serverAddress;

  /** The listening server port pattern to match. */
  volatile std::string serverPort;

  /** The parent component's context. */
  volatile echo::Context parentContext;
};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_VIRTUAL_HOST_H_
