#include <ctype.h>
#include <stddef.h>
#include <string.h>

/**
* trim_line - clean the whitespaces and tabs in blank lines
* @line: string to clean
*
* Return: a pointer to the cleaned string
*/
char *trim_line(char *line)
{
	char *start, *end;

	if (line == NULL)
		return (NULL);

	start = line;

	while (*start && isspace((unsigned char)*start))
		start++;

	if (*start == '\0')
	{
		*line = '\0';
		return (line);
	}

	end = start + strlen(start) - 1;

	while (end > start && isspace((unsigned char)*end))
		end--;

	end[1] = '\0';
	return (start);
}
