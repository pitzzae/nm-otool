/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:47:27 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/18 14:47:29 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	print_section_name(char *segname, char *sectname)
{
	ft_putstr("Contents of (");
	ft_putstr(segname);
	ft_putchar(',');
	ft_putstr(sectname);
	ft_putendl(") section");
}

static void	print_ptr_address(unsigned long n, char *buff, t_head *head)
{
	char 	tmp_address[16];
	char	address[16];
	int 	i;

	ft_bzero(tmp_address, 16);
	ft_bzero(address, 16);
	ft_putbase(n, tmp_address, 16);
	i = 16;
	if (head->mach32)
		i = 8;
	i -= ft_strlen(tmp_address) + 1;
	while (i >= 0)
		address[i--] = 48;
	ft_strcat(address, tmp_address);
	ft_strcat(buff, address);
}

void		print_section(t_head *head, t_sect *s)
{
	size_t	offset;
	short	count;
	char 	buff[64];

	offset = 0;
	ft_bzero(buff, 64);
	print_section_name(s->seg_text, s->sect_text);
	while (s->start + offset != s->end)
	{
		count = 0;
		ft_bzero(buff, 64);
		print_ptr_address(s->offset + offset, buff, head);
		ft_putstr(buff);
		ft_putchar('\t');
		while (count++ != 16)
		{
			ft_puthex((s->start + offset), 1);
			offset++;
			if (s->start + offset == s->end)
				break ;
		}
		ft_putendl("");
	}
}
