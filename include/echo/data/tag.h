#ifndef _ECHO_DATA_TAG_H_
#define _ECHO_DATA_TAG_H_

#include <string>
#include <echo/util/logging/level.h>
#include <echo/context.h>
#include <echo/representation/representation-info.h>

namespace echo {
namespace data {

/**
 * Validation tag equivalent to an HTTP entity tag (E-Tag). "A strong entity tag
 * may be shared by two entities of a resource only if they are equivalent by
 * octet equality.<br>
 * <br>
 * A weak entity tag may be shared by two entities of a resource only if the
 * entities are equivalent and could be substituted for each other with no
 * significant change in semantics."
 * 
 * @see RepresentationInfo#getTag()
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.11">HTTP
 *      Entity Tags</a>
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec13.html#sec13.3.2">HTTP
 *      Entity Tag Cache Validators</a>
 * @author Jerome Louvel
 */
//public final class Tag {
class Tag {

 public:

  /**
   * Parses a tag formatted as defined by the HTTP standard.
   * 
   * @param httpTag
   *            The HTTP tag string; if it starts with 'W/' the tag will be
   *            marked as weak and the data following the 'W/' used as the
   *            tag; otherwise it should be surrounded with quotes (e.g.,
   *            "sometag").
   * @return A new tag instance.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.11">HTTP
   *      Entity Tags</a>
   */
  static Tag parse(const std::string httpTag);

  /**
   * Default constructor. The opaque tag is set to NULL and the weakness
   * indicator is set to true.
   */
  Tag() {
    Tag(NULL, true);
  }

  /**
   * Constructor of weak tags.
   * 
   * @param opaqueTag
   *            The tag value.
   */
  Tag(const std::string opaqueTag) {
    Tag(opaqueTag, true);
  }

  /**
   * Constructor.
   * 
   * @param opaqueTag
   *            The tag value.
   * @param weak
   *            The weakness indicator.
   */
  Tag(const std::string opaqueTag, bool weak) {
    this->name = opaqueTag;
    this->weak = weak;
  }

  /**
   * Indicates if both tags are equal.
   * 
   * @param object
   *            The object to compare to.
   * @return True if both tags are equal.
   */
  //@Override
  bool equals(const Object object) {
    return equals(object, true);
  }

  /**
   * Indicates if both tags are equal.
   * 
   * @param object
   *            The object to compare to.
   * @param checkWeakness
   *            the equality test takes care or not of the weakness.
   * 
   * @return True if both tags are equal.
   */
  bool equals(const Object object, bool checkWeakness);

  /**
   * Returns tag formatted as an HTTP tag string.
   * 
   * @return The formatted HTTP tag string.
   * @see <a
   *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.11">HTTP
   *      Entity Tags</a>
   */
  std::string format();

  /**
   * Returns the name, corresponding to an HTTP opaque tag value.
   * 
   * @return The name, corresponding to an HTTP opaque tag value.
   */
  std::string getName() {
    return this->name;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return format().hashCode();
  }

  /**
   * Indicates if the tag is weak.
   * 
   * @return True if the tag is weak, false if the tag is strong.
   */
  bool isWeak() {
    return this->weak;
  }

  /**
   * Returns the name.
   * 
   * @return The name.
   */
  //@Override
  std::string toString() {
    return getName();
  }

 public:
  /** Tag matching any other tag, used in call's condition data. */
  static const Tag ALL = Tag.parse("*");

 private:
  /** The name. */
  volatile std::string name;

  /** The tag weakness. */
  const bool weak;


};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_TAG_H_
