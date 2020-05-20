#include <iostream> // cout, endl
#include <cstdlib>  // atoi
#include <ctime>    // time_t, clock
#include <cstring>  // strcpy
#include <cstdio>   // sprintf

#include "Vector.h"
#include "PRNG.h"

bool SHOW_COMPARES = false;
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
    std::cout << array[i] << std::endl;
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
    std::cout << array[i - 1] << std::endl;
  }

  std::cout << "(size=" << array.size() << ", capacity=" << 
                           array.capacity() << ", allocs=" << 
                           array.allocations() << ")";
  if (newline)
    std::cout << std::endl;
}

enum SortByKind {sbkID, sbkName, sbkSalary, sbkYears};

SortByKind SortBy = sbkName;

const unsigned ID_LEN = 16;
struct Person
{
  char ID[ID_LEN + 1];
  char lastName[26];   
  char firstName[26];  
  float salary;        
  unsigned years;           

  operator int () const
  {
    return years;
  }  

  bool operator!=(const Person &rhs) const
  {
    if (strcmp(ID, rhs.ID))
      return true;
    if (salary != rhs.salary)
      return true;
    if (years != rhs.years)
      return true;
    if (strcmp(lastName, rhs.lastName))
      return true;
    if (strcmp(firstName, rhs.firstName))
      return true;

    return false;
  }

  bool operator<(const Person &rhs) const
  {
    if (SortBy == sbkID)
    {
      if (strcmp(ID, rhs.ID) < 0)
        return true;
      else
        return false;
    }
    else if (SortBy == sbkSalary)
    {
      return salary < rhs.salary;
    }
    else if (SortBy == sbkYears)
    {
      return years < rhs.years;
    }
    else if (SortBy == sbkName)
    {
      int diff = strcmp(lastName, rhs.lastName);
      
      // if the last names are the same, sort on first name
      if (diff == 0)
      {
        if (strcmp(firstName, rhs.firstName) < 0)
          return true;
        else 
          return false; // both first and last are the same
      }
      else // last names are different
      {
        if (diff < 0)
          return true;
        else
          return false;
      }
    }
    else // default
      return ID < rhs.ID;
  }
};

struct Person PEOPLE[] = 
{
  {"101000", "Last",       "First",        0,  0},
  {"101001", "Faith",      "Ian",      30000, 10},
  {"102001", "Tufnel",     "Nigel",    90000, 12},
  {"103001", "Savage",     "Viv",      50000,  3},
  {"104001", "Shrimpton",  "Mick",     50000,  3},
  {"105001", "Besser",     "Joe",      40000,  5},
  {"106001", "Smalls",     "Derek",    80000, 10},
  {"107001", "St.Hubbins", "David",    90000, 11},
  {"108001", "Fleckman",   "Bobbi",   120000,  8},
  {"109001", "Eton-Hogg",  "Denis",   250000, 22},
  {"110001", "Upham",      "Danny",    60000,  5},
  {"111001", "McLochness", "Ross",     60000,  6},
  {"112001", "Pudding",    "Ronnie",   50000,  2},
  {"113001", "Schindler",  "Danny",    60000,  3},
  {"114001", "Pettibone",  "Jeanine",  85000,  3},
  {"115001", "Fame",       "Duke",     95000,  8},
  {"116001", "Fufkin",     "Artie",    45000,  1},
  {"117001", "DiBergi",    "Marty",    15000,  7},
  {"118001", "Floyd",      "Pink",     25000,  6},
  {"119001", "Zeppelin",   "Led",      35000,  3},
  {"120001", "Mason",      "Nick",     15000,  7},
  {"121001", "Wright",     "Richard",  17000,  9},
  {"122001", "Waters",     "Roger",    10000,  3},
  {"123001", "Gilmore",    "David",    19000,  5}
};

Person **PersonRecs;

int UniqueID = 1;

