/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_mach_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:25:48 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/01 12:43:27 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	dump_is_mach(t_file *bin)
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
	if (!(sizeof(int*) == 4 && bin->mach64))
		dump_load_commands(bin);
	else
		ft_putstr("Error: arch i386 do not support x86_64\n");
}

void		dump_mach_header(t_file *bin)
{
	char		*ptr;

	ptr = NULL;
	if (bin->mach64)
		ptr = (char*)bin->mach64;
	else if (bin->mach32)
		ptr = (char*)bin->mach32;
	else
		ptr = (char*)((bin->ptr) + bin->arch->offset);
	if (!ft_strncmp(ptr, ARMAG, SARMAG))
		dump_static_lib(bin);
	else if (bin->mach32 || bin->mach64)
		dump_is_mach(bin);
}
