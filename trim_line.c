#include <ctype.h>
#include <stddef.h>

/**
* trim_line - clean the whitespaces and tabs in blank lines
* @str: string to clean
*
* Return: a pointer to the cleaned string
*/
char *trim_line(char *str)
{
	char *end;

	if (str == NULL)
		return (NULL);

	while (*str && (*str == ' ' || *str == '\t'))
		str++;

	if (*str == 0)
		return (str);

	end = str;

	while (*end)
		end++;
	end--;

	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	end[1] = '\0';

	return (str);
}
