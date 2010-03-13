#ifndef _ECHO_REQUEST_H_
#define _ECHO_REQUEST_H_

#include <list>

#include <echo/message.h>
#include <echo/data/challenge-response.h>
#include <echo/data/client-info.h>
#include <echo/data/conditions.h>
#include <echo/data/cookie.h>
#include <echo/data/method.h>
#include <echo/data/protocol.h>
#include <echo/data/range.h>
#include <echo/data/reference.h>
#include <echo/engine/util/cookie-series.h>
#include <echo/representation/representation.h>
#include <echo/util/series.h>

/*
  import java.util.concurrent.CopyOnWriteArrayList;
*/

namespace echo {

  /**
   * Generic request sent by client connectors. It is then received by server
   * connectors and processed by Echos. This request can also be processed by a
   * chain of Echos, on both client and server sides. Requests are uniform
   * across all types of connectors, protocols and components.
   * 
   * @see echo::Response
   * @see echo::Uniform
   * @author Eguo Wang
   */
  class Request : public echo::Message {

  public:
    /**
     * Returns the request associated to the current thread. This is reusing the
     * {@link Response#getCurrent()} method.
     * 
     * Warning: this method should only be used under duress. You should by
     * default prefer obtaining the current context using methods such as
     * {@link echo::resource::Resource#getRequest()}.
     * 
     * @return The thread's request.
     */

    static Request getCurrent();

    /**
     * Constructor.
     * 
     * @param method
     *            The call's method.
     * @param resourceRef
     *            The resource reference.
     */
    Request(Method method, Reference resourceRef) {
	  Request(method, resourceRef, null);
    }

    /**
     * Constructor.
     * 
     * @param method
     *            The call's method.
     * @param resourceRef
     *            The resource reference.
     * @param entity
     *            The entity.
     */
    Request(Method method, Reference resourceRef, Representation entity);

    /**
     * Constructor.
     * 
     * @param method
     *            The call's method.
     * @param resourceUri
     *            The resource URI.
     */
    Request(Method method, String resourceUri);

    /**
     * Constructor.
     * 
     * @param method
     *            The call's method.
     * @param resourceUri
     *            The resource URI.
     * @param entity
     *            The entity.
     */
    Request(Method method, String resourceUri, Representation entity);

    /**
     * Returns the authentication response sent by a client to an origin server.
     * Note that when used with HTTP connectors, this property maps to the
     * "Authorization" header.
     * 
     * @return The authentication response sent by a client to an origin server.
     */
    ChallengeResponse getChallengeResponse() {
	  return challengeResponse;
    }

    /**
     * Returns the client-specific information. Creates a new instance if no one
     * has been set.
     * 
     * @return The client-specific information.
     */
    ClientInfo getClientInfo();

    /**
     * Returns the modifiable conditions applying to this request. Creates a new
     * instance if no one has been set.
     * 
     * @return The conditions applying to this call.
     */
    Conditions getConditions();

    /**
     * Returns the modifiable series of cookies provided by the client. Creates
     * a new instance if no one has been set.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Cookie" header.
     * 
     * @return The cookies provided by the client.
     */
    Series<Cookie> getCookies();

    /**
     * Returns the host reference. This may be different from the resourceRef's
     * host, for example for URNs and other URIs that don't contain host
     * information.<br>
     * <br>
     * Note that when used with HTTP connectors, this property maps to the
     * "Host" header.
     * 
     * @return The host reference.
     */
    Reference getHostRef() {
	  return hostRef;
    }

    /**
     * Returns the method.
     * 
     * @return The method.
     */
    Method getMethod() {
	  return method;
    }

    /**
     * Returns the original reference as requested by the client. Note that this
     * property is not used during request routing. See the
     * {@link #getResourceRef()} method for details.
     * 
     * @return The original reference.
     * @see #getResourceRef()
     */
    Reference getOriginalRef() {
	  return originalRef;
    }

    /**
     * Returns the protocol by first returning the resourceRef.schemeProtocol
     * property if it is set, or the baseRef.schemeProtocol property otherwise.
     * 
     * @return The protocol or null if not available.
     */
    Protocol getProtocol();

    /**
     * Returns the authentication response sent by a client to a proxy. Note
     * that when used with HTTP connectors, this property maps to the
     * "Proxy-Authorization" header.
     * 
     * @return The authentication response sent by a client to a proxy.
     */
    ChallengeResponse getProxyChallengeResponse() {
	  return proxyChallengeResponse;
    }

    /**
     * Returns the ranges to return from the target resource's representation.
     * Note that when used with HTTP connectors, this property maps to the
     * "Range" header.
     * 
     * @return The ranges to return.
     */
    std::list<Range> getRanges();

    /**
     * Returns the referrer reference if available. Note that when used with
     * HTTP connectors, this property maps to the "Referer" header.
     * 
     * @return The referrer reference.
     */
    Reference getReferrerRef() {
	  return referrerRef;
    }

    /**
     * Returns the reference of the target resource. This reference is
     * especially important during routing, dispatching and resource finding.
     * During such processing, its base reference is constantly updated to
     * reflect the reference of the parent Restlet or resource and the remaining
     * part of the URI that must be routed or analyzed.
     * 
     * If you need to get the URI reference originally requested by the client,
     * then you should use the {@link #getOriginalRef()} method instead. Also,
     * note that beside the update of its base property, the resource reference
     * can be modified during the request processing.
     * 
     * For example, the {@link org.restlet.service.TunnelService} associated to
     * an application can extract some special extensions or query parameters
     * and replace them by semantically equivalent properties on the request
     * object. Therefore, the resource reference can become different from the
     * original reference.
     * 
     * Finally, when sending out requests via a dispatcher such as
     * {@link Context#getClientDispatcher()} or
     * {@link Context#getServerDispatcher()}, if the reference contains URI
     * template variables, those variables are automatically resolved using the
     * request's attributes.
     * 
     * @return The reference of the target resource.
     * @see #getOriginalRef()
     * @see #getHostRef()
     */
    Reference getResourceRef() {
	  return resourceRef;
    }

