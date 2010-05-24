#ifndef _ECHO_REPRESENTATION_CHARACTER_REPRESENTATION_H_
#define _ECHO_REPRESENTATION_CHARACTER_REPRESENTATION_H_

/*import java.io.IOException;
  import java.io.InputStream;
  import java.io.OutputStream;
  import java.nio.channels.ReadableByteChannel;
  import java.nio.channels.WritableByteChannel;
*/
#include <echo/data/media-type.h>
#include <echo/engine/io/byte-utils.h>

namespace echo {
namespace representation {

/**
 * Representation based on a BIO character stream.
 * 
 * @author Jerome Louvel
 */
//public abstract class CharacterRepresentation extends Representation {
class CharacterRepresentation : public Representation {  

 public:

  /**
   * Constructor.
   * 
   * @param mediaType
   *            The media type.
   */
  CharacterRepresentation(MediaType mediaType) {
    Representation(mediaType);
  }

  //@Override
  ReadableByteChannel getChannel() throws IOException {
    return ByteUtils.getChannel(getStream());
  }

  //  @Override
  InputStream getStream() throws IOException {
    return ByteUtils.getStream(getReader(), getCharacterSet());
  }

  //@Override
  void write(OutputStream outputStream) throws IOException {
    ByteUtils.write(getStream(), outputStream);
  }

  //@Override
  void write(WritableByteChannel writableChannel) throws IOException {
    write(ByteUtils.getStream(writableChannel));
  }

};

} // namespace representation
} // namespace echo

#endif // _ECHO_REPRESENTATION_CHARACTER_REPRESENTATION_H_
