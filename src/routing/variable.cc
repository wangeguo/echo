#include <echo/routing/variable.h>

namespace echo {
namespace routing {

Variable::Variable(int type, std::string defaultValue, bool required,
                   bool fixed, bool decodingOnParse, bool encodingOnFormat) {
  this->type = type;
  this->defaultValue = defaultValue;
  this->required = required;
  this->fixed = fixed;
  this->decodingOnParse = decodingOnParse;
  this->encodingOnFormat = encodingOnFormat;
}

std::string Variable::encode(std::string value) {
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

static const int Variable::TYPE_ALL(1);
static const int Variable::TYPE_ALPHA(2);
static const int Variable::TYPE_ALPHA_DIGIT(3);
static const int Variable::TYPE_COMMENT(4);
static const int Variable::TYPE_COMMENT_ATTRIBUTE(5);
static const int Variable::TYPE_DIGIT(6);
static const int Variable::TYPE_TOKEN(7);
static const int Variable::TYPE_URI_ALL(8);
static const int Variable::TYPE_URI_FRAGMENT(9);
static const int Variable::TYPE_URI_PATH(10);
static const int Variable::TYPE_URI_QUERY(11);
static const int Variable::TYPE_URI_QUERY_PARAM(12);
static const int Variable::TYPE_URI_SCHEME(13);
static const int Variable::TYPE_URI_SEGMENT(14);
static const int Variable::TYPE_URI_UNRESERVED(15);
static const int Variable::TYPE_WORD(16);

} // namespace routing
} // echo

