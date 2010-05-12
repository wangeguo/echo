#ifndef _ECHO_DATA_WARNING_H_
#define _ECHO_DATA_WARNING_H_

//import java.util.Date;
#include <string>

namespace echo {
namespace data {

/**
 * Additional information about the status or transformation of a request or
 * response. This is typically used to warn about a possible issues with caching
 * operations or transformations applied to the entity body.<br>
 * <br>
 * Note that when used with HTTP connectors, this class maps to the "Warning"
 * header.
 * 
 * @author Jerome Louvel
 */
class Warning {

 public:
  
  /**
   * Constructor.
   */
  Warning() {
    this->agent = NULL;
    this->date = NULL;
    this->status = NULL;
    this->text = NULL;
  }

  /**
   * Returns the agent. Typically a caching agent.
   * 
   * @return The agent. Typically a caching agent.
   */
  std::string getAgent() {
    return agent;
  }

  /**
   * Returns the warning date.
   * 
   * @return The warning date.
   */
  Date getDate() {
    return date;
  }

  /**
   * Returns the special status.
   * 
   * @return The special status.
   */
  Status getStatus() {
    return status;
  }

  /**
   * Returns the warning text.
   * 
   * @return The warning text.
   */
  std::string getText() {
    return text;
  }

  /**
   * Sets the agent. Typically a caching agent.
   * 
   * @param agent
   *            The agent. Typically a caching agent.
   */
  void setAgent(std::string agent) {
    this->agent = agent;
  }

  /**
   * Sets the warning date.
   * 
   * @param date
   *            The warning date.
   */
  void setDate(Date date) {
    this->date = date;
  }

  /**
   * Sets the special status.
   * 
   * @param status
   *            The special status.
   */
  void setStatus(Status status) {
    this->status = status;
  }

  /**
   * Sets the warning text.
   * 
   * @param text
   *            The warning text.
   */
  void setText(std::string text) {
    this->text = text;
  }

 private:

  /** The agent. Typically a caching agent. */
  volatile std::string agent;

  /** The warning date. */
  volatile Date date;

  /** The special status. */
  volatile Status status;

  /** The warning text. */
  volatile std::string text;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_WARNING_H_
