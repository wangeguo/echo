#ifndef _ECHO_DATA_METHOD_H_
#define _ECHO_DATA_METHOD_H_

#include <string>

namespace echo {
namespace data {

/**
 * Method to execute when handling a call.
 * 
 * @author Jerome Louvel
 */
//public final class Method implements Comparable<Method> {
class Method {

 public:

  /**
   * Returns the method associated to a given method name. If an existing
   * constant exists then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The method name.
   * @return The associated method.
   */
  static Method valueOf(const std::string name);

  /**
   * Constructor for unsafe and non idempotent methods.
   * 
   * @param name
   *            The technical name of the method.
   * @see org.restlet.data.Method#valueOf(std::string)
   */
  Method(const std::string name) {
    Method(name, NULL);
  }

  /**
   * Constructor for unsafe and non idempotent methods.
   * 
   * @param name
   *            The technical name of the method.
   * @param description
   *            The description.
   * @see org.restlet.data.Method#valueOf(std::string)
   */
  Method(std::string name, std::string description) {
    Method(name, description, NULL, false, false);
  }

  /**
   * Constructor for unsafe and non idempotent methods.
   * 
   * @param name
   *            The technical name.
   * @param description
   *            The description.
   * @param uri
   *            The URI of the specification describing the method.
   * @see org.restlet.data.Method#valueOf(std::string)
   */
  Method(std::string name, std::string description, std::string uri) {
    Method(name, description, uri, false, false);
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The technical name.
   * @param description
   *            The description.
   * @param uri
   *            The URI of the specification describing the method.
   * @param safe
   *            Indicates if the method is safe.
   * @param idempotent
   *            Indicates if the method is idempotent.
   * @see org.restlet.data.Method#valueOf(std::string)
   */
  Method(std::string name, std::string description, std::string uri, bool safe,
         bool idempotent);

  /**
   * Compares this method to another. Based on the method name.
   * 
   * @param o
   *            The other method.
   */
  int compareTo(Method o);

  /** {@inheritDoc} */
  //@Override
  bool equals(const Object object);

  /**
   * Returns the description.
   * 
   * @return The description.
   */
  std::string getDescription() {
    return this->description;
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
   * Returns the URI of the specification describing the method.
   * 
   * @return The URI of the specification describing the method.
   */
  std::string getUri() {
    return this->uri;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return (getName() == NULL) ? 0 : getName().hashCode();
  }

  /**
   * Indicates if the side-effects of several requests is the same as a single
   * request.
   * 
   * @return True if the method is idempotent.
   */
  bool isIdempotent() {
    return idempotent;
  }

  /**
   * Indicates if it should have the significance of taking an action other
   * than retrieval.
   * 
   * @return True if the method is safe.
   */
  bool isSafe() {
    return safe;
  }

  /**
   * Sets the URI of the specification describing the method.
   * 
   * @param uri
   *            The URI of the specification describing the method.
   * 
   * @deprecated Method instances are shared by all Restlet applications and
   *             shouldn't be modifiable.
   */
  //@Deprecated
  void setUri(std::string uri) {
    this->uri = uri;
  }

  /**
   * Returns the name.
   * 
   * @return The name.
   */
  //@Override
  std::string toString() {
    return getName();
  }

 public:

    
  /**
   * Pseudo-method use to match all methods.
   */
  static const Method ALL;

  /**
   * Used with a proxy that can dynamically switch to being a tunnel.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.9">HTTP
   *      RFC - 9.9 CONNECT</a>
   */
  static const Method CONNECT;

  /**
   * Creates a duplicate of the source resource, identified by the
   * Request-URI, in the destination resource, identified by the URI in the
   * Destination header.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_COPY">WEBDAV
   *      RFC - 8.8 COPY Method</a>
   */
  static const Method COPY;

  /**
   * Requests that the origin server deletes the resource identified by the
   * request URI.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.7">HTTP
   *      RFC - 9.7 DELETE</a>
   */
  static const Method DELETE;

  /**
   * Retrieves whatever information (in the form of an entity) that is
   * identified by the request URI.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.3">HTTP
   *      RFC - 9.3 GET</a>
   */
  static const Method GET;

  /**
   * Identical to GET except that the server must not return a message body in
   * the response but only the message header.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.4">HTTP
   *      RFC - 9.4 GET</a>
   */
  static const Method HEAD;

  /**
   * Used to take out a lock of any access type on the resource identified by
   * the request URI.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_LOCK">WEBDAV
   *      RFC - 8.10 LOCK Method</a>
   */
  static const Method LOCK;

  /**
   * MKCOL creates a new collection resource at the location specified by the
   * Request URI.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_MKCOL">WEBDAV
   *      RFC - 8.3 MKCOL Method</a>
   */
  static const Method MKCOL;

  /**
   * Logical equivalent of a copy, followed by consistency maintenance
   * processing, followed by a delete of the source where all three actions
   * are performed atomically.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_MOVE">WEBDAV
   *      RFC - 8.3 MKCOL Method</a>
   */
  static const Method MOVE;

  /**
   * Requests for information about the communication options available on the
   * request/response chain identified by the URI.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.2">HTTP
   *      RFC - 9.2 OPTIONS</a>
   */
  static const Method OPTIONS;

  /**
   * Requests that the origin server accepts the entity enclosed in the
   * request as a new subordinate of the resource identified by the request
   * URI.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.5">HTTP
   *      RFC - 9.5 POST</a>
   */
  static const Method POST;

  /**
   * Retrieves properties defined on the resource identified by the request
   * URI.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_PROPFIND">WEBDAV
   *      RFC - 8.1 PROPFIND</a>
   */
  static const Method PROPFIND;

  /**
   * Processes instructions specified in the request body to set and/or remove
   * properties defined on the resource identified by the request URI.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_PROPPATCH">WEBDAV
   *      RFC - 8.2 PROPPATCH</a>
   */
  static const Method PROPPATCH;

  /**
   * Requests that the enclosed entity be stored under the supplied request
   * URI.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.6"
   *      HTTP RFC - 9.6 PUT</a>
   */
  static const Method PUT;

  /**
   * Used to invoke a remote, application-layer loop-back of the request
   * message.
   * 
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html#sec9.8">HTTP
   *      RFC - 9.8 TRACE</a>
   */
  static const Method TRACE;

  /**
   * Removes the lock identified by the lock token from the request URI, and
   * all other resources included in the lock.
   * 
   * @see <a
   *      href="http://www.webdav.org/specs/rfc2518.html#METHOD_UNLOCK">WEBDAV
   *      RFC - 8.11 UNLOCK Method</a>
   */
  static const Method UNLOCK;

 private:

  static const std::string BASE_HTTP;

  static const std::string BASE_WEBDAV;

  /** The description. */
  const std::string description;

  /**
   * Indicates if the side-effects of several requests is the same as a single
   * request.
   */
  volatile bool idempotent;

  /** The name. */
  volatile std::string name;

  /**
   * Indicates if it should have the significance of taking an action other
   * than retrieval.
   */
  const bool safe;

  /** The URI of the specification describing the method. */
  volatile std::string uri;


};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_METHOD_H_
