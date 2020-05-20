#include <stdio.h>      // printf, sprintf, fflush
#include <stdlib.h>     //  malloc, free, abort, atoi
#include <stdbool.h>    // true, false               
#include <pthread.h>    // thread create/join/exit
#include "threadlist.h" // threadlist stuff           
#include "PRNG.h"       // RandomInt, ut_srand       

typedef struct ThreadData
{
  int id;
  int array_size;
  int low;
  int high;
  int *data;
}ThreadData;

void SwapInt(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void Shuffle(int *array, int count)
{
  for (int i = 0; i < count; i++)
  {
    int r = RandomInt(0, count - 1);
    SwapInt(&array[i], &array[r]);
  }
}

void PrintArray(int *array, int count)
{
  for (int i = 0; i < count; i++)
    printf("%i  ", array[i]);
  printf("\n");
}

void* test_thread1(void *p)
{
  ThreadData *data = (ThreadData *)p;
  int size = data->high - data->low;
  char buffer[11]; // 11 is max digits in an int + NUL char
  sprintf(buffer, "%i", data->id);
  int offset = size * (data->id - 1);

#if 0
  for (int i = 0; i < size; i++)
  {
    printf("ID: %2i: %i\n", data->id, data->data[offset + i]);
  }
#endif
  tl_insert_values(data->data + offset, size, buffer);

  return NULL;
}

void* test_thread2(void *p)
{
  ThreadData *data = (ThreadData *)p;
  int size = data->high - data->low;
  int offset = size * (data->id - 1);

#if 0
  for (int i = 0; i < size; i++)
  {
    printf("ID: %2i: %i\n", data->id, data->data[offset + i]);
  }
#endif
  tl_remove_values(data->data + offset, size);

  return NULL;
}

int main(int argc, char **argv)
{
    // There are 5 required args
  if (argc < 6)
  {
    printf("Usage: threadlist TEST_NUM  THREAD_COUNT  ARRAY_SIZE  USE_LOCKS  REMOVE_THREAD_COUNT\n");
    printf("ARRAY_SIZE must be equally divisible by THREAD_COUNT (or it will be modified).\n");
    printf("REMOVE_THREAD_COUNT must be <= THREAD_COUNT (otherwise, undefined).\n\n");
    printf("ex: threadlist 1 8 32 1 4\n");
    return 1;
  }

  ut_srand(1, 2);

  int test_num = atoi(argv[1]);            // which test number to run
  int thread_count = atoi(argv[2]);        // number of threads to create (insert)
  int array_size = atoi(argv[3]);          // size of the data
  int locks = atoi(argv[4]);               // enable/disable locks
  int delete_thread_count = atoi(argv[5]); // how many threads will delete items

    /* 
       If the array size isn't evenly divisible by thread_count, we need
       to make it so. This just keeps things simpler.
    */
  int extra = array_size % thread_count;
  if (extra)
    array_size += thread_count - extra;

    // Thread IDs
  pthread_t *thread_ids = malloc(thread_count * sizeof(pthread_t));
  if (!thread_ids)
  {
    printf("Malloc:1 failed.\n");
    return 2;
  }

    // Thread data
  ThreadData *tdata = malloc(thread_count * sizeof(ThreadData));
  if (!tdata)
  {
    printf("Can't malloc tdata\n");
    free(thread_ids);
    return 2;
  }

    // Integer data
  int *intdata = malloc(array_size * sizeof(int));
  if (!intdata)
  {
    printf("Can't malloc intdata\n");
    free(thread_ids);
    free(tdata);
    return 3;
  }

    // Create data
  for (int i = 0; i < array_size; i++)
    intdata[i] = i + 1;

    // Mix it up
  Shuffle(intdata, array_size);

    // Make sure the list is set to NULL
  tl_resetlist();

    // Enable/disable locking (to see failures w/o locks)
  if (locks)
    tl_uselocks(true);
  else
    tl_uselocks(false);

  int count = 0;
  tl_node * const *list;                 // a pointer to the list in threadlist.c
  int slice = array_size / thread_count; // how many each thread gets

  switch (test_num)
  {
      //////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////
    case 1:
      #if 1
        // inserting w/multiple threads
      for (int i = 0; i < thread_count; ++i)
      {
        tdata[i].id = i + 1;
        tdata[i].array_size = array_size;
        tdata[i].low = count;
        tdata[i].high = count + slice;
        tdata[i].data = intdata;
        pthread_create(&thread_ids[i], NULL, test_thread1, &tdata[i]);
        count += slice;
      }

      for (int i = 0; i < thread_count; ++i)
      {
        pthread_join(thread_ids[i], NULL);
      }

      list = tl_getlist();
      tl_dump(*list);
      #endif

      #if 1
      printf("------------------\n");
      count = 0;

        //////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        // removing w/multiple threads
      for (int i = 0; i < delete_thread_count; ++i)
      {
        tdata[i].id = i + 1;
        tdata[i].array_size = array_size;
        tdata[i].low = count;
        tdata[i].high = count + slice;
        tdata[i].data = intdata;
        pthread_create(&thread_ids[i], NULL, test_thread2, &tdata[i]);
        count += slice;
      }

      for (int i = 0; i < delete_thread_count; ++i)
      {
        pthread_join(thread_ids[i], NULL);
      }

      if (delete_thread_count)
      {
        list = tl_getlist();
        tl_dump(*list);
        tl_destroy(*list);
      }
      #endif
      break;

    case 2:
      #if 1
      //printf("------------------\n");
      count = 0;

        //////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        // inserting/removing simultaneously w/multiple threads
      for (int i = 0; i < thread_count; ++i)
      {
        tdata[i].id = i + 1;
        tdata[i].array_size = array_size;
        tdata[i].low = count;
        tdata[i].high = count + slice;
        tdata[i].data = intdata;

        /*
          This is non-deterministic because, if a remove thread runs before an
          insert thread, the item to be removed may not exist in the list. This
          means the insert method will insert it, but it won't be removed. But,
          if the insert thread runs first, the remove method will actually have
          something to remove.
         */
        if (i % 2)
          pthread_create(&thread_ids[i], NULL, test_thread2, &tdata[i / 2]); // remove
        else
          pthread_create(&thread_ids[i], NULL, test_thread1, &tdata[i / 2]); // insert

        count += slice;
      }

      for (int i = 0; i < thread_count; ++i)
      {
        pthread_join(thread_ids[i], NULL);
      }

      list = tl_getlist();
      tl_dump(*list);
      tl_destroy(*list);
      #endif
      break;
  }

 
  free(thread_ids);
  free(tdata);
  free(intdata);

  return 0;

}
