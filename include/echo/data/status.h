#ifndef _ECHO_DATA_STATUS_H_
#define _ECHO_DATA_STATUS_H_

/*
  import org.restlet.engine.Edition;
  import org.restlet.engine.Engine;
*/

#include <string>

namespace echo {
  namespace data {

    /**
     * Status to return after handling a call.
     * 
     * @author Jerome Louvel
     */
    //public final class Status {
    class Status {

   public:
      /**
       * The request could not be understood by the server due to malformed
       * syntax.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.1">HTTP
       *      RFC - 10.4.1 400 Bad Request</a>
       */
      static const Status CLIENT_ERROR_BAD_REQUEST;

      /**
       * The request could not be completed due to a conflict with the current
       * state of the resource (as experienced in a version control system).
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.10">HTTP
       *      RFC - 10.4.10 409 Conflict</a>
       */
      static const Status CLIENT_ERROR_CONFLICT;

      /**
       * The user agent expects some behavior of the server (given in an Expect
       * request-header field), but this expectation could not be met by this
       * server.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.18">HTTP
       *      RFC - 10.4.18 417 Expectation Failed</a>
       */
      static const Status CLIENT_ERROR_EXPECTATION_FAILED;

      /**
       * This status code means that the method could not be performed on the
       * resource because the requested action depended on another action and that
       * action failed.
       * 
       * @see <a href="http://www.webdav.org/specs/rfc2518.html#STATUS_424">WEBDAV
       *      RFC - 10.5 424 Failed Dependency</a>
       */
      static const Status CLIENT_ERROR_FAILED_DEPENDENCY;

      /**
       * The server understood the request, but is refusing to fulfill it as it
       * could be explained in the entity.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.4">HTTP
       *      RFC - 10.4.4 403 Forbidden</a>
       */
      static const Status CLIENT_ERROR_FORBIDDEN;

      /**
       * The requested resource is no longer available at the server and no
       * forwarding address is known.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.11">HTTP
       *      RFC - 10.4.11 410 Gone</a>
       */
      static const Status CLIENT_ERROR_GONE;

      /**
       * The server refuses to accept the request without a defined
       * Content-Length.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.12">HTTP
       *      RFC - 10.4.12 411 Length Required</a>
       */
      static const Status CLIENT_ERROR_LENGTH_REQUIRED;

      /**
       * The source or destination resource of a method is locked (or temporarily
       * involved in another process).
       * 
       * @see <a href="http://www.webdav.org/specs/rfc2518.html#STATUS_423">WEBDAV
       *      RFC - 10.4 423 Locked</a>
       */
      static const Status CLIENT_ERROR_LOCKED;

      /**
       * The method specified in the Request-Line is not allowed for the resource
       * identified by the Request-URI.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.6">HTTP
       *      RFC - 10.4.6 405 Method Not Allowed</a>
       */
      static const Status CLIENT_ERROR_METHOD_NOT_ALLOWED;

      /**
       * The resource identified by the request is only capable of generating
       * response entities whose content characteristics do not match the user's
       * requirements (in Accept* headers).
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.7">HTTP
       *      RFC - 10.4.7 406 Not Acceptable</a>
       */
      static const Status CLIENT_ERROR_NOT_ACCEPTABLE;

      /**
       * The server has not found anything matching the Request-URI or the server
       * does not wish to reveal exactly why the request has been refused, or no
       * other response is applicable.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.5">HTTP
       *      RFC - 10.4.5 404 Not Found</a>
       */
      static const Status CLIENT_ERROR_NOT_FOUND;

      /**
       * This code is reserved for future use.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.3">HTTP
       *      RFC - 10.4.3 402 Payment Required</a>
       */
      static const Status CLIENT_ERROR_PAYMENT_REQUIRED;

      /**
       * Sent by the server when the user agent asks the server to carry out a
       * request under certain conditions that are not met.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.13">HTTP
       *      RFC - 10.4.13 412 Precondition Failed</a>
       */
      static const Status CLIENT_ERROR_PRECONDITION_FAILED;

      /**
       * This code is similar to 401 (Unauthorized), but indicates that the client
       * must first authenticate itself with the proxy.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.8">HTTP
       *      RFC - 10.4.8 407 Proxy Authentication Required</a>
       */
      static const Status CLIENT_ERROR_PROXY_AUTHENTIFICATION_REQUIRED;

      /**
       * The server is refusing to process a request because the request entity is
       * larger than the server is willing or able to process.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.14">HTTP
       *      RFC - 10.4.14 413 Request Entity Too Large</a>
       */
      static const Status CLIENT_ERROR_REQUEST_ENTITY_TOO_LARGE;

