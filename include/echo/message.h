#ifndef _ECHO_MESSAGE_H_
#define _ECHO_MESSAGE_H_

/*
  import java.util.Date;
  import java.util.TreeMap;
  import java.util.concurrent.CopyOnWriteArrayList;
*/
#include <string>
#include <map>
#include <list>

//#include <echo/data/cache-directive.h>
//#include <echo/data/form.h>
//#include <echo/data/media-type.h>
//#include <echo/data/warning.h>
//#include <echo/representation/representation.h>
//#include <echo/representation/string-representation.h>
//TODO: 实现下边的类

class Date;
class Representation;
class Object;
class CacheDirective;
class Form;
class Uniform;
class Warning;
class MediaType;


namespace echo {
  
  /**
   * Generic message exchanged between components.
   * 
   * @author Eguo Wang
   */
  class Message {

 public:
	/**
	 * Constructor.
	 */
	Message() {
	  Message((Representation) NULL);
	}

	/**
	 * Constructor.
	 * 
	 * @param entity
	 *            The payload of the message.
	 */
	Message(Representation entity) {
	  attributes = NULL;
	  cacheDirectives = NULL;
	  date = NULL;
	  this->entity = entity;
	  entityForm = NULL;
	  entityText = NULL;
	  onContinue = NULL;
	  onSent = NULL;
	  warnings = NULL;
	}

	/**
	 * Returns the modifiable map of attributes that can be used by developers
	 * to save information relative to the message. Creates a new instance if no
	 * one has been set. This is an easier alternative to the creation of a
	 * wrapper instance around the whole message.<br>
	 * <br>
	 * 
	 * In addition, this map is a shared space between the developer and the
	 * connectors. In this case, it is used to exchange information that is not
	 * uniform across all protocols and couldn't therefore be directly included
	 * in the API. For this purpose, all attribute names starting with
	 * "echo" are reserved. Currently the following attributes are used:
	 * <table>
	 * <tr>
	 * <th>Attribute name</th>
	 * <th>Class name</th>
	 * <th>Description</th>
	 * </tr>
	 * <tr>
	 * <td>echo.http.headers</td>
	 * <td>echo.data.Form</td>
	 * <td>Server HTTP connectors must provide all request headers and client
	 * HTTP connectors must provide all response headers, exactly as they were
	 * received. In addition, developers can also use this attribute to specify
	 * <b>non-standard</b> headers that should be added to the request or to the
	 * response.</td>
	 * </tr>
	 * <tr>
	 * <td>echo.https.clientCertificates</td>
	 * <td>std::list<java.security.cert.Certificate></td>
	 * <td>For requests received via a secure connector, indicates the ordered
	 * list of client certificates, if they are available and accessible.</td>
	 * </tr>
	 * </table>
	 * <br>
	 * Most of the standard HTTP headers are directly supported via the Echo
	 * API. Thus, adding such HTTP headers is forbidden because it could
	 * conflict with the connector's internal behavior, limit portability or
	 * prevent future optimizations. The other standard HTTP headers (that are
	 * not supported) can be added as attributes via the
	 * "echo.http.headers" key.<br>
	 * 
	 * @return The modifiable attributes map.
	 */
	std::map<std::string, Object> getAttributes();

	/**
	 * Returns the cache directives.<br>
	 * <br>
	 * Note that when used with HTTP connectors, this property maps to the
	 * "Cache-Control" header.
	 * 
	 * @return The cache directives.
	 */
	std::list<CacheDirective> getCacheDirectives();
	  
	/**
	 * Returns the date and time at which the message was originated.
	 * 
	 * @return The date and time at which the message was originated.
	 */
	Date getDate() {
	  return date;
	}

	/**
	 * Returns the entity representation.
	 * 
	 * @return The entity representation.
	 */
	Representation getEntity() {
	  return entity;
	}

	/**
	 * Returns the entity as a form. This method can be called several times and
	 * will always return the same form instance. Note that if the entity is
	 * large this method can result in important memory consumption.
	 * 
	 * @return The entity as a form.
	 */
	Form getEntityAsForm();

	/**
	 * Returns the entity as text. This method can be called several times and
	 * will always return the same text. Note that if the entity is large this
	 * method can result in important memory consumption.
	 * 
	 * @return The entity as text.
	 */
	std::string getEntityAsText();

