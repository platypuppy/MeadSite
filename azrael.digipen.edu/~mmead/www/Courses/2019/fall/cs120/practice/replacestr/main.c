#include <stdio.h> /* printf */
#include "replacestr.h"

void usage(void)
{
  printf("Usage:  replacestr filename oldstring newstring\n\n");
  printf("where:  filename is the file to search through\n");
  printf("        oldstring is the text to search for\n");
  printf("        newstring is the text to replace oldstring with\n");
  printf("\n");
  printf("Example: poem.txt are \"may be\"\n\n");
  printf("If either of the strings contain spaces,");
  printf(" it must be surrounded by quotes.\n");
}

int main(int argc, char **argv)
{
  enum FILE_ERR result; /* File errors */

    /* Must get 3 args on the command line */
  if (argc < 4)
  {
    usage();
    return 1;
  }

    /* replacestr(filename, oldstring, newstring) */
  result = replacestr(argv[1], argv[2], argv[3]);
  if (result == feINPUT)
    perror(argv[1]);

  return 0;
}
