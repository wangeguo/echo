#include <echo/data/conditions.h>

namespace echo {
namespace data {

std::list<Tag> Conditions::getMatch() {
  // Lazy initialization with double-check.
  std::list<Tag> m = this->match;
  if (m == NULL) {
    synchronized (this) {
      m = this->match;
      if (m == NULL) {
        this->match = m = new ArrayList<Tag>();
      }
    }
  }
  return m;
}

std::list<Tag> Conditions::getNoneMatch() {
  // Lazy initialization with double-check.
  std::list<Tag> n = this->noneMatch;
  if (n == NULL) {
    synchronized (this) {
      n = this->noneMatch;
      if (n == NULL) {
        this->noneMatch = n = new ArrayList<Tag>();
      }
    }
  }
  return n;
}

Status Conditions::getRangeStatus(RepresentationInfo representationInfo) {
  return getRangeStatus((representationInfo == NULL) ? NULL
                        : representationInfo.getTag(),
                        (representationInfo == NULL) ? NULL : representationInfo
                        .getModificationDate());
}

Status Conditions::getRangeStatus(Tag tag, Date modificationDate) {
  Status result = Status.CLIENT_ERROR_PRECONDITION_FAILED;
  if (getRangeTag() != NULL) {
    bool all = getRangeTag().equals(Tag.ALL);

    // If a tag exists
    if (tag != NULL) {
      if (all || getRangeTag().equals(tag)) {
        result = Status.SUCCESS_OK;
      }
    }
  } else if (getRangeDate() != NULL) {
    // If a modification date exists
    if (getRangeDate().equals(modificationDate)) {
      result = Status.SUCCESS_OK;
    }
  }

  return result;
}

Status Conditions::getStatus(Method method, bool entityExists, Tag tag,
                             Date modificationDate) {
  Status result = NULL;

  // Is the "if-Match" rule followed or not?
  if ((this->match != NULL) && !this->match.isEmpty()) {
    bool matched = false;
    bool failed = false;
    const bool all = getMatch().get(0).equals(Tag.ALL);

    if (entityExists) {
      // If a tag exists
      if (!all && (tag != NULL)) {
        // Check if it matches one of the representations already
        // cached by the client
        Tag matchTag;

        for (const Iterator<Tag> iter = getMatch().iterator(); !matched
                                        && iter.hasNext();) {
          matchTag = iter.next();
          matched = matchTag.equals(tag, false);
        }
      } else {
        matched = all;
      }
    } else {
      // See
      // http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html#sec14.24
      // If none of the entity tags match, or if "*" is given and no
      // current entity exists, the server MUST NOT perform the
      // requested method
      failed = all;
    }

    failed = failed || !matched;

    if (failed) {
      result = Status.CLIENT_ERROR_PRECONDITION_FAILED;
    }
  }

  // Is the "if-None-Match" rule followed or not?
  if ((result == NULL) && (this->noneMatch != NULL)
      && !this->noneMatch.isEmpty()) {
    bool matched = false;

    if (entityExists) {
      // If a tag exists
      if (tag != NULL) {
        // Check if it matches one of the representations
        // already cached by the client
        Tag noneMatchTag;

        for (const Iterator<Tag> iter = getNoneMatch().iterator(); !matched
                                        && iter.hasNext();) {
          noneMatchTag = iter.next();
          matched = noneMatchTag.equals(tag, (Method.GET
                                              .equals(method) || Method.HEAD.equals(method)));
        }

        // The current representation matches one of those already
        // cached by the client
        if (matched) {
          // Check if the current representation has been updated
          // since the "if-modified-since" date. In this case, the
          // rule is followed.
          const Date modifiedSince = getModifiedSince();
          const bool isModifiedSince = (modifiedSince != NULL)
                                       && (DateUtils.after(new Date(), modifiedSince)
                                           || (modificationDate == NULL) || DateUtils
                                           .after(modifiedSince, modificationDate));
          matched = !isModifiedSince;
        }
      }
    } else {
      matched = getNoneMatch().get(0).equals(Tag.ALL);
    }

    if (matched) {
      if (Method.GET.equals(method) || Method.HEAD.equals(method)) {
        result = Status.REDIRECTION_NOT_MODIFIED;
      } else {
        result = Status.CLIENT_ERROR_PRECONDITION_FAILED;
      }
    }
  }

  // Is the "if-Modified-Since" rule followed or not?
  if ((result == NULL) && (getModifiedSince() != NULL)) {
    const Date modifiedSince = getModifiedSince();
    const bool isModifiedSince = (DateUtils.after(new Date(),
                                                  modifiedSince)
                                  || (modificationDate == NULL) || DateUtils.after(
                                      modifiedSince, modificationDate));

    if (!isModifiedSince) {
      if (Method.GET.equals(method) || Method.HEAD.equals(method)) {
        result = Status.REDIRECTION_NOT_MODIFIED;
      } else {
        result = Status.CLIENT_ERROR_PRECONDITION_FAILED;
      }
    }
  }

  // Is the "if-Unmodified-Since" rule followed or not?
  if ((result == NULL) && (getUnmodifiedSince() != NULL)) {
    const Date unModifiedSince = getUnmodifiedSince();
    const bool isUnModifiedSince = ((unModifiedSince == NULL)
                                    || (modificationDate == NULL) || DateUtils.after(
                                        modificationDate, unModifiedSince));

    if (!isUnModifiedSince) {
      result = Status.CLIENT_ERROR_PRECONDITION_FAILED;
    }
  }

  return result;
}

Status Conditions::getStatus(Method method, RepresentationInfo representationInfo) {
  return getStatus(method, representationInfo != NULL,
                   (representationInfo == NULL) ? NULL : representationInfo
                   .getTag(), (representationInfo == NULL) ? NULL
                   : representationInfo.getModificationDate());
}

bool Conditions::hasSome() {
  return (((this->match != NULL) && !this->match.isEmpty())
          || ((this->noneMatch != NULL) && !this->noneMatch.isEmpty())
          || (getModifiedSince() != NULL) || (getUnmodifiedSince() != NULL));
}

} // namespace data
} // namespace echo

