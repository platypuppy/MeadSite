#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi

#include "WarBoats.h"
#include "Ocean.h"
#include "PRNG.h"

void Dump(const CS170::WarBoats::Ocean &ocean, int field_width = 4, 
          bool extraline = false, bool showboats = true)
{
    // Get the size of the ocean
  int width = ocean.GetDimensions().x;
  int height = ocean.GetDimensions().y;

  using CS170::WarBoats::HIT_OFFSET;

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      int value = ocean.GetGrid()[y * width + x];
      if ( (value > 0) && (value < HIT_OFFSET) && (showboats == false) )
        value = 0;
      std::cout << std::setw(field_width) << value;
    }
    std::cout << std::endl;
    if (extraline)
      std::cout << std::endl;
  }
}

void PrintShotResult(const CS170::WarBoats::ShotResult &sr)
{
  const char *strings[] = {"HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL"};
  std::cout << strings[static_cast<int>(sr)] << std::endl;
  //if (sr == CS170::WarBoats::srSUNK)
  //  std::cout << "*************************************************\n";
}

void PrintStats(const CS170::WarBoats::Ocean &ocean)
{
  CS170::WarBoats::ShotStats stats = ocean.GetShotStats();
  std::cout << "      Hits: " << std::setw(3) << stats.hits << std::endl;
  std::cout << "    Misses: " << std::setw(3) << stats.misses << std::endl;
  std::cout << "Duplicates: " << std::setw(3) << stats.duplicates << std::endl;
  std::cout << "Boats Sunk: " << std::setw(3) << stats.sunk << std::endl;
}

void TakeAShot(CS170::WarBoats::Ocean &ocean, const CS170::WarBoats::Point& pt)
{
  CS170::WarBoats::ShotResult sr;
  std::cout << "Shot: " << pt.x << ", " << pt.y << "  ";
  sr = ocean.TakeShot(pt);
  PrintShotResult(sr);
  PrintStats(ocean);
  Dump(ocean);
  std::cout << std::endl;
}

void test1()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 5;
  int xsize = 10;
  int ysize = 10;
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  //std::cout << ocean;
  Dump(ocean);
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;
  CS170::WarBoats::BoatPlacement bp;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  boat.ID = 4;
  location.x = 7;
  location.y = 5;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_LEFT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;


  boat.ID = 5;
  location.x = 7;
  location.y = 0;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_RIGHT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  Dump(ocean);
  std::cout << std::endl;

    // Illegal placement
  boat.ID = 6;
  location.x = 6;
  location.y = 4;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_RIGHT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 6;
  location.x = 6;
  location.y = 5;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_RIGHT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 6;
  location.x = 9;
  location.y = 0;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_LEFT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 6;
  location.x = 8;
  location.y = 0;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_LEFT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 6;
  location.x = 6;
  location.y = 0;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_LEFT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 6;
  location.x = 1;
  location.y = 1;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oDIAGONAL_RIGHT;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  //std::cout << ocean;
  Dump(ocean);
  std::cout << std::endl;
}

void test_placement(int num_boats, int xsize, int ysize,  
                    bool show_attempts = false, bool diagonals_only = false, 
                    bool play = false)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

    // Place the boats randomly in the ocean
  int boats_placed = 0;
  int attempts = 0;
  while (boats_placed < num_boats)
  {
    CS170::WarBoats::Boat boat;

    //boat.hits = 0;
    boat.ID = boats_placed + 1;
    CS170::WarBoats::BoatPlacement bp;
    do
    {
      int orientation;

      if (diagonals_only)
        orientation = CS170::Utils::Random(2, 3);
      else
        orientation = CS170::Utils::Random(0, 3);

        // Pick a random orientation
      boat.orientation = CS170::WarBoats::Orientation(orientation);

        // Pick a random location
      CS170::WarBoats::Point location;
      location.x = CS170::Utils::Random(0, xsize - 1);
      location.y = CS170::Utils::Random(0, ysize - 1);
      boat.position = location;

        // Place the boat
      boat.length = CS170::Utils::Random(3, 7);
      bp = ocean.PlaceBoat(boat);

      attempts++;
      if (show_attempts)
      {
        std::cout << "Attempt " << std::setw(3) << attempts << ": len is "
                  << boat.length << ", x,y is " << location.x << ","
                  << location.y << ", orientation is " << boat.orientation;

        if (bp == CS170::WarBoats::bpREJECTED)
          std::cout << " REJECTED" << std::endl;
        else
          std::cout << " ACCEPTED" << std::endl;
      }      


    }while (bp == CS170::WarBoats::bpREJECTED);
    boats_placed++;
  }

  std::cout << "Boats placed:\n";
  Dump(ocean);
  std::cout << std::endl;

  if (!play)
    return;

    // Try to sink the boats with random shots
  while (num_boats > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, xsize - 1);
      coordinate.y = CS170::Utils::Random(0, ysize - 1);
      //std::cout << "target: " << coordinate.x << ", "
      //          << coordinate.y << std::endl;

      sr = ocean.TakeShot(coordinate);
    } while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

#if 0
    {
      PrintShotResult(sr);
      PrintStats(ocean);
      Dump(ocean, 4, false);
      std::cout << std::endl;
    }
#endif
  }

  std::cout << "Final board:\n";
  PrintStats(ocean);
  Dump(ocean, 4, false);
  std::cout << std::endl;
}

void test2()
{
  test_placement(90, 30, 30, false, false, false); 
}

void test3()
{
  test_placement(90, 30, 30, true, false, false); 
}

void test4()
{
  test_placement(90, 30, 30, false, true, false); 
}

void test5()
{
  test_placement(90, 30, 30, true, true, false); 
}

void test6()
{
  test_placement(90, 30, 30, false, false, true); 
}

int main(int argc, char **argv)
{
  int test_num = 0;
  if (argc > 1)
    test_num = std::atoi(argv[1]);

  typedef void (*TestFn)(void);

  TestFn Tests[] = {test1, test2, test3, test4, test5, test6};

  int num = sizeof(Tests) / sizeof(*Tests);
  if (test_num < 1 || test_num > num)
  {
    for (int i = 0; i < num; i++)
      Tests[i]();
  }
  else if (test_num >= 0 && test_num <= num)
  {
    Tests[test_num - 1]();
  }

  return 0;
}
