////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

#include "WarBoats.h"

namespace CS170
{
  namespace WarBoats
  {
    const int HIT_OFFSET = 100; //!< Add this to the boat ID

    /*!
      This class represents the "board" in WarBoats
    */
    class Ocean
    {
      public:
        
        // Public methods...

          // Provided
        const int *GetGrid(void) const;
        Point GetDimensions(void) const;

      private:
        int *grid_;        //!< The 2D ocean
        int x_quadrants_;  //!< Ocean size along x-axis
        int y_quadrants_;  //!< Ocean size along y-axis
        
        // Other private members...

    }; // class Ocean

  } // namespace WarBoats

} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
