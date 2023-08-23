#include "simpleshell.h"

/**
 * _bshstrglen - Computes the length of a string.
 * @strg: The string for which to determine the length.
 *
 * Return: Integer representing the length of the string.
 */
int _bshstrglen(char *strg)
{
	int j = 0;

	if (!strg)
		return (0);

	while (*strg++)
		j++;
	return (j);
}

/**
 * _bshstrgcmp - Conducts a lexicographic comparison between two strings.
 * @strg1: The first string for comparison.
 * @strg2: The second string for comparison.
 *
 * Return: Negative value if strg1 comes before strg2 lexicographically,
 *					Positive value if strg1 comes after strg2 lexicographically,
 * Zero if strg1 is equal to strg2.
 */
int _bshstrgcmp(char *strg1, char *strg2)
{
	while (*strg1 && *strg2)
	{
		if (*strg1 != *strg2)
			return (*strg1 - *strg2);
		strg1++;
		strg2++;
	}
	if (*strg1 == *strg2)
		return (0);
	else
		return (*strg1 < *strg2 ? -1 : 1);
}

/**
 * bsh_sw - Checks if the needle starts with the haystack.
 * @hystck: The string to search within.
 * @ndle: The substring to locate.
 *
 * Return: Address of the next character after the haystack if found, or NULL.
 */
char *bsh_sw(const char *hystck, const char *ndle)
{
	while (*ndle)
		if (*ndle++ != *hystck++)
			return (NULL);
	return ((char *)hystck);
}

/**
 * _bshstrgcat - Combines two strings.
 * @des_buff: The buffer to which the content will be appended.
 * @src_buff: The buffer containing the content to be appended.
 *
 * Return: Pointer to the destination buffer.
 */
char *_bshstrgcat(char *des_buff, char *src_buff)
{
	char *rtn = des_buff;

	while (*des_buff)
		des_buff++;
	while (*src_buff)
		*des_buff++ = *src_buff++;
	*des_buff = *src_buff;
	return (rtn);
}
