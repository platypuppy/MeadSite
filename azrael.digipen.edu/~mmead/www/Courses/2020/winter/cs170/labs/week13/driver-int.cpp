#include <iostream> // cout, endl
#include <cstdlib>  // atoi
#include <ctime>    // time_t, clock
#include "Vector.h"
#include "PRNG.h"

#define SHOW_COMPARES
#define SHOW_TIMESx

bool KILLED = false;

// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int number = CS170::Utils::Random(low, high); 
  return number;
}

template <typename T>
void Shuffle(T *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    int r = CS170::Utils::Random(0, 2 << 29) % size;
    int t = array[i];
    array[i] = array[r];
    array[r] = t;
  }
}  

template <typename T>
void Print(const CS170::Vector<T>& array, bool newline = true)
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

template <typename T>
void PrintPartial(const CS170::Vector<T>& array, bool newline = true)
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

template <typename T>
void TestPush(void)
{
  std::cout << "\n********** TestPush **********\n";
  CS170::Vector<T> a;
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

template <typename T>
void TestPop(void)
{
  std::cout << "\n********** TestPop **********\n";
  CS170::Vector<T> a;
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

template <typename T>
void TestRemove(void)
{
  std::cout << "\n********** TestRemove **********\n";
  CS170::Vector<T> a;
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

template <typename T>
void TestInsert1(void)
{
  std::cout << "\n********** TestInsert **********\n";
  CS170::Vector<T> a;
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

template <typename T>
void TestSubscripts(void)
{
  std::cout << "\n********** TestSubscripts **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  Print(a);

  std::cout << "multiple each value by 3:\n";
  for (unsigned i = 0; i < 10; i++)
    a[i] = a[i] * 3;
  Print(a);
}

template <typename T>
void TestArray(void)
{
  std::cout << "\n********** TestArray **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";
  CS170::Vector<T> a(ia, size);
  Print(a);
}

template <typename T>
void TestSubscript1(void)
{
  std::cout << "\n********** TestSubscript1 **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";
  const CS170::Vector<T> a(ia, size);
  Print(a);

  unsigned index = a.size() / 2;
  std::cout << "using subscript: a[" << index << "]" << std::endl;
  std::cout << "a[" << index << "] = " << a[index] << std::endl;
}

template <typename T>
void TestALot1(void)
{
  std::cout << "\n********** TestALot1 **********\n";
  CS170::Vector<T> a;

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

template <typename T>
void TestCopy(void)
{
  std::cout << "\n********** TestCopy **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back 10 even integers:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(2 * i);

  std::cout << "Copy: b(a), print a,b\n";
  CS170::Vector<T> b(a);
  Print(a);
  Print(b);

  std::cout << "Copy: c(b), print b,c\n";
  const CS170::Vector<T> c(b);
  Print(b);
  Print(c);
}

template <typename T>
void TestAssign(void)
{
  std::cout << "\n********** TestAssign **********\n";
  CS170::Vector<T> a, b;

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

template <typename T>
void TestAdd1(void)
{
  std::cout << "\n********** TestAdd1 **********\n";
  CS170::Vector<T> a, b;

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
  CS170::Vector<T> c;
  c = a + b;

  Print(a);
  Print(b);
  Print(c);

  std::cout << "clear a,b print c\n";
  a.clear();
  b.clear();
  Print(c);
}

template <typename T>
void TestAdd2(void)
{
  std::cout << "\n********** TestAdd2 **********\n";
  CS170::Vector<T> a, b;

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

template <typename T>
void TestSelectionSort1(void)
{
  int count = 10;
  std::cout << "\n********** TestSelectionSort1 **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back 10 random integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, 20));

  Print(a);
  typename CS170::Vector<T>::SortResult results = a.selection_sort();

#ifdef SHOW_COMPARES
  std::cout << "Sorted: compares = " << results.compares;
  std::cout << ", swaps = " << results.swaps << std::endl;
#else
  std::cout << "Sorted:\n" << results.compares;
#endif
  Print(a);
}

template <typename T>
void TestSelectionSort2(void)
{
  int count = 10;
  std::cout << "\n********** TestSelectionSort2 **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back " << count << " integers:\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  Print(a);
  typename CS170::Vector<T>::SortResult results = a.selection_sort();
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

template <typename T>
void TestSelectionSortStress(void)
{
  int count = 10000;
  std::cout << "\n********** TestSelectionSortStress **********\n";
  CS170::Vector<T> a;

  std::srand(6);
  for (int i = 0; i < count; i++)
    a.push_back(RandomInt(1, count));

  typename CS170::Vector<T>::SortResult results = a.selection_sort();

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

template <typename T>
void TestBSearch1(void)
{
  int count = 10;
  std::cout << "\n********** TestBSearch1 **********\n";
  CS170::Vector<T> a, b;

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

template <typename T>
void TestBSearchStress(void)
{
  int count = 10000;
  std::cout << "\n********** TestBSearchStress **********\n";
  CS170::Vector<T> a;

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
  std::cout << "Elapsed time: " << ((static_cast<double>(end) - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
  delete [] ia;
}

template <typename T>
void TestReverse1(void)
{
  int count = 10;
  std::cout << "\n********** TestReverse1 **********\n";
  CS170::Vector<T> a;

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

template <typename T>
void TestReverse2(void)
{
  int count = 10;
  std::cout << "\n********** TestReverse2 **********\n";
  CS170::Vector<T> a;

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

template <typename T>
void TestSwap1(void)
{
  std::cout << "\n********** TestSwap1 **********\n";
  CS170::Vector<T> a, b, c;

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

template <typename T>
void TestSwapStress(void)
{
  std::cout << "\n********** TestSwapStress **********\n";
  CS170::Vector<T> a, b, c;

  int count = 1000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
  {
    a.push_back(i);
    b.push_back(i * 2);
    c.push_back(i * 3);
  }

  std::cout << "Swapping...\n";
  CS170::Vector<T> x;
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
  std::cout << "Elapsed time: " << ((static_cast<double>(end) - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
}

template <typename T>
void TestAssignStress1(void)
{
  std::cout << "\n********** TestAssignStress1 **********\n";
  CS170::Vector<T> a;

  int count = 20000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  std::cout << "Swapping...\n";
  CS170::Vector<T> x;
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
  std::cout << "Elapsed time: " << ((static_cast<double>(end) - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
}

template <typename T>
void TestAssignStress2(void)
{
  std::cout << "\n********** TestAssignStress2 **********\n";
  CS170::Vector<T> a;

  int count = 20000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(i);

  std::cout << "Swapping...\n";
  CS170::Vector<T> x;
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
  std::cout << "Elapsed time: " << ((static_cast<double>(end) - start) / CLOCKS_PER_SEC) << " secs\n";
#endif
}

template <typename T>
void TestEqual1(void)
{
  std::cout << "\n********** TestEqual1 **********\n";
  CS170::Vector<T> a, b, c;

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

template <typename T>
int Sum(const CS170::Vector<T>& v)
{
  int sum = 0;
  for (unsigned i = 0; i < v.size(); i++)
    sum += v[i];
  return sum;
}

template <typename T>
void TestCrazy(void)
{
  int count = 10000;
  std::cout << "\n********** TestCrazy **********\n";
  CS170::Vector<T> a;

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

template <typename T>
void TestSubscriptEx(void)
{
  std::cout << "\n********** TestSubscriptEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";

  const CS170::Vector<T> a(ia, size); // const
  CS170::Vector<T> b(ia, size);       // non-const
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

template <typename T>
void TestInsertEx(void)
{
  std::cout << "\n********** TestInsertEx **********\n";
  int ia[] = {2, 4, 6, 6, 8, 10, 6, 12, -6, 14, 16, 6, 6};
  unsigned size = static_cast<unsigned>(sizeof(ia)/sizeof(*ia));
  std::cout << "Construct from int array:\n";
  CS170::Vector<T> a(ia, size);
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

template <typename T>
void TestShrink1(void)
{
  std::cout << "\n********** TestShrink1 **********\n";
  CS170::Vector<T> a;

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

typedef void (*TestFn)(void);

#define WATCHDOGx
#if defined(WATCHDOG) //&& !defined(_DEBUG)

#ifdef _MSC_VER
  #include <process.h>
  #include <stdlib.h>
  #include <windows.h>
  #include <time.h>
#endif

static bool Completed = false;

unsigned __stdcall ThreadTest(void *fn)
{
  Completed = false;

  clock_t start, end;
  try
  {
    TestFn testFn = reinterpret_cast<TestFn>(fn);
    start = clock();
    testFn();
    end = clock();
    Completed = true;
  }
  catch(...)
  {
    printf("Unexpected exception thrown in ThreadTest.\n");
  }

  return 0;
}

//typedef unsigned int (*TestFn) __stdcall (void *);

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000, int announce_level = 2)
{
#ifdef _MSC_VER
  HANDLE thread;
  unsigned threadID;

  thread = (HANDLE) _beginthreadex(NULL, 0, &ThreadTest, fn, 0, &threadID);

  clock_t start = clock();
  WaitForSingleObject(thread, maxwait);
  clock_t end = clock();
  CloseHandle(thread);

  if (!Completed)
  {
    printf("\n********** Test test took too long to complete (over %i ms). **********\n", maxwait);
    KILLED = true;
  }
  else if (end - start > safewait)
    printf("\n********** Test took %i ms. (Inefficient) **********\n", end - start);
  else if (announce_level)
  {
    if (announce_level == 1)
      printf("\nTest completed within efficient time limit. (%i ms)\n", safewait);
    else
      printf("\nTest completed within efficient time limit. (%i ms, max=%i ms)\n", end - start, safewait);
  }

  //printf("\n");
#endif
}
//***********************************************************************
//***********************************************************************
//***********************************************************************

#else // WATCHDOG

void ExecuteTest(TestFn fn, int maxwait = 1000, int safewait = 1000)
{
  if (maxwait + safewait > 0)
    fn();
}

#endif

int main(int argc, char **argv)
{
  CS170::Utils::srand(1, 0);

  int test_num = 0;
  if (argc > 1)
    test_num = std::atoi(argv[1]);

  struct TimedTest
  {
    const char *fn;
    void (*test)(void);
    int maxwait;
    int safewait;
  };

  int maxwait =  100;
  int safewait = 100;

  typedef int T;
  TimedTest Tests[] = {
                    {"TestPush",                TestPush<T>,                maxwait, safewait}, //  1 
                    {"TestPop",                 TestPop<T>,                 maxwait, safewait}, //  2
                    {"TestRemove",              TestRemove<T>,              maxwait, safewait}, //  3
                    {"TestInsert1",             TestInsert1<T>,             maxwait, safewait}, //  4
                    {"TestSubscripts",          TestSubscripts<T>,          maxwait, safewait}, //  5
                    {"TestArray",               TestArray<T>,               maxwait, safewait}, //  6
                    {"TestSubscript1",          TestSubscript1<T>,          maxwait, safewait}, //  7
                    {"TestALot1",               TestALot1<T>,               maxwait, safewait}, //  8
                    {"TestCopy",                TestCopy<T>,                maxwait, safewait}, //  9
                    {"TestAssign",              TestAssign<T>,              maxwait, safewait}, // 10
                    {"TestAdd1",                TestAdd1<T>,                maxwait, safewait}, // 11
                    {"TestAdd2",                TestAdd2<T>,                maxwait, safewait}, // 12
                    {"TestSelectionSort1",      TestSelectionSort1<T>,      maxwait, safewait}, // 13
                    {"TestSelectionSort2",      TestSelectionSort2<T>,      maxwait, safewait}, // 14
                    {"TestBSearch1",            TestBSearch1<T>,            maxwait, safewait}, // 15
                    {"TestReverse1",            TestReverse1<T>,            maxwait, safewait}, // 16
                    {"TestReverse2",            TestReverse2<T>,            maxwait, safewait}, // 17
                    {"TestSwap1",               TestSwap1<T>,               maxwait, safewait}, // 18
                    {"TestEqual1",              TestEqual1<T>,              maxwait, safewait}, // 19
                    {"TestShrink1",             TestShrink1<T>,             maxwait, safewait}, // 20
                    {"TestSubscriptEx",         TestSubscriptEx<T>,         maxwait, safewait}, // 21
                    {"TestInsertEx",            TestInsertEx<T>,            maxwait, safewait}, // 22
                    {"TestBSearchStress",       TestBSearchStress<T>,          1000,      500}, // 23
                    {"TestSelectionSortStress", TestSelectionSortStress<T>,    1000,      500}, // 24
                    {"TestSwapStress",          TestSwapStress<T>,             2000,     1000}, // 25
                    {"TestAssignStress1",       TestAssignStress1<T>,          4000,     2000}, // 26
                    {"TestAssignStress2",       TestAssignStress2<T>,          4000,     2000}, // 27
                    {"TestCrazy",               TestCrazy<T>,                  1000,      500}, // 28
                 };

  KILLED = false;
  int num = static_cast<int>(sizeof(Tests) / sizeof(*Tests));
  if (test_num == 0)
  {
    for (int i = 0; i < num; i++)
      ExecuteTest(Tests[i].test, Tests[i].maxwait, Tests[i].safewait);
  }
  else if (test_num > 0 && test_num <= num)
  {
    ExecuteTest(Tests[test_num - 1].test, Tests[test_num - 1].maxwait, Tests[test_num - 1].safewait);
  }

  return 0;
}
