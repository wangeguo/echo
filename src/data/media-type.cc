#include <echo/data/media-type.h>

namespace echo {
namespace data {

const MediaType
MediaType::ALL = MediaType::register("*/*", "All media");

const MediaType
MediaType::APPLICATION_ALL = MediaType::register(
    "application/*", "All application documents");

const MediaType
MediaType::APPLICATION_ALL_XML = MediaType::register(
    "application/*+xml", "All application/*+xml documents");

const MediaType
MediaType::APPLICATION_ATOM = MediaType::register(
    "application/atom+xml", "Atom document");

const MediaType
MediaType::APPLICATION_ATOM_SERVICE_XML = MediaType::register(
    "application/atomsvc+xml", "Atom service document");

const MediaType 
MediaType::APPLICATION_ATOM_XML = MediaType::register(
    "application/atom+xml", "Atom document");

const MediaType
MediaType::APPLICATION_ATOMPUB_CATEGORY = MediaType::register(
    "application/atomcat+xml", "Atom category document");

const MediaType
MediaType::APPLICATION_ATOMPUB_SERVICE = MediaType::register(
    "application/atomsvc+xml", "Atom service document");

const MediaType
MediaType::APPLICATION_CAB = MediaType::register(
    "application/vnd.ms-cab-compressed", "Microsoft Cabinet archive");

const MediaType
MediaType::APPLICATION_COMPRESS = MediaType::register(
    "application/x-compress", "Compressed file");

const MediaType
MediaType::APPLICATION_EXCEL = MediaType::register(
    "application/vnd.ms-excel", "Microsoft Excel document");

const MediaType
MediaType::APPLICATION_FLASH = MediaType::register(
    "application/x-shockwave-flash", "Shockwave Flash object");

const MediaType
MediaType::APPLICATION_GNU_TAR = MediaType::register(
    "application/x-gtar", "GNU Tar archive");

const MediaType
MediaType::APPLICATION_GNU_ZIP = MediaType::register(
    "application/x-gzip", "GNU Zip archive");

const MediaType
MediaType::APPLICATION_HTTP_COOKIES = MediaType::register(
    "application/x-http-cookies", "HTTP cookies");

const MediaType
MediaType::APPLICATION_JAVA = MediaType::register(
    "application/java", "Java class");

const MediaType
MediaType::APPLICATION_JAVA_ARCHIVE = MediaType::register(
    "application/java-archive", "Java archive");

const MediaType
MediaType::APPLICATION_JAVA_OBJECT = MediaType::register(
    "application/x-java-serialized-object",
    "Java serialized object");

const MediaType
MediaType::APPLICATION_JAVA_OBJECT_XML = MediaType::register(
    "application/x-java-serialized-object+xml",
    "Java serialized object (using JavaBeans XML encoder)");

const MediaType
MediaType::APPLICATION_JAVA_OBJECT_GWT = MediaType::register(
    "application/x-java-serialized-object+gwt",
    "Java serialized object (using GWT-RPC encoder)");

const MediaType
MediaType::APPLICATION_JAVASCRIPT = MediaType::register(
    "application/x-javascript", "Javascript document");

const MediaType
MediaType::APPLICATION_JNLP = MediaType::register(
    "application/x-java-jnlp-file", "JNLP");

const MediaType
MediaType::APPLICATION_JSON = MediaType::register(
    "application/json", "JavaScript Object Notation document");

const MediaType
MediaType::APPLICATION_KML = MediaType::register(
    "application/vnd.google-earth.kml+xml",
    "Google Earth/Maps KML document");

const MediaType
MediaType::APPLICATION_KMZ = MediaType::register(
    "application/vnd.google-earth.kmz",
    "Google Earth/Maps KMZ document");

const MediaType
MediaType::APPLICATION_LATEX = MediaType::register(
    "application/x-latex", "LaTeX");

const MediaType
MediaType::APPLICATION_MAC_BINHEX40 = MediaType::register(
    "application/mac-binhex40", "Mac binhex40");

const MediaType
MediaType::APPLICATION_MATHML = MediaType::register(
    "application/mathml+xml", "MathML XML document");

const MediaType
MediaType::APPLICATION_MATHML_XML = MediaType::register(
    "application/mathml+xml", "MathML XML document");

const MediaType
MediaType::APPLICATION_MSOFFICE_DOCM = MediaType::register(
    "application/vnd.ms-word.document.macroEnabled.12",
    "Office Word 2007 macro-enabled document");

const MediaType
MediaType::APPLICATION_MSOFFICE_DOCX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document",
    "Microsoft Office Word 2007 document");

const MediaType
MediaType::APPLICATION_MSOFFICE_DOTM = MediaType::register(
    "application/vnd.ms-word.template.macroEnabled.12",
    "Office Word 2007 macro-enabled document template");

const MediaType
MediaType::APPLICATION_MSOFFICE_DOTX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.wordprocessingml.template",
    "Office Word 2007 template");

