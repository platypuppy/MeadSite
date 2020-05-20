#include <stdio.h>      /* printf              */
#include <stdlib.h>     /* malloc, free, exit  */
#include <string.h>     /* strncpy             */
#include "threadlist.h" /* threadlist stuff    */

/* This is the shared list (head of the list) */
static tl_node *gTList = NULL;

/* To enable/disable locks */
static bool USE_LOCKS = true;

/*!
********************************************************************************
  \brief 
    Locks the static mutex.

  \return 
    0 on success, non-zero on failure
*******************************************************************************/
int Lock(void)
{
}

/*!
********************************************************************************
  \brief 
    Unlocks the static mutex.

  \return 
    0 on success, non-zero on failure
*******************************************************************************/
int Unlock(void)
{
}

static tl_node *make_node(int value, const char *label)
{
  tl_node *node = (tl_node *)malloc(sizeof(tl_node));
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

void tl_dump(const tl_node *list)
{
  while (list)
  {
    printf("%6i: %s\n", list->value, list->label);
    list = list->next;
  }
}
