#include "Point.h"  // Point members
#include <cmath>    // sqrt, atan, sin, cos

namespace CS170
{

const double PI = 3.1415926535897;
const double EPSILON = 0.00001;

///////////////////////////////////////////////////////////////////////////////
// private member functions 
double Point::DegreesToRadians(double degrees) const
{
  return (degrees * PI / 180.0);
}

double Point::RadiansToDegrees(double radians) const
{
  return (radians * 180.0 / PI);
}


///////////////////////////////////////////////////////////////////////////////
// 16 public member functions (2 constructors, 14 operators) 




///////////////////////////////////////////////////////////////////////////////
// 2 friend functions (operators)




///////////////////////////////////////////////////////////////////////////////
// 2 non-members, non-friends (operators)



} // namespace CS170



