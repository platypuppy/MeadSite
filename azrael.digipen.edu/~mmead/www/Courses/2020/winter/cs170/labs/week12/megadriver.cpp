#include <iostream> // cout, endl
#include <cstdlib>  // atoi
#include <ctime>    // time_t, clock
#include "Vector.h" // our Vector class
#include "PRNG.h"   // our random number generator

#define SHOW_COMPARES
#define SHOW_TIMESx

// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int number = CS170::Utils::Random(low, high); 
  return number;
}

void Shuffle(int *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    int r = CS170::Utils::Random(0, 2 << 29) % size;
    int t = array[i];
    array[i] = array[r];
    array[r] = t;
  }
}  

void Print(const CS170::Vector& array, bool newline = true)
{
  for (unsigned i = 0; i < array.size(); i++)
  {
    std::cout << array[i] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

void PrintPartial(const CS170::Vector& array, bool newline = true)
{
  for (unsigned i = 1; i < array.size(); i *= 2)
  {
    std::cout << array[i - 1] << "  ";
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

void TestPush()
{
  std::cout << "\n********** TestPush **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(i);
    Print(a);
  }

  std::cout << "pop_back until empty:\n";
  while (!a.empty())
  {
    a.pop_front();
    Print(a);
  }
}

void TestPop()
{
  std::cout << "\n********** TestPop **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(i);
    Print(a);
  }

  std::cout << "pop_back/pop_front:\n";
  a.pop_back();
  a.pop_front();
  Print(a);

  std::cout << "pop_back/front until empty:\n";
  while (!a.empty())
  {
    a.pop_front();
    a.pop_back();
    Print(a);
  }
}

void TestRemove()
{
  std::cout << "\n********** TestRemove **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "remove(0), remove(3):\n";
  a.remove(0);
  a.remove(3);
  Print(a);
}

void TestInsert1()
{
  std::cout << "\n********** TestInsert **********\n";
  CS170::Vector a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "insert(99, 3):\n";
  a.insert(99, 3);
  Print(a);
  std::cout << "insert(98, 0):\n";
  a.insert(98, 0);
  Print(a);
  std::cout << "insert(97, 6):\n";
  a.insert(97, 6);
  Print(a);
}

void TestSubscripts()
{
  std::cout << "\n********** TestSubscripts **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  Print(a);

  std::cout << "multiple each value by 3:\n";
  for (unsigned i = 0; i < 10; i++)
    a[i] = a[i] * 3;
  Print(a);
}

void TestArray()
{
  std::cout << "\n********** TestArray **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";
  CS170::Vector a(ia, size);
  Print(a);
}

void TestSubscript1()
{
  std::cout << "\n********** TestSubscript1 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";
  const CS170::Vector a(ia, size);
  Print(a);

  unsigned index = a.size() / 2;
  std::cout << "using subscript: a[" << index << "]" << std::endl;
  std::cout << "a[" << index << "] = " << a[index] << std::endl;
}

void TestALot1()
{
  std::cout << "\n********** TestALot1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "push_back 10 odd integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i + 1);
  Print(a);

  std::cout << "empty/fill with 10 ints 3 times:\n";
  for (int i = 0; i < 3; i++)
  {
    while (!a.empty())
      a.pop_back();

    for (int j = 0; j < 10; j++)
      a.push_back(j);
  }
  Print(a);

  std::cout << "remove all but 3 integers:\n";
  while (a.size() > 3)
    a.pop_back();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "push_back 10 more integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);
}

void TestCopy()
{
  std::cout << "\n********** TestCopy **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  std::cout << "Copy: b(a), print a,b\n";
  CS170::Vector b(a);
  Print(a);
  Print(b);

  std::cout << "Copy: c(b), print b,c\n";
  const CS170::Vector c(b);
  Print(b);
  Print(c);
}

void TestAssign()
{
  std::cout << "\n********** TestAssign **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 10 integers:\n";
  for (int i = 0; i < 10; i++)
  {
    a.push_back(2 * i);
    b.push_back(i);
  }

  Print(a);
  Print(b);

  std::cout << "Assign: b = a, print a,b\n";
  b = a;
  Print(a);
  Print(b);

  std::cout << "Assign: a = a, print a\n";
  a = a;
  Print(a);
}

void TestAdd1()
{
  std::cout << "\n********** TestAdd1 **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    b.push_front(10 * i);
    Print(b);
  }

  std::cout << "c = a + b:\n";
  CS170::Vector c;
  c = a + b;

  Print(a);
  Print(b);
  Print(c);

  std::cout << "clear a,b print c\n";
  a.clear();
  b.clear();
  Print(c);
}

