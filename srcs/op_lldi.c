#include "corewar.h"

unsigned int op_ldi(t_game *game, t_carriage *car, t_op op)
{
	__uint32_t		args[3];
	unsigned int	new_pc;
	unsigned int	save_pc;
	int				i;

	if (check_targ(game->arena, car, op, &new_pc) != 0)
		return (new_pc);
	save_pc = car->pc;
	i = -1;
	while (++i < 3)
	{
		args[i] = take_value_shift_pc(car->targ[i], game->arena, &(car->pc), op);
		if (car->targ[i] == T_REG)
        {
            if (args[i] < 0 || args[i] > 15)
				return (-1);
		    else if (i != 2)
				args[i] = car->reg[args[i]];
		}
	}
	car->reg[args[2]] = bytes_to_int(game->arena, (save_pc + (args[0] + args[1])) % MEM_SIZE, REG_SIZE);
	return (new_pc);
}