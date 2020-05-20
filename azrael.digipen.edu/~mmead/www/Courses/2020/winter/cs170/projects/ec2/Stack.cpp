#include <iostream> // cout, endl
#include <climits>  // UINT_MAX
#include "Stack.h"  // The Stack definition

namespace CS170
{

Stack::Stack(size_t maxsize) : maxsize_(maxsize), size_(0)
{
  if (!maxsize_)
    maxsize_ = UINT_MAX;
}

bool Stack::empty() const
{
  return size_ == 0;
}

} // namespace CS170
