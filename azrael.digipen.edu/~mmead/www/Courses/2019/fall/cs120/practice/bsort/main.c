#include <stdio.h> /* printf              */
#include "PRNG.h"  /* RandomInt, ut_srand */

void bsort(int array[], int size);

void Shuffle(int *array, int count)
{
  int i;
  for (i = 0; i < count; i += 1)
  {
    int r = RandomInt(0, count - 1);
    int temp = array[i];
    array[i] = array[r];
    array[r] = temp;
  }
}

void GetValues(int *array, int size)
{
  int i;

  ut_srand(1, 2);
  for (i = 0; i < size; i++)
    array[i] = i;

  Shuffle(array, size);
}


void print_array(int array[], int size)
{
  int i;

  for (i = 0; i < size; i++)
    printf("%i ", array[i]);

  printf("\n");
}

void test1(void)
{
  int array[] = {7, 4, 1, 3, 8, 6, 9, 5, 2};
  int size = sizeof(array) / sizeof(array[0]);

  printf("Original array:\n");
  print_array(array, size);

  bsort(array, size);

  printf("Sorted array:\n");
  print_array(array, size);
  printf("\n");
}

void test2(void)
{
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof(array) / sizeof(array[0]);

  printf("Original array:\n");
  print_array(array, size);

  bsort(array, size);

  printf("Sorted array:\n");
  print_array(array, size);
  printf("\n");
}

void test3(void)
{
  int array[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  int size = sizeof(array) / sizeof(array[0]);

  printf("Original array:\n");
  print_array(array, size);

  bsort(array, size);

  printf("Sorted array:\n");
  print_array(array, size);
  printf("\n");
}

void test4(void)
{
  int array[] = {6};
  int size = sizeof(array) / sizeof(array[0]);

  printf("Original array:\n");
  print_array(array, size);

  bsort(array, size);

  printf("Sorted array:\n");
  print_array(array, size);
  printf("\n");
}

void test5(void)
{
  #define SIZE0 100
  int array[SIZE0];
  GetValues(array, SIZE0);

  printf("Original array:\n");
  print_array(array, SIZE0);

  bsort(array, SIZE0);

  printf("Sorted array:\n");
  print_array(array, SIZE0);
  printf("\n");
}

void test6(void)
{
  #define SIZE1 1000
  int array[SIZE1];
  GetValues(array, SIZE1);

  printf("Original array:\n");
  print_array(array, SIZE1);

  bsort(array, SIZE1);

  printf("Sorted array:\n");
  print_array(array, SIZE1);
  printf("\n");
}

int main(void)
{
  test1();
  /*
  test2();
  test3();
  test4();
  test5();
  test6();
  */
  return 0;
}