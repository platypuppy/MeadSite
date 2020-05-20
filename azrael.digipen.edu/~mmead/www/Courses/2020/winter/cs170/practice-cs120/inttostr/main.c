#include <stdio.h>

/* Prototypes */
void inttostr(int number, char string[]);

void test1(void)
{
  char buffer[12];
  
  inttostr(1, buffer);
  printf("|%s|\n", buffer);

  inttostr(12, buffer);
  printf("|%s|\n", buffer);

  inttostr(123, buffer);
  printf("|%s|\n", buffer);

  inttostr(1234, buffer);
  printf("|%s|\n", buffer);

  inttostr(1234567890, buffer);
  printf("|%s|\n", buffer);

  inttostr(0, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1, buffer);
  printf("|%s|\n", buffer);

  inttostr(-12, buffer);
  printf("|%s|\n", buffer);

  inttostr(-123, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1234, buffer);
  printf("|%s|\n", buffer);

  inttostr(-1234567890, buffer);
  printf("|%s|\n", buffer);
}

int main(void)
{
  test1();  

  return 0;
}

