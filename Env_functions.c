#include "main.h"
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
	return (putenv(var));
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
