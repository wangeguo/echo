#ifndef _ECHO_DATA_CHALLENGE_REQUEST_H_
#define _ECHO_DATA_CHALLENGE_REQUEST_H_

//import java.util.Collection;
//import java.util.concurrent.CopyOnWriteArrayList;

#include <string>
#include <list>

namespace echo {
namespace data {

/**
 * Authentication challenge sent by an origin server to a client. Upon reception
 * of this request, the client should send a new request with the proper
 * {@link ChallengeResponse} set.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the
 * "WWW-Authenticate" header.
 * 
 * @author Jerome Louvel
 */
//public final class ChallengeRequest extends ChallengeMessage {
class ChallengeRequest : public ChallengeMessage {

 public:
  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   */
  ChallengeRequest(ChallengeScheme scheme) {
    ChallengeRequest(scheme, null);
  }

  /**
   * Constructor.
   * 
   * @param scheme
   *            The challenge scheme.
   * @param realm
   *            The authentication realm.
   */
  ChallengeRequest(ChallengeScheme scheme, std::string realm);

  /** {@inheritDoc} */
  // @Override
  bool equals(const Object obj);

  /**
   * Returns the base URI references that collectively define the protected
   * domains for the digest authentication. By default it return a list with a
   * single "/" URI reference.
   * 
   * @return The base URI references.
   */
  std::list<Reference> getDomainRefs();

  /**
   * Returns the available options for quality of protection. The default
   * value is {@link #QUALITY_AUTHENTICATION}.
   * 
   * @return The available options for quality of protection.
   */
  std::list<std::string> getQualityOptions();

  /**
   * Indicates if the previous request from the client was stale.
   * 
   * @return True if the previous request from the client was stale.
   */
  bool isStale() {
    return stale;
  }

  /**
   * Sets the URI references that define the protection domains for the digest
   * authentication.
   * 
   * @param domainRefs
   *            The base URI references.
   */
  void setDomainRefs(std::list<Reference> domainRefs) {
    domainRefs = domainRefs;
  }

  /**
   * Sets the URI references that define the protection domains for the digest
   * authentication.
   * 
   * @param domainUris
   *            The base URI references.
   * @see #setDomainRefs(std::list)
   */
  void setDomainUris(Collection<std::string> domainUris);

  /**
   * Sets the available options for quality of protection. The default value
   * is {@link #QUALITY_AUTHENTICATION}.
   * 
   * @param qualityOptions
   *            The available options for quality of protection.
   */
  void setQualityOptions(std::list<std::string> qualityOptions) {
    this->qualityOptions = qualityOptions;
  }

  /**
   * Indicates if the previous request from the client was stale.
   * 
   * @param stale
   *            True if the previous request from the client was stale.
   */
  void setStale(bool stale) {
    this->stale = stale;
  }

 private:
  
  /** The available options for quality of protection. */
  volatile std::list<std::string> qualityOptions;

  /** The URI references that define the protection domains. */
  volatile std::list<Reference> domainRefs;

  /** Indicates if the previous request from the client was stale. */
  volatile bool stale;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CHALLENGE_REQUEST_H_

