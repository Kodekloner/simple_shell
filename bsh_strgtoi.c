#include "simpleshell.h"

/**
 * bsh_interactive_mode - Indicates whether the shell is in interactive mode.
 * @params: Address of the params_t structure.
 *
 * Return: Returns 1 if the shell is in interactive mode, otherwise 0.
 */

int bsh_interactive_mode(params_t *params)
{
	return (isatty(STDIN_FILENO) && params->readfiledir <= 2);
}

/**
 * bsh_is_str_delim - Checks if a character is a delimiter in a string.
 * @ch: The character to be checked.
 * @strg_deli: The string delimiter.
 * Return: Returns 0 if false, 1 if true.
 */
int bsh_is_str_delim(char *strg_deli, char ch)
{
	while (*strg_deli)
		if (*strg_deli++ == ch)
			return (1);
	return (0);
}

/**
 * bsh_char_alpha - Verifies if a character is alphabetic.
 * @ch: The input character.
 * Return: Returns 1 if 'ch' is an alphabetic character, otherwise 0.
 */

int bsh_char_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * bsh_strgtoi - Transforms a string into an integer.
 * @strg: The input string for conversion.
 * Return: Returns 0 if there are no numerical digits in 'strg',
 *					otherwise the converted number.
 */

int bsh_strgtoi(char *strg)
{
	int j, sgn = 1, flg = 0, out;
	unsigned int res = 0;

	for (j = 0; flg != 2 && strg[j] != '\0'; j++)
	{
		if (strg[j] == '-')
			sgn *= -1;

		if (strg[j] <= '9' && strg[j] >= '0')
		{
			flg = 1;
			res *= 10;
			res += (strg[j] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		out = -res;
	else
		out = res;

	return (out);
}
