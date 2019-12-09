#include "corewar.h"

void cycles_before_execution(t_carriage *car, uint8_t oper)
{
	
	int i;

	i = 0;
	while (i < 18)
	{
		if (op_tab[i].code == oper)
			car->hookbefexe = op_tab[i].wait_cycles;	
		i++;
	}
/*
	if (oper == 0x10)
		car->hookbefexe = 2;
	else if (oper == 0x02 || oper == 0x3)
		car->hookbefexe = 5;
	else if (oper == 0x06 || oper == 0x07 || oper == 0x08)
		car->hookbefexe = 6;
	else if (oper == 0x01 || oper == 0x04 || oper == 0x05 || oper == 0x0d)
		car->hookbefexe = 10;
	else if (oper == 0x09)
		car->hookbefexe = 20;
	else if (oper == 0x0a || oper == 0x0b)
		car->hookbefexe = 25;
	else if (oper == 0x0e)
		car->hookbefexe = 50;
	else if (oper == 0x0c)
		car->hookbefexe = 800;
	else if (oper == 0x0f)
		car->hookbefexe = 1000;
	else
		car->hookbefexe = 0;
		*/
	car->operation = oper;
}

void addition_operation(t_game *game, t_carriage *car, uint8_t operation)
{
	if (operation == 0x09)
		car->pc = op_zjmp(game, car, op_tab[operation - 1]);
	else if (operation == 0x0a)
		car->pc = op_ldi(game, car, op_tab[operation - 1]);
	else if (operation == 0x0b)
		car->pc = op_sti(game, car, op_tab[operation - 1]);
	else if (operation == 0x0c)
		car->pc = op_fork(game, car, op_tab[operation - 1]);
	else if (operation == 0x0d)
		car->pc = op_lld(game, car, op_tab[operation - 1]);
	else if (operation == 0x0e)
		car->pc = op_lldi(game, car, op_tab[operation - 1]);
	else if (operation == 0x0f)
		car->pc = op_lfork(game, car, op_tab[operation - 1]);
	else if (operation == 0x10)
		car->pc = op_aff(game, car, op_tab[operation - 1]);
	else
		car->pc = (car->pc + 1) % MEM_SIZE;
	
} 

void operation(t_game *game, t_carriage *car, uint8_t operation)
{
	/*
	int i;

	i = 0;
	while (i < 18)
	{
		if (op_tab[i].code == operation)
			op_tab[i].func(game, car);
	}
	*/
	
	if (operation == 0x01)
		car->pc = op_live(game, car, op_tab[operation - 1]);
	else if (operation == 0x02)
		car->pc = op_ld(game, car, op_tab[operation - 1]);
	else if (operation == 0x03)
		car->pc = op_st(game, car, op_tab[operation - 1]);
	else if (operation == 0x04)
		car->pc = op_add(game, car, op_tab[operation - 1]);
	else if (operation == 0x05)
		car->pc = op_sub(game, car, op_tab[operation - 1]);
	else if (operation == 0x06)
		car->pc = op_and(game, car, op_tab[operation - 1]);
	else if (operation == 0x07)
		car->pc = op_or(game, car, op_tab[operation - 1]);
	else if (operation == 0x08)
		car->pc = op_xor(game, car, op_tab[operation - 1]);
	else
		addition_operation(game, car, operation);
}