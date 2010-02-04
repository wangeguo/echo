#ifndef _ECHO_DATA_CHALLENGE_SCHEME_H_
#define _ECHO_DATA_CHALLENGE_SCHEME_H_

#include <string>

namespace echo {
namespace data {

/**
 * Challenge scheme used to authenticate remote clients.
 * 
 * @author Jerome Louvel
 */
//public final class ChallengeScheme {
class ChallengeScheme {

 public:

  /**
   * Returns the challenge scheme associated to a scheme name. If an existing
   * constant exists then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The scheme name.
   * @return The associated challenge scheme.
   */
  static ChallengeScheme valueOf(const std::string name);

  /**
   * Constructor.
   * 
   * @param name
   *            The unique name.
   * @param technicalName
   *            The technical name.
   */
  ChallengeScheme(const std::string name, const std::string technicalName) {
    ChallengeScheme(name, technicalName, null);
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The unique name.
   * @param technicalName
   *            The technical name.
   * @param description
   *            The description.
   */
  ChallengeScheme(const std::string name, const std::string technicalName,
                  const std::string description);

  /** {@inheritDoc} */
  //@Override
  boolean equals(const Object object);

  /**
   * Returns the description.
   * 
   * @return The description.
   */
  std::string getDescription() {
    return description;
  }

  /**
   * Returns the name.
   * 
   * @return The name.
   */
  std::string getName() {
    return name;
  }

  /**
   * Returns the technical name (ex: BASIC).
   * 
   * @return The technical name (ex: BASIC).
   */
  std::string getTechnicalName() {
    return technicalName;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode();

  /**
   * Returns the name.
   * 
   * @return The name.
   */
  //@Override
  std::string toString() {
    return getName();
  }

 private:

  /**
   * Sets the technical name (ex: BASIC).
   * 
   * @param technicalName
   *            The technical name (ex: BASIC).
   */
  //@SuppressWarnings("unused")
  void setTechnicalName(std::string technicalName) {
    this->technicalName = technicalName;
  }

 public:

  /** Custom scheme based on IP address or cookies or query parameters, etc. */
  static const ChallengeScheme CUSTOM;

  /** Amazon S3 HTTP scheme. */
  static const ChallengeScheme HTTP_AWS_S3;

  /** Basic HTTP scheme. */
  static const ChallengeScheme HTTP_BASIC;

  /** Cookie HTTP scheme. */
  static const ChallengeScheme HTTP_COOKIE;

  /** Digest HTTP scheme. */
  static const ChallengeScheme HTTP_DIGEST;

  /**
   * Microsoft Azure Shared Key scheme.
   * 
   * @see <a
   *      href="http://msdn.microsoft.com/en-us/library/dd179428.aspx#Subheading2">MSDN
   *      page</a>
   */
  static const ChallengeScheme HTTP_AZURE_SHAREDKEY;

  /**
   * Microsoft Azure Shared Key lite scheme.
   * 
   * @see <a
   *      href="http://msdn.microsoft.com/en-us/library/dd179428.aspx#Subheading2">MSDN
   *      page</a>
   */
  static const ChallengeScheme HTTP_AZURE_SHAREDKEY_LITE;

  /** Microsoft NTML HTTP scheme. */
  static const ChallengeScheme HTTP_NTLM;

  /** OAuth HTTP scheme. */
  static const ChallengeScheme HTTP_OAUTH;

  /** Basic POP scheme. Based on the USER/PASS commands. */
  static const ChallengeScheme POP_BASIC;

  /** Digest POP scheme. Based on the APOP command. */
  static const ChallengeScheme POP_DIGEST;

  /** Plain SMTP scheme. */
  static const ChallengeScheme SMTP_PLAIN;

  /** Plain FTP scheme. */
  static const ChallengeScheme FTP_PLAIN;
  
 private:
  /** The description. */
  const std::string description;

  /** The name. */
  volatile std::string name;

  /** The technical name. */
  volatile std::string technicalName;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CHALLENGE_SCHEME_H_
