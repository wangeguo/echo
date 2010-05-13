#ifndef _ECHO_DATA_PREFERENCE_H_
#define _ECHO_DATA_PREFERENCE_H_

#include <string>
#include <echo/util/series.h>
#include <echo/data/metadata.h>

namespace echo {
namespace data {

/**
 * Metadata preference definition.
 * 
 * @author Jerome Louvel
 */
//public final class Preference<T extends Metadata> {
template<Metadata T> class Preference {

 public:

  /**
   * Constructor.
   */
  Preference() {
    Preference(NULL, 1F, NULL);
  }

  /**
   * Constructor.
   * 
   * @param metadata
   *            The associated metadata.
   */
  Preference(T metadata) {
    Preference(metadata, 1F, NULL);
  }

  /**
   * Constructor.
   * 
   * @param metadata
   *            The associated metadata.
   * @param quality
   *            The quality/preference level.
   */
  Preference(T metadata, float quality) {
    Preference(metadata, quality, NULL);
  }

  /**
   * Constructor.
   * 
   * @param metadata
   *            The associated metadata.
   * @param quality
   *            The quality/preference level.
   * @param parameters
   *            The list of parameters.
   */
  Preference(T metadata, float quality, Series<Parameter> parameters);

  /**
   * Returns the metadata associated with this preference.
   * 
   * @return The metadata associated with this preference.
   */
  T getMetadata() {
    return this->metadata;
  }

  /**
   * Returns the modifiable list of parameters. Creates a new instance if no
   * one has been set.
   * 
   * @return The modifiable list of parameters.
   */
  Series<Parameter> getParameters();

  /**
   * Returns the quality/preference level.
   * 
   * @return The quality/preference level.
   */
  float getQuality() {
    return this->quality;
  }

  /**
   * Sets the metadata associated with this preference.
   * 
   * @param metadata
   *            The metadata associated with this preference.
   */
  void setMetadata(T metadata) {
    this->metadata = metadata;
  }

  /**
   * Sets the modifiable list of parameters.
   * 
   * @param parameters
   *            The modifiable list of parameters.
   */
  void setParameters(Series<Parameter> parameters) {
    this->parameters = parameters;
  }

  /**
   * Sets the quality/preference level.
   * 
   * @param quality
   *            The quality/preference level.
   */
  void setQuality(float quality) {
    this->quality = quality;
  }

  //@Override
  std::string toString();

 private:

  /** The metadata associated with this preference. */
  volatile T metadata;

  /** The modifiable list of parameters. */
  volatile Series<Parameter> parameters;

  /** The quality/preference level. */
  volatile float quality;

};

} // namespace data
} // namespace echo

#endif // _ECHO_DATA_PREFERENCE_H_
