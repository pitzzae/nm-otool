/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:06:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/18 12:06:11 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	parse_result(t_list *lst)
{
	size_t					i;
	t_symbol				*sym;

	i = 0;
	order_lst(lst);
	while (lst != NULL && (sym = (t_symbol*)lst->content) != NULL)
	{
		ft_putstr(sym->address);
		ft_putchar(' ');
		ft_putchar(sym->type);
		ft_putchar(' ');
		ft_putendl(sym->name);
		free(lst->content);
		free(lst);
		lst = lst->next;
		i++;
	}
}

void	ft_nm(t_file *bin)
{
	t_list			*lst;

	bin->pos = 0;
	while (bin->pos < bin->ncmds)
	{
		bin->sym = (struct symtab_command *)bin->lc_t[bin->pos];
		if (bin->sym->cmd == LC_SYMTAB)
		{
			lst = print_symbol_table(bin);
		}
		bin->pos++;
	}
	parse_result(lst);
}
