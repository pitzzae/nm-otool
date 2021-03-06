/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_section_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:46:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	*get_section_offset_64(t_sect *s)
{
	size_t						i;

	i = 0;
	if (s->x64.seg)
	{
		s->x64.sec = (struct section_64 *)(s->x64.seg + 1);
		while (i < s->x64.seg->nsects)
		{
			if (ft_strcmp(s->x64.sec->sectname, s->sect_text) == 0)
				return (s->x64.sec);
			s->x64.sec += 1;
			i++;
		}
	}
	return (NULL);
}

static void	*get_segment_offset_64(t_sect *s, t_file *bin)
{
	size_t						i;

	i = 0;
	while (i < bin->mach64->ncmds)
	{
		if (ft_strcmp(s->x64.seg->segname, s->seg_text) == 0)
			return (s->x64.seg);
		s->x64.seg = (struct segment_command_64 *)
				((char *)s->x64.seg + s->x64.seg->cmdsize);
		i++;
	}
	return (NULL);
}

void		find_section_64(t_file *bin, t_sect *s)
{
	s->x64.seg = (struct segment_command_64 *)(bin->mach64 + 1);
	if (bin->mach64->filetype != MH_OBJECT)
		s->x64.seg = get_segment_offset_64(s, bin);
	s->x64.sec = (struct section_64 *)get_section_offset_64(s);
	if (s->x64.sec)
	{
		s->start = (char *)bin->mach64 + s->x64.sec->offset;
		s->end = s->start + s->x64.sec->size;
		s->offset = s->x64.sec->addr;
		s->len64 = TRUE;
		print_section(s);
	}
}