	/**
	 * Returns the callback invoked before sending the message entity.
	 * 
	 * @return The callback invoked before sending the message entity.
	 */
    Uniform getOnContinue() {
	  return onContinue;
	}

	/**
	 * Returns the callback invoked after sending the message.
	 * 
	 * @return The callback invoked after sending the message.
	 */
    Uniform getOnSent() {
	  return onSent;
	}

	/**
	 * Returns the additional warnings information.<br>
	 * <br>
	 * Note that when used with HTTP connectors, this property maps to the
	 * "Warning" headers.
	 * 
	 * @return The additional warnings information.
	 */
	std::list<Warning> getWarnings();

	/**
	 * Indicates if the message was or will be exchanged confidentially, for
	 * example via a SSL-secured connection.
	 * 
	 * @return True if the message is confidential.
	 */
	virtual bool isConfidential() = 0;

	/**
	 * Indicates if a content is available and can be sent or received. Several
	 * conditions must be met: the content must exists and have some available
	 * data.
	 * 
	 * @return True if a content is available and can be sent.
	 */
	bool isEntityAvailable();

	/**
	 * Releases the message's entity. If the entity is transient and hasn't been
	 * read yet, all the remaining content will be discarded, any open socket,
	 * channel, file or similar source of content will be immediately closed.
	 */
	void release();

	/**
	 * Sets the modifiable map of attributes
	 * 
	 * @param attributes
	 *            The modifiable map of attributes
	 */
	void setAttributes(std::map<std::string, Object> attributes) {
	  this->attributes = attributes;
	}

	/**
	 * Sets the cache directives.<br>
	 * <br>
	 * Note that when used with HTTP connectors, this property maps to the
	 * "Cache-Control" header.
	 * 
	 * @param cacheDirectives
	 *            The cache directives.
	 */
	void setCacheDirectives(std::list<CacheDirective> cacheDirectives) {
	  this->cacheDirectives = cacheDirectives;
	}

	/**
	 * Sets the date and time at which the message was originated.
	 * 
	 * @param date
	 *            The date and time at which the message was originated.
	 */
	void setDate(Date date) {
	  this->date = date;
	}

	/**
	 * Sets the entity representation.
	 * 
	 * @param entity
	 *            The entity representation.
	 */
	void setEntity(Representation entity) {
	  this->entity = entity;
	}

	/**
	 * Sets a textual entity.
	 * 
	 * @param value
	 *            The represented string.
	 * @param mediaType
	 *            The representation's media type.
	 */
	void setEntity(std::string value, MediaType mediaType);

	/**
	 * Sets the callback invoked before sending the message entity.
	 * 
	 * @param onContinueCallback
	 *            The callback invoked before sending the message entity.
	 */
	void setOnContinue(Uniform onContinueCallback) {
	  this->onContinue = onContinueCallback;
	}

	/**
	 * Sets the callback invoked after sending the message.
	 * 
	 * @param onSentCallback
	 *            The callback invoked after sending the message.
	 */
	void setOnSent(Uniform onSentCallback) {
	  this->onSent = onSentCallback;
	}

	/**
	 * Sets the additional warnings information.<br>
	 * <br>
	 * Note that when used with HTTP connectors, this property maps to the
	 * "Warning" headers.
	 * 
	 * @param warnings
	 *            The warnings.
	 */
	void setWarnings(std::list<Warning> warnings) {
	  this->warnings = warnings;
	}

 private:
	/** The modifiable attributes map. */
	volatile std::map<std::string, Object> attributes;

	/** The caching directives. */
	volatile std::list<CacheDirective> cacheDirectives;

	/** The payload of the message. */
	volatile Representation entity;

	/** The optional cached Form. */
	volatile Form entityForm;

	/** The optional cached text. */
	volatile std::string entityText;

	/** Callback invoked before sending the response entity. */
	volatile Uniform onContinue;

	/** Callback invoked after sending the response. */
	volatile Uniform onSent;

	/** The additional warnings information. */
	volatile std::list<Warning> warnings;

	/** The date and time at which the message was originated. */
	volatile Date date;
	
  };

} // namespace echo

#endif // _ECHO_MESSAGE_H_
