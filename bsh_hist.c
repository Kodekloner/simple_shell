#include "simpleshell.h"

/**
 * bsh_get_hist_file - Retrieves the history file.
 * @params: Parameter structure.
 *
 * Return: A dynamically allocated string with the history file.
 */

char *bsh_get_hist_file(params_t *params)
{
	char *buff, *d;

	d = _bshgetenv(params, "HOME=");
	if (!d)
		return (NULL);
	buff = malloc(
		sizeof(char) * (_bshstrglen(d) + _bshstrglen(HISTORY_FILE) + 2)
	);

	if (!buff)
		return (NULL);
	buff[0] = 0;
	_bshstrgcpy(buff, d);
	_bshstrgcat(buff, "/");
	_bshstrgcat(buff, HISTORY_FILE);
	return (buff);
}

/**
 * bsh_wr_hist - Generates a new file or adds content to an existing file.
 * @params: The parameter structure.
 *
 * Return: Returns 1 upon successful operation, otherwise -1.
 */
int bsh_wr_hist(params_t *params)
{
	ssize_t fdir;
	char *fnm = bsh_get_hist_file(params);
	ll_t *nod = NULL;

	if (!fnm)
		return (-1);

	fdir = open(fnm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fnm);
	if (fdir == -1)
		return (-1);
	for (nod = params->bsh_history; nod; nod = nod->next_node)
	{
		_bshputsfdir(fdir, nod->strg);
		_bshputfdir(fdir, '\n');
	}
	_bshputfdir(fdir, FLUSH_BUFF);
	close(fdir);
	return (1);
}

/**
 * bsh_rd_hist - Retrieves history information from a file.
 * @params: The parameter structure.
 *
 * Return: Returns the history count upon successful operation, 0 otherwise.
 */
int bsh_rd_hist(params_t *params)
{
	int j, lst = 0, linecnt = 0;
	ssize_t fdir, readlen, fsz = 0;
	struct stat stt;
	char *buff = NULL, *fnm = bsh_get_hist_file(params);

	if (!fnm)
		return (0);

	fdir = open(fnm, O_RDONLY);
	free(fnm);
	if (fdir == -1)
		return (0);
	if (!fstat(fdir, &stt))
		fsz = stt.st_size;
	if (fsz < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsz + 1));
	if (!buff)
		return (0);
	readlen = read(fdir, buff, fsz);
	buff[fsz] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fdir);
	for (j = 0; j < fsz; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			bsh_bld_hist_list(params, buff + lst, linecnt++);
			lst = j + 1;
		}
	if (lst != j)
		bsh_bld_hist_list(params, buff + lst, linecnt++);
	free(buff);
	params->history_cnt = linecnt;
	while (params->history_cnt-- >= MAX_HISTORY)
		bsh_del_nod_at_idx(&(params->bsh_history), 0);
	bsh_renum_hist(params);
	return (params->history_cnt);
}

/**
 * bsh_bld_hist_list - Appends an entry to a linked list of history.
 * @params: A structure holding potential arguments, utilized for maintaining
 *					a consistent funct prototype.
 * @buff: The buffer containing the entry.
 * @linecnt: The count of history lines, referred to as history_cnt.
 *
 * Return: Always returns 0.
 */
int bsh_bld_hist_list(params_t *params, char *buff, int linecnt)
{
	ll_t *nod = NULL;

	if (params->bsh_history)
		nod = params->bsh_history;
	bsh_nod_add_end(&nod, buff, linecnt);

	if (!params->bsh_history)
		params->bsh_history = nod;
	return (0);
}

/**
 * bsh_renum_hist - Updates the numbering of the history
 *									linked list after modifications.
 * @params: A structure holding potential arguments, used for maintaining
 *					consistency in the funct prototype.
 * Return: The updated history count, referred to as the new history_cnt.
 */
int bsh_renum_hist(params_t *params)
{
	ll_t *nod = params->bsh_history;
	int j;

	j = 0;
	while (nod)
	{
		nod->number = j++;
		nod = nod->next_node;
	}
	return (params->history_cnt = j);
}

