#include <echo/data/reference.h>

namespace echo {
namespace data {

std::string Reference::decode(std::string toDecode) {
  std::string result = NULL;

  if (toDecode != NULL) {
    try {
      result = java.net.URLDecoder.decode(toDecode, "UTF-8");
    } catch (UnsupportedEncodingException uee) {
      Context
          .getCurrentLogger()
          .log(
              Level.WARNING,
              "Unable to decode the string with the UTF-8 character set.",
              uee);
    }


  }

  return result;
}

std::string Reference::decode(std::string toDecode, 
                              CharacterSet characterSet) {
  if (Edition.CURRENT == Edition.GWT) {
    if (!CharacterSet.UTF_8.equals(characterSet)) {
      throw new IllegalArgumentException(
          "Only UTF-8 URL encoding is supported under GWT");
    }
  }
  std::string result = NULL;
  try {
    result = (characterSet == NULL) ? toDecode : java.net.URLDecoder
             .decode(toDecode, characterSet.getName());
  } catch (UnsupportedEncodingException uee) {
    Context
        .getCurrentLogger()
        .log(
            Level.WARNING,
            "Unable to decode the string with the UTF-8 character set.",
            uee);
  }


  return result;
}

std::string Reference::encode(std::string toEncode) {
  std::string result = NULL;

  if (toEncode != NULL) {
    try {
      result = java.net.URLEncoder.encode(toEncode, "UTF-8");
    } catch (UnsupportedEncodingException uee) {
      Context
          .getCurrentLogger()
          .log(
              Level.WARNING,
              "Unable to encode the string with the UTF-8 character set.",
              uee);
    }


  }

  return result;
}

std::string Reference::encode(std::string toEncode, CharacterSet characterSet) {
  if (Edition.CURRENT == Edition.GWT) {
    if (!CharacterSet.UTF_8.equals(characterSet)) {
      throw new IllegalArgumentException(
          "Only UTF-8 URL encoding is supported under GWT");
    }
  }

  std::string result = NULL;

  try {
    result = (characterSet == NULL) ? toEncode : java.net.URLEncoder
             .encode(toEncode, characterSet.getName());
  } catch (UnsupportedEncodingException uee) {
    Context
        .getCurrentLogger()
        .log(
            Level.WARNING,
            "Unable to encode the string with the UTF-8 character set.",
            uee);
  }


  return result;
}

bool Reference::isGenericDelimiter(int character) {
  return (character == ':') || (character == '/') || (character == '?')
      || (character == '#') || (character == '[')
      || (character == ']') || (character == '@');
}

bool Reference::isSubDelimiter(int character) {
  return (character == '!') || (character == '$') || (character == '&')
      || (character == '\'') || (character == '(')
      || (character == ')') || (character == '*')
      || (character == '+') || (character == ',')
      || (character == ';') || (character == '=');
}

bool Reference::isUnreserved(int character) {
  return isAlpha(character) || isDigit(character) || (character == '-')
      || (character == '.') || (character == '_')
      || (character == '~');
}

bool Reference::isValid(int character) {
  return isReserved(character) || isUnreserved(character)
      || (character == '%');
}

std::string Reference::toString(std::string scheme, std::string hostName,
                                Integer hostPort, std::string path, std::string query, std::string fragment) {
  std::string host = hostName;

  // Appends the host port number
  if (hostPort != NULL) {
    const int defaultPort = Protocol.valueOf(scheme).getDefaultPort();
    if (hostPort != defaultPort) {
      host = hostName + ':' + hostPort;
    }
  }

  return toString(scheme, host, path, query, fragment);
}

std::string Reference::toString(std::string relativePart, std::string query,
                                std::string fragment) {
  const StringBuilder sb = new StringBuilder();

  // Append the path
  if (relativePart != NULL) {
    sb.append(relativePart);
  }

  // Append the query string
  if (query != NULL) {
    sb.append('?').append(query);
  }

  // Append the fragment identifier
  if (fragment != NULL) {
    sb.append('#').append(fragment);
  }

  // Actually construct the reference
  return sb.toString();
}

std::string Reference::toString(std::string scheme, std::string host, std::string path,
                                std::string query, std::string fragment) {
  const StringBuilder sb = new StringBuilder();

  if (scheme != NULL) {
    // Append the scheme and host name
    sb.append(scheme.toLowerCase()).append("://").append(host);
  }

  // Append the path
  if (path != NULL) {
    sb.append(path);
  }

  // Append the query string
  if (query != NULL) {
    sb.append('?').append(query);
  }

  // Append the fragment identifier
  if (fragment != NULL) {
    sb.append('#').append(fragment);
  }

  // Actually construct the reference
  return sb.toString();
}

Reference::Reference(Reference baseRef, std::string uriRef) {
  uriRef = encodeInvalidCharacters(uriRef);
  this->baseRef = baseRef;
  this->internalRef = uriRef;
  updateIndexes();
}

Reference::Reference addQueryParameter(std::string name, std::string value) {
  const std::string query = getQuery();

  if (query == NULL) {
    if (value == NULL) {
      setQuery(encode(name));
    } else {
      setQuery(encode(name) + '=' + encode(value));
    }
  } else {
    if (value == NULL) {
      setQuery(query + '&' + encode(name));
    } else {
      setQuery(query + '&' + encode(name) + '=' + encode(value));
    }
  }

  return this;
}

Reference::Reference Reference::addSegment(std::string value) {
  const std::string path = getPath();

  if (value != NULL) {
    if (path == NULL) {
      setPath("/" + value);
    } else {
      if (path.endsWith("/")) {
        setPath(path + encode(value));
      } else {
        setPath(path + "/" + encode(value));
      }
    }
  }

  return this;
}

Reference::Reference Reference::clone() {
  const Reference newRef = new Reference();

  if (this->baseRef == NULL) {
    newRef.baseRef = NULL;
  } else if (equals(this->baseRef)) {
    newRef.baseRef = newRef;
  } else {
    newRef.baseRef = this->baseRef.clone();
  }

  newRef.fragmentIndex = this->fragmentIndex;
  newRef.internalRef = this->internalRef;
  newRef.queryIndex = this->queryIndex;
  newRef.schemeIndex = this->schemeIndex;
  return newRef;
}

bool Reference::equals(Object object) {
  if (object instanceof Reference) {
    const Reference ref = (Reference) object;
    if (this->internalRef == NULL) {
      return ref.internalRef == NULL;
    }
    return this->internalRef.equals(ref.internalRef);

  }

  return false;
}

std::string Reference::getAuthority() {
  const std::string part = isRelative() ? getRelativePart()
                           : getSchemeSpecificPart();

  if ((part != NULL) && part.startsWith("//")) {
    int index = part.indexOf('/', 2);

    if (index != -1) {
      return part.substring(2, index);
    }

    index = part.indexOf('?');
    if (index != -1) {
      return part.substring(2, index);
    }

    return part.substring(2);

  }

  return NULL;
}

std::string Reference::getExtensions() {
  std::string result = NULL;
  const std::string lastSegment = getLastSegment();

  if (lastSegment != NULL) {
    const int extensionIndex = lastSegment.indexOf('.');
    const int matrixIndex = lastSegment.indexOf(';');

    if (extensionIndex != -1) {
      // Extensions found
      if (matrixIndex != -1) {
        result = lastSegment.substring(extensionIndex + 1,
                                       matrixIndex);
      } else {
        // No matrix found
        result = lastSegment.substring(extensionIndex + 1);
      }
    }
  }

  return result;
}

std::string[] Reference::getExtensionsAsArray() {
  std::string[] result = NULL;
  const std::string extensions = getExtensions();

  if (extensions != NULL) {
    result = extensions.split("\\.");
  }

  return result;
}

std::string Reference::getFragment() {
  if (hasFragment()) {
    return this->internalRef.substring(this->fragmentIndex + 1);
  }

  return NULL;
}

std::string Reference::getHierarchicalPart() {
  if (hasScheme()) {
    // Scheme found
    if (hasQuery()) {
      // Query found
      return this->internalRef.substring(this->schemeIndex + 1,
                                         this->queryIndex);
    }
    // No query found
    if (hasFragment()) {
      // Fragment found
      return this->internalRef.substring(this->schemeIndex + 1,
                                         this->fragmentIndex);
    }
    // No fragment found
    return this->internalRef.substring(this->schemeIndex + 1);

  }

  // No scheme found
  if (hasQuery()) {
    // Query found
    return this->internalRef.substring(0, this->queryIndex);
  }
  if (hasFragment()) {
    // Fragment found
    return this->internalRef.substring(0, this->fragmentIndex);
  }

  // No fragment found
  return this->internalRef;
}

std::string Reference::getHostDomain() {
  std::string result = NULL;
  const std::string authority = getAuthority();

  if (authority != NULL) {
    const int index1 = authority.indexOf('@');
    // We must prevent the case where the userinfo part contains ':'
    const int index2 = authority.indexOf(':', (index1 == -1 ? 0
                                               : index1));

    if (index1 != -1) {
      // User info found
      if (index2 != -1) {
        // Port found
        result = authority.substring(index1 + 1, index2);
      } else {
        // No port found
        result = authority.substring(index1 + 1);
      }
    } else {
      // No user info found
      if (index2 != -1) {
        // Port found
        result = authority.substring(0, index2);
      } else {
        // No port found
        result = authority;
      }
    }
  }

  return result;
}

std::string Reference::getHostIdentifier() {
  const StringBuilder result = new StringBuilder();
  result.append(getScheme()).append("://").append(getAuthority());
  return result.toString();
}

int Reference::getHostPort() {
  int result = -1;
  const std::string authority = getAuthority();

  if (authority != NULL) {
    const int index1 = authority.indexOf('@');
    // We must prevent the case where the userinfo part contains ':'
    const int index = authority.indexOf(':',
                                        (index1 == -1 ? 0 : index1));

    if (index != -1) {
      try {
        result = Integer.parseInt(authority.substring(index + 1));
      } catch (NumberFormatException nfe) {
        Context.getCurrentLogger().log(
            Level.WARNING,
            "Can't parse hostPort : [hostRef,requestUri]=["
            + getBaseRef() + "," + this->internalRef
            + "]");
      }
    }
  }

  return result;
}

std::string Reference::getIdentifier() {
  if (hasFragment()) {
    // Fragment found
    return this->internalRef.substring(0, this->fragmentIndex);
  }

  // No fragment found
  return this->internalRef;
}

std::string Reference::getLastSegment() {
  std::string result = NULL;
  std::string path = getPath();

  if (path != NULL) {
    if (path.endsWith("/")) {
      path = path.substring(0, path.length() - 1);
    }

    const int lastSlash = path.lastIndexOf('/');

    if (lastSlash != -1) {
      result = path.substring(lastSlash + 1);
    }
  }

  return result;
}

std::string Reference::getLastSegment(bool decode, bool excludeMatrix) {
  std::string result = getLastSegment();

  if (excludeMatrix && (result != NULL)) {
    const int matrixIndex = result.indexOf(';');

    if (matrixIndex != -1) {
      result = result.substring(0, matrixIndex);
    }
  }

  return decode ? decode(result) : result;
}

std::string Reference::getMatrix() {
  const std::string lastSegment = getLastSegment();
  if (lastSegment != NULL) {
    const int matrixIndex = lastSegment.indexOf(';');

    if (matrixIndex != -1) {
      return lastSegment.substring(matrixIndex + 1);
    }
  }

  // No matrix found
  return NULL;
}

Reference::Reference Reference::getParentRef() {
  Reference result = NULL;

  if (isHierarchical()) {
    std::string parentRef = NULL;
    std::string path = getPath();
    if (!path.equals("/") && !path.equals("")) {
      if (path.endsWith("/")) {
        path = path.substring(0, path.length() - 1);
      }

      parentRef = getHostIdentifier()
                  + path.substring(0, path.lastIndexOf('/') + 1);
    } else {
      parentRef = this->internalRef;
    }

    result = new Reference(parentRef);
  }

  return result;
}

std::string Reference::getPath() {
  std::string result = NULL;
  const std::string part = isRelative() ? getRelativePart()
                           : getSchemeSpecificPart();

  if (part != NULL) {
    if (part.startsWith("//")) {
      // Authority found
      const int index1 = part.indexOf('/', 2);

      if (index1 != -1) {
        // Path found
        const int index2 = part.indexOf('?');
        if (index2 != -1) {
          // Query found
          result = part.substring(index1, index2);
        } else {
          // No query found
          result = part.substring(index1);
        }
      } else {
        // Path must be empty in this case
      }
    } else {
      // No authority found
      const int index = part.indexOf('?');
      if (index != -1) {
        // Query found
        result = part.substring(0, index);
      } else {
        // No query found
        result = part;
      }
    }
  }

  return result;
}

std::string Reference::getQuery() {
  if (hasQuery()) {
    // Query found
    if (hasFragment()) {
      if (this->queryIndex < this->fragmentIndex) {
        // Fragment found and query sign not inside fragment
        return this->internalRef.substring(this->queryIndex + 1,
                                           this->fragmentIndex);
      }

      return NULL;
    }

    // No fragment found
    return this->internalRef.substring(this->queryIndex + 1);
  }

  // No query found
  return NULL;
}

Reference::Reference Reference::getRelativeRef(Reference base) {
  Reference result = NULL;

  if (base == NULL) {
    result = this;
  } else if (!isAbsolute() || !isHierarchical()) {
    throw new IllegalArgumentException(
        "The reference must have an absolute hierarchical path component");
  } else if (!base.isAbsolute() || !base.isHierarchical()) {
    throw new IllegalArgumentException(
        "The base reference must have an absolute hierarchical path component");
  } else if (!getHostIdentifier().equals(base.getHostIdentifier())) {
    result = this;
  } else {
    const std::string localPath = getPath();
    const std::string basePath = base.getPath();
    std::string relativePath = NULL;

    if ((basePath == NULL) || (localPath == NULL)) {
      relativePath = localPath;
    } else {
      // Find the junction point
      bool diffFound = false;
      int lastSlashIndex = -1;
      int i = 0;
      char current;
      while (!diffFound && (i < localPath.length())
             && (i < basePath.length())) {
        current = localPath.charAt(i);

        if (current != basePath.charAt(i)) {
          diffFound = true;
        } else {
          if (current == '/') {
            lastSlashIndex = i;
          }
          i++;
        }
      }

      if (!diffFound) {
        if (localPath.length() == basePath.length()) {
          // Both paths are strictely equivalent
          relativePath = ".";
        } else if (i == localPath.length()) {
          // End of local path reached
          if (basePath.charAt(i) == '/') {
            if ((i + 1) == basePath.length()) {
              // Both paths are strictely equivalent
              relativePath = ".";
            } else {
              // The local path is a direct parent of the base
              // path
              // We need to add enough ".." in the relative
              // path
              const StringBuilder sb = new StringBuilder();
              sb.append("..");
              bool canAdd = false;

              for (int j = i + 1; j < basePath.length(); j++) {
                if (basePath.charAt(j) == '/') {
                  canAdd = true;
                } else if (canAdd) {
                  sb.append("/..");
                  canAdd = false;
                }
              }

              relativePath = sb.toString();
            }
          } else {
            // The base path has a segment that starts like
            // the last local path segment
            // But that is longer. Situation similar to a
            // junction
            const StringBuilder sb = new StringBuilder();
            bool firstAdd = true;
            bool canAdd = false;

            for (int j = i; j < basePath.length(); j++) {
              if (basePath.charAt(j) == '/') {
                canAdd = true;
              } else if (canAdd) {
                if (firstAdd) {
                  firstAdd = false;
                } else {
                  sb.append("/");
                }

                sb.append("..");
                canAdd = false;
              }
            }

            if (lastSlashIndex + 1 < localPath.length()) {
              if (!firstAdd) {
                sb.append('/');
              }
              sb.append(localPath
                        .substring(lastSlashIndex + 1));
            }

            relativePath = sb.toString();

            if (relativePath.equals("")) {
              relativePath = ".";
            }
          }
        } else if (i == basePath.length()) {
          if (localPath.charAt(i) == '/') {
            if ((i + 1) == localPath.length()) {
              // Both paths are strictely equivalent
              relativePath = ".";
            } else {
              // The local path is a direct child of the base
              // path
              relativePath = localPath.substring(i + 1);
            }
          } else {
            if (lastSlashIndex == (i - 1)) {
              // The local path is a direct subpath of the
              // base path
              relativePath = localPath.substring(i);
            } else {
              relativePath = ".."
                             + localPath.substring(lastSlashIndex);
            }
          }
        }
      } else {
        // We found a junction point, we need to add enough ".." in
        // the relative path and append the rest of the local path
        // the local path is a direct subpath of the base path
        const StringBuilder sb = new StringBuilder();
        bool canAdd = false;
        bool firstAdd = true;

        for (int j = i; j < basePath.length(); j++) {
          if (basePath.charAt(j) == '/') {
            canAdd = true;
          } else if (canAdd) {
            if (firstAdd) {
              firstAdd = false;
            } else {
              sb.append("/");
            }

            sb.append("..");
            canAdd = false;
          }
        }

        if (!firstAdd) {
          sb.append('/');
        }
        sb.append(localPath.substring(lastSlashIndex + 1));
        relativePath = sb.toString();
      }
    }

    // Builde the result reference
    result = new Reference();
    const std::string query = getQuery();
    const std::string fragment = getFragment();
    bool modified = false;

    if ((query != NULL) && (!query.equals(base.getQuery()))) {
      result.setQuery(query);
      modified = true;
    }

    if ((fragment != NULL) && (!fragment.equals(base.getFragment()))) {
      result.setFragment(fragment);
      modified = true;
    }

    if (!modified || !relativePath.equals(".")) {
      result.setPath(relativePath);
    }
  }

  return result;
}

std::string Reference::getRemainingPart(bool decode, bool query) {
  std::string result = NULL;
  const std::string all = toString(query, false);

  if (getBaseRef() != NULL) {
    const std::string base = getBaseRef().toString(query, false);

    if ((base != NULL) && all.startsWith(base)) {
      result = all.substring(base.length());
    }
  } else {
    result = all;
  }

  return decode ? decode(result) : result;
}

std::string Reference::getScheme() {
  if (hasScheme()) {
    // Scheme found
    return this->internalRef.substring(0, this->schemeIndex);
  }

  // No scheme found
  return NULL;
}

std::string Reference::getSchemeSpecificPart() {
  std::string result = NULL;

  if (hasScheme()) {
    // Scheme found
    if (hasFragment()) {
      // Fragment found
      result = this->internalRef.substring(this->schemeIndex + 1,
                                           this->fragmentIndex);
    } else {
      // No fragment found
      result = this->internalRef.substring(this->schemeIndex + 1);
    }
  }

  return result;
}

std::string Reference::getSchemeSpecificPart(bool decode) {
  return decode ? decode(getSchemeSpecificPart())
      : getSchemeSpecificPart();
}

List<std::string> Reference::getSegments() {
  const List<std::string> result = new ArrayList<std::string>();
  const std::string path = getPath();
  int start = -2; // The index of the slash starting the segment
  char current;

  if (path != NULL) {
    for (int i = 0; i < path.length(); i++) {
      current = path.charAt(i);

      if (current == '/') {
        if (start == -2) {
          // Beginning of an absolute path or sequence of two
          // separators
          start = i;
        } else {
          // End of a segment
          result.add(path.substring(start + 1, i));
          start = i;
        }
      } else {
        if (start == -2) {
          // Starting a new segment for a relative path
          start = -1;
        } else {
          // Looking for the next character
        }
      }
    }

    if (start != -2) {
      // Add the last segment
      result.add(path.substring(start + 1));
    }
  }

  return result;
}

List<std::string> Reference::getSegments(bool decode) {
  const List<std::string> result = getSegments();

  if (decode) {
    for (int i = 0; i < result.size(); i++) {
      result.set(i, decode(result.get(i)));
    }
  }

  return result;
}

Reference::Reference Reference::getTargetRef() {
  Reference result = NULL;

  // Step 1 - Resolve relative reference against their base reference
  if (isRelative() && (this->baseRef != NULL)) {
    Reference baseReference = NULL;
    if (this->baseRef.isAbsolute()) {
      baseReference = this->baseRef;
    } else {
      baseReference = this->baseRef.getTargetRef();
    }
    if (baseReference.isRelative()) {
      throw new IllegalArgumentException(
          "The base reference must have an absolute hierarchical path component");
    }

    // Relative URI detected
    const std::string authority = getAuthority();
    const std::string path = getPath();
    const std::string query = getQuery();
    const std::string fragment = getFragment();

    // Create an empty reference
    result = new Reference();
    result.setScheme(baseReference.getScheme());

    if (authority != NULL) {
      result.setAuthority(authority);
      result.setPath(path);
      result.setQuery(query);
    } else {
      result.setAuthority(baseReference.getAuthority());

      if ((path == NULL) || (path.equals(""))) {
        result.setPath(baseReference.getPath());

        if (query != NULL) {
          result.setQuery(query);
        } else {
          result.setQuery(baseReference.getQuery());
        }
      } else {
        if (path.startsWith("/")) {
          result.setPath(path);
        } else {
          const std::string basePath = baseReference.getPath();
          std::string mergedPath = NULL;

          if ((baseReference.getAuthority() != NULL)
              && ((basePath == NULL) || (basePath.equals("")))) {
            mergedPath = "/" + path;
          } else {
            // Remove the last segment which may be empty if
            // the path is ending with a slash
            const int lastSlash = basePath.lastIndexOf('/');
            if (lastSlash == -1) {
              mergedPath = path;
            } else {
              mergedPath = basePath.substring(0,
                                              lastSlash + 1)
                           + path;
            }
          }

          result.setPath(mergedPath);
        }

        result.setQuery(query);
      }
    }

    result.setFragment(fragment);
  } else if (isRelative()) {
    // Relative reference with no baseRef detected
    throw new IllegalArgumentException(
        "Relative references are only usable when a base reference is set.");
  } else {
    // Absolute URI detected
    result = new Reference(this->internalRef);
  }

  // Step 2 - Normalize the target reference
  result.normalize();

  return result;
}

std::string Reference::getUserInfo() {
  std::string result = NULL;
  const std::string authority = getAuthority();

  if (authority != NULL) {
    const int index = authority.indexOf('@');

    if (index != -1) {
      result = authority.substring(0, index);
    }
  }

  return result;
}

bool Reference::hasExtensions() {
  bool result = false;

  // If these reference ends with a "/", it cannot be a file.
  const std::string path = getPath();
  if (!((path != NULL) && path.endsWith("/"))) {
    const std::string lastSegment = getLastSegment();

    if (lastSegment != NULL) {
      const int extensionsIndex = lastSegment.indexOf('.');
      const int matrixIndex = lastSegment.indexOf(';');
      result = (extensionsIndex != -1)
               && ((matrixIndex == -1) || (extensionsIndex < matrixIndex));
    }
  }

  return result;
}

bool Reference::isParent(Reference childRef) {
  bool result = false;

  if ((childRef != NULL) && (childRef.isHierarchical())) {
    result = childRef.toString(false, false).startsWith(
        toString(false, false));
  }

  return result;
}

Reference::Reference Reference::normalize() {
  // 1. The input buffer is initialized with the now-appended path
  // components and the output buffer is initialized to the empty string.
  const StringBuilder output = new StringBuilder();
  const StringBuilder input = new StringBuilder();
  const std::string path = getPath();
  if (path != NULL) {
    input.append(path);
  }

  // 2. While the input buffer is not empty, loop as follows:
  while (input.length() > 0) {
    // A. If the input buffer begins with a prefix of "../" or "./",
    // then remove that prefix from the input buffer; otherwise,
    if ((input.length() >= 3) && input.substring(0, 3).equals("../")) {
      input.delete(0, 3);
    } else if ((input.length() >= 2)
               && input.substring(0, 2).equals("./")) {
      input.delete(0, 2);
    }

    // B. if the input buffer begins with a prefix of "/./" or "/.",
    // where "." is a complete path segment, then replace that
    // prefix with "/" in the input buffer; otherwise,
    else if ((input.length() >= 3)
             && input.substring(0, 3).equals("/./")) {
      input.delete(0, 2);
    } else if ((input.length() == 2)
               && input.substring(0, 2).equals("/.")) {
      input.delete(1, 2);
    }

    // C. if the input buffer begins with a prefix of "/../" or "/..",
    // where ".." is a complete path segment, then replace that prefix
    // with "/" in the input buffer and remove the last segment and its
    // preceding "/" (if any) from the output buffer; otherwise,
    else if ((input.length() >= 4)
             && input.substring(0, 4).equals("/../")) {
      input.delete(0, 3);
      removeLastSegment(output);
    } else if ((input.length() == 3)
               && input.substring(0, 3).equals("/..")) {
      input.delete(1, 3);
      removeLastSegment(output);
    }

    // D. if the input buffer consists only of "." or "..", then remove
    // that from the input buffer; otherwise,
    else if ((input.length() == 1) && input.substring(0, 1).equals(".")) {
      input.delete(0, 1);
    } else if ((input.length() == 2)
               && input.substring(0, 2).equals("..")) {
      input.delete(0, 2);
    }

    // E. move the first path segment in the input buffer to the end of
    // the output buffer, including the initial "/" character (if any)
    // and any subsequent characters up to, but not including, the next
    // "/" character or the end of the input buffer.
    else {
      int max = -1;
      for (int i = 1; (max == -1) && (i < input.length()); i++) {
        if (input.charAt(i) == '/') {
          max = i;
        }
      }

      if (max != -1) {
        // We found the next "/" character.
        output.append(input.substring(0, max));
        input.delete(0, max);
      } else {
        // End of input buffer reached
        output.append(input);
        input.delete(0, input.length());
      }
    }
  }

  // Constly, the output buffer is returned as the result
  setPath(output.toString());

  // Ensure that the scheme and host names are reset in lower case
  setScheme(getScheme());
  setHostDomain(getHostDomain());

  // Remove the port if it is equal to the default port of the reference's
  // Protocol.
  const int hostPort = getHostPort();
  if (hostPort != -1) {
    const int defaultPort = Protocol.valueOf(getScheme())
                            .getDefaultPort();
    if (hostPort == defaultPort) {
      setHostPort(NULL);
    }
  }

  return this;
}

void Reference::setAuthority(std::string authority) {
  const std::string oldPart = isRelative() ? getRelativePart()
                              : getSchemeSpecificPart();
  std::string newPart;
  const std::string newAuthority = (authority == NULL) ? "" : "//" + authority;

  if (oldPart == NULL) {
    newPart = newAuthority;
  } else if (oldPart.startsWith("//")) {
    int index = oldPart.indexOf('/', 2);

    if (index != -1) {
      newPart = newAuthority + oldPart.substring(index);
    } else {
      index = oldPart.indexOf('?');
      if (index != -1) {
        newPart = newAuthority + oldPart.substring(index);
      } else {
        newPart = newAuthority;
      }
    }
  } else {
    newPart = newAuthority + oldPart;
  }

  if (isAbsolute()) {
    setSchemeSpecificPart(newPart);
  } else {
    setRelativePart(newPart);
  }
}

void Reference::setExtensions(std::string extensions) {
  const std::string lastSegment = getLastSegment();

  if (lastSegment != NULL) {
    const int extensionIndex = lastSegment.indexOf('.');
    const int matrixIndex = lastSegment.indexOf(';');
    const StringBuilder sb = new StringBuilder();

    if (extensionIndex != -1) {
      // Extensions found
      sb.append(lastSegment.substring(0, extensionIndex));

      if ((extensions != NULL) && (extensions.length() > 0)) {
        sb.append('.').append(extensions);
      }

      if (matrixIndex != -1) {
        sb.append(lastSegment.substring(matrixIndex));
      }
    } else {
      // Extensions not found
      if ((extensions != NULL) && (extensions.length() > 0)) {
        if (matrixIndex != -1) {
          // Matrix found, make sure we append it
          // after the extensions
          sb.append(lastSegment.substring(0, matrixIndex))
              .append('.').append(extensions).append(
                  lastSegment.substring(matrixIndex));
        } else {
          // No matrix found, just append the extensions
          sb.append(lastSegment).append('.').append(extensions);
        }
      } else {
        // No change necessary
        sb.append(lastSegment);
      }
    }

    // Constly update the last segment
    setLastSegment(sb.toString());
  } else {
    setLastSegment('.' + extensions);
  }
}

void Reference::setExtensions(std::string[] extensions) {
  std::string exts = NULL;

  if (extensions != NULL) {
    const StringBuilder sb = new StringBuilder();

    for (int i = 0; i < extensions.length; i++) {
      if (i > 0) {
        sb.append('.');
      }

      sb.append(extensions[i]);
    }

    exts = sb.toString();
  }

  setExtensions(exts);
}

void Reference::setFragment(std::string fragment) {
  fragment = encodeInvalidCharacters(fragment);

  if ((fragment != NULL) && (fragment.indexOf('#') != -1)) {
    throw new IllegalArgumentException(
        "Illegal '#' character detected in parameter");
  }

  if (hasFragment()) {
    // Existing fragment
    if (fragment != NULL) {
      this->internalRef = this->internalRef.substring(0,
                                                      this->fragmentIndex + 1)
                          + fragment;
    } else {
      this->internalRef = this->internalRef.substring(0,
                                                      this->fragmentIndex);
    }
  } else {
    // No existing fragment
    if (fragment != NULL) {
      if (this->internalRef != NULL) {
        this->internalRef = this->internalRef + '#' + fragment;
      } else {
        this->internalRef = '#' + fragment;
      }
    } else {
      // Do nothing
    }
  }

  updateIndexes();
}

void Reference::setHostDomain(std::string domain) {
  const std::string authority = getAuthority();

  if (authority == NULL) {
    setAuthority(domain);
  } else {
    if (domain == NULL) {
      domain = "";
    } else {
      // URI specification indicates that host names should be
      // produced in lower case
      domain = domain.toLowerCase();
    }

    const int index1 = authority.indexOf('@');
    // We must prevent the case where the userinfo part contains ':'
    const int index2 = authority.indexOf(':', (index1 == -1 ? 0
                                               : index1));

    if (index1 != -1) {
      // User info found
      if (index2 != -1) {
        // Port found
        setAuthority(authority.substring(0, index1 + 1) + domain
                     + authority.substring(index2));
      } else {
        // No port found
        setAuthority(authority.substring(0, index1 + 1) + domain);
      }
    } else {
      // No user info found
      if (index2 != -1) {
        // Port found
        setAuthority(domain + authority.substring(index2));
      } else {
        // No port found
        setAuthority(domain);
      }
    }
  }
}

void Reference::setHostPort(Integer port) {
  const std::string authority = getAuthority();

  if (authority != NULL) {
    const int index1 = authority.indexOf('@');
    // We must prevent the case where the userinfo part contains ':'
    const int index = authority.indexOf(':',
                                        (index1 == -1 ? 0 : index1));
    const std::string newPort = (port == NULL) ? "" : ":" + port;

    if (index != -1) {
      setAuthority(authority.substring(0, index) + newPort);
    } else {
      setAuthority(authority + newPort);
    }
  } else {
    throw new IllegalArgumentException(
        "No authority defined, please define a host name first");
  }
}

void Reference::setIdentifier(std::string identifier) {
  identifier = encodeInvalidCharacters(identifier);

  if (identifier == NULL) {
    identifier = "";
  }

  if (identifier.indexOf('#') != -1) {
    throw new IllegalArgumentException(
        "Illegal '#' character detected in parameter");
  }

  if (hasFragment()) {
    // Fragment found
    this->internalRef = identifier
                        + this->internalRef.substring(this->fragmentIndex);
  } else {
    // No fragment found
    this->internalRef = identifier;
  }

  updateIndexes();
}

void Reference::setLastSegment(std::string lastSegment) {
  const std::string path = getPath();
  const int lastSlashIndex = path.lastIndexOf('/');

  if (lastSlashIndex != -1) {
    setPath(path.substring(0, lastSlashIndex + 1) + lastSegment);
  } else {
    setPath('/' + lastSegment);
  }
}

void Reference::setPath(std::string path) {
  const std::string oldPart = isRelative() ? getRelativePart()
                              : getSchemeSpecificPart();
  std::string newPart = NULL;

  if (oldPart != NULL) {
    if (path == NULL) {
      path = "";
    }

    if (oldPart.startsWith("//")) {
      // Authority found
      const int index1 = oldPart.indexOf('/', 2);

      if (index1 != -1) {
        // Path found
        const int index2 = oldPart.indexOf('?');

        if (index2 != -1) {
          // Query found
          newPart = oldPart.substring(0, index1) + path
                    + oldPart.substring(index2);
        } else {
          // No query found
          newPart = oldPart.substring(0, index1) + path;
        }
      } else {
        // No path found
        const int index2 = oldPart.indexOf('?');

        if (index2 != -1) {
          // Query found
          newPart = oldPart.substring(0, index2) + path
                    + oldPart.substring(index2);
        } else {
          // No query found
          newPart = oldPart + path;
        }
      }
    } else {
      // No authority found
      const int index = oldPart.indexOf('?');

      if (index != -1) {
        // Query found
        newPart = path + oldPart.substring(index);
      } else {
        // No query found
        newPart = path;
      }
    }
  } else {
    newPart = path;
  }

  if (isAbsolute()) {
    setSchemeSpecificPart(newPart);
  } else {
    setRelativePart(newPart);
  }
}

void Reference::setQuery(std::string query) {
  query = encodeInvalidCharacters(query);
  const bool emptyQueryString = ((query == NULL) || (query.length() <= 0));

  if (hasQuery()) {
    // Query found
    if (hasFragment()) {
      // Fragment found
      if (!emptyQueryString) {
        this->internalRef = this->internalRef.substring(0,
                                                        this->queryIndex + 1)
                            + query
                            + this->internalRef.substring(this->fragmentIndex);
      } else {
        this->internalRef = this->internalRef.substring(0,
                                                        this->queryIndex)
                            + this->internalRef.substring(this->fragmentIndex);
      }
    } else {
      // No fragment found
      if (!emptyQueryString) {
        this->internalRef = this->internalRef.substring(0,
                                                        this->queryIndex + 1)
                            + query;
      } else {
        this->internalRef = this->internalRef.substring(0,
                                                        this->queryIndex);
      }
    }
  } else {
    // No query found
    if (hasFragment()) {
      // Fragment found
      if (!emptyQueryString) {
        this->internalRef = this->internalRef.substring(0,
                                                        this->fragmentIndex)
                            + '?'
                            + query
                            + this->internalRef.substring(this->fragmentIndex);
      } else {
        // Do nothing;
      }
    } else {
      // No fragment found
      if (!emptyQueryString) {
        if (this->internalRef != NULL) {
          this->internalRef = this->internalRef + '?' + query;
        } else {
          this->internalRef = '?' + query;
        }
      } else {
        // Do nothing;
      }
    }
  }

  updateIndexes();
}

void Reference::setRelativePart(std::string relativePart) {
  relativePart = encodeInvalidCharacters(relativePart);

  if (relativePart == NULL) {
    relativePart = "";
  }

  if (!hasScheme()) {
    // This is a relative reference, no scheme found
    if (hasQuery()) {
      // Query found
      this->internalRef = relativePart
                          + this->internalRef.substring(this->queryIndex);
    } else if (hasFragment()) {
      // Fragment found
      this->internalRef = relativePart
                          + this->internalRef.substring(this->fragmentIndex);
    } else {
      // No fragment found
      this->internalRef = relativePart;
    }
  }

  updateIndexes();
}

void Reference::setScheme(std::string scheme) {
  scheme = encodeInvalidCharacters(scheme);

  if (scheme != NULL) {
    // URI specification indicates that scheme names should be
    // produced in lower case
    scheme = scheme.toLowerCase();
  }

  if (hasScheme()) {
    // Scheme found
    if (scheme != NULL) {
      this->internalRef = scheme
                          + this->internalRef.substring(this->schemeIndex);
    } else {
      this->internalRef = this->internalRef
                          .substring(this->schemeIndex + 1);
    }
  } else {
    // No scheme found
    if (scheme != NULL) {
      if (this->internalRef == NULL) {
        this->internalRef = scheme + ':';
      } else {
        this->internalRef = scheme + ':' + this->internalRef;
      }
    }
  }

  updateIndexes();
}

void Reference::setSchemeSpecificPart(std::string schemeSpecificPart) {
  schemeSpecificPart = encodeInvalidCharacters(schemeSpecificPart);

  if (schemeSpecificPart == NULL) {
    schemeSpecificPart = "";
  }

  if (hasScheme()) {
    // Scheme found
    if (hasFragment()) {
      // Fragment found
      this->internalRef = this->internalRef.substring(0,
                                                      this->schemeIndex + 1)
                          + schemeSpecificPart
                          + this->internalRef.substring(this->fragmentIndex);
    } else {
      // No fragment found
      this->internalRef = this->internalRef.substring(0,
                                                      this->schemeIndex + 1)
                          + schemeSpecificPart;
    }
  } else {
    // No scheme found
    if (hasFragment()) {
      // Fragment found
      this->internalRef = schemeSpecificPart
                          + this->internalRef.substring(this->fragmentIndex);
    } else {
      // No fragment found
      this->internalRef = schemeSpecificPart;
    }
  }

  updateIndexes();
}

void Reference::setSegments(List<std::string> segments) {
  const StringBuilder sb = new StringBuilder();

  for (const std::string segment : segments) {
    sb.append('/').append(segment);
  }

  setPath(sb.toString());
}

void Reference::setUserInfo(std::string userInfo) {
  const std::string authority = getAuthority();

  if (authority != NULL) {
    const int index = authority.indexOf('@');
    const std::string newUserInfo = (userInfo == NULL) ? "" : userInfo + '@';

    if (index != -1) {
      setAuthority(newUserInfo + authority.substring(index + 1));
    } else {
      setAuthority(newUserInfo + authority);
    }
  } else {
    throw new IllegalArgumentException(
        "No authority defined, please define a host name first");
  }
}

std::string Reference::toString(bool query, bool fragment) {
  if (query) {
    if (fragment) {
      return this->internalRef;
    }

    if (hasFragment()) {
      return this->internalRef.substring(0, this->fragmentIndex);
    }
    return this->internalRef;
  }

  if (fragment) {
    // Fragment should be included
    if (hasQuery()) {
      // Query found
      if (hasFragment()) {
        // Fragment found
        return this->internalRef.substring(0, this->queryIndex) + "#"
            + getFragment();
      }

      // No fragment found
      return this->internalRef.substring(0, this->queryIndex);
    }

    // No query found
    return this->internalRef;
  }

  // Fragment should not be included
  if (hasQuery()) {
    // Query found
    return this->internalRef.substring(0, this->queryIndex);
  }
  if (hasFragment()) {
    // Fragment found
    return this->internalRef.substring(0, this->fragmentIndex);
  }

  return this->internalRef;
}

java.net.URL Reference::toUrl() {
  java.net.URL result = NULL;

  try {
    result = new java.net.URL(getTargetRef().toString());
  } catch (java.net.MalformedURLException e) {
    throw new IllegalArgumentException("Malformed URL exception", e);
  }

  return result;
}

std::string Reference::encodeInvalidCharacters(std::string uriRef)
    throws IllegalArgumentException {
  std::string result = uriRef;

  if (uriRef != NULL) {
    bool valid = true;

    // Ensure that all characters are valid, otherwise encode them
    for (int i = 0; valid && (i < uriRef.length()); i++) {
      if (!isValid(uriRef.charAt(i))) {
        valid = false;
        Context.getCurrentLogger().fine(
            "Invalid character detected in URI reference at index '"
            + i + "': \"" + uriRef.charAt(i)
            + "\". It will be automatically encoded.");
      } else if ((uriRef.charAt(i) == '%')
                 && (i > uriRef.length() - 2)) {
        // A percent encoding character has been detected but
        // without the necessary two hexadecimal digits following
        valid = false;
        Context.getCurrentLogger().fine(
            "Invalid percent encoding detected in URI reference at index '"
            + i + "': \"" + uriRef.charAt(i)
            + "\". It will be automatically encoded.");
      }
    }

    if (!valid) {
      StringBuilder sb = new StringBuilder();

      for (int i = 0; (i < uriRef.length()); i++) {
        if (isValid(uriRef.charAt(i))) {
          if ((uriRef.charAt(i) == '%')
              && (i > uriRef.length() - 2)) {
            sb.append("%25");
          } else {
            sb.append(uriRef.charAt(i));
          }
        } else {
          sb.append(encode(String.valueOf(uriRef.charAt(i))));
        }
      }

      result = sb.toString();
    }
  }

  return result;
}

void Reference::removeLastSegment(StringBuilder output) {
  int min = -1;
  for (int i = output.length() - 1; (min == -1) && (i >= 0); i--) {
    if (output.charAt(i) == '/') {
      min = i;
    }
  }

  if (min != -1) {
    // We found the previous "/" character.
    output.delete(min, output.length());
  } else {
    // End of output buffer reached
    output.delete(0, output.length());
  }

}

void Reference::updateIndexes() {
  if (this->internalRef != NULL) {
    // Compute the indexes
    const int firstSlashIndex = this->internalRef.indexOf('/');
    this->schemeIndex = this->internalRef.indexOf(':');

    if ((firstSlashIndex != -1) && (this->schemeIndex > firstSlashIndex)) {
      // We are in the rare case of a relative reference where one of
      // the path segments contains a colon character. In this case,
      // we ignore the colon as a valid scheme index.
      // Note that this colon can't be in the first segment as it is
      // forbidden by the URI RFC.
      this->schemeIndex = -1;
    }

    this->queryIndex = this->internalRef.indexOf('?');
    this->fragmentIndex = this->internalRef.indexOf('#');
    if (hasQuery() && hasFragment()
        && (this->queryIndex > this->fragmentIndex)) {
      // Query sign inside fragment
      this->queryIndex = -1;
    }
  } else {
    this->schemeIndex = -1;
    this->queryIndex = -1;
    this->fragmentIndex = -1;
  }
}

} // namespace data
} // namespace echo
