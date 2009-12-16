#ifndef _ECHO_CONTEXT_H_
#define _ECHO_CONTEXT_H_

namespace echo {

	/**
	 * Contextual data and services provided to a Echo. The context is
	 * the means by which a Echo may access the software environment
	 * within the framework. It is typically provided by the immediate
	 * parent Echo (Application is the most common case).<br>
	 * <br >
	 * Concurrency note: attributes and parameters of a context are
	 * stored in concurrent collections that guarantee threed safe
	 * access and modification. IF several threads councurrently
	 * access objects and modify these collecations, they should
	 * synchronize on the lock of the Context instance.
	 *
	 * @author Eguo Wang
	 */
	class Context {
	  public:

		/**
		 * Constructor. Writes log message to "Echo".
		 */
		Context() { Context("echo");}

		/**
		 * Constructor.
		 *
		 * @param logger
		 *    The logger instance of use.
		 */
		Context(echo::util::logging::Logger logger);

		/**
		 * Constructor.
		 *
		 * @param loggerName
		 *    The name of the logger to use.
		 */
		Context(std::string loggerName);

		/**
		 * Creates a protected child context. This is especially
		 * useful for new application attached to their parent
		 * component, to ensure their isolation from the other
		 * application. By  default it just creates a new context
		 * instance.
		 *
		 * @return The child context.
		 */
		echo::Context createChildContext();

		/**
		 * Returns a modifiable attributes map that can be used by developers to
		 * save information relative to the context. This is a convenient means to
		 * provide common objects to all the Restlets and Resources composing an
		 * Application.<br>
		 * <br>
		 * 
		 * In addition, this map is a shared space between the developer and the
		 * Restlet implementation. For this purpose, all attribute names starting
		 * with "org.restlet" are reserved. Currently the following attributes are
		 * used:
		 * <table>
		 * <tr>
		 * <th>Attribute name</th>
		 * <th>Class name</th>
		 * <th>Description</th>
		 * </tr>
		 * <tr>
		 * <td>org.restlet.application</td>
		 * <td>org.restlet.Application</td>
		 * <td>The parent application providing this context, if any.</td>
		 * </tr>
		 * </table>
		 * </td>
		 * 
		 * @return The modifiable attributes map.
		 */
		ConcurrentMap<String, Object> getAttributes();


		/**
		 * Returns the context associated to the current Echo. The
		 * context can be the one of a Component, an Application, a
		 * Filter or any other Echo subclass.
		 *
		 * Warning: this method should only be used under duress. You
		 * should by default prefer obtaining the current context
		 * using methods such as echo::Echo.getContext() or
		 * echo::resource::Resource.getContext().
		 *
		 * This variables is stored internally as a thread local
		 * variable and updated echo time a request is handled by a
		 * Echo via the echo::Echo::handle(echo::Request,
		 * echo::Response) method.
		 *
		 * @return The current context.
		 */
		static echo::Context getCurrent();

		/**
		 * Returns the current context's logger.
		 *
		 * @return The current Context's logger.
		 */
		static echo::util::logging::Logger getCurrentLogger();

		/**
		 * Sets the context to associated with the current thread.
		 *
		 * @param context
		 *    The thread's context.
		 */
		static void setCurrent(echo::Context context);

		

		echo::util::logging::Logger getLogger();

	  private:
		static const echo::util::ThreadLocal<echo::Context> CURRENT;

		/** The client dispatcher. */
		volatile echo::Client clientDispatcher;

		/** The server dispatcher. */
		volatile echo::Client serveDispatcher;

		/** The modifiable attributes map. */
		const ConcurrentMap<String, Object> attributes;

		/** The logger instance to use. */
		volatile echo::util::logging::Logger logger;

		/** The modifiable series of parameters. */
		const Series<Parameter> parameters;

		/**
		 * The enroler that can add the user roles based on Echo
		 * default authorization model.
		 */
		volatile echo::security::Enroler enroler;

		/**
		 * The verifier that can check the validity of user/secret
		 * couples based on Echo default authorization model.
		 */
		volatile echo::security::Verifier verifier;

		
	};

} // namespace echo
#endif // _ECHO_CONTEXT_H_
