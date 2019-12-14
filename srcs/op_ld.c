#include "corewar.h"

unsigned int op_ld(t_val *val, t_game *game, t_carriage *car, t_op op)
{
	unsigned int	new_pc;
	int32_t			args[3];

	if (check_targ(game->arena, car, op, &new_pc) == -1)
		return (new_pc);
	args[0] = take_value_shift_pc(car->targ[0], game->arena, car, op);
	args[1] = take_value_shift_pc(car->targ[1], game->arena, car, op);
	// printf("-->> %d \n",args[0]);
	// printf("-->> r%d \n",args[1]);
	// printf("new_pc =  %d \n",new_pc);
	// printf("car_step =  %d \n", car->step);
	if (args[1] < 0 || args[1] > 15)
		return (new_pc);
	if (args[0] == 0)
		car->carry = 0;
	else
		car->carry = 1;
	car->reg[args[1]] = args[0];
	if (val->value_param == 4 || val->value_param == 30)
		printf("P %4d | ld %d r%d \n", -car->reg[0], args[0], args[1] + 1);
	if (val->value_param == 16 || val->value_param == 30)
	{ // ADV 7 (0x0000 -> 0x0007) 02 90 00 00 00 00 03
		printf("AVM %d (%#.4x -> %#.4x) ", car->step, car->save_pc, new_pc);
		int i;
		i = 0;
		while (i < car->step - 1)
		{
			printf("%.2x ", game->arena[car->save_pc + i]);
			i++;
		}
		printf("%.2x\n", game->arena[car->save_pc + i]);
	}
	return (new_pc);
}