#ifndef _ECHO_DATA_LANGUAGE_H_
#define _ECHO_DATA_LANGUAGE_H_
/*
  import java.util.Collections;
  import java.util.concurrent.CopyOnWriteArrayList;
*/

#include <list>
#include <string>

namespace echo {
namespace data {

/**
 * Language used in representations and preferences. A language tag is composed
 * of one or more parts: A primary language tag and a possibly empty series of
 * sub-tags. When formatted as a string, parts are separated by hyphens.
 * 
 * @author Jerome Louvel
 */
//public final class Language extends Metadata {
class Language : public Metadata {

 public:

  /**
   * Returns the language associated to a name. If an existing constant exists
   * then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The name.
   * @return The associated language.
   */
  static Language valueOf(const std::string name);

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   */
  Language(const std::string name) {
    Language(name, "Language or range of languages");
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param description
   *            The description.
   */
  Language(const std::string name, const std::string description);

  /** {@inheritDoc} */
  //@Override
  bool equals(const Object object);

  //@Override
  Language getParent();

  /**
   * Returns the primary tag.
   * 
   * @return The primary tag.
   */
  std::string getPrimaryTag();

  /**
   * Returns the unmodifiable list of subtags. This list can be empty.
   * 
   * @return The list of subtags for this language Tag.
   */
  std::list<std::string> getSubTags();

  /** {@inheritDoc} */
  //@Override
  int hashCode();

  /**
   * Indicates if a given language is included in the current one. The test is
   * true if both languages are equal or if the given language is within the
   * range of the current one. For example, ALL includes all languages. A NULL
   * language is considered as included into the current one.
   * <p>
   * Examples:
   * <ul>
   * <li>ENGLISH.includes(ENGLISH_US) -> true</li>
   * <li>ENGLISH_US.includes(ENGLISH) -> false</li>
   * </ul>
   * 
   * @param included
   *            The language to test for inclusion.
   * @return True if the language type is included in the current one.
   * @see #isCompatible(Metadata)
   */
  bool includes(Metadata included);

 public:

  /** All languages acceptable. */
  static const Language ALL = new Language("*", "All languages");

  /**
   * The default language of the JVM.
   * 
   * @see java.util.Locale#getDefault()
   */
  static const Language DEFAULT = new Language(java.util.Locale
                                               .getDefault().getLanguage());


  /** English language. */
  static const Language ENGLISH = new Language("en",
                                               "English language");

  /** English language spoken in USA. */
  static const Language ENGLISH_US = new Language("en-us",
                                                  "English language in USA");

  /** French language. */
  static const Language FRENCH = new Language("fr", "French language");

  /** French language spoken in France. */
  static const Language FRENCH_FRANCE = new Language("fr-fr",
                                                     "French language in France");

  /** Spanish language. */
  static const Language SPANISH = new Language("es",
                                               "Spanish language");

 private:

  /** The metadata main list of subtags taken from the metadata name. */
  volatile std::list<std::string> subTags;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_LANGUAGE_H_
