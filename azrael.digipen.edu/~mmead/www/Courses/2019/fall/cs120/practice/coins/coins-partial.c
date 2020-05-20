#include <stdio.h> /* printf */

void print_coins(int halves, int quarters, int dimes, int nickels, 
                 int pennies)
{
  int sum = halves * 50 + quarters * 25 + dimes * 10 + nickels * 5 
            + pennies;

  printf("You can make $%.2f with ", sum / 100.0);
  if (halves)
    printf("%i hal%s  ", halves, (halves > 1) ? "ves" : "f");
  if (quarters)
    printf("%i quarter%s  ", quarters, (quarters > 1) ? "s" : "");
  if (dimes)
    printf("%i dime%s  ", dimes, (dimes > 1) ? "s" : "");
  if (nickels)
    printf("%i nickel%s  ", nickels, (nickels > 1) ? "s" : "");
  if (pennies)
    printf("%i penn%s  ", pennies, (pennies > 1) ? "ies" : "y");
 
  printf("\n");
}

void calculate_coins(int value, int num_coins)
{
}
