#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{

  char str[] ="12.25 lol 13 14";
  char *pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok(str," ");
  while (pch != NULL)
  {
      printf ("pch = %s\n",pch);
      int x = atoi(pch);
      printf("x = %d\n", x);
      pch = strtok (NULL, " ,.-");
  }
  return 0;
}
