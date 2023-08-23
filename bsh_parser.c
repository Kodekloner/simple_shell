#include "simpleshell.h"

/**
 * is_bsh_cmd - Checks whether a file is an executable command.
 * @params: The params structure.
 * @file_path: Path file.
 *
 * Return: Returns 1 if true, 0 else.
 */
int is_bsh_cmd(char *file_path, params_t *params)
{
	struct stat stt;

	(void)params;
	if (!file_path || stat(file_path, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * bsh_dp_char - Duplicates characters from a string.
 * @pthstr: The input string containing characters.
 * @stid: The beginning index of characters to replicate.
 * @spid: The ending index of characters to replicate.
 *
 * Return: A pointer to a newly created buffer.
 */
char *bsh_dp_char(int stid, char *pthstr, int spid)
{
	static char buff[1024];
	int j = 0, l = 0;

	for (l = 0, j = stid; j < spid; j++)
		if (pthstr[j] != ':')
			buff[l++] = pthstr[j];
	buff[l] = 0;
	return (buff);
}

/**
 * bsh_fi_path - Locates the specified command in the PATH string.
 * @params: The parameter structure containing necessary information.
 * @pthstr: The PATH string where the search is performed.
 * @fndcmd: The command to be located.
 *
 * Return: Returns the full path of the command if found, or NULL if not found.
 */
char *bsh_fi_path(char *pthstr, params_t *params, char *fndcmd)
{
	int j = 0, cpos = 0;
	char *pat;

	if (!pthstr)
		return (NULL);
	if ((_bshstrglen(fndcmd) > 2) && bsh_sw(fndcmd, "./"))
	{
		if (is_bsh_cmd(fndcmd, params))
			return (fndcmd);
	}
	while (1)
	{
		if (!pthstr[j] || pthstr[j] == ':')
		{
			pat = bsh_dp_char(cpos, pthstr, j);
			if (!*pat)
				_bshstrgcat(pat, fndcmd);
			else
			{
				_bshstrgcat(pat, "/");
				_bshstrgcat(pat, fndcmd);
			}
			if (is_bsh_cmd(pat, params))
				return (pat);
			if (!pthstr[j])
				break;
			cpos = j;
		}
		j++;
	}
	return (NULL);
}
