#include <echo/data/digest.h>

namespace echo {
namespace data {

const std::string Digest::ALGORITHM_MD2("MD2");
const std::string Digest::ALGORITHM_MD5("MD5");
const std::string Digest::ALGORITHM_NONE("NONE");
const std::string Digest::ALGORITHM_SHA_1("SHA-1");
const std::string Digest::ALGORITHM_SHA_256("SHA-256");
const std::string Digest::ALGORITHM_SHA_384("SHA-384");
const std::string Digest::ALGORITHM_SHA_512("SHA-512");
const std::string Digest::ALGORITHM_HTTP_DIGEST("HTTP-DIGEST-A1");

Digest::Digest(std::string algorithm, byte[] value) {
  this->algorithm = algorithm;

  // In Java 6, use Arrays.copyOf.
  this->value = new byte[value.length];
  for (int i = 0; i < value.length; i++) {
    this->value[i] = value[i];
  }
}

bool Digest::equals(Object obj) {
  bool result = (obj instanceof Digest);

  if (result) {
    Digest d = (Digest) obj;
    result = getAlgorithm().equals(d.getAlgorithm());
    result = result && Arrays.equals(getValue(), d.getValue());
  }
  return result;
}

byte[] Digest::getValue() {
  // In Java 6, use Arrays.copyOf.
  byte[] result = new byte[this->value.length];
  for (int i = 0; i < this->value.length; i++) {
    result[i] = this->value[i];
  }

  return result;
}

} // namespace data
} // namespace echo
