#include <stdio.h>  /* printf, fopen, fgets, feof, fclose, FILE */
#include <stdlib.h> /* exit                                     */

/* Longest line in the file */
#define BUFFER_SIZE 1000
double average_word_length(const char *text);

static void print(const char *text, double average)
{
  printf("%s\n", text);
  printf("Average word length: %.2f\n", average);
  printf("--------------------------\n");
}

void test(const char *text)
{
  double average = average_word_length(text);
  print(text, average);
}

void test1(void)
{
  test("This is a simple test.");
  test("one one one one one one");
  test("abcdefghijkl");
  test("ab c de f gh i jk l");
  test("a b c d e f g h i j k l");
  test("   This is   \tanother   \t\t test.   ");
  test("");
  test("     ");
}

void test2(void)
{
  const char *filename = "quotes.txt"; /* File containing the strings */
  char buffer[BUFFER_SIZE];            /* Max length of a string      */
  double average;                      /* Average word length         */

    /* Open the file, abort if unsuccessful */
  FILE *fp = fopen(filename, "rt");
  if (!fp)
  {
    printf("Can't open %s for read. Aborting.\n", filename);
    exit(1);
  }

    /* Read all the lines, one-at-a-time */
  while (!feof(fp))
  {
      /* If we got a line, calculate average word length and print */
    if (fgets(buffer, BUFFER_SIZE, fp))
    {
      average = average_word_length(buffer);
      print(buffer, average);
    } 
  }

    /* Close the file */
  fclose(fp);
}

int main(void)
{
  test1(); /* Work with these simple tests first    */
  /*test2();*/ /* Do these tests after the simple tests */

  return 0;
}
