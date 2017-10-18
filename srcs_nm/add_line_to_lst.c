/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:48:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/18 19:01:27 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char	get_char_type(unsigned char c, t_symbol *sym)
{
	if (c == N_UNDF)
	{
		if (sym->n_value != 0)
			return ('c');
		return ('u');
	}
	if (c == N_PBUD)
		return ('u');
	if (c == N_ABS)
		return ('a');
	if (c == N_SECT)
	{
		if (sym->n_sect == 0x01)
			return ('t');
		else if (sym->n_sect == 0x08 || sym->n_sect == 0x0b)
			return ('d');
		else if (sym->n_sect == 0x03 || sym->n_sect == 0x0c)
			return ('b');
		return ('s');
	}
	if (c == N_INDR)
		return ('i');
	return ('?');
}

void		add_line_to_lst(t_symbol *sym, t_list **lst)
{
	t_list		*l;
	int 		i;

	l = *lst;
	while (l)
		l = l->next;
	if (!ft_strcmp(sym->name, "_crc_table"))
		i = sym->n_sect;
	sym->type = get_char_type(sym->n_type & N_TYPE, sym);
	if ((sym->n_type & N_EXT))
		sym->type = ft_toupper(sym->type);
	ft_lstadd(lst, ft_lstnew(sym, sizeof(*sym)));
}
