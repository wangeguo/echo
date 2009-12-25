#ifndef _ECHO_APPLICATION_h_
#define _ECHO_APPLICATION_H_

/*
  import java.util.concurrent.CopyOnWriteArrayList;

  import org.restlet.engine.Engine;
  import org.restlet.engine.RestletHelper;
  import org.restlet.engine.application.ApplicationHelper;
  import org.restlet.engine.resource.AnnotationUtils;
  import org.restlet.resource.Finder;
  import org.restlet.security.Role;
  import org.restlet.service.ConnectorService;
  import org.restlet.service.ConverterService;
  import org.restlet.service.DecoderService;
  import org.restlet.service.MetadataService;
  import org.restlet.service.RangeService;
  import org.restlet.service.Service;
  import org.restlet.service.StatusService;
  import org.restlet.service.TunnelService;
*/

#include <list>
#include <string>

#include <echo/context.h>
#include <echo/util/logging/level.h>
#include <echo/request.h>
#include <echo/response.h>

namespace echo {

  /**
   * Echo managing a coherent set of Resources and Services. Applications are
   * guaranteed to receive calls with their base reference set relatively to the
   * VirtualHost that served them. This class is both a descriptor able to create
   * the root Echo and the actual Echo that can be attached to one or more
   * VirtualHost instances.<br>
   * <br>
   * Applications also have many useful services associated. They are all enabled
   * by default and are available as properties that can be eventually overridden:
   * <ul>
   * <li>"connectorService" to declare necessary client and server connectors.</li>
   * <li>"converterService" to convert between regular objects and
   * representations.</li>
   * <li>"decoderService" to automatically decode or uncompress request entities.</li>
   * <li>"metadataService" to provide access to metadata and their associated
   * extension names.</li>
   * <li>"rangeService" to automatically exposes ranges of response entities.</li>
   * <li>"statusService" to provide common representations for exception status.</li>
   * <li>"taskService" to run tasks asynchronously.</li>
   * <li>"tunnelService" to tunnel method names or client preferences via query
   * parameters.</li>
   * </ul>
   * 
   * Concurrency note: instances of this class or its subclasses can be invoked by
   * several threads at the same time and therefore must be thread-safe. You
   * should be especially careful when storing state in member variables.
   * 
   * @author Jerome Louvel Eguo Wang
   */
  //public class Application extends Restlet {
  class Application : public echo::Echo {

 public:
    /**
     * This variable is stored internally as a thread local variable and updated
     * each time a call enters an application.
     * 
     * Warning: this method should only be used under duress. You should by
     * default prefer obtaining the current application using methods such as
     * {@link echo::resource::Resource#getApplication()}
     * 
     * @return The current context.
     */
    static echo::Application getCurrent() {
      return CURRENT.get();
    }

    /**
     * Sets the context to associated with the current thread.
     * 
     * @param application
     *            The thread's context.
     */
    static void setCurrent(echo::Application application) {
      CURRENT.set(application);
    }

    /**
     * Constructor. Note this constructor is convenient because you don't have
     * to provide a context like for {@link #Application(Context)}. Therefore
     * the context will initially be null. It's only when you attach the
     * application to a virtual host via one of its attach*() methods that a
     * proper context will be set.
     */
    Application() {
      Application(NULL);
    }

    /**
     * Constructor.
     * 
     * @param context
     *            The context to use based on parent component context. This
     *            context should be created using the
     *            {@link Context#createChildContext()} method to ensure a proper
     *            isolation with the other applications.
     */
    Application(echo::Context context) {
      //super(context);
      echo::Echo::Echo(context);

      if (Engine.getInstance() != NULL) {
        this.helper = new ApplicationHelper(this);
      }

      this.roles = new CopyOnWriteArrayList<Role>();

      this.outboundRoot = NULL;
      this.inboundRoot = NULL;
      this.services = new CopyOnWriteArrayList<Service>();
      this.services.add(new TunnelService(true, true));
      this.services.add(new StatusService());
      this.services.add(new DecoderService());
      this.services.add(new RangeService());
      this.services.add(new ConnectorService());
      this.services.add(new ConverterService());
      this.services.add(new MetadataService());

      this.services.add(new org.restlet.service.TaskService());
    }

