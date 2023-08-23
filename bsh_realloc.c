#include "simpleshell.h"

/**
 * _bshmemset - Populates memory with a constant byte value.
 * @m: The pointer to the memory area to be populated.
 * @byt: The byte value used for filling 'm'.
 * @amt_b: The total number of bytes to be filled.
 * Return: Returns 'm', a pointer to the memory area being populated.
 */
char *_bshmemset(char *m, unsigned int amt_b, char byt)
{
	unsigned int j;

	for (j = 0; j < amt_b; j++)
		m[j] = byt;
	return (m);
}

/**
 * bshfree - Releases memory occupied by a string array.
 * @q: The array of strings to be freed.
 */
void bshfree(char **q)
{
	char **b = q;

	if (!q)
		return;
	while (*q)
		free(*q++);
	free(b);
}

/**
 * _bshrealloc - Adjusts the size of a memory block
 *								previously allocated with malloc.
 * @pter: Pointer to the previous memory block allocated with malloc.
 * @oldsz: Byte size of the previous memory block.
 * @nwsz: Byte size of the new memory block.
 *
 * Return: Returns a pointer to the modified memory block.
 */
void *_bshrealloc(unsigned int oldsz, void *pter, unsigned int nwsz)
{
	char *q;

	if (!pter)
		return (malloc(nwsz));
	if (!nwsz)
		return (free(pter), NULL);
	if (nwsz == oldsz)
		return (pter);

	q = malloc(nwsz);
	if (!q)
		return (NULL);

	oldsz = oldsz < nwsz ? oldsz : nwsz;
	while (oldsz--)
		q[oldsz] = ((char *)pter)[oldsz];
	free(pter);
	return (q);
}
