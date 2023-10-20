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
