#include <iostream>
#include <string.h>

using namespace std;

void qSort(char *s, int const left, int const right)
{
	int l = left;
	int r = right;
	char m = s[(l + r) / 2];
	while (l <= r)
	{
		while (s[l] < m)
		{
			l++;
		}
		while (s[r] > m)
		{
			r--;
		}
		if (l <= r)
		{
			char rotate = s[l];
			s[l] = s[r];
			s[r] = rotate;
			l++;
			r--;
		}
	}
	if (left < r)
	{
		qSort(s, left, r);
	}
	if (l < right)
	{
		qSort(s, l, right);
	}
}

int const maximum = 1000;

int main()
{
	/*strings*/
	char s1[maximum] = {};
	cout << "Write first string:\n";
	cin.getline(s1, maximum);
	char s2[maximum] = {};
	cout << "Write second string:"<< endl;
	cin.getline(s2, maximum);
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	qSort(s1, 0, len1);
	qSort(s2, 0, len2);
	if (len2 > len1)
	{
		cout << "false\n";
	}
	else
	{
		int j = 0;
		int i;
		for (i = 0; (i < len1) && (j < len2); i++)
		{
			if (s1[i] == s2[j])
			{
				j++;
			}
		}
		if (j < len2)
		{
			cout << "false\n";
		}
		else
		{
			cout << "true\n";
		}
	}
	return 0;
}

