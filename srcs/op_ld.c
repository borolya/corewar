#include "corewar.h"

unsigned int op_ld(t_game *game, t_carriage *car, t_op op)
{
	unsigned int    new_pc;
	int32_t      args[3];

	if (check_targ(game->arena, car, op, &new_pc) == -1)
		return (new_pc);
	args[0] = take_value_shift_pc(car->targ[0], game->arena, car, op);
	args[1] = take_value_shift_pc(car->targ[1], game->arena, car, op);
	if (args[1] < 0 || args[1] > 15)
		return (new_pc);
	if (args[0] == 0)
		car->carry = 0;
	else
		car->carry = 1;
	car->reg[args[1]] = args[0]; 
	return (new_pc);
}