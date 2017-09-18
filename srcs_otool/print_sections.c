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
	ft_putchar('(');
	ft_putstr(segname);
	ft_putchar(',');
	ft_putstr(sectname);
	ft_putendl(") section");
}

void	print_byte_to_hex(char byte)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
}

void	print_ptr_to_hex(size_t ptr, boolean_t prefix, boolean_t len64)
{
	char	str[16];
	short	count;
	short	char_hex;

	count = -1;
	while (++count != 16)
	{
		char_hex = ptr % 16;
		ptr /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	count--;
	if (!len64)
		count -= 8;
	if (prefix)
		ft_putstr("0x");
	while (count >= 0)
		ft_putchar(str[count--]);
}

void		print_section(t_sect *s)
{
	size_t	offset;
	short	count;
	char	delim;

	offset = 0;
	print_section_name(s->seg_text, s->sect_text);
	if (!ft_strcmp(s->seg_text, "__TEXT") && !ft_strcmp(s->sect_text, "__text"))
		delim = ' ';
	else
		delim = '\t';
	while (s->start + offset != s->end)
	{
		count = 0;
		print_ptr_to_hex(s->offset + offset, FALSE, s->len64);
		ft_putchar(delim);
		while (count++ != 16)
		{
			print_byte_to_hex(*(s->start + offset));
			offset++;
			ft_putchar(' ');
			if (s->start + offset == s->end)
				break ;
		}
		ft_putchar('\n');
	}
}



