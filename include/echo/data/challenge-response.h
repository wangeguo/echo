#ifndef _ECHO_DATA_CHALLENGE_RESPONSE_H_
#define _ECHO_DATA_CHALLENGE_RESPONSE_H_

#include <string>

#include <echo/request.h>
#include <echo/response.h>
#include <echo/engine/util/system-utils.h>
#include <echo/util/series.h>

namespace echo {
namespace data {

/**
 * Authentication response sent by client to an origin server. This is typically
 * following a {@link ChallengeRequest} sent by the origin server to the client.<br>
 * <br>
 * Sometimes, it might be faster to preemptively issue a challenge response if
 * the client knows for sure that the target resource will require
 * authentication.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the
 * "Authorization" header.
 * 
 * @author Jerome Louvel
 */
//public final class ChallengeResponse extends ChallengeMessage {
class ChallengeResponse : public ChallengeMessage {

 public:

  /**
   * Constructor.
   * 
   * @param challengeRequest
   *            The challenge request.
   * @param request
   *            The request.
   * @param response
   *            The response.
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   * @param baseSecret
   *            The user secret, such as a password or a secret key.
   */
  ChallengeResponse(const ChallengeRequest challengeRequest,
                    const echo::Request request, const echo::Response response,
                    const std::string identifier, char[] baseSecret) {
    ChallengeResponse(challengeRequest, request, response, identifier, baseSecret,
                      Digest.ALGORITHM_NONE);
  }

  /**
   * Constructor.
   * 
   * @param challengeRequest
   *            The challenge request.
   * @param request
   *            The request.
   * @param response
   *            The response.
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   * @param baseSecret
   *            The user secret, such as a password or a secret key.
   */
  ChallengeResponse(const ChallengeRequest challengeRequest,
                    const echo::Request request, const echo::Response response,
                    const std::string identifier, std::string baseSecret) {
    ChallengeResponse(challengeRequest, request, response, identifier, baseSecret
                      .toCharArray(), Digest.ALGORITHM_NONE);
  }

  /**
   * Constructor.
   * 
   * @param challengeRequest
   *            The challenge request.
   * @param request
   *            The request.
   * @param response
   *            The response.
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   * @param baseSecret
   *            The base secret used to compute the secret.
   * @param baseSecretAlgorithm
   *            The digest algorithm of the base secret (@see {@link Digest}
   *            class).
   */
  ChallengeResponse(const ChallengeRequest challengeRequest,
                    const echo::Request request, const echo::Response response,
                    const std::string identifier, char[] baseSecret,
                    std::string baseSecretAlgorithm);

