#include "simpleshell.h"

/**
 **_bshstrgncpy - Copies a string.
 *@dst: Destination string to copy to.
 *@source: Source string
 *@num: The number of characters to be copied.
 *Return: The resulting concatenated string.
 */
char *_bshstrgncpy(char *dst, int num, char *source)
{
	int j, i;
	char *strg = dst;

	j = 0;
	while (source[j] != '\0' && j < num - 1)
	{
		dst[j] = source[j];
		j++;
	}
	if (j < num)
	{
		i = j;
		while (i < num)
		{
			dst[i] = '\0';
			i++;
		}
	}
	return (strg);
}

/**
 **_bshstrgncat - Merges two strings.
 *@dst: tThe initial string.
 *@source: The additional string.
 *@num: The maximum number of bytes to be utilized.
 *Return: The resulting merged string.
 */
char *_bshstrgncat(char *dst, int num, char *source)
{
	int j, i;
	char *strg = dst;

	j = 0;
	i = 0;
	while (dst[j] != '\0')
		j++;

	while (source[i] != '\0' && i < num)
	{
		dst[j] = source[i];
		j++;
		i++;
	}
	if (i < num)
		dst[j] = '\0';
	return (strg);
}

/**
 **_bshstrgchr - Finds a character within a string.
 *@strg: The string to be searched.
 *@ch: The character to locate.
 *Return: A pointer to the memory area containing 'ch' within 'strg'.
 */
char *_bshstrgchr(char ch, char *strg)
{
	do {
		if (*strg == ch)
			return (strg);
	} while (*strg++ != '\0');

	return (NULL);
}
