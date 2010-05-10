#ifndef _ECHO_DATA_REFERENCE_LIST_H_
#define _ECHO_DATA_REFERENCE_LIST_H_

/*
  import java.io.BufferedReader;
  import java.io.IOException;
  import java.util.ArrayList;
*/
#include <list>
#include <echo/representation/representation.h>
#include <echo/representation/string-representation.h>
#include <echo/util/wrapper-list.h>

namespace echo {
namespace data {

/**
 * List of URI references.
 * 
 * @author Jerome Louvel
 */
//public class ReferenceList extends WrapperList<Reference> {
class ReferenceList : public WrapperList<Reference> {

 public:
  /**
   * Constructor.
   */
  ReferenceList() {
    super();
  }

  /**
   * Constructor.
   * 
   * @param initialCapacity
   *            The initial list capacity.
   */
  ReferenceList(int initialCapacity) {
    super(new ArrayList<Reference>(initialCapacity));
  }

  /**
   * Constructor.
   * 
   * @param delegate
   *            The delegate list.
   */
  ReferenceList(List<Reference> delegate) {
    super(delegate);
  }

  /**
   * Constructor from a "text/uri-list" representation.
   * 
   * @param uriList
   *            The "text/uri-list" representation to parse.
   * @throws IOException
   */
  ReferenceList(Representation uriList) throws IOException;

  /**
   * Creates then adds a reference at the end of the list.
   * 
   * @param uri
   *            The uri of the reference to add.
   * @return True (as per the general contract of the Collection.add method).
   */
  bool add(std::string uri) {
    return add(new Reference(uri));
  }

  /**
   * Returns the list identifier.
   * 
   * @return The list identifier.
   */
  Reference getIdentifier() {
    return this.identifier;
  }

  /**
   * Returns a representation of the list in the "text/uri-list" format.
   * 
   * @return A representation of the list in the "text/uri-list" format.
   */
  Representation getTextRepresentation();

  /**
   * Returns a representation of the list in "text/html" format.
   * 
   * @return A representation of the list in "text/html" format.
   */
  Representation getWebRepresentation();

  /**
   * Sets the list reference.
   * 
   * @param identifier
   *            The list identifier.
   */
  void setIdentifier(Reference identifier) {
    this.identifier = identifier;
  }

  /**
   * Sets the list reference.
   * 
   * @param identifier
   *            The list identifier as a URI.
   */
  void setIdentifier(std::string identifier) {
    setIdentifier(new Reference(identifier));
  }

  /**
   * Returns a view of the portion of this list between the specified
   * fromIndex, inclusive, and toIndex, exclusive.
   * 
   * @param fromIndex
   *            The start position.
   * @param toIndex
   *            The end position (exclusive).
   * @return The sub-list.
   */
  //@Override
  ReferenceList subList(int fromIndex, int toIndex) {
    return new ReferenceList(getDelegate().subList(fromIndex, toIndex));
  }

 private:

  /** The list's identifier. */
  volatile Reference identifier;


};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_REFERENCE_LIST_H_
