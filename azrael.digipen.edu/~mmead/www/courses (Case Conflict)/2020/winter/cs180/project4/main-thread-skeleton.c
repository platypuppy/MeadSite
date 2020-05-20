#include <stdio.h>         /* printf, fopen, fclose, fscanf */
#include <stdlib.h>        /* exit, malloc                  */
#include <pthread.h>       /* thread create/join/exit       */
#include "matrix-thread.h" /* thread data struct, thread fn */

int *get_matrix(const char *filename, int *width)
{
  int value, *matrix, result;
  FILE *fp;
  
  fp = fopen(filename, "rt");
  if (!fp)
  {
    printf("Can't open file: %s\n", filename);
    exit(-1);
  }
  
  result = fscanf(fp, "%d", width);
  if (result == -1)
  {
    printf("Can't read from file: %s\n", filename);
    fclose(fp);
    exit(-1);
  }

  matrix = malloc(*width * *width * sizeof(int));
  if (!matrix)
  {
    printf("Can't malloc matrix\n");
    fclose(fp);
    exit (-2);
  }
  
  while (!feof(fp))
  {
    result = fscanf(fp, "%d", &value);
    if (result == -1)
      break;
    *matrix++ = value;
  }
  fclose(fp);
  return matrix - (*width * *width);
}

void print_matrix(int *matrix, int width)
{
  int i, size = width * width;
  for (i = 0; i < size; i++)
  {
    printf("%8i", matrix[i]);
    if ( (i + 1) % width == 0)
      printf("\n");
  }
  printf("\n");
}

int main(int argc, char **argv) 
{
  int i;
  int width;          /* width of the matrix           */
  int matsize;        /* total matrix values           */
  int *input_matrix;  /* the matrix read in            */
  int *result_matrix; /* threads will put results here */
  
  if (argc < 2)
  {
    printf("Insufficient parameters supplied\n");
    return -1;
  }
  
    /* Reading the input matrix from a file into it's memory. */
  input_matrix = get_matrix(argv[1], &width);
  matsize = width * width;
  
    /* Printing the input matrix. */
  print_matrix(input_matrix, width);
  
    /* Creating all of the other threads and supplying them with */
    /* their parameters                                          */ 
  for (i = 0; i < matsize; i++)
  {
  }

    /* Waiting for all of the threads to finish. */
    
    /* Printing the resulting squared matrix. */
  print_matrix(result_matrix, width);
  
    /* Cleaning up any memory or resources the main thread created. */
  
  return 0;
}
