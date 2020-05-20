#include <stdio.h> /* printf */

void stripcom(const char *filename);

int main(int argc, char **argv)
{
    /* Must provide a filename on the command line */
  if (argc < 2)
  {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  stripcom(argv[1]);

  return 0;
}
