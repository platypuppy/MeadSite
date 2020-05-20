/*******************************************************************************
  FILE HEADER TO BE ADDED BY THE STUDENT
*******************************************************************************/

/*******************************************************************************
  FUNCTION HEADER TO BE ADDED BY THE STUDENT
*******************************************************************************/
static int mystrlen(const char *string)
{
  int length = 0;  /* The number of characters in the string */
  
    /* Count the characters (not including the NUL) */
  while (*string++)
    length++;

  return length;
}