      /**
       * Sent by the server when an HTTP client opens a connection, but has never
       * sent a request (or never sent the blank line that signals the end of the
       * request).
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.9">HTTP
       *      RFC - 10.4.9 408 Request Timeout</a>
       */
      static const Status CLIENT_ERROR_REQUEST_TIMEOUT;

      /**
       * The server is refusing to service the request because the Request-URI is
       * longer than the server is willing to interpret.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.15">HTTP
       *      RFC - 10.4.15 414 Request-URI Too Long</a>
       */
      static const Status CLIENT_ERROR_REQUEST_URI_TOO_LONG;

      /**
       * The request includes a Range request-header field and the selected
       * resource is too small for any of the byte-ranges to apply.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.17">HTTP
       *      RFC - 10.4.17 416 Requested Range Not Satisfiable</a>
       */
      static const Status CLIENT_ERROR_REQUESTED_RANGE_NOT_SATISFIABLE;

      /**
       * The request requires user authentication.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.2">HTTP
       *      RFC - 10.4.2 401 Unauthorized</a>
       */
      static const Status CLIENT_ERROR_UNAUTHORIZED;

      /**
       * This status code means the server understands the content type of the
       * request entity (syntactically correct) but was unable to process the
       * contained instructions.
       * 
       * @see <a href="http://www.webdav.org/specs/rfc2518.html#STATUS_422">WEBDAV
       *      RFC - 10.3 422 Unprocessable Entity</a>
       */
      static const Status CLIENT_ERROR_UNPROCESSABLE_ENTITY;

      /**
       * The server is refusing to service the request because the entity of the
       * request is in a format not supported by the requested resource for the
       * requested method.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.4.16">HTTP
       *      RFC - 10.4.16 415 Unsupported Media Type</a>
       */
      static const Status CLIENT_ERROR_UNSUPPORTED_MEDIA_TYPE;

      /**
       * A client connector faces an error during the communication with the
       * remote server (interruption, timeout, etc). The status code is 1001.
       */
      static const Status CONNECTOR_ERROR_COMMUNICATION;

      /**
       * A client connector can not connect to the remote server. The status code
       * is 1000.
       */
      static const Status CONNECTOR_ERROR_CONNECTION;

      /**
       * Generic status code sent by a client connector when an error occurs
       * during the process of a request to its server or the process of a
       * response to its client. The status code is 1002.
       */
      static const Status CONNECTOR_ERROR_INTERNAL;

      /**
       * This interim response (the client has to wait for the const response) is
       * used to inform the client that the initial part of the request has been
       * received and has not yet been rejected or completed by the server.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.1.1">HTTP
       *      RFC - 10.1.1 100 Continue</a>
       */
      static const Status INFO_CONTINUE;

      /**
       * This interim response is used to inform the client that the server has
       * accepted the complete request, but has not yet completed it since the
       * server has a reasonable expectation that the request will take
       * significant time to complete.
       * 
       * @see <a href="http://www.webdav.org/specs/rfc2518.html#STATUS_102">WEBDAV
       *      RFC - 10.1 102 Processing</a>
       */
      static const Status INFO_PROCESSING;

      /**
       * The server understands and is willing to comply with the client's
       * request, via the Upgrade message header field, for a change in the
       * application protocol being used on this connection.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.1.2">HTTP
       *      RFC - 10.1.1 101 Switching Protocols</a>
       */
      static const Status INFO_SWITCHING_PROTOCOL;

      /**
       * Warning status code, typically returned by a cache, indicating that the
       * response is stale.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
       *      RFC - 14.46 Warning</a>
       */
      static const Status INFO_STALE_RESPONSE;

      /**
       * Warning status code, typically returned by a cache, indicating that the
       * response is stale because an attempt to revalidate the response failed,
       * due to an inability to reach the server.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
       *      RFC - 14.46 Warning</a>
       */
      static const Status INFO_REVALIDATION_FAILED;

      /**
       * Warning status code, typically returned by a cache, indicating that it is
       * intentionally disconnected from the rest of the network for a period of
       * time.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
       *      RFC - 14.46 Warning</a>
       */
      static const Status INFO_DISCONNECTED_OPERATION;

      /**
       * Warning status code, typically returned by a cache, indicating that it
       * heuristically chose a freshness lifetime greater than 24 hours and the
       * response's age is greater than 24 hours.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
       *      RFC - 14.46 Warning</a>
       */
      static const Status INFO_HEURISTIC_EXPIRATION;

      /**
       * Warning status code, optionally including arbitrary information to be
       * presented to a human user, typically returned by a cache.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
       *      RFC - 14.46 Warning</a>
       */
      static const Status INFO_MISC_WARNING;

