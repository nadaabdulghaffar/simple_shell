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
    int count;

		for (count = 0; Buffer[count] != '\0'; count++)
		{
			if (Buffer[count] == '#')
			{
				Buffer[count] = '\0';
				break;
			}
	}
}
/**
 * Exit_check- check if the user exit
 * @buffer_size: buffer size
 * @Buffer: input buffer
 * Return: void
*/

void Exit_check(ssize_t buffer_size, char *Buffer)
{
	if (buffer_size == -1 || strcmp(Buffer, "exit\n") == 0)
	{
		free_buffer(Buffer);
		exit(0);
	}
	Buffer[buffer_size - 1] = '\0';
}
