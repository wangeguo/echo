#ifndef _ECHO_DATA_SERVER_INFO_H_
#define _ECHO_DATA_SERVER_INFO_H_

#include <string>

namespace echo {
namespace data {

/**
 * Server specific data related to a call.
 * 
 * @author Jerome Louvel
 */
//public final class ServerInfo {
class ServerInfo {

 public:

  /**
   * Constructor.
   */
  ServerInfo() {
    this->address = null;
    this->agent = null;
    this->port = -1;
    this->acceptingRanges = false;
  }

  /**
   * Returns the IP address.
   * 
   * @return The IP address.
   */
  std::string getAddress() {
    return this->address;
  }

  /**
   * Returns the agent name (ex: "Restlet-Framework/2.0").<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Server" header.
   * 
   * @return The agent name.
   */
  std::string getAgent() {
    return this->agent;
  }

  /**
   * Returns the port number which received the call. If no port is specified,
   * -1 is returned.
   * 
   * @return The port number which received the call.
   */
  int getPort() {
    return this->port;
  }

  /**
   * Return true if the server accepts range requests for a resource.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Ranges" header.
   * 
   * @return True if the server accepts range requests for a resource.
   */
  bool isAcceptingRanges() {
    return isAcceptRanges();
  }

  /**
   * Return true if the server accepts range requests for a resource.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Ranges" header.
   * 
   * @return True if the server accepts range requests for a resource.
   * @deprecated Use {@link #isAcceptingRanges()} instead.
   */
  //@Deprecated
  bool isAcceptRanges() {
    return acceptingRanges;
  }

  /**
   * Indicates if the server accepts range requests for a resource.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Ranges" header.
   * 
   * @param acceptingRanges
   *            True if the server accepts range requests for a resource.
   */
  void setAcceptingRanges(bool acceptingRanges) {
    setAcceptRanges(acceptingRanges);
  }

  /**
   * Indicates if the server accepts range requests for a resource.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Accept-Ranges" header.
   * 
   * @param acceptingRanges
   *            True if the server accepts range requests for a resource.
   * @deprecated Use {@link #setAcceptingRanges(bool)} instead.
   */
  //@Deprecated
  void setAcceptRanges(bool acceptingRanges) {
    this->acceptingRanges = acceptingRanges;
  }

  /**
   * Sets the IP address which received the call.
   * 
   * @param address
   *            The IP address which received the call.
   */
  void setAddress(std::string address) {
    this->address = address;
  }

  /**
   * Sets the agent name (ex: "Restlet-Framework/2.0").<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "Server" header.
   * 
   * @param agent
   *            The agent name.
   */
  void setAgent(std::string agent) {
    this->agent = agent;
  }

  /**
   * Sets the port number which received the call.
   * 
   * @param port
   *            The port number which received the call.
   */
  void setPort(int port) {
    this->port = port;
  }


 private:

  /** Indicates if the server accepts range requests for a resource. */
  volatile bool acceptingRanges;

  /** The IP address. */
  volatile std::string address;

  /** The agent name. */
  volatile std::string agent;

  /** The port number. */
  volatile int port;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_SERVER_INFO_H_
