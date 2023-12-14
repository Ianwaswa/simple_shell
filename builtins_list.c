#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * builtins_list - search for match and execute the associated builtin
 * @data: structure to the program's data
 * Return: Return output function executed if a match is there otherwise returns -1
 **/

int builtins_list(data_of_program *data)

{
	int iterator;

	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*go through the struct*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if there is a match:*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*execute the function and return the output value of the function*/
			return (options[iterator].function(data));
		}
/*if no match return -1 */
	}
	return (-1);
}

