#include <echo/data/language.h>

namespace echo {
namespace data {

const Language Language::ALL("*", "All languages");
const Language Language::DEFAULT(java.util.Locale.getDefault().getLanguage());
const Language Language::ENGLISH("en", "English language");
const Language Language::ENGLISH_US("en-us", "English language in USA");
const Language Language::FRENCH("fr", "French language");
const Language Language::FRENCH_FRANCE("fr-fr", "French language in France");
const Language Language::SPANISH("es", "Spanish language");

static Language Language::valueOf(const std::string name) {
  Language result = NULL;

  if ((name != NULL) && !name.equals("")) {
    if (name.equalsIgnoreCase(ALL.getName())) {
      result = ALL;
    } else if (name.equalsIgnoreCase(ENGLISH.getName())) {
      result = ENGLISH;
    } else if (name.equalsIgnoreCase(ENGLISH_US.getName())) {
      result = ENGLISH_US;
    } else if (name.equalsIgnoreCase(FRENCH.getName())) {
      result = FRENCH;
    } else if (name.equalsIgnoreCase(FRENCH_FRANCE.getName())) {
      result = FRENCH_FRANCE;
    } else if (name.equalsIgnoreCase(SPANISH.getName())) {
      result = SPANISH;
    } else {
      result = new Language(name);
    }
  }

  return result;
}

Language::Language(const std::string name, const std::string description) {
  Metadata(name, description);
  this->subTags = NULL;
}

bool Language::equals(const Object object) {
  return (object instanceof Language)
      && getName().equalsIgnoreCase(((Language) object).getName());
}

Language Language::getParent() {
  Language result = NULL;

  if ((getSubTags() != NULL) && !getSubTags().isEmpty()) {
    result = Language.valueOf(getPrimaryTag());
  } else {
    result = equals(ALL) ? NULL : ALL;
  }

  return result;
}

std::string Language::getPrimaryTag() {
  const int separator = getName().indexOf('-');

  if (separator == -1) {
    return getName();
  }

  return getName().substring(0, separator);
}

std::list<std::string> Language::getSubTags() {
  // Lazy initialization with double-check.
  std::list<std::string> v = this->subTags;
  if (v == NULL) {
    synchronized (this) {
      v = this->subTags;
      if (v == NULL) {
        std::list<std::string> tokens = new CopyOnWriteArrayList<std::string>();
        if (getName() != NULL) {
          const std::string[] tags = getName().split("-");
          if (tags.length > 0) {
            for (int i = 1; i < tags.length; i++) {
              tokens.add(tags[i]);
            }
          }
        }

        this->subTags = v = Collections.unmodifiableList(tokens);
      }
    }
  }
  return v;
}

int Language::hashCode() {
  return (getName() == NULL) ? 0 : getName().toLowerCase().hashCode();
}

bool Language::includes(Metadata included) {
  bool result = equals(ALL) || (included == NULL) || equals(included);

  if (!result && (included instanceof Language)) {
    Language includedLanguage = (Language) included;

    if (getPrimaryTag().equals(includedLanguage.getPrimaryTag())) {
      // Both languages are different
      if (getSubTags().equals(includedLanguage.getSubTags())) {
        result = true;
      } else if (getSubTags().isEmpty()) {
        result = true;
      }
    }
  }

  return result;
}

} // namespace data
} // namespace echo