  /**
   * Constructor with no credentials.
   * 
   * @param scheme
   *            The challenge scheme.
   */
  ChallengeResponse(ChallengeScheme scheme);

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param credentials
   *            The raw credentials for custom challenge schemes.
   * @deprecated Use {@link #setRawValue(std::string)} instead.
   */
  //@Deprecated
  ChallengeResponse(ChallengeScheme scheme, std::string credentials);

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   * @param secret
   *            The user secret, such as a password or a secret key.
   */
  ChallengeResponse(const ChallengeScheme scheme,
                    const std::string identifier, char[] secret);

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   * @param parameters
   *            The additional scheme parameters.
   */
  ChallengeResponse(const ChallengeScheme scheme,
                    const std::string identifier, Series<Parameter> parameters);

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   * @param secret
   *            The user secret, such as a password or a secret key.
   */
  ChallengeResponse(const ChallengeScheme scheme,
                    const std::string identifier, std::string secret);

  /** {@inheritDoc} */
  //@Override
  bool equals(Object obj);

  /**
   * Returns the client nonce.
   * 
   * @return The client nonce.
   */
  std::string getClientNonce() {
    return clientNonce;
  }

  /**
   * Returns the raw credentials.
   * 
   * @return The raw credentials.
   * @deprecated Use {@link #getRawValue()} instead.
   */
  //@Deprecated
  std::string getCredentials() {
    return getRawValue();
  }

  /**
   * Returns the {@link echo::Request#getResourceRef()} value duplicated here in
   * case a proxy changed it.
   * 
   * @return The digest URI reference.
   */
  Reference getDigestRef() {
    return digestRef;
  }

  /**
   * Returns the user identifier, such as a login name or an access key.
   * 
   * @return The user identifier, such as a login name or an access key.
   */
  std::string getIdentifier() {
    return identifier;
  }

  /**
   * Gets the principal associated to the identifier property.
   * 
   * @return The principal associated to the identifier property.
   */
  // @FIXME
  /*  java.security.Principal getPrincipal() {
      return new java.security.Principal() {
      public std::string getName() {
      return getIdentifier();
      };
      };
      }*/

  /**
   * Returns the chosen quality of protection.
   * 
   * @return The chosen quality of protection.
   */
  std::string getQuality() {
    return quality;
  }

  /**
   * Returns the user secret, such as a password or a secret key.
   * 
   * It is not recommended to use {@link std::string#std::string(char[])} for security
   * reasons.
   * 
   * @return The user secret, such as a password or a secret key.
   */
  char[] getSecret() {
    return secret;
  }

  /**
   * Returns the server nonce count.
   * 
   * @return The server nonce count.
   */
  int getServerNounceCount() {
    return serverNounceCount;
  }

  /**
   * Returns the server nonce count as an hexadecimal string of eight
   * characters.
   * 
   * @return The server nonce count as an hexadecimal string.
   */
  std::string getServerNounceCountAsHex();

  /** {@inheritDoc} */
  //@Override
  int hashCode();

  /**
   * Indicates if the identifier or principal has been authenticated. The
   * application is responsible for updating this property, relying on a
   * {@link org.restlet.security.Guard} or manually.
   * 
   * @return True if the identifier or principal has been authenticated.
   * @deprecated Use {@link ClientInfo#isAuthenticated()} instead.
   */
  //@Deprecated
  bool isAuthenticated() {
    return authenticated;
  }

  /**
   * Indicates if the identifier or principal has been authenticated. The
   * application is responsible for updating this property, relying on a
   * {@link org.restlet.security.Guard} or manually.
   * 
   * @param authenticated
   *            True if the identifier or principal has been authenticated.
   * @deprecated Use {@link ClientInfo#setAuthenticated(bool)} instead.
   */
  //@Deprecated
  void setAuthenticated(bool authenticated) {
    this->authenticated = authenticated;
  }

  /**
   * Sets the client nonce.
   * 
   * @param clientNonce
   *            The client nonce.
   */
  void setClientNonce(std::string clientNonce) {
    this->clientNonce = clientNonce;
  }

  /**
   * Sets the raw credentials.
   * 
   * @param credentials
   *            The credentials.
   * @deprecated Use {@link #getRawValue()} instead.
   */
  //@Deprecated
  void setCredentials(std::string credentials) {
    setRawValue(credentials);
  }

  /**
   * Sets the digest URI reference.
   * 
   * @param digestRef
   *            The digest URI reference.
   */
  void setDigestRef(Reference digestRef) {
    this->digestRef = digestRef;
  }

  /**
   * Sets the user identifier, such as a login name or an access key.
   * 
   * @param identifier
   *            The user identifier, such as a login name or an access key.
   */
  void setIdentifier(std::string identifier) {
    this->identifier = identifier;
  }

  /**
   * Sets the chosen quality of protection.
   * 
   * @param quality
   *            The chosen quality of protection.
   */
  void setQuality(std::string quality) {
    this->quality = quality;
  }

  /**
   * Sets the user secret, such as a password or a secret key.
   * 
   * @param secret
   *            The user secret, such as a password or a secret key.
   */
  void setSecret(char[] secret) {
    this->secret = secret;
  }

  /**
   * Sets the user secret, such as a password or a secret key.
   * 
   * @param secret
   *            The user secret, such as a password or a secret key.
   */
  void setSecret(std::string secret);

  /**
   * Sets the server nonce count.
   * 
   * @param serverNounceCount
   *            The server nonce count.
   */
  void setServerNounceCount(int serverNounceCount) {
    this->serverNounceCount = serverNounceCount;
  }

 private:
  /**
   * Indicates if the identifier or principal has been authenticated. The
   * application is responsible for updating this property, relying on a
   * {@link org.restlet.security.Guard} or manually.
   */
  volatile bool authenticated;

  /** The client nonce value. */
  volatile std::string clientNonce;

  /**
   * The {@link echo::Request#getResourceRef()} value duplicated here in case a
   * proxy changed it.
   */
  volatile Reference digestRef;

  /** The user identifier, such as a login name or an access key. */
  volatile std::string identifier;

  /** The chosen quality of protection. */
  volatile std::string quality;

  /** The user secret, such as a password or a secret key. */
  volatile char[] secret;

  /** The server nonce count. */
  volatile int serverNounceCount;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CHALLENGE_RESPONSE_H_
