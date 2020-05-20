#include "WarBoats.h"
#include "Ocean.h"

namespace CS170
{

namespace WarBoats
{
  
  /*
   * ALL STUDENT IMPLEMENTATION GOES HERE
  */

  const int *Ocean::GetGrid() const
  {
    return grid_;
  }
  
  Point Ocean::GetDimensions() const
  {
    Point pt = {x_quadrants_, y_quadrants_};
    return pt;
  }

} // namespace WarBoats

} // namespace CS170

