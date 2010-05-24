#ifndef _ECHO_REPRESENTATION_APPENDABLE_REPRESENTATION_H_
#define _ECHO_REPRESENTATION_APPENDABLE_REPRESENTATION_H_

//import java.io.IOException;

#include <string>
#include <echo/data/character-set.h>
#include <echo/data/language.h>
#include <echo/data/media-type.h>

namespace echo {
namespace representation {

/**
 * Represents an appendable sequence of characters.
 * 
 * @author Jerome Louvel
 */
/*public class AppendableRepresentation extends StringRepresentation implements
  Appendable {*/
class AppendableRepresentation : public StringRepresentation {

 public:

  /**
   * Constructor. The following metadata are used by default: "text/plain"
   * media type, no language and the ISO-8859-1 character set.
   * 
   */
  AppendableRepresentation() {
    AppendableRepresentation(NULL);
  }

  /**
   * Constructor. The following metadata are used by default: "text/plain"
   * media type, no language and the ISO-8859-1 character set.
   * 
   * @param text
   *            The string value.
   */
  AppendableRepresentation(CharSequence text) {
    StringRepresentation(text);
  }

  /**
   * Constructor. The following metadata are used by default: "text/plain"
   * media type, no language and the ISO-8859-1 character set.
   * 
   * @param text
   *            The string value.
   * @param language
   *            The language.
   */
  AppendableRepresentation(CharSequence text, Language language) {
    StringRepresentation(text, language);
  }

  /**
   * Constructor. The following metadata are used by default: no language and
   * the ISO-8859-1 character set.
   * 
   * @param text
   *            The string value.
   * @param mediaType
   *            The media type.
   */
  AppendableRepresentation(CharSequence text, MediaType mediaType) {
    StringRepresentation(text, mediaType);
  }

  /**
   * Constructor. The following metadata are used by default: ISO-8859-1
   * character set.
   * 
   * @param text
   *            The string value.
   * @param mediaType
   *            The media type.
   * @param language
   *            The language.
   */
  AppendableRepresentation(CharSequence text, MediaType mediaType,
                           Language language) {
    StringRepresentation(text, mediaType, language);
  }

  /**
   * Constructor.
   * 
   * @param text
   *            The string value.
   * @param mediaType
   *            The media type.
   * @param language
   *            The language.
   * @param characterSet
   *            The character set.
   */
  AppendableRepresentation(CharSequence text, MediaType mediaType,
                           Language language, CharacterSet characterSet) {
    StringRepresentation(text, mediaType, language, characterSet);
  }

  Appendable append(char c) throws IOException;

  Appendable append(CharSequence csq) throws IOException ;

  Appendable append(CharSequence csq, int start, int end)
      throws IOException ;

  //@Override
  std::string getText() {
    return (this->appendableText == NULL) ? NULL : this->appendableText
        .toString();
  }

  //@Override
  void setText(CharSequence text);


 private:

  /** The appendable text. */
  volatile StringBuilder appendableText;

};

} // namespace representation
} // namespace echo

#endif // _ECHO_REPRESENTATION_APPENDABLE_REPRESENTATION_H_