const MediaType
MediaType::APPLICATION_MSOFFICE_ONETOC = MediaType::register(
    "application/onenote", "Microsoft Office OneNote 2007 TOC");

const MediaType
MediaType::APPLICATION_MSOFFICE_ONETOC2 = MediaType::register(
    "application/onenote", "Office OneNote 2007 TOC");

const MediaType
MediaType::APPLICATION_MSOFFICE_POTM = MediaType::register(
    "application/vnd.ms-powerpoint.template.macroEnabled.12",
    "Office PowerPoint 2007 macro-enabled presentation template");

const MediaType
MediaType::APPLICATION_MSOFFICE_POTX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.presentationml.template",
    "Office PowerPoint 2007 template");

const MediaType
MediaType::APPLICATION_MSOFFICE_PPAM = MediaType::register(
    "application/vnd.ms-powerpoint.addin.macroEnabled.12",
    "Office PowerPoint 2007 add-in");

const MediaType
MediaType::APPLICATION_MSOFFICE_PPSM = MediaType::register(
    "application/vnd.ms-powerpoint.slideshow.macroEnabled.12",
    "Office PowerPoint 2007 macro-enabled slide show");

const MediaType
MediaType::APPLICATION_MSOFFICE_PPSX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.presentationml.slideshow",
    "Office PowerPoint 2007 slide show");

const MediaType
MediaType::APPLICATION_MSOFFICE_PPTM = MediaType::register(
    "application/vnd.ms-powerpoint.presentation.macroEnabled.12",
    "Office PowerPoint 2007 macro-enabled presentation");

const MediaType
MediaType::APPLICATION_MSOFFICE_PPTX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.presentationml.presentation",
    "Microsoft Office PowerPoint 2007 presentation");

const MediaType
MediaType::APPLICATION_MSOFFICE_SLDM = MediaType::register(
    "application/vnd.ms-powerpoint.slide.macroEnabled.12",
    "Office PowerPoint 2007 macro-enabled slide");

const MediaType
MediaType::APPLICATION_MSOFFICE_SLDX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.presentationml.slide",
    "Office PowerPoint 2007 slide");

const MediaType
MediaType::APPLICATION_MSOFFICE_XLAM = MediaType::register(
    "application/vnd.ms-excel.addin.macroEnabled.12",
    "Office Excel 2007 add-in");

const MediaType
MediaType::APPLICATION_MSOFFICE_XLSB = MediaType::register(
    "application/vnd.ms-excel.sheet.binary.macroEnabled.12",
    "Office Excel 2007 binary workbook");

const MediaType
MediaType::APPLICATION_MSOFFICE_XLSM = MediaType::register(
    "application/vnd.ms-excel.sheet.macroEnabled.12",
    "Office Excel 2007 macro-enabled workbook");

const MediaType
MediaType::APPLICATION_MSOFFICE_XLSX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
    "Microsoft Office Excel 2007 workbook");

