#include <time.h>   /* time     */
#include <stdlib.h> /* atoi     */
#include "PRNG.h"   /* ut_srand */

void random_walk(int showall);

int main(int argc, char **argv)
{
  int show = 0;          /* Show all boards? */
  int seed = time(NULL); /* Make it random   */

    /* First arg is to show all boards or not */
  if (argc > 1)
    show = atoi(argv[1]);

    /* Second arg is the seed (for debugging) */
  if (argc > 2)
    seed = atoi(argv[2]);    

  ut_srand(seed, seed); /* Seed the PRNG */
  random_walk(show);    /* Do the walk   */

  return 0;
}
