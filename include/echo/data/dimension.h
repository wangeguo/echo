#ifndef _ECHO_DATA_DIMENSION_H_
#define _ECHO_DATA_DIMENSION_H_

//#include <echo/response.h>

namespace echo {
namespace data {

/**
 * Dimension on which the representations of a resource may vary. Note that when
 * used with HTTP connectors, this class maps to the "Vary" header.
 * 
 * @see Response#getDimensions()
 * @author Jerome Louvel
 * @author Piyush Purang (ppurang@gmail.com)
 */
enum Dimension {
  AUTHORIZATION,
  CHARACTER_SET,
  CLIENT_ADDRESS,
  CLIENT_AGENT,
  UNSPECIFIED,
  ENCODING,
  LANGUAGE,
  MEDIA_TYPE,
  TIME,
}

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_DIMENSION_H_
