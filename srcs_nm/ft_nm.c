/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:06:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	print_name_multi_arg(t_file *bin)
{
	if (bin->ac > 2)
	{
		ft_putendl("");
		ft_putstr(bin->filename);
		ft_putendl(":");
	}
}

static void	parse_result(t_file *bin, t_list *lst)
{
	size_t			i;
	t_symbol		*sym;

	i = 0;
	order_lst(lst);
	print_name_multi_arg(bin);
	while (lst != NULL && (sym = (t_symbol*)lst->content) != NULL && sym->name)
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

void		ft_nm(t_file *bin)
{
	t_list			*lst;

	bin->pos = 0;
	lst = NULL;
	while (bin->pos < bin->ncmds)
	{
		bin->sym = (struct symtab_command *)bin->lc_t[bin->pos];
		if (bin->sym->cmd == LC_SYMTAB && bin->sym->nsyms)
			lst = print_symbol_table(bin);
		bin->pos++;
	}
	if (lst)
		parse_result(bin, lst);
}
