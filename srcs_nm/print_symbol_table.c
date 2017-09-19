/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 22:47:27 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/18 22:47:29 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	print_ptr_address(unsigned long n, char *buff, boolean_t x64)
{
	char 	tmp_address[16];
	char	address[16];
	int 	i;
	int 	address_tmp;

	ft_bzero(tmp_address, 16);
	ft_bzero(address, 16);
	i = 16;
	if (!x64)
	{
		i = 8;
		address_tmp = n & 0xffffffff;
		ft_putbase(address_tmp, tmp_address, 16);
	}
	else
		ft_putbase(n, tmp_address, 16);
	i -= ft_strlen(tmp_address) + 1;
	while (i >= 0)
		address[i--] = 48;
	ft_strcat(address, tmp_address);
	ft_strcat(buff, address);
}

static void	add_to_lst(t_list **lst, t_symbol sym)
{
	if (sym.name[0] == '_' || ft_strcmp(sym.name, "dyld_stub_binder") == 0)
		ft_lstadd(lst, ft_lstnew(&sym, sizeof(sym)));
}

t_list		*print_symbol_table_86(t_head *head, char *ptr)
{
	int				i;
	t_list			*lst;
	t_symbol		sym;

	i = 0;
	lst = ft_lstnew(NULL, 0);
	head->nlist32 = (void *)ptr + head->sym->symoff;
	while (i < head->sym->nsyms)
	{
		ft_bzero(sym.address, 17);
		if (head->nlist32[i].n_value > 0)
			print_ptr_address(head->nlist32[i].n_value, sym.address, head->is_x64);
		else
			ft_strcat(sym.address, "        ");
		if ((head->nlist32[i].n_type & N_TYPE) == 14)
			sym.type = 'T';
		else
			sym.type = 'U';
		sym.name = ft_strdup(ptr + head->sym->stroff +
				 head->nlist32[i].n_un.n_strx);
		add_to_lst(&lst, sym);
		i++;
	}
	return (lst);
}

t_list		*print_symbol_table_64(t_head *head, char *ptr)
{
	int				i;
	t_list			*lst;
	t_symbol		sym;

	i = 0;
	lst = ft_lstnew(NULL, 0);
	head->nlist64 = (void *)ptr + head->sym->symoff;
	while (i < head->sym->nsyms)
	{
		ft_bzero(sym.address, 17);
		if (head->nlist64[i].n_value > 0)
			print_ptr_address(head->nlist64[i].n_value, sym.address, head->is_x64);
		else
			ft_strcat(sym.address, "                ");
		if ((head->nlist64[i].n_type & N_TYPE) == 14)
			sym.type = 'T';
		else
			sym.type = 'U';
		sym.name = ptr + head->sym->stroff + head->nlist64[i].n_un.n_strx;
		add_to_lst(&lst, sym);
		i++;
	}
	return (lst);
}
