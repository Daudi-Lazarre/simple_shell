#include "holberton.h"

/**
 * Big boi shell
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	int i;
	char *input = NULL, **command = NULL, **path = NULL;
	size_t size;

	/* get the path info from environment variables */
	path = _getpath(env);
	while (1)
	{
		new_prompt();
		if(getline(&input, &size, stdin) == -1)
			exit(1);
		/* parse input to get command and arguments */
		command = parse_input(input, &size);
		
		/* TODO: use function pointer */
		
		if ((_strcmp(command[0], "exit") == 0))
		{
			free(input);
			free(command);
			free(path);
			exit(0);
		}

		else if ((_strcmp(command[0], "env") == 0))
			print_env(env);
		
		else if ((_strcmp(command[0], "path") == 0))
		{
			for (i = 0; path[i]; i++)
			{
				_puts(path[i]);
				_puts("\n");
			}
		}
		
		else if (_strcmp(command[0], "\n") != 0)
		{
			command[0] = findpath(command[0], path);
			printf("Command is: %s\n", command[0]);
			if (access(command[0], X_OK) == 0)
			{
				execute(command, env);
				free(command[0]);
			}
			else
				_puts("simple shell: no such file or directory\n");
		}
		
		free(command);
	}
	
	free(input);
	free(path);
	return (0);
}
