/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:56:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/20 14:21:03 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	check_magic_lib(t_file *bin)
{
	char 		c[9];
	int 		i;

	i = 0;
	ft_strncpy(c, (char*)bin->ptr, 8);
	if (!ft_strcmp(c, ARMAG))
		i = 1;
	return (i);
}

static void	ft_print_error(void (*print_error)(t_file *bin, char *msg),
							t_file *bin, char *msg)
{
	print_error(bin, msg);
}

int			check_magic_number(t_file *bin)
{
	if (bin->head->magic == MH_MAGIC ||
		bin->head->magic == MH_MAGIC_64 ||
		bin->head->magic == MH_CIGAM ||
		bin->head->magic == MH_CIGAM_64 ||
		bin->head->magic == FAT_MAGIC ||
		bin->head->magic == FAT_CIGAM)
		return (1);
	else if (check_magic_lib(bin))
		return (1);
	else
		ft_print_error(bin->print_error, bin, "");
	return (0);
}
