#include "main.h"

/**
 * is_emtyln - checks if exists a empty line
 * @Buffer: input command
 * Return: 0 or 1 (int)
 */

int is_emtyln(char *Buffer)
{
	int count;

	for (count = 0; Buffer[count] != '\0'; count++)
	{
		if (Buffer[count] != ' ')
			return (0);
	}
	return (1);
}



/**
 * comments_handle- remove everything after #
 * @Buffer: input command;
 * Return:void
 */
void comments_handle(char *Buffer)
{
	unsigned int count;

		for (count = 0; Buffer[count] != '\0'; count++)
		{
			if (Buffer[count] == '#')
			{
				Buffer[count] = '\0';
				break;
			}
	}
}
