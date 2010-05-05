#ifndef _ECHO_DATA_RANGE_H_
#define _ECHO_DATA_RANGE_H_

namespace echo {
namespace data {

/**
 * Describes a range of bytes.
 * 
 * @author Jerome Louvel
 */
class Range {

 public:

  /**
   * Default constructor defining a range starting on the first byte and with
   * a maximum size, i.e. covering the whole entity.
   */
  Range() {
    Range(INDEX_FIRST, SIZE_MAX);
  }

  /**
   * Constructor defining a range starting on the first byte and with the
   * given size.
   * 
   * @param size
   *            Size of the range in number of bytes.
   */
  Range(long size) {
    Range(INDEX_FIRST, size);
  }

  /**
   * Constructor.
   * 
   * @param index
   *            Index from which to start the range
   * @param size
   *            Size of the range in number of bytes.
   */
  Range(long index, long size);

  //@Override
  bool equals(Object object);

  /**
   * Returns the index from which to start the range. If the index is superior
   * or equal to zero, the index will define the start of the range. If its
   * value is {@value #INDEX_LAST} (-1), then it defines the end of the range.
   * The default value is {@link #INDEX_FIRST} (0), starting at the first
   * byte.
   * 
   * @return The index from which to start the range.
   */
  long getIndex() {
    return index;
  }

  /**
   * Returns the size of the range in number of bytes. If the size is the
   * maximum available from the index, then use the {@value #SIZE_MAX}
   * constant.
   * 
   * @return The size of the range in number of bytes.
   */
  long getSize() {
    return size;
  }

  /**
   * Indicates if the given index is included in the range.
   * 
   * @param position
   *            The position to test.
   * @param totalSize
   * 
   * @return True if the given index is included in the range, false
   *         otherwise.
   */
  bool isIncluded(long position, long totalSize);

  /**
   * Sets the index from which to start the range. If the index is superior or
   * equal to zero, the index will define the start of the range. If its value
   * is {@value #INDEX_LAST} (-1), then it defines the end of the range. The
   * default value is {@link #INDEX_FIRST} (0), starting at the first byte
   * 
   * @param index
   *            The index from which to start the range.
   */
  void setIndex(long index) {
    this->index = index;
  }

  /**
   * Sets the size of the range in number of bytes. If the size is the maximum
   * available from the index, then use the {@value #SIZE_MAX} constant.
   * 
   * @param size
   *            The size of the range in number of bytes.
   */
  void setSize(long size) {
    this->size = size;
  }

 public:
  
  /**
   * Index for the first byte of an entity.
   */
  const static long INDEX_FIRST;

  /**
   * Index for the last byte of an entity.
   */
  const static long INDEX_LAST;

  /**
   * Maximum size available from the index.
   */
  const static long SIZE_MAX;

 private:

  /**
   * Index from which to start the range. If the index is superior or equal to
   * zero, the index will define the start of the range. If its value is
   * {@value #INDEX_LAST} (-1), then it defines the end of the range. The
   * default value is {@link #INDEX_FIRST} (0), starting at the first byte.
   */
  volatile long index;

  /**
   * Size of the range in number of bytes. If the size is the maximum
   * available from the index, then use the {@value #SIZE_MAX} constant.
   */
  volatile long size;

};

} // namespace data
} // naemspace echo

#endif // _ECHO_DATA_RANGE_H_
