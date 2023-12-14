#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _print - writes an array of character
 * @string: pointer to array
 * Return: nothing
 */

int _print(char *string)

{
	return (write(STDOUT_FILENO, string, str_length(string)));
}

/**
 * _printe - writes an array of chars on the std err
 * @string: pointer to an array of chars
 * Return: number of bytes written or -1 on err
 */

int _printe(char *string)

{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _print_error - writes an array of chars to the stderr
 * @data: pointer to program data
 * @errorcode: error code
 * Return: number of bytes or -1 on err
 */

int _print_error(int errorcode, data_of_program *data)

{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->tokens[0]);
		if (errorcode == 2)
			_printe(": Illegal number: ");
		else
			_printe(": can't cd to ");
		_printe(data->tokens[1]);
		_printe("\n");
	}
	else if (errorcode == 127)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printe(data->program_name);
		_printe(": ");
		_printe(n_as_string);
		_printe(": ");
		_printe(data->command_name);
		_printe(": Permission denied\n");
	}
	return (0);
}

