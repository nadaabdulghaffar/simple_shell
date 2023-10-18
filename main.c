#include "main.h"
/**
 * execute_command - execute command path, child process
 * @argv: array of string
 * Return: exit status
 */

int execute_command(char **argv)
{
	int id = fork();
	int status;

	if (id == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
			perror("Error");
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}

/**
 * main - project primary file
 * Return: int
 */
int main(void)
{
	char *Buffer = NULL, **argvs;
	size_t read_size = 0;
	ssize_t buffer_size = 0;
	int status = 0;

	while (1)
	{
		argvs = NULL;
		if (isatty(STDIN_FILENO))
			printf("$");
		buffer_size = getline(&Buffer, &read_size, stdin);
		Exit_check(Buffer, buffer_size);
		comments_handle(Buffer);
		if (is_emtyln(Buffer) == 1)
		{
			status = 0;
			continue;
		}
		if (strcmp(Buffer, "env") == 0)
		{
			print_env();
			continue;
		}
		argvs = tokenize(Buffer, buffer_size);
		argvs[0] = search_path(argvs[0]);
		if (argvs[0])
			status = execute_command(argvs);
		else
		{
			perror("Error");
			free_argv(argvs);
		}
		free_buffer(Buffer);
		free(argvs);
	}
	return (status);
}
