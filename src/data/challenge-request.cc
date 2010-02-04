#include <echo/data/challenge-request.h>

namespace echo {
namespace data {

ChallengeRequest::ChallengeRequest(ChallengeScheme scheme, std::string realm) {
  super(scheme, realm);
  domainRefs = null;
  qualityOptions = null;
  stale = false;
}

bool ChallengeRequest::equals(const Object obj) {
  bool result = (obj == this);

  // if obj == this no need to go further
  if (!result) {
    // if obj isn't a challenge request or is null don't evaluate
    // further
    if (obj instanceof ChallengeRequest) {
      final ChallengeRequest that = (ChallengeRequest) obj;
      result = (getParameters().equals(that.getParameters()));

      if (result) {
        if (getRealm() != null) {
          result = getRealm().equals(that.getRealm());
        } else {
          result = (that.getRealm() == null);
        }

        if (result) {
          if (getScheme() != null) {
            result = getScheme().equals(that.getScheme());
          } else {
            result = (that.getScheme() == null);
          }
        }
      }
    }
  }

  return result;
}

std::list<Reference> ChallengeRequest::getDomainRefs() {
  // Lazy initialization with double-check.
  std::list<Reference> r = domainRefs;
  if (r == null) {
    synchronized (this) {
      r = domainRefs;
      if (r == null) {
        domainRefs = r = new CopyOnWriteArrayList<Reference>();
        domainRefs.add(new Reference("/"));
      }
    }
  }
  return r;
}

std::list<std::string> ChallengeRequest::getQualityOptions() {
  // Lazy initialization with double-check.
  std::list<std::string> r = qualityOptions;
  if (r == null) {
    synchronized (this) {
      r = qualityOptions;
      if (r == null) {
        qualityOptions = r = new CopyOnWriteArrayList<std::string>();
        qualityOptions.add(QUALITY_AUTHENTICATION);
      }
    }
  }
  return r;
}

void ChallengeRequest::setDomainUris(Collection<std::string> domainUris) {
  std::list<Reference> domainRefs = null;

  if (domainUris != null) {
    domainRefs = new CopyOnWriteArrayList<Reference>();

    for (std::string domainUri : domainUris) {
      domainRefs.add(new Reference(domainUri));
    }
  }

  setDomainRefs(domainRefs);
}

} // namespace data
} // namespace echo


