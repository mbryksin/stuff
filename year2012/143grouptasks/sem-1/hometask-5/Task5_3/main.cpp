#include <stdio.h>
#include <string.h>

enum Comment {isText, isSlash, isComment, isUltraComment, isString};

int const maximum = 1000;

int main()
{
	if (fopen("input.txt","r"))
	{
	FILE *in = fopen("input.txt","r");
	FILE *out = fopen("output.txt","w");
	char *s = new char [maximum];
	Comment marker = isText;
	while (! feof(in))
	{
		fgets(s, maximum, in);
		char comment [maximum] = {};
		int j = 0;
		int i = 0;
		while (i < strlen(s))
		{
			switch (marker)
			{
				case isText:
					if (s[i] == '/')
					{
						marker = isSlash;
					}
					else if (s[i] == '"')
					{
						marker = isString;
					}
				break;
				case isSlash:
					if (s[i] == '/')
					{
						marker = isComment;
						comment[0] = '/';
						comment[1] = '/';
						j = 2;
					}
					else if (s[i] == '*')
					{
						marker = isUltraComment;
					}
					else
					{
						int h = i + 1;
						if (s[h] != '/' && s[h] != '*')
						{
							marker = isText;
						}
					}
				break;
				case isUltraComment:
					if (s[i] == '*')
					{
						int h = i + 1;
						if (s[h] == '/')
						{
							marker = isText;
							i += 2;
						}
					}
				break;
				case isString:
					if (s[i] == '"')
					{
						marker = isText;
					}
				break;
				case isComment:
					comment[j++] = s[i];
				break;
			}
			i++;
		}
		if (j > 0)
		{
			fprintf(out, "Comment: %s", comment);
			marker = isText;
		}
	}
	delete s;
	fclose(in);
	fclose(out);
	}
	return 0;
}

