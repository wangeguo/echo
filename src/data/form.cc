#include <echo/data/form.h>

namespace echo {
namespace data {

Series<Parameter> Form::createSeries(std::list<Parameter> delegate) {
  if (delegate != NULL) {
    return new Form(delegate);
  }

  return new Form();
}

std::string Form::encode(CharacterSet characterSet, char separator)
    throws IOException {
  const StringBuilder sb = new StringBuilder();
  for (int i = 0; i < size(); i++) {
    if (i > 0) {
      sb.append(separator);
    }
    get(i).encode(sb, characterSet);
  }

  return sb.toString();
}

std::string Form::getMatrixString(CharacterSet characterSet) {
  try {
    return encode(characterSet, ';');
  } catch (IOException ioe) {
    return NULL;
  }
}

std::string Form::getQueryString(CharacterSet characterSet) {
  try {
    return encode(characterSet);
  } catch (IOException ioe) {
    return NULL;
  }
}

} // namespace data
} // namespace echo
