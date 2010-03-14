#ifndef _ECHO_DATA_FORM_H_
#define _ECHO_DATA_FORM_H_

/* import java.io.IOException; */
#include <list>
#include <string>

#include <echo/engine/util/form-utils.h>
#include <echo/representation/representation.h>
#include <echo/representation/string-representation.h>
#include <echo/util/series.h>

namespace echo {
namespace data {

/**
 * Form which is a specialized modifiable list of parameters.
 * 
 * @author Jerome Louvel
 */
//public class Form extends Series<Parameter> {
class Form : public Series<Parameter> {

 public:

  /**
   * Empty constructor.
   */
  Form() {
    Series();
  }

  /**
   * Constructor.
   * 
   * @param initialCapacity
   *            The initial list capacity.
   */
  Form(int initialCapacity) {
    Series(initialCapacity);
  }

  /**
   * Constructor.
   * 
   * @param delegate
   *            The delegate list.
   */
  Form(std::list<Parameter> delegate) {
    Series(delegate);
  }

  /**
   * Constructor.
   * 
   * @param webForm
   *            The URL encoded Web form.
   * @throws IOException
   */
  Form(Representation webForm) {
    FormUtils.parse(this, webForm);
  }

  /**
   * Constructor. Uses UTF-8 as the character set for encoding non-ASCII
   * characters.
   * 
   * @param queryString
   *            The Web form parameters as a string.
   * @throws IOException
   */
  Form(std::string queryString) {
    Form(queryString, CharacterSet.UTF_8);
  }

  /**
   * Constructor. Uses UTF-8 as the character set for encoding non-ASCII
   * characters.
   * 
   * @param parametersString
   *            The parameters string to parse.
   * @param separator
   *            The separator character to append between parameters.
   * @throws IOException
   */
  Form(std::string parametersString, char separator) {
    Form(parametersString, CharacterSet.UTF_8, separator);
  }

  /**
   * Constructor.
   * 
   * @param queryString
   *            The Web form parameters as a string.
   * @param characterSet
   *            The supported character encoding.
   * @throws IOException
   */
  Form(std::string queryString, CharacterSet characterSet) {
    Form(queryString, characterSet, '&');
  }

  /**
   * Constructor.
   * 
   * @param parametersString
   *            The parameters string to parse.
   * @param characterSet
   *            The supported character encoding.
   * @param separator
   *            The separator character to append between parameters.
   * @throws IOException
   */
  Form(std::string parametersString, CharacterSet characterSet,
       char separator) {
    FormUtils.parse(this, parametersString, characterSet, true, separator);
  }

  //@Override
  Parameter createEntry(std::string name, std::string value) {
    return new Parameter(name, value);
  }

  //@Override
  Series<Parameter> createSeries(std::list<Parameter> delegate);

  /**
   * Encodes the form using the standard URI encoding mechanism and the UTF-8
   * character set.
   * 
   * @return The encoded form.
   * @throws IOException
   */
  std::string encode() throws IOException {
    return encode(CharacterSet.UTF_8);
  }

  /**
   * URL encodes the form. The '&' character is used as a separator.
   * 
   * @param characterSet
   *            The supported character encoding.
   * @return The encoded form.
   * @throws IOException
   */
  std::string encode(CharacterSet characterSet) throws IOException {
    return encode(characterSet, '&');
  }

  /**
   * URL encodes the form.
   * 
   * @param characterSet
   *            The supported character encoding.
   * @param separator
   *            The separator character to append between parameters.
   * @return The encoded form.
   * @throws IOException
   */
  std::string encode(CharacterSet characterSet, char separator) throws IOException;

  /**
   * Formats the form as a matrix path string. Uses UTF-8 as the character set
   * for encoding non-ASCII characters.
   * 
   * @return The form as a matrix string.
   * @see <a href="http://www.w3.org/DesignIssues/MatrixURIs.html">Matrix URIs
   *      by Tim Berners Lee</a>
   */
  std::string getMatrixString() {
    return getMatrixString(CharacterSet.UTF_8);
  }

  /**
   * Formats the form as a query string.
   * 
   * @param characterSet
   *            The supported character encoding.
   * @return The form as a matrix string.
   * @see <a href="http://www.w3.org/DesignIssues/MatrixURIs.html">Matrix URIs
   *      by Tim Berners Lee</a>
   */
  std::string getMatrixString(CharacterSet characterSet);

  /**
   * Formats the form as a query string. Uses UTF-8 as the character set for
   * encoding non-ASCII characters.
   * 
   * @return The form as a query string.
   */
  std::string getQueryString() {
    return getQueryString(CharacterSet.UTF_8);
  }

  /**
   * Formats the form as a query string.
   * 
   * @param characterSet
   *            The supported character encoding.
   * @return The form as a query string.
   */
  std::string getQueryString(CharacterSet characterSet);

  /**
   * Returns the form as a Web representation
   * (MediaType.APPLICATION_WWW_FORM). Uses UTF-8 as the character set for
   * encoding non-ASCII characters.
   * 
   * @return The form as a Web representation.
   */
  Representation getWebRepresentation() {
    return getWebRepresentation(CharacterSet.UTF_8);
  }

  /**
   * Returns the form as a Web representation
   * (MediaType.APPLICATION_WWW_FORM).
   * 
   * @param characterSet
   *            The supported character encoding.
   * @return The form as a Web representation.
   */
  Representation getWebRepresentation(CharacterSet characterSet) {
    return new StringRepresentation(getQueryString(characterSet),
                                    MediaType.APPLICATION_WWW_FORM, NULL, characterSet);
  }

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_FORM_H_
