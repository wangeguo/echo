#ifndef _ECHO_DATA_CHALLENGE_MESSAGE_H_
#define _ECHO_DATA_CHALLENGE_MESSAGE_H_

#include <string>

#include <echo/engine/util/system-utils.h>
#include <echo/util/series.h>

namespace echo {
namespace data {


/**
 * Base authentication challenge message exchanged between an origin server and
 * a client.
 * 
 * @author Jerome Louvel
 */
//public abstract class ChallengeMessage {
class ChallengeMessage {

 public:

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   */
  ChallengeMessage(ChallengeScheme scheme) {
    ChallengeMessage(scheme, null, null);
  }

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param parameters
   *            The additional scheme parameters.
   */
  ChallengeMessage(ChallengeScheme scheme, Series<Parameter> parameters) {
    ChallengeMessage(scheme, null, null);
  }

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param realm
   *            The authentication realm.
   */
  ChallengeMessage(ChallengeScheme scheme, std::string realm) {
    ChallengeMessage(scheme, realm, null);
  }

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param realm
   *            The authentication realm.
   * @param parameters
   *            The additional scheme parameters.
   */
  ChallengeMessage(ChallengeScheme scheme, std::string realm,
                   Series<Parameter> parameters);

  /**
   * Returns the digest algorithm. See {@link Digest} class for DIGEST_*
   * constants. Default value is {@link Digest#ALGORITHM_MD5}.
   * 
   * @return The digest algorithm.
   */
  std::string getDigestAlgorithm() {
    return digestAlgorithm;
  }

  /**
   * Returns an opaque string of data which should be returned by the client
   * unchanged.
   * 
   * @return An opaque string of data.
   */
  std::string getOpaque() {
    return opaque;
  }

  /**
   * Returns the modifiable series of scheme parameters. Creates a new
   * instance if no one has been set.
   * 
   * @return The modifiable series of scheme parameters.
   */
  Series<Parameter> getParameters();

  /**
   * Returns the raw challenge value.
   * 
   * @return The raw challenge value.
   */
  std::string getRawValue() {
    return rawValue;
  }

  /**
   * Returns the realm name.
   * 
   * @return The realm name.
   */
  std::string getRealm() {
    return realm;
  }

  /**
   * Returns the scheme used.
   * 
   * @return The scheme used.
   */
  ChallengeScheme getScheme() {
    return scheme;
  }

  /**
   * Returns the server nonce.
   * 
   * @return The server nonce.
   */
  std::string getServerNonce() {
    return serverNonce;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return SystemUtils.hashCode(getScheme(), getRealm(), getParameters());
  }

  /**
   * Sets the digest algorithm. See {@link Digest} class for ALGORITHM_*
   * constants. Default value is {@link Digest#ALGORITHM_MD5}.
   * 
   * @param digestAlgorithm
   *            The digest algorithm.
   */
  void setDigestAlgorithm(std::string digestAlgorithm) {
    this->digestAlgorithm = digestAlgorithm;
  }

  /**
   * Sets an opaque string of data which should be returned by the client
   * unchanged.
   * 
   * @param opaque
   *            An opaque string of data.
   */
  void setOpaque(std::string opaque) {
    this->opaque = opaque;
  }

  /**
   * Sets the parameters.
   * 
   * @param parameters
   *            The parameters.
   */
  void setParameters(Series<Parameter> parameters) {
    this->parameters = parameters;
  }

  /**
   * Sets the raw value.
   * 
   * @param rawValue
   *            The raw value.
   */
  void setRawValue(std::string rawValue) {
    this->rawValue = rawValue;
  }

  /**
   * Sets the realm name.
   * 
   * @param realm
   *            The realm name.
   */
  void setRealm(std::string realm) {
    this->realm = realm;
  }

  /**
   * Sets the scheme used.
   * 
   * @param scheme
   *            The scheme used.
   */
  void setScheme(ChallengeScheme scheme) {
    this->scheme = scheme;
  }

  /**
   * Sets the server nonce.
   * 
   * @param serverNonce
   *            The server nonce.
   */
  void setServerNonce(std::string serverNonce) {
    this->serverNonce = serverNonce;
  }

 public:

  /** Authentication quality. */
  static const std::string QUALITY_AUTHENTICATION;

  /** Authentication and integrity. */
  static const std::string QUALITY_AUTHENTICATION_INTEGRITY;

 private:
  
  /** The raw value for custom challenge schemes. */
  volatile std::string rawValue;

  /** The additional scheme parameters. */
  volatile Series<Parameter> parameters;

  /** The challenge scheme. */
  volatile ChallengeScheme scheme;

  /** The server nonce. */
  volatile std::string serverNonce;

  /** The authentication realm. */
  volatile std::string realm;

  /**
   * An opaque string of data which should be returned by the client
   * unchanged.
   */
  volatile std::string opaque;

  /** The digest algorithm. */
  volatile std::string digestAlgorithm;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CHALLENGE_MESSAGE_H_
