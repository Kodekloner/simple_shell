#include "simpleshell.h"

/**
 * bsh_errstrgtoi - Converts a string to an integer.
 * @strg: The string to be converted.
 * Return: Returns 0 if no numbers are found in the string,
 *       the converted number otherwise. Returns -1 in case of an error.
 */
int bsh_errstrgtoi(char *strg)
{
	int j = 0;
	unsigned long int res = 0;

	if (*strg == '+')
		strg++;
	for (j = 0;  strg[j] != '\0'; j++)
	{
		if (strg[j] >= '0' && strg[j] <= '9')
		{
			res *= 10;
			res += (strg[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * bsh_echo_err - Displays an error message.
 * @params: The parameter and return parameter structure.
 * @spec_err: A string containing the specified error type.
 * Return: Returns 0 if no numbers are in the string,
 *        otherwise the converted number. Returns -1 in case of an error.
 */
void bsh_echo_err(params_t *params, char *spec_err)
{
	_bsheputs(params->bsh_fname);
	_bsheputs(": ");
	bsh_echo_d(params->err_cnt, STDERR_FILENO);
	_bsheputs(": ");
	_bsheputs(params->gtl_str[0]);
	_bsheputs(": ");
	_bsheputs(spec_err);
}

/**
 * bsh_echo_d - This function prints a decimal (integer) number in base 10.
 * @in: The input integer.
 * @fdir: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int bsh_echo_d(int in, int fdir)
{
	int (*__bshputchar)(char) = _bshputchar;
	int j, cnt = 0;
	unsigned int _abst_, curr;

	if (fdir == STDERR_FILENO)
		__bshputchar = _bsheputchar;
	if (in < 0)
	{
		_abst_ = -in;
		__bshputchar('-');
		cnt++;
	}
	else
		_abst_ = in;
	curr = _abst_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abst_ / j)
		{
			__bshputchar('0' + curr / j);
			cnt++;
		}
		curr %= j;
	}
	__bshputchar('0' + curr);
	cnt++;

	return (cnt);
}

/**
 * bsh_conv_num -  Conversion function similar to 'itoa'.
 * @number: The number to be converted.
 * @bs: The base for conversion.
 * @flgs: Flags related to the arguments.
 *
 * Return: Returns the resulting string.
 */
char *bsh_conv_num(long int number, int bs, int flgs)
{
	static char *arr;
	static char buff[50];
	char sgn = 0;
	char *p;
	unsigned long num = number;

	if (!(flgs & TO_UNSIGNED) && number < 0)
	{
		num = -number;
		sgn = '-';

	}
	arr = flgs & TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do	{
		*--p = arr[num % bs];
		num /= bs;
	} while (num != 0);

	if (sgn)
		*--p = sgn;
	return (p);
}

/**
 * bsh_rmv_cmts - This function replaces the first occurrence of '#' with '\0'.
 * @buff: The address of the string to be modified.
 *
 * Return: Always returns 0.
 */
void bsh_rmv_cmts(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if ((!j || buff[j - 1] == ' ') && buff[j] == '#')
		{
			buff[j] = '\0';
			break;
		}
}
