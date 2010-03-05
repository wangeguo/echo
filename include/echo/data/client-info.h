#ifndef _ECHO_DATA_CLIENT_INFO_H_
#define _ECHO_DATA_CLIENT_INFO_H_

/*
  import java.io.BufferedReader;
  import java.io.IOException;
  import java.io.InputStreamReader;
  import java.util.ArrayList;
  import java.util.HashMap;
*/
#include <string>
#include <list>
#include <map>

#include <echo/context.h>
#include <echo/engine/engine.h>
#include <echo/representation/variant.h>

namespace echo {
namespace data {

/**
 * Client specific data related to a call. When extracted from a request, most
 * of these data are directly taken from the underlying headers. There are some
 * exceptions: agentAttributes and mainAgentProduct which are taken from the
 * agent name (for example the "user-agent" header for HTTP requests).<br>
 * <br>
 * As described by the HTTP specification, the "user-agent" can be seen as a
 * ordered list of products name (ie a name and a version) and/or comments.<br>
 * <br>
 * Each HTTP client (mainly browsers and web crawlers) defines its own
 * "user-agent" header which can be seen as the "signature" of the client.
 * Unfortunately, there is no rule to identify clearly a kind a client and its
 * version (let's say firefox 2.x, Internet Explorer IE 7.0, Opera, etc)
 * according to its signature. Each signature follow its own rules which may
 * vary according to the version of the client.<br>
 * <br>
 * In order to help retrieving interesting data such as product name (Firefox,
 * IE, etc), version, operating system, Restlet users has the ability to define
 * their own way to extract data from the "user-agent" header. It is based on a
 * list of templates declared in a file called "agent.properties" and located in
 * the classpath in the sub directory "org/restlet/data". Each template
 * describes a typical user-agent string and allows to use predefined variables
 * that help to retrieve the content of the agent name, version, operating
 * system.<br>
 * <br>
 * The "user-agent" string is confronted to the each template from the beginning
 * of the property file to the end. The loop stops at the first matched
 * template.<br>
 * <br>
 * Here is a sample of such template:<br>
 * 
 * <pre>
 * #Firefox for Windows
 *  Mozilla/{mozillaVersion} (Windows; U; {agentOs}; {osData}; rv:{releaseVersion}) Gecko/{geckoReleaseDate} {agentName}/{agentVersion}
 * </pre>
 * 
 * This template matches the "user-agent" string of the Firefox client for
 * windows:
 * 
 * <pre>
 *  Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1) Gecko/20060918 Firefox/2.0
 * </pre>
 * 
 * At this time, six predefined variables are used:<br>
 * <table>
 * <tr>
 * <th>Name</th>
 * <th>Description</th>
 * </tr>
 * <tr>
 * <td>agentName</td>
 * <td>Name of the user agent (i.e.: Firefox)</td>
 * </tr>
 * <tr>
 * <td>agentVersion</td>
 * <td>Version of the user agent</td>
 * </tr>
 * <tr>
 * <td>agentOs</td>
 * <td>Operating system of the user agent</td>
 * </tr>
 * <tr>
 * <td>agentComment</td>
 * <td>Comment string, that is to say a sequence of characters enclosed "(", or
 * ")"</td>
 * </tr>
 * <tr>
 * <td>commentAttribute</td>
 * <td>A sequence of characters enclosed by ";", "(", or ")"</td>
 * </tr>
 * <tr>
 * <td>facultativeData</td>
 * <td>A sequence of characters that can be empty</td>
 * </tr>
 * </table>
 * <br>
 * <br>
 * These variables are used to generate a {@link Product} instance with the main
 * data (name, version, comment). This instance is accessible via the
 * {@link ClientInfo#getMainAgentProduct()} method. All other variables used in
 * the template aims at catching a sequence of characters and are accessible via
 * the {@link ClientInfo#getAgentAttributes()} method.
 * 
 * @author Jerome Louvel
 */
//public final class ClientInfo {
class ClientInfo {

 public:

  /**
   * Constructor.
   */
  ClientInfo();

  /**
   * Returns the modifiable list of character set preferences. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Charset" header.
   * 
   * @return The character set preferences.
   */
  std::list<Preference<CharacterSet>> getAcceptedCharacterSets();

  /**
   * Returns the modifiable list of encoding preferences. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Encoding" header.
   * 
   * @return The encoding preferences.
   */
  std::list<Preference<Encoding>> getAcceptedEncodings();