const MediaType
MediaType::APPLICATION_MSOFFICE_XLTM = MediaType::register(
    "application/vnd.ms-excel.template.macroEnabled.12",
    "Office Excel 2007 macro-enabled workbook template");

const MediaType
MediaType::APPLICATION_MSOFFICE_XLTX = MediaType::register(
    "application/vnd.openxmlformats-officedocument.spreadsheetml.template",
    "Office Excel 2007 template");

const MediaType
MediaType::APPLICATION_OCTET_STREAM = MediaType::register(
    "application/octet-stream", "Raw octet stream");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODB = MediaType::register(
    "application/vnd.oasis.opendocument.database",
    "OpenDocument Database");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODC = MediaType::register(
    "application/vnd.oasis.opendocument.chart", "OpenDocument Chart");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODF = MediaType::register(
    "application/vnd.oasis.opendocument.formula",
    "OpenDocument Formula");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODG = MediaType::register(
    "application/vnd.oasis.opendocument.graphics",
    "OpenDocument Drawing");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODI = MediaType::register(
    "application/vnd.oasis.opendocument.image", "OpenDocument Image ");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODM = MediaType::register(
    "application/vnd.oasis.opendocument.text-master",
    "OpenDocument Master Document");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODP = MediaType::register(
    "application/vnd.oasis.opendocument.presentation",
    "OpenDocument Presentation ");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODS = MediaType::register(
    "application/vnd.oasis.opendocument.spreadsheet",
    "OpenDocument Spreadsheet");

const MediaType
MediaType::APPLICATION_OPENOFFICE_ODT = MediaType::register(
    "application/vnd.oasis.opendocument.text ", "OpenDocument Text");

const MediaType
MediaType::APPLICATION_OPENOFFICE_OTG = MediaType::register(
    "application/vnd.oasis.opendocument.graphics-template",
    "OpenDocument Drawing Template");

const MediaType
MediaType::APPLICATION_OPENOFFICE_OTH = MediaType::register(
    "application/vnd.oasis.opendocument.text-web",
    "HTML Document Template");

const MediaType
MediaType::APPLICATION_OPENOFFICE_OTP = MediaType::register(
    "application/vnd.oasis.opendocument.presentation-template",
    "OpenDocument Presentation Template");

const MediaType
MediaType::APPLICATION_OPENOFFICE_OTS = MediaType::register(
    "application/vnd.oasis.opendocument.spreadsheet-template",
    "OpenDocument Spreadsheet Template");

const MediaType
MediaType::APPLICATION_OPENOFFICE_OTT = MediaType::register(
    "application/vnd.oasis.opendocument.text-template",
    "OpenDocument Text Template");

const MediaType
MediaType::APPLICATION_OPENOFFICE_OXT = MediaType::register(
    "application/vnd.openofficeorg.extension",
    "OpenOffice.org extension");

const MediaType
MediaType::APPLICATION_PDF = MediaType::register("application/pdf",
                                                 "Adobe PDF document");

const MediaType
MediaType::APPLICATION_POSTSCRIPT = MediaType::register(
    "application/postscript", "Postscript document");

const MediaType
MediaType::APPLICATION_POWERPOINT = MediaType::register(
    "application/vnd.ms-powerpoint", "Microsoft Powerpoint document");

const MediaType
MediaType::APPLICATION_PROJECT = MediaType::register(
    "application/vnd.ms-project", "Microsoft Project document");

const MediaType
MediaType::APPLICATION_RDF_TRIG = MediaType::register(
    "application/x-trig",
    "Plain text serialized Resource Description Framework document");

const MediaType
MediaType::APPLICATION_RDF_TRIX = MediaType::register(
    "application/trix",
    "Simple XML serialized Resource Description Framework document");

const MediaType
MediaType::APPLICATION_RDF_TURTLE = MediaType::register(
    "application/x-turtle",
    "Plain text serialized Resource Description Framework document");

const MediaType
MediaType::APPLICATION_RDF_XML = MediaType::register(
    "application/rdf+xml",
    "Normalized XML serialized Resource Description Framework document");

