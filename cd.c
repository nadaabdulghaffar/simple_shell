#include "main.h"
/**
 * change_dir - Change Dirctorie
 * @argvs: Parsed Command
 * @er: Statue Last Command Excuted
 * Return: 0 Succes 1 Failed (For Old Pwd Always 0 Case No Old PWD)
 */
int change_dir(char **argvs, __attribute__((unused)) int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (argvs[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (strcmp(argvs[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(argvs[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * process_command - Process the command based on Buffer content.
 * @Buf: The input command buffer.
 * @status: Pointer to the status variable.
 * @buf_size: Size of the buffer.
 * @argv: Array of command arguments.
 */

void process_command(char *Buf, int *status, size_t buf_size, char **argv)
{
	if (strncmp(Buf, "cd", 2) == 0)
	{
		argv = tokenize(Buf, buf_size);
		*status = change_dir(argv, *status);
		free_argv(argv);
		return;
	}
	if (argv[0])
	{
		if (strcmp(argv[0], "set") == 0 || strcmp(argv[0], "unset") == 0)
		{
			*status = execute_set_unset_command(argv);
		}
	}
}
