/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:48:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 20:25:02 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char	get_char_type(unsigned char c, t_symbol *sym, t_file *bin)
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
		if (sym->n_sect == bin->tdb->text_nsect)
			return ('t');
		else if (sym->n_sect == bin->tdb->data_nsect)
			return ('d');
		else if (sym->n_sect == bin->tdb->bss_nsect)
			return ('b');
		return ('s');
	}
	if (c == N_INDR)
		return ('i');
	return ('?');
}

void		add_line_to_lst(t_file *bin, t_symbol *sym, t_list **lst)
{
	t_list		*l;

	l = *lst;
	while (l)
		l = l->next;
	sym->type = get_char_type(sym->n_type & N_TYPE, sym, bin);
	if ((sym->n_type & N_EXT))
		sym->type = ft_toupper(sym->type);
	ft_lstadd(lst, ft_lstnew(sym, sizeof(*sym) + 32));
}
