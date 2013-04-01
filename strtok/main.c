#include <stdio.h>
#include <string.h>
int main ()
{
    char str[80];
    int i;

    sscanf("привет 1 2 3 4 5", "%s%d", str, &i);
    printf("%s %d", str, i);

  char str[] ="12.25 13 14";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ");
  while (pch != NULL)
  {
      printf ("%s\n",pch);
      int x = sprintf(pch, "");
      pch = strtok (NULL, " ,.-");
  }
  return 0;
}
