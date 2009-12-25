#ifndef _ECHO_CONNECTOR_H_
#define _ECHO_CONNECTOR_H_

/*
  import java.util.concurrent.CopyOnWriteArrayList;
*/
#include <list>

#include <echo/context.h>
//#include <echo/data/protocol.h>

namespace echo {

/**
 * Echo enabling communication between Components. "A connector is an
 * abstract mechanism that mediates communication, coordination, or cooperation
 * among components. Connectors enable communication between components by
 * transferring data elements from one interface to another without changing the
 * data." Roy T. Fielding<br>
 * <br>
 * "Encapsulate the activities of accessing resources and transferring resource
 * representations. The connectors present an abstract interface for component
 * communication, enhancing simplicity by providing a clean separation of
 * concerns and hiding the underlying implementation of resources and
 * communication mechanisms" Roy T. Fielding<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @see <a
 *      href="http://roy.gbiv.com/pubs/dissertation/software_arch.htm#sec_1_2_2">Source
 *      dissertation</a>
 * @see <a
 *      href="http://roy.gbiv.com/pubs/dissertation/rest_arch_style.htm#sec_5_2_2">Source
 *      dissertation</a>
 * @author Jerome Louvel Eguo Wang
 */

  //public abstract class Connector extends Restlet {

  class Connector : public echo::Echo {

 public:

    /**
     * Constructor.
     * 
     * @param context
     *            The context.
     */
    Connector(echo::Context context) {
        Connector(context, NULL);
    }

    /**
     * Constructor.
     * 
     * @param context
     *            The context.
     * @param protocols
     *            The supported protocols.
     */
    Connector(echo::Context context, std::list<echo::data::Protocol> protocols);

    /**
     * Returns the modifiable list of protocols simultaneously supported.
     * 
     * @return The protocols simultaneously supported.
     */
    std::list<echo::data::Protocol> getProtocols() {
        return protocols;
    }

    /**
     * Indicates the underlying connector helper is available.
     * 
     * @return True if the underlying connector helper is available.
     */
    virtual bool isAvailable() = 0;

    /**
     * Sets the protocols simultaneously supported. Method synchronized to make
     * compound action (clear, addAll) atomic, not for visibility.
     * 
     * @param protocols
     *            The protocols simultaneously supported.
     */
    //public synchronized void setProtocols(List<Protocol> protocols) {
    void setProtocols(std::list<echo::data::Protocol> protocols) {
        this->protocols->clear();
        if (protocols != NULL) {
            this->protocols->addAll(protocols);
        }
    }

        
    /** The list of protocols simultaneously supported. */
 private:
    const std::list<echo::data::Protocol> protocols;

  };

} // namespace echo

#endif // _ECHO_CONNECTOR_H_
