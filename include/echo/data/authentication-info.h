#ifndef _ECHO_DATA_AUTHENTICATION_INFO_H_
#define _ECHO_DATA_AUTHENTICATION_INFO_H_

#include <string>
#include <echo/engine/util/system-utils.h>

namespace echo {
namespace data {

/**
 * Preemptive authentication information. Sent by an origin server to a client
 * after a successful digest authentication attempt.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the
 * "Authentication-Info" header.
 * 
 * @see <a href="http://tools.ietf.org/html/rfc2617#section-3.2.3">HTTP
 *      Authentication - The Authentication-Info Header</a>
 * 
 * @author Kelly McLaughlin
 * @author Jerome Louvel
 */
class AuthenticationInfo {

 public:
  /**
   * Default constructor.
   * 
   * @param nextNonce
   *            The next nonce value.
   */
  // public AuthenticationInfo(std::string nextNonce) {
  // this(nextNonce, 0, );
  // }

  /**
   * Constructor.
   * 
   * @param nextNonce
   *            The next nonce value.
   * @param nonceCount
   *            The nonce-count value.
   * @param cnonce
   *            The cnonce value.
   * @param quality
   *            The quality of protection.
   * @param responseDigest
   *            The optional response digest for mutual authentication.
   */
  AuthenticationInfo(std::string nextNonce, int nonceCount, std::string cnonce,
                     std::string quality, std::string responseDigest);

  /** {@inheritDoc} */
  //@Override
  const bool equals(const Object obj);

  /**
   * Returns the client nonce.
   * 
   * @return The client nonce.
   */
  std::string getClientNonce() {
    return clientNonce;
  }

  /**
   * Returns the next server nonce. This is the nonce the server wishes the
   * client to use for a future authentication response
   * 
   * @return The next nonce value.
   */
  std::string getNextServerNonce() {
    return nextServerNonce;
  }

  /**
   * Returns the nonce-count value.
   * 
   * @return The nonce-count value.
   */
  int getNonceCount() {
    return nonceCount;
  }

  /**
   * Returns the quality of protection. The value can be
   * {@link ChallengeMessage#QUALITY_AUTHENTICATION} for authentication or
   * {@link ChallengeMessage#QUALITY_AUTHENTICATION_INTEGRITY} for
   * authentication with integrity protection.
   * 
   * @return The quality of protection.
   */
  std::string getQuality() {
    return quality;
  }

  /**
   * Returns the optional response digest for mutual authentication.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "response-digest" value in the "response-auth" directive of the
   * "Authentication-Info" header.
   * 
   * @return The optional response digest for mutual authentication.
   */
  std::string getResponseDigest() {
    return responseDigest;
  }

  /** {@inheritDoc} */
  // @Override
  int hashCode();

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
   * Sets the next server nonce. This is the nonce the server wishes the
   * client to use for a future authentication response
   * 
   * @param nextNonce
   *            The next nonce.
   */
  void setNextServerNonce(std::string nextNonce) {
    nextServerNonce = nextNonce;
  }

  /**
   * Sets the nonce-count value.
   * 
   * @param nonceCount
   *            The nonceCount value.
   */
  void setNonceCount(int nonceCount) {
    this->nonceCount = nonceCount;
  }

  /**
   * Sets the quality of protection. The value can be
   * {@link ChallengeMessage#QUALITY_AUTHENTICATION} for authentication or
   * {@link ChallengeMessage#QUALITY_AUTHENTICATION_INTEGRITY} for authentication with
   * integrity protection.
   * 
   * @param qop
   *            The quality of protection.
   */
  void setQuality(std::string qop) {
    quality = qop;
  }

  /**
   * Sets the optional response digest for mutual authentication.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "response-digest" value in the "response-auth" directive of the
   * "Authentication-Info" header.
   * 
   * @param responseDigest
   *            The response digest.
   */
  void setResponseDigest(std::string responseDigest) {
    this->responseDigest = responseDigest;
  }

 private:

  /** The next nonce value. */
  volatile std::string nextServerNonce;

  /** The nonce-count value. */
  volatile int nonceCount;

  /** The client nonce. */
  volatile std::string clientNonce;

  /** The quality of protection. */
  volatile std::string quality;

  /** The optional response digest for mutual authentication. */
  volatile std::string responseDigest;

};

} // namespace data
} // echo

#endif // _ECHO_DATA_AUTHENTICATION_INFO_H_
