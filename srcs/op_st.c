#include "corewar.h"

unsigned int op_st(t_game *game, t_carriage *car, t_op op)
{
	unsigned int    new_pc;
	int32_t      args[3];
	int32_t      adr;

	if (check_targ(game->arena, car, op, &new_pc) == -1)
		return (new_pc);
	args[0] = take_value_shift_pc(car->targ[0], game->arena, &(car->pc), op);
	if (args[0] < 0 || args[0] > 15)
		return (new_pc);
	if (car->targ[1] == T_REG)
	{
		args[1] = take_value_shift_pc(T_REG, game->arena, &(car->pc), op);
		if (args[0] < 0 || args[0] > 15)
			return (new_pc);
		car->reg[args[1]] = car->reg[args[0]];
		return (new_pc);
	}
	adr = bytes_to_int(game->arena, car->pc, IND_SIZE);
	int_to_bytes(car->reg[args[0]], game->arena, adr, REG_SIZE);
	return (new_pc);
}