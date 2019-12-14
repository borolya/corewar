#include "corewar.h"

unsigned int op_live(t_val *val, t_game *game, t_carriage *car, t_op op)
{
    int32_t t_dir;

    (void)val;
    game->live++;
    car->pc = (car->pc + 1) % MEM_SIZE;
    t_dir = take_value_shift_pc(T_DIR, game->arena, car, op);
    car->live = game->hook;
    if (t_dir < 0 && t_dir >= -(game->champs))
        game->last_alive = -t_dir; 
    return (car->pc);    
}