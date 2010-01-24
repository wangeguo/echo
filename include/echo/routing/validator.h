#ifndef _ECHO_ROUTING_VALIDATOR_H_
#define _ECHO_ROUTING_VALIDATOR_H_

/*
  import java.util.concurrent.CopyOnWriteArrayList;
  import java.util.regex.Pattern;

*/

#include <list>
#include <string>

#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/status.h>

namespace echo {
namespace routing {

/**
 * Filter validating attributes from a call. Validation is verified based on
 * regex pattern matching.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @author Jerome Louvel
 * @see Pattern
 */
class Validator : public echo::routing::Filter {

 public:
  /**
   * Constructor.
   */
  Validator() {
    Validator(null);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   */
  Validator(echo::Context context) {
    Validator(context, null);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   * @param next
   *            The next Echo.
   */
  Validator(echo::Context context, Echo::Echo next) {
    Filter(context, next);
  }

 protected:     
  /**
   * Allows filtering before its handling by the target Echo. By default it
   * parses the template variable, adjust the base reference, then extracts
   * the attributes from form parameters (query, cookies, entity) and finally
   * tries to validates the variables as indicated by the
   * {@link #validate(std::string, bool, std::string)} method.
   * 
   * @param request
   *            The request to filter.
   * @param response
   *            The response to filter.
   * @return The continuation status.
   */
  //@Override
  int beforeHandle(echo::Request request, echo::Response response) {
    if (validations != null) {
      for (final ValidateInfo validate : getValidations()) {
        if (validate.required
            && !request.getAttributes().containsKey(
                validate.attribute)) {
          response
              .setStatus(
                  Status.CLIENT_ERROR_BAD_REQUEST,
                  "Unable to find the \""
                  + validate.attribute
                  + "\" attribute in the request. Please check your request.");
        } else if (validate.format != null) {
          final Object value = request.getAttributes().get(
              validate.attribute);
          if (value == null) {
            response
                .setStatus(
                    Status.CLIENT_ERROR_BAD_REQUEST,
                    "Unable to validate the \""
                    + validate.attribute
                    + "\" attribute with a null value. Please check your request.");
          } else {
            if (!Pattern.matches(validate.format, value.toString())) {
              response
                  .setStatus(
                      Status.CLIENT_ERROR_BAD_REQUEST,
                      "Unable to validate the value of the \""
                      + validate.attribute
                      + "\" attribute. The expected format is: "
                      + validate.format
                      + " (Java Regex). Please check your request.");
            }
          }
        }
      }
    }

    return CONTINUE;
  }

  /**
   * Checks the request attributes for presence, format, etc. If the check
   * fails, then a response status CLIENT_ERROR_BAD_REQUEST is returned with
   * the proper status description.
   * 
   * @param attribute
   *            Name of the attribute to look for.
   * @param required
   *            Indicates if the attribute presence is required.
   * @param format
   *            Format of the attribute value, using Regex pattern syntax.
   */
  void validate(std::string attribute, bool required, std::string format) {
    getValidations().add(new ValidateInfo(attribute, required, format));
  }

 private:    
  /** Internal class holding validation information. */
  static const class ValidateInfo {

   public:
    /**
     * Constructor.
     * 
     * @param attribute
     *            Name of the attribute to look for.
     * @param required
     *            Indicates if the attribute presence is required.
     * @param format
     *            Format of the attribute value, using Regex pattern syntax.
     */
    ValidateInfo(std::string attribute, bool required, std::string format) {
      this->attribute = attribute;
      this->required = required;
      this->format = format;
    }

   protected:
    /** Name of the attribute to look for. */
    std::string attribute;

    /** Format of the attribute value, using Regex pattern syntax. */
    std::string format;

    /** Indicates if the attribute presence is required. */
    bool required;

  };

    
  /**
   * Returns the list of attribute validations.
   * 
   * @return The list of attribute validations.
   */
  std::list<ValidateInfo> getValidations() {
    // Lazy initialization with double-check.
    std::list<ValidateInfo> v = validations;
    if (v == null) {
      synchronized (this) {
        v = validations;
        if (v == null) {
          validations = v = new CopyOnWriteArrayList<ValidateInfo>();
        }
      }
    }
    return v;
  }

  /** The list of attribute validations. */
  volatile std::list<ValidateInfo> validations;
    
};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_VALIDATOR_H_
