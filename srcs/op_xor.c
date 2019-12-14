#include "corewar.h"

unsigned int op_xor(t_game *game, t_carriage *car, t_op op)
{
    unsigned int new_pc;
    int32_t args[3];
    int i;
    int32_t xor;

    if (check_targ(game->arena, car, op, &new_pc) == -1)
		return (new_pc);
    i = -1;
    while (++i < 3)
	{
		args[i] = take_value_shift_pc(car->targ[i], game->arena, car, op);
		if (car->targ[i] == T_REG)
        {
            if (args[i] < 0 || args[i] > 15)
				return (new_pc);
		    else if (i != 2)
				args[i] = car->reg[args[i]];
		}
	}
    xor = args[0] ^ args[1];
    if (xor == 0)
        car->carry = 0;
    else
        car->carry = 1;
    car->reg[args[2]] = xor;
    return (new_pc);
}