void TestAdd2()
{
  std::cout << "\n********** TestAdd2 **********\n";
  CS170::Vector a, b;

  std::cout << "push_back 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(i);
    Print(a);
  }

  std::cout << "push_front 5 integers:\n";
  for (int i = 0; i < 5; i++)
  {
    b.push_front(10 * i);
    Print(b);
  }

  std::cout << "a += b:\n";
  a += b;
  Print(a);
  Print(b);

  std::cout << "clear b print a\n";
  b.clear();
  Print(a);

  std::cout << "a += a:\n";
  a += a;
  Print(a);
}

void TestSelectionSort1()
{
  int count = 10;
  std::cout << "\n********** TestSelectionSort1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 10 random integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, 20));

  Print(a);
  CS170::Vector::SortResult results = a.selection_sort();

#ifdef SHOW_COMPARES
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
#else
  std::cout << "Sorted:\n" << results.compares;
#endif
  Print(a);
}

void TestSelectionSort2()
{
  int count = 10;
  std::cout << "\n********** TestSelectionSort2 **********\n";
  CS170::Vector a;

  std::cout << "push_back " << count << " integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  Print(a);
  CS170::Vector::SortResult results = a.selection_sort();
#ifdef SHOW_COMPARES
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
#else
  std::cout << "Sorted:\n" << results.compares;
#endif
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(i);

  Print(a);
  results = a.selection_sort();
#ifdef SHOW_COMPARES
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
#else
  std::cout << "Sorted:\n" << results.compares;
#endif
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " integers:\n";
  for (int i = count; i > 0; i--)
    a.push_back(5);

  Print(a);
  results = a.selection_sort();
#ifdef SHOW_COMPARES
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
#else
  std::cout << "Sorted:\n" << results.compares;
#endif
  Print(a);
}

void TestSelectionSortStress()
{
  int count = 10000;
  std::cout << "\n********** TestSelectionSortStress **********\n";
  CS170::Vector a;

  std::srand(6);
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, count));

  CS170::Vector::SortResult results = a.selection_sort();

#ifdef SHOW_COMPARES
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
#else
  std::cout << "Sorted:\n" << results.compares;
#endif
  for (unsigned i = 1; i < static_cast<unsigned>(count); i *= 2)
    std::cout << a[i] << "  ";
  std::cout << std::endl;
  //Print(a);
}

void TestBSearch1()
{
  int count = 10;
  std::cout << "\n********** TestBSearch1 **********\n";
  CS170::Vector a, b;

  std::srand(6);
  std::cout << "push_back 10 random integers:\n";
  for (unsigned i = 0; i < static_cast<unsigned>(count); i++)
  {
    a.push_back(RandomInt(1000, 9999));
    b.push_back(a[i]);
  }

  Print(a);
  a.selection_sort();
  Print(a);

  for (unsigned i = 0; i < a.size(); i++)
  {
    int index = a.bsearch(b[i]);
    std::cout << "Index of " << b[i] << " is " << index << std::endl;
  }
}

void TestBSearchStress()
{
  int count = 10000;
  std::cout << "\n********** TestBSearchStress **********\n";
  CS170::Vector a;

  int *ia = new int[count];

  std::cout << "Generating...\n";
  for (int i = 0; i < count; i++)
    ia[i] = i;

  std::cout << "Shuffling...\n";
  Shuffle(ia, count);

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(ia[i]);

  //Print(a);
  a.selection_sort();
  //Print(a);

  std::cout << "Searching...\n";
#ifdef SHOW_TIMES
  std::time_t start = std::clock();
#endif
  for (int i = 0; i < 100; i++)
  {
    for (int j = 0; j < count; j++)
    {
      a.bsearch(ia[i]);
      //std::cout << "Index of " << ia[i] << " is " << index << std::endl;
    }
  }
#ifdef SHOW_TIMES
  std::time_t end = std::clock();
#endif
  std::cout << "Done...\n";
#ifdef SHOW_TIMES
  std::cout << "Elapsed time: " << (static_cast<double>(end - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
  delete [] ia;
}

void TestReverse1()
{
  int count = 10;
  std::cout << "\n********** TestReverse1 **********\n";
  CS170::Vector a;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);

  std::cout << "Remove last element:\n";
  a.pop_back();
  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);
}

void TestReverse2()
{
  int count = 10;
  std::cout << "\n********** TestReverse2 **********\n";
  CS170::Vector a;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  Print(a);
  a.reverse();
  std::cout << "Reversed:\n";
  Print(a);

  while (!a.empty())
  {
    if (a.size() % 2) // odd
    {
      std::cout << "Remove last element:\n";
      a.pop_back();
    }
    else // even
    {
      std::cout << "Remove first element:\n";
      a.pop_front();
    }
    Print(a);
    a.reverse();
    std::cout << "Reversed:\n";
    Print(a);
  }
}

