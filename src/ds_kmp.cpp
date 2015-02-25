//http://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm
#include <stdlib.h>
#include <string.h>

int* ds_kmp_init(const char *str, int nLength)
{
	int *table = (int *)malloc((nLength + 2) * sizeof(int));
	table[0] = -1;
	table[1] = 0;
	
	int cnd = 0;
	for (int pos = 2; pos < nLength; )
	{
		if (str[pos - 1] == str[cnd])
		{
			++cnd;
			table[pos] = cnd;
			++pos;
		}
		else if (cnd > 0)
		{
			cnd = table[cnd];
		}
		else
		{
			table[pos] = 0;
			++pos;
		}
	}
	return table;
}

void ds_kmp_destroy(int *table)
{
	free(table);
}

int ds_kmp_search(const char *str, const char *substr, 
	int substrlength, const int *table)
{
	int cur_str = 0;
	int cur_substr = 0;
	int strlength = strlen(str);
	while (cur_str + cur_substr < strlength)
	{
		if (substr[cur_substr] == str[cur_str + cur_substr])
		{
			if (cur_substr == substrlength - 1)
			{
				return cur_str;
			}
			++cur_substr;
		}
		else
		{
			if (table[cur_substr] > -1)
			{
				cur_str += cur_substr - table[cur_substr];
				cur_substr = table[cur_substr];
			}
			else
			{
				cur_substr = 0;
				++cur_str;
			}
		}
	}
	
	return -1;
}