/*******************************************************************************
*******************************************************************************/
#include <stdio.h>  /* printf         */
#include "jumble.h" /* jumble, DECODE */

int main(void)
{
    /* The encoded string */
  char original[] = "ÉÛÖ™ØÑÚÕ™ÂàĞŞ µÜÂŞŒÈŞÕåĞîÑŒÕèÆœŒÃŞÍÙÑ×ŞİÑ™µØÑÓŞÑŞÆ™ØÑåÔ¥´áÅŞÅĞîÔÛÏ ÕãÂçÏÑŒÌçĞçŒÂÛĞåàâÕœŒÃŞÍÙÑ×ŞİÑ";
    
  char phrase[sizeof(original)]; /* Need to make a copy between decodings */
  char password[6] = {0};        /* The password is 5 characters long     */

  printf("The encoded string:\n%s\n\n", original);

  /* 
  
  
    The rest of the code goes here... 


  */

  printf("The password is %s and the decoded string is:\n%s\n", password, phrase);

  return 0;
}
