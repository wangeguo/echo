#ifndef _ECHO_ECHO_H_
#define _ECHO_ECHO_H_

#include <string>

#include <echo/uniform.h>
#include <echo/util/logging/logger.h>
#include <echo/data/status.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/engine/engine.h>
#include <echo/context.h>
#include <echo/application.h>

/**
 * Uniform class that provides a context and life cycle support. It
 * has many subclasses that focus on specific ways to process
 * calls. The context property is typically provided by a parent
 * Component as a way to encapsulate access to shared features such as
 * logging and client connectors.<br /><br />
 * 
 * Concurrency noto: instances of theis class or tis subclasses can be
 * invlked by several threads at the same time and therefore must be
 * thread-safe. You should be especially careful when storing state in
 * member variables.
 *
 * @auther Eguo Wang
 */

namespace echo {

  const std::string echo_version =  "0.0.4";

  class Echo : public echo::Uniform {
  public:

	/**
	 * Constructor with null context.
	 */
	Echo();

	/**
	 * Constructor with the Echo's context which can be the parent's
	 * application context, but shouldn't be the parent  Component's
	 * context for security reasons.
	 *
	 * @see Context#createChildContext()
	 *
	 * @param context
	 *     The context of the Echo.
	 */
	Echo(echo::Context context);

	/**
	 * Returns the parent application if it exists, or null.
	 *
	 * @return The parent application if it exists, or null.
	 */
	echo::Application getApplication();

	/**
	 * Returns the author(s).
	 *
	 * @return The author(s).
	 */
	std::string getAuthor();

	/**
	 * Return the context.
	 *
	 * @return The Context.
	 */
	echo::Context getContext();

	/**
	 * Return the description.
	 *
	 * @return The description
	 */
	std::string getDescription();

	/**
	 * Returns the context's logger.
	 *
	 * @return the context's logger.
	 */
	echo::util::logging::Logger getLogger();

	/**
	 * Returns the display name.
	 *
	 * @return The display name.
	 */
	std::string getName();

	/**
	 * Returns the owner(s).
	 *
	 * @return The owner(s).
	 */
	std::string getOwner();

	/**
     * Handles a call. The default behavior is to initialize the Echo by
     * setting the current context using the {@link Context#setCurrent(Context)}
     * method and by attempting to start it, unless it was already started. If
     * an exception is thrown during the start action, then the response status
     * is set to {@link Status#SERVER_ERROR_INTERNAL}.
     * <p>
     * Subclasses overriding this method should make sure that they call
     * super.handle(request, response) before adding their own logic.
     * 
     * @param request
     *            The request to handle.
     * @param response
     *            The response to update.
     */
	virtual void handle(echo::Request request,
						echo::Response response);

	/**
	 * Indicates if the Echo is started.
	 *
	 * @return True if the Echo is started.
	 */
	bool isStarted();

	/**
	 * Indicates if the Echo is stopped.
	 * @return True if the Echo is stopped.
	 */
	bool isStopped();

	/**
	 * Sets the author(s).
	 *
	 * @param author
	 *    The author(s).
	 */
	void setAuthor(std::string author);

	/**
	 * Sets the context.
	 *
	 * @param context
	 *    The context.
	 */
	void setContext(echo::Context context);

	/**
	 * Sets the description.
	 *
	 * @param description
	 *    The description.
	 */
	void setDescription(std::string description);

	/**
	 * Sets the display name.
	 *
	 * @param name
	 *    The display name.
	 */
	 void setName(std::string name);

	 /**
	  * Sets the owner(s).
	  *
	  * @param owner
	  *    The owner(s).
	  */
	 void setOwner(std::string owner);

	 /** starts the Echo */
	 void start();

	 /** Stops the Echo */
	 void stop();

  private:

	// Error message.
	 static const std::string UNABLE_TO_START;

	// The author(s).
	std::string author;

	// The context.
	echo::Context context;

	// The description.
	std::string description;

	// The display name.
	std::string name;

	// The owner(s).
	std::string owner;

	// Indicates if the Echo was started.
	bool started;
	
  };

} // namespace echo

#endif // _ECHO_ECHO_H_
