#ifndef _ECHO_UNIFORM_H_
#define _ECHO_UNIFORM_H_

#include <echo/request.h>
#include <echo/response.h>

namespace echo {

  /**
   * Uniform REST interface. "The central that distinguishes the REST
   * architectural style from other network-based styles is its
   * emphasis on a unform interface between components. By applying
   * the software engineering principle of generality to the component
   * interface, the overall system architecture is simplified and the
   * visibility of interactions is improved. Implementations are
   * decoupled from the services they provide, which encourages
   * independent evolvability. "Roy T.Fielding
   *
   * @see <a
   * href="http://roy.gbiv.com/pubs/dissertation/rest_arch_style.html#sec_5_1_5">Source
   * dissertation</a>
   * @auther Eguo Wang
   */
  class Uniform {

	/**
	 * Handles a uniform call. It is important to realize thhat this
     * interface can be used either on the client-side or one the
     * server-side. 
	 * 
	 * @param request
	 *    The request to handle.
	 * @param response
	 *    The associated response.
	 */
  public:
	virtual void handle(echo::Request request, echo::Response response) = 0;
  };
} // namespace echo

#endif // _ECHO_UNIFORM_H_
