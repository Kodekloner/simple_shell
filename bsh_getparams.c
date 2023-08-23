#include "simpleshell.h"

/**
 * bsh_clr_params - Initializes the params_t structure.
 * @params: Address of the structure.
 */
void bsh_clr_params(params_t *params)
{
	params->gtl_arg = NULL;
	params->gtl_str = NULL;
	params->curr_path = NULL;
	params->arc = 0;
}

/**
 * bsh_set_params - Sets up the params_t structure.
 * @params: Address of the structure instance.
 * @arv: Array of arguments.
 */
void bsh_set_params(params_t *params, char **arv)
{
	int j = 0;

	params->bsh_fname = arv[0];
	if (params->gtl_arg)
	{
		params->gtl_str = bshstrgtow(params->gtl_arg, " \t");
		if (!params->gtl_str)
		{
			params->gtl_str = malloc(sizeof(char *) * 2);
			if (params->gtl_str)
			{
				params->gtl_str[0] = _bshstrgdup(params->gtl_arg);
				params->gtl_str[1] = NULL;
			}
		}
		for (j = 0; params->gtl_str && params->gtl_str[j]; j++)
			;
		params->arc = j;

		bsh_rplc_alias(params);
		bsh_rplc_vars(params);
	}
}

/**
 * bsh_free_params - Releases memory occupied by fields
 *										in the params_t structure.
 * @params: Address of the structure.
 * @all_flds: Boolean indicating whether to free all fields (true or false).
 */
void bsh_free_params(params_t *params, int all_flds)
{
	bshfree(params->gtl_str);
	params->gtl_str = NULL;
	params->curr_path = NULL;
	if (all_flds)
	{
		if (!params->cmd_buff)
			free(params->gtl_arg);
		if (params->bsh_env)
			bsh_frlst(&(params->bsh_env));
		if (params->bsh_history)
			bsh_frlst(&(params->bsh_history));
		if (params->bsh_alias)
			bsh_frlst(&(params->bsh_alias));
		bshfree(params->environ);
			params->environ = NULL;
		bshbfree((void **)params->cmd_buff);
		if (params->readfiledir > 2)
			close(params->readfiledir);
		_bshputchar(FLUSH_BUFF);
	}
}
