/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:59:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 14:38:41 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char	*get_htxt(int i)
{
	if (i == 0)
		return ("      magic");
	if (i == 1)
		return (" cputype");
	if (i == 2)
		return (" cpusubtype");
	if (i == 3)
		return ("  caps");
	if (i == 4)
		return ("    filetype");
	if (i == 5)
		return (" ncmds");
	if (i == 6)
		return (" sizeofcmds");
	if (i == 7)
		return ("      flags");
	return ("");
}

static void	ft_print_hex()
{

}

static void	print_header_32(t_file *bin)
{
	(void)bin;
	ft_print_hex();
}

static void	print_header_64(t_file *bin)
{
	ft_putstr_whsp("coucou", ft_strlen(get_htxt(0)));
	ft_putstr_whsp(ft_itoa(bin->mach64->cputype), ft_strlen(get_htxt(1)));
	ft_putstr_whsp(ft_itoa(bin->mach64->cpusubtype), ft_strlen(get_htxt(2)));
	ft_putstr_whsp("coucou", ft_strlen(get_htxt(3)));
	ft_putstr_whsp(ft_itoa(bin->mach64->filetype), ft_strlen(get_htxt(4)));
	ft_putstr_whsp(ft_itoa(bin->mach64->ncmds), ft_strlen(get_htxt(5)));
	ft_putstr_whsp(ft_itoa(bin->mach64->sizeofcmds), ft_strlen(get_htxt(6)));
	ft_putstr_whsp("coucou", ft_strlen(get_htxt(7)));
}

void		ft_otool_h(t_file *bin)
{
	int			i;

	i = 0;
	if (bin->mach32 || bin->mach64)
	{
		ft_putstr("Mach header\n");
		while (i < 8)
		{
			ft_putstr(get_htxt(i++));
		}
		ft_putchar('\n');
	}
	if (bin->mach32)
		print_header_32(bin);
	else if (bin->mach64)
		print_header_64(bin);
}
