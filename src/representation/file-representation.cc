#include <echo/representation/file-representation.h>

namespace echo {
namespace representation {

FileRepresentation::FileRepresentation(File file, MediaType mediaType, int timeToLive) {
  Representation(mediaType);
  this->file = file;
  setModificationDate(new Date(file.lastModified()));

  if (timeToLive == 0) {
    setExpirationDate(new Date());
  } else if (timeToLive > 0) {
    setExpirationDate(new Date(System.currentTimeMillis()
                               + (1000L * timeToLive)));
  }

  setMediaType(mediaType);
  setDownloadName(file.getName());
}

FileChannel FileRepresentation::getChannel() throws IOException {
  try {
    return new FileInputStream(this->file).getChannel();
  } catch (FileNotFoundException fnfe) {
    throw new IOException("Couldn't get the channel. File not found");
  }
}

long FileRepresentation::getSize() {
  if (super.getSize() != UNKNOWN_SIZE) {
    return super.getSize();
  }

  return this->file.length();
}

//@Override
FileInputStream FileRepresentation::getStream() throws IOException {
  try {
    return new FileInputStream(this->file);
  } catch (FileNotFoundException fnfe) {
    throw new IOException("Couldn't get the stream. File not found");
  }
}

void FileRepresentation::release() {
  if (isAutoDeleting() && getFile() != NULL) {
    try {
      getFile().delete();
    } catch (Exception e) {
    }
  }

  setFile(NULL);
  super.release();
}

File FileRepresentation::createFile(String path) {
  if (path.startsWith("file://")) {
    return new LocalReference(path).getFile();
  }

  return new File(path);
}

} // namespace representation
} // namespace echo
