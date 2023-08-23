#include "simpleshell.h"

/**
 * _bsheputs - Outputs a provided string.
 * @strg: The string to be printed.
 * Return: No specific return value.
 */
void _bsheputs(char *strg)
{
	int j = 0;

	if (!strg)
		return;
	while (strg[j] != '\0')
	{
		_bsheputchar(strg[j]);
		j++;
	}
}

/**
 * _bsheputchar - Writes the character 'ch'
 *								to the standard error stream (stderr).
 * @ch: The character to be printed.
 *
 * Return: Returns 1 upon success.
 * If an error occurs, -1 is returned,
 * and the 'errno' variable is set accordingly.
 */
int _bsheputchar(char ch)
{
	static int j;
	static char buff[RECORD_BUFF_SIZE];

	if (j >= RECORD_BUFF_SIZE || ch == FLUSH_BUFF)
	{
		write(2, buff, j);
		j = 0;
	}
	if (ch != FLUSH_BUFF)
		buff[j++] = ch;
	return (1);
}

/**
 * _bshputfdir - Writes the character 'ch'
 *								to the provided file descriptor 'fdir'.
 * @ch: The character to be printed.
 * @fdir: The file descriptor to write to.
 *
 * Return: Returns 1 upon success.
 * If an error occurs, -1 is returned,
 * and the 'errno' variable is set accordingly.
 */
int _bshputfdir(int fdir, char ch)
{
	static int j;
	static char buff[RECORD_BUFF_SIZE];

	if (j >= RECORD_BUFF_SIZE || ch == FLUSH_BUFF)
	{
		write(fdir, buff, j);
		j = 0;
	}
	if (ch != FLUSH_BUFF)
		buff[j++] = ch;
	return (1);
}

/**
 * _bshputsfdir - Outputs the given string to the specified file descriptor.
 * @strg: The string to be printed.
 * @fdir: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _bshputsfdir(int fdir, char *strg)
{
	int j = 0;

	if (!strg)
		return (0);
	while (*strg)
	{
		j += _bshputfdir(fdir, *strg++);
	}
	return (j);
}
