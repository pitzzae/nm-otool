/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 20:43:20 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 17:14:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void		ft_print_ot_option(t_file *bin)
{
	ft_putstr("Usage: ");
	ft_putstr(bin->exename);
	ft_putstr(" [-faht]  <object file> ...\n"
				"\t-f print the fat headers\n"
				"\t-a print the archive header\n"
				"\t-h print the mach header\n"
				"\t-t print the text section\n"
				"\t-arch= select arch display [i386,x86_64,all]\n");
}

void		ft_otool(t_file *bin)
{
	if (bin->d_opt & OT_OPT_H)
		ft_otool_h(bin);
	if (bin->d_opt & OT_OPT_A && bin->ar_lib && bin->is_arlib)
		ft_otool_a(bin);
	if (bin->d_opt & OT_OPT_T)
		ft_otool_t(bin);
	if (bin->d_opt & OT_OPT_F && !bin->is_arlib)
		ft_otool_f(bin);
	if (!bin->is_arlib && !bin->arch_all)
		bin->is_print = 1;
}
