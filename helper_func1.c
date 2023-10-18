#include "main.h"

/**
 * _getline -Read The Input By User From Stdin
 * @Buffer: Buffer
 * @Buffer_size: buffer size
 * @stream: stream of data (stdin)
 * Return: number of chars readed
*/
ssize_t _getline(char **Buffer, size_t *Buffer_size, FILE *stream)
{
	ssize_t char_count;

	char_count = getline(Buffer, Buffer_size, stream);

	return (char_count);
}

/**
 * tokenize - tokenzie input command into array of string
 * @command: input command
 * @num_charin: size of readed chars
 * Return: array of string
 */
char **tokenize(char *command, ssize_t num_charin)
{
	char *copy_command = NULL;
	char *delim = " ";
	char *token;
	int num_token = 0, i;
	char **argv = NULL;

	copy_command = malloc(sizeof(char) * num_charin);
	if (copy_command == NULL)
	{
		free(copy_command);
		return (NULL);
	}
	strcpy(copy_command, command);

	token = strtok(copy_command, delim);
	while (token)
	{
		num_token++;
		token = strtok(NULL, delim);
	}
	num_token++;

	argv = malloc(sizeof(char *) * num_token);
	if (argv == NULL)
	{
		free(copy_command);
		return (NULL);
	}
	token = strtok(command, delim);

	for (i = 0 ; token; i++)
	{
		argv[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(argv[i], token);

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;
	free(copy_command);
	return (argv);
}

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
 * print_env - prints environment
 * Return : void
 */
void print_env(void)
{
	int count = 0;

	while (environ[count])
	{
		printf("%s\n", environ[count]);
		count++;
	}
}



/**
 * search_path - search file between the path
 * @command: cmd
 * Return: cmd path
 */

char *search_path(char *command)
{
	char *path = getenv("PATH"), *path_cpy;
	char **path_split;
	char *path_concat = NULL;
	int i = 0, path_len = 0;
	struct stat info;

	if (stat(command, &info) == 0)
		return (command);

	path_cpy = malloc(strlen(path) + 1);

	path_cpy = strcpy(path_cpy, path);
	path_split = _split(path_cpy, ":");

	while (path_split[i])
	{
		path_len = strlen(path_split[i]);

		if (path_split[i][path_len - 1] != '/')
			path_concat = strcat(path_split[i], "/");

		path_concat = strcat(path_split[i], command);

		if (stat(path_concat, &info) == 0)
			break;

		i++;
	}

	free(path_cpy);

	if (!path_split[i])
	{
		free(path_split);
		return (NULL);
	}

	free(path_split);
	return (path_concat);
}


/**
 * _split - split string
 * @str: string
 * @sep: separator
 * Return: divided path
 */

char **_split(char *str, char *sep)
{
	char *aux, **split_str;
	int i = 0;

	aux = strtok(str, sep);
	split_str = (char **)malloc(100 * sizeof(char *));

	if (!split_str)
	{
		free(split_str);
		return (NULL);
	}

	while (aux)
	{
		split_str[i] = aux;
		aux = strtok(NULL, sep);
		i++;
	}
	return (split_str);
}
