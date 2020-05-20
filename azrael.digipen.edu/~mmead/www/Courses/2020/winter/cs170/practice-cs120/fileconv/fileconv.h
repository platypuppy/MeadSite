#define CR 0x0D /* Carriage Return */
#define LF 0x0A /* Line Feed       */

/* Possible file errors */
enum FILE_ERR {feNONE, feINPUT, feOUTPUT};

enum FILE_ERR win2unix(const char *finput, const char *foutput);
enum FILE_ERR unix2win(const char *finput, const char *foutput);
