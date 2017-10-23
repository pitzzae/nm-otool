/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 20:43:20 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 12:38:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	print_filename(t_file *bin, char *filename)
{
	if (!bin->is_arlib)
	{
		ft_putstr(filename);
		ft_putendl(":");
	}
}

static void	ft_otool_t(t_file *bin)
{
	t_sect		s;

	print_filename(bin, bin->filename);
	s.seg_text = SEG_TEXT;
	s.sect_text = SECT_TEXT;
	if (bin->mach64)
		find_section_64(bin, &s);
	else if (bin->mach32)
		find_section_32(bin, &s);
}

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
	if (bin->d_opt & OT_OPT_T)
		ft_otool_t(bin);
	else if (bin->d_opt == OT_OPT_NO)
		ft_print_ot_option(bin);
}