const MediaType
MediaType::APPLICATION_RELAXNG_COMPACT = MediaType::register(
    "application/relax-ng-compact-syntax",
    "Relax NG Schema document, Compact syntax");

const MediaType
MediaType::APPLICATION_RELAXNG_XML = MediaType::register(
    "application/x-relax-ng+xml",
    "Relax NG Schema document, XML syntax");

const MediaType
MediaType::APPLICATION_RSS = MediaType::register(
    "application/rss+xml", "Really Simple Syndication document");

const MediaType
MediaType::APPLICATION_RSS_XML = MediaType::register(
    "application/rss+xml", "Really Simple Syndication document");

const MediaType
MediaType::APPLICATION_RTF = MediaType::register("application/rtf",
                                                 "Rich Text Format document");

const MediaType
MediaType::APPLICATION_SPARQL_RESULTS_JSON = MediaType::register(
    "application/sparql-results+json",
    "SPARQL Query Results JSON document");

const MediaType
MediaType::APPLICATION_SPARQL_RESULTS_XML = MediaType::register(
    "application/sparql-results+xml",
    "SPARQL Query Results XML document");

const MediaType
MediaType::APPLICATION_SPSS_SAV = MediaType::register(
    "application/x-spss-sav", "SPSS Data");

const MediaType
MediaType::APPLICATION_SPSS_SPS = MediaType::register(
    "application/x-spss-sps", "SPSS Script Syntax");

const MediaType
MediaType::APPLICATION_STATA_STA = MediaType::register(
    "application/x-stata", "Stata data file");

const MediaType
MediaType::APPLICATION_STUFFIT = MediaType::register(
    "application/x-stuffit", "Stuffit archive");

const MediaType
MediaType::APPLICATION_TAR = MediaType::register(
    "application/x-tar", "Tar archive");

const MediaType
MediaType::APPLICATION_TEX = MediaType::register(
    "application/x-tex", "Tex file");

const MediaType
MediaType::APPLICATION_TROFF_MAN = MediaType::register(
    "application/x-troff-man", "LaTeX");

const MediaType
MediaType::APPLICATION_VOICEXML = MediaType::register(
    "application/voicexml+xml", "VoiceXML");

const MediaType
MediaType::APPLICATION_W3C_SCHEMA = MediaType::register(
    "application/x-xsd+xml", "W3C XML Schema document");

const MediaType
MediaType::APPLICATION_W3C_SCHEMA_XML = MediaType::register(
    "application/x-xsd+xml", "W3C XML Schema document");

const MediaType
MediaType::APPLICATION_W3C_XSLT = MediaType::register(
    "application/xslt+xml", "W3C XSLT Stylesheet");

const MediaType
MediaType::APPLICATION_WADL = MediaType::register(
    "application/vnd.sun.wadl+xml",
    "Web Application Description Language document");

const MediaType
MediaType::APPLICATION_WADL_XML = MediaType::register(
    "application/vnd.sun.wadl+xml",
    "Web Application Description Language document");

const MediaType
MediaType::APPLICATION_WORD = MediaType::register(
    "application/msword", "Microsoft Word document");

const MediaType
MediaType::APPLICATION_WWW_FORM = MediaType::register(
    "application/x-www-form-urlencoded", "Web form (URL encoded)");

const MediaType
MediaType::APPLICATION_XHTML = MediaType::register(
    "application/xhtml+xml", "XHTML document");

const MediaType
MediaType::APPLICATION_XHTML_XML = MediaType::register(
    "application/xhtml+xml", "XHTML document");

const MediaType
MediaType::APPLICATION_XML = MediaType::register("application/xml",
                                                 "XML document");

const MediaType
MediaType::APPLICATION_XML_DTD = MediaType::register(
    "application/xml-dtd", "XML DTD");

const MediaType
MediaType::APPLICATION_XUL = MediaType::register(
    "application/vnd.mozilla.xul+xml", "XUL document");

