#ifndef _ECHO_REPRESENTATION_CHANNEL_REPRESENTATION_H_
#define _ECHO_REPRESENTATION_CHANNEL_REPRESENTATION_H_

/*
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Reader;
import java.io.Writer;
*/

#include <echo/data/media-type.h>
#include <echo/engine/io/byte-utils.h>

namespace echo {
namespace representation {

/**
 * Representation based on a NIO byte channel.
 * 
 * @author Jerome Louvel
 */
//public abstract class ChannelRepresentation extends Representation {
class ChannelRepresentation : public Representation {

 public:

  /**
   * Constructor.
   * 
   * @param mediaType
   *            The media type.
   */
  ChannelRepresentation(MediaType mediaType) {
    Representation(mediaType);
  }

  //@Override
  Reader getReader() throws IOException {
    return ByteUtils.getReader(getStream(), getCharacterSet());
  }

  //@Override
  InputStream getStream() throws IOException {
    return ByteUtils.getStream(getChannel());
  }

  //@Override
  void write(OutputStream outputStream) throws IOException {
    write(ByteUtils.getChannel(outputStream));
  }

  //@Override
  void write(Writer writer) throws IOException {
    write(ByteUtils.getStream(writer));
  }

};

} // namespace data
} // namespace echo

#endif // _ECHO_REPRESENTATION_CHANNEL_REPRESENTATION_H_
