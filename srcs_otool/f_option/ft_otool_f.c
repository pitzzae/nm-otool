/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 10:54:00 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/24 11:29:50 by gtorresa         ###   ########.fr       */
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

static void	ft_print_arch(int arch, int pos)
{
	(void)arch;
	ft_putstr("architecture ");
	ft_putnbr(pos);
	ft_putstr("\n\tcputype ");
	ft_putnbr(pos);
	ft_putstr("\n\tcpusubtype ");
	ft_putnbr(pos);
	ft_putstr("\n\tcapabilities ");
	ft_putnbr(pos);
	ft_putstr("\n\toffset ");
	ft_putnbr(pos);
	ft_putstr("\n\tsize ");
	ft_putnbr(pos);
	ft_putstr("\n\talign ");
	ft_putnbr(pos);
	ft_putchar('\n');
}

void		ft_otool_f(t_file *bin)
{
	char				str[16];
	uint32_t			i;

	i = 0;
	ft_putstr("Fat headers\nfat_magic ");
	ft_putstr(ft_pex(bin->head->magic, &str[0]));
	ft_putstr("\nnfat_arch ");
	ft_putnbr((long)bin->head->nfat_arch);
	ft_putchar('\n');
	while (i++ < bin->head->nfat_arch)
		ft_print_arch(bin->fat_l[i], i);
}