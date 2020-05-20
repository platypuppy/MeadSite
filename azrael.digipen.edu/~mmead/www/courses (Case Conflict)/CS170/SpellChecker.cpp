#include "FileStrings.h"

extern "C" void *create_spellchecker(const char *dictionary)
{
  return new CS170::SpellChecker(dictionary);
}

extern "C" void destroy_spellchecker(void *checker)
{
  delete static_cast<CS170::SpellChecker*>(checker);
}

extern "C" int spellcheck(void *checker, const char *word)
{
  return static_cast<CS170::SpellChecker*>(checker)->SpellCheck(word);
}
