#include "corewar.h"

unsigned int op_sub(t_game *game, t_carriage *car, t_op op)
{
    unsigned int new_pc;
    int32_t args[3];
    int i;
    int32_t sub;

    if (check_targ(game->arena,car, op, &new_pc) == -1)
		return (new_pc);
    i = -1;
    while (++i < op.count_args)
    {
        args[i] = take_value_shift_pc(T_REG, game->arena, car, op);
        if (args[i] < 0 || args[i] > 15)
            return (new_pc);
    }
    sub = car->reg[args[0]] - car->reg[args[1]];
    if (sub == 0)
        car->carry = 1;
    else
        car->carry = 0;
    car->reg[args[2]] = sub;
    return (new_pc);
}