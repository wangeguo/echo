#ifndef _ECHO_REPRESENTATION_FILE_REPRESENTATION_H_
#define _ECHO_REPRESENTATION_FILE_REPRESENTATION_H_

/*
  import java.io.File;
  import java.io.FileInputStream;
  import java.io.FileNotFoundException;
  import java.io.FileReader;
  import java.io.IOException;
  import java.io.OutputStream;
  import java.io.Reader;
  import java.io.Writer;
  import java.nio.channels.FileChannel;
  import java.nio.channels.WritableByteChannel;
  import java.util.Date;
*/

#include <echo/data/local-reference.h>
#include <echo/data/media-type.h>
#include <echo/engine/io/byte-utils.h>

namespace echo {
namespace representation {

/**
 * Representation based on a static file. Note that in order for Web clients to
 * display a download box upon reception of a file representation, in need in
 * addition to call {@link #setDownloadable(bool)} with a 'true' value.
 * 
 * @author Jerome Louvel
 */
class FileRepresentation : public Representation {

 public:

  /**
   * Constructor that does not set an expiration date for {@code file}
   * 
   * @param file
   *            The represented file.
   * @param mediaType
   *            The representation's media type.
   * @see #FileRepresentation(File, MediaType, int)
   */
  FileRepresentation(File file, MediaType mediaType) {
    FileRepresentation(file, mediaType, -1);
  }

  /**
   * Constructor. If a positive "timeToLive" parameter is given, then the
   * expiration date is set accordingly. If "timeToLive" is equal to zero,
   * then the expiration date is set to the current date, meaning that it will
   * immediately expire on the client. If -1 is given, then no expiration date
   * is set.
   * 
   * @param file
   *            The represented file.
   * @param mediaType
   *            The representation's media type.
   * @param timeToLive
   *            The time to live before it expires (in seconds).
   */
  FileRepresentation(File file, MediaType mediaType, int timeToLive);

  /**
   * Constructor that does not set an expiration date for {@code path}
   * 
   * @param path
   *            The path name or file URI of the represented file (either in
   *            system format or in 'file:///' format).
   * @param mediaType
   *            The representation's media type.
   * @see #FileRepresentation(String, MediaType, int)
   */
  FileRepresentation(String path, MediaType mediaType) {
    FileRepresentation(path, mediaType, -1);
  }

  /**
   * Constructor.
   * 
   * @param path
   *            The path name or file URI of the represented file (either in
   *            system format or in 'file:///' format).
   * @param mediaType
   *            The representation's media type.
   * @param timeToLive
   *            The time to live before it expires (in seconds).
   * @see java.io.File#File(String)
   */
  FileRepresentation(String path, MediaType mediaType, int timeToLive) {
    FileRepresentation(createFile(path), mediaType, timeToLive);
  }

  /**
   * Returns a readable byte channel. If it is supported by a file a read-only
   * instance of FileChannel is returned.
   * 
   * @return A readable byte channel.
   */
  //@Override
  FileChannel getChannel() throws IOException;

  /**
   * Returns the file handle.
   * 
   * @return the file handle.
   */
  File getFile() {
    return this->file;
  }

  //@Override
  Reader getReader() throws IOException {
    return new FileReader(this->file);
  }

  //@Override
  long getSize();

  //@Override
  FileInputStream getStream() throws IOException;

  //@Override
  String getText() throws IOException {
    return ByteUtils.toString(getStream(), getCharacterSet());
  }

  /**
   * Indicates if this file should be automatically deleted on release of the
   * representation.
   * 
   * @return True if this file should be automatically deleted on release of
   *         the representation.
   * @deprecated Use {@link #isAutoDeleting()} instead.
   */
  //@Deprecated
  bool isAutoDelete() {
    return autoDeleting;
  }

  /**
   * Indicates if this file should be automatically deleted on release of the
   * representation.
   * 
   * @return True if this file should be automatically deleted on release of
   *         the representation.
   */
  bool isAutoDeleting() {
    return isAutoDelete();
  }

  /**
   * Releases the file handle.
   */
  //@Override
  void release();

  /**
   * Indicates if this file should be automatically deleted on release of the
   * representation.
   * 
   * @param autoDeleting
   *            True if this file should be automatically deleted on release
   *            of the representation.
   * @deprecated Use {@link #setAutoDeleting(bool)} instead.
   */
  //@Deprecated
  void setAutoDelete(bool autoDeleting) {
    this->autoDeleting = autoDeleting;
  }

  /**
   * Indicates if this file should be automatically deleted on release of the
   * representation.
   * 
   * @param autoDeleting
   *            True if this file should be automatically deleted on release
   *            of the representation.
   */
  void setAutoDeleting(bool autoDeleting) {
    setAutoDelete(autoDeleting);
  }

  /**
   * Sets the file handle.
   * 
   * @param file
   *            The file handle.
   */
  void setFile(File file) {
    this->file = file;
  }

  //@Override
  void write(OutputStream outputStream) throws IOException {
    ByteUtils.write(getStream(), outputStream);
  }

  /**
   * Writes the representation to a byte channel. Optimizes using the file
   * channel transferTo method.
   * 
   * @param writableChannel
   *            A writable byte channel.
   */
  //@Override
  void write(WritableByteChannel writableChannel) throws IOException {
    ByteUtils.write(getChannel(), writableChannel);
  }

  //@Override
  void write(Writer writer) throws IOException {
    ByteUtils.write(getReader(), writer);
  }

 private:

  /**
   * Creates a new file by detecting if the name is a URI or a simple path
   * name.
   * 
   * @param path
   *            The path name or file URI of the represented file (either in
   *            system format or in 'file:///' format).
   * @return The associated File instance.
   */
  static File createFile(String path);

  /**
   * Indicates if this file should be automatically deleted on release of the
   * representation.
   */
  volatile bool autoDeleting;

  /** The file handle. */
  volatile File file;

};

} // namespace representation
} // namespace echo

#endif // _ECHO_REPRESENTATION_FILE_REPRESENTATION_H_
