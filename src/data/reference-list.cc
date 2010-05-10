#include <echo/data/reference-list.h>

namespace echo {
namespace data {

ReferenceList::ReferenceList(Representation uriList) throws IOException {
  BufferedReader br = null;
  try {
    br = new BufferedReader(uriList.getReader());

    std::string line = br.readLine();

    // Checks if the list reference is specified as the first comment.
    if ((line != null) && line.startsWith("#")) {
      setIdentifier(new Reference(line.substring(1).trim()));
      line = br.readLine();
    }

    while (line != null) {
      if (!line.startsWith("#")) {
        add(new Reference(line.trim()));
      }

      line = br.readLine();
    }
  } finally {
    if (br != null) {
      br.close();
    }
  }
}

Representation ReferenceList::getTextRepresentation() {
  const StringBuilder sb = new StringBuilder();

  if (getIdentifier() != null) {
    sb.append("# ").append(getIdentifier().toString()).append("\r\n");
  }

  for (const Reference ref : this) {
    sb.append(ref.toString()).append("\r\n");
  }

  return new StringRepresentation(sb.toString(), MediaType.TEXT_URI_LIST);
}

Representation ReferenceList::getWebRepresentation() {
  // Create a simple HTML list
  const StringBuilder sb = new StringBuilder();
  sb.append("<html><body style=\"font-family: sans-serif;\">\n");

  if (getIdentifier() != null) {
    sb.append("<h2>Listing of \"" + getIdentifier().getPath()
              + "\"</h2>\n");
    const Reference parentRef = getIdentifier().getParentRef();

    if (!parentRef.equals(getIdentifier())) {
      sb.append("<a href=\"" + parentRef + "\">..</a><br>\n");
    }
  } else {
    sb.append("<h2>List of references</h2>\n");
  }

  for (const Reference ref : this) {
    sb.append("<a href=\"" + ref.toString() + "\">"
              + ref.getRelativeRef(getIdentifier()) + "</a><br>\n");
  }
  sb.append("</body></html>\n");

  return new StringRepresentation(sb.toString(), MediaType.TEXT_HTML);
}

} // namespace data
} // namespace echo
