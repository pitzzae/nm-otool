/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 13:48:22 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/18 13:48:24 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char get_char_type(t_symbol *sym)
{
	char 		c;
	int i = (sym->n_sect & N_EXT);

	c = 'u';
	(void)i;
	if ((sym->n_sect & 0x01))
		c = 't';
	else if ((sym->n_sect & 0x08))
		c = 'd';
	if ((sym->n_type & N_EXT))
		c = ft_toupper(c);
	return (c);
}

void		add_line_to_lst(t_symbol *sym, t_list **lst)
{
	t_list			*l;

	l = *lst;
	while (l)
		l = l->next;
	sym->type = get_char_type(sym);
	ft_lstadd(lst, ft_lstnew(sym, sizeof(*sym)));
}
