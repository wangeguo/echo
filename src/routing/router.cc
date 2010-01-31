#include <echo/routing/router.h>

namespace echo {
namespace routing {

Router::Router(echo::Context context) {
  Echo(context);
  routes = new RouteList();
  defaultMatchingMode = Template.MODE_EQUALS;
  defaultMatchingQuery = false;
  defaultRoute = null;
  finderClass = Finder.class;
  routingMode = MODE_FIRST_MATCH;
  requiredScore = 0.5F;
  maxAttempts = 1;
  retryDelay = 500L;
}

Route Router::attach(std::string pathTemplate, Class<?> targetClass) {
  return attach(pathTemplate, createFinder(targetClass));
}

Route Router::attach(std::string pathTemplate, echo::Echo target) {
  const Route result = createRoute(pathTemplate, target);
  getRoutes().add(result);
  return result;
}

Route Router::attachDefault(Class<?> defaultTargetClass) {
  return attachDefault(createFinder(defaultTargetClass));
}

Route Router::attachDefault(echo::Echo defaultTarget) {
  Route result = createRoute("", defaultTarget);
  result.setMatchingMode(Template.MODE_STARTS_WITH);
  setDefaultRoute(result);
  return result;
}

echo::resource::Finder
Router::createFinder(Class<?> targetClass) {
  return Finder.createFinder(targetClass, getFinderClass(), getContext(),
                             getLogger());
}


void Router::detach(echo::Echo target) {
  getRoutes().removeAll(target);
  if ((getDefaultRoute() != null)
      && (getDefaultRoute().getNext() == target)) {
    setDefaultRoute(null);
  }
}



echo::Echo Router::getNext(echo::Request request, echo::Response response) {
  Route result = null;

  for (int i = 0; (result == null) && (i < getMaxAttempts()); i++) {
    if (i > 0) {
      // Before attempting another time, let's
      // sleep during the "retryDelay" set.
      try {
        Thread.sleep(getRetryDelay());
      } catch (InterruptedException e) {
      }
    }

    if (routes != null) {
      // Select the routing mode
      switch (getRoutingMode()) {
        case MODE_BEST_MATCH:
          result = getRoutes().getBest(request, response,
                                       getRequiredScore());
          break;

        case MODE_FIRST_MATCH:
          result = getRoutes().getFirst(request, response,
                                        getRequiredScore());
          break;

        case MODE_LAST_MATCH:
          result = getRoutes().getLast(request, response,
                                       getRequiredScore());
          break;

        case MODE_NEXT_MATCH:
          result = getRoutes().getNext(request, response,
                                       getRequiredScore());
          break;

        case MODE_RANDOM_MATCH:
          result = getRoutes().getRandom(request, response,
                                         getRequiredScore());
          break;

        case MODE_CUSTOM:
          result = getCustom(request, response);
          break;
      }
    }
  }

  if (result == null) {
    // If nothing matched in the routes list, check the default
    // route
    if ((getDefaultRoute() != null)
        && (getDefaultRoute().score(request, response) >= getRequiredScore())) {
      result = getDefaultRoute();
    } else {
      // No route could be found
      response.setStatus(Status.CLIENT_ERROR_NOT_FOUND);
    }
  }

  logRoute(result);
  return result;
}

void Router::handle(echo::Request request, echo::Response response) {
  super.handle(request, response);

  echo::Echo next = getNext(request, response);
  if (next != null) {
    doHandle(next, request, response);
  } else {
    response.setStatus(Status.CLIENT_ERROR_NOT_FOUND);
  }
}


void Router::setDefaultMatchingQuery(bool defaultMatchingQuery) {
  setDefaultMatchQuery(defaultMatchingQuery);
}

void Router::start() throw (std::runtime_error) {
  if (isStopped()) {
    super.start();

    for (Route route : getRoutes()) {
      route.start();
    }

    if (getDefaultRoute() != null) {
      getDefaultRoute().start();
    }
  }
}

void Router::stop() throw (std::runtime_error) {
  if (isStarted()) {
    if (getDefaultRoute() != null) {
      getDefaultRoute().stop();
    }

    for (Route route : getRoutes()) {
      route.stop();
    }

    super.stop();
  }
}

  
Route Router::createRoute(std::string uriPattern, echo::Echo target) {
  Route result = new Route(this, uriPattern, target);

  if (target instanceof Directory) {
    result.getTemplate().setMatchingMode(Template.MODE_STARTS_WITH);
  } else {
    result.getTemplate().setMatchingMode(getDefaultMatchingMode());
  }

  result.setMatchingQuery(getDefaultMatchingQuery());

  return result;
}

void Router::doHandle(echo::Echo next, echo::Request request, echo::Response response) {
  next.handle(request, response);
}

void Router::logRoute(Route route) {
  if (getLogger().isLoggable(Level.FINE)) {
    if (getDefaultRoute() == route) {
      getLogger().fine("The default route was selected.");
    } else {
      getLogger().fine("This route was selected: \"" + route + "\"");
    }
  }
}

static const int Router::BEST(1);
static const int Router::CUSTOM(6);
static const int Router::FIRST(2);
static const int Router::LAST(3);
static const int Router::MODE_BEST_MATCH(1);
static const int Router::MODE_CUSTOM(6);
static const int Router::MODE_FIRST_MATCH(2);
static const int Router::MODE_LAST_MATCH(3);
static const int Router::MODE_NEXT_MATCH(4);
static const int Router::MODE_RANDOM_MATCH(5);
static const int Router::NEXT(4);
static const int Router::RANDOM(5);

} // namespace routing
} // namespace echo
