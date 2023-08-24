#include "simpleshell.h"

/**
 * **bshstrgtow - Divides a string into individual words,
 *								ignoring repeated delimiters.
 * @strg: The input string to be split.
 * @strg_deli: The delimiter string used for splitting.
 * Return: Returns a pointer to an array of strings or NULL in case of failure.
 */

char **bshstrgtow(char *strg, char *strg_deli)
{
	int j, z, l, n, no_wrds = 0;
	char **p;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!strg_deli)
		strg_deli = " ";
	for (j = 0; strg[j] != '\0'; j++)
		if (!bsh_is_str_delim(strg_deli, strg[j])
		&& (bsh_is_str_delim(strg_deli, strg[j + 1]) || !strg[j + 1]))
			no_wrds++;

	if (no_wrds == 0)
		return (NULL);
	p = malloc((1 + no_wrds) * sizeof(char *));
	if (!p)
		return (NULL);
	for (j = 0, z = 0; z < no_wrds; z++)
	{
		while (bsh_is_str_delim(strg_deli, strg[j]))
			j++;
		l = 0;
		while (!bsh_is_str_delim(strg_deli, strg[j + l]) && strg[j + l])
			l++;
		p[z] = malloc((l + 1) * sizeof(char));
		if (!p[z])
		{
			for (l = 0; l < z; l++)
				free(p[l]);
			free(p);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			p[z][n] = strg[j++];
		p[z][n] = 0;
	}
	p[z] = NULL;
	return (p);
}

/**
 * **bshstrgtow2 - Separates a string into distinct words.
 * @strg: The input string to be divided.
 * @strg_deli: The delimiter that indicates where the division occurs.
 * Return: Provides a pointer to an array of strings
 *					or NULL if there's an issue.
 */
char **bshstrgtow2(char strg_deli, char *strg)
{
	int j, z, l, n, no_wrds = 0;
	char **p;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (j = 0; strg[j] != '\0'; j++)
		if ((strg[j] != strg_deli && strg[j + 1] == strg_deli) ||
				    (strg[j] != strg_deli && !strg[j + 1]) || strg[j + 1] == strg_deli)
			no_wrds++;
	if (no_wrds == 0)
		return (NULL);
	p = malloc((1 + no_wrds) * sizeof(char *));
	if (!p)
		return (NULL);
	for (j = 0, z = 0; no_wrds > z; z++)
	{
		while (strg[j] == strg_deli && strg[j] != strg_deli)
			j++;
		l = 0;
		while (strg[j + l] != strg_deli && strg[j + l] && strg[j + l] != strg_deli)
			l++;
		p[z] = malloc((l + 1) * sizeof(char));
		if (!p[z])
		{
			for (l = 0; l < z; l++)
				free(p[l]);
			free(p);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			p[z][n] = strg[j++];
		p[z][n] = 0;
	}
	p[z] = NULL;
	return (p);
}
