#include "simpleShell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: 1 on success, -1 on error, and errno is set accordingly.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
/**
 * *startsWith - checks if str1 starts with certain substring
 * @str1: string to search
 * @substring: the substring to find
 * Return: pointer of next char of string or NULL
 */
char *startsWith(const char *str1, const char *substring)
{
	while (*substring)
		if (*substring++ != *str1++)
			return (NULL);
	return ((char *)str1);
}
/**
 * _strcmp - comparison two strings.
 * @s1: first string
 * @s2: second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
