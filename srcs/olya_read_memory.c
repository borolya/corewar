/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   olya_read_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenly-b <crenly-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:01:32 by crenly-b          #+#    #+#             */
/*   Updated: 2019/12/11 20:02:46 by crenly-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_take_uint(t_champ *champ, int fd, int *n, int tmp)
{
	int		i;
	uint8_t	byte;

	*n = 0;
	i = 0;
	while (i < 4)
	{
		if (read(fd, &byte, 1) <= 0)
			ft_error("Short file");
		*n = *n * 16 * 16 + byte;
		i++;
	}
	if (champ->exec_code_size > CHAMP_MAX_SIZE)
		ft_error("Exec_size_code too big");
	else if (champ->exec_code_size == 0)
		ft_error("Exec_size_code too small");
	if (read(fd, champ->comment, COMMENT_LENGTH) <= 0)
		ft_error("Short file");
	if (read(fd, &tmp, 4) < 0)
		ft_error("Short file");
	if (tmp != 0x00000000)
		ft_error("Missing NULL after comment");
}

void		init_champ(int fd, t_champ *champ, int pos_of_player)
{
	unsigned int	tmp;
	uint8_t			numb;
	int				i;

	if (read(fd, &tmp, 4) <= 0)
		ft_error("Short file");
	if (tmp != 0xf383ea00)
		ft_error("Missing magic header");
	if (read(fd, champ->name, PROG_NAME_LENGTH) < 0)
		ft_error("Short file");
	if (read(fd, &tmp, 4) <= 0)
		ft_error("Short file");
	if (tmp != 0x00000000)
		ft_error("Missing NULL after name");
	ft_take_uint(champ, fd, &(champ->exec_code_size), tmp);
	i = -1;
	while (read(fd, &numb, 1) > 0 && i < CHAMP_MAX_SIZE - 1)  // еще && i < CHAMP_MAX_SIZE
		champ->exec_code[++i] = numb;
	if (++i != champ->exec_code_size)
		ft_error("Wrong exec_code_size");
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"
		, pos_of_player + 1, champ->exec_code_size
			, champ->name, champ->comment);
}
