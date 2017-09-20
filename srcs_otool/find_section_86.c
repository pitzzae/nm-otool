/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_section_86.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:38:51 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 17:25:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	*get_section_offset_86(t_sect *s)
{
	size_t						i;

	i = 0;
	if (s->x86.seg)
	{
		s->x86.sec = (struct section *)(s->x86.seg + 1);
		while (i < s->x86.seg->nsects)
		{
			if (ft_strcmp(s->x86.sec->sectname, s->sect_text) == 0)
				return (s->x86.sec);
			s->x86.sec += 1;
			i++;
		}
	}
	return (NULL);
}

static void	*get_segment_offset_86(t_sect *s, t_head *headers)
{
	size_t						i;

	i = 0;
	while (i < headers->mach32->ncmds)
	{
		if (ft_strcmp(s->x86.seg->segname, s->seg_text) == 0)
			return (s->x86.seg);
		s->x86.seg = (struct segment_command *)
				((char *)s->x86.seg + s->x86.seg->cmdsize);
		i++;
	}
	return (NULL);
}

void		find_section_86(t_head *head, t_sect *s)
{
	s->x86.seg = (struct segment_command *)(head->mach32 + 1);
	if (head->mach32->filetype != MH_OBJECT)
		s->x86.seg = get_segment_offset_86(s, head);
	s->x86.sec = (struct section *)get_section_offset_86(s);
	if (s->x86.sec)
	{
		s->start = (char *)head->mach32 + s->x86.sec->offset;
		s->end = s->start + s->x86.sec->size;
		s->offset = s->x86.sec->addr;
		s->len64 = FALSE;
		print_section(s);
	}
}
