#include <ctype.h>
#include <stddef.h>

/**
* clean_blank_line - clean the whitespaces ant tabs in blank lines
* @str: string to clean
*
* Return: a pointer to the cleaned string
*/
char *clean_blank_line(char *str)
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
