#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * execute - executes commands with the entire path variables
 * @data: func pointer to program data
 * Return: zero for success, otherwise -1
 */

int execute(data_of_program *data)

{
	int retval = 0, status;
	pid_t pidd;

	/* checks for the program builtins */
	retval = builtins_list(data);
	if (retval != -1)/* if program found  builtins */
		return (retval);

	/* checks for the program file system */
	retval = find_program(data);
	if (retval)
	{/* if not found */
		return (retval);
	}
	else
	{/* if found */
		pidd = fork(); /* creates child process */
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

