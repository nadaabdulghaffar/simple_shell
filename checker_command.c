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
	int inside_quotes = 0, i;

	for (i = 0; Buffer[i] != '\0'; i++)
	{
		if (Buffer[i] == '\"')
		{
			inside_quotes = !inside_quotes;
		}

		if (Buffer[i] == '#' && !inside_quotes)
		{
			Buffer[i] = '\0';
			break;
		}
	}
}

/**
 * Exit_check- check if the user exit
 * @Buffer: input buffer
 * @buffer_size: Buffer size
 * @argvs: array of toknzied command
 * Return: void
*/
void Exit_check(char *Buffer, ssize_t buffer_size, char **argvs)
{
	if (Buffer != NULL)
	{
		if (strncmp(Buffer, "exit", 4) == 0)
		{
			int status = 0;

			if (sscanf(Buffer, "exit %d", &status) == 1)
			{
				free_buffer(Buffer);
				free_argv(argvs);
				exit(status);
			}
			else if (strncmp(Buffer, "exit", 4) == 0)
			{
				free_buffer(Buffer);
				free(argvs);
				exit(0);
			}
		}
		else if (buffer_size == -1)
		{
			free_buffer(Buffer);
			free(argvs);
			exit(0);
		}

		Buffer[strlen(Buffer) - 1] = '\0';
	}
}

/**
 * execute_set_unset_command - decied which one will execute
 * @argvs: tokenzied command
 * Return:status
*/
int execute_set_unset_command(char **argvs)
{
	int status = 0;

	if (strcmp(argvs[0], "set") == 0)
	{
		if (argvs[1] && argvs[2])
			status = setenv_command(argvs[1], argvs[2], 1);
		else
		{
			fprintf(stderr, "set: Missing argument(s)\n");
			status = -1;
		}
	}
	else if (strcmp(argvs[0], "unset") == 0)
	{
		if (argvs[1])
			status = unsetenv_command(argvs[1]);
		else
		{
			fprintf(stderr, "unset: Missing argument\n");
			status = -1;
		}
	}

	return (status);
}
/**
 * _getenv - get env variables
 * @env_var: env variable
 * Return: env variable result, its content
 */

char *_getenv(char *env_var)
{
	int count = 0, count2, status;

	while (environ[count])
	{
		status = 1;

		for (count2 = 0; environ[count][count2] != '='; count2++)
		{
			if (env_var[count2] != environ[count][count2])
				status = 0;
		}
		if (status == 1)
			break;
		count++;
	}
	return (&environ[count][count2 + 1]);
}
