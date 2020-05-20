#include <time.h>   /* time     */
#include <stdlib.h> /* atoi     */
#include "PRNG.h"   /* ut_srand */

void random_walk(int showall);

void test1(int showall, int count)
{
  int i;

  count = -count;

  for (i = 0; i < count; i++)
  {
    random_walk(showall);
  }

}

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

  if (seed < 0)
  {
    ut_srand(1, 1); 
    test1(show, seed);
  }
  else
  {
    return 0;
    ut_srand(seed, seed); /* Seed the PRNG */
    random_walk(show);    /* Do the walk   */
  }

  return 0;
}
