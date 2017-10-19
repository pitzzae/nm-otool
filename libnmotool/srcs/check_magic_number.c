/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:56:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 21:48:35 by gtorresa         ###   ########.fr       */
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

static void	ft_ot_print_error(t_file *bin)
{
	ft_putstr(bin->filename);
	ft_putendl(": is not an object file");
}

static void	ft_nm_print_error(t_file *bin)
{
	ft_putstr_fd(bin->exename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(bin->filename, 2);
	ft_putendl_fd(" The file was not recognized as a valid object file", 2);
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
	{
		if (bin->print_error == OT_DISPLAY)
			ft_ot_print_error(bin);
		else if (bin->print_error == NM_DISPLAY)
			ft_nm_print_error(bin);
		return (0);
	}
}
