#include <echo/data/cookie-setting.h>

namespace echo {
namespace data {

CookieSetting::CookieSetting(int version, std::string name, std::string value, std::string path,
                             std::string domain, std::string comment, int maxAge, bool secure,
                             bool accessRestricted) {
  Cookie(version, name, value, path, domain);
  this->comment = comment;
  this->maxAge = maxAge;
  this->secure = secure;
  this->accessRestricted = accessRestricted;
}

bool CookieSetting::equals(Object obj) {
  bool result = (obj == this);

  // if obj == this no need to go further
  if (!result) {
    // test for equality at Cookie level i.e. name and value.
    if (super.equals(obj)) {
      // if obj isn't a cookie setting or is NULL don't evaluate
      // further
      if (obj instanceof CookieSetting) {
        const CookieSetting that = (CookieSetting) obj;
        result = (this->maxAge == that.maxAge)
                 && (this->secure == that.secure);

        if (result) // if "maxAge" and "secure" properties are equal
          // test comments
        {
          if (!(this->comment == NULL)) // compare comments
            // taking care of nulls
          {
            result = (this->comment.equals(that.comment));
          } else {
            result = (that.comment == NULL);
          }
        }
      }
    }
  }

  return result;
}

int CookieSetting::hashCode() {
  return SystemUtils.hashCode(super.hashCode(), getComment(),
                              getMaxAge(), isSecure());
}

} // namespace data
} // namespace echo