    /**
     * Creates a inbound root Restlet that will receive all incoming calls. In
     * general, instances of Router, Filter or Finder classes will be used as
     * initial application Restlet. The default implementation returns null by
     * default. This method is intended to be overridden by subclasses.
     * 
     * @return The server root Restlet.
     */
    echo::Echo createInboundRoot() {
      return NULL;
    }

    /**
     * Creates a outbound root Restlet that will receive all outgoing calls from
     * ClientResource. In general, instances of Router, Filter or Finder classes
     * will be used as initial application Restlet. The default implementation
     * returns the {@link Context#getClientDispatcher()} by default. This method
     * is intended to be overridden by subclasses.
     * 
     * @return The server root Restlet.
     */
    echo::Echo createOutboundRoot() {
      return (getContext() != NULL) ? getContext().getClientDispatcher()
          : NULL;
    }

    /**
     * Creates a inbound root Restlet that will receive all incoming calls. In
     * general, instances of Router, Filter or Handler classes will be used as
     * initial application Restlet. The default implementation returns null by
     * default. This method is intended to be overridden by subclasses.
     * 
     * @return The server root Restlet.
     * @deprecated Override the {@link #createInboundRoot()} method instead.
     */
    //@Deprecated
    echo::Echo createRoot() {
      return createInboundRoot();
    }

    /**
     * Finds the role associated to the given name.
     * 
     * @param name
     *            The name of the role to find.
     * @return The role matched or null.
     */
    Role findRole(std::string name) {
      for (Role role : getRoles()) {
        if (role.getName().equals(name)) {
          return role;
        }
      }

      return NULL;
    }

    /**
     * Returns the connector service. The service is enabled by default.
     * 
     * @return The connector service.
     */
    ConnectorService getConnectorService() {
      return getService(ConnectorService.class);
    }

    /**
     * Returns the converter service. The service is enabled by default.
     * 
     * @return The converter service.
     */
    ConverterService getConverterService() {
      return getService(ConverterService.class);
    }

    /**
     * Returns the decoder service. The service is enabled by default.
     * 
     * @return The decoder service.
     */
    DecoderService getDecoderService() {
      return getService(DecoderService.class);
    }

    /**
     * Returns the finder class used to instantiate resource classes. By
     * default, it returns the {@link Finder} class.
     * 
     * @return the finder class to instantiate.
     */
    Class<? extends Finder> getFinderClass() {
      return finderClass;
    }

    /**
     * Returns the inbound root Echo.
     * 
     * @return The inbound root Echo.
     */
    synchronized echo::Echo getInboundRoot() {
      if (this.inboundRoot == NULL) {
        this.inboundRoot = createRoot();
      }

      return this.inboundRoot;
    }

    /**
     * Returns the metadata service. The service is enabled by default.
     * 
     * @return The metadata service.
     */
    MetadataService getMetadataService() {
      return getService(MetadataService.class);
    }

    /**
     * Returns the outbound root Echo.
     * 
     * @return The outbound root Echo.
     */
    synchronized echo::Echo getOutboundRoot() {
      if (this.outboundRoot == NULL) {
        this.outboundRoot = createOutboundRoot();
      }

      return this.outboundRoot;
    }

    /**
     * Returns the range service.
     * 
     * @return The range service.
     */
    RangeService getRangeService() {
      return getService(RangeService.class);
    }

    /**
     * Returns the modifiable list of roles.
     * 
     * @return The modifiable list of roles.
     */
    std::list<Role> getRoles() {
      return roles;
    }

    /**
     * Returns the root inbound Restlet. Invokes the createRoot() method if no
     * inbound root has been set, and stores the Restlet created for future
     * uses.
     * 
     * @return The root inbound Restlet.
     * @deprecated Use the {@link #getInboundRoot()} method instead.
     */
    //@Deprecated
    synchronized echo::Echo getRoot() {
      return getInboundRoot();
    }

