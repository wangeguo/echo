#ifndef _ECHO_DATA_METADATA_H_
#define _ECHO_DATA_METADATA_H_

#include <string>

namespace echo {
namespace data {

/**
 * Representations metadata for content negotiation. Metadata is in the form of
 * name-value pairs, where the name corresponds to a standard that defines the
 * value's structure and semantics. Response messages may include both
 * representation metadata and resource metadata: information about the resource
 * that is not specific to the supplied representation." Roy T. Fielding
 * 
 * @see Preference
 * @see <a href=
 *      "http://roy.gbiv.com/pubs/dissertation/rest_arch_style.htm#sec_5_2_1_2"
 *      >Source dissertation</a>
 * @author Jerome Louvel
 */
//public abstract class Metadata {
class Metadata {

 public:
  /**
   * Returns the parent metadata if available or null.
   * 
   * @return The parent metadata.
   */
  //public abstract Metadata getParent();
  virtual Metadata getParent() = 0;
  /**
   * Indicates if a given metadata is included in the current one. The test is
   * true if both metadata are equal or if the given metadata is within the
   * range of the current one. For example, {@link MediaType#ALL} includes all
   * media types.
   * <p>
   * Examples:
   * <ul>
   * <li>TEXT_ALL.includes(TEXT_PLAIN) -> true</li>
   * <li>TEXT_PLAIN.includes(TEXT_ALL) -> false</li>
   * </ul>
   * 
   * @param included
   *            The metadata to test for inclusion.
   * @return True if the given metadata is included in the current one.
   * @see #isCompatible(Metadata)
   */
  //public abstract bool includes(Metadata included);
  virtual bool includes(Metadata included) = 0;

  /**
   * Checks if this metadata is compatible with the given metadata.
   * <p>
   * Examples:
   * <ul>
   * <li>TEXT_ALL.isCompatible(TEXT_PLAIN) -> true</li>
   * <li>TEXT_PLAIN.isCompatible(TEXT_ALL) -> true</li>
   * <li>TEXT_PLAIN.isCompatible(APPLICATION_ALL) -> false</li>
   * </ul>
   * 
   * @param otherMetadata
   *            The other metadata to compare.
   * @return True if the metadata are compatible.
   * @see #includes(Metadata)
   */
  bool isCompatible(Metadata otherMetadata) {
    return (otherMetadata != NULL)
        && (includes(otherMetadata) || otherMetadata.includes(this));
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The unique name.
   */
  Metadata(std::string name) {
    Metadata(name, NULL);
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The unique name.
   * @param description
   *            The description.
   */
  Metadata(std::string name, std::string description) {
    this->name = name;
    this->description = description;
  }

  /** {@inheritDoc} */
  //@Override
  bool equals(Object object) {
    return (object instanceof Metadata)
        && ((Metadata) object).getName().equals(getName());
  }

  /**
   * Returns the description.
   * 
   * @return The description.
   */
  std::string getDescription() {
    return description;
  }

  /**
   * Returns the name (ex: "text/html" or "compress" or "iso-8851-1").
   * 
   * @return The name (ex: "text/html" or "compress" or "iso-8851-1").
   */
  std::string getName() {
    return name;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return (getName() == NULL) ? 0 : getName().hashCode();
  }

  /**
   * Returns the metadata name.
   * 
   * @return The metadata name.
   */
  //@Override
  std::string toString() {
    return getName();
  }

 private:

  /** The metadata name like "text/html" or "compress" or "iso-8851-1". */
  const std::string name;

  /** The description of this metadata. */
  const std::string description;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_METADATA_H_
