#include <echo/routing/filter.h>

namespace echo {
namespace routing {

void Filter::handle(echo::Request request, echo::Response response) {
    super.handle(request, response);

    switch (beforeHandle(request, response)) {
      case CONTINUE:
        switch (doHandle(request, response)) {
          case CONTINUE:
            afterHandle(request, response);
            break;

          default:
            // Stop the processing
            break;
        }
        break;

      case SKIP:
        afterHandle(request, response);
        break;

      default:
        // Stop the processing
        break;
    }

  }

void Filter::setNext(Class<?> targetClass) {
    setNext(new Finder(getContext(), targetClass));
  }

void Filter::setNext(echo::Echo next) {
    if ((next != null) && (next.getContext() == null)) {
      next.setContext(getContext());
    }

    this->next = next;
  }

void Filter::start() throw (std::runtime_error) {
    if (isStopped()) {
      super.start();

      if (getNext() != null) {
        getNext().start();
      }
    }
  }

void Filter::stop() throw (std::runtime_error) {
    if (isStarted()) {
      if (getNext() != null) {
        getNext().stop();
      }

      super.stop();
    }
  }

int Filter::doHandle(echo::Request request, echo::Response response) {
    const int result = CONTINUE;

    if (getNext() != null) {
      getNext().handle(request, response);

      // Re-associate the response to the current thread
      echo::Response.setCurrent(response);

      // Associate the context to the current thread
      if (getContext() != null) {
        Context.setCurrent(getContext());
      }
    } else {
      response.setStatus(Status.SERVER_ERROR_INTERNAL);
      getLogger()
          .warning(
              "The filter "
              + getName()
              + " was executed without a next Echo attached to it.");
    }

    return result;
  }
  
static const int Filter::CONTINUE(0);
static const int Filter::SKIP(1);
static const int Filter::STOP(2);

} // namespace routing
} // namespace echo


