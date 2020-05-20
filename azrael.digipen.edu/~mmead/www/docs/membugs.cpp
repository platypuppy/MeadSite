#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

void test0()
{
  // no op
}

void test1()
{
  new char[123];
}

void test2()
{
  char *p = new char[123];
  delete p;
}

void test3()
{
  char *p = new char;
  delete [] p;
}

void test4()
{
  char *p = (char *)malloc(123);
  delete p;
}

void test5()
{
  char *p = new char;
  free(p);
}

void test6()
{
  char *p = new char[5];
  std::strcpy(p, "abcde");
  delete [] p;
}

void test7()
{
  char *p = new char[5];
  std::strcpy(p - 5, "abcdefg");
  delete [] p;
}

void test8()
{
  char a[10];
  std::cout << a << std::endl;
}

void test9()
{
  char a[5];
  char buffer[100];

  if (!fgets(buffer, 50, stdin))
    return;
    
  strcpy(a, buffer);
}

int main(int argc, char **argv)
{
  int test = 1;
  if (argc > 1)
    test = std::atoi(argv[1]);

  void (*tests[])() = {test0, // nothing
                       test1, // leak
                       test2, // new[]/delete
                       test3, // new/delete[]
                       test4, // malloc/delete
                       test5, // new/free
                       test6, // buffer overflow (heap)
                       test7, // buffer underflow (heap)
                       test8, // uninitialized read
                       test9, // buffer overflow (stack)
                      };

  int size = sizeof(tests) / sizeof(*tests);
  if (test > size)
    test = 1;

  if (test > size || test < 0)
  {
    for (int i = 0; i < size - 1; i++)
      tests[i]();
  }
  else
    tests[test]();

  return 0;
}