const MediaType
MediaType::APPLICATION_ZIP = MediaType::register("application/zip",
                                                 "Zip archive");

const MediaType
MediaType::AUDIO_ALL = MediaType::register("audio/*", "All audios");

const MediaType
MediaType::AUDIO_BASIC = MediaType::register(
    "audio/basic", "AU audio");

const MediaType
MediaType::AUDIO_MIDI = MediaType::register("audio/midi",
                                            "MIDI audio");

const MediaType
MediaType::AUDIO_MPEG = MediaType::register("audio/mpeg",
                                            "MPEG audio (MP3)");

const MediaType
MediaType::AUDIO_REAL = MediaType::register("audio/x-pn-realaudio",
                                            "Real audio");

const MediaType
MediaType::AUDIO_WAV = MediaType::register("audio/x-wav",
                                           "Waveform audio");

const MediaType
MediaType::IMAGE_ALL = MediaType::register("image/*", "All images");

const MediaType
MediaType::IMAGE_BMP = MediaType::register("image/bmp",
                                           "Windows bitmap");

const MediaType
MediaType::IMAGE_GIF = MediaType::register("image/gif", "GIF image");

const MediaType
MediaType::IMAGE_ICON = MediaType::register("image/x-icon",
                                            "Windows icon (Favicon)");

const MediaType
MediaType::IMAGE_JPEG = MediaType::register("image/jpeg",
                                            "JPEG image");

const MediaType
MediaType::IMAGE_PNG = MediaType::register("image/png", "PNG image");

const MediaType
MediaType::IMAGE_SVG = MediaType::register("image/svg+xml",
                                           "Scalable Vector Graphics");

const MediaType
MediaType::IMAGE_TIFF = MediaType::register("image/tiff",
                                            "TIFF image");

const MediaType
MediaType::MESSAGE_ALL = MediaType::register("message/*",
                                             "All messages");

const MediaType
MediaType::MODEL_ALL = MediaType::register("model/*", "All models");

const MediaType
MediaType::MODEL_VRML = MediaType::register("model/vrml", "VRML");

const MediaType
MediaType::MULTIPART_ALL = MediaType::register("multipart/*",
                                               "All multipart data");

const MediaType
MediaType::MULTIPART_FORM_DATA = MediaType::register(
    "multipart/form-data", "Multipart form data");

const MediaType
MediaType::TEXT_ALL = MediaType::register("text/*", "All texts");

const MediaType
MediaType::TEXT_CALENDAR = MediaType::register("text/calendar",
                                               "iCalendar event");

const MediaType
MediaType::TEXT_CSS = MediaType::register("text/css",
                                          "CSS stylesheet");

const MediaType
MediaType::TEXT_CSV = MediaType::register("text/csv",
                                          "Comma-separated Values");

const MediaType
MediaType::TEXT_DAT = MediaType::register("text/x-fixed-field",
                                          "Fixed-width Values");

const MediaType
MediaType::TEXT_HTML = MediaType::register("text/html",
                                           "HTML document");

const MediaType
MediaType::TEXT_J2ME_APP_DESCRIPTOR = MediaType::register(
    "text/vnd.sun.j2me.app-descriptor", "J2ME Application Descriptor");

const MediaType
MediaType::TEXT_JAVASCRIPT = MediaType::register("text/javascript",
                                                 "Javascript document");

const MediaType
MediaType::TEXT_PLAIN = MediaType::register("text/plain",
                                            "Plain text");

const MediaType
MediaType::TEXT_RDF_N3 = MediaType::register(
    "text/n3","N3 serialized Resource Description Framework document");

const MediaType
MediaType::TEXT_RDF_NTRIPLES = MediaType::register(
    "text/n-triples",
    "N-Triples serialized Resource Description Framework document");

const MediaType
MediaType::TEXT_TSV = MediaType::register(
    "text/tab-separated-values", "Tab-separated Values");

