#include <echo/data/authentication-info.h>

namespace echo {
namespace data {

AuthenticationInfo::AuthenticationInfo(std::string nextNonce, int nonceCount, std::string cnonce,
                                       std::string quality, std::string responseDigest) {
  nextServerNonce = nextNonce;
  this->nonceCount = nonceCount;
  clientNonce = cnonce;
  this->quality = quality;
  this->responseDigest = responseDigest;
}

const bool AuthenticationInfo::equals(const Object obj) {
  bool result = (obj == this);

  // if obj == this no need to go further
  if (!result) {
    // if obj isn't a challenge request or is null don't evaluate
    // further
    if (obj instanceof AuthenticationInfo) {
      final AuthenticationInfo that = (AuthenticationInfo) obj;
      if (getNextServerNonce() != null) {
        result = getNextServerNonce().equals(
            that.getNextServerNonce());
      } else {
        result = (that.getNextServerNonce() == null);
      }

      if (result) {
        result = (getNonceCount() == that.getNonceCount());
      }

      if (result) {
        if (getClientNonce() != null) {
          result = getClientNonce().equals(that.getClientNonce());
        } else {
          result = (that.getClientNonce() == null);
        }
      }

      if (result) {
        if (getQuality() != null) {
          result = getQuality().equals(that.getQuality());
        } else {
          result = (that.getQuality() == null);
        }
      }

      if (result) {
        if (getResponseDigest() != null) {
          result = getResponseDigest().equals(
              that.getResponseDigest());
        } else {
          result = (that.getResponseDigest() == null);
        }
      }
    }
  }

  return result;
}

int AuthenticationInfo::hashCode() {
  return SystemUtils.hashCode(getNextServerNonce(), getNonceCount(),
                              getClientNonce(), getQuality(), getResponseDigest());
}

} // namespace data
} // echo