void TestSwap1()
{
  std::cout << "\n********** TestSwap1 **********\n";
  CS170::Vector a, b, c;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i + 1);
  for (int i = 0; i < 5; i++)
    b.push_back(10 * (i + 1));

  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  std::cout << "swapv a,b:\n";
  a.swapv(b);
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  std::cout << "swapv a,c:\n";
  a.swapv(c);
  std::cout << "a: ";
  Print(a);
  std::cout << "c: ";
  Print(c);

  std::cout << "swapv b,b:\n";
  b.swapv(b);
  std::cout << "b: ";
  Print(b);
}

void TestSwapStress()
{
  std::cout << "\n********** TestSwapStress **********\n";
  CS170::Vector a, b, c;

  int count = 1000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
  {
    a.push_back(i);
    b.push_back(i * 2);
    c.push_back(i * 3);
  }

  std::cout << "Swapping...\n";
  CS170::Vector x;
#ifdef SHOW_TIMES
  std::time_t start = std::clock();
#endif
  for (int i = 0; i < 10000001; i++)
  {
    a.swapv(b);
    b.swapv(c);
    c.swapv(a);
  }

  PrintPartial(a);
  PrintPartial(b);
  PrintPartial(c);

#ifdef SHOW_TIMES
  std::time_t end = std::clock();
#endif
  std::cout << "Done...\n";
#ifdef SHOW_TIMES
  std::cout << "Elapsed time: " << (static_cast<double>(end - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
}

void TestAssignStress1()
{
  std::cout << "\n********** TestAssignStress1 **********\n";
  CS170::Vector a;

  int count = 20000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  std::cout << "Swapping...\n";
  CS170::Vector x;
#ifdef SHOW_TIMES
  std::time_t start = std::clock();
#endif
  for (int i = 0; i < 10; i++)
  {
    x = a;
  }
#ifdef SHOW_TIMES
  std::time_t end = std::clock();
#endif
  std::cout << "Done...\n";
#ifdef SHOW_TIMES
  std::cout << "Elapsed time: " << (static_cast<double>(end - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
}

void TestAssignStress2()
{
  std::cout << "\n********** TestAssignStress2 **********\n";
  CS170::Vector a;

  int count = 20000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  std::cout << "Swapping...\n";
  CS170::Vector x;
#ifdef SHOW_TIMES
  std::time_t start = std::clock();
#endif
  for (int i = 0; i < 5; i++)
  {
    x = a;
    a.push_back(0);
  }
#ifdef SHOW_TIMES
  std::time_t end = std::clock();
#endif
  std::cout << "Done...\n";
#ifdef SHOW_TIMES
  std::cout << "Elapsed time: " << (static_cast<double>(end - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
}

void TestEqual1()
{
  std::cout << "\n********** TestEqual1 **********\n";
  CS170::Vector a, b, c;

  std::cout << "push_back integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(i + 1);
  for (int i = 0; i < 10; i++)
    b.push_back(i + 1);

  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);

  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of a:\n";
  a.pop_back();
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of b:\n";
  b.pop_back();
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "change last element of b to 100:\n";
  b[b.size() - 1] = 100;
  std::cout << "a: ";
  Print(a);
  std::cout << "b: ";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";
}

int Sum(const CS170::Vector& v)
{
  int sum = 0;
  for (unsigned i = 0; i < v.size(); i++)
    sum += v[i];
  return sum;
}

void TestCrazy()
{
  int count = 10000;
  std::cout << "\n********** TestCrazy **********\n";
  CS170::Vector a;

  std::srand(6);
  for (int i = 0; i < count; i++)
    a.push_back(i + 1);

  std::cout << "Sum before: " << Sum(a) << std::endl;
  //Print(a);
  for (unsigned i = 0; i < a.size(); i++)
  {
    int from = RandomInt(0, static_cast<int>(a.size()) - 1);
    int value = a[static_cast<unsigned>(from)];
    a.remove(value);
    int to = RandomInt(0, static_cast<int>(a.size()) - 1);
    a.insert(value, static_cast<unsigned>(to));
  }
  std::cout << " Sum after: " << Sum(a) << std::endl;
  //Print(a);
  for (unsigned i = 1; i < a.size(); i *= 2)
    std::cout << a[i] << " ";
  std::cout << std::endl;
}

void TestSubscriptEx()
{
  std::cout << "\n********** TestSubscriptEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";

  const CS170::Vector a(ia, size); // const
  CS170::Vector b(ia, size);       // non-const
  Print(a);
  Print(b);

  try
  {
    unsigned index = a.size() * 2; // illegal
    std::cout << "accessing subscript on const vector: a[" << index << "]" << std::endl;
    std::cout << a[index] << std::endl;
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }

  try
  {
    unsigned index = b.size() * 2; // illegal
    std::cout << "accessing subscript on non-const vector: b[" << index << "]" << std::endl;
    std::cout << b[index] << std::endl;
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }

}

void TestInsertEx()
{
  std::cout << "\n********** TestInsertEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";
  CS170::Vector a(ia, size);
  Print(a);

  try
  {
    unsigned index = a.size() * 3; // illegal
    std::cout << "insert integer at index " << index << ":\n";
    a.insert(99, index);
  }
  catch(const CS170::SubscriptError &se)
  {
    std::cout << "Bad subscript: " << se.GetSubscript() << std::endl;
  }
}

void TestShrink1()
{
  std::cout << "\n********** TestShrink1 **********\n";
  CS170::Vector a;

  std::cout << "push_back 8 integers:\n";
  for (int i = 0; i < 8; i++)
    a.push_back(i);
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "pop last 3:\n";
  a.pop_back();
  a.pop_back();
  a.pop_back();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "push_back one integer:\n";
  a.push_back(100);
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);
}

//***********************************************************************
//***********************************************************************
//***********************************************************************
typedef void (*TestFn)();

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000)
{
  if (maxwait + safewait > 0)
    fn();
}

int main(int argc, char **argv)
{
  CS170::Utils::srand(1, 0);

  int test_num = 0;
  if (argc > 1)
    test_num = std::atoi(argv[1]);

  struct TimedTest
  {
    const char *fn;
    void (*test)();
    int maxwait;
    int safewait;
  };

  int maxwait =  100;
  int safewait = 100;
  TimedTest Tests[] = {
                    {"TestPush",                TestPush,                maxwait, safewait}, //  1 
                    {"TestPop",                 TestPop,                 maxwait, safewait}, //  2
                    {"TestRemove",              TestRemove,              maxwait, safewait}, //  3
                    {"TestInsert1",             TestInsert1,             maxwait, safewait}, //  4
                    {"TestSubscripts",          TestSubscripts,          maxwait, safewait}, //  5
                    {"TestArray",               TestArray,               maxwait, safewait}, //  6
                    {"TestSubscript1",          TestSubscript1,          maxwait, safewait}, //  7
                    {"TestALot1",               TestALot1,               maxwait, safewait}, //  8
                    {"TestCopy",                TestCopy,                maxwait, safewait}, //  9
                    {"TestAssign",              TestAssign,              maxwait, safewait}, // 10
                    {"TestAdd1",                TestAdd1,                maxwait, safewait}, // 11
                    {"TestAdd2",                TestAdd2,                maxwait, safewait}, // 12
                    {"TestSelectionSort1",      TestSelectionSort1,      maxwait, safewait}, // 13
                    {"TestSelectionSort2",      TestSelectionSort2,      maxwait, safewait}, // 14
                    {"TestBSearch1",            TestBSearch1,            maxwait, safewait}, // 15
                    {"TestReverse1",            TestReverse1,            maxwait, safewait}, // 16
                    {"TestReverse2",            TestReverse2,            maxwait, safewait}, // 17
                    {"TestSwap1",               TestSwap1,               maxwait, safewait}, // 18
                    {"TestEqual1",              TestEqual1,              maxwait, safewait}, // 19
                    {"TestShrink1",             TestShrink1,             maxwait, safewait}, // 20
                    {"TestSubscriptEx",         TestSubscriptEx,         maxwait, safewait}, // 21
                    {"TestInsertEx",            TestInsertEx,            maxwait, safewait}, // 22
                    {"TestBSearchStress",       TestBSearchStress,          1000,      500}, // 23
                    {"TestSelectionSortStress", TestSelectionSortStress,    1000,      500}, // 24
                    {"TestSwapStress",          TestSwapStress,             2000,     1000}, // 25
                    {"TestAssignStress1",       TestAssignStress1,          4000,     2000}, // 26
                    {"TestAssignStress2",       TestAssignStress2,          4000,     2000}, // 27
                    {"TestCrazy",               TestCrazy,                  1000,      500}, // 28
                 };

  int num = static_cast<int>(sizeof(Tests) / sizeof(*Tests));
  if (test_num == 0)
  {
    for (int i = 0; i < num; i++)
      ExecuteTest(Tests[i].test, Tests[i].maxwait, Tests[i].safewait);
  }
  else if (test_num == 99)
  {
    for (int i = 0; i < 24; i++)
      ExecuteTest(Tests[i].test, Tests[i].maxwait, Tests[i].safewait);
  }
  else if (test_num > 0 && test_num <= num)
  {
    ExecuteTest(Tests[test_num - 1].test, Tests[test_num - 1].maxwait, Tests[test_num - 1].safewait);
  }

  return 0;
}
