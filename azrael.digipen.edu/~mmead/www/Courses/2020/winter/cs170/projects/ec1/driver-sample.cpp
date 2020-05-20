#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi

#include "WarBoats.h"
#include "Ocean.h"
#include "PRNG.h"

using namespace CS170::WarBoats;
using CS170::Utils::Random;

static bool forceSpacing = false;
static bool useDiagonals = false;

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

CS170::WarBoats::Ocean RandomOcean(int xsize, int ysize, int num_boats)
{
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize, forceSpacing);

    // Place the boats randomly in the ocean
  int boats_placed = 0;
  //int attempts = 0;
  while (boats_placed < num_boats)
  {
    CS170::WarBoats::Boat boat;        // random boat attributes
    CS170::WarBoats::BoatPlacement bp; // accepted or rejected 
    boat.ID = boats_placed + 1;        // IDs are 1-based

      // Keep placing a random boat until it is accepted
    do
    {
        // Pick a random orientation
      int orientation;

      if (useDiagonals)
        orientation = CS170::Utils::Random(0, 3);
      else
        orientation = CS170::Utils::Random(0, 1);

      boat.orientation = CS170::WarBoats::Orientation(orientation);

        // Pick a random location (all valid)
      CS170::WarBoats::Point location;
      location.x = CS170::Utils::Random(0, xsize - 1);
      location.y = CS170::Utils::Random(0, ysize - 1);
      boat.position = location;
      boat.length = CS170::Utils::Random(3, 7);

        // Place the boat
      bp = ocean.PlaceBoat(boat);

#if 0
      attempts++;
      {
        std::cout << "Attempt " << std::setw(3) << attempts << ": len is "
                  << boat.length << ", x,y is " << location.x << ","
                  << location.y << ", orientation is " << boat.orientation;

        if (bp == CS170::WarBoats::bpREJECTED)
          std::cout << " REJECTED" << std::endl;
        else
          std::cout << " ACCEPTED" << std::endl;
      }      
#endif

    }while (bp == CS170::WarBoats::bpREJECTED); // place until accepted

    boats_placed++;
  }

  return ocean;
}

void RandomShots(CS170::WarBoats::Ocean& ocean, int num_shots)
{
    int num_boats = ocean.GetNumBoats();
    CS170::WarBoats::Point size = ocean.GetDimensions();

    // Try to sink the boats with random shots
  while (num_boats > 0 && num_shots > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, size.x - 1);
      coordinate.y = CS170::Utils::Random(0, size.y- 1);
      sr = ocean.TakeShot(coordinate);
    }
    while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

      // Stop once the number of shots has been reached
    num_shots--;
  }
}

void CompareOceans(const Ocean& lhs, const Ocean& rhs)
{
  if (lhs == rhs)
    std::cout << "The oceans are the same." << std::endl;
  else
    std::cout << "The oceans are NOT the same." << std::endl;
}

// copy constructors
void test_copy()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

  Ocean ocean1 = RandomOcean(20, 12, 10);
  RandomShots(ocean1, 50);
  Ocean copy1(ocean1); // copy constructor

  RandomShots(ocean1, 50);
  Ocean copy2(ocean1); // copy constructor

  std::cout << ocean1 << "-----------------------------------" << std::endl;
  std::cout << copy2 << "-----------------------------------" << std::endl;
  CompareOceans(ocean1, copy2); // the same

  std::cout << copy1 << "-----------------------------------" << std::endl;
  CompareOceans(ocean1, copy1); // NOT the same

  Ocean ocean2 = RandomOcean(12, 20, 5);
  CompareOceans(ocean2, ocean1); // NOT the same

  Ocean ocean3 = RandomOcean(10, 10, 3);
  RandomShots(ocean3, 20);
  Ocean copy3(ocean3); // copy constructor
  CompareOceans(ocean3, copy3); // the same

  RandomShots(copy3, 1);
  std::cout << ocean3 << "-----------------------------------" << std::endl;
  std::cout << copy3 << "-----------------------------------" << std::endl;
  CompareOceans(ocean3, copy3); // NOT the same
}

// default constructors, copy assignment
void test_default_assign()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

  Ocean ocean1 = RandomOcean(20, 12, 10);
  RandomShots(ocean1, 50);

  Ocean copy1;    // default constructor
  copy1 = ocean1; // copy assignment

  RandomShots(ocean1, 50);

  Ocean copy2;    // default constructor
  copy2 = ocean1; // copy assignment

  std::cout << ocean1 << "-----------------------------------" << std::endl;
  std::cout << copy2 << "-----------------------------------" << std::endl;
  CompareOceans(ocean1, copy2); // the same
  std::cout << copy1 << "-----------------------------------" << std::endl;
  CompareOceans(ocean1, copy1); // NOT the same

  Ocean ocean2 = RandomOcean(12, 20, 5);
  CompareOceans(ocean2, ocean1); // NOT the same

  Ocean ocean3 = RandomOcean(10, 10, 3);
  RandomShots(ocean3, 20);
  
  Ocean copy3;    // default constructor
  copy3 = ocean3; // copy assignment

  CompareOceans(ocean3, copy3); // NOT the same

  RandomShots(copy3, 1);
  std::cout << ocean3 << "-----------------------------------" << std::endl;
  std::cout << copy3 << "-----------------------------------" << std::endl;
  CompareOceans(ocean3, copy3); // NOT the same

  copy2 = copy2; // copy assignment
  CompareOceans(copy2, copy2); // the same

  copy2 = copy1 = ocean1;
  CompareOceans(copy1, copy2);  // the same
  CompareOceans(copy2, ocean1); // the same
}