      /**
       * The requested resource resides temporarily under a different URI which
       * should not be used for future requests by the client (use status codes
       * 303 or 307 instead since this status has been manifestly misused).
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.3">HTTP
       *      RFC - 10.3.3 302 Found</a>
       */
      static const Status REDIRECTION_FOUND;

      /**
       * The server lets the user agent choosing one of the multiple
       * representations of the requested resource, each representation having its
       * own specific location provided in the response entity.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.1">HTTP
       *      RFC - 10.3.1 300 Multiple Choices</a>
       */
      static const Status REDIRECTION_MULTIPLE_CHOICES;

      /**
       * Status code sent by the server in response to a conditional GET request
       * in case the document has not been modified.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.5">HTTP
       *      RFC - 10.3.5 304 Not Modified</a>
       */
      static const Status REDIRECTION_NOT_MODIFIED;

      /**
       * The requested resource has been assigned a new permanent URI and any
       * future references to this resource SHOULD use one of the returned URIs.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.2">HTTP
       *      RFC - 10.3.2 301 Moved Permanently</a>
       */
      static const Status REDIRECTION_PERMANENT;

      /**
       * The response to the request can be found under a different URI and SHOULD
       * be retrieved using a GET method on that resource.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.4">HTTP
       *      RFC - 10.3.4 303 See Other</a>
       */
      static const Status REDIRECTION_SEE_OTHER;

      /**
       * The requested resource resides temporarily under a different URI which
       * should not be used for future requests by the client.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.8">HTTP
       *      RFC - 10.3.8 307 Temporary Redirect</a>
       */
      static const Status REDIRECTION_TEMPORARY;

      /**
       * The requested resource MUST be accessed through the proxy given by the
       * Location field.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.3.6">HTTP
       *      RFC - 10.3.6 305 Use Proxy</a>
       */
      static const Status REDIRECTION_USE_PROXY;

      /**
       * The server, while acting as a gateway or proxy, received an invalid
       * response from the upstream server it accessed in attempting to fulfill
       * the request.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.5.3">HTTP
       *      RFC - 10.5.3 502 Bad Gateway</a>
       */
      static const Status SERVER_ERROR_BAD_GATEWAY;

      /**
       * The server, while acting as a gateway or proxy, could not connect to the
       * upstream server.
       * 
       * @see <a
       *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.5.5">HTTP
       *      RFC - 10.5.5 504 Gateway Timeout</a>
       */
      static const Status SERVER_ERROR_GATEWAY_TIMEOUT;

      /**
       * This status code means the method could not be performed on the resource
       * because the server is unable to store the representation needed to
       * successfully complete the request.
       * 
       * @see <a href="http://www.webdav.org/specs/rfc2518.html#STATUS_507">WEBDAV
       *      RFC - 10.6 507 Insufficient Storage</a>
       */
      static const Status SERVER_ERROR_INSUFFICIENT_STORAGE;
      507);

    /**
     * The server encountered an unexpected condition which prevented it from
     * fulfilling the request.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.5.1">HTTP
     *      RFC - 10.5.1 500 Internal Server Error</a>
     */
    static const Status SERVER_ERROR_INTERNAL;

    /**
     * The server does not support the functionality required to fulfill the
     * request.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.5.2">HTTP
     *      RFC - 10.5.2 501 Not Implemented</a>
     */
    static const Status SERVER_ERROR_NOT_IMPLEMENTED;

    /**
     * The server is currently unable to handle the request due to a temporary
     * overloading or maintenance of the server.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.5.4">HTTP
     *      RFC - 10.5.4 503 Service Unavailable</a>
     */
    static const Status SERVER_ERROR_SERVICE_UNAVAILABLE;

    /**
     * The server does not support, or refuses to support, the HTTP protocol
     * version that was used in the request message.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.5.6">HTTP
     *      RFC - 10.5.6 505 HTTP Version Not Supported</a>
     */
    static const Status SERVER_ERROR_VERSION_NOT_SUPPORTED;

    /**
     * The request has been accepted for processing, but the processing has not
     * been completed.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.3">HTTP
     *      RFC - 10.2.3 202 Accepted</a>
     */
    static const Status SUCCESS_ACCEPTED;

    /**
     * The request has been fulfilled and resulted in a new resource being
     * created.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.2">HTTP
     *      RFC - 10.2.2 201 Created</a>
     */
    static const Status SUCCESS_CREATED;

