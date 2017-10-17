/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 20:43:20 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/17 20:43:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void	ft_otool(t_file *bin)
{
	struct segment_command *seg32;
	struct segment_command_64 *seg64;
	uint32_t		i;

	i = 0;
	while (i < bin->ncmds)
	{
		if (bin->dump->is_64)
			seg64 = bin->seg64_t[i];
		else
			seg32 = bin->seg32_t[i];
		if (bin->lc_t[i]->cmd == LC_SEGMENT)
		{
			ft_putstr(seg32->segname);
			ft_putnbr(bin->lc_t[i]->cmd);
			ft_putstr(" ");
			ft_putnbr(bin->lc_t[i]->cmdsize);
			ft_putendl("");
		}
		i++;
	}
}
