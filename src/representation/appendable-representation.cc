#include <echo/representation/appendable-representation.h>

namespace echo {
namespace representation {

Appendable AppendableRepresentation::append(char c) throws IOException {
  if (this->appendableText == NULL) {
    this->appendableText = new StringBuilder(c);
  } else {
    this->appendableText.append(c);
  }

  return this;
}

Appendable AppendableRepresentation::append(CharSequence csq) throws IOException {
  if (this->appendableText == NULL) {
    this->appendableText = new StringBuilder(csq);
  } else {
    this->appendableText.append(csq);
  }

  return this;
}

Appendable AppendableRepresentation::append(CharSequence csq, int start, int end)
    throws IOException {
  if (this->appendableText == NULL) {
    this->appendableText = new StringBuilder();
  }

  this->appendableText.append(csq, start, end);

  return this;
}

void AppendableRepresentation::setText(CharSequence text) {
  if (text != NULL) {
    if (this->appendableText == NULL) {
      this->appendableText = new StringBuilder(text);
    } else {
      this->appendableText.delete(0, this->appendableText.length());
      this->appendableText.append(text);
    }
  } else {
    this->appendableText = NULL;
  }
}

} // namespace representation
} // namespace echo


