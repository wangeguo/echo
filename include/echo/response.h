#ifndef _ECHO_RESPONSE_H_
#define _ECHO_RESPONSE_H_

/*
  import java.util.Date;
  import java.util.List;
  import java.util.Set;
  import java.util.concurrent.CopyOnWriteArrayList;
  import java.util.concurrent.CopyOnWriteArraySet;

  import org.restlet.data.AuthenticationInfo;
  import org.restlet.data.ChallengeRequest;
  import org.restlet.data.CookieSetting;
  import org.restlet.data.Dimension;
  import org.restlet.data.Method;
  import org.restlet.data.Reference;
  import org.restlet.data.ServerInfo;

  import org.restlet.engine.util.CookieSettingSeries;
  import org.restlet.util.Series;
*/

#include <list>
#include <set>

#include <echo/message.h>
#include <echo/data/status.h>

namespace echo {

  /**
   * Generic response sent by server connectors. It is then received by client
   * connectors. Responses are uniform across all types of connectors, protocols
   * and components.
   * 
   * @see echo::Request
   * @see echo::Uniform
   * @author Jerome Louvel Eguo Wang
   */
class Response : public echo::Message {

 public:
    /**
     * Returns the response associated to the current thread.
     * 
     * Warning: this method should only be used under duress. You should by
     * default prefer obtaining the current context using methods such as
     * {@link org.restlet.resource.Resource#getResponse()}.
     * 
     * This variable is stored internally as a thread local variable and updated
     * each time a call is handled by a Restlet via the
     * {@link Restlet#handle(org.restlet.Request, org.restlet.Response)} method.
     * 
     * @return The current context.
     */
    static Response getCurrent() {
      return CURRENT.get();
    }

    /**
     * Sets the response associated with the current thread.
     * 
     * @param response
     *            The thread's response.
     */
    static void setCurrent(Response response) {
      CURRENT.set(response);
    }


    /**
     * Constructor.
     * 
     * @param request
     *            The request associated to this response.
     */
    Response(Request request);

    /**
     * Returns the estimated amount of time since a response was generated or
     * revalidated by the origin server. Origin servers should leave the 0
     * default value. Only caches are expected to set this property.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the "Age"
     * header.
     * 
     * @return The response age.
     */
    int getAge() {
      return age;
    }

    /**
     * Returns the modifiable set of methods allowed on the requested resource.
     * This property only has to be updated when a status
     * CLIENT_ERROR_METHOD_NOT_ALLOWED is set. Creates a new instance if no one
     * has been set.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Allow" header.
     * 
     * @return The set of allowed methods.
     */
    Set<Method> getAllowedMethods();

    /**
     * Returns information sent by an origin server related to an successful
     * authentication attempt. If none is available, null is returned.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Authentication-Info" header.
     * 
     * @return The authentication information provided by the server.
     */
    AuthenticationInfo getAuthenticationInfo() {
      return this->authenticationInfo;
    }

    /**
     * Returns the list of authentication requests sent by an origin server to a
     * client. If none is available, an empty list is returned.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "WWW-Authenticate" header.
     * 
     * @return The list of authentication requests.
     */
    List<ChallengeRequest> getChallengeRequests();

    /**
     * Returns the modifiable series of cookie settings provided by the server.
     * Creates a new instance if no one has been set.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Set-Cookie" and "Set-Cookie2" headers.
     * 
     * @return The cookie settings provided by the server.
     */
    Series<CookieSetting> getCookieSettings();

    /**
     * Returns the modifiable set of selecting dimensions on which the response
     * entity may vary. If some server-side content negotiation is done, this
     * set should be properly updated, other it can be left empty. Creates a new
     * instance if no one has been set.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Vary" header.
     * 
     * @return The set of dimensions on which the response entity may vary.
     */
    Set<Dimension> getDimensions();

    /**
     * Returns the location reference. This is the reference that the client
     * should follow for redirections or resource creations.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Location" header.
     * 
     * @return The redirection reference.
     */
    Reference getLocationRef() {
      return this->locationRef;
    }

    /**
     * Returns the callback invoked on response reception. If the value is not
     * null, then the associated request will be executed asynchronously.
     * 
     * @return The callback invoked on response reception.
     */
    Uniform getOnReceived() {
      return onReceived;
    }

    /**
     * Returns the list of authentication requests sent by an origin server to a
     * client. If none is available, an empty list is returned.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Proxy-Authenticate" header.
     * 
     * @return The list of authentication requests.
     */
    List<ChallengeRequest> getProxyChallengeRequests();

    /**
     * Returns the associated request
     * 
     * @return The associated request
     */
    Request getRequest() {
      return this->request;
    }

    /**
     * Indicates how long the service is expected to be unavailable to the
     * requesting client. Default value is null.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Retry-After" header.
     * 
     * @return Date after with a retry attempt could occur.
     */
    Date getRetryAfter() {
      return retryAfter;
    }

