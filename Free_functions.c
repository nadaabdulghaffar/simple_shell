#include "main.h"
/**
 * free_argv - free tokenized command
 * @argv: array of tokenzied command
 * Return: void
 */
void free_argv(char **argv)
{
	unsigned int i;

	for (i = 0; argv[i] != NULL; i++)
		free(argv[i]);
	free(argv);

}

/**
 * free_buffer - free Buffer
 * @Buffer: input command
 * Return: void
*/

void free_buffer(char *Buffer)
{
    if (Buffer != NULL)
    {
        if (Buffer[0] != '\0')
        {
            free(Buffer);
        }
    }
}
