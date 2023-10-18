#include "main.h"
/**
 * main - project primary file
 * Return: int
 */
int main(void)
{
	char *Buffer = NULL, **argvs = NULL;
	size_t read_size = 0;
	ssize_t buffer_size = 0;
	int exit_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$");

		buffer_size = _getline(&Buffer, &read_size, stdin);
		Exit_check(buffer_size, Buffer);
		comments_handle(Buffer);
		if (is_emtyln(Buffer) == 1)
		{
			exit_status = 0;
			continue;
		}
		if (strcmp(Buffer, "env") == 0)
		{
			print_env();
			continue;
		}

		argvs = tokenize(Buffer, buffer_size);

		if (argvs != NULL)
			exit_status = execute_command(argvs);
		else
			perror("Error");

		free_argv(argvs);
		free_buffer(Buffer);
	}
	return (exit_status);
}
