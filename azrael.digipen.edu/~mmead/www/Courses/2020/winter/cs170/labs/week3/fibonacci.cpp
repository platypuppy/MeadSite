#include <iostream> // cout
#include <iomanip>  // 

void fibonacci(int max)
{
  std::cout << "           Fibonacci        Fibonacci" << std::endl;
  std::cout << " N           number          quotient" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << " 0             0                  N/A" << std::endl;
  std::cout << " 1             1                  N/A" << std::endl;

  int count = max;
  int fib1 = 0, fib2 = 1;
  for (int i = 2; i <= count; i++)
  {
    int next = fib1 + fib2;
    
    // Add statements to print here...

    fib1 = fib2;
    fib2 = next;
  }
}