    /**
     * Returns the server-specific information. Creates a new instance if no one
     * has been set.
     * 
     * @return The server-specific information.
     */
    ServerInfo getServerInfo();

    /**
     * Returns the status.
     * 
     * @return The status.
     */
    echo::data::Status getStatus() {
      return this->status;
    }

    //@Override
    boolean isConfidential();

    /**
     * Permanently redirects the client to a target URI. The client is expected
     * to reuse the same method for the new request.
     * 
     * @param targetRef
     *            The target URI reference.
     */
    void redirectPermanent(Reference targetRef);

    /**
     * Permanently redirects the client to a target URI. The client is expected
     * to reuse the same method for the new request.<br>
     * <br>
     * If you pass a relative target URI, it will be resolved with the current
     * base reference of the request's resource reference (see
     * {@link Request#getResourceRef()} and {@link Reference#getBaseRef()}.
     * 
     * @param targetUri
     *            The target URI.
     */
    void redirectPermanent(String targetUri);

    /**
     * Redirects the client to a different URI that SHOULD be retrieved using a
     * GET method on that resource. This method exists primarily to allow the
     * output of a POST-activated script to redirect the user agent to a
     * selected resource. The new URI is not a substitute reference for the
     * originally requested resource.
     * 
     * @param targetRef
     *            The target reference.
     */
    void redirectSeeOther(Reference targetRef);

    /**
     * Redirects the client to a different URI that SHOULD be retrieved using a
     * GET method on that resource. This method exists primarily to allow the
     * output of a POST-activated script to redirect the user agent to a
     * selected resource. The new URI is not a substitute reference for the
     * originally requested resource.<br>
     * <br>
     * If you pass a relative target URI, it will be resolved with the current
     * base reference of the request's resource reference (see
     * {@link Request#getResourceRef()} and {@link Reference#getBaseRef()}.
     * 
     * @param targetUri
     *            The target URI.
     */
    void redirectSeeOther(String targetUri);
    /**
     * Temporarily redirects the client to a target URI. The client is expected
     * to reuse the same method for the new request.
     * 
     * @param targetRef
     *            The target reference.
     */
    void redirectTemporary(Reference targetRef);

    /**
     * Temporarily redirects the client to a target URI. The client is expected
     * to reuse the same method for the new request.<br>
     * <br>
     * If you pass a relative target URI, it will be resolved with the current
     * base reference of the request's resource reference (see
     * {@link Request#getResourceRef()} and {@link Reference#getBaseRef()}.
     * 
     * @param targetUri
     *            The target URI.
     */
    void redirectTemporary(String targetUri);

    /**
     * Sets the estimated amount of time since a response was generated or
     * revalidated by the origin server. Origin servers should leave the 0
     * default value. Only caches are expected to set this property.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the "Age"
     * header.
     * 
     * @param age
     *            The response age.
     */
    void setAge(int age) {
      this->age = age;
    }

    /**
     * Sets the set of methods allowed on the requested resource. The set
     * instance set must be thread-safe (use {@link CopyOnWriteArraySet} for
     * example.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Allow" header.
     * 
     * @param allowedMethods
     *            The set of methods allowed on the requested resource.
     */
    void setAllowedMethods(Set<Method> allowedMethods) {
      this->allowedMethods = allowedMethods;
    }

    /**
     * Sets the authentication information sent by an origin server to a client
     * after a successful authentication attempt.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Authentication-Info" header.
     * 
     * @param authenticationInfo
     *            The data returned by the server in response to successful
     *            authentication.
     */
    void setAuthenticationInfo(AuthenticationInfo authenticationInfo) {
      this->authenticationInfo = authenticationInfo;
    }

    /**
     * Sets the authentication request sent by an origin server to a client.
     * 
     * @param request
     *            The authentication request sent by an origin server to a
     *            client.
     * @deprecated Add request to {@link #getChallengeRequests()} method result
     *             instead or use {@link #setChallengeRequests(List)}.
     */
    //@Deprecated
    void setChallengeRequest(ChallengeRequest request);

    /**
     * Sets the list of authentication requests sent by an origin server to a
     * client. The list instance set must be thread-safe (use
     * {@link CopyOnWriteArrayList} for example.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "WWW-Authenticate" header.
     * 
     * @param requests
     *            The list of authentication requests sent by an origin server
     *            to a client.
     */
    void setChallengeRequests(List<ChallengeRequest> requests);

    /**
     * Sets the cookie settings provided by the server. Note that when used with
     * HTTP connectors, this property maps to the "Set-Cookie" and "Set-Cookie2"
     * headers.
     * 
     * @param cookieSettings
     *            The cookie settings provided by the server.
     */
    void setCookieSettings(Series<CookieSetting> cookieSettings) {
      this->cookieSettings = cookieSettings;
    }

