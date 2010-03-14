#ifndef _ECHO_DATA_LOCAL_REFERENCE_H_
#define _ECHO_DATA_LOCAL_REFERENCE_H_
                                     
/*import java.io.File;*/

#include <string>

namespace echo {
namespace data {

/**
 * Reference to a local resource. It has helper methods for the three following
 * schemes: {@link Protocol#CLAP}, {@link Protocol#FILE}, {@link Protocol#JAR}
 * and {@link Protocol#RIAP}.
 * 
 * @author Jerome Louvel
 */
//public final class LocalReference extends Reference {
class LocalReference : public Reference {

 public:

  /**
   * Constructor.
   * 
   * @param authorityType
   *            The authority type for the resource path.
   * @param path
   *            The resource path.
   */
  static LocalReference
  createClapReference(int authorityType,std::string path);

  /**
   * Constructor.
   * 
   * @param file
   *            The file whose path must be used.
   * @return The new local reference.
   * @see #createFileReference(std::string)
   */
  static LocalReference createFileReference(File file) {
    return createFileReference(file.getAbsolutePath());
  }

  /**
   * Constructor.
   * 
   * @param filePath
   *            The local file path.
   * @see #createFileReference(std::string, std::string)
   */
  static LocalReference createFileReference(std::string filePath) {
    return createFileReference("", filePath);
  }

  /**
   * Constructor.
   * 
   * @param hostName
   *            The authority (can be a host name or the special "localhost"
   *            or an empty value).
   * @param filePath
   *            The file path.
   */
  static LocalReference
  createFileReference(std::string hostName,std::string filePath);

  /**
   * Constructor.
   * 
   * @param jarFile
   *            The JAR file reference.
   * @param entryPath
   *            The entry path inside the JAR file.
   */
  static LocalReference
  createJarReference(Reference jarFile,std::string entryPath);

  /**
   * Constructor.
   * 
   * @param authorityType
   *            The authority type for the resource path.
   * @param path
   *            The resource path.
   */
  static LocalReference
  createRiapReference(int authorityType,std::string path);

  /**
   * Constructor.
   * 
   * @param zipFile
   *            The Zip file reference.
   * @param entryPath
   *            The entry path inside the Zip file.
   */
  static LocalReference
  createZipReference(Reference zipFile,std::string entryPath);

  /**
   * Returns an authority name.
   * 
   * @param authority
   *            The authority.
   * @return The name.
   */
  static std::string getAuthorityName(int authority);

  /**
   * Localize a path by converting all the separator characters to the
   * system-dependent separator character.
   * 
   * @param path
   *            The path to localize.
   * @return The localized path.
   */
  static std::string localizePath(std::string path);

  /**
   * Normalize a path by converting all the system-dependent separator
   * characters to the standard '/' separator character.
   * 
   * @param path
   *            The path to normalize.
   * @return The normalize path.
   */
  static std::string normalizePath(std::string path);

  /**
   * Constructor.
   * 
   * @param localRef
   *            The local reference.
   */
  LocalReference(Reference localRef) {
    Reference(localRef.toString());
  }

  /**
   * Constructor.
   * 
   * @param localUri
   *            The local URI.
   */
  LocalReference(std::string localUri) {
    Reference(localUri);
  }

  /**
   * Returns the type of authority.
   * 
   * @return The type of authority.
   */
  int getClapAuthorityType();

  /**
   * Gets the local file corresponding to the reference. Only URIs referring
   * to the "localhost" or to an empty authority are supported.
   * 
   * @return The local file corresponding to the reference.
   */
  File getFile();

  /**
   * Returns the JAR entry path.
   * 
   * @return The JAR entry path.
   */
  std::string getJarEntryPath();

  /**
   * Returns the JAR file reference.
   * 
   * @return The JAR file reference.
   */
  Reference getJarFileRef();

  /**
   * Returns the type of authority.
   * 
   * @return The type of authority.
   */
  int getRiapAuthorityType();

 public:

  
  /**
   * The resources will be resolved from the classloader associated with the
   * local class. Examples: clap://class/rootPkg/subPkg/myClass.class or
   * clap://class/rootPkg/file.html
   * 
   * @see java.lang.Class#getClassLoader()
   */
  static const int CLAP_CLASS;

  /**
   * The resources will be resolved from the system's classloader. Examples:
   * clap://system/rootPkg/subPkg/myClass.class or
   * clap://system/rootPkg/file.html
   * 
   * @see java.lang.ClassLoader#getSystemClassLoader()
   */
  static const int CLAP_SYSTEM;

  /**
   * The resources will be resolved from the current thread's classloader.
   * Examples: clap://thread/rootPkg/subPkg/myClass.class or
   * clap://thread/rootPkg/file.html
   * 
   * @see java.lang.Thread#getContextClassLoader()
   */
  static const int CLAP_THREAD;

  /**
   * The resources will be resolved from the current application's root
   * Restlet. Example riap://application/myPath/myResource
   */
  static const int RIAP_APPLICATION;

  /**
   * The resources will be resolved from the current component's internal
   * (private) router. Example riap://component/myAppPath/myResource
   */
  static const int RIAP_COMPONENT;

  /**
   * The resources will be resolved from the current component's virtual host.
   * Example riap://host/myAppPath/myResource
   */
  static const int RIAP_HOST;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_LOCAL_REFERENCE_H_
