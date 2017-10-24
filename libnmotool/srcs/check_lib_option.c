/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/24 17:49:06 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	fat_is_select(t_file *bin, int pos)
{
	uint32_t		i;
	int				find_64;

	i = 0;
	find_64 = 0;
	if (bin->arch_all)
		return (1);
	while (i < bin->nfat_arch)
	{
		if (bin->fat_l[i] == bin->arch_opt)
			find_64 = bin->arch_opt;
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
	if (i && (!bin->is_print || bin->arch_all))
	{
		bin->is_print = i;
		return (i);
	}
	else
		return (0);
}
