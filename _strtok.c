#include "main.h"
/**
 * delim_check - Checks If A Character Match Any Char *
 * @c: Character To Check
 * @str: String To Check
 * Return: 1 Succes, 0 Failed
 */
unsigned int delim_check(char c, const char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - Token A String Into Token (strtrok)
 * @str: String
 * @delim: Delimiter
 * Return: Pointer To The Next Token Or NULL
 */
char *_strtok(char *str, const char *delim)
{
	unsigned int i;
	static char *tks;
	static char *ntk;

	if (str != NULL)
		ntk = str;
	tks = ntk;
	if (tks == NULL)
		return (NULL);
	for (i = 0; tks[i] != '\0'; i++)
	{
		if (delim_check(tks[i], delim) == 0)
			break;
	}
	if (ntk[i] == '\0' || ntk[i] == '#')
	{
		ntk = NULL;
		return (NULL);
	}
	tks = ntk + i;
	ntk = tks;
	for (i = 0; ntk[i] != '\0'; i++)
	{
		if (delim_check(ntk[i], delim) == 1)
			break;
	}
	if (ntk[i] == '\0')
		ntk = NULL;
	else
	{
		ntk[i] = '\0';
		ntk = ntk + i + 1;
		if (*ntk == '\0')
			ntk = NULL;
	}
	return (tks);
}
