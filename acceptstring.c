#include <stdio.h>
#include <string.h>
#define max_size 21

void acceptstring(char *str)
{
 int ln = 0;
 fflush(stdin);
 fgets(str,max_size,stdin);
  ln = strlen(str);
 if((ln>0) && (str[ln-1] == '\n'))
  str[ln-1] = '\0';
}
