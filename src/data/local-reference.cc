#include <echo/data/local-reference.h>

namespace echo {
namespace data {

const int LocalReference::CLAP_CLASS(1);
const int LocalReference::CLAP_SYSTEM(2);
const int LocalReference::CLAP_THREAD(3);
const int LocalReference::RIAP_APPLICATION(4);
const int LocalReference::RIAP_COMPONENT(5);
const int LocalReference::RIAP_HOST(6);

static LocalReference
LocalReference::createClapReference(int authorityType,
                                    std::string path) {
  return new LocalReference("clap://" + getAuthorityName(authorityType) + path);
}

static LocalReference
LocalReference::createFileReference(std::string hostName,
                                    std::string filePath) {
  return new LocalReference("file://" + hostName + "/"
                            + normalizePath(filePath));
}

static LocalReference
LocalReference::createJarReference(Reference jarFile,
                                   std::string entryPath) {
  return new LocalReference("jar:" + jarFile.toString() + "!/"
                            + entryPath);
}

static LocalReference
LocalReference::createRiapReference(int authorityType,std::string path) {
  return new LocalReference("riap://" + getAuthorityName(authorityType)
                            + path);
}

static LocalReference
LocalReference::createZipReference(Reference zipFile,std::string entryPath) {
  return new LocalReference("zip:" + zipFile.toString() + "!/"
                            + entryPath);
}

static std::string
LocalReference::getAuthorityName(int authority) {
  std::string result = NULL;

  switch (authority) {
    case CLAP_CLASS:
      result = "class";
      break;
    case CLAP_SYSTEM:
      result = "system";
      break;
    case CLAP_THREAD:
      result = "thread";
      break;
    case RIAP_APPLICATION:
      result = "application";
      break;
    case RIAP_COMPONENT:
      result = "component";
      break;
    case RIAP_HOST:
      result = "host";
      break;
  }

  return result;
}

static std::string LocalReference::localizePath(std::string path) {
  const StringBuilder result = new StringBuilder();
  char nextChar;
  for (int i = 0; i < path.length(); i++) {
    nextChar = path.charAt(i);
    if (nextChar == '/') {
      // Convert the URI separator to
      // the system dependent path separator
      result.append(File.separatorChar);
    } else {
      result.append(nextChar);
    }
  }

  return result.toString();
}

static std::string LocalReference::normalizePath(std::string path) {
  const StringBuilder result = new StringBuilder();
  char nextChar;
  for (int i = 0; i < path.length(); i++) {
    nextChar = path.charAt(i);
    if ((nextChar == File.separatorChar)) {
      // Convert the Windows style path separator
      // to the standard path separator
      result.append('/');
    } else if (!isUnreserved(nextChar)) {
      result.append(Reference.encode("" + nextChar));
    } else {
      result.append(nextChar);
    }
  }

  return result.toString();
}

int LocalReference::getClapAuthorityType() {
  int result = 0;

  if (getSchemeProtocol().equals(Protocol.CLAP)) {
    const std::string authority = getAuthority();

    if (authority != NULL) {
      if (authority.equalsIgnoreCase(getAuthorityName(CLAP_CLASS))) {
        result = CLAP_CLASS;
      } else if (authority
                 .equalsIgnoreCase(getAuthorityName(CLAP_SYSTEM))) {
        result = CLAP_SYSTEM;
      } else if (authority
                 .equalsIgnoreCase(getAuthorityName(CLAP_THREAD))) {
        result = CLAP_THREAD;
      }
    }
  }

  return result;
}

File LocalReference::getFile() {
  File result = NULL;

  if (getSchemeProtocol().equals(Protocol.FILE)) {
    const std::string hostName = getAuthority();

    if ((hostName == NULL) || hostName.equals("")
        || hostName.equalsIgnoreCase("localhost")) {
      const std::string filePath = Reference.decode(getPath());
      result = new File(filePath);
    } else {
      throw new RuntimeException(
          "Can't resolve files on remote host machines");
    }
  }

  return result;
}

std::string LocalReference::getJarEntryPath() {
  std::string result = NULL;

  if (getSchemeProtocol().equals(Protocol.JAR)) {
    const std::string ssp = getSchemeSpecificPart();

    if (ssp != NULL) {
      const int separatorIndex = ssp.indexOf("!/");

      if (separatorIndex != -1) {
        result = ssp.substring(separatorIndex + 2);
      }
    }
  }

  return result;
}

Reference LocalReference::getJarFileRef() {
  Reference result = NULL;

  if (getSchemeProtocol().equals(Protocol.JAR)) {
    const std::string ssp = getSchemeSpecificPart();

    if (ssp != NULL) {
      const int separatorIndex = ssp.indexOf("!/");

      if (separatorIndex != -1) {
        result = new Reference(ssp.substring(0, separatorIndex));
      }
    }
  }

  return result;
}

int LocalReference::getRiapAuthorityType() {
  int result = 0;

  if (getSchemeProtocol().equals(Protocol.RIAP)) {
    const std::string authority = getAuthority();

    if (authority != NULL) {
      if (authority
          .equalsIgnoreCase(getAuthorityName(RIAP_APPLICATION))) {
        result = RIAP_APPLICATION;
      } else if (authority
                 .equalsIgnoreCase(getAuthorityName(RIAP_COMPONENT))) {
        result = RIAP_COMPONENT;
      } else if (authority
                 .equalsIgnoreCase(getAuthorityName(RIAP_HOST))) {
        result = RIAP_HOST;
      }
    }
  }

  return result;
}

} // namespace data
} // namespace echo

