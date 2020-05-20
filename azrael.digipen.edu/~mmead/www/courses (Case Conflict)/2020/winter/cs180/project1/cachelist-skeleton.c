#include <stdio.h>     /* printf          */
#include <stdlib.h>    /* malloc, exit    */
#include <string.h>    /* strncpy         */
#include "cachelist.h" /* cachelist stuff */

static cl_node *make_node(int value, const char *label)
{
  cl_node *node = (cl_node *)malloc(sizeof(cl_node));
  if (!node)
  {
    printf("Can't allocate new node.\n");
    exit(1);
  }

  node->value = value;
  node->next = NULL;

    /* Be sure not to overwrite memory */
  strncpy(node->label, label, LABEL_SIZE - 1);
  node->label[LABEL_SIZE - 1] = 0;
  
  return node;
}

void cl_dump(const cl_node *list)
{
  printf("==================\n");
  while (list)
  {
    printf("%4i: %s\n", list->value, list->label);
    list = list->next;    
  }
}
