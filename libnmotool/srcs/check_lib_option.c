/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 17:34:15 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	fat_is_select(t_file *bin, int pos)
{
	uint32_t		i;
	int 			find_64;

	i = 0;
	find_64 = 0;
	while (i < bin->nfat_arch)
	{
		if (bin->fat_l[i] == CPU_TYPE_X86_64)
			find_64 = CPU_TYPE_X86_64;
		i++;
	}
	if (bin->fat_l[pos] == find_64)
		return (1);
	else
		return (0);
}

int			check_lib_option(t_file *bin, int pos)
{
	int				i;

	if (bin->nfat_arch)
		i = fat_is_select(bin, pos);
	else
		i = 1;
	if (i)
		bin->is_print = i;
	return (i);
}
