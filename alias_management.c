#include "shell.h"
#include <unistd.h>

/**
 * print_alias - add, remove or display aliases
 * @data: structure for program's data
 * @alias: name of alias to be output
 * Return: zero for success or any number if declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
				&&	data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j]; j++)
				{
					buffer[j] = data->alias_list[i][j];
					if (data->alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove, display aliases
 * @data: structure for program's data
 * @name: name of requested alias
 * Return: zero for success or any number if declared in arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int i, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_list[i], alias_length) &&
			data->alias_list[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add/override alias
 * @alias_string: alias to be set in of form (name='value')
 * @data: structure of the program's data
 * Return: zero for success or any number if declared in arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], i) &&
			data->alias_list[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}

