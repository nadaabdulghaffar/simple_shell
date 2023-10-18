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
 * @Buffer: input buffer
 * @buffer_size: Buffer size
 * Return: void
*/

void Exit_check(char *Buffer, ssize_t buffer_size)
{
	if (Buffer != NULL)
	{
		if (strncmp(Buffer, "exit", 4) == 0)
		{
			int status = 0;

			if (sscanf(Buffer, "exit %d", &status) == 1)
			{
				free_buffer(Buffer);
				exit(status);
			}
			else if (strncmp(Buffer, "exit", 4) == 0)
			{
				free_buffer(Buffer);
				exit(0);
			}
		}
		else if (buffer_size == -1)
		{
			free_buffer(Buffer);
			exit(0);
		}

		Buffer[strlen(Buffer) - 1] = '\0';
	}
	else
	{
		exit(0);
	}
}
