#include <echo/data/cookie.h>

namespace echo {
namespace data {


Cookie::Cookie(int version, std::string name, std::string value, std::string path,
               std::string domain) {
  Parameter(name, value);
  this->version = version;
  this->path = path;
  this->domain = domain;
}

bool Cookie::equals(Object obj) {
  bool result = (obj == this);

  // if obj == this no need to go further
  if (!result) {
    // test for equality at Parameter level i.e. name and value.
    if (super.equals(obj)) {
      // if obj isn't a cookie or is NULL don't evaluate further
      if (obj instanceof Cookie) {
        const Cookie that = (Cookie) obj;
        result = (this->version == that.version);
        if (result) // if versions are equal test domains
        {
          if (!(this->domain == NULL)) // compare domains
            // taking care of NULLs
          {
            result = (this->domain.equals(that.domain));
          } else {
            result = (that.domain == NULL);
          }

          if (result) // if domains are equal test the paths
          {
            if (!(this->path == NULL)) // compare paths taking
              // care of NULLs
            {
              result = (this->path.equals(that.path));
            } else {
              result = (that.path == NULL);
            }
          }
        }
      }
    }
  }

  return result;
}

int Cookie::hashCode() {
  return SystemUtils.hashCode(super.hashCode(), getVersion(), getPath(),
                              getDomain());
}

} // namespace data
} // namespace echo