    /**
     * This response is used to inform the client that the HTTP response entity
     * contains a set of status codes generated during the method invocation.
     * 
     * @see <a href="http://www.webdav.org/specs/rfc2518.html#STATUS_207">WEBDAV
     *      RFC - 10.2 207 Multi-Status</a>
     */
    static const Status SUCCESS_MULTI_STATUS;

    /**
     * The server has fulfilled the request but does not need to return an
     * entity-body (for example after a DELETE), and might want to return
     * updated metainformation.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.5">HTTP
     *      RFC - 10.2.5 204 No Content</a>
     */
    static const Status SUCCESS_NO_CONTENT;

    /**
     * The request has succeeded but the returned metainformation in the
     * entity-header do not come from the origin server, but is gathered from a
     * local or a third-party copy.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.4">HTTP
     *      RFC - 10.2.4 203 Non-Authoritative Information</a>
     */
    static const Status SUCCESS_NON_AUTHORITATIVE;

    /**
     * The request has succeeded.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.1">HTTP
     *      RFC - 10.2.1 200 OK</a>
     */
    static const Status SUCCESS_OK;

    /**
     * Warning status code, typically returned by a cache or a proxy, indicating
     * that the response has been transformed.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
     *      RFC - 14.46 Warning</a>
     */
    static const Status SUCCESS_TRANSFORMATION_APPLIED;

    /**
     * Warning status code, optionally including arbitrary information to be
     * presented to a human user, typically returned by a cache.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.46">HTTP
     *      RFC - 14.46 Warning</a>
     */
    static const Status SUCCESS_MISC_PERSISTENT_WARNING;

    /**
     * The server has fulfilled the partial GET request for the resource
     * assuming the request has included a Range header field indicating the
     * desired range.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.7">HTTP
     *      RFC - 10.2.7 206 Partial Content</a>
     */
    static const Status SUCCESS_PARTIAL_CONTENT;

    /**
     * The server has fulfilled the request and the user agent SHOULD reset the
     * document view which caused the request to be sent.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10.2.6">HTTP
     *      RFC - 10.2.6 205 Reset Content</a>
     */
    static const Status SUCCESS_RESET_CONTENT;

    /**
     * Check if the provided description of the status contains forbidden
     * characters such as CR and LF. an IllegalArgumentException is thrown in
     * this case.
     * 
     * @see <a
     *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6.1.1">Status
     *      Code and Reason Phrase</a>
     * @param description
     *            the description to check
     * @return the description if it is correct.
     */

    /**
     * Indicates if the status is a client error status, meaning "The request
     * contains bad syntax or cannot be fulfilled".
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is a client error status.
     */
    static bool isClientError(int code) {
      return (code >= 400) && (code <= 499);
    }

    /**
     * Indicates if the status is a connector error status, meaning "The
     * connector failed to send or receive an apparently valid message".
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is a server error status.
     */
    static bool isConnectorError(int code) {
      return (code >= 1000) && (code <= 1099);
    }

    /**
     * Indicates if the status is an error (client or server) status.
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is an error (client or server) status.
     */
    static bool isError(int code);

    /**
     * Indicates if the status is an information status, meaning "request
     * received, continuing process".
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is an information status.
     */
    static bool isInformational(int code) {
      return (code >= 100) && (code <= 199);
    }

    /**
     * Indicates if the status is a redirection status, meaning "Further action
     * must be taken in order to complete the request".
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is a redirection status.
     */
    static bool isRedirection(int code) {
      return (code >= 300) && (code <= 399);
    }

    /**
     * Indicates if the status is a server error status, meaning "The server
     * failed to fulfill an apparently valid request".
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is a server error status.
     */
    static bool isServerError(int code) {
      return (code >= 500) && (code <= 599);
    }

    /**
     * Indicates if the status is a success status, meaning "The action was
     * successfully received, understood, and accepted".
     * 
     * @param code
     *            The code of the status.
     * @return True if the status is a success status.
     */
    static bool isSuccess(int code) {
      return (code >= 200) && (code <= 299);
    }

    /**
     * Returns the status associated to a code. If an existing constant exists
     * then it is returned, otherwise a new instance is created.
     * 
     * @param code
     *            The code.
     * @return The associated status.
     */
    static Status valueOf(int code);


    /**
     * Constructor.
     * 
     * @param code
     *            The specification code.
     */
    Status(int code) {
      Status(code, NULL, NULL, NULL);
    }

    /**
     * Constructor.
     * 
     * @param code
     *            The specification code.
     * @param name
     *            The name.
     * @param description
     *            The description.
     * @param uri
     *            The URI of the specification describing the method.
     */
    Status(int code, const std::string name, const std::string description,
           const std::string uri) {
      Status(code, NULL, name, description, uri);
    }

