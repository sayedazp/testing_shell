#include "main.h"

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 * no function return
 */

void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

	}
}

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 * no function return
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * Return: void
 */

void free_info(info_t *info)
{
	ssfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
}

/**
 * ffree_info - frees info_t struct fields
 * @info: struct address
 * no function return
 */

void ffree_info(info_t *info)
{

	free_info(info);
	if (!info->cmd_buf)
		free(info->arg);
	if (info->env)
		free_list(&(info->env));
	ssfree(info->environ);
	info->environ = NULL;
	bfree((void **)info->cmd_buf);
	_putchar(B_FLUSH);
}

/**
 * bfree - frees info_t struct fields
 * @ptr: struct address
 * Return: 1 for free proccess or 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
