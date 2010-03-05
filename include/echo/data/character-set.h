#ifndef _ECHO_DATA_CHARACTER_SET_H_
#define _ECHO_DATA_CHARACTER_SET_H_

namespace echo {
namespace data {

/**
 * Character set used to encode characters in textual representations.
 * 
 * @author Jerome Louvel
 */
//public final class CharacterSet extends Metadata {
class CharacterSet : public Metadata {

 public:
  
  /**
   * Returns the character set associated to a name. If an existing constant
   * exists then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The name.
   * @return The associated character set.
   */
  static CharacterSet valueOf(std::string name);

  /**
   * Constructor.
   * 
   * @param charset
   *            The character set.
   */
  CharacterSet(const java.nio.charset.Charset charset) {
    CharacterSet(charset.name(), charset.displayName());
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   */
  CharacterSet(std::string name) {
    CharacterSet(name == null ? null : name.toUpperCase(),
                 "Character set or range of character sets");
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param description
   *            The description.
   */
  CharacterSet(std::string name, std::string description) {
    Metadata(getIanaName(name), description);
  }

  /** {@inheritDoc} */
  //@Override
  bool equals(Object object) {
    return (object instanceof CharacterSet)
        && getName()
        .equalsIgnoreCase(((CharacterSet) object).getName());
  }

  //@Override
  Metadata getParent() {
    return equals(ALL) ? null : ALL;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return (getName() == null) ? 0 : getName().toLowerCase().hashCode();
  }

  /**
   * Indicates if a given character set is included in the current one. The
   * test is true if both character sets are equal or if the given character
   * set is within the range of the current one. For example, ALL includes all
   * character sets. A null character set is considered as included into the
   * current one.
   * <p>
   * Examples:
   * <ul>
   * <li>ALL.includes(UTF_16) -> true</li>
   * <li>UTF_16.includes(ALL) -> false</li>
   * </ul>
   * 
   * @param included
   *            The character set to test for inclusion.
   * @return True if the given character set is included in the current one.
   * @see #isCompatible(Metadata)
   */
  bool includes(Metadata included) {
    return equals(ALL) || (included == null) || equals(included);
  }

  /**
   * Returns the NIO charset matching the character set name.
   * 
   * @return The NIO charset.
   */
  java.nio.charset.Charset toCharset() {
    return java.nio.charset.Charset.forName(getName());
  }

 private:

  /**
   * Handles mapping between Java character set names and IANA preferred name.
   * For example, "MACROMAN" is not an official IANA name and "ISO-8859-6" is
   * preferred over "arabic".
   * 
   * @param name
   *            The character set name.
   * @return The IANA character set name.
   */
  static std::string getIanaName(std::string name);

 public:
  
  /** All character sets acceptable. */
  static const CharacterSet ALL;

  /**
   * The ISO/IEC 8859-1 (Latin 1) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-1">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_1;

  /**
   * The ISO/IEC 8859-2 (Latin 2) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-2">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_2;

  /**
   * The ISO/IEC 8859-3 (Latin 3) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-3">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_3;

  /**
   * The ISO/IEC 8859-4 (Latin 4) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-4">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_4;

  /**
   * The ISO/IEC 8859-5 (Cyrillic) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-5">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_5;

  /**
   * The ISO/IEC 8859-6 (Arabic) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-6">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_6;

  /**
   * The ISO/IEC 8859-7 (Greek) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-7">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_7;

  /**
   * The ISO/IEC 8859-8 (Hebrew) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-8">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_8;

  /**
   * The ISO/IEC 8859-9 (Latin 5) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-9">Wikipedia page</a>
   */
  static const CharacterSet ISO_8859_9;

  /**
   * The ISO/IEC 8859-10 (Latin 6) character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-10">Wikipedia
   *      page</a>
   */
  static const CharacterSet ISO_8859_10;

  /**
   * The Macintosh ("Mac OS Roman") character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/Mac_OS_Roman">Wikipedia
   *      page</a>
   */
  static const CharacterSet MACINTOSH;

  /**
   * The US-ASCII character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/US-ASCII">Wikipedia page</a>
   */
  static const CharacterSet US_ASCII;

  /**
   * The UTF-16 character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/UTF-16">Wikipedia page</a>
   */
  static const CharacterSet UTF_16;

  /**
   * The UTF-8 character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/UTF-8">Wikipedia page</a>
   */
  static const CharacterSet UTF_8;

  /**
   * The Windows-1252 ('ANSI') character set.
   * 
   * @see <a href="http://en.wikipedia.org/wiki/Windows-1252">Wikipedia
   *      page</a>
   * 
   */
  static const CharacterSet WINDOWS_1252;

  /**
   * The default character set of the JVM.
   * 
   * @see java.nio.charset.Charset#defaultCharset()
   */
  static const CharacterSet DEFAULT;
  

};

} // namespace data
} // namespace echo
#endif // _ECHO_DATA_CHARACTER_SET_H_