    /**
     * Constructor.
     * 
     * @param code
     *            The specification code.
     * @param throwable
     *            The related error or exception.
     */
    Status(int code, Throwable throwable) {
      Status(code, throwable, NULL, NULL, NULL);
    }

    /**
     * Constructor.
     * 
     * @param code
     *            The specification code.
     * @param throwable
     *            The related error or exception.
     * @param name
     *            The name.
     * @param description
     *            The description.
     * @param uri
     *            The URI of the specification describing the method.
     */
    Status(int code, Throwable throwable, const std::string name,
           const std::string description, const std::string uri);

    /**
     * Constructor.
     * 
     * @param status
     *            The status to copy.
     * @param description
     *            The description to associate.
     */
    Status(const Status status, const std::string description);

    /**
     * Constructor.
     * 
     * @param status
     *            The status to copy.
     * @param throwable
     *            The related error or exception.
     */
    Status(const Status status, const Throwable throwable);
    /**
     * Constructor.
     * 
     * @param status
     *            The status to copy.
     * @param throwable
     *            The related error or exception.
     * @param description
     *            The description to associate.
     */
    Status(const Status status, const Throwable throwable,
           const std::string description);

    /**
     * Indicates if the status is equal to a given one.
     * 
     * @param object
     *            The object to compare to.
     * @return True if the status is equal to a given one.
     */
    //@Override
    bool equals(const Object object);

    /**
     * Returns the corresponding code (HTTP or WebDAV or custom code).
     * 
     * @return The corresponding code.
     */
    int getCode() {
      return code;
    }

    /**
     * Returns the description.
     * 
     * @return The description.
     */
    std::string getDescription();
    /**
     * Returns the name of this status.
     * 
     * @return The name of this status.
     */
    std::string getName();

    /**
     * Returns the related error or exception.
     * 
     * @return The related error or exception.
     */
    Throwable getThrowable() {
      return throwable;
    }

    /**
     * Returns the URI of the specification describing the status.
     * 
     * @return The URI of the specification describing the status.
     */
    std::string getUri();

    /** {@inheritDoc} */
    //@Override
    int hashCode();

    /**
     * Indicates if the status is a client error status, meaning "The request
     * contains bad syntax or cannot be fulfilled".
     * 
     * @return True if the status is a client error status.
     */
    bool isClientError();

    /**
     * Indicates if the status is a connector error status, meaning "The
     * connector failed to send or receive an apparently valid message".
     * 
     * @return True if the status is a connector error status.
     */
    bool isConnectorError();

    /**
     * Indicates if the status is an error (client or server) status.
     * 
     * @return True if the status is an error (client or server) status.
     */
    bool isError();

    /**
     * Indicates if the status is an information status, meaning "request
     * received, continuing process".
     * 
     * @return True if the status is an information status.
     */
    bool isInformational();

    /**
     * Indicates if an error is recoverable, meaning that simply retrying after
     * a delay could result in a success. Tests {@link #isConnectorError()} and
     * if the status is {@link #CLIENT_ERROR_REQUEST_TIMEOUT} or
     * {@link #SERVER_ERROR_GATEWAY_TIMEOUT} or
     * {@link #SERVER_ERROR_SERVICE_UNAVAILABLE}.
     * 
     * @return True if the error is recoverable.
     */
    bool isRecoverableError();

    /**
     * Indicates if the status is a redirection status, meaning "Further action
     * must be taken in order to complete the request".
     * 
     * @return True if the status is a redirection status.
     */
    bool isRedirection();

    /**
     * Indicates if the status is a server error status, meaning "The server
     * failed to fulfill an apparently valid request".
     * 
     * @return True if the status is a server error status.
     */
    bool isServerError();

    /**
     * Indicates if the status is a success status, meaning "The action was
     * successfully received, understood, and accepted".
     * 
     * @return True if the status is a success status.
     */
    bool isSuccess();

    /**
     * Returns the name of the status followed by its HTTP code.
     * 
     * @return The name of the status followed by its HTTP code.
     */
    //@Override
    std::string toString();

 private:

    static std::string checkDescription(std::string description);

    static const std::string BASE_HTTP;

    static const std::string BASE_RESTLET;

    static const std::string BASE_WEBDAV;

    /** The specification code. */
    const int code;

    /** The description. */
    const std::string description;

    /** The name. */
    volatile std::string name;

    /** The related error or exception. */
    const Throwable throwable;

    /** The URI of the specification describing the method. */
    const std::string uri;

  };


} // namespace data
} // namespace echo

#endif // _ECHO_DATA_STATUS_H_
