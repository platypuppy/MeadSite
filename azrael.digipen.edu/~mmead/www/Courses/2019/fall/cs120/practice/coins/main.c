#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi   */

void calculate_coins(int, int);

void usage(void)
{
  printf("Usage: coins <amount> <number_of_coins>\n\n");
  printf("where: 1 <= amount <= 2000\n");
  printf("       1 <= number_of_coins <= 40\n");
  exit(1);
}

int main(int argc, char **argv)
{
  int value, coins;

  if (argc < 3)
    usage();

    /* get/convert cmdline args */
  value = atoi(argv[1]);
  coins = atoi(argv[2]);

    /* Validate */
  if (value < 1 || value > 2000)
    usage();
  if (coins < 1 || coins > 40)
    usage();

  calculate_coins(value, coins);

  return 0;
}
