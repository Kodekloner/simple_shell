#include "simpleshell.h"

/**
 * _get_bshenviron - Retrieves a copy of the string array
 *										representing our environ.
 * @params: A structure holding potential arguments. Employed to uphold
 *          a consistent func prototype.
 * Return: Always returns 0.
 */
char **_get_bshenviron(params_t *params)
{
	if (!params->environ || params->bsh_env_changed)
	{
		params->environ = bsh_ll_to_strg(params->bsh_env);
		params->bsh_env_changed = 0;
	}

	return (params->environ);
}

/**
 * _unsetbshenv - Deletes an environment variable.
 * @params: A structure holding potential arguments. Utilized for maintaining
 *        a consistent funct prototype.
 *  Return: Returns 1 upon successful deletion, 0 otherwise.
 * @vr: The string property of the environment variable.
 */
int _unsetbshenv(params_t *params, char *vr)
{
	ll_t *nod = params->bsh_env;
	size_t j = 0;
	char *q;

	if (!nod || !vr)
		return (0);

	while (nod)
	{
		q = bsh_sw(nod->strg, vr);
		if (q && *q == '=')
		{
			params->bsh_env_changed = bsh_del_nod_at_idx(&(params->bsh_env), j);
			j = 0;
			nod = params->bsh_env;
			continue;
		}
		nod = nod->next_node;
		j++;
	}
	return (params->bsh_env_changed);
}

/**
 * _bshsetenv - Creates a new environment variable or modifies an existing one.
 * @params: A structure holding potential arguments. Employed for maintaining
 *        a consistent funct prototype.
 * @vr: The string property of the environment variable.
 * @val: The string value of the environment variable.
 *  Return: Always returns 0.
 */
int _bshsetenv(params_t *params, char *vr, char *val)
{
	char *buff = NULL;
	ll_t *nod;
	char *q;

	if (!vr || !val)
		return (0);

	buff = malloc(_bshstrglen(vr) + _bshstrglen(val) + 2);
	if (!buff)
		return (1);
	_bshstrgcpy(buff, vr);
	_bshstrgcat(buff, "=");
	_bshstrgcat(buff, val);
	nod = params->bsh_env;
	while (nod)
	{
		q = bsh_sw(nod->strg, vr);
		if (q && *q == '=')
		{
			free(nod->strg);
			nod->strg = buff;
			params->bsh_env_changed = 1;
			return (0);
		}
		nod = nod->next_node;
	}
	bsh_nod_add_end(&(params->bsh_env), buff, 0);
	free(buff);
	params->bsh_env_changed = 1;
	return (0);
}
