#include <echo/data/preference.h>

namespace echo {
namespace data {

template<Metadata T>
Preference<T>::Preference(T metadata, float quality, Series<Parameter> parameters) {
  this->metadata = metadata;
  this->quality = quality;
  this->parameters = parameters;
}

template<Metadata T>
Series<Parameter> Preference<T>::getParameters() {
  // Lazy initialization with double-check.
  Series<Parameter> p = this->parameters;
  if (p == NULL) {
    synchronized (this) {
      p = this->parameters;
      if (p == NULL) {
        this->parameters = p = new Form();
      }
    }
  }
  return p;
}

template<Metadata T>
std::string Preference<T>::toString() {
  return (getMetadata() == NULL) ? ""
      : (getMetadata().getName() + ":" + getQuality());
}

} // namespace data
} // namespace echo
