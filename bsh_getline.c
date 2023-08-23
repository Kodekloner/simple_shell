#include "simpleshell.h"

/**
 * input_buf - Buffers chained commands.
 * @params: Parameter structure.
 * @buff: Address of the buffer.
 * @ln: Address of the length variable.
 *
 * Return: Number of bytes read.
 */
ssize_t input_buf(params_t *params, char **buff, size_t *ln)
{
	ssize_t t = 0;
	size_t ln_q = 0;

	if (!*ln)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, bsh_sgintHdler);
#if USING_GET_LINE
		t = getline(buff, &ln_q, stdin);
#else
		t = _bshgetline(params, buff, &ln_q);
#endif
		if (t > 0)
		{
			if ((*buff)[t - 1] == '\n')
			{
				(*buff)[t - 1] = '\0';
				t--;
			}
			params->flaged_line = 1;
			bsh_rmv_cmts(*buff);
			bsh_bld_hist_list(params, *buff, params->history_cnt++);
			{
				*ln = t;
				params->cmd_buff = buff;
			}
		}
	}
	return (t);
}

/**
 * _bsh_input - Retrieves a line excluding the newline character.
 * @params: Parameter structure.
 *
 * Return: Number of bytes read.
 */
ssize_t _bsh_input(params_t *params)
{
	static char *buff;
	static size_t j, z, ln;
	ssize_t t = 0;
	char **buff_q = &(params->gtl_arg), *q;

	_bshputchar(FLUSH_BUFF);
	t = input_buf(params, &buff, &ln);
	if (t == -1)
		return (-1);

	if (ln)
	{
		z = j;
		q = buff + j;

		bsh_chk_chn(params, buff, &z, j, ln);
		while (z < ln)
		{
			if (bsh_is_chn(params, buff, &z))
				break;
			z++;
		}

		j = z + 1;
		if (j >= ln)
		{
			j = ln = 0;
			params->cmd_buff_types = BSH_NORM_CMD;
		}

		*buff_q = q;
		return (_bshstrglen(q));
	}

	*buff_q = buff;
	return (t);
}

/**
 * read_buf - Reads data into a buffer.
 * @params: Parameter structure.
 * @buff: The buffer to read into.
 * @sz: The size of the buffer.
 *
 * Return: The result 'r'.
 */
ssize_t read_buf(params_t *params, char *buff, size_t *sz)
{
	ssize_t t = 0;

	if (*sz)
		return (0);
	t = read(params->readfiledir, buff, FETCH_BUFF_SIZE);
	if (t >= 0)
		*sz = t;
	return (t);
}

/**
 * _bshgetline - Retrieves the next line of input from STDIN.
 * @params: Parameter structure.
 * @pter: Address of a pointer to a buffer, which can be preallocated or NULL.
 * @len: Size of the preallocated buffer pointed to by 'pter' if it's not NULL.
 *
 * Return: The resulting 's'.
 */
int _bshgetline(params_t *params, char **pter, size_t *len)
{
	static char buff[FETCH_BUFF_SIZE];
	static size_t j, ln;
	size_t l;
	ssize_t t = 0, strg = 0;
	char *q = NULL, *new_q = NULL, *ch;

	q = *pter;
	if (q && len)
		strg = *len;
	if (j == ln)
		j = ln = 0;

	t = read_buf(params, buff, &ln);
	if (t == -1 || (t == 0 && ln == 0))
		return (-1);

	ch = _bshstrgchr('\n', buff + j);
	l = ch ? 1 + (unsigned int)(ch - buff) : ln;
	new_q = _bshrealloc(strg, q, strg ? strg + l : l + 1);
	if (!new_q) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (strg)
		_bshstrgncat(new_q, l - j, buff + j);
	else
		_bshstrgncpy(new_q, l - j + 1, buff + j);

	strg += l - j;
	j = l;
	q = new_q;

	if (len)
		*len = strg;
	*pter = q;
	return (strg);
}

/**
 * bsh_sgintHdler - Handles blocking of Ctrl-C.
 * @sgnum: The signal number.
 *
 * Return: Void.
 */
void bsh_sgintHdler(__attribute__((unused))int sgnum)
{
	_bshputs("\n");
	_bshputs("$ ");
	_bshputchar(FLUSH_BUFF);
}
