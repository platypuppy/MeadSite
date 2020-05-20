////////////////////////////////////////////////////////////////////////////////
#ifndef WARBOATS_H
#define WARBOATS_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{
  namespace WarBoats
  {
    enum Orientation {oHORIZONTAL, oVERTICAL, oDIAGONAL_RIGHT, oDIAGONAL_LEFT};
    enum ShotResult {srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL};
    enum DamageType {dtOK = 0, dtBLOWNUP = -1};
    enum BoatPlacement {bpACCEPTED, bpREJECTED};

    struct Point
    {
      int x; // x-coordinate (column)
      int y; // y-coordinate (row)
    };

    struct Boat
    {
      int hits;                 // Hits taken so far
      int ID;                   // Unique ID
      int length;               // Length of the boat
      Orientation orientation;  // Horizontal/Vertical
      Point position;           // x-y coordinate (left-top)
    };

    struct ShotStats
    {
      int hits;       // shots hit a boat
      int misses;     // shots missed all boats
      int duplicates; // shot was already taken
      int sunk;       // how many boats have been sunk
    };

  } // namespace WarBoats

} // namespace CS170

#endif // WARBOATS_H
////////////////////////////////////////////////////////////////////////////////
