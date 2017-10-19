/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_segments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 14:59:48 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 12:05:15 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	is_magic_64(uint32_t magic) {
	return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}

static int	should_swap_bytes(uint32_t magic) {
	return magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM;
}

static int	is_fat(uint32_t magic) {
	return magic == FAT_MAGIC || magic == FAT_CIGAM;
}

static void	init_struct(t_file *bin)
{
	bin->head = NULL;
	bin->dump = NULL;
	bin->mach32 = NULL;
	bin->mach64 = NULL;
}

void		dump_segments(t_file *bin) {
	t_dump				dump;

	init_struct(bin);
	bin->head = (struct fat_header*)bin->ptr;
	dump.is_64 = is_magic_64(bin->head->magic);
	dump.is_swap = should_swap_bytes(bin->head->magic);
	dump.fat = is_fat(bin->head->magic);
	bin->dump = &dump;
	if (!check_magic_number(bin))
		return ;
	if (dump.fat)
		dump_fat_header(bin);
	else
	{
		bin->mach64 = NULL;
		bin->mach32 = (struct mach_header*)((bin->ptr));
		if (bin->dump->is_64 == 1)
		{
			bin->mach32 = NULL;
			bin->mach64 = (struct mach_header_64*)((bin->ptr));
		}
		if (check_lib_option(bin))
			dump_mach_header(bin);
	}
}
