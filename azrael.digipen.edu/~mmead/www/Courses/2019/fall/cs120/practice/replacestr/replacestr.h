/* Max length of a line */
#define LINE_MAX 2048

/* Possible file errors */
enum FILE_ERR {feNONE, feINPUT};
enum FILE_ERR replacestr(const char *filename, 
                         const char *oldstr, 
                         const char *newstr);
