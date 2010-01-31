#include <echo/routing/template-route.h>

namespace echo {
namespace routing {

TemplateRoute::TemplateRoute(Router router, std::string uriTemplate, Echo::Echo next) {
    TemplateRoute(router, new Template(uriTemplate, Template.MODE_STARTS_WITH,
                              Variable.TYPE_URI_SEGMENT, "", true, false), next);
  }

TemplateRoute::TemplateRoute(Router router, Template template, Echo::Echo next) {
    Filter(router == null ? null : router.getContext(), next);
    matchingQuery = (router == null) ? true : router
                         .getDefaultMatchingQuery();
    this->router = router;
    this->template = template;
  }

int TemplateRoute::getMatchingMode() {
    return getTemplate().getMatchingMode();
  }

float TemplateRoutescore(echo::Request request, echo::Response response) {
    float result = 0F;

    if ((getRouter() != null) && (request.getResourceRef() != null)
        && (getTemplate() != null)) {
      const std::string remainingPart = request.getResourceRef()
                                   .getRemainingPart(false, isMatchingQuery());
      if (remainingPart != null) {
        const int matchedLength = getTemplate().match(remainingPart);

        if (matchedLength != -1) {
          const float totalLength = remainingPart.length();

          if (totalLength > 0.0F) {
            result = getRouter().getRequiredScore()
                     + (1.0F - getRouter().getRequiredScore())
                     * (matchedLength / totalLength);
          } else {
            result = 1.0F;
          }
        }
      }

      if (getLogger().isLoggable(Level.FINER)) {
        getLogger().finer(
            "Call score for the \"" + getTemplate().getPattern()
            + "\" URI pattern: " + result);
      }
    }

    return result;
  }

void TemplateRoute::setMatchingMode(int matchingMode) {
    getTemplate().setMatchingMode(matchingMode);
  }

void TemplateRoute::setMatchingQuery(bool matchingQuery) {
    setMatchQuery(matchingQuery);
  }

std::string TemplateRoute::toString() {
    return (getTemplate() == null) ? super.toString() : getTemplate()
        .getPattern();
  }

int TemplateRoute::beforeHandle(echo::Request request, echo::Response response) {
    // 1 - Parse the template variables and adjust the base reference
    if (getTemplate() != null) {
      const std::string remainingPart = request.getResourceRef()
                                   .getRemainingPart(false, isMatchingQuery());
      const int matchedLength = getTemplate().parse(remainingPart,
                                                    request);

      if (getLogger().isLoggable(Level.FINER)) {
        getLogger().finer(
            "Attempting to match this pattern: "
            + getTemplate().getPattern() + " >> "
            + matchedLength);
      }

      if (matchedLength != -1) {
        // Updates the context
        const std::string matchedPart = remainingPart.substring(0,
                                                           matchedLength);
        Reference baseRef = request.getResourceRef().getBaseRef();

        if (baseRef == null) {
          baseRef = new Reference(matchedPart);
        } else {
          baseRef = new Reference(baseRef.toString(false, false)
                                  + matchedPart);
        }

        request.getResourceRef().setBaseRef(baseRef);

        if (getLogger().isLoggable(Level.FINE)) {
          getLogger().fine(
              "New base URI: "
              + request.getResourceRef().getBaseRef());
          getLogger().fine(
              "New remaining part: "
              + request.getResourceRef()
              .getRemainingPart(false,
                                isMatchingQuery()));
        }

        if (getLogger().isLoggable(Level.FINE)) {
          getLogger().fine(
              "Delegating the call to the target Echo");
        }
      } else {
        response.setStatus(Status.CLIENT_ERROR_NOT_FOUND);
      }
    }

    return CONTINUE;
  }

} // namespace routing
} // namespace echo

