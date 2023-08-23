#include "simpleshell.h"

/**
 * _bshhistory - Presents the bsh_history list, showing one command per line,
 *              each accompanied by line numbers, commencing at 0.
 * @params: A structure holding potential arguments, utilized for maintaining
 *        a consistent funct prototype.
 *  Return: Always returns 0.
 */
int _bshhistory(params_t *params)
{
	_bsh_prt_lst(params->bsh_history);
	return (0);
}

/**
 * unset_alias - Assigns an alias to a string.
 * @params: Parameter structure.
 * @strg: The string representing the alias.
 *
 * Return: Returns 0 upon success, 1 on error.
 */
int unset_alias(params_t *params, char *strg)
{
	char *q, ch;
	int rtn;

	q = _bshstrgchr('=', strg);
	if (!q)
		return (1);
	ch = *q;
	*q = 0;
	rtn = bsh_del_nod_at_idx(&(params->bsh_alias),
		bsh_nod_idx(params->bsh_alias, bsh_nod_sw(params->bsh_alias, strg, -1)));
	*q = ch;
	return (rtn);
}

/**
 * set_alias - Associates an alias with a string.
 * @params: Parameter structure.
 * @strg: The string denoting the alias.
 *
 * Return: Returns 0 upon success, 1 on error.
 */
int set_alias(params_t *params, char *strg)
{
	char *q;

	q = _bshstrgchr('=', strg);
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(params, strg));

	unset_alias(params, strg);
	return (bsh_nod_add_end(&(params->bsh_alias), strg, 0) == NULL);
}

/**
 * print_alias - Displays an alias string.
 * @nod: The alias node.
 *
 * Return: Returns 0 upon success, 1 on error.
 */
int print_alias(ll_t *nod)
{
	char *q = NULL, *j = NULL;

	if (nod)
	{
		q = _bshstrgchr('=', nod->strg);
		for (j = nod->strg; j <= q; j++)
		_bshputchar(*j);
		_bshputchar('\'');
		_bshputs(q + 1);
		_bshputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _bshalias - Emulates the behavior of the alias built-in
 *							(refer to 'man alias').
 * @params: A structure holding potential arguments, employed for maintaining
 *          a consistent func prototype.
 *  Return: Always returns 0.
 */
int _bshalias(params_t *params)
{
	int j = 0;
	char *q = NULL;
	ll_t *nod = NULL;

	if (params->arc == 1)
	{
		nod = params->bsh_alias;
		while (nod)
		{
			print_alias(nod);
			nod = nod->next_node;
		}
		return (0);
	}
	for (j = 1; params->gtl_str[j]; j++)
	{
		q = _bshstrgchr('=', params->gtl_str[j]);
		if (q)
			set_alias(params, params->gtl_str[j]);
		else
			print_alias(bsh_nod_sw(params->bsh_alias, params->gtl_str[j], '='));
	}

	return (0);
}
