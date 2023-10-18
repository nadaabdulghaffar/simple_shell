#include "main.h"

/**
 * tokenize - tokenzie input command into array of string
 * @command: input command
 * @num_charin: size of readed chars
 * Return: array of string
 */
char **tokenize(char *command, ssize_t num_charin)
{
	char *copy_command = NULL, *delim = " ", *token;
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
	free(token);
	free(copy_command);
	return (argv);
}

/**
 * search_path - search file between the path
 * @command: cmd
 * Return: cmd path
 */

char *search_path(char *command)
{
	char **path_split;
	char *path_concat = NULL;
	int i = 0, path_len = 0;
	struct stat info;
	char *path, *path_cpy;
	path = _getenv("PATH");
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
	char *tmp, **split_str;
	int i = 0;

	tmp = strtok(str, sep);
	split_str = (char **)malloc(100 * sizeof(char *));

	if (!split_str)
	{
		free(split_str);
		return (NULL);
	}

	while (tmp)
	{
		split_str[i] = tmp;
		tmp = strtok(NULL, sep);
		i++;
	}
	return (split_str);
}
