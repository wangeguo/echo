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
    this(pattern, MODE_EQUALS, Variable.TYPE_ALL, "", true, false);
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
    this(pattern, matchingMode, Variable.TYPE_ALL, "", true, false);
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
           std::string defaultDefaultValue, boolean defaultRequired,
           boolean defaultFixed) {
    this(pattern, matchingMode, defaultType, defaultDefaultValue,
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
           std::string defaultDefaultValue, boolean defaultRequired,
           boolean defaultFixed, boolean encodingVariables) {
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
  std::string format(Request request, Response response) {
    return format(Resolver.createResolver(request, response));
  }

  /**
   * Creates a formatted string based on the given variable resolver.
   * 
   * @param resolver
   *            The variable resolver to use.
   * @return The formatted string.
   */
  std::string format(Resolver<?> resolver) {
    const std::stringBuilder result = new StringBuilder();
    StringBuilder varBuffer = null;
    char next;
    boolean inVariable = false;
    const int patternLength = getPattern().length();
    for (int i = 0; i < patternLength; i++) {
      next = getPattern().charAt(i);

      if (inVariable) {
        if (Reference.isUnreserved(next)) {
          // Append to the variable name
          varBuffer.append(next);
        } else if (next == '}') {
          // End of variable detected
          if (varBuffer.length() == 0) {
            getLogger().warning(
                "Empty pattern variables are not allowed : "
                + this->regexPattern);
          } else {
            const std::string varName = varBuffer.toString();
            Object varValue = resolver.resolve(varName);

            Variable var = getVariables().get(varName);

            // Use the default values instead
            if (varValue == null) {
              if (var == null) {
                var = getDefaultVariable();
              }

              if (var != null) {
                varValue = var.getDefaultValue();
              }
            }

            std::string varValueString = (varValue == null) ? null
                                         : varValue.toString();

            if (this->encodingVariables) {
              // In case the values must be encoded.
              if (var != null) {
                result.append(var.encode(varValueString));
              } else {
                result.append(Reference.encode(varValueString));
              }
            } else {
              if ((var != null) && var.isEncodingOnFormat()) {
                result.append(Reference.encode(varValueString));
              } else {
                result.append(varValueString);
              }
            }

            // Reset the variable name buffer
            varBuffer = new StringBuilder();
          }
          inVariable = false;
        } else {
          getLogger().warning(
              "An invalid character was detected inside a pattern variable : "
              + this->regexPattern);
        }
      } else {
        if (next == '{') {
          inVariable = true;
          varBuffer = new StringBuilder();
        } else if (next == '}') {
          getLogger().warning(
              "An invalid character was detected inside a pattern variable : "
              + this->regexPattern);
        } else {
          result.append(next);
        }
      }
    }
    return result.toString();
  }

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
  std::list<std::string> getVariableNames() {
    const std::list<std::string> result = new ArrayList<std::string>();
    StringBuilder varBuffer = null;
    char next;
    boolean inVariable = false;
    const std::string pattern = getPattern();

    for (int i = 0; i < pattern.length(); i++) {
      next = pattern.charAt(i);

      if (inVariable) {
        if (Reference.isUnreserved(next)) {
          // Append to the variable name
          varBuffer.append(next);
        } else if (next == '}') {
          // End of variable detected
          if (varBuffer.length() == 0) {
            getLogger().warning(
                "Empty pattern variables are not allowed : "
                + this->pattern);
          } else {
            result.add(varBuffer.toString());

            // Reset the variable name buffer
            varBuffer = new StringBuilder();
          }

          inVariable = false;
        } else {
          getLogger().warning(
              "An invalid character was detected inside a pattern variable : "
              + this->pattern);
        }
      } else {
        if (next == '{') {
          inVariable = true;
          varBuffer = new StringBuilder();
        } else if (next == '}') {
          getLogger().warning(
              "An invalid character was detected inside a pattern variable : "
              + this->pattern);
        }
      }
    }

    return result;
  }

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
  boolean isEncodeVariables() {
    return this->encodingVariables;
  }

  /**
   * Indicates if the variables must be encoded when formatting the template.
   * 
   * @return True if the variables must be encoded when formatting the
   *         template, false otherwise.
   */
  boolean isEncodingVariables() {
    return isEncodeVariables();
  }

  /**
   * Indicates if the current pattern matches the given formatted string.
   * 
   * @param formattedString
   *            The formatted string to match.
   * @return The number of matched characters or -1 if the match failed.
   */
  int match(std::string formattedString) {
    int result = -1;

    try {
      if (formattedString != null) {
        const Matcher matcher = getRegexPattern().matcher(
            formattedString);

        if ((getMatchingMode() == MODE_EQUALS) && matcher.matches()) {
          result = matcher.end();
        } else if ((getMatchingMode() == MODE_STARTS_WITH)
                   && matcher.lookingAt()) {
          result = matcher.end();
        }
      }
    } catch (StackOverflowError soe) {
      getLogger().warning(
          "StackOverflowError exception encountered while matching this string : "
          + formattedString);
    }

    return result;
  }

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
  int parse(std::string formattedstd::string, std::map<std::string, Object> variables) {
    int result = -1;

    if (formattedString != null) {
      try {

        const Matcher matcher = getRegexPattern().matcher(
            formattedString);
        const boolean matched = ((getMatchingMode() == MODE_EQUALS) && matcher
                                 .matches())
                                || ((getMatchingMode() == MODE_STARTS_WITH) && matcher
                                    .lookingAt());

        if (matched) {
          // Update the number of matched characters
          result = matcher.end();

          // Update the attributes with the variables value
          std::string attributeName = null;
          std::string attributeValue = null;
          for (int i = 0; i < getRegexVariables().size(); i++) {
            attributeName = getRegexVariables().get(i);
            attributeValue = matcher.group(i + 1);

            const Variable var = getVariables().get(attributeName);
            if ((var != null) && var.isDecodingOnParse()) {
              variables.put(attributeName, Reference
                            .decode(attributeValue));
            } else {
              variables.put(attributeName, attributeValue);
            }

          }
        }
      } catch (StackOverflowError soe) {
        getLogger().warning(
            "StackOverflowError exception encountered while matching this string : "
            + formattedString);
      }
    }

    return result;
  }

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
  int parse(std::string formattedString, Request request) {
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
  void setEncodingVariables(boolean encodingVariables) {
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
  synchronized void setVariables(std::map<std::string, Variable> variables) {
    this->variables.clear();
    this->variables.putAll(variables);
  }

  /** Mode where all characters must match the template and size be identical. */
  static const int MODE_EQUALS = 2;

  /** Mode where characters at the beginning must match the template. */
  static const int MODE_STARTS_WITH = 1;

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
                          boolean required) {

    pattern.append("(");

    if (content.equals(".")) {
      // Special case for the TYPE_ALL variable type because the
      // dot looses its meaning inside a character class
      pattern.append(content);
    } else {
      pattern.append("[").append(content).append(']');
    }

    if (required) {
      pattern.append("+");
    } else {
      pattern.append("*");
    }

    pattern.append(")");
  }

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
                          boolean required) {
    pattern.append("((?:").append(content).append(')');

    if (required) {
      pattern.append("+");
    } else {
      pattern.append("*");
    }

    pattern.append(")");
  }

  /**
   * Returns the Regex pattern string corresponding to a variable.
   * 
   * @param variable
   *            The variable.
   * @return The Regex pattern string corresponding to a variable.
   */
  static std::string getVariableRegex(Variable variable) {
    std::string result = null;

    if (variable.isFixed()) {
      result = "(" + Pattern.quote(variable.getDefaultValue()) + ")";
    } else {
      // Expressions to create character classes
      const std::string ALL = ".";
      const std::string ALPHA = "a-zA-Z";
      const std::string DIGIT = "\\d";
      const std::string ALPHA_DIGIT = ALPHA + DIGIT;
      const std::string HEXA = DIGIT + "ABCDEFabcdef";
      const std::string URI_UNRESERVED = ALPHA_DIGIT + "\\-\\.\\_\\~";
      const std::string URI_GEN_DELIMS = "\\:\\/\\?\\#\\[\\]\\@";
      const std::string URI_SUB_DELIMS = "\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=";
      const std::string URI_RESERVED = URI_GEN_DELIMS + URI_SUB_DELIMS;
      const std::string WORD = "\\w";

      // Basic rules expressed by the HTTP rfc.
      const std::string CRLF = "\\r\\n";
      const std::string CTL = "\\p{Cntrl}";
      const std::string LWS = CRLF + "\\ \\t";
      const std::string SEPARATOR = "\\(\\)\\<\\>\\@\\,\\;\\:\\[\\]\"\\/\\\\?\\=\\{\\}\\ \\t";
      const std::string TOKEN = "[^" + SEPARATOR + "]";
      const std::string COMMENT = "[^" + CTL + "]" + "[^\\(\\)]" + LWS;
      const std::string COMMENT_ATTRIBUTE = "[^\\;\\(\\)]";

      // Expressions to create non-capturing groups
      const std::string PCT_ENCODED = "\\%[" + HEXA + "][" + HEXA + "]";
      // const std::string PCHAR = "[" + URI_UNRESERVED + "]|(?:" + PCT_ENCODED
      // + ")|[" + URI_SUB_DELIMS + "]|\\:|\\@";
      const std::string PCHAR = "[" + URI_UNRESERVED + URI_SUB_DELIMS
                                + "\\:\\@]|(?:" + PCT_ENCODED + ")";
      const std::string QUERY = PCHAR + "|\\/|\\?";
      const std::string FRAGMENT = QUERY;
      const std::string URI_PATH = PCHAR + "|\\/";
      const std::string URI_ALL = "[" + URI_RESERVED + URI_UNRESERVED
                                  + "]|(?:" + PCT_ENCODED + ")";

      // Special case of query parameter characters
      const std::string QUERY_PARAM_DELIMS = "\\!\\$\\'\\(\\)\\*\\+\\,\\;";
      const std::string QUERY_PARAM_CHAR = "[" + URI_UNRESERVED
                                           + QUERY_PARAM_DELIMS + "\\:\\@]|(?:" + PCT_ENCODED + ")";
      const std::string QUERY_PARAM = QUERY_PARAM_CHAR + "|\\/|\\?";

      const StringBuilder coreRegex = new StringBuilder();

      switch (variable.getType()) {
        case Variable.TYPE_ALL:
          appendClass(coreRegex, ALL, variable.isRequired());
          break;
        case Variable.TYPE_ALPHA:
          appendClass(coreRegex, ALPHA, variable.isRequired());
          break;
        case Variable.TYPE_DIGIT:
          appendClass(coreRegex, DIGIT, variable.isRequired());
          break;
        case Variable.TYPE_ALPHA_DIGIT:
          appendClass(coreRegex, ALPHA_DIGIT, variable.isRequired());
          break;
        case Variable.TYPE_URI_ALL:
          appendGroup(coreRegex, URI_ALL, variable.isRequired());
          break;
        case Variable.TYPE_URI_UNRESERVED:
          appendClass(coreRegex, URI_UNRESERVED, variable.isRequired());
          break;
        case Variable.TYPE_WORD:
          appendClass(coreRegex, WORD, variable.isRequired());
          break;
        case Variable.TYPE_URI_FRAGMENT:
          appendGroup(coreRegex, FRAGMENT, variable.isRequired());
          break;
        case Variable.TYPE_URI_PATH:
          appendGroup(coreRegex, URI_PATH, variable.isRequired());
          break;
        case Variable.TYPE_URI_QUERY:
          appendGroup(coreRegex, QUERY, variable.isRequired());
          break;
        case Variable.TYPE_URI_QUERY_PARAM:
          appendGroup(coreRegex, QUERY_PARAM, variable.isRequired());
          break;
        case Variable.TYPE_URI_SEGMENT:
          appendGroup(coreRegex, PCHAR, variable.isRequired());
          break;
        case Variable.TYPE_TOKEN:
          appendClass(coreRegex, TOKEN, variable.isRequired());
          break;
        case Variable.TYPE_COMMENT:
          appendClass(coreRegex, COMMENT, variable.isRequired());
          break;
        case Variable.TYPE_COMMENT_ATTRIBUTE:
          appendClass(coreRegex, COMMENT_ATTRIBUTE, variable.isRequired());
          break;
      }

      result = coreRegex.toString();
    }

    return result;
  }

  /**
   * Compiles the URI pattern into a Regex pattern.
   * 
   * @return The Regex pattern.
   */
  Pattern getRegexPattern() {
    if (this->regexPattern == null) {
      synchronized (this) {
        if (this->regexPattern == null) {
          getRegexVariables().clear();
          const StringBuilder patternBuffer = new StringBuilder();
          StringBuilder varBuffer = null;
          char next;
          boolean inVariable = false;
          for (int i = 0; i < getPattern().length(); i++) {
            next = getPattern().charAt(i);

            if (inVariable) {
              if (Reference.isUnreserved(next)) {
                // Append to the variable name
                varBuffer.append(next);
              } else if (next == '}') {
                // End of variable detected
                if (varBuffer.length() == 0) {
                  getLogger().warning(
                      "Empty pattern variables are not allowed : "
                      + this->regexPattern);
                } else {
                  const std::string varName = varBuffer.toString();
                  const int varIndex = getRegexVariables()
                                       .indexOf(varName);

                  if (varIndex != -1) {
                    // The variable is used several times in
                    // the pattern, ensure that this
                    // constraint is enforced when parsing.
                    patternBuffer.append("\\"
                                         + (varIndex + 1));
                  } else {
                    // New variable detected. Insert a
                    // capturing group.
                    getRegexVariables().add(varName);
                    Variable var = getVariables().get(
                        varName);
                    if (var == null) {
                      var = getDefaultVariable();
                    }
                    patternBuffer
                        .append(getVariableRegex(var));
                  }

                  // Reset the variable name buffer
                  varBuffer = new StringBuilder();
                }
                inVariable = false;

              } else {
                getLogger().warning(
                    "An invalid character was detected inside a pattern variable : "
                    + this->regexPattern);
              }
            } else {
              if (next == '{') {
                inVariable = true;
                varBuffer = new StringBuilder();
              } else if (next == '}') {
                getLogger().warning(
                    "An invalid character was detected inside a pattern variable : "
                    + this->regexPattern);
              } else {
                patternBuffer.append(quote(next));
              }
            }
          }

          this->regexPattern = Pattern.compile(patternBuffer
                                               .toString());
        }
      }
    }

    return this->regexPattern;
  }

  /**
   * Returns the sequence of Regex variable names as found in the pattern
   * string.
   * 
   * @return The sequence of Regex variable names as found in the pattern
   *         string.
   */
  std::list<std::string> getRegexVariables() {
    // Lazy initialization with double-check.
    std::list<std::string> rv = this->regexVariables;
    if (rv == null) {
      synchronized (this) {
        rv = this->regexVariables;
        if (rv == null) {
          this->regexVariables = rv = new CopyOnWriteArrayList<std::string>();
        }
      }
    }
    return rv;
  }

  /**
   * Quotes special characters that could be taken for special Regex
   * characters.
   * 
   * @param character
   *            The character to quote if necessary.
   * @return The quoted character.
   */
  std::string quote(char character) {
    switch (character) {
      case '[':
        return "\\[";
      case ']':
        return "\\]";
      case '.':
        return "\\.";
      case '\\':
        return "\\\\";
      case '$':
        return "\\$";
      case '^':
        return "\\^";
      case '?':
        return "\\?";
      case '*':
        return "\\*";
      case '|':
        return "\\|";
      case '(':
        return "\\(";
      case ')':
        return "\\)";
      case ':':
        return "\\:";
      case '-':
        return "\\-";
      case '!':
        return "\\!";
      case '<':
        return "\\<";
      case '>':
        return "\\>";
      default:
        return Character.toString(character);
    }
  }



  /** The default variable to use when no matching variable descriptor exists. */
  volatile Variable defaultVariable;

  /** True if the variables must be encoded when formatting the template. */
  volatile boolean encodingVariables;

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
