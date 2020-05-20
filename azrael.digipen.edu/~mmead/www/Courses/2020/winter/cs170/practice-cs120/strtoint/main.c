#include <stdio.h>

/* Prototypes */
int strtoint(const char string[]);

void test1(void)
{
  printf("%i\n", strtoint("0"));
  printf("%i\n", strtoint("1"));
  printf("%i\n", strtoint("12"));
  printf("%i\n", strtoint("123"));
  printf("%i\n", strtoint("1234"));
  printf("%i\n", strtoint("1234567890"));
  printf("%i\n", strtoint("-0"));
  printf("%i\n", strtoint("-12"));
  printf("%i\n", strtoint("-123"));
  printf("%i\n", strtoint("-124"));
  printf("%i\n", strtoint("-1234567890"));
}

int main(void)
{
  test1();  

  return 0;
}

