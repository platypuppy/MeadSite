#include <stdio.h>

#define TRUE  1
#define FALSE 0

int is_leapyear(int year)
{
  return 0;
}

int day_of_the_week(int day, int month, int year)
{
  int month_keys[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
  int year_keys[] = {4, 2, 0, 6};

  return 0;
}

void print_calendar(int month, int year)
{
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *months[] = {"January",   "February", "March",    "April", 
                    "May",       "June",     "July",     "August",
                    "September", "October",  "November", "December"};

    /* Print calendar header */
  printf("%s, %i\n", months[month - 1], year);
  printf("Su Mo Tu We Th Fr Sa\n");
  printf("---------------------\n");

}

