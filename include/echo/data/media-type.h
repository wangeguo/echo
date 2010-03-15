#ifndef _ECHO_DATA_MEDIA_TYPE_H_
#define _ECHO_DATA_MEDIA_TYPE_H_
/*
  import java.util.HashMap;
*/
#include <map>
#include <string>

#include <echo/engine/util/system-utils.h>
#include <echo/util/series.h>

namespace echo {
namespace data {

/**
 * Media type used in representations and preferences.
 * 
 * @see <a href="http://en.wikipedia.org/wiki/MIME">MIME types on Wikipedia</a>
 * @author Jerome Louvel
 */
//public final class MediaType extends Metadata {
class MediaType : public Metadata {

 public:

  /**
   * Returns the first of the most specific MediaTypes of the given array of
   * MediaTypes.
   * <p>
   * Examples:
   * <ul>
   * <li>"text/plain" is more specific than "text/*" or "image/*"</li>
   * <li>"text/html" is same specific as "application/pdf" or "image/jpg"</li>
   * <li>"text/*" is same specific than "application/*" or "image/*"</li>
   * <li>"*<!----->/*" is the must unspecific MediaType</li>
   * </ul>
   * 
   * @param mediaTypes
   *            An array of media types.
   * @return The most concrete MediaType.
   * @throws IllegalArgumentException
   *             If the array is NULL or empty.
   */
  static MediaType
  getMostSpecific(MediaType... mediaTypes) throws IllegalArgumentException;

  /**
   * Register a media type as a known type that can later be retrieved using
   * {@link #valueOf(std::string)}. If the type already exists, the existing type
   * is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The name.
   * @param description
   *            The description.
   * @return The registered media type
   */
  static MediaType register(std::string name, std::string description);

