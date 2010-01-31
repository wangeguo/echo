#ifndef _ECHO_ROUTING_TEMPLATE_H_
#define _ECHO_ROUTING_TEMPLATE_H_

/*
  import java.util.ArrayList;
  import java.util.concurrent.ConcurrentHashMap;
  import java.util.concurrent.CopyOnWriteArrayList;
  import java.util.regex.Matcher;
  import java.util.regex.Pattern;
*/

#include <list>
#include <map>
#include <string>

#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/data/reference.h>
#include <echo/util/resolver.h>
#include <echo/util/logging/logger.h>

namespace echo {
namespace routing {

/**
 * String template with a pluggable model. Supports both formatting and parsing.
 * The template variables can be inserted using the "{name}" syntax and
 * described using the modifiable map of variable descriptors. When no
 * descriptor is found for a given variable, the template logic uses its default
 * variable property initialized using the default {@link Variable} constructor.<br>
 * <br>
 * Note that the variable descriptors can be changed before the first parsing or
 * matching call. After that point, changes won't be taken into account.<br>
 * <br>
 * Format and parsing methods are specially available to deal with requests and
 * response. See {@link #format(Request, Response)} and
 * {@link #parse(std::string, Request)}.
 * 
 * @see Resolver
 * @see <a href="http://code.google.com/p/uri-templates/">URI Template
 *      specification</a>
 * @author Jerome Louvel
 */
class Template {

 public:
  /**
   * Default constructor. Each variable matches any sequence of characters by
   * default. When parsing, the template will attempt to match the whole
   * template. When formatting, the variable are replaced by an empty string
   * if they don't exist in the model.
   * 
   * @param pattern
   *            The pattern to use for formatting or parsing.
   */
  Template(std::string pattern) {
    Template(pattern, MODE_EQUALS, Variable.TYPE_ALL, "", true, false);
  }

  /**
   * Constructor.
   * 
   * @param pattern
   *            The pattern to use for formatting or parsing.
   * @param matchingMode
   *            The matching mode to use when parsing a formatted reference.
   */
  Template(std::string pattern, int matchingMode) {
    Template(pattern, matchingMode, Variable.TYPE_ALL, "", true, false);
  }

  /**
   * Constructor.
   * 
   * @param pattern
   *            The pattern to use for formatting or parsing.
   * @param matchingMode
   *            The matching mode to use when parsing a formatted reference.
   * @param defaultType
   *            The default type of variables with no descriptor.
   * @param defaultDefaultValue
   *            The default value for null variables with no descriptor.
   * @param defaultRequired
   *            The default required flag for variables with no descriptor.
   * @param defaultFixed
   *            The default fixed value for variables with no descriptor.
   */
  Template(std::string pattern, int matchingMode, int defaultType,
           std::string defaultDefaultValue, bool defaultRequired,
           bool defaultFixed) {
    Template(pattern, matchingMode, defaultType, defaultDefaultValue,
             defaultRequired, defaultFixed, false);
  }

  /**
   * Constructor.
   * 
   * @param pattern
   *            The pattern to use for formatting or parsing.
   * @param matchingMode
   *            The matching mode to use when parsing a formatted reference.
   * @param defaultType
   *            The default type of variables with no descriptor.
   * @param defaultDefaultValue
   *            The default value for null variables with no descriptor.
   * @param defaultRequired
   *            The default required flag for variables with no descriptor.
   * @param defaultFixed
   *            The default fixed value for variables with no descriptor.
   * @param encodingVariables
   *            True if the variables must be encoded when formatting the
   *            template.
   */
  Template(std::string pattern, int matchingMode, int defaultType,
           std::string defaultDefaultValue, bool defaultRequired,
           bool defaultFixed, bool encodingVariables) {
    this->logger = (logger == null) ? Context.getCurrentLogger() : logger;
    this->pattern = pattern;
    this->defaultVariable = new Variable(defaultType, defaultDefaultValue,
                                         defaultRequired, defaultFixed);
    this->matchingMode = matchingMode;
    this->variables = new ConcurrentHashMap<std::string, Variable>();
    this->regexPattern = null;
    this->encodingVariables = encodingVariables;
  }

