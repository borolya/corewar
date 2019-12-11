#include "corewar.h"

void int_to_bytes(int numb, __uint8_t arena[], int pc, int size)
{
	// int i;
	void *p;
	// i = size;
	// while (--i > -1)
	// {
	// 	arena[(pc + i) % MEM_SIZE] = numb % 256;
	// 	numb = numb / 256;
	// }
	p = &numb;
	if (size == 4)
	{
		arena[pc % MEM_SIZE] = *(uint8_t*)(p + 3);
		arena[pc % MEM_SIZE] = *(uint8_t*)(p + 2);
		arena[pc % MEM_SIZE] = *(uint8_t*)(p + 1);
		arena[pc % MEM_SIZE] = *(uint8_t*)(p);
	}
	else 
		ft_error("ERROR IN INT_TO_BYTE\n");

}

int bytes_to_int(uint8_t arena[], int pc, int size)
{
	int			numb;
	void		*p;
	int16_t double_byte;

	numb = 0;
	if (size == 1)
		numb = arena[pc % MEM_SIZE];
	else if (size == 2)
	{
		p = &double_byte;
		*(int16_t*)(p  + 1) = arena[pc % MEM_SIZE];
		*(int16_t*)p = arena[(pc + 1) % MEM_SIZE];
		numb = double_byte;
	}
	else if (size == 4)
	{
		p = &numb;
		*(int*)(p + 3) = arena[pc % MEM_SIZE];
		*(int*)(p + 2) = arena[(pc + 1) % MEM_SIZE];
		*(int*)(p + 1) = arena[(pc + 2) % MEM_SIZE];
		*(int*)(p) = arena[(pc + 3) % MEM_SIZE];
	}
	else
		ft_error("bad byte\n");
	ft_printf("byte to int = %d\n", numb);
	return (numb);
}


/*
int bytes_to_int(uint8_t arena[], int pc, int size)
{
	unsigned int unumb;
	int numb;
	//int *p;
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

	unumb = 0;
	i = 0;
	while (i < size)
	{
		unumb = unumb * 256 + arena[(pc + i) % MEM_SIZE];
		i++; 
	}
	if (size == 4 && unumb > 2147483647)
		numb = unumb
	numb = - numb + size 
	return (numb); //
}
*/	