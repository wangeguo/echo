#ifndef _ECHO_REPRESENTATION_DIGEST_REPRESENTATION_H_
#define _ECHO_REPRESENTATION_DIGEST_REPRESENTATION_H_
/*
  import java.io.IOException;
  import java.io.InputStream;
  import java.io.OutputStream;
  import java.io.Reader;
  import java.io.Writer;
  import java.nio.channels.ReadableByteChannel;
  import java.nio.channels.WritableByteChannel;
  import java.security.DigestInputStream;
  import java.security.DigestOutputStream;
  import java.security.MessageDigest;
  import java.security.NoSuchAlgorithmException;
*/

#include <echo/data/digest.h>
#include <echo/engine/io/byte-utils.h>
#include <echo/util/wrapper-representation.h>

namespace echo {
namespace representation {

/**
 * Representation capable of computing a digest. It wraps another representation
 * and allows to get the computed digest of the wrapped entity after reading or
 * writing operations. The final digest value is guaranteed to be correct only
 * after the wrapped representation has been entirely exhausted (that is to say
 * read or written).<br>
 * <br>
 * This wrapper allows to get the computed digest at the same time the
 * representation is read or written. It does not need two separate operations
 * which may require specific attention for transient representations.
 * 
 * @see Representation#isTransient().
 * @deprecated See {@link DigesterRepresentation} instead.
 * @author Jerome Louvel
 */
//@Deprecated
//public abstract class DigestRepresentation extends WrapperRepresentation {
class DigestRepresentation : public WrapperRepresentation {

 public:
  
  /**
   * Constructor.<br>
   * By default, the instance relies on the {@link Digest#ALGORITHM_MD5}
   * digest algorithm.
   * 
   * @param wrappedRepresentation
   *            The wrapped representation.
   * @throws NoSuchAlgorithmException
   */
  DigestRepresentation(Representation wrappedRepresentation)
  throws NoSuchAlgorithmException {
    DigestRepresentation(wrappedRepresentation, Digest.ALGORITHM_MD5);
  }

  /**
   * Constructor.<br>
   * 
   * @param wrappedRepresentation
   *            The wrapped representation.
   * @param algorithm
   *            The digest algorithm
   * @throws NoSuchAlgorithmException
   */
  DigestRepresentation(Representation wrappedRepresentation,
                       std::string algorithm) throws NoSuchAlgorithmException {
    WrapperRepresentation(wrappedRepresentation);
    this->algorithm = algorithm;
    this->computedDigest = MessageDigest.getInstance(algorithm);
  }

  /**
   * Check that the digest computed from the wrapped representation content
   * and the digest declared by the wrapped representation are the same. User
   * must be aware that the computed value is accurate only after a complete
   * reading or writing operation.
   */
  //@Override
  bool checkDigest() {
    Digest digest = getDigest();
    return (digest != null && digest.equals(getComputedDigest()));
  }

  /**
   * {@inheritDoc} <br>
   * If case the given algorithm is the same than the one provided at
   * instantiation, the check operation is made with the current stored
   * computed value and does not require to exhaust entirely the
   * representation's stream.
   */
  //@Override
  bool checkDigest(std::string algorithm) {
    if (this->algorithm != null && this->algorithm.equals(algorithm)) {
      return checkDigest();
    }

    return super.checkDigest(algorithm);
  }

  /**
   * {@inheritDoc} <br>
   * If case the given algorithm is the same than the one provided at
   * instantiation, the computation operation is made with the current stored
   * computed value and does not require to exhaust entirely the
   * representation's stream.
   */
  //@Override
  Digest computeDigest(std::string algorithm) {
    if (this->algorithm != null && this->algorithm.equals(algorithm)) {
      return getComputedDigest();
    }

    return super.computeDigest(algorithm);
  }

  //@Override
  ReadableByteChannel getChannel() throws IOException {
    return ByteUtils.getChannel(getStream());
  }

  /**
   * Returns the current computed digest value of the representation. User
   * must be aware that, if the representation has not been entirely read or
   * written, the computed digest value may not be accurate.
   * 
   * @return The current computed digest value.
   */
  Digest getComputedDigest() {
    return new Digest(this->algorithm, computedDigest.digest());
  }

  //@Override
  Reader getReader() throws IOException {
    return ByteUtils.getReader(getStream(), getCharacterSet());
  }

  /**
   * {@inheritDoc}<br>
   * 
   * The stream of the underlying representation is wrapped with a new
   * instance of the {@link DigestInputStream} class, which allows to compute
   * progressively the digest value.
   */
  //@Override
  InputStream getStream() throws IOException {
    return new DigestInputStream(getWrappedRepresentation().getStream(),
                                 this->computedDigest);
  }

  /**
   * {@inheritDoc}<br>
   * 
   * The output stream is wrapped with a new instance of the
   * {@link DigestOutputStream} class, which allows to compute progressively
   * the digest value.
   */
  //@Override
  void write(OutputStream outputStream) throws IOException {
    getWrappedRepresentation().write(
        new DigestOutputStream(outputStream, this->computedDigest));
  }

  //@Override
  void write(WritableByteChannel writableChannel) throws IOException {
    write(ByteUtils.getStream(writableChannel));
  }

  //@Override
  void write(Writer writer) throws IOException {
    write(ByteUtils.getStream(writer));
  }

 private:
  
  /** The digest algorithm. */
  const std::string algorithm;

  /** The computed digest value. */
  volatile MessageDigest computedDigest;
};

} // namespace representation
} // namespace echo

#endif // _ECHO_REPRESENTATION_DIGEST_REPRESENTATION_H_
