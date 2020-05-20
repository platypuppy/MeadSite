#include <stdio.h>

void setcolors(int foreground, int background, int attribute)
{
  printf("\033[%i;%i;%im", attribute, foreground, background);  
}

void resetcolors(void)
{
  printf("\033[0m");  
}

void showcolors(void)
{
  int attributes[] = {0, 1, 4, 5, 7, 8};
  int fgcolors[]   = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96};
  int bgcolors[]   = {40, 41, 42, 43, 44, 45, 46, 47, 100, 101, 102, 103, 104, 105, 106};

  int attrsize = sizeof(attributes) / sizeof(*attributes);
  int fgsize = sizeof(fgcolors) / sizeof(*fgcolors);
  int bgsize = sizeof(bgcolors) / sizeof(*bgcolors);

  int attr, fore, back;

  for (attr = 0; attr < attrsize; attr++)
  {
    for (fore = 0; fore < fgsize; fore++)
    {
      for (back = 0; back < bgsize; back++)
      {
        setcolors(fgcolors[fore], bgcolors[back], attributes[attr]);
        printf("%i;%i;%i", attributes[attr], fgcolors[fore], bgcolors[back]);
        resetcolors();
        printf(" ");
      }
      printf("\n");
    }
    printf("\n");
  }
}