    /**
     * Returns a service matching a given service class.
     * 
     * @param <T>
     *            The service type.
     * @param clazz
     *            The service class to match.
     * @return The matched service instance.
     */
    @SuppressWarnings("unchecked")
        <T extends Service> T getService(Class<T> clazz) {
      for (Service service : getServices()) {
        if (clazz.isAssignableFrom(service.getClass())) {
          return (T) service;
        }
      }

      return NULL;
    }

    /**
     * Returns the modifiable list of services.
     * 
     * @return The modifiable list of services.
     */
    std::list<Service> getServices() {
      return services;
    }

    /**
     * Returns the status service. The service is enabled by default.
     * 
     * @return The status service.
     */
    StatusService getStatusService() {
      return getService(StatusService.class);
    }

    /**
     * Returns a task service to run concurrent tasks. The service is enabled by
     * default.
     * 
     * @return A task service.
     */
    org.restlet.service.TaskService getTaskService() {
      return getService(org.restlet.service.TaskService.class);
    }

    /**
     * Returns the tunnel service. The service is enabled by default.
     * 
     * @return The tunnel service.
     */
    TunnelService getTunnelService() {
      return getService(TunnelService.class);
    }

    //@Override
    void handle(echo::Request request,echo::Response response) {
      super.handle(request, response);

      if (getHelper() != NULL) {
        getHelper().handle(request, response);
      }
    }

    /**
     * Sets the client root Resource class.
     * 
     * @param clientRootClass
     *            The client root Resource class.
     */
    synchronized void setClientRoot(Class<?> clientRootClass) {
      setOutboundRoot(Finder.createFinder(clientRootClass, getFinderClass(),
                                          getContext(), getLogger()));
    }

    /**
     * Sets the connector service.
     * 
     * @param connectorService
     *            The connector service.
     */
    void setConnectorService(ConnectorService connectorService) {
      setService(connectorService);
    }

    /**
     * Sets the converter service.
     * 
     * @param converterService
     *            The converter service.
     */
    void setConverterService(ConverterService converterService) {
      setService(converterService);
    }

    /**
     * Sets the decoder service.
     * 
     * @param decoderService
     *            The decoder service.
     */
    void setDecoderService(DecoderService decoderService) {
      setService(decoderService);
    }

    /**
     * Sets the finder class to instantiate.
     * 
     * @param finderClass
     *            The finder class to instantiate.
     */
    void setFinderClass(Class<? extends Finder> finderClass) {
      this.finderClass = finderClass;
    }

    /**
     * Sets the inbound root Resource class.
     * 
     * @param inboundRootClass
     *            The inbound root Resource class.
     */
    synchronized void setInboundRoot(Class<?> inboundRootClass) {
      setInboundRoot(Finder.createFinder(inboundRootClass, getFinderClass(),
                                         getContext(), getLogger()));
    }

    /**
     * Sets the inbound root Restlet.
     * 
     * @param inboundRoot
     *            The inbound root Restlet.
     */
    synchronized void setInboundRoot(Restlet inboundRoot) {
      this.inboundRoot = inboundRoot;

      if ((inboundRoot != NULL) && (inboundRoot.getContext() == NULL)) {
        inboundRoot.setContext(getContext());
      }
    }

    /**
     * Sets the metadata service.
     * 
     * @param metadataService
     *            The metadata service.
     */
    void setMetadataService(MetadataService metadataService) {
      setService(metadataService);
    }

    /**
     * Sets the outbound root Restlet.
     * 
     * @param outboundRoot
     *            The outbound root Restlet.
     */
    synchronized void setOutboundRoot(Restlet outboundRoot) {
      this.outboundRoot = outboundRoot;

      if ((outboundRoot != NULL) && (outboundRoot.getContext() == NULL)) {
        outboundRoot.setContext(getContext());
      }
    }

    /**
     * Sets the range service.
     * 
     * @param rangeService
     *            The range service.
     */
    void setRangeService(RangeService rangeService) {
      setService(rangeService);
    }

    /**
     * Sets the list of roles.
     * 
     * @param roles
     *            The list of roles.
     */
    void setRoles(std::list<Role> roles) {
      this.roles.clear();

      if (roles != NULL) {
        this.roles.addAll(roles);
      }
    }