  /**
   * Returns the modifiable list of language preferences. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Language" header.
   * 
   * @return The language preferences.
   */
  std::list<Preference<Language>> getAcceptedLanguages();

  /**
   * Returns the modifiable list of media type preferences. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept" header.
   * 
   * @return The media type preferences.
   */
  std::list<Preference<MediaType>> getAcceptedMediaTypes();

  /**
   * Returns the immediate client's IP address. If the real client is
   * separated from the server by a proxy server, this will return the IP
   * address of the proxy.
   * 
   * @return The immediate client's IP address.
   * @see #getUpstreamAddress()
   * @see #getForwardedAddresses()
   */
  std::string getAddress() {
    return this->address;
  }

  /**
   * Returns the list of client IP addresses.<br>
   * <br>
   * The first address is the one of the immediate client component as
   * returned by the getClientAdress() method and the last address should
   * correspond to the origin client (frequently a user agent).<br>
   * <br>
   * This is useful when the user agent is separated from the origin server by
   * a chain of intermediary components. Creates a new instance if no one has
   * been set.
   * 
   * @return The client IP addresses.
   * @deprecated Use the {@link #getForwardedAddresses()} method instead.
   */
  //@Deprecated
  std::list<std::string> getAddresses() {
    return getForwardedAddresses();
  }

  /**
   * Returns the agent name (ex: "Restlet-Framework/2.0").<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "User-Agent" header.
   * 
   * @return The agent name.
   */
  std::string getAgent() {
    return this->agent;
  }

  /**
   * Returns a list of attributes taken from the name of the user agent.
   * 
   * @return A list of attributes taken from the name of the user agent.
   * @see #getAgent()
   */
  std::map<std::string, std::string> getAgentAttributes();

  /**
   * Returns the name of the user agent.
   * 
   * @return The name of the user agent.
   * @see #getAgent()
   */
  std::string getAgentName();

  /**
   * Returns the list of product tokens from the user agent name.
   * 
   * @return The list of product tokens from the user agent name.
   * @see #getAgent()
   */
  std::list<Product> getAgentProducts();

  /**
   * Returns the version of the user agent.
   * 
   * @return The version of the user agent.
   * @see #getAgent()
   */
  std::string getAgentVersion();

  /**
   * Returns the list of forwarded IP addresses.<br>
   * <br>
   * This is useful when the user agent is separated from the origin server by
   * a chain of intermediary components. Creates a new instance if no one has
   * been set. <br>
   * <br>
   * The first address is the one of the immediate client component and the
   * last address should correspond to the origin client (frequently a user
   * agent).<br>
   * <br>
   * This information is only safe for intermediary components within your
   * local network. Other addresses could easily be changed by setting a fake
   * header and should not be trusted for serious security checks.<br>
   * <br>
   * Note that your HTTP server connectors have a special
   * "useForwardedForHeader" parameter that you need to explicitly set to
   * "true" in order to activate this feature due to potential security
   * issues.
   * 
   * @return The list of forwarded IP addresses.
   * @see <a href="http://en.wikipedia.org/wiki/X-Forwarded-For">Wikipedia
   *      page for the "X-Forwarded-For" HTTP header</a>
   */
  std::list<std::string> getForwardedAddresses();
  /**
   * Returns the email address of the human user controlling the user agent.
   * Default value is null.
   * 
   * @return The email address of the human user controlling the user agent.
   */
  std::string getFrom() {
    return from;
  }

  /**
   * Returns a Product object based on the name of the user agent.
   * 
   * @return A Product object based on name of the user agent.
   */
  Product getMainAgentProduct();

  /**
   * Returns the port number which sent the call. If no port is specified, -1
   * is returned.
   * 
   * @return The port number which sent the call.
   */
  int getPort() {
    return this->port;
  }

  /**
   * Returns the preferred character set among a list of supported ones, based
   * on the client preferences.
   * 
   * @param supported
   *            The supported character sets.
   * @return The preferred character set.
   */
  CharacterSet getPreferredCharacterSet(std::list<CharacterSet> supported);
  /**
   * Returns the preferred encoding among a list of supported ones, based on
   * the client preferences.
   * 
   * @param supported
   *            The supported encodings.
   * @return The preferred encoding.
   */
  Encoding getPreferredEncoding(std::list<Encoding> supported);

  /**
   * Returns the preferred language among a list of supported ones, based on
   * the client preferences.
   * 
   * @param supported
   *            The supported languages.
   * @return The preferred language.
   */
  Language getPreferredLanguage(std::list<Language> supported);