const MediaType
MediaType::TEXT_URI_LIST = MediaType::register("text/uri-list",
                                               "List of URIs");

const MediaType
MediaType::TEXT_VCARD = MediaType::register("text/x-vcard", "vCard");

const MediaType
MediaType::TEXT_XML = MediaType::register("text/xml", "XML text");

const MediaType
MediaType::VIDEO_ALL = MediaType::register("video/*", "All videos");

const MediaType
MediaType::VIDEO_AVI = MediaType::register("video/x-msvideo",
                                           "AVI video");

const MediaType
MediaType::VIDEO_MP4 = MediaType::register("video/mp4",
                                           "MPEG-4 video");

const MediaType
MediaType::VIDEO_MPEG = MediaType::register("video/mpeg",
                                            "MPEG video");

const MediaType
MediaType::VIDEO_QUICKTIME = MediaType::register("video/quicktime",
                                                 "Quicktime video");

const MediaType
MediaType::VIDEO_WMV = MediaType::register("video/x-ms-wmv",
                                           "Windows movie");

const std::string MediaType::_TSPECIALS("()<>@,;:/[]?=\\\"");

std::map<std::string, MediaType> MediaType::_types = NULL;


static MediaType MediaType::getMostSpecific(MediaType... mediaTypes)
    throws IllegalArgumentException {
  if ((mediaTypes == NULL) || (mediaTypes.length == 0)) {
    throw new IllegalArgumentException(
        "You must give at least one MediaType");
  }

  if (mediaTypes.length == 1) {
    return mediaTypes[0];
  }

  MediaType mostSpecific = mediaTypes[mediaTypes.length - 1];

  for (int i = mediaTypes.length - 2; i >= 0; i--) {
    const MediaType mediaType = mediaTypes[i];

    if (mediaType.getMainType().equals("*")) {
      continue;
    }

    if (mostSpecific.getMainType().equals("*")) {
      mostSpecific = mediaType;
      continue;
    }

    if (mostSpecific.getSubType().contains("*")) {
      mostSpecific = mediaType;
      continue;
    }
  }

  return mostSpecific;
}

static MediaType MediaType::register(std::string name,
                                     std::string description) {

  if (!getTypes().containsKey(name)) {
    const MediaType type = new MediaType(name, description);
    getTypes().put(name, type);
  }

  return getTypes().get(name);
}

static MediaType MediaType::valueOf(std::string name) {
  MediaType result = NULL;

  if ((name != NULL) && !name.equals("")) {
    result = getTypes().get(name);
    if (result == NULL) {
      result = new MediaType(name);
    }
  }

  return result;
}

//@SuppressWarnings("unchecked")
MediaType::MediaType(std::string name, Series<Parameter> parameters,
                     std::string description) {
  Metadata(normalizeType(name), description);

  if (parameters != NULL) {
    this->parameters = (Series<Parameter>) Series
                       .unmodifiableSeries(parameters);
  }
}

bool MediaType::equals(Object obj, bool ignoreParameters) {
  bool result = (obj == this);

  // if obj == this no need to go further
  if (!result) {
    // test for equality at Metadata level i.e. name and value.
    if (super.equals(obj)) {
      // if obj isn't a mediatype or is NULL don't evaluate further
      if (obj instanceof MediaType) {
        const MediaType that = (MediaType) obj;
        result = ignoreParameters
                 || getParameters().equals(that.getParameters());
      }
    }
  }

  return result;
}

std::string MediaType::getMainType() {
  std::string result = NULL;

  if (getName() != NULL) {
    int index = getName().indexOf('/');

    // Some clients appear to use name types without subtypes
    if (index == -1) {
      index = getName().indexOf(';');
    }

    if (index == -1) {
      result = getName();
    } else {
      result = getName().substring(0, index);
    }
  }

  return result;
}

