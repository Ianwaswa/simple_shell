#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * builtin_exit - exit point status of program
 * @data: struct for program data
 * Return: zero for success or any other number if declared in the arguments
 */

int builtin_exit(data_of_program *data)

{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - changes current working directory to the speciified one
 * @data: struct for program data
 * Return: zero for or any other number if declared in the argument
 */

int builtin_cd(data_of_program *data)

{
	char *dir_home = env_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - sets working directory
 * @data: struct for program data
 * @new_dir: path to be working dir
 * Return: zero for success else stated otherwise in the arguement
 */

int set_work_directory(data_of_program *data, char *new_dir)

{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - shows env in which shell runs
 * @data: struct for program data
 * Return: zero for success else stated otherwise in the arguement
 */

int builtin_help(data_of_program *data)

{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[i], length))
		{
			_print(mensajes[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - add, remove or display aliases
 * @data: struct for program data
 * Return: zero for success or otherwise
 */

int builtin_alias(data_of_program *data)

{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
