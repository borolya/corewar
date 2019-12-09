#include "corewar.h"

void int_to_bytes(uint32_t numb, __uint8_t arena[], int pc, int size)
{
	int i;

	i = size;
	while (--i > -1)
	{
		arena[(pc + i) % MEM_SIZE] = numb % 256;
		numb = numb / 256;
	}
}

int bytes_to_int(uint8_t arena[], int pc, int size)
{
	unsigned int numb;
	int *p;
	int i;

	*p = &numb;
	i = 0;
	while (i < size && i < 4)
	{
		ft_memcpy(p + i, arena[(pc + i) % MEM_SIZE], 1);
		size++;
		i++;
	}
	return (numb);
	
/*
	numb = 0;
	i = 0;
	while (i < size)
	{
		numb = numb * 256 + arena[(pc + i) % MEM_SIZE];
		i++; 
	}
	numb = - numb + size 
	return (numb); //
*/
}