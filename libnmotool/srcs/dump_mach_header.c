/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mach_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:25:48 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

void		dump_mach_header(t_file *bin)
{
	char 		*ptr;

	if (bin->mach64)
		ptr = (char*)bin->mach64;
	else if (bin->mach32)
		ptr = (char*)bin->mach32;
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		dump_static_lib(bin);
	else
	{
		if (bin->mach64)
		{
			bin->ncmds = bin->mach64->ncmds;
			bin->lc = (struct load_command*)(bin->mach64 + 1);
		}
		else if (bin->mach32)
		{
			bin->ncmds = bin->mach32->ncmds;
			bin->lc = (struct load_command*)(bin->mach32 + 1);
		}
		dump_load_commands(bin);
	}
}