void MakeRandomPerson(Person &person)
{
  //sprintf(person.ID, "%06i", RandomInt(0, 999999));
  sprintf(person.ID, "%06i", UniqueID++);
  strcpy(person.lastName, PEOPLE[RandomInt(0, 20)].lastName);
  strcpy(person.firstName, PEOPLE[RandomInt(0, 20)].firstName);
  person.salary = static_cast<float>(RandomInt(10, 500) * 1000);
  person.years = RandomInt(1, 30);
}

void FreePersonRecs()
{
  int count = static_cast<int>(sizeof(PEOPLE) / sizeof(*PEOPLE));

  for (int i = 0; i < count; i++)
    delete PersonRecs[i];

  delete[] PersonRecs;
}

void FillPersonRecs()
{
  int count = static_cast<int>(sizeof(PEOPLE) / sizeof(*PEOPLE));
  PersonRecs = (Person **) new Person[count];

  int index = 0;
  for (int i = 0; i < count; i++)
  {
    Person *person = new Person;
    std::strcpy(person->ID, PEOPLE[i].ID);
    std::strcpy(person->lastName, PEOPLE[i].lastName);
    std::strcpy(person->firstName, PEOPLE[i].firstName);
    person->salary = PEOPLE[i].salary;
    person->years = PEOPLE[i].years;
    PersonRecs[index++] = person;
  }
}

std::ostream& operator<<(std::ostream &os, const Person &person)
{
  char buffer[200];
  std::sprintf(buffer, "Key: %8s, Name: %12s, %12s    Salary:%7.0f, Years: %2d", 
                  person.ID, person.lastName, person.firstName, person.salary, 
                  person.years);
  os << buffer;
  return os;
}

bool operator==(const Person &lhs, const Person &rhs)
{
  if ( (!strcmp(lhs.lastName, rhs.lastName)) &&
       (!strcmp(lhs.firstName, rhs.firstName)) &&
       (!strcmp(lhs.ID, rhs.ID)) &&
       (lhs.salary == rhs.salary) &&
       (lhs.years == rhs.years)
    )
    return true;

  return false;
}

template <typename T>
void TestPush(void)
{
  std::cout << "\n********** TestPush **********\n";
  CS170::Vector<T> a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(PEOPLE[i]);
    Print(a);
  }

  std::cout << "push_front 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(PEOPLE[i]);
    Print(a);
  }

  std::cout << "pop_front until empty:\n";
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

  std::cout << "push_back 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(PEOPLE[i]);
    Print(a);
  }

  std::cout << "push_front 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_front(PEOPLE[i]);
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

  std::cout << "push_back 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(PEOPLE[i]);
    Print(a);
  }

  std::cout << "remove(0), remove(3):\n";
  a.remove(PEOPLE[0]);
  a.remove(PEOPLE[3]);
  Print(a);
}

template <typename T>
void TestInsert1(void)
{
  std::cout << "\n********** TestInsert1 **********\n";
  CS170::Vector<T> a;
  std::cout << "Empty array:\n";
  Print(a);

  std::cout << "push_back 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(PEOPLE[i]);
    Print(a);
  }

  std::cout << "insert(PEOPLE[8], 3):\n";
  a.insert(PEOPLE[8], 3);
  Print(a);
  std::cout << "insert(PEOPLE[9], 0):\n";
  a.insert(PEOPLE[9], 0);
  Print(a);
  std::cout << "insert(PEOPLE[10], 6):\n";
  a.insert(PEOPLE[10], 6);
  Print(a);
}

template <typename T>
void TestSubscripts(void)
{
  std::cout << "\n********** TestSubscripts **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back 10 Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i]);

  Print(a);

  std::cout << "replace each Person:\n";
  for (unsigned i = 0; i < 10; i++)
    a[i] = a[10 - i - 1];
  Print(a);
}

