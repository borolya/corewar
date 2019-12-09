#include "corewar.h"

unsigned int op_fork(t_game *game, t_carriage *car,t_op op)
{
	__uint32_t	t_dir;
	t_carriage	new_car;
	t_list		*new;

	car->pc = (car->pc + 1) % MEM_SIZE;
	t_dir = take_value_shift_pc(T_DIR, game->arena, &(car->pc), op);
	new_car = copy_carriage(car);
	new_car.pc = (t_dir % IDX_MOD) % MEM_SIZE;
	
	//new_car.numb??
	if (!(new = ft_lstnew((void*)&new_car, sizeof(t_carriage))))
			ft_error("memor :(");
	ft_lstadd(&(game->carriages), new); 
	return ((car->pc) % MEM_SIZE);
	//car->numb??
}