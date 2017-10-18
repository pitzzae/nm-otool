/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:48:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/18 18:38:29 by gtorresa         ###   ########.fr       */
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
		else if (sym->n_sect == 0x08)
			return ('d');
		else if (sym->n_sect == 0x03)
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
	sym->type = get_char_type(sym->n_type & N_TYPE, sym);
	if (!ft_strcmp(sym->name, "_testp"))
		i = sym->n_type & N_STAB;
	if ((sym->n_type & N_EXT))
		sym->type = ft_toupper(sym->type);
	ft_lstadd(lst, ft_lstnew(sym, sizeof(*sym)));
}
