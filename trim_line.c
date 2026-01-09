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

	while (*start && (*start == ' ' || *start == '\t' || *start == '\n'))
		start++;

	if (*start == '\0')
	{
		*line = '\0';
		return (line);
	}

	end = start + strlen(start) - 1;

	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	end[1] = '\0';

	if (start != line)
		memmove(line, start, strlen(start) + 1);

	return (line);
}
