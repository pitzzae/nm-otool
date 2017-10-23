/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 01:00:40 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

void		ft_swap_fat_header(t_file *bin, struct fat_header *header)
{
	header->magic = ft_swapuint32(bin->head->magic);
	header->nfat_arch = ft_swapuint32(bin->head->nfat_arch);
	bin->head = header;
}

void		ft_swap_fat_arch(t_file *bin, struct fat_arch *arch)
{
	arch->cputype = ft_swapuint32(bin->arch->cputype);
	arch->cpusubtype = ft_swapuint32(bin->arch->cpusubtype);
	arch->offset = ft_swapuint32(bin->arch->offset);
	arch->size = ft_swapuint32(bin->arch->size);
	arch->align = ft_swapuint32(bin->arch->align);
	bin->arch = arch;
}
