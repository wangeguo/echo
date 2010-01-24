#ifndef _ECHO_ROUTING_VARIABLE_H_
#define _ECHO_ROUTING_VARIABLE_H_

#include <string>
#include <echo/data/reference.h>

namespace echo {
namespace routing {

/**
 * Variable descriptor for reference templates.
 * 
 * @see Template
 * @author Jerome Louvel
 */
//public final class Variable {
class Variable {

 public:
  /**
   * Default constructor. Type is TYPE_ALL, default value is "", required is
   * true and fixed is false.
   */
  Variable() {
    Variable(Variable.TYPE_ALL, "", true, false);
  }

  /**
   * Constructor. Default value is "", required is true and fixed is false.
   * 
   * @param type
   *            The type of variable. See TYPE_* constants.
   */
  Variable(int type) {
    Variable(type, "", true, false);
  }

  /**
   * Constructor.
   * 
   * @param type
   *            The type of variable. See TYPE_* constants.
   * @param defaultValue
   *            The default value to use if the key couldn't be found in the
   *            model.
   * @param required
   *            Indicates if the variable is required or optional.
   * @param fixed
   *            Indicates if the value is fixed, in which case the
   *            "defaultValue" property is always used.
   */
  Variable(int type, std::string defaultValue, bool required,
           bool fixed) {
    Variable(type, defaultValue, required, fixed, false, false);
  }

  /**
   * Constructor.
   * 
   * @param type
   *            The type of variable. See TYPE_* constants.
   * @param defaultValue
   *            The default value to use if the key couldn't be found in the
   *            model.
   * @param required
   *            Indicates if the variable is required or optional.
   * @param fixed
   *            Indicates if the value is fixed, in which case the
   *            "defaultValue" property is always used.
   * @param decodingOnParse
   *            Indicates if the parsed value must be decoded.
   * @param encodingOnFormat
   *            Indicates if the formatted value must be encoded.
   */
  Variable(int type, std::string defaultValue, bool required,
           bool fixed, bool decodingOnParse, bool encodingOnFormat) {
    this->type = type;
    this->defaultValue = defaultValue;
    this->required = required;
    this->fixed = fixed;
    this->decodingOnParse = decodingOnParse;
    this->encodingOnFormat = encodingOnFormat;
  }

  /**
   * According to the type of the variable, encodes the value given in
   * parameters.
   * 
   * @param value
   *            The value to encode.
   * @return The encoded value, according to the variable type.
   */
  std::string encode(std::string value) {
    switch (type) {
      case Variable.TYPE_URI_ALL:
        return Reference.encode(value);
      case Variable.TYPE_URI_UNRESERVED:
        return Reference.encode(value);
      case Variable.TYPE_URI_FRAGMENT:
        return Reference.encode(value);
      case Variable.TYPE_URI_PATH:
        return Reference.encode(value);
      case Variable.TYPE_URI_QUERY:
        return Reference.encode(value);
      case Variable.TYPE_URI_SEGMENT:
        return Reference.encode(value);
      default:
        return value;
    }
  }

  /**
   * Returns the default value to use if the key couldn't be found in the
   * model.
   * 
   * @return The default value to use if the key couldn't be found in the
   *         model.
   */
  std::string getDefaultValue() {
    return defaultValue;
  }

  /**
   * Returns the type of variable. See TYPE_* constants.
   * 
   * @return The type of variable. See TYPE_* constants.
   */
  int getType() {
    return type;
  }

  /**
   * Indicates if the parsed value must be decoded.
   * 
   * @return True if the parsed value must be decoded, false otherwise.
   * @deprecated Use {@link #isDecodingOnParse()} instead.
   */
  //@Deprecated
  bool isDecodedOnParse() {
    return decodingOnParse;
  }

  /**
   * Indicates if the parsed value must be decoded.
   * 
   * @return True if the parsed value must be decoded, false otherwise.
   */
  bool isDecodingOnParse() {
    return isDecodedOnParse();
  }

  /**
   * Indicates if the formatted value must be encoded.
   * 
   * @return True if the formatted value must be encoded, false otherwise.
   * @deprecated Use {@link #isEncodingOnFormat()} instead.
   */
  //@Deprecated
  bool isEncodedOnFormat() {
    return encodingOnFormat;
  }

  /**
   * Indicates if the formatted value must be encoded.
   * 
   * @return True if the formatted value must be encoded, false otherwise.
   */
  bool isEncodingOnFormat() {
    return isEncodedOnFormat();
  }

  /**
   * Returns true if the value is fixed, in which case the "defaultValue"
   * property is always used.
   * 
   * @return True if the value is fixed, in which case the "defaultValue"
   *         property is always used.
   */
  bool isFixed() {
    return fixed;
  }