  /**
   * Returns the media type associated to a name. If an existing constant
   * exists then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The name.
   * @return The associated media type.
   */
  static MediaType valueOf(std::string name);

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   */
  MediaType(std::string name) {
    MediaType(name, NULL, "Media type or range of media types");
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param parameters
   *            The list of parameters.
   */
  MediaType(std::string name, Series<Parameter> parameters) {
    MediaType(name, parameters, "Media type or range of media types");
  }

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param parameters
   *            The list of parameters.
   * @param description
   *            The description.
   */
  //@SuppressWarnings("unchecked")
  MediaType(std::string name, Series<Parameter> parameters,
            std::string description);

  /**
   * Constructor.
   * 
   * @param name
   *            The name.
   * @param description
   *            The description.
   */
  MediaType(std::string name, std::string description) {
    MediaType(name, NULL, description);
  }

  /** {@inheritDoc} */
  //@Override
  bool equals(Object obj) {
    return equals(obj, false);
  }

  /**
   * Test the equality of two media types, with the possibility to ignore the
   * parameters.
   * 
   * @param obj
   *            The object to compare to.
   * @param ignoreParameters
   *            Indicates if parameters should be ignored during comparison.
   * @return True if both media types are equal.
   */
  bool equals(Object obj, bool ignoreParameters);

  /**
   * Returns the main type.
   * 
   * @return The main type.
   */
  std::string getMainType();

  /**
   * Returns the unmodifiable list of parameters. Creates a new instance if no
   * one has been set.
   * 
   * @return The list of parameters.
   */
  //@SuppressWarnings("unchecked")
  Series<Parameter> getParameters();

  //@Override
  MediaType getParent();

  /**
   * Returns the sub-type.
   * 
   * @return The sub-type.
   */
  std::string getSubType();

  /** {@inheritDoc} */
  //@Override
  int hashCode();

  /**
   * Indicates if a given media type is included in the current one. The test
   * is true if both types are equal or if the given media type is within the
   * range of the current one. For example, ALL includes all media types.
   * Parameters are ignored for this comparison. A NULL media type is
   * considered as included into the current one.
   * <p>
   * Examples:
   * <ul>
   * <li>TEXT_ALL.includes(TEXT_PLAIN) -> true</li>
   * <li>TEXT_PLAIN.includes(TEXT_ALL) -> false</li>
   * </ul>
   * 
   * @param included
   *            The media type to test for inclusion.
   * @return True if the given media type is included in the current one.
   * @see #isCompatible(Metadata)
   */
  bool includes(Metadata included);

  /**
   * Checks if the current media type is concrete. A media type is concrete if
   * neither the main type nor the sub-type are equal to "*".
   * 
   * @return True if this media type is concrete.
   */
  bool isConcrete() {
    return !getName().contains("*");
  }

  //@Override
  std::string toString();

 private:
  
  /**
   * Returns the known media types map.
   * 
   * @return the known media types map.
   */
  static std::map<std::string, MediaType> getTypes();

  /**
   * Normalizes the specified token.
   * 
   * @param token
   *            Token to normalize.
   * @return The normalized token.
   * @throws IllegalArgumentException
   *             if <code>token</code> is not legal.
   */
  static std::string normalizeToken(std::string token);

  /**
   * Normalizes the specified media type.
   * 
   * @param name
   *            The name of the type to normalize.
   * @return The normalized type.
   */
  static std::string normalizeType(std::string name);
  

 public:

  static const MediaType ALL;

  static const MediaType APPLICATION_ALL;

  static const MediaType APPLICATION_ALL_XML;

  static const MediaType APPLICATION_ATOM;

  /**
   * @deprecated Use {@link #APPLICATION_ATOMPUB_SERVICE} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_ATOM_SERVICE_XML;

  /**
   * @deprecated Use {@link #APPLICATION_ATOMPUB_SERVICE} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_ATOM_XML;

  static const MediaType APPLICATION_ATOMPUB_CATEGORY;

  static const MediaType APPLICATION_ATOMPUB_SERVICE;

  static const MediaType APPLICATION_CAB;

  static const MediaType APPLICATION_COMPRESS;

  static const MediaType APPLICATION_EXCEL;

  static const MediaType APPLICATION_FLASH;

  static const MediaType APPLICATION_GNU_TAR;

  static const MediaType APPLICATION_GNU_ZIP;

  static const MediaType APPLICATION_HTTP_COOKIES;

  static const MediaType APPLICATION_JAVA;

  static const MediaType APPLICATION_JAVA_ARCHIVE;

  static const MediaType APPLICATION_JAVA_OBJECT;

  static const MediaType APPLICATION_JAVA_OBJECT_XML;

  static const MediaType APPLICATION_JAVA_OBJECT_GWT;

  static const MediaType APPLICATION_JAVASCRIPT;

  static const MediaType APPLICATION_JNLP;

  static const MediaType APPLICATION_JSON;

  static const MediaType APPLICATION_KML;

  static const MediaType APPLICATION_KMZ;

  static const MediaType APPLICATION_LATEX;

  static const MediaType APPLICATION_MAC_BINHEX40;

  static const MediaType APPLICATION_MATHML;

  /**
   * @deprecated Use {@link #APPLICATION_MATHML} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_MATHML_XML;

  static const MediaType APPLICATION_MSOFFICE_DOCM;

  static const MediaType APPLICATION_MSOFFICE_DOCX;

  static const MediaType APPLICATION_MSOFFICE_DOTM;

  static const MediaType APPLICATION_MSOFFICE_DOTX;

  static const MediaType APPLICATION_MSOFFICE_ONETOC;

  static const MediaType APPLICATION_MSOFFICE_ONETOC2;

  static const MediaType APPLICATION_MSOFFICE_POTM;

  static const MediaType APPLICATION_MSOFFICE_POTX;

  static const MediaType APPLICATION_MSOFFICE_PPAM;

  static const MediaType APPLICATION_MSOFFICE_PPSM;

  static const MediaType APPLICATION_MSOFFICE_PPSX;

  static const MediaType APPLICATION_MSOFFICE_PPTM;

  static const MediaType APPLICATION_MSOFFICE_PPTX;

  static const MediaType APPLICATION_MSOFFICE_SLDM;

  static const MediaType APPLICATION_MSOFFICE_SLDX;

  static const MediaType APPLICATION_MSOFFICE_XLAM;

  static const MediaType APPLICATION_MSOFFICE_XLSB;

  static const MediaType APPLICATION_MSOFFICE_XLSM;

  static const MediaType APPLICATION_MSOFFICE_XLSX;

  static const MediaType APPLICATION_MSOFFICE_XLTM;

  static const MediaType APPLICATION_MSOFFICE_XLTX;

  static const MediaType APPLICATION_OCTET_STREAM;

  static const MediaType APPLICATION_OPENOFFICE_ODB;

  static const MediaType APPLICATION_OPENOFFICE_ODC;

  static const MediaType APPLICATION_OPENOFFICE_ODF;

  static const MediaType APPLICATION_OPENOFFICE_ODG;

  static const MediaType APPLICATION_OPENOFFICE_ODI;

  static const MediaType APPLICATION_OPENOFFICE_ODM;

  static const MediaType APPLICATION_OPENOFFICE_ODP;

  static const MediaType APPLICATION_OPENOFFICE_ODS;

  static const MediaType APPLICATION_OPENOFFICE_ODT;

  static const MediaType APPLICATION_OPENOFFICE_OTG;

  static const MediaType APPLICATION_OPENOFFICE_OTH;

  static const MediaType APPLICATION_OPENOFFICE_OTP;

  static const MediaType APPLICATION_OPENOFFICE_OTS;

  static const MediaType APPLICATION_OPENOFFICE_OTT;

  static const MediaType APPLICATION_OPENOFFICE_OXT;

  static const MediaType APPLICATION_PDF;

  static const MediaType APPLICATION_POSTSCRIPT;

  static const MediaType APPLICATION_POWERPOINT;

  static const MediaType APPLICATION_PROJECT;

  static const MediaType APPLICATION_RDF_TRIG;

  static const MediaType APPLICATION_RDF_TRIX;

  static const MediaType APPLICATION_RDF_TURTLE;

  static const MediaType APPLICATION_RDF_XML;

  static const MediaType APPLICATION_RELAXNG_COMPACT;

  static const MediaType APPLICATION_RELAXNG_XML;

  static const MediaType APPLICATION_RSS;

  /**
   * @deprecated Use {@link #APPLICATION_RSS} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_RSS_XML;

  static const MediaType APPLICATION_RTF;

  static const MediaType APPLICATION_SPARQL_RESULTS_JSON;

  static const MediaType APPLICATION_SPARQL_RESULTS_XML;

  static const MediaType APPLICATION_SPSS_SAV;

  static const MediaType APPLICATION_SPSS_SPS;

  static const MediaType APPLICATION_STATA_STA;

  static const MediaType APPLICATION_STUFFIT;

  static const MediaType APPLICATION_TAR;

  static const MediaType APPLICATION_TEX;

  static const MediaType APPLICATION_TROFF_MAN;

  static const MediaType APPLICATION_VOICEXML;

  static const MediaType APPLICATION_W3C_SCHEMA

  /**
   * @deprecated Use {@link #APPLICATION_W3C_SCHEMA} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_W3C_SCHEMA_XML;

  static const MediaType APPLICATION_W3C_XSLT;

  static const MediaType APPLICATION_WADL;
  /**
   * @deprecated Use {@link #APPLICATION_WADL} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_WADL_XML;

  static const MediaType APPLICATION_WORD;

  static const MediaType APPLICATION_WWW_FORM;

  static const MediaType APPLICATION_XHTML;

  /**
   * @deprecated Use {@link #APPLICATION_XHTML} instead.
   */
  //@Deprecated
  static const MediaType APPLICATION_XHTML_XML;

  static const MediaType APPLICATION_XML;

  static const MediaType APPLICATION_XML_DTD;

  static const MediaType APPLICATION_XUL;

  static const MediaType APPLICATION_ZIP;

  static const MediaType AUDIO_ALL;

  static const MediaType AUDIO_BASIC;

  static const MediaType AUDIO_MIDI;

  static const MediaType AUDIO_MPEG;

  static const MediaType AUDIO_REAL;

  static const MediaType AUDIO_WAV;

  static const MediaType IMAGE_ALL;

  static const MediaType IMAGE_BMP;

  static const MediaType IMAGE_GIF;

  static const MediaType IMAGE_ICON;

  static const MediaType IMAGE_JPEG;

  static const MediaType IMAGE_PNG;

  static const MediaType IMAGE_SVG;

  static const MediaType IMAGE_TIFF;

  static const MediaType MESSAGE_ALL;

  static const MediaType MODEL_ALL;

  static const MediaType MODEL_VRML;

  static const MediaType MULTIPART_ALL;

  static const MediaType MULTIPART_FORM_DATA;

  static const MediaType TEXT_ALL;

  static const MediaType TEXT_CALENDAR;

  static const MediaType TEXT_CSS;

  static const MediaType TEXT_CSV;

  static const MediaType TEXT_DAT;

  static const MediaType TEXT_HTML;

  static const MediaType TEXT_J2ME_APP_DESCRIPTOR;

  static const MediaType TEXT_JAVASCRIPT;

  static const MediaType TEXT_PLAIN;

  static const MediaType TEXT_RDF_N3;

  static const MediaType TEXT_RDF_NTRIPLES;

  static const MediaType TEXT_TSV;

  static const MediaType TEXT_URI_LIST;

  static const MediaType TEXT_VCARD;

  static const MediaType TEXT_XML;

  static const MediaType VIDEO_ALL;

  static const MediaType VIDEO_AVI;

  static const MediaType VIDEO_MP4;

  static const MediaType VIDEO_MPEG;

  static const MediaType VIDEO_QUICKTIME;

  static const MediaType VIDEO_WMV;

 private:

  /** The list of parameters. */
  volatile Series<Parameter> parameters;

  /**
   * Illegal ASCII characters as defined in RFC 1521.<br>
   * Keep the underscore for the ordering
   * 
   * @see http://www.ietf.org/rfc/rfc1521.txt
   * 
   */
  static const std::string _TSPECIALS;

  /**
   * The known media types registered with {@link #register(std::string, std::string)},
   * retrievable using {@link #valueOf(std::string)}.<br>
   * Keep the underscore for the ordering.
   */
  static volatile std::map<std::string, MediaType> _types;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_MEDIA_TYPE_H_
