/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_fat_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:23:02 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/17 17:23:04 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int is_magic_64(uint32_t magic) {
	return magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
}

static void ft_swap_fat_header(t_file *bin, struct fat_header *header)
{
	header->magic = ft_swapuint32(bin->head->magic);
	header->nfat_arch = ft_swapuint32(bin->head->nfat_arch);
	bin->head = header;
}

static void ft_swap_fat_arch(t_file *bin, struct fat_arch *arch)
{
	arch->cputype = ft_swapuint32(bin->arch->cputype);
	arch->cpusubtype = ft_swapuint32(bin->arch->cpusubtype);
	arch->offset = ft_swapuint32(bin->arch->offset);
	arch->size = ft_swapuint32(bin->arch->size);
	arch->align = ft_swapuint32(bin->arch->align);
	bin->arch = arch;
}

void 		dump_fat_header(t_file *bin)
{
	struct fat_header	header;
	struct mach_header	*mach;
	struct fat_arch		arch;
	uint32_t			i;

	i = 0;
	if (bin->dump->is_swap)
		ft_swap_fat_header(bin, &header);
	while (i < header.nfat_arch)
	{
		bin->arch = (struct fat_arch*)(((bin->ptr) + sizeof(struct fat_header))
					+ (sizeof(struct fat_arch) * i));
		if (bin->dump->is_swap)
			ft_swap_fat_arch(bin, &arch);
		mach = (struct mach_header*)((bin->ptr) + bin->arch->offset);
		bin->dump->is_64 = is_magic_64(mach->magic);
		dump_mach_header(bin);
		i++;
	}
}
