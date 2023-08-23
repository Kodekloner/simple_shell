#include "simpleshell.h"

/**
 * bsh_is_chn - Determines if the current character in the
 *							buffer is a chaining delimiter.
 * @params: The parameter structure.
 * @buff: The character buffer.
 * @pos: Address of the current position in the buffer.
 *
 * Return: Returns 1 if the character is a chaining delimiter, 0 otherwise.
 */
int bsh_is_chn(params_t *params, char *buff, size_t *pos)
{
	size_t z = *pos;

	if (buff[z] == '|' && buff[z + 1] == '|')
	{
		buff[z] = 0;
		z++;
		params->cmd_buff_types = BSH_OR_CMD;
	}
	else if (buff[z] == '&' && buff[z + 1] == '&')
	{
		buff[z] = 0;
		z++;
		params->cmd_buff_types = BSH_AND_CMD;
	}
	else if (buff[z] == ';')
	{
		buff[z] = 0;
		params->cmd_buff_types = BSH_CHAIN_CMD;
	}
	else
		return (0);
	*pos = z;
	return (1);
}

/**
 * bsh_chk_chn - Checks whether chaining should continue
 *								based on the last command status.
 * @params: The parameter structure.
 * @buff: The character buffer.
 * @pos: Address of the current position in the buffer.
 * @stbuff: Starting position in the buffer.
 * @ln: Length of the buffer.
 *
 * Return: Void.
 */
void bsh_chk_chn(
	params_t *params, char *buff, size_t *pos, size_t stbuff, size_t ln
)
{
	size_t z = *pos;

	if (params->cmd_buff_types == BSH_AND_CMD)
	{
		if (params->cmd_status)
		{
			buff[stbuff] = 0;
			z = ln;
		}
	}
	if (params->cmd_buff_types == BSH_OR_CMD)
	{
		if (!params->cmd_status)
		{
			buff[stbuff] = 0;
			z = ln;
		}
	}

	*pos = z;
}

/**
 * bsh_rplc_alias - Substitutes aliases in the tokenized string.
 * @params: The parameter structure.
 *
 * Return: Returns 1 if replacements are made, 0 otherwise.
 */
int bsh_rplc_alias(params_t *params)
{
	int j;
	ll_t *nod;
	char *pos;

	for (j = 0; j < 10; j++)
	{
		nod = bsh_nod_sw(params->bsh_alias, params->gtl_str[0], '=');
		if (!nod)
			return (0);
		free(params->gtl_str[0]);
		pos = _bshstrgchr('=', nod->strg);
		if (!pos)
			return (0);
		pos = _bshstrgdup(pos + 1);
		if (!pos)
			return (0);
		params->gtl_str[0] = pos;
	}
	return (1);
}

/**
 * bsh_rplc_vars - Substitutes variables in the tokenized string.
 * @params: The parameter structure.
 *
 * Return: Returns 1 if replacements are made, 0 otherwise.
 */
int bsh_rplc_vars(params_t *params)
{
	int j = 0;
	ll_t *nod;

	for (j = 0; params->gtl_str[j]; j++)
	{
		if (params->gtl_str[j][0] != '$' || !params->gtl_str[j][1])
			continue;

		if (!_bshstrgcmp(params->gtl_str[j], "$?"))
		{
			bsh_rplc_strg(&(params->gtl_str[j]),
					_bshstrgdup(bsh_conv_num(params->cmd_status, 10, 0)));
			continue;
		}
		if (!_bshstrgcmp(params->gtl_str[j], "$$"))
		{
			bsh_rplc_strg(&(params->gtl_str[j]),
					_bshstrgdup(bsh_conv_num(getpid(), 10, 0)));
			continue;
		}
		nod = bsh_nod_sw(params->bsh_env, &params->gtl_str[j][1], '=');
		if (nod)
		{
			bsh_rplc_strg(&(params->gtl_str[j]),
					_bshstrgdup(_bshstrgchr('=', nod->strg) + 1));
			continue;
		}
		bsh_rplc_strg(&params->gtl_str[j], _bshstrgdup(""));

	}
	return (0);
}

/**
 * bsh_rplc_strg - Replaces a specified old string with a new one.
 * @odstrg: Address of the old string.
 * @nwstrg: The new string.
 *
 * Return: Returns 1 if the replacement is successful, 0 otherwise.
 */
int bsh_rplc_strg(char **odstrg, char *nwstrg)
{
	free(*odstrg);
	*odstrg = nwstrg;
	return (1);
}
