#ifndef _ECHO_ENGINE_ENGINE_H_
#define _ECHO_ENGINE_ENGINE_H_

#include <echo/context.h>

namespace echo {
	namespace engine {
		class Engine {
		  public:
			Engine();
			static echo::engine::Engine getInstance();
		};
	} // namespace  engine
} // namespace echo

#endif // _ECHO_ENGINE_ENGINE_H_
