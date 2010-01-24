#ifndef _ECHO_ROUTING_FILTER_H_
#define _ECHO_ROUTING_FILTER_H_

#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/status.h>
#include <echo/resource/finder.h>
#include <echo/resource/server-resource.h>

namespace echo {
namespace routing {


/**
 * Echo filtering calls before passing them to an attached Echo. The
 * purpose is to do some pre-processing or post-processing on the calls going
 * through it before or after they are actually handled by an attached Echo.
 * Also note that you can attach and detach targets while handling incoming
 * calls as the filter is ensured to be thread-safe.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @author Jerome Louvel
 */
//public abstract class Filter extends Echo {
class Filter : public echo::Echo {

 public:
  
  /**
   * Constructor.
   */
  Filter() {
    Filter(null);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   */
  Filter(Context context) {
    Filter(context, null);
  }

  /**
   * Constructor.
   * 
   * @param context
   *            The context.
   * @param next
   *            The next Echo.
   */
  Filter(Context context, echo::Echo next) {
    super(context);
    this->next = next;
  }

  /**
   * Returns the next Echo.
   * 
   * @return The next Echo or null.
   */
  echo::Echo getNext() {
    return next;
  }

  /**
   * Handles a call by first invoking the beforeHandle() method for
   * pre-filtering, then distributing the call to the next Echo via the
   * doHandle() method. When the handling is completed, it finally invokes the
   * afterHandle() method for post-filtering.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  //@Override
  const void handle(echo::Request request, echo::Response response) {
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

  /**
   * Indicates if there is a next Echo.
   * 
   * @return True if there is a next Echo.
   */
  bool hasNext() {
    return getNext() != null;
  }

  /**
   * Sets the next Echo as a Finder for a given
   * {@link org.restlet.resource.Handler} or {@link ServerResource} class.
   * When the call is delegated to the Finder instance, a new instance of the
   * resource class will be created and will actually handle the request.
   * 
   * @param targetClass
   *            The target resource class to attach.
   */
  void setNext(Class<?> targetClass) {
    setNext(new Finder(getContext(), targetClass));
  }

  /**
   * Sets the next Echo.
   * 
   * In addition, this method will set the context of the next Echo if it
   * is null by passing a reference to its own context.
   * 
   * @param next
   *            The next Echo.
   */
  void setNext(echo::Echo next) {
    if ((next != null) && (next.getContext() == null)) {
      next.setContext(getContext());
    }

    this->next = next;
  }

  /**
   * Starts the filter and the next Echo if attached.
   */
  //@Override
  synchronized void start() throws Exception {
    if (isStopped()) {
      super.start();

      if (getNext() != null) {
        getNext().start();
      }
    }
  }

  /**
   * Stops the filter and the next Echo if attached.
   */
  //@Override
  synchronized void stop() throws Exception {
    if (isStarted()) {
      if (getNext() != null) {
        getNext().stop();
      }

      super.stop();
    }
  }


 protected:  
  /**
   * Allows filtering after processing by the next Echo. Does nothing by
   * default.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   */
  void afterHandle(echo::Request request, echo::Response response) {
    // To be overriden
  }

  /**
   * Allows filtering before processing by the next Echo. Returns
   * {@link #CONTINUE} by default.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   * @return The continuation status. Either {@link #CONTINUE} or
   *         {@link #SKIP} or {@link #STOP}.
   */
  int beforeHandle(echo::Request request, echo::Response response) {
    return CONTINUE;
  }

  /**
   * Handles the call by distributing it to the next Echo. If no Echo is
   * attached, then a {@link Status#SERVER_ERROR_INTERNAL} status is returned.
   * Returns {@link #CONTINUE} by default.
   * 
   * @param request
   *            The request to handle.
   * @param response
   *            The response to update.
   * @return The continuation status. Either {@link #CONTINUE} or
   *         {@link #STOP}.
   */
  int doHandle(echo::Request request, echo::Response response) {
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
  

 public:
  /**
   * Indicates that the request processing should continue normally. If
   * returned from the {@link #beforeHandle(echo::Request, echo::Response)} method, the
   * filter then invokes the {@link #doHandle(echo::Request, echo::Response)} method. If
   * returned from the {@link #doHandle(echo::Request, echo::Response)} method, the filter
   * then invokes the {@link #afterHandle(echo::Request, echo::Response)} method.
   */
  static const int CONTINUE = 0;

  /**
   * Indicates that after the {@link #beforeHandle(echo::Request, echo::Response)} method,
   * the request processing should skip the
   * {@link #doHandle(echo::Request, echo::Response)} method to continue with the
   * {@link #afterHandle(echo::Request, echo::Response)} method.
   */
  static const int SKIP = 1;

  /**
   * Indicates that the request processing should stop and return the current
   * response from the filter.
   */
  static const int STOP = 2;

 private:
  /** The next Echo. */
  volatile echo::Echo next;

};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_FILTER_H_
