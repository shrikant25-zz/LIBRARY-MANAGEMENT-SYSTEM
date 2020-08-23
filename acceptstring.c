#include <stdio.h>
#include <string.h>
#define max_size 21

void acceptstring(char *str)
{
 int ln = 0;
 fflush(stdin);                                       //flushesh the stream
 fgets(str,max_size,stdin);                           //fgets with input of max_size=21
  ln = strlen(str);                                   //storing the length of string ln variable
 if((ln>0) && (str[ln-1] == '\n'))                    //checks if last positions (before '\0' character) contains '\n'
  str[ln-1] = '\0';                                   //if present then replace '\n' with '\0'
}
