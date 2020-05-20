#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Stack.h"
#include "PRNG.h"

#include <list>

void TestPush()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestPush..." << std::endl;

  int size = 10;
  CS170::Stack stack;
  for (int i = 1; i <= size; i++)
    stack.push(i);

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;
}

void TestPushPop()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestPushPop..." << std::endl;

  int size = 10;
  CS170::Stack stack;
  for (int i = 1; i <= size; i++)
    stack.push(i);

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;

  std::cout << "Popping all items..." << std::endl;
  for (int i = 1; i <= size; i++)
    stack.pop();

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;

  std::cout << std::endl;
}

void TestPushPopEmpty()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestPushPopEmpty..." << std::endl;

  int size = 10;
  CS170::Stack stack;
  for (int i = 1; i <= size; i++)
    stack.push(i);

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;

  std::cout << "Popping all items..." << std::endl;
  while (!stack.empty())
    stack.pop();

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;

  std::cout << std::endl;
}

void TestPushTopPop()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestPushTopPop..." << std::endl;

  int size = 10;
  CS170::Stack stack;
  for (int i = 1; i <= size; i++)
    stack.push(i);

  std::cout << "Items in the stack: " << stack.size() << std::endl;

  for (int i = 1; i <= size; i++)
  {
    int value = stack.top();
    std::cout << "Pop: " << std::setw(2) << value << " (size: " 
              << std::setw(2) << stack.size() << ") ";
    stack.pop();
    stack.print(false);
  }

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;

  std::cout << std::endl;
}

void TestSwap1()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestSwap1..." << std::endl;

  int size = 10;
  CS170::Stack stack1, stack2;
  for (int i = 1; i <= size; i++)
  {
    stack1.push(i);
    stack2.push(i + 100);
  }

    // Remove the top 3
  stack1.pop();
  stack1.pop();
  stack1.pop();

  std::cout << "Items in stack1: (" << std::setw(2) << stack1.size() << ") ";
  stack1.print(false);
  std::cout << "Items in stack2: (" << std::setw(2) << stack2.size() << ") ";
  stack2.print(false);

  stack1.swap(stack2);
  std::cout << "Swapped stacks:" << std::endl;
  std::cout << "Items in stack1: (" << std::setw(2) << stack1.size() << ") ";
  stack1.print(false);
  std::cout << "Items in stack2: (" << std::setw(2) << stack2.size() << ") ";
  stack2.print(false);

  std::cout << std::endl;
}

void TestCopyConstructor1()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestCopyConstructor1..." << std::endl;

  int size = 10;
  CS170::Stack stack1;
  for (int i = 1; i <= size; i++)
    stack1.push(i);

  CS170::Stack stack2(stack1);

  std::cout << "Items in stack1: (" << std::setw(2) << stack1.size() << ") ";
  stack1.print(false);
  std::cout << "Items in stack2: (" << std::setw(2) << stack2.size() << ") ";
  stack2.print(false);

  std::cout << std::endl;
}

void TestAssignment1()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestAssignment1..." << std::endl;

  int size = 10;
  CS170::Stack stack1;
  for (int i = 1; i <= size; i++)
    stack1.push(i);

  CS170::Stack stack2;

  stack2 = stack1;

  std::cout << "Items in stack1: (" << std::setw(2) << stack1.size() << ") ";
  stack1.print(false);
  std::cout << "Items in stack2: (" << std::setw(2) << stack2.size() << ") ";
  stack2.print(false);

  stack1 = stack1;
  std::cout << "Items in stack1: (" << std::setw(2) << stack1.size() << ") ";
  stack1.print(false);

  std::cout << std::endl;
}


void TestAssignment2(void)
{
  std::cout << "TestAssignment2..." << std::endl;
  int size = 10;
  CS170::Stack stack1, stack2, stack3;
  for (int i = 1; i <= size; i++)
    stack1.push(i);

  std::cout << "Before assignment:" << std::endl;
  std::cout << "stack1: ";
  stack1.print(false);
  std::cout << "stack2: ";
  stack2.print(false);
  std::cout << "stack3: ";
  stack3.print(false);

  stack3 = stack2 = stack1;
  std::cout << "After assignment:" << std::endl;
  std::cout << "stack1: ";
  stack2.print(false);
  std::cout << "stack2: ";
  stack2.print(false);
  std::cout << "stack3: ";
  stack3.print(false);

  std::cout << std::endl;
}

void TestPushException()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestPushException..." << std::endl;

  int size = 10;
  CS170::Stack stack(5);
  for (int i = 1; i <= size; i++)
  {
    try 
    {
      stack.push(i);
    }
    catch (const CS170::StackError& se)
    {
      std::cout << "Exception thrown in TestPushException." << std::endl;
      std::cout << "Message: " << se.what() << std::endl;
    }
  }

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;
}

void TestPopException()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestPopException..." << std::endl;

  int size = 10;
  CS170::Stack stack(10);
  for (int i = 1; i <= size; i++)
  {
    try 
    {
      stack.push(i);
    }
    catch (const CS170::StackError& se)
    {
      std::cout << "Exception thrown in TestPushException." << std::endl;
      std::cout << "Message: " << se.what() << std::endl;
    }
  }

    // Should NOT throw
  while (!stack.empty())
  {
    try 
    {
      stack.pop();
    }
    catch (const CS170::StackError& se)
    {
      std::cout << "Exception thrown in TestPopException." << std::endl;
      std::cout << "Message: " << se.what() << std::endl;
    }
  }

    // Should throw
  try 
  {
    stack.pop();
  }
  catch (const CS170::StackError& se)
  {
    std::cout << "Exception thrown in TestPopException." << std::endl;
    std::cout << "Message: " << se.what() << std::endl;
  }

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;
}

