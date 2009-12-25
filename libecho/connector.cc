#include <echo/connector.h>
#include <list>
#include <echo/context.h>
//#include <echo/data/protocol.h>

namespace echo {

Connector::Connector(echo::Context context, std::list<echo::data::Protocol> protocols) {
      //super(context);
      echo::Echo::Echo(context);
        if (protocols == NULL) {
          this->protocols = new CopyOnWriteArrayList<echo::data::Protocol>();
        } else {
          this->protocols = new CopyOnWriteArrayList<echo::data::Protocol>(protocols);
        }

        if (this->protocols->isEmpty()) {
            getLogger()
                    .fine(
                            "The connector has been instantiated without any protocol.");
        }
    }

void Connector::setProtocols(std::list<echo::data::Protocol> protocols) {
        this->protocols->clear();
        if (protocols != NULL) {
            this->protocols->addAll(protocols);
        }
    }

} // namespace echo
