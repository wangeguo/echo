#include <echo/data/encoding.h>

namespace echo {
namespace data {


const Encoding Encoding::ALL("*", "All encodings");

const Encoding Encoding::COMPRESS("compress",
                                  "Common Unix compression");

const Encoding Encoding::DEFLATE("deflate",
                                 "Deflate compression using the zlib format");

const Encoding Encoding::FREEMARKER("freemarker",
                                    "FreeMarker templated representation");

const Encoding Encoding::GZIP("gzip", "GZip compression");

const Encoding Encoding::IDENTITY("identity",
                                  "The default encoding with no transformation");

const Encoding Encoding::VELOCITY("velocity",
                                  "Velocity templated representation");

const Encoding Encoding::ZIP("zip", "Zip compression");

static Encoding Encoding::valueOf(const std::string name) {
  Encoding result = NULL;

  if ((name != NULL) && !name.equals("")) {
    if (name.equalsIgnoreCase(ALL.getName())) {
      result = ALL;
    } else if (name.equalsIgnoreCase(GZIP.getName())) {
      result = GZIP;
    } else if (name.equalsIgnoreCase(ZIP.getName())) {
      result = ZIP;
    } else if (name.equalsIgnoreCase(COMPRESS.getName())) {
      result = COMPRESS;
    } else if (name.equalsIgnoreCase(DEFLATE.getName())) {
      result = DEFLATE;
    } else if (name.equalsIgnoreCase(IDENTITY.getName())) {
      result = IDENTITY;
    } else if (name.equalsIgnoreCase(FREEMARKER.getName())) {
      result = FREEMARKER;
    } else if (name.equalsIgnoreCase(VELOCITY.getName())) {
      result = VELOCITY;
    } else {
      result = new Encoding(name);
    }
  }

  return result;
}

bool Encoding::equals(const Object object) {
  return (object instanceof Encoding)
      && getName().equalsIgnoreCase(((Encoding) object).getName());
}
  
} // namespace data
} // namespace echo