void TestClear()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestClear..." << std::endl;

  int size = 10;
  CS170::Stack stack;
  for (int i = 1; i <= size; i++)
    stack.push(i);

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;

  std::cout << "Clearing the stack..." << std::endl;
  stack.clear();
  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;

  std::cout << "Push 5 more..." << std::endl;
  for (int i = 1; i <= 5; i++)
    stack.push(i);

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;
}

void TestArray()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestArray..." << std::endl;

  int array[] = {2, 4, 6, 8, 1, 3, 5, 7, 9};
  CS170::Stack stack(array, sizeof(array) / sizeof(*array));

  stack.print();
  std::cout << "Items in the stack: " << stack.size() << std::endl;
  std::cout << std::endl;
}

void TestALot()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestALot..." << std::endl;

  CS170::Stack stack1, stack2, stack3;
  for (int i = 1; i <= 10; i++)
  {
    stack1.push(CS170::Utils::Random(10, 99));
    stack2.push(CS170::Utils::Random(100, 999));
  }

  std::cout << "[" << stack1.size() << "] ";
  stack1.print(false);
  std::cout << "[" << stack2.size() << "] ";
  stack2.print(false);

  for (int i = 0; i <= 5; i++)
  {
    stack3.push(stack1.top());
    stack1.pop();
    stack2.push(stack1.top());
  }

  while (stack1.size() || stack2.size() || stack3.size())
  {
    try
    {
      if (!(CS170::Utils::Random(1, 10) % 3))
        stack1.push(100);
      else 
        stack1.pop();

      if (!(CS170::Utils::Random(1, 10) % 3))
        stack2.push(100);
      else 
        stack2.pop();

      if (!(CS170::Utils::Random(1, 10) % 3))
        stack3.push(100);
      else 
        stack3.pop();
    }
    catch (const CS170::StackError& se)
    {
      std::cout << se.what() << std::endl;
    }
    std::cout << "Items in stack1: (" << stack1.size() << ") ";
    stack1.print(false);
    std::cout << "Items in stack2: (" << stack2.size() << ") ";
    stack2.print(false);
    std::cout << "Items in stack3: (" << stack3.size() << ") ";
    stack3.print(false);
    std::cout << std::endl;
  }
}

void TestSwapStress()
{
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << "TestSwapStress..." << std::endl;

  int size = 1000000;
  int swaps = 100000;
  CS170::Stack stack1, stack2, stack3;

  std::cout << "Pushing " << size << " items..." << std::endl;
  for (int i = 0; i < size; i++)
  {
    stack1.push(i / 2);
    stack2.push(i);
    stack3.push(i * 2);
  }

  std::cout << "Swapping " << swaps << " times..." << std::endl;
  for (int i = 0; i < swaps; i++)
  {
    stack1.swap(stack2);
    stack2.swap(stack3);
    stack3.swap(stack1);
  }

  std::cout << "Popping all but 10 items..." << std::endl;
  for (int i = 0; i < size - 10; i++)
  {
    stack1.pop();
    stack2.pop();
    stack3.pop();
  }

  std::cout << "Items in stack1: (" << stack1.size() << ") ";
  stack1.print(false);
  std::cout << "Items in stack2: (" << stack2.size() << ") ";
  stack2.print(false);
  std::cout << "Items in stack3: (" << stack3.size() << ") ";
  stack3.print(false);
  std::cout << std::endl;
}


int main(int argc, char **argv)
{
#if 0
  std::list<int> st1;
  CS170::Stack st2;


  for (int i = 0; i < 3000000; i++)
    st1.push_front(i);

  return 0;
#endif

  typedef void (*TestFn)();
  struct Test
  {
    TestFn test;
    const char *name;
  };
  
  Test tests[] = {TestPush,             "TestPush",                //  1
                  TestPushPop,          "TestPushPop",             //  2
                  TestPushPopEmpty,     "TestPushPopEmpty",        //  3
                  TestPushTopPop,       "TestPushTopPop",          //  4
                  TestSwap1,            "TestSwap1",               //  5
                  TestCopyConstructor1, "TestCopyConstructor1",    //  6
                  TestAssignment1,      "TestAssignment1",         //  7
                  TestAssignment2,      "TestAssignment2",         //  8
                  TestPushException,    "TestPushException",       //  9
                  TestPopException,     "TestPopException",        // 10
                  TestClear,            "TestClear",               // 11
                  TestArray,            "TestArray",               // 12
                  TestALot,             "TestALot",                // 13
                  TestSwapStress,       "TestSwapStress",          // 14
                };

  int count = sizeof(tests) / sizeof(*tests);
  int testno = 0;
  int i;

  CS170::Utils::srand(3, 4);

  if (argc > 1)
    testno = std::atoi(argv[1]);

 if (testno > count || testno < 0)
   testno = 0;

  if (testno == 0)
  {
    for (i = 0; i < count; i++)
    {
      try {
        tests[i].test();
      }
      catch (...) {
        std::cout << "***" << tests[i].name 
                  << " revealed something bad in the Stack class" << std::endl;    
      }
    }
  }
  else
    tests[testno - 1].test();

  return 0;
}
