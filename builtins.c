#include "main.h"

/**
 * _theexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int _theexit(info_t *info)
{
	int exit;
	char *s = info->argv[1];

	if (info->argv[1])
	{
		exit = atoi(s);
		if (exit <= 255 && exit >= 0)
		{
			info->err_num = exit;
		}
		else
		{
			info->err_num = 13;
		}
	}
	else
	{
		info->err_num = -1;
	}
	return (-2);
}
/**
 * _cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _cd(info_t *info)
{
	char *the_dir, *k, buff[1024];
	int ch_ind;

	k = getcwd(buff, 1024);
	if (!k)
		_puts("No such directory\n");
	if (info->argv[1] == NULL)
	{
		the_dir = _getenv(info, "HOME=");
		if (!the_dir)
			ch_ind = chdir((the_dir = _getenv(info, "PWD=")) ? the_dir : "/");
		else
			ch_ind = chdir(the_dir);
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(k);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_ind = chdir((the_dir = _getenv(info, "OLDPWD=")) ? the_dir : "/");
	}
	else
		ch_ind = chdir(info->argv[1]);
	if (ch_ind == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}


/**
 * _theenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _theenv(info_t *info)
{
	print_list(info->env);
	return (0);
}
