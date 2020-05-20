#include <stdio.h>
#include "SpellChecker.h"

enum SCResult { scrFILE_OK = -10,       /* File was opened successfully */
                scrFILE_ERR_OPEN = -20, /* File was unable to be opened */
                scrWORD_OK = 10,        /* Word found in dictionary     */
                scrWORD_BAD = 20        /* Word not found in dictionary */ 
              };


int main(int argc, char **argv)
{
  const char *dictionary = "allwords.txt";
  void *spellchecker;
  const char *words[] = {"Four", "SCORE", "and", "sevn", "years", "ago", "ar",
                         "fawthers", "brought", "foarth", "on", "this", "contnent",
                         "a", "gnu", "nashun"
                        };

  int size = sizeof(words) / sizeof(*words);
  int i;

    /* Assume filename */
  if (argc > 1)
    dictionary = argv[1];

  spellchecker = create_spellchecker(dictionary);

  for (i = 0; i < size; i++)
  {
    int result = spellcheck(spellchecker, words[i]);
    if (result == scrWORD_OK)
      printf("%s is correct.\n", words[i]);
    else if (result == scrWORD_BAD)
      printf("%s is incorrect.\n", words[i]);
    else if (result == scrFILE_ERR_OPEN)
      printf("Couldn't open the file: %s.\n", dictionary);
    else
      printf("Shouldn't see this.\n");
  }

  destroy_spellchecker(spellchecker);

  return 0;
}