  /**
   * Returns true if the variable is required or optional.
   * 
   * @return True if the variable is required or optional.
   */
  bool isRequired() {
    return required;
  }

  /**
   * Indicates if the parsed value must be decoded.
   * 
   * @param decodingOnParse
   *            True if the parsed value must be decoded, false otherwise.
   * @deprecated Use {@link #setDecodingOnParse(bool)} instead.
   */
  @Deprecated
  void setDecodedOnParse(bool decodingOnParse) {
    this->decodingOnParse = decodingOnParse;
  }

  /**
   * Indicates if the parsed value must be decoded.
   * 
   * @param decodingOnParse
   *            True if the parsed value must be decoded, false otherwise.
   */
  void setDecodingOnParse(bool decodingOnParse) {
    setDecodedOnParse(decodingOnParse);
  }

  /**
   * Sets the default value to use if the key couldn't be found in the model.
   * 
   * @param defaultValue
   *            The default value to use if the key couldn't be found in the
   *            model.
   */
  void setDefaultValue(std::string defaultValue) {
    this->defaultValue = defaultValue;
  }

  /**
   * Indicates if the formatted value must be encoded.
   * 
   * @param encodingOnFormat
   *            True if the formatted value must be encoded, false otherwise.
   * @deprecated Use {@link #setEncodingOnFormat(bool)} instead.
   */
  @Deprecated
  void setEncodedOnFormat(bool encodingOnFormat) {
    this->encodingOnFormat = encodingOnFormat;
  }

  /**
   * Indicates if the formatted value must be encoded.
   * 
   * @param encodingOnFormat
   *            True if the formatted value must be encoded, false otherwise.
   */
  void setEncodingOnFormat(bool encodingOnFormat) {
    setEncodedOnFormat(encodingOnFormat);
  }

  /**
   * Indicates if the value is fixed
   * 
   * @param fixed
   *            True if the value is fixed
   */
  void setFixed(bool fixed) {
    this->fixed = fixed;
  }

  /**
   * Indicates if the variable is required or optional.
   * 
   * @param required
   *            True if the variable is required or optional.
   */
  void setRequired(bool required) {
    this->required = required;
  }

  /**
   * Sets the type of variable. See TYPE_* constants.
   * 
   * @param type
   *            The type of variable.
   */
  void setType(int type) {
    this->type = type;
  }

 public:
  /** Matches all characters. */
  static const int TYPE_ALL = 1;

  /** Matches all alphabetical characters. */
  static const int TYPE_ALPHA = 2;

  /** Matches all alphabetical and digital characters. */
  static const int TYPE_ALPHA_DIGIT = 3;

  /** Matches any TEXT excluding "(" and ")". */
  static const int TYPE_COMMENT = 4;

  /** Matches any TEXT inside a comment excluding ";". */
  static const int TYPE_COMMENT_ATTRIBUTE = 5;

  /** Matches all digital characters. */
  static const int TYPE_DIGIT = 6;

  /** Matches any CHAR except CTLs or separators. */
  static const int TYPE_TOKEN = 7;

  /** Matches all URI characters. */
  static const int TYPE_URI_ALL = 8;

  /** Matches URI fragment characters. */
  static const int TYPE_URI_FRAGMENT = 9;

  /** Matches URI path characters (not the query or the fragment parts). */
  static const int TYPE_URI_PATH = 10;

  /** Matches URI query characters. */
  static const int TYPE_URI_QUERY = 11;

  /** Matches URI query parameter characters (name or value). */
  static const int TYPE_URI_QUERY_PARAM = 12;

  /** Matches URI scheme characters. */
  static const int TYPE_URI_SCHEME = 13;

  /** Matches URI segment characters. */
  static const int TYPE_URI_SEGMENT = 14;

  /** Matches unreserved URI characters. */
  static const int TYPE_URI_UNRESERVED = 15;

  /** Matches all alphabetical and digital characters plus the underscore. */
  static const int TYPE_WORD = 16;

 private:
  /** Indicates if the parsed value must be decoded. */
  volatile bool decodingOnParse;

  /** The default value to use if the key couldn't be found in the model. */
  volatile std::string defaultValue;

  /** Indicates if the formatted value must be encoded. */
  volatile bool encodingOnFormat;

  /**
   * Indicates if the value is fixed, in which case the "defaultValue"
   * property is always used.
   */
  volatile bool fixed;

  /** Indicates if the variable is required or optional. */
  volatile bool required;

  /** The type of variable. See TYPE_* constants. */
  volatile int type;

};

} // namespace routing
} // echo

#endif // _ECHO_ROUTING_VARIABLE_H_
