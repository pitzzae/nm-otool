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

static size_t	add_line_to_lst1(uint8_t t, uint32_t f_type,
								  uint8_t n, t_symbol *sym)
{
	int				i;
	int 			j;
	int 			k;

	i = 0;
	j = I(t);
	k = I(n);
	if (f_type != MH_DYLIB && t == 0x0e && n == 0x01 && (i = 1))
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
	else if (I(t) == 14 && (I(n) == 4 || I(n) == 15) && (i = 1))
		sym->type = 's';
	else if ((I(t) == 14 || I(t) == 30) && I(n) == 1 && (i = 1))
		sym->type = 't';
	else if (I(t) == 30 && I(n) == 24 && (i = 1))
		sym->type = 'd';
	else if (I(t) == 14 && I(n) == 26 && (i = 1))
		sym->type = 'b';
	return (size_t)(i);
}

size_t			add_line_to_lst(uint8_t n_type, uint32_t f_type,
								 uint8_t n, t_symbol *sym)
{
	int				i;

	i = 0;
	if ((n_type == 0x24 || n_type == 0x0f) && n == 0x01 && (i = 1))
	{
		if ((sym->type = 'T') && f_type == MH_DYLIB && n_type != 0x0f)
			sym->type = 't';
		if (ft_strcmp(sym->address, S_X64) == 0 && sym->type == 'T')
			ft_memcpy(sym->address, "0000000000000000", 16);
		else if (ft_strcmp(sym->address, S_X86) == 0 && sym->type == 'T')
			ft_memcpy(sym->address, "00000000", 8);
	}
	else if (n_type == 0x01 && n == 0x00 && (i = 1))
		sym->type = 'U';
	else if (n_type == 0x26 && (n == 0x09) && (i = 1))
		sym->type = 'd';
	else if (n_type == 0xe && (I(n) == 3 || I(n) == 8 || I(n) == 10) && (i = 1))
		sym->type = 'b';
	else if (i == 0 && add_line_to_lst1(n_type, f_type, n, sym) == 1)
		return (size_t)(1);
	return (size_t)(i);
}