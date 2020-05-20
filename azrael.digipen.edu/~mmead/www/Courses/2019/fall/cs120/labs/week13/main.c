#include <stdio.h>  /* printf */
#include <string.h> /* strcpy */

struct GRADE
{
  int score;
  int max;
};

/* These are the functions you need to write */
double calculate_grade(const char *filename);
struct GRADE parse_line(const char *line);

/* Given a score out of 100, print the letter grade */
void print_grade(double score)
{
  if (score >= 93)
    printf("A");
  else if (score >= 90)
    printf("A-");
  else if (score >= 87)
    printf("B+");
  else if (score >= 83)
    printf("B");
  else if (score >= 80)
    printf("B-");
  else if (score >= 77)
    printf("C+");
  else if (score >= 73)
    printf("C");
  else if (score >= 70)
    printf("C-");
  else if (score >= 60)
    printf("D");
  else
    printf("F");
}

void test_parse(void)
{
  /* Lines are of the form: LAB02:100/100 and the tag is exactly 5 chars. */
  const char *lines[] = 
    {
      "LAB02:100/100",
      "LAB03:0/100",
      "LAB04:100/100",
      "LAB05:100/100",
      "LAB06:100/100",
      "LAB07:100/100",
      "LAB08:100/100",
      "LAB09:100/100",
      "LAB10:0/100",
      "LAB11:100/100",
      "LAB12:0/100",
      "LAB13:100/100",
      "PHW01:90/100",
      "PHW02:65/80",
      "PHW03:75/80",
      "PHW04:80/80",
      "PHW05:85/100",
      "PHW06:100/120",
      "MID00:60/79",
      "FIN00:87/100",
    };

  int size = sizeof(lines) / sizeof(*lines);
  int i;
  for (i = 0; i < size; i++)
  {
    char tag[14]; /* Max line length is 13 */
    struct GRADE grade = parse_line(lines[i]);
    strcpy(tag, lines[i]);
    tag[5] = '\0';
    printf("Tag: %s, Score: %i, Max: %i\n", tag, grade.score, grade.max);
  }
}

void test_calculate(int argc, char **argv)
{
  double total; /* The score out of 100 */

  if (argc < 2)
  {
    printf("Usage: grades textfile_with_grades\n");
    return;
  }

    /* Get the total score for the class */
  total = calculate_grade(argv[1]);

    /* Display the score and the letter grade */
  printf("Your final score in CS120 is %.2f ", total);
  printf("and your letter grade is: ");
  print_grade(total);
  printf(".\n");
}

int main(int argc, char **argv)
{
  if (argc < 2)
    test_parse();
  else
    test_calculate(argc, argv);

  return 0;
}
