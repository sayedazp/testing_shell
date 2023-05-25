#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RB_SIZE 1024
#define WB_SIZE 1024
#define B_FLUSH -1

#define CMD_NORM	0
#define CMD_CHAIN	3

extern char **environ;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0}
/**
 * struct liststr - known as list_node
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_node;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_node *env;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
} info_t;

/**
 * struct builtin - known as builtin_table
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;



int __getline(info_t *info, char **lineptr, size_t *n);
void sigintHandler(__attribute__((unused))int sig_num);
int _putchar(char c);
int _eputchar(char c);
char *itoa(long int num, int base, int flags);
char *starts_with(const char *haystack, const char *needle);
void _puts(char *str);

list_node *add_node(list_node **, const char *);
list_node *add_node_end(list_node **, const char *);
size_t print_list(const list_node *);
int delete_node_at_index(list_node **, unsigned int);
void free_list(list_node **);


int populate_env_list(info_t *info);

int shellin(info_t *info, char **av);
ssize_t get_input(info_t *info);


void set_info(info_t *info, char **av);

int is_delim(char c, char *delim);

char **strtow(char *str, char *d);

void find_cmd(info_t *info);

char *find_path(info_t *info, char *pathstr, char *cmd);

char *_getenv(info_t *info, const char *name);
int _setenv(info_t *info, char *var, char *value);

int is_cmd(info_t *info, char *path);
void fork_cmd(info_t *info);
char *dup_chars(char *pathstr, int start, int stop);

char **list_to_strings(list_node *head);
char **get_environ(info_t *info);

void print_error(info_t *info, char *estr);
void _eputs(char *str);
int _eputchar(char c);

int _theexit(info_t *info);
int find_builtin(info_t *info);
int _cd(info_t *info);

void ssfree(char **pp);

void free_info(info_t *info);
void ffree_info(info_t *info);
void clear_info(info_t *info);
int bfree(void **);


int is_chain(info_t *info, char *buf, size_t j);

ssize_t input_buf(info_t *info, char **buf, size_t *len);
int interactive(info_t *info);
int print_d(int input, int fd);

int _theenv(info_t *info);


#endif
