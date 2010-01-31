#include <echo/routing/redirector.h>

namespace echo {
namespace routing {

Redirector::Redirector(echo::Context context, std::string targetPattern, int mode) {
  echo::Echo(context);
  this.targetTemplate = targetPattern;
  this.mode = mode;
}

void Redirector::handle(echo::Request request, echo::Response response) {
  // Generate the target reference
  const Reference targetRef = getTargetRef(request, response);

  switch (this.mode) {
    case MODE_CLIENT_PERMANENT:
      getLogger().log(Level.INFO,
                      "Permanently redirecting client to: " + targetRef);
      response.redirectPermanent(targetRef);
      break;

    case MODE_CLIENT_FOUND:
      getLogger().log(Level.INFO,
                      "Redirecting client to found location: " + targetRef);
      response.setLocationRef(targetRef);
      response.setStatus(Status.REDIRECTION_FOUND);
      break;

    case MODE_CLIENT_SEE_OTHER:
      getLogger().log(Level.INFO,
                      "Redirecting client to another location: " + targetRef);
      response.setLocationRef(targetRef);
      response.setStatus(Status.REDIRECTION_SEE_OTHER);
      break;

    case MODE_CLIENT_TEMPORARY:
      getLogger().log(Level.INFO,
                      "Temporarily redirecting client to: " + targetRef);
      response.redirectTemporary(targetRef);
      break;

    case MODE_DISPATCHER:
      getLogger().log(Level.INFO,
                      "Redirecting via client connector to: " + targetRef);
      redirectDispatcher(targetRef, request, response);
      break;

    case MODE_CLIENT_DISPATCHER:
      getLogger().log(Level.INFO,
                      "Redirecting via client dispatcher to: " + targetRef);
      redirectClientDispatcher(targetRef, request, response);
      break;

    case MODE_SERVER_DISPATCHER:
      getLogger().log(Level.INFO,
                      "Redirecting via server dispatcher to: " + targetRef);
      redirectServerDispatcher(targetRef, request, response);
      break;
  }
}

void Redirector::redirectClientDispatcher(Reference targetRef,
                                          echo::Request request, echo::Response response) {
  redirectDispatcher(getContext().getClientDispatcher(), targetRef,
                     request, response);
}

void Redirector::redirectDispatcher(Reference targetRef, echo::Request request,
                                    echo::Response response) {
  redirectClientDispatcher(targetRef, request, response);
}

void Redirector::redirectServerDispatcher(Reference targetRef,
                                          echo::Request request, echo::Response response) {
  redirectDispatcher(getContext().getServerDispatcher(), targetRef,
                     request, response);
}
Reference Redirector::getTargetRef(echo::Request request, echo::Response response) {
  // Create the template
  const Template rt = new Template(this.targetTemplate);
  rt.setLogger(getLogger());

  // Return the formatted target URI
  return new Reference(rt.format(request, response));
}

void Redirector::redirectDispatcher(Client dispatcher, Reference targetRef,
                                    echo::Request request, echo::Response response) {
  // Save the base URI if it exists as we might need it for redirections
  const Reference baseRef = request.getResourceRef().getBaseRef();

  // Update the request to cleanly go to the target URI
  request.setResourceRef(targetRef);
  request.getAttributes().remove("org.restlet.http.headers");
  dispatcher.handle(request, response);

  // Allow for response rewriting and clean the headers
  response.setEntity(rewrite(response.getEntity()));
  response.getAttributes().remove("org.restlet.http.headers");

  // In case of redirection, we may have to rewrite the redirect URI
  if (response.getLocationRef() != null) {
    const Template rt = new Template(this.targetTemplate);
    rt.setLogger(getLogger());
    const int matched = rt.parse(response.getLocationRef().toString(),
                                 request);

    if (matched > 0) {
      const std::string remainingPart = (std::string) request.getAttributes()
                                        .get("rr");

      if (remainingPart != null) {
        response.setLocationRef(baseRef.toString() + remainingPart);
      }
    }
  }
}


static const int Redirector::MODE_CLIENT_PERMANENT(1);
static const int Redirector::MODE_CLIENT_FOUND(2);
static const int Redirector::MODE_CLIENT_SEE_OTHER(3);
static const int Redirector::MODE_CLIENT_TEMPORARY(4);
static const int Redirector::MODE_DISPATCHER(5);
static const int Redirector::MODE_CLIENT_DISPATCHER(6);
static const int Redirector::MODE_SERVER_DISPATCHER(7);

} // namespace routing
} // namespace echo
