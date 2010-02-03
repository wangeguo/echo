#include <echo/data/cache-directive.h>

namespace echo {
namespace data {

static CacheDirective CacheDirective::maxAge(int maxAge) {
  return new CacheDirective(HttpConstants.CACHE_MAX_AGE, Integer
                            .toString(maxAge));
}

static CacheDirective CacheDirective::maxStale() {
  return new CacheDirective(HttpConstants.CACHE_MAX_STALE);
}

static CacheDirective CacheDirective::maxStale(int maxStale) {
  return new CacheDirective(HttpConstants.CACHE_MAX_STALE, Integer
                            .toString(maxStale));
}

static CacheDirective CacheDirective::minFresh(int minFresh) {
  return new CacheDirective(HttpConstants.CACHE_MIN_FRESH, Integer
                            .toString(minFresh));
}

static CacheDirective CacheDirective::mustRevalidate() {
  return new CacheDirective(HttpConstants.CACHE_MUST_REVALIDATE);
}

static CacheDirective CacheDirective::noCache() {
  return new CacheDirective(HttpConstants.CACHE_NO_CACHE);
}

static CacheDirective CacheDirective::noCache(std::list<std::string> fieldNames) {
  StringBuilder sb = new StringBuilder();

  if (fieldNames != null) {
    for (int i = 0; i < fieldNames.size(); i++) {
      sb.append("\"" + fieldNames.get(i) + "\"");

      if (i < fieldNames.size() - 1) {
        sb.append(',');
      }
    }
  }

  return new CacheDirective(HttpConstants.CACHE_NO_CACHE, sb.toString());
}

static CacheDirective CacheDirective::noCache(std::string fieldName) {
  return new CacheDirective(HttpConstants.CACHE_NO_CACHE, "\""
                            + fieldName + "\"");
}

static CacheDirective CacheDirective::noStore() {
  return new CacheDirective(HttpConstants.CACHE_NO_STORE);
}

static CacheDirective CacheDirective::noTransform() {
  return new CacheDirective(HttpConstants.CACHE_NO_TRANSFORM);
}

static CacheDirective CacheDirective::onlyIfCached() {
  return new CacheDirective(HttpConstants.CACHE_ONLY_IF_CACHED);
}

static CacheDirective CacheDirective::privateInfo() {
  return new CacheDirective(HttpConstants.CACHE_PRIVATE);
}

static CacheDirective CacheDirective::privateInfo(std::list<std::string> fieldNames) {
  StringBuilder sb = new StringBuilder();

  if (fieldNames != null) {
    for (int i = 0; i < fieldNames.size(); i++) {
      sb.append("\"" + fieldNames.get(i) + "\"");

      if (i < fieldNames.size() - 1) {
        sb.append(',');
      }
    }
  }

  return new CacheDirective(HttpConstants.CACHE_PRIVATE, sb.toString());
}

static CacheDirective CacheDirective::privateInfo(std::string fieldName) {
  return new CacheDirective(HttpConstants.CACHE_PRIVATE, "\"" + fieldName
                            + "\"");
}

static CacheDirective CacheDirective::proxyMustRevalidate() {
  return new CacheDirective(HttpConstants.CACHE_PROXY_MUST_REVALIDATE);
}

static CacheDirective CacheDirective::publicInfo() {
  return new CacheDirective(HttpConstants.CACHE_PUBLIC);
}

static CacheDirective CacheDirective::sharedMaxAge(int sharedMaxAge) {
  return new CacheDirective(HttpConstants.CACHE_SHARED_MAX_AGE, Integer
                            .toString(sharedMaxAge));
}

} // namespace data
} // namespace echo
