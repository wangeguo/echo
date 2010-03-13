#ifndef _ECHO_DATA_CONDITIONS_H_
#define _ECHO_DATA_CONDITIONS_H_

/*
  import java.util.ArrayList;
  import java.util.Iterator;
*/

#include <list>

#include <echo/engine/util/date-utils.h>
#include <echo/representation/representation-info.h>

namespace echo {
namespace data {

/**
 * Set of conditions applying to a request. This is equivalent to the HTTP
 * conditional headers.
 * 
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.24"
 *      >If-Match</a>
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.25"
 *      >If-Modified-Since</a>
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.26"
 *      >If-None-Match</a>
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.27"
 *      >If-Range</a>
 * @see <a
 *      href="http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.28"
 *      >If-Unmodified-Since</a>
 * 
 * @author Jerome Louvel
 */

//public final class Conditions {
class Conditions {

 public:

  /**
   * Constructor.
   */
  Conditions() {
  }

  /**
   * Returns the modifiable list of tags that must be matched. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Match" header.
   * 
   * @return The "if-match" condition.
   */
  std::list<Tag> getMatch();

  /**
   * Returns the condition based on the modification date of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Modified-Since" header.
   * 
   * @return The condition date.
   */
  Date getModifiedSince() {
    return this->modifiedSince;
  }

  /**
   * Returns the modifiable list of tags that mustn't match. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-None-Match" header.
   * 
   * @return The list of tags that mustn't match.
   */
  std::list<Tag> getNoneMatch();

  /**
   * Returns the range condition based on the modification date of the
   * requested variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Range" header.
   * 
   * @return The range condition date.
   */
  Date getRangeDate() {
    return rangeDate;
  }

  /**
   * Returns the range conditional status of an entity.
   * 
   * @param representationInfo
   *            The representation information that will be tested.
   * @return the status of the response.
   */
  Status getRangeStatus(RepresentationInfo representationInfo);

  /**
   * Returns the range conditional status of an entity.
   * 
   * @param tag
   *            The tag of the entity.
   * @param modificationDate
   *            The modification date of the entity.
   * @return The status of the response.
   */
  Status getRangeStatus(Tag tag, Date modificationDate);

  /**
   * Returns the range condition based on the entity tag of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Range" header.
   * 
   * @return The range entity tag.
   */
  Tag getRangeTag() {
    return rangeTag;
  }

  /**
   * Returns the conditional status of a variant using a given method.
   * 
   * @param method
   *            The request method.
   * @param entityExists
   *            Indicates if the entity exists.
   * @param tag
   *            The tag.
   * @param modificationDate
   *            The modification date.
   * @return NULL if the requested method can be performed, the status of the
   *         response otherwise.
   */
  Status getStatus(Method method, bool entityExists, Tag tag,
                   Date modificationDate);

  /**
   * Returns the conditional status of a variant using a given method.
   * 
   * @param method
   *            The request method.
   * @param representationInfo
   *            The representation information that will be tested.
   * @return NULL if the requested method can be performed, the status of the
   *         response otherwise.
   */
  Status getStatus(Method method, RepresentationInfo representationInfo);

  /**
   * Returns the condition based on the modification date of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Unmodified-Since" header.
   * 
   * @return The condition date.
   */
  Date getUnmodifiedSince() {
    return this->unmodifiedSince;
  }

  /**
   * Indicates if there are some conditions set.
   * 
   * @return True if there are some conditions set.
   */
  bool hasSome();

  /**
   * Indicates if there are some range conditions set.
   * 
   * @return True if there are some range conditions set.
   */
  bool hasSomeRange() {
    return getRangeTag() != NULL || getRangeDate() != NULL;
  }

  /**
   * Sets the modifiable list of tags that must be matched.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Match" header.
   * 
   * @param tags
   *            The "if-match" condition.
   */
  void setMatch(std::list<Tag> tags) {
    this->match = tags;
  }

  /**
   * Sets the condition based on the modification date of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Modified-Since" header.
   * 
   * @param date
   *            The modification date.
   */
  void setModifiedSince(Date date) {
    this->modifiedSince = DateUtils.unmodifiable(date);
  }

  /**
   * Sets the modifiable list of tags that mustn't match. Creates a new
   * instance if no one has been set.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-None-Match" header.
   * 
   * @param tags
   *            The list of tags that mustn't match.
   */
  void setNoneMatch(std::list<Tag> tags) {
    this->noneMatch = tags;
  }

  /**
   * Sets the range condition based on the modification date of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Range" header.
   * 
   * @param rangeDate
   *            The date of the range condition.
   */
  void setRangeDate(Date rangeDate) {
    this->rangeDate = rangeDate;
  }

  /**
   * Sets the range condition based on the entity tag of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Range" header.
   * 
   * @param rangeTag
   *            The entity tag of the range condition.
   */
  void setRangeTag(Tag rangeTag) {
    this->rangeTag = rangeTag;
  }

  /**
   * Sets the condition based on the modification date of the requested
   * variant.<br>
   * <br>
   * Note that when used with HTTP connectors, this property maps to the
   * "If-Unmodified-Since" header.
   * 
   * @param date
   *            The condition date.
   */
  void setUnmodifiedSince(Date date) {
    this->unmodifiedSince = DateUtils.unmodifiable(date);
  }

 private:

  /** The "if-match" condition. */
  volatile std::list<Tag> match;

  /** The "if-modified-since" condition. */
  volatile Date modifiedSince;

  /** The "if-none-match" condition. */
  volatile std::list<Tag> noneMatch;

  /** The "if-range" condition as a Date. */
  volatile Date rangeDate;

  /** The "if-range" condition as an entity tag. */
  volatile Tag rangeTag;

  /** The "if-unmodified-since" condition */
  volatile Date unmodifiedSince;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_CONDITIONS_H_
