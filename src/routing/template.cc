#include <echo/routing/template.h>

namespace echo {
namespace routing {

Template::Template(std::string pattern, int matchingMode, int defaultType,
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

std::string Template::format(Resolver<?> resolver) {
  const std::stringBuilder result = new StringBuilder();
  StringBuilder varBuffer = null;
  char next;
  bool inVariable = false;
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

std::list<std::string> Template::getVariableNames() {
  const std::list<std::string> result = new ArrayList<std::string>();
  StringBuilder varBuffer = null;
  char next;
  bool inVariable = false;
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

int Template::match(std::string formattedString) {
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

int Template::parse(std::string formattedString, std::map<std::string, Object> variables) {
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

void Template::setVariables(std::map<std::string, Variable> variables) {
  this->variables.clear();
  this->variables.putAll(variables);
}

static void Template::appendClass(StringBuilder pattern, std::string content,
                                  bool required) {

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

static void Template::appendGroup(StringBuilder pattern, std::string content,
                                  bool required) {
  pattern.append("((?:").append(content).append(')');

  if (required) {
    pattern.append("+");
  } else {
    pattern.append("*");
  }

  pattern.append(")");
}

static std::string Template::getVariableRegex(Variable variable) {
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

Pattern Template::getRegexPattern() {
  if (this->regexPattern == null) {
    synchronized (this) {
      if (this->regexPattern == null) {
        getRegexVariables().clear();
        const StringBuilder patternBuffer = new StringBuilder();
        StringBuilder varBuffer = null;
        char next;
        bool inVariable = false;
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

std::list<std::string> Template::getRegexVariables() {
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

std::string Template::quote(char character) {
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

static const int MODE_EQUALS(2);
static const int MODE_STARTS_WITH(1);

} // namespace routing
} // namespace echo

