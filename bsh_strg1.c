#include "simpleshell.h"

/**
 * _bshstrgcpy - Duplicates a string.
 * @des_buff: The destination buffer.
 * @src_buff: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *_bshstrgcpy(char *des_buff, char *src_buff)
{
	int j = 0;

	if (des_buff == src_buff || src_buff == 0)
		return (des_buff);
	while (src_buff[j])
	{
		des_buff[j] = src_buff[j];
		j++;
	}
	des_buff[j] = 0;
	return (des_buff);
}

/**
 * _bshstrgdup - Replicates the content of a string.
 * @strg: The original string to be duplicated.
 *
 * Return: Pointer to the duplicated string.
 */
char *_bshstrgdup(const char *strg)
{
	int len = 0;
	char *rtn;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		len++;
	rtn = malloc(sizeof(char) * (len + 1));
	if (!rtn)
		return (NULL);
	for (len++; len--;)
		rtn[len] = *--strg;
	return (rtn);
}

/**
 * _bshputs - Displays an input string.
 * @strg: The string to be shown.
 *
 * Return: None
 */
void _bshputs(char *strg)
{
	int j = 0;

	if (!strg)
		return;
	while (strg[j] != '\0')
	{
		_bshputchar(strg[j]);
		j++;
	}
}

/**
 * _bshputchar - Outputs the character 'ch' to standard output.
 * @ch: The character to be printed.
 *
 * Return: Returns 1 on success.
 * On error, returns -1 and sets errno appropriately.
 */
int _bshputchar(char ch)
{
	static int j;
	static char buff[RECORD_BUFF_SIZE];

	if (ch == FLUSH_BUFF || j >= RECORD_BUFF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != FLUSH_BUFF)
		buff[j++] = ch;
	return (1);
}
