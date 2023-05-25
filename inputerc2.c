#include "main.h"
#include <unistd.h>
/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: r
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		bfree((void **)info->cmd_buf);
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buf, &len_p, stdin);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				if ((*buf)[0] == '\n')
					return (0);
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * __getline - gets the next line of input from file discriptor
 * @info: parameter struct
 * @lineptr: address of pointer to buffer, preallocated or NULL
 * @n: size of preallocated lineptr buffer if not NULL
 *
 * Return: number of char readed
 */

int __getline(info_t *info, char **lineptr, size_t *n)
{
	int count = 0, size_realloc = RB_SIZE;
	ssize_t r = 0;
	int loop = 0;
	char *buf = NULL;

	do {
		if (loop == 0)
		{
			buf = malloc(size_realloc * sizeof(char));
		}
		else
		{
			if (buf[(RB_SIZE * loop) - 1] == '\n')
			{
				buf[count + r] = '\0';
				break;
			}
			else if (r == RB_SIZE)
			{
				size_realloc += RB_SIZE;
				buf = realloc(buf, size_realloc * sizeof(char));
				count += RB_SIZE;
			}
		}
		if (!buf)
			return (buf ? free(buf), -1 : -1);
		r = read(info->readfd, &buf[count], RB_SIZE);
		buf[count + r] = '\0';
		if (r == -1 || r == 0)
		{
			free(buf);
			return (-1);
		}
		loop++;
	} while (r == RB_SIZE);
	*lineptr = buf;
	*n = count + RB_SIZE;
	return (count + r);
}
/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((_getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
