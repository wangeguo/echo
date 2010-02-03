#ifndef _ECHO_DATA_CACHE_DIRECTIVE_H_
#define _ECHO_DATA_CACHE_DIRECTIVE_H_

#include <string>
#include <list>

#include <echo/engine/http/http-constants.h>

namespace echo {
namespace data {


/**
 * Directive for caching mechanisms along the call chain. This overrides the
 * default behavior of those caches and proxies.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the
 * "Cache-Control" header.
 * 
 * @author Jerome Louvel
 */
//public final class CacheDirective extends Parameter {
class CacheDirective : public Parameter {

 public:
  
  /**
   * Creates a "max-age" directive. Indicates that the client is willing to
   * accept a response whose age is no greater than the specified time in
   * seconds. Unless "max-stale" directive is also included, the client is not
   * willing to accept a stale response.<br>
   * <br>
   * Note that this directive can be used on requests or responses.
   * 
   * @param maxAge
   *            Maximum age in seconds.
   * @return A new "max-age" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.3">HTTP
   *      1.1 - Modifications of the Basic Expiration Mechanism</a>
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.4">HTTP
   *      1.1 - Cache Revalidation and Reload Controls</a>
   */
  static CacheDirective maxAge(int maxAge);

  /**
   * Creates a "max-stale" directive. Indicates that the client is willing to
   * accept a response that has exceeded its expiration time by any amount of
   * time.<br>
   * <br>
   * Note that this directive can be used on requests only.
   * 
   * @return A new "max-stale" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.3">HTTP
   *      1.1 - Modifications of the Basic Expiration Mechanism</a>
   */
  static CacheDirective maxStale();

  /**
   * Creates a "max-stale" directive. Indicates that the client is willing to
   * accept a response that has exceeded its expiration time by a given amount
   * of time.<br>
   * <br>
   * Note that this directive can be used on requests only.
   * 
   * @param maxStale
   *            Maximum stale age in seconds.
   * @return A new "max-stale" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.3">HTTP
   *      1.1 - Modifications of the Basic Expiration Mechanism</a>
   */
  static CacheDirective maxStale(int maxStale);

  /**
   * Creates a "min-fresh" directive. Indicates that the client is willing to
   * accept a response whose freshness lifetime is no less than its current
   * age plus the specified time in seconds. That is, the client wants a
   * response that will still be fresh for at least the specified number of
   * seconds.<br>
   * <br>
   * Note that this directive can be used on requests only.
   * 
   * @param minFresh
   *            Minimum freshness lifetime in seconds.
   * @return A new "min-fresh" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.3">HTTP
   *      1.1 - Modifications of the Basic Expiration Mechanism</a>
   */
  static CacheDirective minFresh(int minFresh);

  /**
   * Creates a "must-revalidate" directive. Indicates that the origin server
   * requires revalidation of a cache entry on any subsequent use.<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @return A new "must-revalidate" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.4">HTTP
   *      1.1 - Cache Revalidation and Reload Controls</a>
   */
  static CacheDirective mustRevalidate();

  /**
   * Creates a "no-cache" directive. Indicates that a cache must not use the
   * response to satisfy subsequent requests without successful revalidation
   * with the origin server.<br>
   * <br>
   * Note that this directive can be used on requests or responses.
   * 
   * @return A new "no-cache" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective noCache();

  /**
   * Creates a "no-cache" directive. Indicates that a cache must not use the
   * response to satisfy subsequent requests without successful revalidation
   * with the origin server.<br>
   * <br>
   * Note that this directive can be used on requests or responses.
   * 
   * @param fieldNames
   *            Field names, typically a HTTP header name, that must not be
   *            sent by caches.
   * @return A new "no-cache" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective noCache(std::list<std::string> fieldNames);

  /**
   * Creates a "no-cache" directive. Indicates that a cache must not use the
   * response to satisfy subsequent requests without successful revalidation
   * with the origin server.<br>
   * <br>
   * Note that this directive can be used on requests or responses.
   * 
   * @param fieldName
   *            A field name, typically a HTTP header name, that must not be
   *            sent by caches.
   * @return A new "no-cache" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective noCache(std::string fieldName);

  /**
   * Creates a "no-store" directive. Indicates that a cache must not release
   * or retain any information about the call. This applies to both private
   * and shared caches.<br>
   * <br>
   * Note that this directive can be used on requests or responses.
   * 
   * @return A new "no-store" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.2">HTTP
   *      1.1 - What May be Stored by Caches</a>
   */
  static CacheDirective noStore();

  /**
   * Creates a "no-transform" directive. Indicates that a cache or
   * intermediary proxy must not transform the response entity.<br>
   * <br>
   * Note that this directive can be used on requests or responses.
   * 
   * @return A new "no-transform" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.5">HTTP
   *      1.1 - No-Transform Directive</a>
   */
  static CacheDirective noTransform();

  /**
   * Creates a "onlyIfCached" directive. Indicates that only cached responses
   * should be returned to the client.<br>
   * <br>
   * Note that this directive can be used on requests only.
   * 
   * @return A new "only-if-cached" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.4">HTTP
   *      1.1 - Cache Revalidation and Reload Controls</a>
   */
  static CacheDirective onlyIfCached();

  /**
   * Creates a "private" directive. Indicates that all or part of the response
   * message is intended for a single user and must not be cached by a shared
   * cache.<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @return A new "private" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective privateInfo();

  /**
   * Creates a "private" directive. Indicates that all or part of the response
   * message is intended for a single user and must not be cached by a shared
   * cache.<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @param fieldNames
   *            Field names, typically a HTTP header name, that must be
   *            private.
   * @return A new "private" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective privateInfo(std::list<std::string> fieldNames);

  /**
   * Creates a "private" directive. Indicates that all or part of the response
   * message is intended for a single user and must not be cached by a shared
   * cache.<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @param fieldName
   *            A field name, typically a HTTP header name, that is private.
   * @return A new "private" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective privateInfo(std::string fieldName);

  /**
   * Creates a "proxy-revalidate" directive. Indicates that the origin server
   * requires revalidation of a cache entry on any subsequent use, except that
   * it does not apply to non-shared user agent caches<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @return A new "proxy-revalidate" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.4">HTTP
   *      1.1 - Cache Revalidation and Reload Controls</a>
   */
  static CacheDirective proxyMustRevalidate();

  /**
   * Creates a "public" directive. Indicates that the response may be cached
   * by any cache, even if it would normally be non-cacheable or cacheable
   * only within a non-shared cache.<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @return A new "public" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.1">HTTP
   *      1.1 - What is Cacheable</a>
   */
  static CacheDirective publicInfo();

  /**
   * Creates a "s-maxage" directive. Indicates that the client is willing to
   * accept a response from a shared cache (but not a private cache) whose age
   * is no greater than the specified time in seconds.<br>
   * <br>
   * Note that this directive can be used on responses only.
   * 
   * @param sharedMaxAge
   *            Maximum age in seconds.
   * @return A new "s-maxage" directive.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.9.3">HTTP
   *      1.1 - Modifications of the Basic Expiration Mechanism</a>
   */
  static CacheDirective sharedMaxAge(int sharedMaxAge);

  /**
   * Constructor for directives with no value.
   * 
   * @param name
   *            The directive name.
   */
  CacheDirective(std::string name) {
    CacheDirective(name, null);
  }

  /**
   * Constructor for directives with a value.
   * 
   * @param name
   *            The directive name.
   * @param value
   *            The directive value.
   */
  CacheDirective(std::string name, std::string value) {
    Parameter(name, value);
  }

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CACHE_DIRECTIVE_H_
