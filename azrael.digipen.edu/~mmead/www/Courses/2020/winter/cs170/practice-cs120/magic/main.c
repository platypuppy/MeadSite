#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi   */

/* Prototype */
int magic_square(int size, int showall);

int main(int argc, char **argv)
{
  int size = 5;    /* Default size of the square */
  int showall = 0; /* Show every square?         */
  int magic_sum;   /* The "Magic Sum" returned   */

    /* First arg is the size */
  if (argc > 1)
    size = atoi(argv[1]);

    /* Second arg determines which boards to show */
  if (argc > 2)
    showall = atoi(argv[2]);

    /* Size must be positive and odd */
  if (size < 1 || !(size % 2))
  {
    printf("Size must be an odd integer.\n");
    return 1;
  }

  printf("Size: %i\n", size);
  magic_sum = magic_square(size, showall);
  printf("The magic sum is %i\n", magic_sum);

  return 0;
}