template <typename T>
void TestArray(void)
{
  std::cout << "\n********** TestArray **********\n";
  Person array[] = {{"101001", "Faith",      "Ian",      80000, 10},
                    {"102001", "Tufnel",     "Nigel",    90000, 12},
                    {"103001", "Savage",     "Viv",      50000,  4},
                    {"104001", "Shrimpton",  "Mick",     50000,  4},
                    {"105001", "Besser",     "Joe",      40000,  1},
                    {"106001", "Smalls",     "Derek",    80000, 10},
                    {"107001", "St.Hubbins", "David",    90000, 12},
                    {"108001", "Fleckman",   "Bobbi",   120000,  8},
                    {"109001", "Eton-Hogg",  "Denis",   250000, 22},
                    {"110001", "Upham",      "Danny",    60000,  5}
                   };

  int size = static_cast<int>(sizeof(array) / sizeof(*array));
  std::cout << "Construct from Person array:\n";
  CS170::Vector<T> a(array, size);
  Print(a);
}

template <typename T>
void TestSubscript1(void)
{
  std::cout << "\n********** TestSubscript1 **********\n";
  Person array[] = {{"101001", "Faith",      "Ian",      80000, 10},
                    {"102001", "Tufnel",     "Nigel",    90000, 12},
                    {"103001", "Savage",     "Viv",      50000,  4},
                    {"104001", "Shrimpton",  "Mick",     50000,  4},
                    {"105001", "Besser",     "Joe",      40000,  1},
                    {"106001", "Smalls",     "Derek",    80000, 10},
                    {"107001", "St.Hubbins", "David",    90000, 12},
                    {"108001", "Fleckman",   "Bobbi",   120000,  8},
                    {"109001", "Eton-Hogg",  "Denis",   250000, 22},
                    {"110001", "Upham",      "Danny",    60000,  5}
                   };

  int size = static_cast<int>(sizeof(array) / sizeof(*array));
  std::cout << "Construct from Person array:\n";
  const CS170::Vector<T> a(array, size);
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

  std::cout << "push_back 10 Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i]);
  Print(a);

  std::cout << "clear:\n";
  a.clear();
  Print(a);

  std::cout << "push_back 10 more Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i + 10]);
  Print(a);

  std::cout << "empty/fill with 10 Persons 3 times:\n";
  for (int i = 0; i < 3; i++)
  {
    while (!a.empty())
      a.pop_back();

    for (int j = 0; j < 10; j++)
      a.push_back(PEOPLE[j]);
  }
  Print(a);

  std::cout << "remove all but 3 Persons:\n";
  while (a.size() > 3)
    a.pop_back();
  Print(a);

  std::cout << "shrink:\n";
  a.shrink_to_fit();
  Print(a);

  std::cout << "push_back 10 more Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i]);
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

  std::cout << "push_back 10 Person:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i]);

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

  std::cout << "push_back 10 Persons:\n";
  for (int i = 0; i < 10; i++)
  {
    a.push_back(PEOPLE[10 + i]);
    b.push_back(PEOPLE[i]);
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

  std::cout << "push_back 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(PEOPLE[i]);
  }
  Print(a);

  std::cout << "push_front 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    b.push_front(PEOPLE[10 + i]);
  }
  Print(b);

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

  std::cout << "push_back 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    a.push_back(PEOPLE[i]);
  }
  Print(a);
  std::cout << "push_front 5 Persons:\n";
  for (int i = 0; i < 5; i++)
  {
    b.push_front(PEOPLE[10 + i]);
  }
  Print(b);

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
  const int count = 10;
  std::cout << "\n********** TestSelectionSort1 **********\n";

  CS170::Vector<T> a;

  int ia[count];
  for (int i = 0; i < count; i++)
    ia[i] = i;

  Shuffle(ia, count);
  std::cout << "push_back 10 random Persons:\n";
  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[ia[i]]);

  Print(a);
  typename CS170::Vector<T>::SortResult results = a.selection_sort();

  if (SHOW_COMPARES)
  {
    std::cout << "Sorted: compares = " << results.compares;
    std::cout << ", swaps = " << results.swaps << std::endl;
  }

  if (SortBy == sbkName)
    std::cout << "Sorting on Name:\n";
  else if (SortBy == sbkSalary)
    std::cout << "Sorting on salary:\n";
  else if (SortBy == sbkYears)
    std::cout << "Sorting on years:\n";
  else 
    std::cout << "Sorting on ID:\n";

  Print(a);
}

