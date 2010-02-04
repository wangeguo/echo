#include <echo/data/challenge-response.h>

namespace echo {
namespace data {

ChallengeResponse::ChallengeResponse(const ChallengeRequest challengeRequest,
                                     const echo::Request request, const echo::Response response,
                                     const std::string identifier, char[] baseSecret,
                                     std::string baseSecretAlgorithm) {
  ChallengeMessage(challengeRequest.getScheme());
  this->identifier = identifier;
  /*org.restlet.engine.security.AuthenticatorUtils.update(this, request,
    response, identifier, baseSecret, baseSecretAlgorithm);*/
  echo::engine::security::AuthenticatorUtils::update(this, request,
                                                     response, identifier, baseSecret, baseSecretAlgorithm);
}

ChallengeResponse::ChallengeResponse(ChallengeScheme scheme) {
  super(scheme);
  identifier = null;
  secret = null;
  authenticated = false;
  clientNonce = null;
  digestRef = null;
  quality = null;
  serverNounceCount = 1;
}

ChallengeResponse::ChallengeResponse(ChallengeScheme scheme, std::string credentials) {
  ChallengeResponse(scheme);
  setRawValue(credentials);
}

ChallengeResponse::ChallengeResponse(const ChallengeScheme scheme,
                                     const std::string identifier, char[] secret) {
  ChallengeMessage(scheme);
  this->identifier = identifier;
  this->secret = secret;
}

ChallengeResponse::ChallengeResponse(const ChallengeScheme scheme,
                                     const std::string identifier, Series<Parameter> parameters) {
  ChallengeMessage(scheme, parameters);
  this->identifier = identifier;
  this->secret = null;
}

ChallengeResponse::ChallengeResponse(const ChallengeScheme scheme,
                                     const std::string identifier, std::string secret) {
  ChallengeMessage(scheme);
  this->identifier = identifier;
  this->secret = (secret != null) ? secret.toCharArray() : null;
}

bool ChallengeResponse::equals(Object obj) {
  bool result = (obj == this);

  // if obj == this no need to go further
  if (!result) {
    // if obj isn't a challenge request or is null don't evaluate
    // further
    if (obj instanceof ChallengeResponse) {
      const ChallengeResponse that = (ChallengeResponse) obj;

      if (getCredentials() != null) {
        result = getCredentials().equals(that.getCredentials());
      } else {
        result = (that.getCredentials() == null);
      }

      if (result) {
        if (getIdentifier() != null) {
          result = getIdentifier().equals(that.getIdentifier());
        } else {
          result = (that.getIdentifier() == null);
        }

        if (result) {
          if (getScheme() != null) {
            result = getScheme().equals(that.getScheme());
          } else {
            result = (that.getScheme() == null);
          }

          if (result) {
            if ((getSecret() == null)
                || (that.getSecret() == null)) {
              // check if both are null
              result = (getSecret() == that.getSecret());
            } else {
              if (getSecret().length == that.getSecret().length) {
                bool equals = true;
                for (int i = 0; (i < getSecret().length)
                             && equals; i++) {
                  equals = (getSecret()[i] == that
                            .getSecret()[i]);
                }
                result = equals;
              }
            }
          }
        }
      }
    }
  }

  return result;
}

std::string ChallengeResponse::getServerNounceCountAsHex() {
  /*return org.restlet.engine.security.AuthenticatorUtils
    .formatNonceCount(getServerNounceCount());*/
    
  return echo::engine::security::AuthenticatorUtils::formatNonceCount(getServerNounceCount());
}

int ChallengeResponse::hashCode() {
  return SystemUtils.hashCode(getScheme(), getIdentifier(),
                              // Secret is simply discarded from hash code calculation because we
                              // don't want it to be materialized as a string
                              // (getSecret() == null) ? null : new std::string(getSecret()),
                              getCredentials());
}

void ChallengeResponse::setSecret(std::string secret) {
  this->secret = (secret == null) ? null : secret.toCharArray();
}

} // namespace data
} // namespace echo
