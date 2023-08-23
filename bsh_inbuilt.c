#include "simpleshell.h"

/**
 * _bshexit - Terminates the bill shell.
 * @params: Structure containing parameters.
 * Return: Exits with a command status.
 * (0) if params.gtl_str[0] is not equal to "exit".
 */
int _bshexit(params_t *params)
{
	int chk_exit;

	if (params->gtl_str[1])
	{
		chk_exit = bsh_errstrgtoi(params->gtl_str[1]);
		if (chk_exit == -1)
		{
			params->cmd_status = 2;
			bsh_echo_err(params, "number not allowed: ");
			_bsheputs(params->gtl_str[1]);
			_bsheputchar('\n');
			return (1);
		}
		params->exit_err = bsh_errstrgtoi(params->gtl_str[1]);
		return (-2);
	}
	params->exit_err = -1;
	return (-2);
}

/**
 * _bshcd - Modifies the current directory of the process.
 * @params: A structure holding potential arguments, utilized for maintaining
 * a consistent func prototype.
 * Return: Always returns 0.
 */
int _bshcd(params_t *params)
{
	char *cwd, *fld, buff[1024];
	int chfld_rtn;

	cwd = getcwd(buff, 1024);
	if (!cwd)
		_bshputs("TODO: >>getcwd failure emsg here<<\n");
	if (!params->gtl_str[1])
	{
		fld = _bshgetenv(params, "HOME=");
		if (!fld)
			chfld_rtn =
				chdir((fld = _bshgetenv(params, "PWD=")) ? fld : "/");
		else
			chfld_rtn = chdir(fld);
	}
	else if (_bshstrgcmp(params->gtl_str[1], "-") == 0)
	{
		if (!_bshgetenv(params, "OLDPWD="))
		{
			_bshputs(cwd);
			_bshputchar('\n');
			return (1);
		}
		_bshputs(_bshgetenv(params, "OLDPWD=")), _bshputchar('\n');
		chfld_rtn =
			chdir((fld = _bshgetenv(params, "OLDPWD=")) ? fld : "/");
	}
	else
		chfld_rtn = chdir(params->gtl_str[1]);
	if (chfld_rtn == -1)
	{
		bsh_echo_err(params, "can't cd to ");
		_bsheputs(params->gtl_str[1]), _bsheputchar('\n');
	}
	else
	{
		_bshsetenv(params, "OLDPWD", _bshgetenv(params, "PWD="));
		_bshsetenv(params, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _bshhelp - Displays helpful information about the shell.
 * @params: A structure holding potential arguments, utilized for maintaining
 * a consistent func prototype.
 * Return: Always returns 0.
 */
int _bshhelp(params_t *params)
{
	char **params_array;

	params_array = params->gtl_str;
	_bshputs("help call works. Function not yet implemented \n");
	if (0)
		_bshputs(*params_array);
	return (0);
}
