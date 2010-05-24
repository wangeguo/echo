#ifndef _ECHO_REPRESENTATION_EMPTY_REPRESENTATION_H_
#define _ECHO_REPRESENTATION_EMPTY_REPRESENTATION_H_

/*
  import java.io.IOException;
  import java.io.InputStream;
  import java.io.OutputStream;
  import java.io.Reader;
*/

namespace echo {
namespace representation {

/**
 * Empty representation with no content.
 * 
 * @author Jerome Louvel
 */
class EmptyRepresentation : public Representation {

 public:

  /**
   * Constructor.
   */
  EmptyRepresentation() {
    setAvailable(false);
    setTransient(true);
    setSize(0);
  }

  //@Override
  java.nio.channels.ReadableByteChannel getChannel()
  throws IOException {
    return null;
  }

  //@Override
  Reader getReader() throws IOException {
    return null;
  }

  //@Override
  InputStream getStream() throws IOException {
    return null;
  }

  //@Override
  void write(java.io.Writer writer) throws IOException {
    // Do nothing
  }

  //@Override
  void write(java.nio.channels.WritableByteChannel writableChannel)
      throws IOException {
    // Do nothing
  }

  //@Override
  void write(OutputStream outputStream) throws IOException {
    // Do nothing
  }
};

} // namespace representation
} // namespace echo

#endif // _ECHO_REPRESENTATION_EMPTY_REPRESENTATION_H_
