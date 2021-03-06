/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_t.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 12:56:39 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:23 by gtorresa         ###   ########.fr       */
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

void		ft_otool_t(t_file *bin)
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
