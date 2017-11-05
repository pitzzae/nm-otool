/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:06:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/05 14:02:47 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	ft_free_lst(void *ptr, size_t len)
{
	(void)len;
	(void)ptr;
}

static void	print_name_multi_arg(t_file *bin)
{
	if (bin->ac > 2)
	{
		ft_putendl("");
		ft_putstr(bin->filename);
		ft_putendl(":");
	}
	else if ((bin->dump->fat == 1 && bin->mach32))
	{
		ft_putstr(bin->filename);
		ft_putendl(":");
	}
}

static void	parse_result(t_file *bin, t_list *lst)
{
	size_t			i;
	t_symbol		*sym;
	void			(*ft_nm_print_error)(t_file *, char *);

	i = 0;
	order_lst(bin, lst);
	ft_nm_print_error = bin->print_error;
	if (bin->error_order > 0)
	{
		print_name_multi_arg(bin);
		while (lst != NULL && (sym = (t_symbol*)lst->content) != NULL && sym)
		{
			ft_putstr(sym->address);
			ft_putchar(' ');
			ft_putchar(sym->type);
			ft_putchar(' ');
			ft_putendl(sym->name);
			free(lst->content);
			lst = lst->next;
			i++;
		}
	}
}

void		ft_print_nm_option(t_file *bin)
{
	ft_putstr("Usage: ");
	ft_putstr(bin->exename);
	ft_putstr(" -arch=  <object file> ...\n"
					"\t-arch= select arch display [i386,x86_64,all]\n");
}

void		ft_nm(t_file *bin)
{
	t_list			*lst;

	bin->pos = 0;
	lst = NULL;
	while (bin->pos < bin->ncmds)
	{
		bin->sym = (struct symtab_command *)bin->lc_t[bin->pos];
		if (bin->sym->cmd == LC_SYMTAB && bin->sym->nsyms && !lst)
			lst = print_symbol_table(bin);
		bin->pos++;
	}
	if (lst)
		parse_result(bin, lst);
	if (lst)
		ft_lstdel(&lst, ft_free_lst);
}
