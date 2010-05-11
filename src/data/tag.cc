#include <echo/data/tag.h>

namespace echo {
namespace data {

const Tag Tag::ALL = Tag::parse("*");

Tag Tag::parse(const std::string httpTag) {
  Tag result = NULL;
  bool weak = false;
  std::string httpTagCopy = httpTag;

  if (httpTagCopy.startsWith("W/")) {
    weak = true;
    httpTagCopy = httpTagCopy.substring(2);
  }

  if (httpTagCopy.startsWith("\"") && httpTagCopy.endsWith("\"")) {
    result = new Tag(
        httpTagCopy.substring(1, httpTagCopy.length() - 1), weak);
  } else if (httpTagCopy.equals("*")) {
    result = new Tag("*", weak);
  } else {
    Context.getCurrentLogger().log(Level.WARNING,
                                   "Invalid tag format detected: " + httpTagCopy);
  }

  return result;
}

bool Tag::equals(const Object object, bool checkWeakness) {
  bool result = (object != NULL) && (object instanceof Tag);

  if (result) {
    const Tag that = (Tag) object;

    if (checkWeakness) {
      result = (that.isWeak() == isWeak());
    }

    if (result) {
      if (getName() == NULL) {
        result = (that.getName() == NULL);
      } else {
        result = getName().equals(that.getName());
      }
    }
  }

  return result;
}

std::string Tag::format() {
  if (getName().equals("*")) {
    return "*";
  }

  const StringBuilder sb = new StringBuilder();
  if (isWeak()) {
    sb.append("W/");
  }
  return sb.append('"').append(getName()).append('"').toString();
}

} // namespace data
} // namespace echo
