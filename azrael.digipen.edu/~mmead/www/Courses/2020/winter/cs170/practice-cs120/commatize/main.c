/*
See this:
https://sourceforge.net/p/mingw-w64/wiki2/gnu%20printf/
*/

#include <stdio.h> /* printf */

/*-9,223,372,036,854,775,808*/
char *commatize(long long number);

int main(void)
{
  long long nums[] = {
                 0, 1, 12, 123, 1234, 12345, 123456, 1234567, 12345678,
                 123456789, 1234567890, 12345678901, 123456789012,
                 1234567890123, 12345678901234, 123456789012345,
                 1234567890123456, 12345678901234567, 123456789012345678,
                 1234567890123456789, 9223372036854775807,
                 -0, -1, -12, -123, -1234, -12345, -123456, -1234567, -12345678,
                 -123456789, -1234567890, -12345678901, -123456789012,
                 -1234567890123, -12345678901234, -123456789012345,
                 -1234567890123456, -12345678901234567, -123456789012345678,
                 -1234567890123456789, -9223372036854775807
                };

  int size = sizeof(nums) / sizeof(*nums);
  int i;

  for (i = 0; i < size; i++)
      /* Need this to print 64-bit ints on Windows with MinGW */
    #ifdef __MINGW64__
      __mingw_printf("%20lli|%26s|\n", nums[i], commatize(nums[i]));
    #else
      printf("%20lli|%26s|\n", nums[i], commatize(nums[i]));
    #endif

  return 0;
}
