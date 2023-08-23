#include "simpleshell.h"

/**
 * bsh_nod_add - Inserts a node at the beginning of the list.
 * @hd_node: Address of a pointer to the head node.
 * @strg: The string field of the new node.
 * @node: The node index used for history.
 *
 * Return: Size of the list.
 */
ll_t *bsh_nod_add(ll_t **hd_node, const char *strg, int node)
{
	ll_t *nw_hd_node;

	if (!hd_node)
		return (NULL);
	nw_hd_node = malloc(sizeof(ll_t));
	if (!nw_hd_node)
		return (NULL);
	_bshmemset((void *)nw_hd_node, sizeof(ll_t), 0);
	nw_hd_node->number = node;
	if (strg)
	{
		nw_hd_node->strg = _bshstrgdup(strg);
		if (!nw_hd_node->strg)
		{
			free(nw_hd_node);
			return (NULL);
		}
	}
	nw_hd_node->next_node = *hd_node;
	*hd_node = nw_hd_node;
	return (nw_hd_node);
}

/**
 * bsh_nod_add_end - Appends a node to the end of the list.
 * @hd_node: Address of a pointer to the head node.
 * @strg: The string field of the new node.
 * @node: The node index used for history.
 *
 * Return: Size of the list.
 */
ll_t *bsh_nod_add_end(ll_t **hd_node, const char *strg, int node)
{
	ll_t *nw_nod, *nod;

	if (!hd_node)
		return (NULL);

	nod = *hd_node;
	nw_nod = malloc(sizeof(ll_t));
	if (!nw_nod)
		return (NULL);
	_bshmemset((void *)nw_nod, sizeof(ll_t), 0);
	nw_nod->number = node;
	if (strg)
	{
		nw_nod->strg = _bshstrgdup(strg);
		if (!nw_nod->strg)
		{
			free(nw_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next_node)
			nod = nod->next_node;
		nod->next_node = nw_nod;
	}
	else
		*hd_node = nw_nod;
	return (nw_nod);
}

/**
 * bsh_prt_lstr - Outputs only the 'str' element of a linked list (ll_t).
 * @fstnd: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t bsh_prt_lstr(const ll_t *fstnd)
{
	size_t j = 0;

	while (fstnd)
	{
		_bshputs(fstnd->strg ? fstnd->strg : "(nil)");
		_bshputs("\n");
		fstnd = fstnd->next_node;
		j++;
	}
	return (j);
}

/**
 * bsh_del_nod_at_idx - Removes a node at the specified index.
 * @fstnd: Address of a pointer to the first node.
 * @idx: Index of the node to be deleted.
 *
 * Return: 1 upon success, 0 upon failure.
 */
int bsh_del_nod_at_idx(ll_t **fstnd, unsigned int idx)
{
	ll_t *nod, *pre_nod;
	unsigned int j = 0;

	if (!fstnd || !*fstnd)
		return (0);

	if (!idx)
	{
		nod = *fstnd;
		*fstnd = (*fstnd)->next_node;
		free(nod->strg);
		free(nod);
		return (1);
	}
	nod = *fstnd;
	while (nod)
	{
		if (j == idx)
		{
			pre_nod->next_node = nod->next_node;
			free(nod->strg);
			free(nod);
			return (1);
		}
		j++;
		pre_nod = nod;
		nod = nod->next_node;
	}
	return (0);
}

/**
 * bsh_frlst - Releases memory occupied by all nodes of a list.
 * @hd_pter: Address of a pointer to the head node.
 *
 * Return: Void.
 */
void bsh_frlst(ll_t **hd_pter)
{
	ll_t *nod, *nxt_nod, *hd;

	if (!hd_pter || !*hd_pter)
		return;

	hd = *hd_pter;
	nod = hd;
	while (nod)
	{
		nxt_nod = nod->next_node;
		free(nod->strg);
		free(nod);
		nod = nxt_nod;
	}
	*hd_pter = NULL;
}