  /**
   * Returns the preferred media type among a list of supported ones, based on
   * the client preferences.
   * 
   * @param supported
   *            The supported media types.
   * @return The preferred media type.
   */
  MediaType getPreferredMediaType(std::list<MediaType> supported);

  /**
   * Returns the best variant for a given resource according the the client
   * preferences: accepted languages, accepted character sets, accepted media
   * types and accepted encodings.<br>
   * A default language is provided in case the variants don't match the
   * client preferences.
   * 
   * @param variants
   *            The list of variants to compare.
   * @param metadataService
   *            The metadata service.
   * @return The best variant.
   * @see <a
   *      href="http://httpd.apache.org/docs/2.2/en/content-negotiation.html#algorithm">Apache
   *      content negotiation algorithm</a>
   */
  Variant getPreferredVariant(std::list<Variant> variants,
                              org.restlet.service.MetadataService metadataService);

  /**
   * Returns the best variant for a given resource according the the client
   * preferences.<br>
   * A default language is provided in case the resource's variants don't
   * match the client preferences.
   * 
   * @param resource
   *            The resource for which the best representation needs to be
   *            set.
   * @param metadataService
   *            The metadata service.
   * @return The best variant.
   * @see <a
   *      href="http://httpd.apache.org/docs/2.2/en/content-negotiation.html#algorithm">Apache
   *      content negotiation algorithm</a>
   * @deprecated Used
   *             {@link #getPreferredVariant(List, org.restlet.service.MetadataService)}
   *             instead.
   */
  //@Deprecated
  Variant getPreferredVariant(org.restlet.resource.Resource resource,
                              org.restlet.service.MetadataService metadataService);

  /**
   * Returns the client principals.
   * 
   * @return The client principals.
   */
  std::list<java.security.Principal> getPrincipals();

  /**
   * Returns the authenticated user roles.
   * 
   * @return The authenticated user roles.
   */
  n  std::list<org.restlet.security.Role> getRoles();

  /**
   * Returns the IP address of the upstream client component. In general this
   * will correspond the the user agent IP address. This is useful if there
   * are intermediary components like proxies and load balancers.
   * 
   * If the supporting {@link #getForwardedAddresses()} method returns a non
   * empty list, the IP address will be the first element. Otherwise, the
   * value of {@link #getAddress()} will be returned.<br>
   * <br>
   * Note that your HTTP server connectors have a special
   * "useForwardedForHeader" parameter that you need to explicitly set to
   * "true" in order to activate this feature due to potential security
   * issues.
   * 
   * @return The most upstream IP address.
   */
  std::string getUpstreamAddress();

  /**
   * Returns the authenticated user.
   * 
   * @return The authenticated user.
   */
  org.restlet.security.User getUser() {
    return user;
  }

  /**
   * Indicates if the identifier or principal has been authenticated. The
   * application is responsible for updating this property, relying on a
   * {@link org.restlet.security.Guard} or manually.
   * 
   * @return True if the identifier or principal has been authenticated.
   */
  bool isAuthenticated() {
    return this->authenticated;
  }

  /**
   * Sets the character set preferences.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Charset" header.
   * 
   * @param acceptedCharacterSets
   *            The character set preferences.
   */
  void setAcceptedCharacterSets(
      std::list<Preference<CharacterSet>> acceptedCharacterSets) {
    this->acceptedCharacterSets = acceptedCharacterSets;
  }

  /**
   * Sets the encoding preferences.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Encoding" header.
   * 
   * @param acceptedEncodings
   *            The encoding preferences.
   */
  void setAcceptedEncodings(
      std::list<Preference<Encoding>> acceptedEncodings) {
    this->acceptedEncodings = acceptedEncodings;
  }

  /**
   * Sets the language preferences.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Language" header.
   * 
   * @param acceptedLanguages
   *            The language preferences.
   */
  void setAcceptedLanguages(
      std::list<Preference<Language>> acceptedLanguages) {
    this->acceptedLanguages = acceptedLanguages;
  }

  /**
   * Sets the media type preferences.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept" header.
   * 
   * @param acceptedMediaTypes
   *            The media type preferences.
   */
  void setAcceptedMediaTypes(
      std::list<Preference<MediaType>> acceptedMediaTypes) {
    this->acceptedMediaTypes = acceptedMediaTypes;
  }