    /**
     * Returns the application root reference.
     * 
     * @return The application root reference.
     */
    Reference getRootRef() {
	  return rootRef;
    }

    /**
     * Implemented based on the {@link Protocol#isConfidential()} method for the
     * request's protocol returned by {@link #getProtocol()};
     */
    // TODO: @Override
	  bool isConfidential();

    /**
     * Indicates if a content is available and can be sent. Several conditions
     * must be met: the method must allow the sending of content, the content
     * must exists and have some available data.
     * 
     * @return True if a content is available and can be sent.
     */
    //TODO: @Override
	  bool isEntityAvailable();

    /**
     * Sets the authentication response sent by a client to an origin server.
     * Note that when used with HTTP connectors, this property maps to the
     * "Authorization" header.
     * 
     * @param challengeResponse
     *            The authentication response sent by a client to an origin
     *            server.
     */
    void setChallengeResponse(ChallengeResponse challengeResponse);

    /**
     * Sets the client-specific information.
     * 
     * @param clientInfo
     *            The client-specific information.
     */
    void setClientInfo(ClientInfo clientInfo);

    /**
     * Sets the conditions applying to this request.
     * 
     * @param conditions
     *            The conditions applying to this request.
     */
    void setConditions(Conditions conditions);

    /**
     * Sets the cookies provided by the client. Note that when used with HTTP
     * connectors, this property maps to the "Cookie" header.
     * 
     * @param cookies
     *            The cookies provided by the client.
     */
    void setCookies(Series<Cookie> cookies);

    /**
     * Sets the host reference. Note that when used with HTTP connectors, this
     * property maps to the "Host" header.
     * 
     * @param hostRef
     *            The host reference.
     */
    void setHostRef(Reference hostRef);

    /**
     * Sets the host reference using an URI string. Note that when used with
     * HTTP connectors, this property maps to the "Host" header.
     * 
     * @param hostUri
     *            The host URI.
     */
    void setHostRef(std::string hostUri);

    /**
     * Sets the method called.
     * 
     * @param method
     *            The method called.
     */
    void setMethod(Method method);

    /**
     * Sets the original reference requested by the client.
     * 
     * @param originalRef
     *            The original reference.
     * @see #getOriginalRef()
     */
    void setOriginalRef(Reference originalRef);

    /**
     * Sets the authentication response sent by a client to a proxy. Note that
     * when used with HTTP connectors, this property maps to the
     * "Proxy-Authorization" header.
     * 
     * @param challengeResponse
     *            The authentication response sent by a client to a proxy.
     */
    void setProxyChallengeResponse(ChallengeResponse challengeResponse);

    /**
     * Sets the ranges to return from the target resource's representation. Note
     * that when used with HTTP connectors, this property maps to the "Range"
     * header.
     * 
     * @param ranges
     *            The ranges.
     */
    void setRanges(std::list<Range> ranges);

    /**
     * Sets the referrer reference if available. Note that when used with HTTP
     * connectors, this property maps to the "Referer" header.
     * 
     * @param referrerRef
     *            The referrer reference.
     */
    void setReferrerRef(Reference referrerRef);

    /**
     * Sets the referrer reference if available using an URI string. Note that
     * when used with HTTP connectors, this property maps to the "Referer"
     * header.
     * 
     * @param referrerUri
     *            The referrer URI.
     * @see #setReferrerRef(Reference)
     */
    void setReferrerRef(std::string referrerUri);

    /**
     * Sets the target resource reference. If the reference is relative, it will
     * be resolved as an absolute reference. Also, the context's base reference
     * will be reset. Finally, the reference will be normalized to ensure a
     * consistent handling of the call.
     * 
     * @param resourceRef
     *            The resource reference.
     * @see #getResourceRef()
     */
    void setResourceRef(Reference resourceRef);

    /**
     * Sets the target resource reference using an URI string. Note that the URI
     * can be either absolute or relative to the context's base reference.
     * 
     * @param resourceUri
     *            The resource URI.
     * @see #setResourceRef(Reference)
     */
    void setResourceRef(std::string resourceUri);
    /**
     * Sets the application root reference.
     * 
     * @param rootRef
     *            The application root reference.
     */
    void setRootRef(Reference rootRef);

  private:
    /** The authentication response sent by a client to an origin server. */
    volatile ChallengeResponse challengeResponse;

    /** The authentication response sent by a client to a proxy. */
    volatile ChallengeResponse proxyChallengeResponse;

    /** The client-specific information. */
    volatile ClientInfo clientInfo;

    /** The condition data. */
    volatile Conditions conditions;

    /** The cookies provided by the client. */
    volatile Series<Cookie> cookies;

    /** The host reference. */
    volatile Reference hostRef;

    /** The method. */
    volatile Method method;

    /** The original reference. */
    volatile Reference originalRef;

    /** The ranges to return from the target resource's representation. */
    volatile std::list<Range> ranges;

    /** The referrer reference. */
    volatile Reference referrerRef;

    /** The resource reference. */
    volatile Reference resourceRef;

    /** The application root reference. */
    volatile Reference rootRef;

  };

} // namespace echo

#endif // _ECHO_REQUEST_H_
