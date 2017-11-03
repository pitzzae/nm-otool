/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:06:24 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/03 17:42:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void		swap_content(t_list *l, boolean_t *lst_is_order)
{
	t_symbol			*sym;

	sym = l->content;
	l->content = l->next->content;
	l->next->content = sym;
	*lst_is_order = FALSE;
}

static void		order_by_address(t_list *l, boolean_t *lst_is_order)
{
	int					cmp;

	cmp = ft_strcmp(((t_symbol*)(l->content))->address,
					((t_symbol*)(l->next->content))->address);
	if (cmp > 0)
		swap_content(l, lst_is_order);
}

void			order_lst(t_file *bin, t_list *lst)
{
	boolean_t			lst_is_order;
	t_list				*l;
	int					cmp;

	lst_is_order = FALSE;
	l = lst;
	while (!lst_is_order && l->content)
	{
		bin->error_order = (int)((t_symbol*)(l->content))->name;
		lst_is_order = TRUE;
		while (l->next && l->next->content && l->next->next
			&& bin->error_order > 0)
		{
			bin->error_order = (int)((t_symbol*)(l->content))->name;
			cmp = ft_strcmp(((t_symbol*)(l->content))->name,
							((t_symbol*)(l->next->content))->name);
			if (cmp > 0)
				swap_content(l, &lst_is_order);
			else if (cmp == 0)
				order_by_address(l, &lst_is_order);
			l = l->next;
		}
		l = lst;
	}
}