Series<Parameter> MediaType::getParameters() {
  // Lazy initialization with double-check.
  Series<Parameter> p = this->parameters;
  if (p == NULL) {
    synchronized (this) {
      p = this->parameters;
      if (p == NULL) {
        Form params = NULL;

        if (getName() != NULL) {
          int index = getName().indexOf(';');

          if (index != -1) {
            params = new Form(getName().substring(index + 1)
                              .trim(), ';');
          }
        }

        if (params == NULL) {
          params = new Form();
        }

        this->parameters = p = (Series<Parameter>) Series
                           .unmodifiableSeries(params);
      }
    }
  }
  return p;
}

MediaType MediaType::getParent() {
  MediaType result = NULL;

  if (getSubType().equals("*")) {
    result = equals(ALL) ? NULL : ALL;
  } else {
    result = MediaType.valueOf(getMainType() + "/*");
  }

  return result;
}

std::string MediaType::getSubType() {
  std::string result = NULL;

  if (getName() != NULL) {
    const int slash = getName().indexOf('/');

    if (slash == -1) {
      // No subtype found, assume that all subtypes are accepted
      result = "*";
    } else {
      const int separator = getName().indexOf(';');
      if (separator == -1) {
        result = getName().substring(slash + 1);
      } else {
        result = getName().substring(slash + 1, separator);
      }
    }
  }

  return result;
}

int MediaType::hashCode() {
  return SystemUtils.hashCode(super.hashCode(), getParameters());
}

bool MediaType::includes(Metadata included) {
  bool result = equals(ALL) || (included == NULL) || equals(included);

  if (!result && (included instanceof MediaType)) {
    MediaType includedMediaType = (MediaType) included;

    if (getMainType().equals(includedMediaType.getMainType())) {
      // Both media types are different
      if (getSubType().equals(includedMediaType.getSubType())) {
        result = true;
      } else if (getSubType().equals("*")) {
        result = true;
      } else if (getSubType().startsWith("*+")
                 && includedMediaType.getSubType().endsWith(
                     getSubType().substring(2))) {
        result = true;
      }
    }
  }

  return result;
}

std::string MediaType::toString() {
  const StringBuilder sb = new StringBuilder();

  if (getName() != NULL) {
    sb.append(getName());

    for (const Parameter param : getParameters()) {
      sb.append("; ").append(param.getName()).append('=').append(
          param.getValue());
    }
  }
  return sb.toString();
}

static std::map<std::string, MediaType>
MediaType::getTypes() {
  if (_types == NULL) {
    _types = new HashMap<std::string, MediaType>();
  }
  return _types;
}

static std::string MediaType::normalizeToken(std::string token) {
  int length;
  char c;

  // Makes sure we're not dealing with a "*" token.
  token = token.trim();
  if ("".equals(token) || "*".equals(token))
    return "*";

  // Makes sure the token is RFC compliant.
  length = token.length();
  for (int i = 0; i < length; i++) {
    c = token.charAt(i);
    if (c <= 32 || c >= 127 || _TSPECIALS.indexOf(c) != -1)
      throw new IllegalArgumentException("Illegal token: " + token);
  }

  return token;
}

static std::string MediaType::normalizeType(std::string name) {
  int slashIndex;
  int colonIndex;
  std::string mainType;
  std::string subType;
  std::string parameters = NULL;

  // Ignore NULL names (backward compatibility).
  if (name == NULL)
    return NULL;

  // Check presence of parameters
  if ((colonIndex = name.indexOf(';')) != -1) {
    parameters = name.substring(colonIndex + 1);
    name = name.substring(0, colonIndex);
  }

  // No main / sub separator, assumes name/*.
  if ((slashIndex = name.indexOf('/')) == -1) {
    mainType = normalizeToken(name);
    subType = "*";
  }

  // Normalizes the main and sub types.
  else {
    mainType = normalizeToken(name.substring(0, slashIndex));
    subType = normalizeToken(name.substring(slashIndex + 1));
  }

  return (parameters == NULL) ? mainType + '/' + subType : mainType + '/'
      + subType + ";" + parameters;
}

} // namespace data
} // namespace echo
