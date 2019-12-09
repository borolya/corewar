#include "corewar.h"

unsigned int op_add(t_game *game, t_carriage *car, t_op op)
{
    unsigned int new_pc;
    __uint32_t args[3];
    int i;
    __uint32_t sum;

    if (check_targ(game->arena, car, op, &new_pc) == -1)
		return (new_pc);
    i = -1;
    while (++i < op.count_args)
    {
        args[i] = take_value_shift_pc(T_REG, game->arena, &(car->pc), op);
        if (args[i] > 15)
            return (new_pc);
    }
    sum = car->reg[args[0]] + car->reg[args[1]];
    if (sum == 0)
        car->carry = 1;
    else
        car->carry = 0;
    car->reg[args[2]] = sum;
    return (new_pc);
}