#include <stdio.h>  /* fopen, fgets, fclose */
#include <stdlib.h> /* atoi                 */
#include <string.h> /* strstr, strchr       */

/* Change these for each course */
#define LAB_WEIGHT      .15
#define HOMEWORK_WEIGHT .20
#define MIDTERM_WEIGHT  .20
#define FINAL_WEIGHT    .45
#define MAX_LABS        15
#define MAX_PHW         15

/* This will help you keep track of each lab, assignment, etc.  */
/* You should make an array of these for labs and assignments.  */
struct GRADE
{
  int score;
  int max;
};

/* 
 * Since all helper functions will need access to this data, I'm
 * going to make them available. You don't have to do it this way,
 * it's just a suggestion. If you'd rather pass all of the data
 * to all of the functions, you can. But, if you use these you
 * CANNOT remove the static keywords. If you don't use them, you
 * can just remove all of them from this file.
 */
static struct GRADE labz[MAX_LABS];    /* Handle up to MAX_LABS */
static struct GRADE homework[MAX_PHW]; /* Handle up to MAX_PHW  */
static struct GRADE midterm;
static struct GRADE final;

static struct GRADE lab_totals;
static struct GRADE homework_totals;

static int num_labs;
static int num_homeworks;

/* Helper functions here */


struct GRADE parse_line(const char *line)
{
  struct GRADE grade;

  /* More code here */

  return grade;
}

double calculate_grade(const char *filename)
{
  double total = 0.0;

  /* More code here */

  return total;
}
