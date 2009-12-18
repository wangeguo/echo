#include <echo/message.h>

namespace echo {
  
  std::map<std::string, Object> Message::getAttributes() {
	if (attributes == NULL) {
	  attributes = new TreeMap<std::string, Object>();
	}
	
	return attributes;
  }

  std::list<CacheDirective> Message::getCacheDirectives() {
	// Lazy initialization with double-check.
	list<CacheDirective> r = cacheDirectives;
	if (r == null) {
	  synchronized (this) {
		r = cacheDirectives;
		if (r == NULL) {
		  cacheDirectives = r = new CopyOnWriteArrayList<CacheDirective>();
		}
	  }
	}
	return r;
  }

  Form Message::getEntityAsForm() {
	if (entityForm == NULL) {
	  entityForm = new Form(getEntity());
	}

	return entityForm;
  }

  std::string Message::getEntityAsText() {
	if (entityText == NULL) {
	  try {
		entityText = getEntity().getText();
	  } catch (java.io.IOException e) {
		Context.getCurrentLogger().log(java.util.logging.Level.FINE,
									   "Unable to get the entity text.", e);
	  }
	}
		
	return entityText;
  }

  std::list<Warning> Message::getWarnings() {
	// Lazy initialization with double-check.
	list<Warning> r = warnings;
	if (r == NULL) {
	  synchronized (this) {
		r = warnings;
		if (r == NULL) {
		  warnings = r = new CopyOnWriteArrayList<Warning>();
		}
	  }
	}
	return r;
  }

  bool Message::isEntityAvailable() {
	// The declaration of the "result" variable is a workaround for the GWT
	// platform. Please keep it!
	bool result = (getEntity() != NULL) && getEntity().isAvailable();
	return result;
  }

  void Message::release() {
	if (getEntity() != NULL) {
	  getEntity().release();
	}
  }

  void Message::setEntity(std::string value, MediaType mediaType) {
	setEntity(new StringRepresentation(value, mediaType));
  }

} // namespace echo
