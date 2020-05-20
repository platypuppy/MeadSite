#include <stdio.h>    /* printf, perror */
#include <string.h>   /* strcmp         */
#include "fileconv.h"

void usage(void)
{
  printf("Usage:  fileconv target input_file output_file\n");
  printf("\n");
  printf("where:  target is either win or unix (the resulting format)\n");
  printf("        input_file is the file to convert\n");
  printf("        output_file is the newly converted file\n");
  printf("\n");
  printf("Example: (Converts a Windows text file to a Unix text file)\n");
  printf("  fileconv unix file-with-CRLF.txt file-with-LF.txt\n");
}

int main(int argc, char **argv)
{
  enum FILE_ERR result; /* File failures */

    /* Make sure we get the required arguments */
  if (argc < 4)
  {
    usage();
    return 1;
  }

    /* Do the conversion, check for errors */
  if (!strcmp(argv[1], "unix"))
    result = win2unix(argv[2], argv[3]);
  else if (!strcmp(argv[1], "win"))
    result = unix2win(argv[2], argv[3]);
  else
  {
    printf("Unknown target: %s\n", argv[1]);
    usage();
    return 2;
  }

  if (result == feINPUT)
    perror(argv[2]);
  else if (result == feOUTPUT)
    perror(argv[3]);

  return 0;
}
