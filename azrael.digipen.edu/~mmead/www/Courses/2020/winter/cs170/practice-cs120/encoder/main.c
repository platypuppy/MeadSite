#include <stdio.h>
#include <string.h>

enum ENCODE_MODE {ENCODE, DECODE};

void encode(FILE *infile, FILE *outfile);
void decode(FILE *infile, FILE *outfile);

/*****************************************************************************
       Name: main

Description: The front-end of the encoder/decoder. Accepts filenames from the
             command line, opens them for read/write, and checks for errors.

     Inputs: argc - The number of command line options.
             argv - The actual arguments. argv[1] is the input filename and
                    argv[2] is the name of the output file.

     Return: 0 on success or a positive value on error.
*****************************************************************************/
int main(int argc, char **argv)
{
  const char *infilename;  /* Name of the input file  */
  const char *outfilename; /* Name of the output file */
  FILE *infile;            /* The opened input file   */
  FILE *outfile;           /* The opened output file  */

  enum ENCODE_MODE mode = ENCODE; /* Assume encoding */

    /* Must get at least 2 additional command line args */
  if (argc < 3)
  {
    printf("Usage: encoder [-d] inputfile outputfile\n");
    printf("       -d will decode, default is encode\n");
    return 3; /* Failure */
  }

    /* Use descriptive names for the filenames */
  infilename = argv[1];
  outfilename = argv[2];

    /* If we get a -d, we will be decoding instead */
  if (!strcmp(argv[1], "-d"))
  {
    mode = DECODE;
    infilename = argv[2];
    outfilename = argv[3];    
  }

    /* Open input file and check for errors */
  infile = fopen(infilename, "rb");
  if (!infile)
  {
    printf("Can't open %s for read.\n", argv[1]);
    return 1; /* Failure */
  }

    /* Open output file and check for errors */
  outfile = fopen(outfilename, "wb");
  if (!outfile)
  {
    printf("Can't open %s for write.\n", argv[2]);
    fclose(infile);
    return 2; /* Failure */
  }

    /* Do the encoding/decoding (this calls the student's code) */
  if (mode == ENCODE)
    encode(infile, outfile);
  else
    decode(infile, outfile);

    /* Cleanup */
  fclose(infile);
  fclose(outfile);

  return 0; /* Success */
}
