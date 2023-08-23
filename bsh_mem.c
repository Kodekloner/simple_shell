#include "simpleshell.h"

/**
 * bshbfree - Releases memory pointed to by a pointer
 *						and sets the address to NULL.
 * @pter: Address of the pointer to be freed.
 *
 * Return: Returns 1 if memory is freed, otherwise 0.
 */
int bshbfree(void **pter)
{
	if (pter && *pter)
	{
		free(*pter);
		*pter = NULL;
		return (1);
	}
	return (0);
}
