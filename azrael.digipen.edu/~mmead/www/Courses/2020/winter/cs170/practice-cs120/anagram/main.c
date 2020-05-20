#include <stdio.h>  /* printf */
#include <string.h> /* strlen */
#include <stdlib.h> /* atoi   */

int is_anagram(const char word1[], const char word2[], int size);

char *words[] = {"rat", "tar",
                 "trap", "part",
                 "baker", "break",
                 "eager", "agree",
                 "nicest", "insect",
                 "promise", "imposer",
                 "mattress", "smartest",
                 "present", "serpent",
                 "senator", "treason",
                 "weather", "wreathe",
                 "roasting", "organist",
                 "worried", "wordier",
                 "reversed", "reserved"
                };

int main(void)
{
  int i;
  int size = sizeof(words) / sizeof(*words);
  
  for (i = 1; i < size; i += 2)
  {
    int result;
    char *word1 = words[i - 1];
    char *word2 = words[i];

    /*printf("%s, %s\n", word1, word2);*/

    result = is_anagram(word1, word2, strlen(word1));
    if (result)
      printf("%s is an anagram of %s\n", word1, word2);
    else
      printf("%s is NOT an anagram of %s\n", word1, word2);
  }

  for (i = 1; i < size; i += 2)
  {
    int result;
    char *word1 = words[i - 1] + 1;
    char *word2 = words[i] + 1;

    result = is_anagram(word1, word2, strlen(word1));
    if (result)
      printf("%s is an anagram of %s\n", word1, word2);
    else
      printf("%s is NOT an anagram of %s\n", word1, word2);
  }

  return 0;
}
