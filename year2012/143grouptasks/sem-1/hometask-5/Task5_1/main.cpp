#include <stdio.h>
#include <string.h>

int const maximum = 1000;

int main()
{
	FILE *in;
	if (!(in = fopen("input.txt","r")))
	{
		return 0;
	}
	FILE *out = fopen("output.txt","w");
	while (! feof(in))
	{
		char s[maximum] = {};
		fgets(s, maximum, in);
		int space = -1;
		int i = 0;
		while (i < (strlen(s)))
		{
			if (s[i] == ' ')
			{
				space = i;
				fputc(s[i], out);
			}
			else
			{
				int j = i - 1;
				bool isDouble = false;
				while (j > space)
				{
					isDouble = (s[i] == s[j]);
					if (isDouble)
					{
						break;
					}
					else
					{
						j--;
					}
				}
				if (! isDouble)
				{
					fputc(s[i], out);
				}
			}
			i++;
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}

