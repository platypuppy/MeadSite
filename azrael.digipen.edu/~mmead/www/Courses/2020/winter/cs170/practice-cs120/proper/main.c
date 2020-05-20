#include <stdio.h> /* printf */

void proper(const char *filename);

int main(int argc, char **argv)
{
    /* Must get a filename on the command line */
  if (argc < 2)
  {
    printf("Usage: %s filename\n", argv[0]);
    return -1;
  }

  proper(argv[1]);
  
  return 0;
}
