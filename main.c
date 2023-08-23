#include "simpleshell.h"

/**
 * main - entry point for the shell program
 * @arg_c: argc (argument count) represent the number of command-line arguments
 * @arg_v: argv (argument vector) an array of pointers to those arguments
 *
 * Return: 1 for error, 0 for success
 */

int main(int arg_c, char **arg_v)
{
	params_t params[] = { PARAMS_INIT };
	int fdir = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdir)
			: "r" (fdir));

	if (arg_c == 2)
	{
		fdir = open(arg_v[1], O_RDONLY);
		if (fdir == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_bsheputs(arg_v[0]);
				_bsheputs(": 0: Can't open ");
				_bsheputs(arg_v[1]);
				_bsheputchar('\n');
				_bsheputchar(FLUSH_BUFF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		params->readfiledir = fdir;
	}
	bsh_pop_env(params);
	bsh_rd_hist(params);
	bsh(arg_v, params);
	return (EXIT_SUCCESS);
}
