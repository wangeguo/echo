#include <echo/data/range.h>

namespace echo {
namespace data {

const static long Range::INDEX_FIRST(0);
const static long Range::INDEX_LAST(-1);
const static long Range::SIZE_MAX(-1);

Range::Range(long index, long size) {
  this->index = index;
  this->size = size;
}
 
bool Range::equals(Object object) {
  return (object instanceof Range)
      && ((Range) object).getIndex() == getIndex()
      && ((Range) object).getSize() == getSize();
}

bool Range::isIncluded(long position, long totalSize) {
  bool result = false;

  if (getIndex() == INDEX_LAST) {
    // The range starts from the end
    result = (0 <= position) && (position < totalSize);

    if (result) {
      result = position >= (totalSize - getSize());
    }
  } else {
    // The range starts from the beginning
    result = position >= getIndex();

    if (result && (getSize() != SIZE_MAX)) {
      result = position < getIndex() + getSize();
    }
  }

  return result;
}

} // namespace data
} // naemspace echo

