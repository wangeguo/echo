#ifndef _ECHO_DATA_COOKIE_H_
#define _ECHO_DATA_COOKIE_H_

#include <echo/request.h>
#include <echo/engine/util/system-utils.h>

namespace echo {
namespace data {



/**
 * Cookie provided by a client. To get the list of all cookies sent by a client,
 * you can use the {@link Request#getCookies()} method.<br>
 * <br>
 * Note that if you are on the server side and want to set a cookie on the
 * client, you should use the {@link CookieSetting} class instead.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the "Cookie"
 * header.
 * 
 * @see Request#getCookies()
 * @author Jerome Louvel
 */
//public class Cookie extends Parameter {
class Cookie : public Parameter {

 public:
  /**
   * Constructor.
   */
  Cookie() {
    Cookie(0, NULL, NULL, NULL, NULL);
  }

  /**
   * Constructor.
   * 
   * @param version
   *            The version number.
   * @param name
   *            The name.
   * @param value
   *            The value.
   */
  Cookie(int version, std::string name, std::string value) {
    Cookie(version, name, value, NULL, NULL);
  }

  /**
   * Constructor.
   * 
   * @param version
   *            The version number.
   * @param name
   *            The name.
   * @param value
   *            The value.
   * @param path
   *            The validity path.
   * @param domain
   *            The domain name.
   */
  Cookie(int version, std::string name, std::string value, std::string path,
         std::string domain);

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param value
   *            The value.
   */
  Cookie(std::string name, std::string value) {
    Cookie(0, name, value, NULL, NULL);
  }

  /** {@inheritDoc} */
  //@Override
  bool equals(Object obj);

  /**
   * Returns the domain name.
   * 
   * @return The domain name.
   */
  std::string getDomain() {
    return this->domain;
  }

  /**
   * Returns the validity path.
   * 
   * @return The validity path.
   */
  std::string getPath() {
    return this->path;
  }

  /**
   * Returns the cookie specification version.
   * 
   * @return The cookie specification version.
   */
  int getVersion() {
    return this->version;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return SystemUtils.hashCode(super.hashCode(), getVersion(), getPath(),
                                getDomain());
  }

  /**
   * Sets the domain name.
   * 
   * @param domain
   *            The domain name.
   */
  void setDomain(std::string domain) {
    this->domain = domain;
  }

  /**
   * Sets the validity path.
   * 
   * @param path
   *            The validity path.
   */
  void setPath(std::string path) {
    this->path = path;
  }

  /**
   * Sets the cookie specification version.
   * 
   * @param version
   *            The cookie specification version.
   */
  void setVersion(int version) {
    this->version = version;
  }
	
 private:
  /** The domain name. */
  volatile std::string domain;

  /** The validity path. */
  volatile std::string path;

  /** The version number. */
  volatile int version;
};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_COOKIE_H_
