#include "corewar.h"

unsigned int op_sti(t_val *val, t_game *game, t_carriage *car, t_op op)
{
	int32_t			args[3];
	unsigned int	new_pc;
	int				i;

	(void)val;
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
		    if (i != 0)
				args[i] = car->reg[args[i]];
		}
	}
	int_to_bytes(car->reg[args[0]], game->arena, car->save_pc + (args[1] + args[2]) % IDX_MOD, REG_SIZE);
	return (new_pc);
}