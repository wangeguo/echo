#include <echo/data/challenge-scheme.h>

namespace echo {
namespace data {

static ChallengeScheme ChallengeScheme::valueOf(const std::string name) {
  ChallengeScheme result = null;

  if ((name != null) && !name.equals("")) {
    if (name.equalsIgnoreCase(CUSTOM.getName())) {
      result = CUSTOM;
    } else if (name.equalsIgnoreCase(HTTP_AWS_S3.getName())) {
      result = HTTP_AWS_S3;
    } else if (name.equalsIgnoreCase(HTTP_BASIC.getName())) {
      result = HTTP_BASIC;
    } else if (name.equalsIgnoreCase(HTTP_COOKIE.getName())) {
      result = HTTP_COOKIE;
    } else if (name.equalsIgnoreCase(HTTP_DIGEST.getName())) {
      result = HTTP_DIGEST;
    } else if (name.equalsIgnoreCase(HTTP_AZURE_SHAREDKEY.getName())) {
      result = HTTP_AZURE_SHAREDKEY;
    } else if (name.equalsIgnoreCase(HTTP_AZURE_SHAREDKEY_LITE
                                     .getName())) {
      result = HTTP_AZURE_SHAREDKEY_LITE;
    } else if (name.equalsIgnoreCase(HTTP_NTLM.getName())) {
      result = HTTP_NTLM;
    } else if (name.equalsIgnoreCase(HTTP_OAUTH.getName())) {
      result = HTTP_OAUTH;
    } else if (name.equalsIgnoreCase(POP_BASIC.getName())) {
      result = POP_BASIC;
    } else if (name.equalsIgnoreCase(POP_DIGEST.getName())) {
      result = POP_DIGEST;
    } else if (name.equalsIgnoreCase(SMTP_PLAIN.getName())) {
      result = SMTP_PLAIN;
    } else {
      result = new ChallengeScheme(name, null, null);
    }
  }

  return result;
}

ChallengeScheme::ChallengeScheme(const std::string name,
                                 const std::string technicalName,
                                 const std::string description) {
  this->name = name;
  this->description = description;
  this->technicalName = technicalName;
}

boolean ChallengeScheme::equals(const Object object) {
  return (object instanceof ChallengeScheme)
      && ((ChallengeScheme) object).getName().equalsIgnoreCase(
          getName());
}

int ChallengeScheme::hashCode() {
  return (getName() == null) ? 0 : getName().toLowerCase().hashCode();
}


const ChallengeScheme
ChallengeScheme::CUSTOM("CUSTOM","Custom", "Custom authentication");

const ChallengeScheme
ChallengeScheme::HTTP_AWS_S3("HTTP_AWS", "AWS", "Amazon S3 HTTP authentication");

const ChallengeScheme
ChallengeScheme::HTTP_BASIC("HTTP_BASIC", "Basic", "Basic HTTP authentication");

const ChallengeScheme
ChallengeScheme::HTTP_COOKIE("HTTP_Cookie", "Cookie", "Cookie HTTP authentication");

const ChallengeScheme
ChallengeScheme::HTTP_DIGEST("HTTP_DIGEST", "Digest", "Digest HTTP authentication");

const ChallengeScheme
ChallengeScheme::HTTP_AZURE_SHAREDKEY(
    "HTTP_AZURE_SHAREDKEY", "SharedKey",
    "Microsoft Azure Shared Key authorization (authentication)");

const ChallengeScheme
ChallengeScheme::HTTP_AZURE_SHAREDKEY_LITE(
    "HTTP_AZURE_SHAREDKEY_LITE",
    "SharedKeyLite",
    "Microsoft Azure Shared Key lite authorization\ (authentication)");

const ChallengeScheme
ChallengeScheme::HTTP_NTLM("HTTP_NTLM", "NTLM", "Microsoft NTLM HTTP authentication");

const ChallengeScheme
ChallengeScheme::HTTP_OAUTH("HTTP_OAuth", "OAuth", "Open protocol for API authentication");

const ChallengeScheme
ChallengeScheme::POP_BASIC("POP_BASIC", "Basic",
                           "Basic POP authentication (USER/PASS commands)");

const ChallengeScheme
ChallengeScheme::POP_DIGEST("POP_DIGEST", "Digest",
                            "Digest POP authentication (APOP command)");

const ChallengeScheme
ChallengeScheme::SMTP_PLAIN("SMTP_PLAIN", "PLAIN", "Plain SMTP authentication");

const ChallengeScheme 
ChallengeScheme::FTP_PLAIN("FTP_PLAIN", "PLAIN", "Plain FTP authentication");

} // namespace data
} // namespace echo

