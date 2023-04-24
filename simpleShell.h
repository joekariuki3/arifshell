#ifndef SIMPLESHELL_H
#define SIMPLESHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Reading and writing buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* connect two commands */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* converting numbers*/
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/*for using system getline*/
#define USE_GETLINE 0
#define USE_STRTOK 0

/*for shell file history*/
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/*for environment variables */
extern char **environ;

/*list string struct*/
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/*list prototypes*/
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
size_t printListStr(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);
size_t listLen(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* string prototypes */
int _strlen(char *);
int _strcmp(char *, char *);
char *startsWith(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strdup(const char *);
char *_strchr(char *, char);
void _puts(char *);
int _putchar(char);

/*passing information struct*/
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/*error prototypes*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erratoi(char *);
int print_d(int, int);
void print_error(info_t *, char *);
int printInt(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);

/* Default commands*/
/*default struct*/
/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*default prototype */
int _myExit(info_t *);
int _cd(info_t *);
int _history(info_t *);
int _alias(info_t *);

/* protootype of info*/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);

/*get: (enviro, line) */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);

/* prototype of signal */
void sigintHandler(int);

/* prototype of environment */
char *_getenv(info_t *, const char *);
int _env(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* prototype atoi */
int interactive(info_t *);
int isDelim(char, char *);
int isAlpha(int);
int _atoi(char *);

/* prototype for histry */
char *getHistoryFile(info_t *);
int writeHistory(info_t *);
int readHistory(info_t *);
int buildHistoryList(info_t *, char *, int);
int reNumberHistory(info_t *);

/*prototype of all memory*/
char *memSet(char *, char, unsigned int);
void ffree(char **);
void *reAlloc(void *, unsigned int, unsigned int);
int bufferFree(void **);

/* prototype of parse*/
int isCmd(info_t *, char *);
char *dupChars(char *, int, int);
char *findPath(info_t *, char *, char *);

/*prototype of loop*/
int hsh(info_t *, char **);
int findBuiltin(info_t *);
void findCmd(info_t *);
void forkCmd(info_t *);

/*prototype of tokenize*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/* prototype of connect command*/
int isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVars(info_t *);
int replaceString(char **, char *);

#endif
