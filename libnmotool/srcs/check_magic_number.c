/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 11:56:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 12:09:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

int 		check_magic_number(t_file *bin)
{
	if (bin->head->magic == MH_MAGIC ||
		bin->head->magic == MH_MAGIC_64 ||
		bin->head->magic == MH_CIGAM ||
		bin->head->magic == MH_CIGAM_64 ||
		bin->head->magic == FAT_MAGIC ||
		bin->head->magic == FAT_CIGAM)
		return (1);
	else
	{
		ft_putstr_fd(bin->exename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(bin->filename, 2);
		ft_putendl_fd(" The file was not recognized as a valid object file", 2);
		return (0);
	}
}
