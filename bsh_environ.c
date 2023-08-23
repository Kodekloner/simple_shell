#include "simpleshell.h"

/**
 * _bshenv - Displays the current environment's information.
 * @params: A structure that holds potential arguments. This structure is
 *          utilized to keep a consistent function prototype.
 * Return: It consistently returns 0.
 */
int _bshenv(params_t *params)
{
	bsh_prt_lstr(params->bsh_env);
	return (0);
}

/**
 * _bshgetenv - Retrieves the value of an environment variable.
 * @params: A structure holding potential arguments. Utilized for maintaining
 * @env_nm: Name of the environment variable.
 *
 * Return: The corresponding value.
 */
char *_bshgetenv(params_t *params, const char *env_nm)
{
	ll_t *nod = params->bsh_env;
	char *q;

	while (nod)
	{
		q = bsh_sw(nod->strg, env_nm);
		if (q && *q)
			return (q);
		nod = nod->next_node;
	}
	return (NULL);
}

/**
 * _setbshenv - Initializes a new bsh environment variable
 *							or modifies an existing one.
 * @params: A structure holding potential arguments. Employed for maintaining
 *        a consistent function prototype.
 *  Return: Always returns 0.
 */
int _setbshenv(params_t *params)
{
	if (params->arc != 3)
	{
		_bsheputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_bshsetenv(params, params->gtl_str[1], params->gtl_str[2]))
		return (0);
	return (1);
}

/**
 * _bshunsetenv - Deletes an environment variable.
 * @params: A structure holding potential arguments. Utilized for maintaining
 *        a consistent function prototype.
 * Return: Always returns 0.
 */
int _bshunsetenv(params_t *params)
{
	int j;

	if (params->arc == 1)
	{
		_bsheputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= params->arc; j++)
		_unsetbshenv(params, params->gtl_str[j]);

	return (0);
}

/**
 * bsh_pop_env - Populates an environment linked list.
 * @params: A structure holding potential arguments. Employed for maintaining
 *          a consistent function prototype.
 * Return: Always returns 0.
 */
int bsh_pop_env(params_t *params)
{
	ll_t *nod = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		bsh_nod_add_end(&nod, environ[j], 0);
	params->bsh_env = nod;
	return (0);
}
