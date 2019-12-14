#include "corewar.h"

unsigned int op_lld(t_val *val, t_game *game, t_carriage *car, t_op op)
{
	int32_t args[3];
	unsigned int new_pc;

	(void)val;	
	if (check_targ(game->arena, car, op, &new_pc) != 0)
		return (new_pc);
	args[0] = take_value_shift_pc(car->targ[0], game->arena, car, op);
    args[1] = take_value_shift_pc(car->targ[1], game->arena, car, op);
	if (args[1] < 0 || args[1] > 15)
       	return (new_pc);
	car->reg[args[1]] = args[0]; // правильно записывает????
	return (new_pc);
}