template <typename T>
void TestSelectionSortA(void)
{
  SortBy = sbkID;
  TestSelectionSort1<T>();
  SortBy = sbkSalary;
  TestSelectionSort1<T>();
  SortBy = sbkYears;
  TestSelectionSort1<T>();
  SortBy = sbkName;
  TestSelectionSort1<T>();
}

template <typename T>
void TestSelectionSort2(void)
{
  SortBy = sbkName;
  int count = 10;
  std::cout << "\n********** TestSelectionSort2 **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back " << count << " Persons:\n";
  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[i]);

  Print(a);
  typename CS170::Vector<T>::SortResult results = a.selection_sort();
  if (SHOW_COMPARES)
  {
    std::cout << "Sorted: compares = " << results.compares;
    std::cout << ", swaps = " << results.swaps << std::endl;
  }
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " Persons:\n";
  for (int i = count; i > 0; i--)
    a.push_back(PEOPLE[i]);

  Print(a);
  results = a.selection_sort();
  if (SHOW_COMPARES)
  {
    std::cout << "Sorted: compares = " << results.compares;
    std::cout << ", swaps = " << results.swaps << std::endl;
  }
  Print(a);

  a.clear();
  std::cout << "push_back " << count << " Persons:\n";
  for (int i = count; i > 0; i--)
    a.push_back(PEOPLE[5]);

  Print(a);
  results = a.selection_sort();
  if (SHOW_COMPARES)
  {
    std::cout << "Sorted: compares = " << results.compares;
    std::cout << ", swaps = " << results.swaps << std::endl;
  }
  Print(a);
}

template <typename T>
void TestSelectionSortStress(void)
{
  int count = 10000;
  std::cout << "\n********** TestSelectionSortStress **********\n";
  CS170::Vector<T> a;

  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[RandomInt(1, 20)]);

  //Print(a);

  typename CS170::Vector<T>::SortResult results = a.selection_sort();

  if (SHOW_COMPARES)
  {
    std::cout << "Sorted: compares = " << results.compares;
    std::cout << ", swaps = " << results.swaps << std::endl;
  }
  for (unsigned i = 1; i < static_cast<unsigned>(count); i += count / 20)
    std::cout << a[i] << std::endl;
  std::cout << std::endl;
  //Print(a);
}

template <typename T>
void TestBSearch1(void)
{
  const int count = 10;
  std::cout << "\n********** TestBSearch1 **********\n";
  CS170::Vector<T> a, b;

  int ia[count];
  for (int i = 0; i < count; i++)
    ia[i] = i;

  Shuffle(ia, count);

  std::cout << "push_back 10 random Persons:\n";
  for (unsigned i = 0; i < static_cast<unsigned>(count); i++)
  {
    a.push_back(PEOPLE[ia[i]]);
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

  std::cout << "Generating...\n";
  Person p;
  for (int i = 0; i < count; i++)
  {
    MakeRandomPerson(p);
    a.push_back(p);
  }

  SortBy = sbkID;
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
      #if 0
        int index = a.bsearch(a[j]);
        std::cout << "Index of " << a[j] << " is " << index << std::endl;
      #else 
        if (a.bsearch(a[j]) == -1) // should never happen
          std::cout << "Can't find item at index " << j << std::endl;
      #endif
    }
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
void TestReverse1(void)
{
  int count = 10;
  std::cout << "\n********** TestReverse1 **********\n";
  CS170::Vector<T> a;

  std::cout << "push_back Persons:\n";
  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[i + 1]);

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

  std::cout << "push_back Persons:\n";
  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[i + 1]);

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

  std::cout << "push_back Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i + 1]);
  for (int i = 0; i < 5; i++)
    b.push_back(PEOPLE[10 + (i + 1)]);

  std::cout << "a:\n";
  Print(a);
  std::cout << "b:\n";
  Print(b);

  std::cout << "swapv a,b:\n";
  a.swapv(b);
  std::cout << "a:\n";
  Print(a);
  std::cout << "b:\n";
  Print(b);

  std::cout << "swapv a,c:\n";
  a.swapv(c);
  std::cout << "a:\n";
  Print(a);
  std::cout << "c:\n";
  Print(c);

  std::cout << "swapv b,b:\n";
  b.swapv(b);
  std::cout << "b:\n";
  Print(b);
}

