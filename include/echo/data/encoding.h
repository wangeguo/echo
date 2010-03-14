#ifndef _ECHO_DATA_ENCODING_H_
#define _ECHO_DATA_ENCODING_H_

#include <string>

namespace echo {
namespace data {

/**
 * Modifier of a representation's media type. Useful to apply compression
 * without losing the identity of the underlying media type.
 * 
 * @author Jerome Louvel
 */
//public final class Encoding extends Metadata {
class Encoding : public Metadata {

 public:

  /**
   * Returns the encoding associated to a name. If an existing constant exists
   * then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The name.
   * @return The associated encoding.
   */
  static Encoding valueOf(const std::string name);

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   */
  Encoding(const std::string name) {
    Encoding(name, "Encoding applied to a representation");
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param description
   *            The description.
   */
  Encoding(const std::string name, const std::string description) {
    Metadata(name, description);
  }

  /** {@inheritDoc} */
  //@Override
  bool equals(const Object object);

  //@Override
  Metadata getParent() {
    return equals(ALL) ? NULL : ALL;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return (getName() == NULL) ? 0 : getName().toLowerCase().hashCode();
  }

  /**
   * Indicates if a given encoding is included in the current one. The test is
   * true if both encodings are equal or if the given encoding is within the
   * range of the current one. For example, ALL includes all encodings. A NULL
   * encoding is considered as included into the current one.
   * <p>
   * Examples:
   * <ul>
   * <li>ALL.includes(COMPRESS) -> true</li>
   * <li>COMPRESS.includes(ALL) -> false</li>
   * </ul>
   * 
   * @param included
   *            The encoding to test for inclusion.
   * @return True if the given encoding is included in the current one.
   * @see #isCompatible(Metadata)
   */
  bool includes(Metadata included) {
    return equals(ALL) || (included == NULL) || equals(included);
  }

 public:

  /** All encodings acceptable. */
  static const Encoding ALL;

  /** The common Unix file compression. */
  static const Encoding COMPRESS;

  /** The zlib format defined by RFC 1950 and 1951. */
  static const Encoding DEFLATE;

  /** The FreeMarker encoding. */
  static const Encoding FREEMARKER;

  /** The GNU Zip encoding. */
  static const Encoding GZIP;

  /** The default (identity) encoding. */
  static const Encoding IDENTITY;

  /** The Velocity encoding. */
  static const Encoding VELOCITY;

  /** The Info-Zip encoding. */
  static const Encoding ZIP;
  
};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_ENCODING_H_
