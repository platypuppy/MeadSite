#include <stdio.h> /* printf  */
#include <ctype.h> /* toupper */

int main(void)
{
  int sum = 0; /* The total value of the word */
  int letter;  /* Each character in the word  */

    /* Prompt the user for a word */
  printf("Enter a word: ");

    /* Read the first character */
  letter = getchar();

    /* While it's not the newline (end of the word) */
  while (letter != '\n')
  {

    /* Your code here */


      /* Read next character in the word */
    letter = getchar();
  }

  printf("Scrabble value is : %i\n", sum);

  return 0;
}