  /**
   * Creates a formatted string based on the given map of values.
   * 
   * @param values
   *            The values to use when formatting.
   * @return The formatted string.
   * @see Resolver#createResolver(std::map)
   */
  std::string format(std::map<std::string, ?> values) {
    return format(Resolver.createResolver(values));
  }

  /**
   * Creates a formatted string based on the given request and response.
   * 
   * @param request
   *            The request to use as a model.
   * @param response
   *            The response to use as a model.
   * @return The formatted string.
   * @see Resolver#createResolver(Request, Response)
   */
  std::string format(echo::Request request, echo::Response response) {
    return format(Resolver.createResolver(request, response));
  }

  /**
   * Creates a formatted string based on the given variable resolver.
   * 
   * @param resolver
   *            The variable resolver to use.
   * @return The formatted string.
   */
  std::string format(Resolver<?> resolver); 

  /**
   * Returns the default variable.
   * 
   * @return The default variable.
   */
  Variable getDefaultVariable() {
    return this->defaultVariable;
  }

  /**
   * Returns the logger to use.
   * 
   * @return The logger to use.
   */
  Logger getLogger() {
    return this->logger;
  }

  /**
   * Returns the matching mode to use when parsing a formatted reference.
   * 
   * @return The matching mode to use when parsing a formatted reference.
   */
  int getMatchingMode() {
    return this->matchingMode;
  }

  /**
   * Returns the pattern to use for formatting or parsing.
   * 
   * @return The pattern to use for formatting or parsing.
   */
  std::string getPattern() {
    return this->pattern;
  }


  /**
   * Returns the list of variable names in the template.
   * 
   * @return The list of variable names.
   */
  std::list<std::string> getVariableNames();

  /**
   * Returns the modifiable map of variable descriptors. Creates a new
   * instance if no one has been set. Note that those variables are only
   * descriptors that can influence the way parsing and formatting is done,
   * they don't contain the actual value parsed.
   * 
   * @return The modifiable map of variables.
   */
  synchronized std::map<std::string, Variable> getVariables() {
    return this->variables;
  }

  /**
   * Indicates if the variables must be encoded when formatting the template.
   * 
   * @return True if the variables must be encoded when formatting the
   *         template, false otherwise.
   * @deprecated Use {@link #isEncodingVariables()} instead.
   */
  // @Deprecated
  bool isEncodeVariables() {
    return this->encodingVariables;
  }

  /**
   * Indicates if the variables must be encoded when formatting the template.
   * 
   * @return True if the variables must be encoded when formatting the
   *         template, false otherwise.
   */
  bool isEncodingVariables() {
    return isEncodeVariables();
  }

  /**
   * Indicates if the current pattern matches the given formatted string.
   * 
   * @param formattedString
   *            The formatted string to match.
   * @return The number of matched characters or -1 if the match failed.
   */
  int match(std::string formattedString);

  /**
   * Attempts to parse a formatted reference. If the parsing succeeds, the
   * given request's attributes are updated.<br>
   * Note that the values parsed are directly extracted from the formatted
   * reference and are therefore not percent-decoded.
   * 
   * @see Reference#decode(std::string)
   * 
   * @param formattedString
   *            The string to parse.
   * @param variables
   *            The map of variables to update.
   * @return The number of matched characters or -1 if no character matched.
   */
  int parse(std::string formattedString, std::map<std::string, Object> variables);

  /**
   * Attempts to parse a formatted reference. If the parsing succeeds, the
   * given request's attributes are updated.<br>
   * Note that the values parsed are directly extracted from the formatted
   * reference and are therefore not percent-decoded.
   * 
   * @see Reference#decode(std::string)
   * 
   * @param formattedString
   *            The string to parse.
   * @param request
   *            The request to update.
   * @return The number of matched characters or -1 if no character matched.
   */
  int parse(std::string formattedString, echo::Request request) {
    return parse(formattedString, request.getAttributes());
  }


