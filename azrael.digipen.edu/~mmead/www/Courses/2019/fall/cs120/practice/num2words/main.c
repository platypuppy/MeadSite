#include <stdio.h> /* printf, scanf, getchar */

void number_to_words(int number);

void myflush(void)
{
  while (getchar() != '\n')
    ;
}

int main(void)
{
  do
  {
    int number;

    printf("Enter a two-digit integer (10-99)? (0=quit) ");
    scanf("%d", &number);
    if (number < 10 || number > 99)
      break;

    number_to_words(number);

    myflush();
  } while (1);

  return 0;
}