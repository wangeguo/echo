#include <echo/data/character-set.h>

namespace echo {
namespace data {


/** All character sets acceptable. */
static const CharacterSet CharacterSet::ALL("*","All character sets");

/**
 * The ISO/IEC 8859-1 (Latin 1) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-1">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_1("ISO-8859-1", "ISO/IEC 8859-1 or Latin 1 character set");

/**
 * The ISO/IEC 8859-2 (Latin 2) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-2">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_2("ISO-8859-2", "ISO/IEC 8859-2 or Latin 2 character set");

/**
 * The ISO/IEC 8859-3 (Latin 3) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-3">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_3("ISO-8859-3", "ISO/IEC 8859-3 or Latin 3 character set");

/**
 * The ISO/IEC 8859-4 (Latin 4) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-4">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_4("ISO-8859-4", "ISO/IEC 8859-4 or Latin 4 character set");

/**
 * The ISO/IEC 8859-5 (Cyrillic) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-5">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_5("ISO-8859-5", "ISO/IEC 8859-5 or Cyrillic character set");

/**
 * The ISO/IEC 8859-6 (Arabic) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-6">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_6("ISO-8859-6", "ISO/IEC 8859-6 or Arabic character set");

/**
 * The ISO/IEC 8859-7 (Greek) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-7">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_7("ISO-8859-7", "ISO/IEC 8859-7 or Greek character set");

/**
 * The ISO/IEC 8859-8 (Hebrew) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-8">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_8("ISO-8859-8", "ISO/IEC 8859-8 or Hebrew character set");

/**
 * The ISO/IEC 8859-9 (Latin 5) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-9">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_9("ISO-8859-9", "ISO/IEC 8859-9 or Latin 5 character set");

/**
 * The ISO/IEC 8859-10 (Latin 6) character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/ISO_8859-10">Wikipedia
 *      page</a>
 */
static const CharacterSet
CharacterSet::ISO_8859_10("ISO-8859-10", "ISO/IEC 8859-10 or Latin 6 character set");

/**
 * The Macintosh ("Mac OS Roman") character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/Mac_OS_Roman">Wikipedia
 *      page</a>
 */
static const CharacterSet
CharacterSet::MACINTOSH("macintosh","Mac OS Roman character set");

/**
 * The US-ASCII character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/US-ASCII">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::US_ASCII("US-ASCII","US ASCII character set");

/**
 * The UTF-16 character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/UTF-16">Wikipedia page</a>
 */
static const CharacterSet
CharacterSet::UTF_16("UTF-16","UTF 16 character set");

/**
 * The UTF-8 character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/UTF-8">Wikipedia page</a>
 */
static const CharacterSet CharacterSet::UTF_8("UTF-8","UTF 8 character set");

/**
 * The Windows-1252 ('ANSI') character set.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/Windows-1252">Wikipedia
 *      page</a>
 * 
 */
static const CharacterSet
CharacterSet::WINDOWS_1252("windows-1252", "Windows 1232 character set");

/**
 * The default character set of the JVM.
 * 
 * @see java.nio.charset.Charset#defaultCharset()
 */
static const CharacterSet
CharacterSet::DEFAULT(java.nio.charset.Charset.defaultCharset());

static CharacterSet::CharacterSet CharacterSet::valueOf(std::string name) {
  CharacterSet result = null;
  name = getIanaName(name);

  if ((name != null) && !name.equals("")) {
    if (name.equalsIgnoreCase(ALL.getName())) {
      result = ALL;
    } else if (name.equalsIgnoreCase(ISO_8859_1.getName())) {
      result = ISO_8859_1;
    } else if (name.equalsIgnoreCase(US_ASCII.getName())) {
      result = US_ASCII;
    } else if (name.equalsIgnoreCase(UTF_8.getName())) {
      result = UTF_8;
    } else if (name.equalsIgnoreCase(UTF_16.getName())) {
      result = UTF_16;
    } else if (name.equalsIgnoreCase(WINDOWS_1252.getName())) {
      result = WINDOWS_1252;
    } else if (name.equalsIgnoreCase(MACINTOSH.getName())) {
      result = MACINTOSH;
    } else {
      result = new CharacterSet(name);
    }
  }

  return result;
}

static std::string CharaterSet::getIanaName(std::string name) {
  if (name != null) {
    name = name.toUpperCase();

    if (name.equalsIgnoreCase("MACROMAN")) {
      name = MACINTOSH.getName();
    } else if (name.equalsIgnoreCase("ASCII")) {
      name = US_ASCII.getName();
    } else if (name.equalsIgnoreCase("latin1")) {
      name = ISO_8859_1.getName();
    } else if (name.equalsIgnoreCase("latin2")) {
      name = ISO_8859_2.getName();
    } else if (name.equalsIgnoreCase("latin3")) {
      name = ISO_8859_3.getName();
    } else if (name.equalsIgnoreCase("latin4")) {
      name = ISO_8859_4.getName();
    } else if (name.equalsIgnoreCase("cyrillic")) {
      name = ISO_8859_5.getName();
    } else if (name.equalsIgnoreCase("arabic")) {
      name = ISO_8859_6.getName();
    } else if (name.equalsIgnoreCase("greek")) {
      name = ISO_8859_7.getName();
    } else if (name.equalsIgnoreCase("hebrew")) {
      name = ISO_8859_8.getName();
    } else if (name.equalsIgnoreCase("latin5")) {
      name = ISO_8859_9.getName();
    } else if (name.equalsIgnoreCase("latin6")) {
      name = ISO_8859_10.getName();
    }
  }

  return name;
}

} // namespace data
} // namespace echo

