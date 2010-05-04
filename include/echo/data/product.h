#ifndef _ECHO_DATA_PRODUCT_H_
#define _ECHO_DATA_PRODUCT_H_

#include <string>

namespace echo {
namespace data {

/**
 * Product tokens are used to allow communicating applications to identify
 * themselves by software name and version.
 * 
 * @author Thierry Boileau
 * @see <a href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.43">User-Agent</a>
 * @see <a href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.8">Product Tokens</a>
 */
class Product {

 public:

  /**
   * Constructor.
   * 
   * @param name
   *            The product name.
   * @param version
   *            The product version.
   * @param comment
   *            The product comment.
   */
  Product(std::string name, std::string version, std::string comment) {
    //super();
    this->name = name;
    this->version = version;
    this->comment = comment;
  }

  /**
   * Returns the facultative comment.
   * 
   * @return The facultative comment.
   */
  std::string getComment() {
    return this->comment;
  }

  /**
   * Returns the product name.
   * 
   * @return The product name.
   */
  std::string getName() {
    return this->name;
  }

  /**
   * Returns the version of the product.
   * 
   * @return The version of the product.
   */
  std::string getVersion() {
    return this->version;
  }

  /**
   * Sets the facultative comment.
   * 
   * @param comment
   *            The facultative comment.
   */
  void setComment(std::string comment) {
    this->comment = comment;
  }

  /**
   * Sets the product name.
   * 
   * @param name
   *            The product name.
   */
  void setName(std::string name) {
    this->name = name;
  }

  /**
   * Sets the version of the product.
   * 
   * @param version
   *            The version of the product.
   */
  void setVersion(std::string version) {
    this->version = version;
  }

 private:

  /** Comment. */
  volatile std::string comment;

  /** Product name. */
  volatile std::string name;

  /** Version number. */
  volatile std::string version;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_PRODUCT_H_
