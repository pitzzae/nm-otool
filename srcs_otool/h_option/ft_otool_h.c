/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_h.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:59:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/01 13:24:55 by gtorresa         ###   ########.fr       */
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

static char	*ft_pex(unsigned long a, char *str, size_t len)
{
	char		tmp[16];
	int			i;
	int			j;

	i = 0;
	ft_bzero(str, 16);
	ft_bzero(tmp, 16);
	ft_strcat(str, "0x");
	ft_putbase(a, tmp, 16);
	j = 8 - ft_strlen(tmp);
	if (len && ft_strlen(tmp) < 8)
	{
		while (i < j)
		{
			ft_strcat(str, "0");
			i++;
		}
	}
	if (a == 0)
		ft_strcat(str, "00");
	else
		ft_putbase(a, str, 16);
	return (str);
}

static void	print_header_32(t_file *bin)
{
	char		str[16];
	char		*tmp;

	ft_putstr_whsp(ft_pex(bin->mach32->magic, &str[0], 0), ' ',
				ft_strlen(get_htxt(0)));
	tmp = ft_itoa(bin->mach32->cputype);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(1)));
	free(tmp);
	tmp = ft_itoa(bin->mach32->cpusubtype & 0xffff);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(2)));
	free(tmp);
	ft_putstr_whsp(ft_pex(((uint32_t)(bin->mach32->cpusubtype) &
			CPU_SUBTYPE_MASK) >> 24, &str[0], 0), ' ', ft_strlen(get_htxt(3)));
	tmp = ft_itoa(bin->mach32->filetype);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(4)));
	free(tmp);
	tmp = ft_itoa(bin->mach32->ncmds);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(5)));
	free(tmp);
	tmp = ft_itoa(bin->mach32->sizeofcmds);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(6)));
	free(tmp);
	ft_putstr_whsp(ft_pex(bin->mach32->flags, &str[0], 1), ' ',
				ft_strlen(get_htxt(7)));
	ft_putchar('\n');
}

static void	print_header_64(t_file *bin)
{
	char		str[16];
	char		*tmp;

	ft_putstr_whsp(ft_pex(bin->mach64->magic, &str[0], 0), ' ',
				ft_strlen(get_htxt(0)));
	tmp = ft_itoa(bin->mach64->cputype);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(1)));
	free(tmp);
	tmp = ft_itoa(bin->mach64->cpusubtype & 0x00ffffff);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(2)));
	free(tmp);
	ft_putstr_whsp(ft_pex(((uint32_t)(bin->mach64->cpusubtype) &
			CPU_SUBTYPE_MASK) >> 24, &str[0], 0), ' ', ft_strlen(get_htxt(3)));
	tmp = ft_itoa(bin->mach64->filetype);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(4)));
	free(tmp);
	tmp = ft_itoa(bin->mach64->ncmds);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(5)));
	free(tmp);
	tmp = ft_itoa(bin->mach64->sizeofcmds);
	ft_putstr_whsp(tmp, ' ', ft_strlen(get_htxt(6)));
	free(tmp);
	ft_putstr_whsp(ft_pex(bin->mach64->flags, &str[0], 1), ' ',
				ft_strlen(get_htxt(7)));
	ft_putchar('\n');
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
