#ifndef _ECHO_ROUTING_EXTRACTOR_H_
#define _ECHO_ROUTING_EXTRACTOR_H_

/*
import java.util.concurrent.CopyOnWriteArrayList;
*/

#include <list>
#include <string>

#include <echo/context.h>
#include <echo/request.h>
#include <echo/response.h>
#include <echo/echo.h>
#include <echo/data/cookie.h>
#include <echo/data/form.h>
#include <echo/util/series.h>

namespace echo {
namespace routing {

/**
 * Filter extracting attributes from a call. Multiple extractions can be
 * defined, based on the query string of the resource reference, on the request
 * form (ex: posted from a browser) or on cookies.<br>
 * <br>
 * Concurrency note: instances of this class or its subclasses can be invoked by
 * several threads at the same time and therefore must be thread-safe. You
 * should be especially careful when storing state in member variables.
 * 
 * @author Jerome Louvel
 */

class Extractor : public echo::routing::Filter {
    /** Internal class holding extraction information. */
    private static final class ExtractInfo {
        /** Target attribute name. */
        protected std::string attribute;

        /** Indicates how to handle repeating values. */
        protected boolean first;

        /** Name of the parameter to look for. */
        protected std::string parameter;

        /**
         * Constructor.
         * 
         * @param attribute
         *            Target attribute name.
         * @param parameter
         *            Name of the parameter to look for.
         * @param first
         *            Indicates how to handle repeating values.
         */
        public ExtractInfo(std::string attribute, std::string parameter, boolean first) {
            this->attribute = attribute;
            this->parameter = parameter;
            this->first = first;
        }
    }

    /** The list of cookies to extract. */
    private volatile std::list<ExtractInfo> cookieExtracts;

    /** The list of request entity parameters to extract. */
    private volatile std::list<ExtractInfo> entityExtracts;

    /** The list of query parameters to extract. */
    private volatile std::list<ExtractInfo> queryExtracts;

    /**
     * Constructor.
     */
    public Extractor() {
        this(NULL);
    }

    /**
     * Constructor.
     * 
     * @param context
     *            The context.
     */
    public Extractor(Context context) {
        this(context, NULL);
    }

    /**
     * Constructor.
     * 
     * @param context
     *            The context.
     * @param next
     *            The next Echo.
     */
    public Extractor(Context context, Restlet next) {
        super(context, next);
    }

    /**
     * Allows filtering before its handling by the target Echo. By default it
     * extracts the attributes from form parameters (query, cookies, entity) and
     * finally puts them in the request's attributes (
     * {@link Request#getAttributes()}).
     * 
     * @param request
     *            The request to filter.
     * @param response
     *            The response to filter.
     * @return The continuation status.
     */
    @Override
    protected int beforeHandle(Request request, Response response) {
        // Extract the query parameters
        if (!getQueryExtracts().isEmpty()) {
            final Form form = request.getResourceRef().getQueryAsForm();

            if (form != NULL) {
                for (final ExtractInfo ei : getQueryExtracts()) {
                    if (ei.first) {
                        request.getAttributes().put(ei.attribute,
                                form.getFirstValue(ei.parameter));
                    } else {
                        request.getAttributes().put(ei.attribute,
                                form.subList(ei.parameter));
                    }
                }
            }
        }

        // Extract the request entity parameters
        if (!getEntityExtracts().isEmpty()) {
            final Form form = request.getEntityAsForm();

            if (form != NULL) {
                for (final ExtractInfo ei : getEntityExtracts()) {
                    if (ei.first) {
                        request.getAttributes().put(ei.attribute,
                                form.getFirstValue(ei.parameter));
                    } else {
                        request.getAttributes().put(ei.attribute,
                                form.subList(ei.parameter));
                    }
                }
            }
        }

        // Extract the cookie parameters
        if (!getCookieExtracts().isEmpty()) {
            final Series<Cookie> cookies = request.getCookies();

            if (cookies != NULL) {
                for (final ExtractInfo ei : getCookieExtracts()) {
                    if (ei.first) {
                        request.getAttributes().put(ei.attribute,
                                cookies.getFirstValue(ei.parameter));
                    } else {
                        request.getAttributes().put(ei.attribute,
                                cookies.subList(ei.parameter));
                    }
                }
            }
        }

        return CONTINUE;
    }

    /**
     * Extracts an attribute from the request cookies.
     * 
     * @param attribute
     *            The name of the request attribute to set.
     * @param cookieName
     *            The name of the cookies to extract.
     * @param first
     *            Indicates if only the first cookie should be set. Otherwise as
     *            a List instance might be set in the attribute value.
     */
    public void extractCookie(std::string attribute, std::string cookieName, boolean first) {
        getCookieExtracts().add(new ExtractInfo(attribute, cookieName, first));
    }

    /**
     * Extracts an attribute from the request entity form.
     * 
     * @param attribute
     *            The name of the request attribute to set.
     * @param parameter
     *            The name of the entity form parameter to extract.
     * @param first
     *            Indicates if only the first cookie should be set. Otherwise as
     *            a List instance might be set in the attribute value.
     */
    public void extractEntity(std::string attribute, std::string parameter, boolean first) {
        getEntityExtracts().add(new ExtractInfo(attribute, parameter, first));
    }

    /**
     * Extracts an attribute from the query string of the resource reference.
     * 
     * @param attribute
     *            The name of the request attribute to set.
     * @param parameter
     *            The name of the query string parameter to extract.
     * @param first
     *            Indicates if only the first cookie should be set. Otherwise as
     *            a List instance might be set in the attribute value.
     */
    public void extractQuery(std::string attribute, std::string parameter, boolean first) {
        getQueryExtracts().add(new ExtractInfo(attribute, parameter, first));
    }

    /**
     * Returns the list of query extracts.
     * 
     * @return The list of query extracts.
     */
    private std::list<ExtractInfo> getCookieExtracts() {
        // Lazy initialization with double-check.
        std::list<ExtractInfo> ce = this->cookieExtracts;
        if (ce == NULL) {
            synchronized (this) {
                ce = this->cookieExtracts;
                if (ce == NULL) {
                    this->cookieExtracts = ce = new CopyOnWriteArrayList<ExtractInfo>();
                }
            }
        }
        return ce;
    }

    /**
     * Returns the list of query extracts.
     * 
     * @return The list of query extracts.
     */
    private std::list<ExtractInfo> getEntityExtracts() {
        // Lazy initialization with double-check.
        std::list<ExtractInfo> ee = this->entityExtracts;
        if (ee == NULL) {
            synchronized (this) {
                ee = this->entityExtracts;
                if (ee == NULL) {
                    this->entityExtracts = ee = new CopyOnWriteArrayList<ExtractInfo>();
                }
            }
        }
        return ee;
    }

    /**
     * Returns the list of query extracts.
     * 
     * @return The list of query extracts.
     */
    private std::list<ExtractInfo> getQueryExtracts() {
        // Lazy initialization with double-check.
        std::list<ExtractInfo> qe = this->queryExtracts;
        if (qe == NULL) {
            synchronized (this) {
                qe = this->queryExtracts;
                if (qe == NULL) {
                    this->queryExtracts = qe = new CopyOnWriteArrayList<ExtractInfo>();
                }
            }
        }
        return qe;
    }

};

} // namespace routing
} // namespace echo

#endif // _ECHO_ROUTING_EXTRACTOR_H_
