#include "corewar.h"

unsigned int op_aff(t_game*game, t_carriage *car, t_op op)
{
    unsigned int    new_pc;
    __uint32_t        reg;

    if (check_targ(game->arena, car, op, &new_pc) == -1)
        return (new_pc);
    reg = take_value_shift_pc(car->targ[0], game->arena, &(car->pc), op);
    if (reg > 15)
        return (new_pc);
    ft_printf("%d", car->reg[reg]); // \n? 
    return (new_pc);
}