  /**
   * Sets the variable to use, if no variable is given.
   * 
   * @param defaultVariable
   */
  void setDefaultVariable(Variable defaultVariable) {
    this->defaultVariable = defaultVariable;
  }

  /**
   * Indicates if the variables must be encoded when formatting the template.
   * 
   * @param encodingVariables
   *            True if the variables must be encoded when formatting the
   *            template.
   * @deprecated Use {@link #setEncodingVariables(boolean)} instead.
   */
  //@Deprecated
  void setEncodeVariables(boolean encodingVariables) {
    this->encodingVariables = encodingVariables;
  }

  /**
   * Indicates if the variables must be encoded when formatting the template.
   * 
   * @param encodingVariables
   *            True if the variables must be encoded when formatting the
   *            template.
   */
  void setEncodingVariables(bool encodingVariables) {
    setEncodeVariables(encodingVariables);
  }

  /**
   * Sets the logger to use.
   * 
   * @param logger
   *            The logger to use.
   */
  void setLogger(Logger logger) {
    this->logger = logger;
  }

  /**
   * Sets the matching mode to use when parsing a formatted reference.
   * 
   * @param matchingMode
   *            The matching mode to use when parsing a formatted reference.
   */
  void setMatchingMode(int matchingMode) {
    this->matchingMode = matchingMode;
  }

  /**
   * Sets the pattern to use for formatting or parsing.
   * 
   * @param pattern
   *            The pattern to use for formatting or parsing.
   */
  void setPattern(std::string pattern) {
    this->pattern = pattern;
    this->regexPattern = null;
  }

  /**
   * Sets the modifiable map of variables.
   * 
   * @param variables
   *            The modifiable map of variables.
   */
  synchronized void setVariables(std::map<std::string, Variable> variables);

  /** Mode where all characters must match the template and size be identical. */
  static const int MODE_EQUALS;

  /** Mode where characters at the beginning must match the template. */
  static const int MODE_STARTS_WITH;

 private:
  /**
   * Appends to a pattern a repeating group of a given content based on a
   * class of characters.
   * 
   * @param pattern
   *            The pattern to append to.
   * @param content
   *            The content of the group.
   * @param required
   *            Indicates if the group is required.
   */
  static void appendClass(StringBuilder pattern, std::string content,
                          bool required);

  /**
   * Appends to a pattern a repeating group of a given content based on a
   * non-capturing group.
   * 
   * @param pattern
   *            The pattern to append to.
   * @param content
   *            The content of the group.
   * @param required
   *            Indicates if the group is required.
   */
  static void appendGroup(StringBuilder pattern, std::string content,
                          bool required);

  /**
   * Returns the Regex pattern string corresponding to a variable.
   * 
   * @param variable
   *            The variable.
   * @return The Regex pattern string corresponding to a variable.
   */
  static std::string getVariableRegex(Variable variable);

  /**
   * Compiles the URI pattern into a Regex pattern.
   * 
   * @return The Regex pattern.
   */
  Pattern getRegexPattern();

  /**
   * Returns the sequence of Regex variable names as found in the pattern
   * string.
   * 
   * @return The sequence of Regex variable names as found in the pattern
   *         string.
   */
  std::list<std::string> getRegexVariables();

  /**
   * Quotes special characters that could be taken for special Regex
   * characters.
   * 
   * @param character
   *            The character to quote if necessary.
   * @return The quoted character.
   */
  std::string quote(char character);

  /** The default variable to use when no matching variable descriptor exists. */
  volatile Variable defaultVariable;

  /** True if the variables must be encoded when formatting the template. */
  volatile bool encodingVariables;

  /** The logger to use. */
  volatile Logger logger;

  /** The matching mode to use when parsing a formatted reference. */
  volatile int matchingMode;

  /** The pattern to use for formatting or parsing. */
  volatile std::string pattern;

  /** The internal Regex pattern. */
  volatile Pattern regexPattern;

  /** The sequence of Regex variable names as found in the pattern string. */
  volatile std::list<std::string> regexVariables;

  /** The map of variables associated to the route's template. */
  const std::map<std::string, Variable> variables;

};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_TEMPLATE_H_
