#include <stdio.h>      /* printf                                         */
#include "bytes.h"      /* exchange_bytes                                 */
#include "scantext.h"   /* count_tabs, calculate_lengths, substitute_char */
#include "spellcheck.h" /* mystrup                                        */

/* bytes */
static void test1(void)
{
  /*               0123456789.123456789.123456789.  */
  /*                         1         2            */
  char string[] = "Four score and seven years ago.";

  printf("\nTest1 ======================================\n");

  printf("BEFORE: %s\n", string);
  exchange_bytes(string + 5, string + 15, 5);
  printf(" AFTER: %s\n", string);
  exchange_bytes(string + 0, string + 27, 4);
  printf(" AFTER: %s\n", string);
  exchange_bytes(string + 7, string + 19, 9);
  printf(" AFTER: %s\n", string);
}

/* scantext */
static void test2(void)
{
  char string[] = "Four\nscore\tand\nseven\tyears";

  int count;
  int tabs;
  int tabsize;
  int char_count;
  int print_length;

  printf("\nTest2 ======================================\n");
  printf("|%s|\n", string);
  tabs = count_tabs(string);
  printf("Number of tabs is %i.\n", tabs);

  tabsize = 4;
  calculate_lengths(string, tabsize, &char_count, &print_length);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("With tab size of %i, the print length is %i.\n", tabsize, print_length);

  count = substitute_char(string, '\n', ' ');
  printf("Replacements made: %i. After replacing newlines with spaces:\n", count);
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("Number of tabs is %i\n", count_tabs(string));

  count = substitute_char(string, '\t', ' ');
  printf("Replacements made: %i. After replacing tabs with spaces:\n", count);
  printf("|%s|\n", string);
  printf("Number of characters in the string is %i.\n", char_count);
  printf("Number of tabs is %i\n", count_tabs(string));
}

/* spellcheck */
static void test3(void)
{
  char s[] = "This is a string";
  mystrupr(s);
  printf("\nTest3 ======================================\n");
  printf("%s\n", s);
}

int main(void)
{
  test1(); /* bytes test      */
  test2(); /* scantext test   */
  test3(); /* spellcheck test */
 
  return 0;
}

