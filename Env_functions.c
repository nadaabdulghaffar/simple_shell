#include "main.h"

/**
 * print_env - prints all environment variables
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
 * unsetenv_command - Remove an environment variable
 * @name: varialbe name
 * Return: 0 on success ,-1 on faliure
 */
int unsetenv_command(const char *name)
{

	size_t namelen = strlen(name);
	char **new_environ = NULL, **env;
	int count = 0, i = 0;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)

		return (-1);

	for (env = environ; *env != NULL; ++env)
	{
		if (strncmp(*env, name, namelen) != 0 || (*env)[namelen] != '=')
		{
			++count;
		}
	}
	new_environ = (char **)malloc((count + 1) * sizeof(char *));
	if (new_environ == NULL)
	{
		return (-1);
	}

	for (env = environ; *env != NULL; ++env)
	{
		if (strncmp(*env, name, namelen) != 0 || (*env)[namelen] != '=')
		{
			new_environ[i++] = *env;
		}
	}
	new_environ[i] = NULL;

	free(environ);
	environ = new_environ;

	return (0);
}
/**
 * setenv_command - Initialize new env var,or modify an existing one
 * @name: variable name
 * @value: value of variable
 * @overwrite:1 overwrite previous value, 0 no change if it's already set.
 * Return: -1 on faliure , 0 on success
 */
int setenv_command(const char *name, const char *value, int overwrite)
{
	char *var = NULL;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
	{
		fprintf(stderr, "setenv: Invalid variable name\n");
		return (-1);
	}

	if (getenv(name) != NULL && overwrite == 0)
	{
		fprintf(stderr, "setenv:Variable already exists, overwrite not allowed\n");
		return (-1);
	}

	var = malloc(strlen(name) + strlen(value) + 2);
	if (var == NULL)
	{
		fprintf(stderr, "setenv: Memory allocation failed\n");
		return (-1);
	}

	sprintf(var, "%s=%s", name, value);
	return (_putenv(var));
}



/**
 * _putenv - Modify the environment of the current process.
 * @string: The string in the form "name=value".
 *
 * Return: 0 on success, -1 on failure.
 */
int _putenv(char *string)
{
	char *name, **env, **new_environ = NULL, **new_env;

	if (string == NULL || strchr(string, '=') == NULL)
		return (-1);

	name = strtok(string, "=");
	env = environ;
	while (*env != NULL)
	{
		if (strncmp(*env, name, strlen(name)) == 0 && (*env)[strlen(name)] == '=')
		{
			*env = string;
			return (0);
		}
		env++;
	}
	new_environ = (char **)malloc((environ_count() + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (-1);
	env = environ;
	new_env = new_environ;

	while (*env != NULL)
	{
		*new_env = *env;
		env++;
		new_env++;
	}
	*new_env = string;
	new_env++;
	*new_env = NULL;
	free(environ);
	environ = new_environ;
	return (0);
}

/**
 * environ_count - Count the number of environment variables.
 *
 * Return: The number of environment variables.
 */
int environ_count(void)
{
	char **env = environ;
	int count = 0;

	while (*env != NULL)
	{
		count++;
		env++;
	}

	return (count);
}
