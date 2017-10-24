/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 20:43:20 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/24 10:30:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void		ft_print_ot_option(t_file *bin)
{
	ft_putstr("Usage: ");
	ft_putstr(bin->exename);
	ft_putendl(" [-fahlt]  <object file> ...");
	ft_putendl("\t-f print the fat headers\n"
				"\t-a print the archive header\n"
				"\t-h print the mach header\n"
				"\t-l print the load commands\n"
				"\t-t print the text section");
}

void		ft_otool(t_file *bin)
{
	if (bin->d_opt & OT_OPT_H)
		ft_otool_h(bin);
	if (bin->d_opt & OT_OPT_A && bin->ar_lib)
		ft_otool_a(bin);
	if (bin->d_opt & OT_OPT_T)
		ft_otool_t(bin);
	bin->is_print = 0;
}
