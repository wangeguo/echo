#include <echo/data/parameter.h>

namespace echo {
namespace data {

Parameter Parameter::create(CharSequence name, CharSequence value) {
  if (value != NULL) {
    return new Parameter(name.toString(), value.toString());
  }
  return new Parameter(name.toString(), NULL);
}

void Parameter::encode(Appendable buffer, CharacterSet characterSet)
    throws IOException {
  if (getName() != NULL) {
    buffer.append(Reference.encode(getName(), characterSet));

    if (getValue() != NULL) {
      buffer.append('=');
      buffer.append(Reference.encode(getValue(), characterSet));
    }
  }
}

std::string Parameter::encode(CharacterSet characterSet) throws IOException {
  const StringBuilder sb = new StringBuilder();
  encode(sb, characterSet);
  return sb.toString();
}

} // namespace data
} // namespace echo
