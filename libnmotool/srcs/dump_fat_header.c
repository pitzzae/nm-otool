/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_fat_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:23:02 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/26 18:31:25 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int		is_magic_64(uint32_t magic) {
	return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}

static int		init_fat_header(t_file *bin, struct fat_header *header)
{
	if (bin->dump->is_swap)
		ft_swap_fat_header(bin, header);
	bin->fat_l = (int*)malloc(sizeof(int) * header->nfat_arch + 2);
	bin->nfat_arch = header->nfat_arch;
	return ((int)header->nfat_arch);
}

static void		make_fat_head_list(t_file *bin, struct fat_arch *arch)
{
	uint32_t			i;

	i = 0;
	while (i < bin->nfat_arch)
	{
		bin->arch = (struct fat_arch*)(((bin->ptr) + sizeof(struct fat_header))
						+ (sizeof(struct fat_arch) * i));
		if (bin->dump->is_swap)
			ft_swap_fat_arch(bin, arch);
		bin->mach32 = (struct mach_header*)((bin->ptr) + bin->arch->offset);
		bin->mach64 = NULL;
		bin->fat_l[i] = (int)bin->arch->cputype;
		i++;
	}
}

static void		dump_fat_mach(t_file *bin)
{
	bin->mach64 = NULL;
	bin->mach32 = (struct mach_header*)((bin->ptr) + bin->arch->offset);
	bin->dump->is_64 = is_magic_64(bin->mach32->magic);
	if (bin->dump->is_64 == 1)
	{
		bin->mach32 = NULL;
		bin->mach64 = (struct mach_header_64*)((bin->ptr) + bin->arch->offset);
	}
}

void			dump_fat_header(t_file *bin)
{
	struct fat_header	header;
	struct fat_arch		arch;
	struct fat_arch		arch_tmp;
	uint32_t			i;

	i = 0;
	init_fat_header(bin, &header);
	make_fat_head_list(bin, &arch_tmp);
	while (i < bin->nfat_arch)
	{
		bin->arch = (struct fat_arch*)(((bin->ptr) + sizeof(struct fat_header))
					+ (sizeof(struct fat_arch) * i));
		if (bin->dump->is_swap)
			ft_swap_fat_arch(bin, &arch);
		dump_fat_mach(bin);
		if (check_lib_option(bin, i))
			dump_mach_header(bin);
		i++;
	}
	free(bin->fat_l);
}
