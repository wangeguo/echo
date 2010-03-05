#include <echo/data/client-info.h>

namespace echo {
namespace data {

ClientInfo::ClientInfo() {
  this->address = null;
  this->agent = null;
  this->port = -1;
  this->acceptedCharacterSets = null;
  this->acceptedEncodings = null;
  this->acceptedLanguages = null;
  this->acceptedMediaTypes = null;
  this->forwardedAddresses = null;
  this->from = null;
  this->agentProducts = null;
  this->principals = null;
}

std::list<Preference<CharacterSet>> ClientInfo::getAcceptedCharacterSets() {
  // Lazy initialization with double-check.
  std::list<Preference<CharacterSet>> a = this->acceptedCharacterSets;
  if (a == null) {
    synchronized (this) {
      a = this->acceptedCharacterSets;
      if (a == null) {
        this->acceptedCharacterSets = a = new ArrayList<Preference<CharacterSet>>();
      }
    }
  }
  return a;
}

std::list<Preference<Encoding>> ClientInfo::getAcceptedEncodings() {
  // Lazy initialization with double-check.
  std::list<Preference<Encoding>> a = this->acceptedEncodings;
  if (a == null) {
    synchronized (this) {
      a = this->acceptedEncodings;
      if (a == null) {
        this->acceptedEncodings = a = new ArrayList<Preference<Encoding>>();
      }
    }
  }
  return a;
}

std::list<Preference<Language>> ClientInfo::getAcceptedLanguages() {
  // Lazy initialization with double-check.
  std::list<Preference<Language>> a = this->acceptedLanguages;
  if (a == null) {
    synchronized (this) {
      a = this->acceptedLanguages;
      if (a == null) {
        this->acceptedLanguages = a = new ArrayList<Preference<Language>>();
      }
    }
  }
  return a;
}

std::list<Preference<MediaType>> ClientInfo::getAcceptedMediaTypes() {
  // Lazy initialization with double-check.
  std::list<Preference<MediaType>> a = this->acceptedMediaTypes;
  if (a == null) {
    synchronized (this) {
      a = this->acceptedMediaTypes;
      if (a == null) {
        this->acceptedMediaTypes = a = new ArrayList<Preference<MediaType>>();
      }
    }
  }
  return a;
}

std::map<std::string, std::string> ClientInfo::getAgentAttributes() {

  if (this->agentAttributes == null) {
    this->agentAttributes = new HashMap<std::string, std::string>();
    const std::map<std::string, Object> map = new HashMap<std::string, Object>();

    // Loop on a list of user-agent templates until a template match
    // the current user-agent string. The list of templates is
    // located in a file named "agent.properties" available on
    // the classpath.
    // Some defined variables are used in order to catch the name,
    // version and facultative comment. Respectively, these
    // variables are called "agentName", "agentVersion" and
    // "agentComment".
    org.restlet.routing.Template template = null;
    // Predefined variables.
    const org.restlet.routing.Variable agentName = new org.restlet.routing.Variable(
        org.restlet.routing.Variable.TYPE_TOKEN);
    const org.restlet.routing.Variable agentVersion = new org.restlet.routing.Variable(
        org.restlet.routing.Variable.TYPE_TOKEN);
    const org.restlet.routing.Variable agentComment = new org.restlet.routing.Variable(
        org.restlet.routing.Variable.TYPE_COMMENT);
    const org.restlet.routing.Variable agentCommentAttribute = new org.restlet.routing.Variable(
        org.restlet.routing.Variable.TYPE_COMMENT_ATTRIBUTE);
    const org.restlet.routing.Variable facultativeData = new org.restlet.routing.Variable(
        org.restlet.routing.Variable.TYPE_ALL, null, false, false);
    for (std::string string : ClientInfo.getUserAgentTemplates()) {
      template = new org.restlet.routing.Template(string,
                                                  org.restlet.routing.Template.MODE_EQUALS);
      // Update the predefined variables.
      template.getVariables().put("agentName", agentName);
      template.getVariables().put("agentVersion", agentVersion);
      template.getVariables().put("agentComment", agentComment);
      template.getVariables().put("agentOs", agentCommentAttribute);
      template.getVariables().put("commentAttribute",
                                  agentCommentAttribute);
      template.getVariables().put("facultativeData", facultativeData);
      // Parse the template
      if (template.parse(getAgent(), map) > -1) {
        for (const std::string key : map.keySet()) {
          this->agentAttributes.put(key, (std::string) map.get(key));
        }
        break;
      }
    }
  }

  return this->agentAttributes;
}

std::string ClientInfo::getAgentName() {
  const Product product = getMainAgentProduct();
  if (product != null) {
    return product.getName();
  }

  return null;
}

std::list<Product> ClientInfo::getAgentProducts() {
  if (this->agentProducts == null) {
    this->agentProducts = org.restlet.engine.http.UserAgentUtils
                          .parse(getAgent());
  }
  return this->agentProducts;
}

std::string ClientInfo::getAgentVersion() {
  const Product product = getMainAgentProduct();
  if (product != null) {
    return product.getVersion();
  }
  return null;

}

std::list<std::string> ClientInfo::getForwardedAddresses() {
  // Lazy initialization with double-check.
  std::list<std::string> a = this->forwardedAddresses;
  if (a == null) {
    synchronized (this) {
      a = this->forwardedAddresses;
      if (a == null) {
        this->forwardedAddresses = a = new ArrayList<std::string>();
      }
    }
  }
  return a;
}

Product ClientInfo::getMainAgentProduct() {
  if (this->agentMainProduct == null) {
    if (getAgentAttributes() != null) {
      this->agentMainProduct = new Product(getAgentAttributes().get(
          "agentName"), getAgentAttributes().get("agentVersion"),
                                           getAgentAttributes().get("agentComment"));
    }
  }

  return this->agentMainProduct;
}

CharacterSet ClientInfo::getPreferredCharacterSet(std::list<CharacterSet> supported) {
  return org.restlet.engine.util.ConnegUtils.getPreferredMetadata(
      supported, getAcceptedCharacterSets());
}

Encoding ClientInfo::getPreferredEncoding(std::list<Encoding> supported) {
  return org.restlet.engine.util.ConnegUtils.getPreferredMetadata(
      supported, getAcceptedEncodings());
}

Language ClientInfo::getPreferredLanguage(std::list<Language> supported) {
  return org.restlet.engine.util.ConnegUtils.getPreferredMetadata(
      supported, getAcceptedLanguages());
}

MediaType ClientInfo::getPreferredMediaType(std::list<MediaType> supported) {
  return org.restlet.engine.util.ConnegUtils.getPreferredMetadata(
      supported, getAcceptedMediaTypes());
}

Variant ClientInfo::getPreferredVariant(std::list<Variant> variants,
                                        org.restlet.service.MetadataService metadataService) {
  return org.restlet.engine.util.ConnegUtils.getPreferredVariant(this,
                                                                 variants, metadataService);
}

Variant ClientInfo::getPreferredVariant(org.restlet.resource.Resource resource,
                                        org.restlet.service.MetadataService metadataService) {
  return getPreferredVariant(resource.getVariants(), metadataService);
}

std::list<java.security.Principal> ClientInfo::getPrincipals() {
  // Lazy initialization with double-check.
  std::list<java.security.Principal> a = this->principals;
  if (a == null) {
    synchronized (this) {
      a = this->principals;
      if (a == null) {
        this->principals = a = new ArrayList<java.security.Principal>();
      }
    }
  }
  return a;
}

std::list<org.restlet.security.Role> ClientInfo::getRoles() {
  // Lazy initialization with double-check.
  std::list<org.restlet.security.Role> a = this->roles;
  if (a == null) {
    synchronized (this) {
      a = this->roles;
      if (a == null) {
        this->roles = a = new ArrayList<org.restlet.security.Role>();
      }
    }
  }
  return a;
}

std::string ClientInfo::getUpstreamAddress() {
  if (this->forwardedAddresses == null
      || this->forwardedAddresses.isEmpty()) {
    return getAddress();
  }

  return this->forwardedAddresses.get(0);
}

static std::list<std::string> ClientInfo::getUserAgentTemplates() {
  // Lazy initialization with double-check.
  std::list<std::string> u = ClientInfo.userAgentTemplates;
  if (u == null) {
    synchronized (ClientInfo.class) {
      u = ClientInfo.userAgentTemplates;
      if (u == null) {
        // Load from the "agent.properties" file
        const java.net.URL userAgentPropertiesUrl = Engine
                                                    .getClassLoader().getResource(
                                                        "org/restlet/data/agent.properties");
        if (userAgentPropertiesUrl != null) {
          BufferedReader reader;
          try {
            reader = new BufferedReader(new InputStreamReader(
                userAgentPropertiesUrl.openStream(),
                CharacterSet.UTF_8.getName()));
            std::string line = reader.readLine();
            for (; line != null; line = reader.readLine()) {
              if ((line.trim().length() > 0)
                  && !line.trim().startsWith("#")) {
                if (u == null) {
                  u = new ArrayList<std::string>();
                }
                u.add(line);
              }
            }
            reader.close();
          } catch (IOException e) {
            if (Context.getCurrent() != null) {
              Context
                  .getCurrent()
                  .getLogger()
                  .warning(
                      "Cannot read '"
                      + userAgentPropertiesUrl
                      .toString()
                      + "' due to: "
                      + e.getMessage());
            }

          }
        }
      }
    }
  }
  return u;
}

} // namespace data
} // namespace echo