void test_compare()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

  int width = Random(10, 30);
  int height = Random(10, 30);
  int boats = Random(1, width * height / 10);
  Ocean ocean1 = RandomOcean(width, height, boats);

  Ocean copy1(ocean1);
  Ocean copy2;
  copy2 = copy1;

  CompareOceans(ocean1, copy1);
  std::cout << ocean1 << "-----------------------------------" << std::endl;
  std::cout << copy1 << "-----------------------------------" << std::endl;
  CompareOceans(copy1, copy2);
  std::cout << copy1 << "-----------------------------------" << std::endl;
  std::cout << copy2 << "-----------------------------------" << std::endl;

  RandomShots(ocean1, width * height / 4);
  CompareOceans(ocean1, copy1);
  std::cout << ocean1 << "-----------------------------------" << std::endl;
  std::cout << copy1 << "-----------------------------------" << std::endl;
}


void simple_test()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 50;
  int xsize = 10;
  int ysize = 10;
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize, forceSpacing);

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
  location.x = 6;
  location.y = 1;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #3, touches
  boat.ID = 3;
  location.x = 0;
  location.y = 4;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #4, touches
  boat.ID = 4;
  location.x = 0;
  location.y = 0;
  boat.length = 4;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #5, touches
  boat.ID = 5;
  location.x = 4;
  location.y = 4;
  boat.length = 2;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #6, touches
  boat.ID = 6;
  location.x = 4;
  location.y = 0;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #7, touches
  boat.ID = 7;
  location.x = 7;
  location.y = 0;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #8, touches
  boat.ID = 8;
  location.x = 5;
  location.y = 5;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Boat #9, touches
  boat.ID = 9;
  location.x = 7;
  location.y = 4;
  boat.length = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;


  Dump(ocean);
  std::cout << std::endl;
}

void test_placement(int num_boats, int xsize, int ysize,  
                    bool show_attempts = false, bool diagonals = false, 
                    bool force_spacing = false, bool play = false)
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize, force_spacing);

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

        // include diagonals?
      if (diagonals)
        orientation = CS170::Utils::Random(0, 3);
      else
        orientation = CS170::Utils::Random(0, 1);

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

void test1()
{
  forceSpacing = false;
  simple_test();
  forceSpacing = true;
  simple_test();
}

/*
void test_placement(int num_boats, int xsize, int ysize,  
bool show_attempts = false, bool diagonals = false,  bool play = false)
*/

// no attempts shown, game played
void test_all1()
{
  test_placement(70, 40, 40, false, useDiagonals, forceSpacing, true); 
}

// no attempts shown, no game played
void test_all2()
{
  test_placement(65, 50, 20, false, useDiagonals, forceSpacing, true); 
}


int main(int argc, char **argv)
{
  int test_num = 0;

  if (argc > 1)
    test_num = std::atoi(argv[1]);

  if (argc > 2)
  {
    int value = std::atoi(argv[2]);
    if (value)
      useDiagonals = true;
    else
      useDiagonals = false;
  }

  if (argc > 3)
  {
    int value = std::atoi(argv[3]);
    if (value)
      forceSpacing = true;
    else
      forceSpacing = false;
  }

  typedef void (*TestFn)(void);

  TestFn Tests[] = {test_copy,
                    test_default_assign,
                    test_compare,
                    test_all1,
                    test_all2, 
                   };

  int num = sizeof(Tests) / sizeof(*Tests);
  if (test_num == 99)
  {
      // 1 1 1
    useDiagonals = true;
    forceSpacing = true;
    Tests[0]();

      // 2 1 1
    useDiagonals = true;
    forceSpacing = true;
    Tests[1]();

      // 3 1 1
    useDiagonals = true;
    forceSpacing = true;
    Tests[2]();

      // 4 0 0
    useDiagonals = false;
    forceSpacing = false;
    Tests[3]();

      // 4 0 1
    useDiagonals = false;
    forceSpacing = true;
    Tests[3]();

      // 4 1 0
    useDiagonals = true;
    forceSpacing = false;
    Tests[3]();

      // 4 1 1
    useDiagonals = true;
    forceSpacing = true;
    Tests[3]();

      // 5 1 1
    useDiagonals = true;
    forceSpacing = true;
    Tests[4]();

  }
  else if (test_num < 1 || test_num > num)
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
