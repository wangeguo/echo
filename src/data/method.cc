#include <echo/data/method.h>

namespace echo {
namespace data {

const Method Method::ALL("*",
                         "Pseudo-method use to match all methods.");

const Method Method::CONNECT("CONNECT",
                             "Used with a proxy that can dynamically switch to being a tunnel",
                             BASE_HTTP + "#sec9.9", false, false);

const Method Method::COPY(
    "COPY",
    "Creates a duplicate of the source resource, identified by the Request-URI, in the destination resource, identified by the URI in the Destination header",
    BASE_WEBDAV + "#METHOD_COPY", false, true);

const Method Method::DELETE(
    "DELETE",
    "Requests that the origin server deletes the resource identified by the request URI",
    BASE_HTTP + "#sec9.7", false, true);

const Method Method::GET(
    "GET",
    "Retrieves whatever information (in the form of an entity) that is identified by the request URI",
    BASE_HTTP + "#sec9.3", true, true);

const Method Method::HEAD(
    "HEAD",
    "Identical to GET except that the server must not return a message body in the response",
    BASE_HTTP + "#sec9.4", true, true);

const Method Method::LOCK(
    "LOCK",
    "Used to take out a lock of any access type (WebDAV)", BASE_WEBDAV
    + "#METHOD_LOCK", true, false);

const Method Method::MKCOL("MKCOL",
                           "Used to create a new collection (WebDAV)", BASE_WEBDAV
                           + "#METHOD_MKCOL", false, true);

const Method Method::MOVE(
    "MOVE",
    "Logical equivalent of a copy, followed by consistency maintenance processing, followed by a delete of the source (WebDAV)",
    BASE_WEBDAV + "#METHOD_MOVE", false, false);

const Method Method::OPTIONS(
    "OPTIONS",
    "Requests for information about the communication options available on the request/response chain identified by the URI",
    BASE_HTTP + "#sec9.2", true, true);

const Method Method::POST(
    "POST",
    "Requests that the origin server accepts the entity enclosed in the request as a new subordinate of the resource identified by the request URI",
    BASE_HTTP + "#sec9.5", false, false);

const Method Method::PROPFIND(
    "PROPFIND",
    "Retrieves properties defined on the resource identified by the request URI",
    BASE_WEBDAV + "#METHOD_PROPFIND", true, true);

const Method Method::PROPPATCH = new Method(
    "PROPPATCH",
    "Processes instructions specified in the request body to set and/or remove properties defined on the resource identified by the request URI",
    BASE_WEBDAV + "#METHOD_PROPPATCH", false, true);

const Method Method::PUT(
    "PUT",
    "Requests that the enclosed entity be stored under the supplied request URI",
    BASE_HTTP + "#sec9.6", false, true);

const Method Method::TRACE = new Method(
    "TRACE",
    "Used to invoke a remote, application-layer loop-back of the request message",
    BASE_HTTP + "#sec9.8", true, true);

const Method Method::UNLOCK(
    "UNLOCK",
    "Removes the lock identified by the lock token from the request URI, and all other resources included in the lock",
    BASE_WEBDAV + "#METHOD_UNLOCK", true, false);


//private
const std::string
Method::BASE_HTTP = "http://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html";

const std::string Method::BASE_WEBDAV = "http://www.webdav.org/specs/rfc2518.html";

Method Method::valueOf(const std::string name) {
  Method result = NULL;

  if ((name != NULL) && !name.equals("")) {
    if (name.equalsIgnoreCase(GET.getName())) {
      result = GET;
    } else if (name.equalsIgnoreCase(POST.getName())) {
      result = POST;
    } else if (name.equalsIgnoreCase(HEAD.getName())) {
      result = HEAD;
    } else if (name.equalsIgnoreCase(OPTIONS.getName())) {
      result = OPTIONS;
    } else if (name.equalsIgnoreCase(PUT.getName())) {
      result = PUT;
    } else if (name.equalsIgnoreCase(DELETE.getName())) {
      result = DELETE;
    } else if (name.equalsIgnoreCase(CONNECT.getName())) {
      result = CONNECT;
    } else if (name.equalsIgnoreCase(COPY.getName())) {
      result = COPY;
    } else if (name.equalsIgnoreCase(LOCK.getName())) {
      result = LOCK;
    } else if (name.equalsIgnoreCase(MKCOL.getName())) {
      result = MKCOL;
    } else if (name.equalsIgnoreCase(MOVE.getName())) {
      result = MOVE;
    } else if (name.equalsIgnoreCase(PROPFIND.getName())) {
      result = PROPFIND;
    } else if (name.equalsIgnoreCase(PROPPATCH.getName())) {
      result = PROPPATCH;
    } else if (name.equalsIgnoreCase(TRACE.getName())) {
      result = TRACE;
    } else if (name.equalsIgnoreCase(UNLOCK.getName())) {
      result = UNLOCK;
    } else {
      result = new Method(name);
    }
  }

  return result;
}

Method::Method(std::string name, std::string description, std::string uri, bool safe,
               bool idempotent) {
  this->name = name;
  this->description = description;
  this->uri = uri;
  this->safe = safe;
  this->idempotent = idempotent;
}

int Method::compareTo(Method o) {
  if (o != NULL) {
    return this->getName().compareTo(o.getName());
  }
  return 1;
}

bool Method::equals(const Object object) {
  return (object instanceof Method)
      && ((Method) object).getName().equals(getName());
}

} // namespace data
} // namespace echo


