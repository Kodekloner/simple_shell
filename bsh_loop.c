#include "simpleshell.h"

/**
 * bsh - Primary shell loop.
 * @params: The parameter and return parameter structure.
 * @arg_v: The argument vector from the main() function.
 *
 * Return: Returns 0 upon success, 1 on error, or an error code.
 */
int bsh(char **arg_v, params_t *params)
{
	ssize_t t = 0;
	int inbuilt_rtn = 0;

	while (t != -1 && inbuilt_rtn != -2)
	{
		bsh_clr_params(params);
		if (bsh_interactive_mode(params))
			_bshputs("$ ");
		_bsheputchar(FLUSH_BUFF);
		t = _bsh_input(params);
		if (t != -1)
		{
			bsh_set_params(params, arg_v);
			inbuilt_rtn = bsh_inbuilt_fd(params);
			if (inbuilt_rtn == -1)
				bsh_cmd_fd(params);
		}
		else if (bsh_interactive_mode(params))
			_bshputchar('\n');
		bsh_free_params(params, 0);
	}
	bsh_wr_hist(params);
	bsh_free_params(params, 1);
	if (!bsh_interactive_mode(params) && params->cmd_status)
		exit(params->cmd_status);
	if (inbuilt_rtn == -2)
	{
		if (params->exit_err == -1)
			exit(params->cmd_status);
		exit(params->exit_err);
	}
	return (inbuilt_rtn);
}

/**
 * bsh_inbuilt_fd - Locates a built-in command.
 * @params: The parameter and return parameter structure.
 *
 * Return: -1 if the built-in command is not found,
 *	0 if the in-built command is executed successfully,
 *	1 if the in-built command is found but not successful,
 *	2 if the in-built command signals an exit().
 */
int bsh_inbuilt_fd(params_t *params)
{
	int j, inbuilt_rtn = -1;
	inbuilt_tbl inbuilttbl[] = {
			{"exit", _bshexit},
			{"env", _bshenv},
			{"help", _bshhelp},
			{"history", _bshhistory},
			{"setenv", _setbshenv},
			{"unsetenv", _bshunsetenv},
			{"cd", _bshcd},
			{"alias", _bshalias},
			{NULL, NULL}
	};

	for (j = 0; inbuilttbl[j].inbuilt_type; j++)
		if (_bshstrgcmp(params->gtl_str[0], inbuilttbl[j].inbuilt_type) == 0)
		{
			params->err_cnt++;
			inbuilt_rtn = inbuilttbl[j].inbuilt_func(params);
			break;
		}
	return (inbuilt_rtn);
}

/**
 * bsh_cmd_fd - Locates a command in the PATH.
 * @params: The parameter and return parameter structure.
 *
 * Return: Void.
 */
void bsh_cmd_fd(params_t *params)
{
	char *pat = NULL;
	int j, l;

	params->curr_path = params->gtl_str[0];
	if (params->flaged_line == 1)
	{
		params->err_cnt++;
		params->flaged_line = 0;
	}
	for (j = 0, l = 0; params->gtl_arg[j]; j++)
	{
		if (!bsh_is_str_delim(" \t\n", params->gtl_arg[j]))
		{
			l++;
		}
	}
	if (!l)
		return;

	pat = bsh_fi_path(_bshgetenv(params, "PATH="), params, params->gtl_str[0]);
	if (pat)
	{
		params->curr_path = pat;
		bsh_cmd_fk(params);
	}
	else
	{
		if ((bsh_interactive_mode(params) || _bshgetenv(params, "PATH=")
					|| params->gtl_str[0][0] == '/')
					&& is_bsh_cmd(params->gtl_str[0], params))
			bsh_cmd_fk(params);
		else if (*(params->gtl_arg) != '\n')
		{
			params->cmd_status = 127;
			bsh_echo_err(params, "not found\n");
		}
	}
}

/**
 * bsh_cmd_fk - Spawns a new process using fork and exec to run a command.
 * @params: The parameter and return parameter structure.
 *
 * Return: Void.
 */
void bsh_cmd_fk(params_t *params)
{
	pid_t chld_pid;

	chld_pid = fork();
	if (chld_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (chld_pid == 0)
	{
		if (
			execve(params->curr_path, params->gtl_str, _get_bshenviron(params)) == -1
		)
		{
			bsh_free_params(params, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(params->cmd_status));
		if (WIFEXITED(params->cmd_status))
		{
			params->cmd_status = WEXITSTATUS(params->cmd_status);
			if (params->cmd_status == 126)
				bsh_echo_err(params, "Permission denied\n");
		}
	}
}
