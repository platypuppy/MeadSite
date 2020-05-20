#include "Vector.h"
#include <iostream>  // cout
#include <cstdlib>   // abort

namespace CS170
{

Vector::Vector() : array_(0), size_(0), capacity_(0), allocs_(0)
{
}

bool Vector::empty() const
{
  return size_ == 0;
}

unsigned Vector::size() const
{
  return size_;
}

unsigned Vector::capacity() const
{
  return capacity_;
}

unsigned Vector::allocations() const
{
  return allocs_;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Vector::check_bounds(unsigned index) const
{
    // Don't have to check for < 0 because index is unsigned
  if (index >= size_)
  {
    std::cout << "Attempting to access index " << index << ".";
    std::cout << " The size of the array is " << size_ << ". Aborting...\n";
    std::abort();
  }
}

void Vector::grow()
{
    // Double the capacity
  if (capacity_)
    capacity_ *= 2;
  else
    capacity_ = 1;
    
    // Rest of the code here...

}

} // namespace CS170