template <typename T>
void TestSwapStress(void)
{
  std::cout << "\n********** TestSwapStress **********\n";
  CS170::Vector<T> a, b, c;

  int count = 1000000;

  std::cout << "Pushing back...\n";
  Person p;
  for (int i = 0; i < count; i++)
  {
    MakeRandomPerson(p);
    a.push_back(p);
    MakeRandomPerson(p);
    b.push_back(p);
    MakeRandomPerson(p);
    c.push_back(p);
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

  int count = 1000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[RandomInt(0, 20)]);

  std::cout << "Assigning...\n";
#ifdef SHOW_TIMES
  std::time_t start = std::clock();
#endif
  for (int i = 0; i < 20; i++)
  {
    CS170::Vector<T> x;
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

  int count = 1000000;

  std::cout << "Pushing back...\n";
  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[RandomInt(0, 20)]);

  std::cout << "Assigning...\n";
  CS170::Vector<T> x;
#ifdef SHOW_TIMES
  std::time_t start = std::clock();
#endif
  for (int i = 0; i < 10; i++)
  {
    x = a;
    a.push_back(PEOPLE[0]);
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

  std::cout << "push_back Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i + 1]);
  for (int i = 0; i < 10; i++)
    b.push_back(PEOPLE[i + 1]);

  std::cout << "a:\n";
  Print(a);
  std::cout << "b:\n";
  Print(b);

  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of a:\n";
  a.pop_back();
  std::cout << "a:\n";
  Print(a);
  std::cout << "b:\n";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "remove last element of b:\n";
  b.pop_back();
  std::cout << "a:\n";
  Print(a);
  std::cout << "b:\n";
  Print(b);
  if (a == b)
    std::cout << "a is equal to b\n";
  else
    std::cout << "a is NOT equal to b\n";

  std::cout << "change last element of b:\n";
  b[b.size() - 1] = PEOPLE[20];
  std::cout << "a:\n";
  Print(a);
  std::cout << "b:\n";
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

  for (int i = 0; i < count; i++)
    a.push_back(PEOPLE[RandomInt(0, 20)]);

  std::cout << "Sum before: " << Sum(a) << std::endl;
  //Print(a);

  for (unsigned i = 0; i < a.size(); i++)
  {
    int from = RandomInt(0, static_cast<int>(a.size()) - 1);
    T value = a[static_cast<unsigned>(from)];
    a.remove(value);
    if ( (i % 3) == 0)
    {
      int to = RandomInt(0, static_cast<int>(a.size()) - 1);
      a.insert(value, static_cast<unsigned>(to));
    }
  }

  std::cout << " Sum after: " << Sum(a) << std::endl;
  //Print(a);

  for (unsigned i = 1; i < a.size(); i += count / 20)
    std::cout << a[i] << std::endl;
  std::cout << std::endl;
}

template <typename T>
void TestSubscriptEx(void)
{
  std::cout << "\n********** TestSubscriptEx **********\n";

  CS170::Vector<T> b;
  std::cout << "push_back Persons:\n";
  for (int i = 0; i < 10; i++)
    b.push_back(PEOPLE[i + 1]);

  std::cout << "make a copy:\n";
  const CS170::Vector<T> a(b);
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

  CS170::Vector<T> a;
  std::cout << "push_back Persons:\n";
  for (int i = 0; i < 10; i++)
    a.push_back(PEOPLE[i + 1]);

  Print(a);

  try
  {
    unsigned index = a.size() * 3; // illegal
    std::cout << "insert Person at index " << index << ":\n";
    a.insert(PEOPLE[20], index);
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

  std::cout << "push_back 8 Persons:\n";
  for (int i = 0; i < 8; i++)
    a.push_back(PEOPLE[i]);
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

  std::cout << "push_back one Person:\n";
  a.push_back(PEOPLE[20]);
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

  typedef Person T;
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
                    {"TestSelectionSortA",      TestSelectionSortA<T>,      maxwait, safewait}, // 13
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
