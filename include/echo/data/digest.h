#ifndef _ECHO_DATA_DIGEST_H_
#define _ECHO_DATA_DIGEST_H_

/*
  import java.util.Arrays;
*/
#include <string>

#include <echo/representation/representation.h>

namespace echo {
namespace data {

/**
 * Describes a digest value and the digest algorithm used. Digests can have
 * several use cases such as ensuring the integrity of representations exchanges
 * between resources, or for authentication purpose.
 * 
 * @see Representation#getDigest()
 * @author Jerome Louvel
 */
class Digest {

 public:

  /**
   * Constructor using the MD5 algorithm by default.
   * 
   * @param value
   *            The digest value.
   */
  Digest(byte[] value) {
    Digest(ALGORITHM_MD5, value);
  }

  /**
   * Constructor.
   * 
   * @param algorithm
   *            The digest algorithm.
   * @param value
   *            The digest value.
   */
  Digest(std::string algorithm, byte[] value);

  //@Override
  bool equals(Object obj);

  /**
   * Returns the digest algorithm.
   * 
   * @return The digest algorithm.
   */
  std::string getAlgorithm() {
    return algorithm;
  }

  /**
   * Returns the digest value.
   * 
   * @return The digest value.
   */
  byte[] getValue() {
    // In Java 6, use Arrays.copyOf.
    byte[] result = new byte[this->value.length];
    for (int i = 0; i < this->value.length; i++) {
      result[i] = this->value[i];
    }

    return result;
  }

 public:

  /** Digest algorithm defined in RFC 1319. */
  static const std::string ALGORITHM_MD2;

  /** Digest algorithm defined in RFC 1321. */
  static const std::string ALGORITHM_MD5;

  /** No digest algorithm defined. */
  static const std::string ALGORITHM_NONE;

  /** Digest algorithm defined in Secure Hash Standard, NIST FIPS 180-1. */
  static const std::string ALGORITHM_SHA_1;

  /** NIST approved digest algorithm from SHA-2 family. */
  static const std::string ALGORITHM_SHA_256;

  /** NIST approved digest algorithm from SHA-2 family. */
  static const std::string ALGORITHM_SHA_384;

  /** NIST approved digest algorithm from SHA-2 family. */
  static const std::string ALGORITHM_SHA_512;

  /**
   * Digest algorithm for the HTTP DIGEST scheme. This is exactly the A1 value
   * specified in RFC2617 which is a MD5 hash of the user name, realm and
   * password, separated by a colon character.
   */
  static const std::string ALGORITHM_HTTP_DIGEST;

 private:

  /** The digest algorithm. */
  const std::string algorithm;

  /** The digest value. */
  const byte[] value;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_DIGEST_H_
