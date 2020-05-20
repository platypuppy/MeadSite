////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{

// Do not modify this class
class SubscriptError
{
  public:
    SubscriptError(int Subscript) : subscript_(Subscript) {};
    int GetSubscript() const { return subscript_; }

  private:
    int subscript_;
};

template <typename T>
class Vector
{
  public:

    static const int NO_INDEX = -1;

    struct SortResult
    {
      unsigned compares;
      unsigned swaps;
    };

      // Adds an element to the back of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items.
    void push_back(const T& value);

      // Adds an element to the front of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items. All items to the right must be
      // shifted over one element to the right.
    void push_front(const T& value);

      // Concatenates a vector onto the end of this vector.
      // This operator is optimized from the previous lab. Instead of growing
      // the vector incrementally as we push_back more items, we are going to
      // grow it once to accommodate all of the new items. See the driver for
      // output details, especially the number of allocations performed.
    Vector& operator+=(const Vector& rhs);

    // More public methods from the previous lab (Vector4)

  private:
    T *array_;          // The dynamically allocated array
    
    // Other private stuff ...

};

} // namespace CS170

#include "Vector.cpp"

#endif // VECTOR_H
