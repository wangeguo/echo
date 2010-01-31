#include <echo/routing/virtual-host.h>

namespace echo {
namespace routing {

static Integer VirtualHost::getCurrent() {
  return CURRENT.get();
}

static std::string VirtualHost::getIpAddress(std::string domain) {
  std::string result = null;

  try {
    result = InetAddress.getByName(domain).getHostAddress();
  } catch (UnknownHostException e) {
  }

  return result;
}

static std::string VirtualHost::getLocalHostAddress() {
  std::string result = null;

  try {
    result = InetAddress.getLocalHost().getHostAddress();
  } catch (UnknownHostException e) {
  }

  return result;
}

static std::string VirtualHost::getLocalHostName() {
  std::string result = null;

  try {
    result = InetAddress.getLocalHost().getHostName();
  } catch (UnknownHostException e) {
  }

  return result;
}

static void VirtualHost::setCurrent(Integer code) {
  CURRENT.set(code);
}

VirtualHost::VirtualHost(echo::Context parentContext, std::string hostDomain,
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

Route VirtualHost::attach(Echo::Echo target) {
  if ((target.getContext() == null) && (parentContext != null)) {
    target.setContext(parentContext.createChildContext());
  }

  return super.attach(target);
}

Route VirtualHost::attach(std::string uriPattern, Echo::Echo target) {
  if ((target.getContext() == null) && (parentContext != null)) {
    target.setContext(parentContext.createChildContext());
  }

  return super.attach(uriPattern, target);
}

Route VirtualHost::attachDefault(Echo::Echo defaultTarget) {
  if ((defaultTarget.getContext() == null)
      && (parentContext != null)) {
    defaultTarget.setContext(parentContext.createChildContext());
  }

  return super.attachDefault(defaultTarget);
}

Finder VirtualHost::createFinder(Class<?> targetClass) {
  Finder result = super.createFinder(targetClass);
  result.setContext(getContext().createChildContext());
  return result;
}

Route VirtualHost::createRoute(std::string uriPattern, Echo::Echo target) {
  return new Route(this, uriPattern, target) {
    //@Override
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

static const ThreadLocal<Integer> VirtualHost::CURRENT = new ThreadLocal<Integer>();

} // namespace routing
} // namespace echo
