#include "corewar.h"

int shift_arg(__uint8_t t_array[], int size, int dir_size)
{
	int shift;
	int i;

	shift = 0;
	i = 0;
	while (i < size)
	{
		if (t_array[i] ==  T_REG)
			shift++;
		else if (t_array[i] == T_DIR)
			shift += dir_size;
		else if (t_array[i] == T_IND)
			shift += 2;
		i++;
	}
	return (shift);
}

int32_t take_value_shift_pc(__uint8_t type, __uint8_t arena[], unsigned int *pc, t_op op) //5 параметров!!!
{
	int adr;
	int32_t numb;

	if (type == T_DIR)
	{
		numb = bytes_to_int(arena, *pc, op.dir_size);
		*pc += op.dir_size;
	}
	else if (type == T_REG)
	{
		numb = (int)arena[(*pc) % MEM_SIZE] - 1;
		*pc = *pc + 1;
	}
	else if (type == T_IND)
	{
		if (op.idx_mod)
			adr = (*pc + bytes_to_int(arena, *pc, IND_SIZE) % IDX_MOD) % MEM_SIZE;
		else
			adr = (*pc + bytes_to_int(arena, *pc, IND_SIZE)) % MEM_SIZE;
		numb = bytes_to_int(arena, adr, REG_SIZE);
		*pc += REG_SIZE;
	}
	else
		return (0);
	return (numb);
}

int check_targ(__uint8_t arena[], t_carriage *car, t_op op, unsigned int *new_pc)
{
    int i;

    if (op.tcode)
    {
		car->pc = (car->pc + LEN_ARGS_CODE) % MEM_SIZE;
        take_targ(arena[car->pc], car->targ, op.count_args);
        car->pc = (car->pc + 1) % MEM_SIZE;
		*new_pc = (car->pc +
			shift_arg(car->targ, op.count_args, op.dir_size)) % MEM_SIZE;
        i = -1;
        while (++i < op.count_args)
        {
            if ((op.targ[i] & car->targ[i]) == 0)
                return (-1);
        }
    }
    else
    {
		*new_pc = (car->pc  + 1) % MEM_SIZE; //+1 ??
        i = -1;
        while (++i < op.count_args)
            car->targ[i] = op.targ[i];
    }
    return (0);
}

void take_targ(__uint8_t byte, __uint8_t targ[], int size)
{
	int i;
	__uint8_t type_code;

	i = 0;
	while (i < size)
	{
		type_code = (byte & 0xc0) >> 6;
		if (type_code == REG_CODE)
			targ[i] = T_REG;
		else if (type_code == DIR_CODE)
			targ[i] = T_DIR;
		else if (type_code == IND_CODE)
			targ[i] = T_IND;
		else
			targ[i] = T_LAB;
		byte = byte << 2;
		i++;
	}
}
/*
int main ()
{
	t_type array[3];
	uint8_t byts[] = {0x7b, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x07};

	int i;
	int pc;
	take_type(byts[0], array, 3);
	i = 0;
	pc = 1;
	while (i < 3)
	{
		if (array[i] ==  REG_CODE)
			printf("REG ");
		else if (array[i] ==  DIR_CODE)
			printf("DIR ");
		else if (array[i] == IND_CODE)
			printf("IND ");
		printf("val = %d \n", take_value_shift_pc(array[i], byts, &pc, 2));
		i++;
	}
	printf("\n");
	printf(" %d, %d, %d\n", array[0], array[1], array[2]);
	printf(" shift = %d\n", shift_arg(array, 0, 3, 2));
	return (0);
}
*/
