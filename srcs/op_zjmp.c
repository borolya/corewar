#include "corewar.h"

unsigned int op_zjmp(t_game *game, t_carriage *car, t_op op)
{
	__uint32_t t_dir;
	//if carry == 0 сдвигать на количество аргументов? нет
    
	if (car->carry == 1)
	{
        t_dir = bytes_to_int(game->arena, car->pc + 1, op.dir_size);
		car->pc = (car->pc + t_dir % IDX_MOD) % MEM_SIZE;
		return ((car->pc) % MEM_SIZE);
	}
	return ((car->pc + 1) % MEM_SIZE); // + t_dir_size??
}