    /**
     * Sets the inbound root Resource class.
     * 
     * @param inboundRootClass
     *            The inbound root Resource class.
     * @deprecated Use the {@link #setInboundRoot(Class)} method instead.
     */
    //@Deprecated
    synchronized void setRoot(Class<?> inboundRootClass) {
      setInboundRoot(inboundRootClass);
    }

    /**
     * Sets the inbound root Restlet.
     * 
     * @param inboundRoot
     *            The inbound root Restlet.
     * @deprecated Use the {@link #setInboundRoot(Restlet)} method instead.
     */
    //@Deprecated
    synchronized void setRoot(echo::Echo inboundRoot) {
      setInboundRoot(inboundRoot);
    }

    /**
     * Sets the list of services.
     * 
     * @param services
     *            The list of services.
     */
    synchronized void setServices(std::list<Service> services) {
      this.services.clear();

      if (services != NULL) {
        this.services.addAll(services);
      }
    }

    /**
     * Sets the status service.
     * 
     * @param statusService
     *            The status service.
     */
    void setStatusService(StatusService statusService) {
      setService(statusService);
    }

    /**
     * Sets the task service.
     * 
     * @param taskService
     *            The task service.
     */
    void setTaskService(org.restlet.service.TaskService taskService) {
      setService(taskService);
    }

    /**
     * Sets the tunnel service.
     * 
     * @param tunnelService
     *            The tunnel service.
     */
    void setTunnelService(TunnelService tunnelService) {
      setService(tunnelService);
    }

    /**
     * Starts the application, all the enabled associated services then the
     * inbound and outbound roots.
     */
    //@Override
    synchronized void start() throws Exception {
      if (isStopped()) {
        super.start();

        if (getHelper() != NULL) {
          getHelper().start();
        }

        for (Service service : getServices()) {
          service.start();
        }

        if (getInboundRoot() != NULL) {
          getInboundRoot().start();
        }

        if (getOutboundRoot() != NULL) {
          getOutboundRoot().start();
        }
      }
    }

    /**
     * Starts the application, the inbound and outbound roots then all the
     * enabled associated services.
     */
    //@Override
    synchronized void stop() throws Exception {
      if (isStarted()) {
        if (getOutboundRoot() != NULL) {
          getOutboundRoot().stop();
        }

        if (getInboundRoot() != NULL) {
          getInboundRoot().stop();
        }

        for (Service service : getServices()) {
          service.stop();
        }

        if (getHelper() != NULL) {
          getHelper().stop();
        }

        // Clear the annotations cache
        AnnotationUtils.clearCache();

        super.stop();
      }
    }

 protected:
    
    /**
     * Replaces or adds a service. The replacement is based on the service
     * class.
     * 
     * @param newService
     *            The new service to set.
     */
    synchronized void setService(Service newService) {
      std::list<Service> services = new CopyOnWriteArrayList<Service>();
      Service service;
      bool replaced = false;

      for (int i = 0; (i < this.services.size()); i++) {
        service = this.services.get(i);

        if (service != NULL) {
          if (service.getClass().isAssignableFrom(newService.getClass())) {
            try {
              service.stop();
            } catch (Exception e) {
              getLogger().log(Level.WARNING,
                              "Unable to stop service replaced", e);
            }

            services.add(newService);
            replaced = true;
          } else {
            services.add(service);
          }
        }
      }

      if (!replaced) {
        services.add(newService);
      }

      setServices(services);
    }
    

 private:

    /**
     * Returns the helper provided by the implementation.
     * 
     * @return The helper provided by the implementation.
     */
    RestletHelper<Application> getHelper() {
      return this.helper;
    }

    static const ThreadLocal<echo::Application> CURRENT = new ThreadLocal<echo::Application>();

    /** Finder class to instantiate. */
    volatile Class<? extends Finder> finderClass;

    /** The helper provided by the implementation. */
    volatile RestletHelper<Application> helper;

    /** The modifiable list of roles. */
    const std::list<Role> roles;

    /** The inbound root Echo. */
    volatile echo::Echo inboundRoot;

    /** The outbound root Echo. */
    volatile echo::Echo outboundRoot;

    /** The list of services. */
    const std::list<Service> services;

  };

} // namespace echo
#endif
