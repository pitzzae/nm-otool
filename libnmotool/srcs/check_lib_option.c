/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 01:59:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	fat_is_select(t_file *bin)
{
	uint32_t		i;
	int 			j;

	i = 0;
	j = 1;
	while (i < bin->nfat_arch)
	{
		if (!bin->dump->is_64 && bin->fat_l[i])
			j = 0;
		i++;
	}
	return (j);
}

int 		check_lib_option(t_file *bin)
{
	if (bin->nfat_arch)
		return (fat_is_select(bin));
	else
		return (1);
}