    /**
     * Sets the set of dimensions on which the response entity may vary. The set
     * instance set must be thread-safe (use {@link CopyOnWriteArraySet} for
     * example.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Vary" header.
     * 
     * @param dimensions
     *            The set of dimensions on which the response entity may vary.
     */
    void setDimensions(Set<Dimension> dimensions) {
      this->dimensions = dimensions;
    }

    /**
     * Sets the reference that the client should follow for redirections or
     * resource creations. Note that when used with HTTP connectors, this
     * property maps to the "Location" header.
     * 
     * @param locationRef
     *            The reference to set.
     */
    void setLocationRef(Reference locationRef) {
      this->locationRef = locationRef;
    }

    /**
     * Sets the reference that the client should follow for redirections or
     * resource creations. If you pass a relative location URI, it will be
     * resolved with the current base reference of the request's resource
     * reference (see {@link Request#getResourceRef()} and
     * {@link Reference#getBaseRef()}.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Location" header.
     * 
     * @param locationUri
     *            The URI to set.
     * @see #setLocationRef(Reference)
     */
    void setLocationRef(String locationUri);

    /**
     * Sets the callback invoked on response reception. If the value is not
     * null, then the associated request will be executed asynchronously.
     * 
     * @param onReceivedCallback
     *            The callback invoked on response reception.
     */
    void setOnReceived(Uniform onReceivedCallback) {
      this->onReceived = onReceivedCallback;
    }

    /**
     * Sets the list of authentication requests sent by a proxy to a client. The
     * list instance set must be thread-safe (use {@link CopyOnWriteArrayList}
     * for example.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Proxy-Authenticate" header.
     * 
     * @param requests
     *            The list of authentication requests sent by a proxy to a
     *            client.
     */
    void setProxyChallengeRequests(List<ChallengeRequest> requests) {
      this->proxyChallengeRequests = requests;
    }

    /**
     * Sets the associated request.
     * 
     * @param request
     *            The associated request
     */
    void setRequest(Request request) {
      this->request = request;
    }

    /**
     * Indicates how long the service is expected to be unavailable to the
     * requesting client. Default value is null.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Retry-After" header.
     * 
     * @param retryAfter
     *            Date after with a retry attempt could occur.
     */
    void setRetryAfter(Date retryAfter) {
      this->retryAfter = retryAfter;
    }

    /**
     * Sets the server-specific information.
     * 
     * @param serverInfo
     *            The server-specific information.
     */
    void setServerInfo(ServerInfo serverInfo) {
      this->serverInfo = serverInfo;
    }

    /**
     * Sets the status.
     * 
     * @param status
     *            The status to set.
     */
    void setStatus(echo::data::Status status) {
      this->status = status;
    }

    /**
     * Sets the status.
     * 
     * @param status
     *            The status to set.
     * @param message
     *            The status message.
     */
    void setStatus(echo::data::Status status, String message);

    /**
     * Sets the status.
     * 
     * @param status
     *            The status to set.
     * @param throwable
     *            The related error or exception.
     */
    void setStatus(echo::data::Status status, Throwable throwable);

    /**
     * Sets the status.
     * 
     * @param status
     *            The status to set.
     * @param throwable
     *            The related error or exception.
     * @param message
     *            The status message.
     */
    void setStatus(echo::data::Status status, Throwable throwable, String message);


 private:
    static final ThreadLocal<Response> CURRENT = new ThreadLocal<Response>();
    /**
     * Estimated amount of time since a response was generated or revalidated by
     * the origin server.
     */
    volatile int age;

    /** The set of methods allowed on the requested resource. */
    volatile Set<Method> allowedMethods;

    /** The authentication requests sent by an origin server to a client. */
    volatile List<ChallengeRequest> challengeRequests;

    /** The authentication requests sent by a proxy to a client. */
    volatile List<ChallengeRequest> proxyChallengeRequests;

    /** The cookie settings provided by the server. */
    volatile Series<CookieSetting> cookieSettings;

    /** The set of dimensions on which the response entity may vary. */
    volatile Set<Dimension> dimensions;

    /** The reference used for redirections or creations. */
    volatile Reference locationRef;

    /** The associated request. */
    volatile Request request;

    /** The server-specific information. */
    volatile ServerInfo serverInfo;

    /** The status. */
    volatile echo::data::Status status;

    /**
     * The authentication information sent by an origin server to a client in
     * the case of a successful authentication attempt.
     */
    volatile AuthenticationInfo authenticationInfo;

    /** Callback invoked on response reception. */
    volatile Uniform onReceived;

    /**
     * Indicates how long the service is expected to be unavailable to the
     * requesting client.
     */
    volatile Date retryAfter;

  };

} // namespace echo

#endif // _ECHO_RESPONSE_H_
