#ifndef _ECHO_DATA_COOKIE_SETTING_H_
#define _ECHO_DATA_COOKIE_SETTING_H_

#include <echo/response.h>
#include <echo/engine/util/system-utils.h>

namespace echo {
namespace data {

/**
 * Cookie setting provided by a server. This allows a server side application to
 * add, modify or remove a cookie on the client.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the "Set-Cookie"
 * and "Set-Cookie2" headers.
 * 
 * @see Response#getCookieSettings()
 * @author Jerome Louvel
 */
//public final class CookieSetting extends Cookie {
class CookieSetting : public Cookie {

 public:

  /**
   * Default constructor.
   */
  CookieSetting() {
    CookieSetting(0, NULL, NULL);
  }

  /**
   * Constructor.
   * 
   * @param version
   *            The cookie's version.
   * @param name
   *            The cookie's name.
   * @param value
   *            The cookie's value.
   */
  CookieSetting(int version, std::string name, std::string value) {
    CookieSetting(version, name, value, NULL, NULL);
  }

  /**
   * Constructor.
   * 
   * @param version
   *            The cookie's version.
   * @param name
   *            The cookie's name.
   * @param value
   *            The cookie's value.
   * @param path
   *            The cookie's path.
   * @param domain
   *            The cookie's domain name.
   */
  CookieSetting(int version, std::string name, std::string value, std::string path,
                std::string domain) {
    CookieSetting(version, name, value, path, domain, NULL, -1, false, false);
  }

  /**
   * Constructor.
   * 
   * @param version
   *            The cookie's version.
   * @param name
   *            The cookie's name.
   * @param value
   *            The cookie's value.
   * @param path
   *            The cookie's path.
   * @param domain
   *            The cookie's domain name.
   * @param comment
   *            The cookie's comment.
   * @param maxAge
   *            Sets the maximum age in seconds.<br>
   *            Use 0 to immediately discard an existing cookie.<br>
   *            Use -1 to discard the cookie at the end of the session
   *            (default).
   * @param secure
   *            Indicates if cookie should only be transmitted by secure
   *            means.
   */
  CookieSetting(int version, std::string name, std::string value, std::string path,
                std::string domain, std::string comment, int maxAge, bool secure) {
    CookieSetting(version, name, value, path, domain, comment, maxAge, secure, false);
  }

  /**
   * Constructor.
   * 
   * @param version
   *            The cookie's version.
   * @param name
   *            The cookie's name.
   * @param value
   *            The cookie's value.
   * @param path
   *            The cookie's path.
   * @param domain
   *            The cookie's domain name.
   * @param comment
   *            The cookie's comment.
   * @param maxAge
   *            Sets the maximum age in seconds.<br>
   *            Use 0 to immediately discard an existing cookie.<br>
   *            Use -1 to discard the cookie at the end of the session
   *            (default).
   * @param secure
   *            Indicates if cookie should only be transmitted by secure
   *            means.
   * @param accessRestricted
   *            Indicates whether to restrict cookie access to untrusted
   *            parties. Currently this toggles the non-standard but widely
   *            supported HttpOnly cookie parameter.
   */
  CookieSetting(int version, std::string name, std::string value, std::string path,
                std::string domain, std::string comment, int maxAge, bool secure,
                bool accessRestricted);

  /**
   * Preferred constructor.
   * 
   * @param name
   *            The cookie's name.
   * @param value
   *            The cookie's value.
   */
  CookieSetting(std::string name, std::string value) {
    CookieSetting(0, name, value, NULL, NULL);
  }

  /** {@inheritDoc} */
  //@Override
  bool equals(Object obj);

  /**
   * Returns the comment for the user.
   * 
   * @return The comment for the user.
   */
  std::string getComment() {
    return this->comment;
  }

  /**
   * Returns the description of this REST element.
   * 
   * @return The description of this REST element.
   */
  std::string getDescription() {
    return "Cookie setting";
  }

  /**
   * Returns the maximum age in seconds.<br>
   * Use 0 to immediately discard an existing cookie.<br>
   * Use -1 to discard the cookie at the end of the session (default).
   * 
   * @return The maximum age in seconds.
   */
  int getMaxAge() {
    return this->maxAge;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode();

  /**
   * Indicates if cookie access is restricted for untrusted parties. Currently
   * this toggles the non-standard but widely supported HttpOnly cookie
   * parameter.
   * 
   * @return accessRestricted True if cookie access should be restricted
   */
  bool isAccessRestricted() {
    return this->accessRestricted;
  }

  /**
   * Indicates if cookie should only be transmitted by secure means.
   * 
   * @return True if cookie should only be transmitted by secure means.
   */
  bool isSecure() {
    return this->secure;
  }

  /**
   * Indicates whether to restrict cookie access to untrusted parties.
   * Currently this toggles the non-standard but widely supported HttpOnly
   * cookie parameter.
   * 
   * @param accessRestricted
   *            True if cookie access should be restricted
   */
  void setAccessRestricted(bool accessRestricted) {
    this->accessRestricted = accessRestricted;
  }

  /**
   * Sets the comment for the user.
   * 
   * @param comment
   *            The comment for the user.
   */
  void setComment(std::string comment) {
    this->comment = comment;
  }

  /**
   * Sets the maximum age in seconds.<br>
   * Use 0 to immediately discard an existing cookie.<br>
   * Use -1 to discard the cookie at the end of the session (default).
   * 
   * @param maxAge
   *            The maximum age in seconds.
   */
  void setMaxAge(int maxAge) {
    this->maxAge = maxAge;
  }

  /**
   * Indicates if cookie should only be transmitted by secure means.
   * 
   * @param secure
   *            True if cookie should only be transmitted by secure means.
   */
  void setSecure(bool secure) {
    this->secure = secure;
  }


 private:
  /**
   * Indicates whether to restrict cookie access to untrusted parties.
   * Currently this toggles the non-standard but widely supported HttpOnly
   * cookie parameter.
   */
  volatile bool accessRestricted;

  /** The user's comment. */
  volatile std::string comment;

  /**
   * The maximum age in seconds. Use 0 to discard an existing cookie.
   */
  volatile int maxAge;

  /** Indicates if cookie should only be transmitted by secure means. */
  volatile bool secure;
  

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_COOKIE_SETTING_H_
