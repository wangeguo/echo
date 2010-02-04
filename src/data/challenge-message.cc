#include <echo/data/challenge-message.h>

namespace echo {
namespace data {

ChallengeMessage::ChallengeMessage(ChallengeScheme scheme, std::string realm,
                                   Series<Parameter> parameters) {
  this->scheme = scheme;
  rawValue = null;
  this->realm = realm;
  this->parameters = parameters;
  digestAlgorithm = Digest.ALGORITHM_MD5;
  serverNonce = null;
  opaque = null;
}

Series<Parameter> ChallengeMessage::getParameters() {
  if (parameters == null) {
    parameters = new Form();
  }

  return parameters;
}

int ChallengeMessage::hashCode() {
  return SystemUtils.hashCode(getScheme(), getRealm(), getParameters());
}

static const std::string ChallengeMessage::QUALITY_AUTHENTICATION("auth");
static const std::string ChallengeMessage::QUALITY_AUTHENTICATION_INTEGRITY("auth-int");

} // namespace data
} // namespace echo
