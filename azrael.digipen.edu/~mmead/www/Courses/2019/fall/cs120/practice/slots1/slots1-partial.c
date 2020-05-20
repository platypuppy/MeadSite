#include <stdio.h> /* printf     */
#include "PRNG.h"  /* PRNG stuff */

int main(void)
{
  /* Data declarations here */

    /* Seed the PRNG (Do not change this!) */
  ut_srand(5, 2);

    /* Print out the instructions */
  printf("You start with 100 points. Each play costs 10 points.\n");
  printf("There are 3 slots, each contains 5 different values.\n");
  printf("If you get 2 of the same, you win 15 points.\n");
  printf("If you get 3 of the same, you win 30 points.\n");
  printf("Here we go!\n\n");

  /* YOUR CODE HERE */

  return 0;
}
