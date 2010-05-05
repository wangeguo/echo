#ifndef _ECHO_DATA_PROTOCOL_H_
#define _ECHO_DATA_PROTOCOL_H_

#include <string>

namespace echo {
namespace data {

/**
 * Protocol used by client and server connectors. Connectors enable the
 * communication between components by implementing standard protocols.
 * 
 * @author Jerome Louvel
 */
//public final class Protocol {
class Protocol {

 public:

  /**
   * Creates the protocol associated to a URI scheme name. If an existing
   * constant exists then it is returned, otherwise a new instance is created.
   * 
   * @param name
   *            The scheme name.
   * @return The associated protocol.
   */
  static Protocol valueOf(const std::string name);

  /**
   * Constructor.
   * 
   * @param schemeName
   *            The scheme name.
   */
  Protocol(const std::string schemeName);

  /**
   * Constructor.
   * 
   * @param schemeName
   *            The scheme name.
   * @param name
   *            The unique name.
   * @param description
   *            The description.
   * @param defaultPort
   *            The default port.
   */
  Protocol(const std::string schemeName, const std::string name,
           const std::string description, int defaultPort) {
    Protocol(schemeName, name, description, defaultPort, false);
  }

  /**
   * Constructor.
   * 
   * @param schemeName
   *            The scheme name.
   * @param name
   *            The unique name.
   * @param description
   *            The description.
   * @param defaultPort
   *            The default port.
   * @param confidential
   *            The confidentiality.
   */
  Protocol(const std::string schemeName, const std::string name,
           const std::string description, int defaultPort,
           const bool confidential);

  /** {@inheritDoc} */
  //@Override
  bool equals(const Object object);

  /**
   * Returns the default port number.
   * 
   * @return The default port number.
   */
  int getDefaultPort() {
    return this->defaultPort;
  }

  /**
   * Returns the description.
   * 
   * @return The description.
   */
  std::string getDescription() {
    return this->description;
  }

  /**
   * Returns the name.
   * 
   * @return The name.
   */
  std::string getName() {
    return name;
  }

  /**
   * Returns the URI scheme name.
   * 
   * @return The URI scheme name.
   */
  std::string getSchemeName() {
    return this->schemeName;
  }

  /** {@inheritDoc} */
  //@Override
  int hashCode() {
    return (getName() == null) ? 0 : getName().toLowerCase().hashCode();
  }

  /**
   * Indicates if the protocol guarantees the confidentially of the messages
   * exchanged, for example via a SSL-secured connection.
   * 
   * @return True if the protocol is confidential.
   */
  bool isConfidential() {
    return this->confidential;
  }

  /**
   * Returns the name.
   * 
   * @return The name.
   */
  //@Override
  std::string toString() {
    return getName();
  }

 public:

  /** Indicates that the port number is undefined. */
  static const int UNKNOWN_PORT;

  /**
   * AJP 1.3 protocol to communicate with Apache HTTP server or Microsoft IIS.
   */
  static const Protocol AJP;

  /** All protocols wildcard. */
  static const Protocol ALL;

  /**
   * CLAP (ClassLoader Access Protocol) is a custom scheme to access to
   * representations via classloaders. Example URI:
   * "clap://thread/org/restlet/Restlet.class".<br>
   * <br>
   * In order to work, CLAP requires a client connector provided by the core
   * Restlet engine.
   * 
   * @see org.restlet.data.LocalReference
   */
  static const Protocol CLAP;

  /**
   * FILE is a standard scheme to access to representations stored in the file
   * system (locally most of the time). Example URI:
   * "file:///D/root/index.html".<br>
   * <br>
   * In order to work, FILE requires a client connector provided by the core
   * Restlet engine.
   * 
   * @see org.restlet.data.LocalReference
   */
  static const Protocol FILE;

  /** FTP protocol. */
  static const Protocol FTP;

  /** HTTP protocol. */
  static const Protocol HTTP;

  /** HTTPS protocol (via SSL socket). */
  static const Protocol HTTPS;

  /**
   * JAR (Java ARchive) is a common scheme to access to representations inside
   * archive files. Example URI:
   * "jar:http://www.foo.com/bar/baz.jar!/COM/foo/Quux.class".
   * 
   * @see org.restlet.data.LocalReference#createJarReference(Reference,
   *      std::string)
   */
  static const Protocol JAR;

  /** JDBC protocol. */
  static const Protocol JDBC;

  /** POP protocol. */
  static const Protocol POP;

  /** POPS protocol (via SSL/TLS socket).. */
  static const Protocol POPS;

  /**
   * RIAP (Restlet Internal Access Protocol) is a custom scheme to access
   * representations via internal calls to virtual hosts/components. Example
   * URIs: "riap://component/myAppPath/myResource" and
   * "riap://application/myResource".<br>
   * <br>
   * In order to work, RIAP doesn't requires any client connector and is
   * automatically supported by the Restlet engine.
   * 
   * @see org.restlet.data.LocalReference
   */
  static const Protocol RIAP;

  /** SMTP protocol. */
  static const Protocol SMTP;

  /** SMTPS protocol (via SSL/TLS socket). */
  static const Protocol SMTPS;

  /** Local Web Archive access protocol. */
  static const Protocol WAR;

  /**
   * ZIP is a special scheme to access to representations inside Zip archive
   * files. Example URI: "zip:file:///tmp/test.zip!/test.txt".
   * 
   * @see org.restlet.data.LocalReference#createZipReference(Reference,
   *      std::string)
   */
  static const Protocol ZIP;

 private:

  /** The confidentiality. */
  volatile bool confidential;

  /** The default port if known or -1. */
  volatile int defaultPort;

  /** The description. */
  const std::string description;

  /** The name. */
  volatile std::string name;

  /** The scheme name. */
  volatile std::string schemeName;


};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_PROTOCOL_H_
