/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 10:54:00 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 18:51:44 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char	*ft_pex(unsigned long a, char *str)
{
	ft_bzero(str, 16);
	ft_strcat(str, "0x");
	ft_putbase(a, str, 16);
	return (str);
}

static void	ft_print_arch(struct fat_arch *arch, int pos)
{
	char				str[16];

	(void)arch;
	ft_putstr("architecture ");
	ft_putnbr(pos);
	ft_putstr("\n    cputype ");
	ft_putnbr(arch->cputype);
	ft_putstr("\n    cpusubtype ");
	ft_putnbr(arch->cpusubtype & 0x00ffffff);
	ft_putstr("\n    capabilities ");
	ft_putstr(ft_pex(((uint32_t)(arch->cpusubtype) &
					CPU_SUBTYPE_MASK) >> 24, &str[0]));
	ft_putstr("\n    offset ");
	ft_putnbr(arch->offset);
	ft_putstr("\n    size ");
	ft_putnbr(arch->size);
	ft_putstr("\n    align 2^");
	ft_putnbr(arch->align);
	ft_putstr(" (");
	ft_putnbr(ft_pow(2, arch->align));
	ft_putstr(")\n");
}

static void	ft_print_header_arch(t_file *bin)
{
	char				str[16];

	ft_putstr("Fat headers\nfat_magic ");
	ft_putstr(ft_pex(bin->head->magic, &str[0]));
	ft_putstr("\nnfat_arch ");
	ft_putnbr((long)bin->head->nfat_arch);
	ft_putchar('\n');
}

void		ft_otool_f(t_file *bin)
{
	struct fat_arch		ta;
	t_file				tb;
	void				*ptr;
	uint32_t			i;

	i = 0;
	if (ft_strncmp(bin->ptr, ARMAG, SARMAG) && bin->dump->fat)
	{
		ft_print_header_arch(bin);
		ptr = (bin->ptr + sizeof(struct fat_header));
		while (i < bin->head->nfat_arch)
		{
			tb.arch = (struct fat_arch*)(ptr + (sizeof(struct fat_arch) * i));
			ft_swap_fat_arch(&tb, &ta);
			ft_print_arch(tb.arch, i);
			i++;
		}
	}
}
