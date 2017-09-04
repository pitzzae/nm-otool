/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_headers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:51:41 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/23 14:51:43 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <nmotool.h>

static uint32_t	get_headers_offset(uint32_t nb)
{
    uint32_t	rev;

    rev = ((nb >> 24) & 0xff) |
          ((nb << 8) & 0xff0000) |
          ((nb >> 8) & 0xff00) |
          ((nb << 24) & 0xff000000);
    return (rev);
}

static void	get_fat_headers(void *ptr, t_head *head)
{
    struct fat_header		*fat_h;
    struct fat_arch			*fat_ar;
    struct mach_header_64	*header_64;
    size_t					count;

    count = 0;
    fat_h = (struct fat_header *)ptr;
    fat_ar = (struct fat_arch *)(fat_h + 1);
    while (count < get_headers_offset(fat_h->nfat_arch))
    {
		header_64 = (void *)((char *)ptr + get_headers_offset(fat_ar->offset));
        if (header_64->magic == MH_MAGIC_64
            && header_64->cputype == CPU_TYPE_X86_64)
			head->mach64 = header_64;
        else if (header_64->magic == MH_MAGIC
                 && header_64->cputype == CPU_TYPE_X86)
			head->mach32 = (struct mach_header *)header_64;
        fat_ar += 1;
        count++;
    }
}

static void	get_header(void *ptr, t_head *head)
{
    struct mach_header_64	*header_64;

	header_64 = (struct mach_header_64 *)ptr;
    if (header_64->magic == MH_MAGIC_64
        && header_64->cputype == CPU_TYPE_X86_64)
		head->mach64 = header_64;
    else if (header_64->magic == MH_MAGIC
             && header_64->cputype == CPU_TYPE_X86)
		head->mach32 = (struct mach_header *)header_64;
}

void		get_binary_headers(void *ptr, t_head *head)
{
    struct fat_header		*fat_h;

	head->mach64 = NULL;
	head->mach32 = NULL;
    fat_h = (struct fat_header *)ptr;
    if (fat_h->magic == FAT_CIGAM)
        get_fat_headers(ptr, head);
    else
        get_header(ptr, head);
}
