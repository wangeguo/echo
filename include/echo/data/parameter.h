#ifndef _ECHO_DATA_PARAMETER_H_
#define _ECHO_DATA_PARAMETER_H_

/*
  import java.io.IOException;
*/
#include <string>
#include <echo/util/couple.h>

namespace echo {
namespace data {

/**
 * Multi-usage parameter. Note that the name and value properties are thread
 * safe, stored in volatile members.
 * 
 * @author Jerome Louvel
 */
/*public class Parameter extends Couple<String, String> implements
  Comparable<Parameter> {*/

class Parameter : public echo::util::Couple<std::string, std::string>
{

 public:

  /**
   * Default constructor.
   */
  Parameter() {
    Parameter(NULL, NULL);
  }

  /**
   * Creates a parameter.
   * 
   * @param name
   *            The parameter name buffer.
   * @param value
   *            The parameter value buffer (can be null).
   * @return The created parameter.
   * @throws IOException
   */
  static Parameter create(CharSequence name, CharSequence value);

  /**
   * Preferred constructor.
   * 
   * @param name
   *            The name.
   * @param value
   *            The value.
   */
  Parameter(std::string name, std::string value) {
    Couple(name, value);
  }

  /**
   * Compares this object with the specified object for order.
   * 
   * @param o
   *            The object to be compared.
   * @return A negative integer, zero, or a positive integer as this object is
   *         less than, equal to, or greater than the specified object.
   */
  int compareTo(Parameter o) {
    return getName().compareTo(o.getName());
  }

  /**
   * Encodes the parameter and appends the result to the given buffer. Uses
   * the standard URI encoding mechanism.
   * 
   * @param buffer
   *            The buffer to append.
   * @param characterSet
   *            The supported character encoding
   * @throws IOException
   */
  void encode(Appendable buffer, CharacterSet characterSet) throws IOException;

  /**
   * Encodes the parameter using the standard URI encoding mechanism.
   * 
   * @param characterSet
   *            The supported character encoding.
   * @return The encoded string.
   * @throws IOException
   */
  std::string encode(CharacterSet characterSet) throws IOException;

  /**
   * Returns the name of this parameter.
   * 
   * @return The name of this parameter.
   */
  std::string getName() {
    return getFirst();
  }

  /**
   * Returns the value.
   * 
   * @return The value.
   */
  std::string getValue() {
    return getSecond();
  }

  /**
   * Sets the name.
   * 
   * @param name
   *            The name.
   */
  void setName(std::string name) {
    setFirst(name);
  }

  /**
   * Sets the value.
   * 
   * @param value
   *            The value.
   */
  void setValue(std::string value) {
    setSecond(value);
  }

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_PARAMETER_H_
