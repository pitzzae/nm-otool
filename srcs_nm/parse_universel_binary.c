/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_universel_binary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:37:32 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/22 14:37:34 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

uint32_t		ft_swapuint32(uint32_t u)
{
	return (((((uint32_t)(u) & 0xff000000) >> 24) |
			(((uint32_t)(u) & 0x00ff0000) >> 8) |
			(((uint32_t)(u) & 0x0000ff00) << 8) |
			(((uint32_t)(u) & 0x000000ff) << 24)));
}

size_t		parse_universel_binary(t_bin *bin)
{
	struct fat_header		*fh;
	struct fat_arch			*fa;
	int						i;

	fh = (struct fat_header*)bin->ptr;
	fa = (struct fat_arch*)(bin->ptr + sizeof(struct fat_header));
	if ((i = 0) && (fh->magic == FAT_MAGIC || fh->magic == FAT_CIGAM))
	{
		if (ft_swapuint32(fa->cputype) == CPU_TYPE_X86 && (i = 1))
		{
			bin->head.arch32 = fa;
			bin->head.mach32 = (struct mach_header *)(bin->ptr +
								ft_swapuint32(fa->offset));
			bin->head.lc = (struct load_command*)(bin->head.mach32 + 1);
			bin->head.is_x64 = FALSE;
		}
		if (ft_swapuint32(fa->cputype) == CPU_TYPE_X86_64 && (i = 1))
		{
			bin->head.arch64 = fa;
			bin->head.mach64 = (struct mach_header_64 *)(bin->ptr +
								ft_swapuint32(fa->offset));
			bin->head.lc = (struct load_command*)(bin->head.mach64 + 1);
			bin->head.is_x64 = TRUE;
		}
	}
	return (i);
}