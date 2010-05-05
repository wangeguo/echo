#include <echo/data/protocol.h>

namespace echo {
namespace data {

const int Protocol::UNKNOWN_PORT(-1);

const Protocol Protocol::AJP("ajp", "AJP",
                             "Apache Jakarta Protocol", 8009);

const Protocol Protocol::ALL("all", "ALL",
                             "Wildcard for all protocols", UNKNOWN_PORT);

const Protocol Protocol::CLAP("clap", "CLAP",
                              "Class Loader Access Protocol", UNKNOWN_PORT, true);

const Protocol Protocol::FILE("file", "FILE",
                              "Local File System Protocol", UNKNOWN_PORT, true);

const Protocol Protocol::FTP("ftp", "FTP",
                             "File Transfer Protocol", 21);

const Protocol Protocol::HTTP("http", "HTTP",
                              "HyperText Transport Protocol", 80);

const Protocol Protocol::HTTPS("https", "HTTPS",
                               "HyperText Transport Protocol (Secure)", 443, true);

const Protocol Protocol::JAR("jar", "JAR",
                             "Java ARchive", UNKNOWN_PORT, true);

const Protocol Protocol::JDBC("jdbc", "JDBC",
                              "Java DataBase Connectivity", UNKNOWN_PORT);

const Protocol Protocol::POP("pop", "POP",
                             "Post Office Protocol", 110);

const Protocol Protocol::POPS("pops", "POPS",
                              "Post Office Protocol (Secure)", 995, true);

const Protocol Protocol::RIAP("riap", "RIAP",
                              "Restlet Internal Access Protocol", UNKNOWN_PORT, true);

const Protocol Protocol::SMTP("smtp", "SMTP",
                              "Simple Mail Transfer Protocol", 25);

const Protocol Protocol::SMTPS("smtps", "SMTPS",
                               "Simple Mail Transfer Protocol (Secure)", 465, true);

const Protocol Protocol::WAR("war", "WAR",
                             "Web Archive Access Protocol", UNKNOWN_PORT, true);

const Protocol Protocol::ZIP("zip", "ZIP",
                             "Zip Archive Access Protocol", UNKNOWN_PORT, true);

Protocol Protocol::valueOf(const std::string name) {
  Protocol result = null;

  if ((name != null) && !name.equals("")) {
    if (name.equalsIgnoreCase(AJP.getSchemeName())) {
      result = AJP;
    } else if (name.equalsIgnoreCase(CLAP.getSchemeName())) {
      result = CLAP;
    } else if (name.equalsIgnoreCase(FILE.getSchemeName())) {
      result = FILE;
    } else if (name.equalsIgnoreCase(FTP.getSchemeName())) {
      result = FTP;
    } else if (name.equalsIgnoreCase(HTTP.getSchemeName())) {
      result = HTTP;
    } else if (name.equalsIgnoreCase(HTTPS.getSchemeName())) {
      result = HTTPS;
    } else if (name.equalsIgnoreCase(JAR.getSchemeName())) {
      result = JAR;
    } else if (name.equalsIgnoreCase(JDBC.getSchemeName())) {
      result = JDBC;
    } else if (name.equalsIgnoreCase(POP.getSchemeName())) {
      result = POP;
    } else if (name.equalsIgnoreCase(POPS.getSchemeName())) {
      result = POPS;
    } else if (name.equalsIgnoreCase(RIAP.getSchemeName())) {
      result = RIAP;
    } else if (name.equalsIgnoreCase(SMTP.getSchemeName())) {
      result = SMTP;
    } else if (name.equalsIgnoreCase(SMTPS.getSchemeName())) {
      result = SMTPS;
    } else if (name.equalsIgnoreCase(WAR.getSchemeName())) {
      result = WAR;
    } else if (name.equalsIgnoreCase(ZIP.getSchemeName())) {
      result = ZIP;
    } else {
      result = new Protocol(name);
    }
  }

  return result;
}

Protocol::Protocol(const std::string schemeName) {
  Protocol(schemeName, schemeName.toUpperCase(), schemeName.toUpperCase()
           + " Protocol", UNKNOWN_PORT);
}

Protocol::Protocol(const std::string schemeName, const std::string name,
                   const std::string description, int defaultPort,
                   const bool confidential) {
  this->name = name;
  this->description = description;
  this->schemeName = schemeName;
  this->defaultPort = defaultPort;
  this->confidential = confidential;
}

bool Protocol::equals(const Object object) {
  return (object instanceof Protocol)
      && getName().equalsIgnoreCase(((Protocol) object).getName());
}

} // namespace data
} // namespace echo
