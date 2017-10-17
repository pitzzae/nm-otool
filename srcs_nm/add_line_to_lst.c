/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 01:01:28 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/22 01:01:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static size_t 	add_line_to_lst2(uint8_t t, uint32_t f_type,
								  uint8_t n, t_symbol *sym)
{
	int				i;
	int 			j;
	int 			k;

	(void)f_type;
	i = 0;
	j = I(t);
	k = I(n);
	if (t & N_TYPE)
		i = 0;
	if (I(t) == 14 && I(n) == 11 && (i = 1))
		sym->type = 'd';
	if (I(t) == 15 && I(n) == 11 && (i = 1))
		sym->type = 'D';
	if (I(t) == 38 && I(n) == 10 && (i = 1))
		sym->type = 's';
	if (I(t) == 32 && I(n) == 0 && (i = 1))
		sym->type = 'S';
	return (size_t)(i);
}

static size_t	add_line_to_lst1(uint8_t t, uint32_t f_type,
								  uint8_t n, t_symbol *sym)
{
	int				i;

	i = 0;
	if (f_type != MH_DYLIB && t == N_TYPE && n == N_EXT && (i = 1))
	{
		if ((sym->type = 'T') && (f_type == MH_OBJECT || f_type == MH_EXECUTE))
			sym->type = 't';
	}
	else if (I(t) == 15 && (I(n) == 8 || I(n) == 2) && (i = 1))
		sym->type = 'D';
	else if (I(t) == 15 && I(n) == 10 && (i = 1))
		sym->type = 'S';
	else if (I(t) == 30 && (I(n) == 22 || I(n) == 23 || I(n) == 25) && (i = 1))
		sym->type = 's';
	else if (I(t) == 14 && (I(n) == 4 || I(n) == 5 || I(n) == 15) && (i = 1))
		sym->type = 's';
	else if ((I(t) == 14 || I(t) == 30) && I(n) == 1 && (i = 1))
		sym->type = 't';
	else if (I(t) == 30 && I(n) == 24 && (i = 1))
		sym->type = 'd';
	else if (I(t) == 14 && (I(n) == 26 || I(n) == 12) && (i = 1))
		sym->type = 'b';
	else if (i == 0 && add_line_to_lst2(t, f_type, n, sym) == 1)
		return (size_t)(1);
	return (size_t)(i);
}

char	parse_n_type_64(unsigned char c, struct nlist_64 *list)
{
	if (c == N_UNDF)
	{
		if (list->n_value != 0)
			return ('c');
		return ('u');
	}
	if (c == N_PBUD)
		return ('u');
	if (c == N_ABS)
		return ('a');
	if (c == N_SECT)
	{
		if (list->n_sect == 0x01)
			return ('t');
		else if (list->n_sect == '\v')
			return ('d');
		else if (list->n_sect == '\f')
			return ('b');
		return ('s');
	}
	if (c == N_INDR)
		return ('i');
	return ('?');
}

size_t			add_line_to_lst(void *nlst, t_head *head, t_symbol *sym)
{
	uint32_t		f_type;
	uint8_t 		t;
	uint8_t 		s;
	uint16_t 		d;
	uint32_t		v32;
	uint64_t		v64;
	int				i;
	char 			c;
	uint8_t 		tmp;

	i = 0;
	t = 0;
	sym->type = 0;
	if (head->is_x64 && (f_type = head->mach64->filetype))
	{
		t = ((struct nlist_64*)nlst)->n_type;
		s = ((struct nlist_64*)nlst)->n_sect;
		d = ((struct nlist_64*)nlst)->n_desc;
		v32 = ((struct nlist_64*)nlst)->n_value;
	}
	else if ((f_type = head->mach32->filetype))
	{
		t = ((struct nlist*)nlst)->n_type;
		s = ((struct nlist*)nlst)->n_sect;
		d = ((struct nlist*)nlst)->n_desc;
		v64 = ((struct nlist*)nlst)->n_value;
	}
	tmp = t & N_TYPE;
	c = parse_n_type_64(t & N_TYPE, ((struct nlist_64*)nlst));
	if ((t & N_EXT) && c != '?')
		c = ft_toupper(c);
	if ((t == 0x24 || t == 0x0f) && s == 0x01 && (i = 1))
	{
		if ((sym->type = 'T') && f_type == MH_DYLIB && t != 0x0f)
			sym->type = 't';
		if (ft_strcmp(sym->address, S_X64) == 0 && sym->type == 'T')
			ft_memcpy(sym->address, "0000000000000000", 16);
		else if (ft_strcmp(sym->address, S_X86) == 0 && sym->type == 'T')
			ft_memcpy(sym->address, "00000000", 8);
	}
	else if (t == 0x01 && s == 0x00 && (i = 1))
		sym->type = 'U';
	else if (t == 0x26 && (s == 0x09) && (i = 1))
		sym->type = 'd';
	else if (t == 0xe && (I(s) == 3 || I(s) == 8 || I(s) == 10) && (i = 1))
		sym->type = 'b';
	else if (i == 0 && f_type != 6 && add_line_to_lst1(t, f_type, s, sym) == 1)
		return (size_t)(1);
	return (size_t)(i);
}