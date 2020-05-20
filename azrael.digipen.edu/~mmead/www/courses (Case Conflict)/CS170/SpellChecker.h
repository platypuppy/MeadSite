void *create_spellchecker(const char *dictionary);
void destroy_spellchecker(void *checker);
int spellcheck(void *checker, const char *word);