  /**
   * Sets the client's IP address.
   * 
   * @param address
   *            The client's IP address.
   */
  void setAddress(std::string address) {
    this->address = address;
  }

  /**
   * Sets the list of client IP addresses.
   * 
   * @param addresses
   *            The list of client IP addresses.
   * @deprecated See the {@link #setForwardedAddresses(std::list)} method instead.
   */
  //@Deprecated
  void setAddresses(std::list<std::string> addresses) {
    setForwardedAddresses(addresses);
  }

  /**
   * Sets the agent name (ex: "Restlet-Framework/2.0").<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "User-Agent" header.
   * 
   * @param agent
   *            The agent name.
   */
  void setAgent(std::string agent) {
    this->agent = agent;
  }

  /**
   * Indicates if the identifier or principal has been authenticated. The
   * application is responsible for updating this property, relying on a
   * {@link org.restlet.security.Guard} or manually.
   * 
   * @param authenticated
   *            True if the identifier or principal has been authenticated.
   */
  void setAuthenticated(bool authenticated) {
    this->authenticated = authenticated;
  }

  /**
   * Sets the list of forwarded IP addresses.
   * 
   * @param forwardedAddresses
   *            The list of forwarded IP addresses.
   * @see #getForwardedAddresses()
   */
  void setForwardedAddresses(std::list<std::string> forwardedAddresses) {
    this->forwardedAddresses = forwardedAddresses;
  }

  /**
   * Sets the email address of the human user controlling the user agent.
   * 
   * @param from
   *            The email address of the human user controlling the user
   *            agent.
   */
  void setFrom(std::string from) {
    this->from = from;
  }

  /**
   * Sets the port number which sent the call.
   * 
   * @param port
   *            The port number which sent the call.
   */
  void setPort(int port) {
    this->port = port;
  }

  /**
   * Sets the user principals.
   * 
   * @param principals
   *            The user principals.
   */
  void setPrincipals(std::list<java.security.Principal> principals) {
    this->principals = principals;
  }

  /**
   * Sets the authenticated user roles.
   * 
   * @param roles
   *            The authenticated user roles.
   */
  void setRoles(std::list<org.restlet.security.Role> roles) {
    this->roles = roles;
  }

  /**
   * Sets the authenticated user.
   * 
   * @param user
   *            The authenticated user.
   */
  void setUser(org.restlet.security.User user) {
    this->user = user;
  }

 private:
  /**
   * Returns the list of user-agent templates defined in "agent.properties"
   * file.
   * 
   * @return The list of user-agent templates defined in "agent.properties"
   *         file.
   * @see The {@link ClientInfo#getAgentAttributes()} method.
   */
  static std::list<std::string> getUserAgentTemplates();
  

 private:  
  /**
   * std::list of user-agent templates defined in "agent.properties" file.<br>
   * 
   * @see The {@link ClientInfo#getAgentAttributes()} method.
   */
  static std::list<std::string> userAgentTemplates = null;

  /** The character set preferences. */
  volatile std::list<Preference<CharacterSet>> acceptedCharacterSets;

  /** The encoding preferences. */
  volatile std::list<Preference<Encoding>> acceptedEncodings;

  /** The language preferences. */
  volatile std::list<Preference<Language>> acceptedLanguages;

  /** The media preferences. */
  volatile std::list<Preference<MediaType>> acceptedMediaTypes;

  /** The immediate IP addresses. */
  volatile std::string address;

  /** The email address of the human user controlling the user agent. */
  volatile std::string from;

  /** The agent name. */
  volatile std::string agent;

  /** The attributes data taken from the agent name. */
  volatile std::map<std::string, std::string> agentAttributes;

  /** The main product data taken from the agent name. */
  volatile Product agentMainProduct;

  /** The list of product tokens taken from the agent name. */
  volatile std::list<Product> agentProducts;

  /**
   * Indicates if the subject has been authenticated. The application is
   * responsible for updating this property, relying on
   * {@link org.restlet.security.Authenticator} or manually.
   */
  volatile bool authenticated;

  /** The forwarded IP addresses. */
  volatile std::list<std::string> forwardedAddresses;

  /** The port number. */
  volatile int port;

  /** List of security principals. */
  volatile std::list<java.security.Principal> principals;

  /** Authenticated user. */
  volatile org.restlet.security.User user;

  /** List of user roles. */
  volatile std::list<org.restlet.security.Role> roles;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CLIENT_INFO_H_
