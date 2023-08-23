#include "simpleshell.h"

/**
 * bsh_lst_len - Calculates the length of a linked list.
 * @fstnd: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t bsh_lst_len(const ll_t *fstnd)
{
	size_t j = 0;

	while (fstnd)
	{
		fstnd = fstnd->next_node;
		j++;
	}
	return (j);
}

/**
 * bsh_ll_to_strg - Converts the list of 'strg' elements
 *									into an array of strings.
 * @fstnd: Pointer to the first node.
 *
 * Return: Array of strings.
 */
char **bsh_ll_to_strg(ll_t *fstnd)
{
	ll_t *nod = fstnd;
	size_t j = bsh_lst_len(fstnd), z;
	char **strgs;
	char *strg;

	if (!fstnd || !j)
		return (NULL);
	strgs = malloc(sizeof(char *) * (j + 1));
	if (!strgs)
		return (NULL);
	for (j = 0; nod; nod = nod->next_node, j++)
	{
		strg = malloc(_bshstrglen(nod->strg) + 1);
		if (!strg)
		{
			for (z = 0; z < j; z++)
				free(strgs[z]);
			free(strgs);
			return (NULL);
		}

		strg = _bshstrgcpy(strg, nod->strg);
		strgs[j] = strg;
	}
	strgs[j] = NULL;
	return (strgs);
}


/**
 * _bsh_prt_lst - Displays all elements of a linked list (ll_t).
 * @fstnd: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t _bsh_prt_lst(const ll_t *fstnd)
{
	size_t j = 0;

	while (fstnd)
	{
		_bshputs(bsh_conv_num(fstnd->number, 10, 0));
		_bshputchar(':');
		_bshputchar(' ');
		_bshputs(fstnd->strg ? fstnd->strg : "(nil)");
		_bshputs("\n");
		fstnd = fstnd->next_node;
		j++;
	}
	return (j);
}

/**
 * bsh_nod_sw - Locates a node whose string starts with a specified prefix.
 * @nod: Pointer to the list head.
 * @regstr: String to be matched as the prefix.
 * @ch: The character to match after the prefix.
 *
 * Return: The matching node or NULL if not found.
 */
ll_t *bsh_nod_sw(ll_t *nod, char *regstr, char ch)
{
	char *q = NULL;

	while (nod)
	{
		q = bsh_sw(nod->strg, regstr);
		if (q && ((ch == -1) || (*q == ch)))
			return (nod);
		nod = nod->next_node;
	}
	return (NULL);
}

/**
 * bsh_nod_idx - Retrieves the index of a node in the list.
 * @lstnd: Pointer to the list head.
 * @nod: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t bsh_nod_idx(ll_t *lstnd, ll_t *nod)
{
	size_t j = 0;

	while (lstnd)
	{
		if (lstnd == nod)
			return (j);
		lstnd = lstnd->next_node;
		j++;
	}
	return (-1);
}
