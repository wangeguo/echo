#include <echo/routing/validator.h>

namespace echo {
namespace routing {

int Validator::beforeHandle(echo::Request request, echo::Response response) {
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

void Validator::validate(std::string attribute, bool required, std::string format) {
  getValidations().add(new ValidateInfo(attribute, required, format));
}

std::list<ValidateInfo> Validator::getValidations() {
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

} // namespace routing
} // namespace echo

