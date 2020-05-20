#include <iostream> // cout, endl
#include <iomanip>  // setw
#include <cstdlib>  // atoi

#include "WarBoats.h"
#include "Ocean.h"
#include "PRNG.h"

using namespace CS170::WarBoats;
using CS170::Utils::Random;


void PrintShotResult(const CS170::WarBoats::ShotResult &sr)
{
  const char *strings[] = {"HIT", "MISS", "DUPLICATE", "SUNK", "ILLEGAL"};
  std::cout << strings[static_cast<int>(sr)] << std::endl;
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
  std::cout << ocean;
  std::cout << std::endl;
}

void test0()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 3;
  int xsize = 8;
  int ysize = 8;
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  std::cout << ocean;
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;
  CS170::WarBoats::BoatPlacement bp;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
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
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 4;
  location.x = 10;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 4;
  location.x = 2;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

      // Illegal placement
  boat.ID = 4;
  location.x = 5;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  bp = ocean.PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  std::cout << ocean;
  std::cout << std::endl;
}

void test1()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 3;
  int xsize = 8;
  int ysize = 8;
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  std::cout << ocean;
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean.PlaceBoat(boat);

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  ocean.PlaceBoat(boat);

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean.PlaceBoat(boat);

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  std::cout << ocean;
  std::cout << std::endl;

  CS170::WarBoats::Point coordinate;

    // Illegal coordinate
  coordinate.x = 10;
  coordinate.y = 5;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 1;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // MISS
  coordinate.x = 5;
  coordinate.y = 7;
  TakeAShot(ocean, coordinate);

    // DUPLICATE
  coordinate.x = 1;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 2;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // HIT
  coordinate.x = 3;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);

    // SUNK
  coordinate.x = 4;
  coordinate.y = 3;
  TakeAShot(ocean, coordinate);
}

void test2()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean (check 100, 30x30)
  int num_boats = 5;
  int xsize = 10;
  int ysize = 10;

    // Use a pointer to an ocean and dynamically create it
  CS170::WarBoats::Ocean *ocean;
  ocean = new CS170::WarBoats::Ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  std::cout << *ocean;
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;

    // Boat #1
  boat.ID = 1;
  location.x = 1;
  location.y = 3;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean->PlaceBoat(boat);

    // Boat #2
  boat.ID = 2;
  location.x = 5;
  location.y = 1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  ocean->PlaceBoat(boat);

    // Boat #3
  boat.ID = 3;
  location.x = 0;
  location.y = 5;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean->PlaceBoat(boat);

    // Boat #4
  boat.ID = 4;
  location.x = 3;
  location.y = 8;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oHORIZONTAL;
  ocean->PlaceBoat(boat);

    // Boat #5
  boat.ID = 5;
  location.x = 9;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  ocean->PlaceBoat(boat);

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  std::cout << *ocean;
  std::cout << std::endl;

    // Try to sink the boats with random shots
  int shots = 0;
  while (num_boats > 0)
  {
    CS170::WarBoats::ShotResult sr;
    do
    {
      CS170::WarBoats::Point coordinate;
      coordinate.x = CS170::Utils::Random(0, xsize - 1);
      coordinate.y = CS170::Utils::Random(0, ysize - 1);
      std::cout << "Shot #"
                << ++shots
                << " at coordinate "
                << coordinate.x
                << ", "
                << coordinate.y
                << "  ";

      sr = ocean->TakeShot(coordinate);
      PrintShotResult(sr);
    } while (sr == CS170::WarBoats::srDUPLICATE);

      // Sunk a boat
    if (sr == CS170::WarBoats::srSUNK)
      num_boats--;

    //if (sr == CS170::WarBoats::srSUNK)
    {
      //PrintShotResult(sr);
      PrintStats(*ocean);
      std::cout << *ocean;
      std::cout << std::endl;
    }
  }

  // Must delete the ocean "manually"
  delete ocean;
}

void test3()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(0, 0);

    // Setup the ocean
  int num_boats = 1;
  int xsize = 5;
  int ysize = 5;

  CS170::WarBoats::Ocean *ocean;
  ocean = new CS170::WarBoats::Ocean(num_boats, xsize, ysize);

  std::cout << "The empty board" << std::endl;
  std::cout << *ocean;
  std::cout << std::endl;

  CS170::WarBoats::Boat boat;
  CS170::WarBoats::Point location;
  CS170::WarBoats::BoatPlacement bp;

    // Illegal placement
  boat.ID = 1;
  location.x = -1;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = -10;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = -1;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = -10;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 6;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 100;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

	    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = 6;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Illegal placement
  boat.ID = 1;
  location.x = 0;
  location.y = 100;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

    // Legal placement
  boat.ID = 1;
  location.x = 0;
  location.y = 0;
  boat.position = location;
  boat.orientation = CS170::WarBoats::oVERTICAL;
  bp = ocean->PlaceBoat(boat);
  if (bp == CS170::WarBoats::bpREJECTED)
    std::cout << "Boat placement is rejected." << std::endl;
  else
    std::cout << "Boat placement is accepted." << std::endl;

  std::cout << "The board with " << num_boats << " boats" << std::endl;
  std::cout << *ocean;
  std::cout << std::endl;

  CS170::WarBoats::Point coordinate;

    // Illegal coordinate
  coordinate.x = -1;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = -100;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = -1;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = -100;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 6;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 60;
  coordinate.y = 0;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = 6;
  TakeAShot(*ocean, coordinate);

  coordinate.x = 0;
  coordinate.y = 60;
  TakeAShot(*ocean, coordinate);

  delete ocean;
}

CS170::WarBoats::Ocean RandomOcean(int xsize, int ysize, int num_boats)
{
  CS170::WarBoats::Ocean ocean(num_boats, xsize, ysize);

    // Place the boats randomly in the ocean
  int boats_placed = 0;
  while (boats_placed < num_boats)
  {
    CS170::WarBoats::Boat boat;        // random boat attributes
    CS170::WarBoats::BoatPlacement bp; // accepted or rejected 
    boat.ID = boats_placed + 1;        // IDs are 1-based

      // Keep placing a random boat until it is accepted
    do
    {
        // Pick a random orientation
      boat.orientation = CS170::Utils::Random(0, 1)
                                 ? CS170::WarBoats::oHORIZONTAL
                                 : CS170::WarBoats::oVERTICAL;

        // Pick a random location (all valid)
      CS170::WarBoats::Point location;
      location.x = CS170::Utils::Random(0, xsize - 1);
      location.y = CS170::Utils::Random(0, ysize - 1);
      boat.position = location;

        // Place the boat
      bp = ocean.PlaceBoat(boat);

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
void test4()
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
void test5()
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

  CompareOceans(ocean3, copy3); // the same

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

int gSeed = 0;

void test6()
{
    // Initialize the pseudo-random number generator
  CS170::Utils::srand(gSeed, gSeed + gSeed);

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



int main(int argc, char **argv)
{
  int test_num = -1;
  if (argc > 1)
    test_num = std::atoi(argv[1]);

  if (argc > 2)
    gSeed = std::atoi(argv[2]);

  typedef void (*TestFn)(void);

    // test0 - test3 are from before
  TestFn Tests[] = {test0, test1, test2, test3, test4, test5, test6};

  int num = sizeof(Tests) / sizeof(*Tests);
  if (test_num < 0 || test_num > num)
  {
    for (int i = 0; i < num; i++)
      Tests[i]();
  }
  else if (test_num >= 0 && test_num <= num)
  {
    Tests[test_num]();
  }

  return 0;
}
