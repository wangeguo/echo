#include <echo/data/status.h>

namespace echo {
namespace data {

const Status Status::CLIENT_ERROR_BAD_REQUEST = new Status(400);

const Status Status::CLIENT_ERROR_CONFLICT = new Status(409);

const Status Status::CLIENT_ERROR_EXPECTATION_FAILED = new Status(417);

const Status Status::CLIENT_ERROR_FAILED_DEPENDENCY = new Status(424);

const Status Status::CLIENT_ERROR_FORBIDDEN = new Status(403);

const Status Status::CLIENT_ERROR_GONE = new Status(410);

const Status Status::CLIENT_ERROR_LENGTH_REQUIRED = new Status(411);

const Status Status::CLIENT_ERROR_LOCKED = new Status(423);

const Status Status::CLIENT_ERROR_METHOD_NOT_ALLOWED = new Status(405);

const Status Status::CLIENT_ERROR_NOT_ACCEPTABLE = new Status(406);

const Status Status::CLIENT_ERROR_NOT_FOUND = new Status(404);

const Status Status::CLIENT_ERROR_PAYMENT_REQUIRED = new Status(402);

const Status Status::CLIENT_ERROR_PRECONDITION_FAILED = new Status(
    412);

const Status Status::CLIENT_ERROR_PROXY_AUTHENTIFICATION_REQUIRED = new Status(
    407);

const Status Status::CLIENT_ERROR_REQUEST_ENTITY_TOO_LARGE = new Status(
    413);

const Status Status::CLIENT_ERROR_REQUEST_TIMEOUT = new Status(408);

const Status Status::CLIENT_ERROR_REQUEST_URI_TOO_LONG = new Status(
    414);

const Status Status::CLIENT_ERROR_REQUESTED_RANGE_NOT_SATISFIABLE = new Status(
    416);

const Status Status::CLIENT_ERROR_UNAUTHORIZED = new Status(401);

const Status Status::CLIENT_ERROR_UNPROCESSABLE_ENTITY = new Status(422);

const Status Status::CLIENT_ERROR_UNSUPPORTED_MEDIA_TYPE = new Status(
    415);

const Status Status::CONNECTOR_ERROR_COMMUNICATION = new Status(1001);

const Status Status::CONNECTOR_ERROR_CONNECTION = new Status(1000);

const Status Status::CONNECTOR_ERROR_INTERNAL = new Status(1002);

const Status Status::INFO_CONTINUE = new Status(100);

const Status Status::INFO_PROCESSING = new Status(102);

const Status Status::INFO_SWITCHING_PROTOCOL = new Status(101);

const Status Status::INFO_STALE_RESPONSE = new Status(110);

const Status Status::INFO_REVALIDATION_FAILED = new Status(111);

const Status Status::INFO_DISCONNECTED_OPERATION = new Status(112);

const Status Status::INFO_HEURISTIC_EXPIRATION = new Status(113);

const Status Status::INFO_MISC_WARNING = new Status(199);

const Status Status::REDIRECTION_FOUND = new Status(302);

const Status Status::REDIRECTION_MULTIPLE_CHOICES = new Status(300);

const Status Status::REDIRECTION_NOT_MODIFIED = new Status(304);

const Status Status::REDIRECTION_PERMANENT = new Status(301);

const Status Status::REDIRECTION_SEE_OTHER = new Status(303);

const Status Status::REDIRECTION_TEMPORARY = new Status(307);

const Status Status::REDIRECTION_USE_PROXY = new Status(305);

const Status Status::SERVER_ERROR_BAD_GATEWAY = new Status(502);

const Status Status::SERVER_ERROR_GATEWAY_TIMEOUT = new Status(504);

const Status Status::SERVER_ERROR_INSUFFICIENT_STORAGE = new Status(
    507);

const Status Status::SERVER_ERROR_INTERNAL = new Status(500);

const Status Status::SERVER_ERROR_NOT_IMPLEMENTED = new Status(501);

const Status Status::SERVER_ERROR_SERVICE_UNAVAILABLE = new Status(
    503);

const Status Status::SERVER_ERROR_VERSION_NOT_SUPPORTED = new Status(
    505);

const Status Status::SUCCESS_ACCEPTED = new Status(202);

const Status Status::SUCCESS_CREATED = new Status(201);

const Status Status::SUCCESS_MULTI_STATUS = new Status(207);

const Status Status::SUCCESS_NO_CONTENT = new Status(204);

const Status Status::SUCCESS_NON_AUTHORITATIVE = new Status(203);

const Status Status::SUCCESS_OK = new Status(200);

const Status Status::SUCCESS_TRANSFORMATION_APPLIED = new Status(214);

const Status Status::SUCCESS_MISC_PERSISTENT_WARNING = new Status(299);

const Status Status::SUCCESS_PARTIAL_CONTENT = new Status(206);


const Status Status::SUCCESS_RESET_CONTENT = new Status(205);

bool Status::isError(int code) {
  return isClientError(code) || isServerError(code)
      || isConnectorError(code);
}


Status Status::valueOf(int code) {
  Status result = null;

  switch (code) {
    case 100:
      result = INFO_CONTINUE;
      break;
    case 101:
      result = INFO_SWITCHING_PROTOCOL;
      break;
    case 102:
      result = INFO_PROCESSING;
      break;
    case 110:
      result = INFO_STALE_RESPONSE;
      break;
    case 111:
      result = INFO_REVALIDATION_FAILED;
      break;
    case 112:
      result = INFO_DISCONNECTED_OPERATION;
      break;
    case 113:
      result = INFO_HEURISTIC_EXPIRATION;
      break;
    case 199:
      result = INFO_MISC_WARNING;
      break;

    case 200:
      result = SUCCESS_OK;
      break;
    case 201:
      result = SUCCESS_CREATED;
      break;
    case 202:
      result = SUCCESS_ACCEPTED;
      break;
    case 203:
      result = SUCCESS_NON_AUTHORITATIVE;
      break;
    case 204:
      result = SUCCESS_NO_CONTENT;
      break;
    case 205:
      result = SUCCESS_RESET_CONTENT;
      break;
    case 206:
      result = SUCCESS_PARTIAL_CONTENT;
      break;
    case 207:
      result = SUCCESS_MULTI_STATUS;
      break;
    case 214:
      result = SUCCESS_TRANSFORMATION_APPLIED;
      break;
    case 299:
      result = SUCCESS_MISC_PERSISTENT_WARNING;
      break;

    case 300:
      result = REDIRECTION_MULTIPLE_CHOICES;
      break;
    case 301:
      result = REDIRECTION_PERMANENT;
      break;
    case 302:
      result = REDIRECTION_FOUND;
      break;
    case 303:
      result = REDIRECTION_SEE_OTHER;
      break;
    case 304:
      result = REDIRECTION_NOT_MODIFIED;
      break;
    case 305:
      result = REDIRECTION_USE_PROXY;
      break;
    case 307:
      result = REDIRECTION_TEMPORARY;
      break;

    case 400:
      result = CLIENT_ERROR_BAD_REQUEST;
      break;
    case 401:
      result = CLIENT_ERROR_UNAUTHORIZED;
      break;
    case 402:
      result = CLIENT_ERROR_PAYMENT_REQUIRED;
      break;
    case 403:
      result = CLIENT_ERROR_FORBIDDEN;
      break;
    case 404:
      result = CLIENT_ERROR_NOT_FOUND;
      break;
    case 405:
      result = CLIENT_ERROR_METHOD_NOT_ALLOWED;
      break;
    case 406:
      result = CLIENT_ERROR_NOT_ACCEPTABLE;
      break;
    case 407:
      result = CLIENT_ERROR_PROXY_AUTHENTIFICATION_REQUIRED;
      break;
    case 408:
      result = CLIENT_ERROR_REQUEST_TIMEOUT;
      break;
    case 409:
      result = CLIENT_ERROR_CONFLICT;
      break;
    case 410:
      result = CLIENT_ERROR_GONE;
      break;
    case 411:
      result = CLIENT_ERROR_LENGTH_REQUIRED;
      break;
    case 412:
      result = CLIENT_ERROR_PRECONDITION_FAILED;
      break;
    case 413:
      result = CLIENT_ERROR_REQUEST_ENTITY_TOO_LARGE;
      break;
    case 414:
      result = CLIENT_ERROR_REQUEST_URI_TOO_LONG;
      break;
    case 415:
      result = CLIENT_ERROR_UNSUPPORTED_MEDIA_TYPE;
      break;
    case 416:
      result = CLIENT_ERROR_REQUESTED_RANGE_NOT_SATISFIABLE;
      break;
    case 417:
      result = CLIENT_ERROR_EXPECTATION_FAILED;
      break;
    case 422:
      result = CLIENT_ERROR_UNPROCESSABLE_ENTITY;
      break;
    case 423:
      result = CLIENT_ERROR_LOCKED;
      break;
    case 424:
      result = CLIENT_ERROR_FAILED_DEPENDENCY;
      break;

    case 500:
      result = SERVER_ERROR_INTERNAL;
      break;
    case 501:
      result = SERVER_ERROR_NOT_IMPLEMENTED;
      break;
    case 502:
      result = SERVER_ERROR_BAD_GATEWAY;
      break;
    case 503:
      result = SERVER_ERROR_SERVICE_UNAVAILABLE;
      break;
    case 504:
      result = SERVER_ERROR_GATEWAY_TIMEOUT;
      break;
    case 505:
      result = SERVER_ERROR_VERSION_NOT_SUPPORTED;
      break;
    case 507:
      result = SERVER_ERROR_INSUFFICIENT_STORAGE;
      break;

    case 1000:
      result = CONNECTOR_ERROR_CONNECTION;
      break;
    case 1001:
      result = CONNECTOR_ERROR_COMMUNICATION;
      break;
    case 1002:
      result = CONNECTOR_ERROR_INTERNAL;
      break;

    default:
      result = new Status(code);
  }

  return result;
}

Status::Status(int code, Throwable throwable, const std::string name,
               const std::string description, const std::string uri) {
  this->name = name;
  this->description = checkDescription(description);
  this->throwable = throwable;
  this->code = code;
  this->uri = uri;
}

Status::Status(const Status status, const std::string description) {
  Status(status.getCode(), status.getName(), description, status.getUri());
}

Status::Status(const Status status, const Throwable throwable) {
  Status(status.getCode(), throwable, status.getName(),
         (throwable == null) ? null : throwable.getMessage(), status
         .getUri());
}

Status::Status(const Status status, const Throwable throwable,
               const std::string description) {
  Status(status.getCode(), throwable, status.getName(), description, status
         .getUri());
}

@Override
bool Status::equals(const Object object) {
  return (object instanceof Status)
      && (this->code == ((Status) object).getCode());
}

std::string Status::getDescription() {
  std::string result = this->description;

  if (result == null) {
    switch (this->code) {
      case 100:
        result = "The client should continue with its request";
        break;
      case 101:
        result = "The server is willing to change the application protocol being used on this connection";
        break;
      case 102:
        result = "Interim response used to inform the client that the server has accepted the complete request, but has not yet completed it";
        break;
      case 110:
        result = "MUST be included whenever the returned response is stale";
        break;
      case 111:
        result = "MUST be included if a cache returns a stale response because an attempt to revalidate the response failed, due to an inability to reach the server";
        break;
      case 112:
        result = "SHOULD be included if the cache is intentionally disconnected from the rest of the network for a period of time";
        break;
      case 113:
        result = "MUST be included if the cache heuristically chose a freshness lifetime greater than 24 hours and the response's age is greater than 24 hours";
        break;
      case 199:
        result = "The warning text MAY include arbitrary information to be presented to a human user, or logged. A system receiving this warning MUST NOT take any automated action, besides presenting the warning to the user";
        break;

      case 200:
        result = "The request has succeeded";
        break;
      case 201:
        result = "The request has been fulfilled and resulted in a new resource being created";
        break;
      case 202:
        result = "The request has been accepted for processing, but the processing has not been completed";
        break;
      case 203:
        result = "The returned metainformation is not the definitive set as available from the origin server";
        break;
      case 204:
        result = "The server has fulfilled the request but does not need to return an entity-body, and might want to return updated metainformation";
        break;
      case 205:
        result = "The server has fulfilled the request and the user agent should reset the document view which caused the request to be sent";
        break;
      case 206:
        result = "The server has fulfilled the partial get request for the resource";
        break;
      case 207:
        result = "Provides status for multiple independent operations";
        break;
      case 214:
        result = "MUST be added by an intermediate cache or proxy if it applies any transformation changing the content-coding (as specified in the Content-Encoding header) or media-type (as specified in the Content-Type header) of the response, or the entity-body of the response, unless this Warning code already appears in the response";
        break;
      case 299:
        result = "The warning text MAY include arbitrary information to be presented to a human user, or logged. A system receiving this warning MUST NOT take any automated action";
        break;

      case 300:
        result = "The requested resource corresponds to any one of a set of representations";
        break;
      case 301:
        result = "The requested resource has been assigned a new permanent URI";
        break;
      case 302:
        result = "The requested resource can be found under a different URI";
        break;
      case 303:
        result = "The response to the request can be found under a different URI";
        break;
      case 304:
        result = "The client has performed a conditional GET request and the document has not been modified";
        break;
      case 305:
        result = "The requested resource must be accessed through the proxy given by the location field";
        break;
      case 307:
        result = "The requested resource resides temporarily under a different URI";
        break;

      case 400:
        result = "The request could not be understood by the server due to malformed syntax";
        break;
      case 401:
        result = "The request requires user authentication";
        break;
      case 402:
        result = "This code is reserved for future use";
        break;
      case 403:
        result = "The server understood the request, but is refusing to fulfill it";
        break;
      case 404:
        result = "The server has not found anything matching the request URI";
        break;
      case 405:
        result = "The method specified in the request is not allowed for the resource identified by the request URI";
        break;
      case 406:
        result = "The resource identified by the request is only capable of generating response entities which have content characteristics not acceptable according to the accept headers sent in the request";
        break;
      case 407:
        result = "This code is similar to Unauthorized, but indicates that the client must first authenticate itself with the proxy";
        break;
      case 408:
        result = "The client did not produce a request within the time that the server was prepared to wait";
        break;
      case 409:
        result = "The request could not be completed due to a conflict with the current state of the resource";
        break;
      case 410:
        result = "The requested resource is no longer available at the server and no forwarding address is known";
        break;
      case 411:
        result = "The server refuses to accept the request without a defined content length";
        break;
      case 412:
        result = "The precondition given in one or more of the request header fields evaluated to false when it was tested on the server";
        break;
      case 413:
        result = "The server is refusing to process a request because the request entity is larger than the server is willing or able to process";
        break;
      case 414:
        result = "The server is refusing to service the request because the request URI is longer than the server is willing to interpret";
        break;
      case 415:
        result = "The server is refusing to service the request because the entity of the request is in a format not supported by the requested resource for the requested method";
        break;
      case 416:
        result = "For byte ranges, this means that the first byte position were greater than the current length of the selected resource";
        break;
      case 417:
        result = "The expectation given in the request header could not be met by this server";
        break;
      case 422:
        result = "The server understands the content type of the request entity and the syntax of the request entity is correct but was unable to process the contained instructions";
        break;
      case 423:
        result = "The source or destination resource of a method is locked";
        break;
      case 424:
        result = "The method could not be performed on the resource because the requested action depended on another action and that action failed";
        break;

      case 500:
        result = "The server encountered an unexpected condition which prevented it from fulfilling the request";
        break;
      case 501:
        result = "The server does not support the functionality required to fulfill the request";
        break;
      case 502:
        result = "The server, while acting as a gateway or proxy, received an invalid response from the upstream server it accessed in attempting to fulfill the request";
        break;
      case 503:
        result = "The server is currently unable to handle the request due to a temporary overloading or maintenance of the server";
        break;
      case 504:
        result = "The server, while acting as a gateway or proxy, did not receive a timely response from the upstream server specified by the URI (e.g. HTTP, FTP, LDAP) or some other auxiliary server (e.g. DNS) it needed to access in attempting to complete the request";
        break;
      case 505:
        result = "The server does not support, or refuses to support, the protocol version that was used in the request message";
        break;
      case 507:
        result = "The method could not be performed on the resource because the server is unable to store the representation needed to successfully complete the request";
        break;

      case 1000:
        result = "The connector failed to connect to the server";
        break;
      case 1001:
        result = "The connector failed to complete the communication with the server";
        break;
      case 1002:
        result = "The connector encountered an unexpected condition which prevented it from fulfilling the request";
        break;
    }
  }

  return result;
}

std::string Status::getName() {
  std::string result = this->name;

  if (result == null) {
    switch (this->code) {
      case 100:
        result = "Continue";
        break;
      case 101:
        result = "Switching Protocols";
        break;
      case 102:
        result = "Processing";
        break;
      case 110:
        result = "Response is stale";
        break;
      case 111:
        result = "Revalidation failed";
        break;
      case 112:
        result = "Disconnected operation";
        break;
      case 113:
        result = "Heuristic expiration";
        break;
      case 199:
        result = "Miscellaneous warning";
        break;

      case 200:
        result = "OK";
        break;
      case 201:
        result = "Created";
        break;
      case 202:
        result = "Accepted";
        break;
      case 203:
        result = "Non-Authoritative Information";
        break;
      case 204:
        result = "No Content";
        break;
      case 205:
        result = "Reset Content";
        break;
      case 206:
        result = "Partial Content";
        break;
      case 207:
        result = "Multi-Status";
        break;
      case 214:
        result = "Transformation applied";
        break;
      case 299:
        result = "Miscellaneous persistent warning";
        break;

      case 300:
        result = "Multiple Choices";
        break;
      case 301:
        result = "Moved Permanently";
        break;
      case 302:
        result = "Found";
        break;
      case 303:
        result = "See Other";
        break;
      case 304:
        result = "Not Modified";
        break;
      case 305:
        result = "Use Proxy";
        break;
      case 307:
        result = "Temporary Redirect";
        break;

      case 400:
        result = "Bad Request";
        break;
      case 401:
        result = "Unauthorized";
        break;
      case 402:
        result = "Payment Required";
        break;
      case 403:
        result = "Forbidden";
        break;
      case 404:
        result = "Not Found";
        break;
      case 405:
        result = "Method Not Allowed";
        break;
      case 406:
        result = "Not Acceptable";
        break;
      case 407:
        result = "Proxy Authentication Required";
        break;
      case 408:
        result = "Request Timeout";
        break;
      case 409:
        result = "Conflict";
        break;
      case 410:
        result = "Gone";
        break;
      case 411:
        result = "Length Required";
        break;
      case 412:
        result = "Precondition Failed";
        break;
      case 413:
        result = "Request Entity Too Large";
        break;
      case 414:
        result = "Request URI Too Long";
        break;
      case 415:
        result = "Unsupported Media Type";
        break;
      case 416:
        result = "Requested Range Not Satisfiable";
        break;
      case 417:
        result = "Expectation Failed";
        break;
      case 422:
        result = "Unprocessable Entity";
        break;
      case 423:
        result = "Locked";
        break;
      case 424:
        result = "Failed Dependency";
        break;

      case 500:
        result = "Internal Server Error";
        break;
      case 501:
        result = "Not Implemented";
        break;
      case 502:
        result = "Bad Gateway";
        break;
      case 503:
        result = "Service Unavailable";
        break;
      case 504:
        result = "Gateway Timeout";
        break;
      case 505:
        result = "Version Not Supported";
        break;
      case 507:
        result = "Insufficient Storage";
        break;

      case 1000:
        result = "Connection Error";
        break;
      case 1001:
        result = "Communication Error";
        break;
      case 1002:
        result = "Internal Connector Error";
        break;
    }
  }

  return result;
}

std::string Status::getUri() {
  std::string result = this->uri;

  if (result == null) {
    switch (this->code) {
      case 100:
        result = BASE_HTTP + "#sec10.1.1";
        break;
      case 101:
        result = BASE_HTTP + "#sec10.1.2";
        break;
      case 102:
        result = BASE_WEBDAV + "#STATUS_102";
        break;
      case 110:
      case 111:
      case 112:
      case 113:
      case 199:
      case 214:
      case 299:
        result = "http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46";
        break;

      case 200:
        result = BASE_HTTP + "#sec10.2.1";
        break;
      case 201:
        result = BASE_HTTP + "#sec10.2.2";
        break;
      case 202:
        result = BASE_HTTP + "#sec10.2.3";
        break;
      case 203:
        result = BASE_HTTP + "#sec10.2.4";
        break;
      case 204:
        result = BASE_HTTP + "#sec10.2.5";
        break;
      case 205:
        result = BASE_HTTP + "#sec10.2.6";
        break;
      case 206:
        result = BASE_HTTP + "#sec10.2.7";
        break;
      case 207:
        result = BASE_WEBDAV + "#STATUS_207";
        break;

      case 300:
        result = BASE_HTTP + "#sec10.3.1";
        break;
      case 301:
        result = BASE_HTTP + "#sec10.3.2";
        break;
      case 302:
        result = BASE_HTTP + "#sec10.3.3";
        break;
      case 303:
        result = BASE_HTTP + "#sec10.3.4";
        break;
      case 304:
        result = BASE_HTTP + "#sec10.3.5";
        break;
      case 305:
        result = BASE_HTTP + "#sec10.3.6";
        break;
      case 307:
        result = BASE_HTTP + "#sec10.3.8";
        break;

      case 400:
        result = BASE_HTTP + "#sec10.4.1";
        break;
      case 401:
        result = BASE_HTTP + "#sec10.4.2";
        break;
      case 402:
        result = BASE_HTTP + "#sec10.4.3";
        break;
      case 403:
        result = BASE_HTTP + "#sec10.4.4";
        break;
      case 404:
        result = BASE_HTTP + "#sec10.4.5";
        break;
      case 405:
        result = BASE_HTTP + "#sec10.4.6";
        break;
      case 406:
        result = BASE_HTTP + "#sec10.4.7";
        break;
      case 407:
        result = BASE_HTTP + "#sec10.4.8";
        break;
      case 408:
        result = BASE_HTTP + "#sec10.4.9";
        break;
      case 409:
        result = BASE_HTTP + "#sec10.4.10";
        break;
      case 410:
        result = BASE_HTTP + "#sec10.4.11";
        break;
      case 411:
        result = BASE_HTTP + "#sec10.4.12";
        break;
      case 412:
        result = BASE_HTTP + "#sec10.4.13";
        break;
      case 413:
        result = BASE_HTTP + "#sec10.4.14";
        break;
      case 414:
        result = BASE_HTTP + "#sec10.4.15";
        break;
      case 415:
        result = BASE_HTTP + "#sec10.4.16";
        break;
      case 416:
        result = BASE_HTTP + "#sec10.4.17";
        break;
      case 417:
        result = BASE_HTTP + "#sec10.4.18";
        break;
      case 422:
        result = BASE_WEBDAV + "#STATUS_422";
        break;
      case 423:
        result = BASE_WEBDAV + "#STATUS_423";
        break;
      case 424:
        result = BASE_WEBDAV + "#STATUS_424";
        break;

      case 500:
        result = BASE_HTTP + "#sec10.5.1";
        break;
      case 501:
        result = BASE_HTTP + "#sec10.5.2";
        break;
      case 502:
        result = BASE_HTTP + "#sec10.5.3";
        break;
      case 503:
        result = BASE_HTTP + "#sec10.5.4";
        break;
      case 504:
        result = BASE_HTTP + "#sec10.5.5";
        break;
      case 505:
        result = BASE_HTTP + "#sec10.5.6";
        break;
      case 507:
        result = BASE_WEBDAV + "#STATUS_507";
        break;

      case 1000:
        result = BASE_RESTLET
                 + "org/restlet/data/Status.html#CONNECTOR_ERROR_CONNECTION";
        break;
      case 1001:
        result = BASE_RESTLET
                 + "org/restlet/data/Status.html#CONNECTOR_ERROR_COMMUNICATION";
        break;
      case 1002:
        result = BASE_RESTLET
                 + "org/restlet/data/Status.html#CONNECTOR_ERROR_INTERNAL";
        break;
    }
  }

  return result;
}

//@Override
int Status::hashCode() {
  return getCode();
}

bool Status::isClientError() {
  return isClientError(getCode());
}

bool Status::isConnectorError() {
  return isConnectorError(getCode());
}

bool Status::isError() {
  return isError(getCode());
}

bool Status::isInformational() {
  return isInformational(getCode());
}

bool Status::isRecoverableError() {
  return isConnectorError()
      || equals(Status.CLIENT_ERROR_REQUEST_TIMEOUT)
      || equals(Status.SERVER_ERROR_GATEWAY_TIMEOUT)
      || equals(Status.SERVER_ERROR_SERVICE_UNAVAILABLE);
}

bool Status::isRedirection() {
  return isRedirection(getCode());
}

bool Status::isServerError() {
  return isServerError(getCode());
}

bool Status::isSuccess() {
  return isSuccess(getCode());
}

//@Override
std::string Status::toString() {
  return getName() + " (" + this->code + ")"
      + ((getDescription() == null) ? "" : " - " + getDescription());
}

std::string Status::checkDescription(std::string description) {
  if (description != null) {
    if (description.contains("\n") && description.contains("\r")) {
      throw new IllegalArgumentException(
          "Description of the status must not contain CR and LF characters.");
    }
  }

  return description;
}


        
const std::string Status::BASE_HTTP = "http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html";

const std::string Status::BASE_RESTLET = "http://www.restlet.org/documentation/"
                                         + Engine.MAJOR_NUMBER
                                         + '.'
                                         + Engine.MINOR_NUMBER
                                         + "/"
                                         + Edition.CURRENT.getShortName().toLowerCase() + "/api/";

const std::string Status::BASE_WEBDAV = "http://www.webdav.org/specs/rfc2518.html";

} // namespace data
} // namespace echo

