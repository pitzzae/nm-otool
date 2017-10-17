/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_segment_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:35:39 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/25 12:35:40 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "nmotool.h"


static int	load_section_name_64(t_head *head, char *sectname, char *segn)
{

	int	i;

	i = 0;
	while (i < (int)head->sect.x64.seg->nsects)
	{
		if ((ft_strcmp(head->sect.x64.seg->segname, sectname) == 0)
			&& (ft_strcmp(head->sect.x64.seg->segname, segn) == 0))
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

void		get_segment_command(t_head *head)
{
	if (head->is_x64)
	{
		head->sect.segcom.text = load_section_name_64(head, SECT_TEXT, SEG_TEXT);
		head->sect.segcom.data = load_section_name_64(head, SECT_DATA, SEG_DATA);
		head->sect.segcom.bss = load_section_name_64(head, SECT_BSS, SEG_DATA);
	}
	else
	{
		//head->segcom.text = load_section_name_32(ofile, SECT_TEXT, SEG_TEXT);
		//head->segcom.data = load_section_name_32(ofile, SECT_DATA, SEG_DATA);
		//head->segcom.bss = load_section_name_32(ofile, SECT_BSS, SEG_DATA);
	}
}