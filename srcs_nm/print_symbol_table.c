/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 22:47:27 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 17:23:48 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void		print_ptr_addr(unsigned long n, char *buff, boolean_t x64)
{
	char			tmp_address[16];
	char			address[16];
	int				i;
	int				address_tmp;

	ft_bzero(tmp_address, 16);
	ft_bzero(address, 16);
	i = 16;
	if (!x64)
	{
		i = 8;
		address_tmp = (int)(n & 0xffffffff);
		ft_putbase((unsigned long)address_tmp, tmp_address, 16);
	}
	else
		ft_putbase(n, tmp_address, 16);
	i -= ft_strlen(tmp_address) + 1;
	while (i >= 0)
		address[i--] = 48;
	ft_strcat(address, tmp_address);
	ft_strcat(buff, address);
}

static void		fuc_is_public(t_list **lst, t_symbol *sym)
{
	t_list			*l;
	t_symbol		*s;

	l = *lst;
	while (l)
	{
		s = ((t_symbol*)(l->content));
		if (s && ft_strcmp(s->name, sym->name) == 0 &&
				ft_strcmp(s->address, sym->address) == 0)
		{
			s->type = 'T';
			return ;
		}
		l = l->next;
	}
	ft_lstadd(lst, ft_lstnew(sym, sizeof(*sym)));
}

static size_t	add_line_to_lst(uint8_t n_type, uint32_t f_type,
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
	else if (f_type != MH_DYLIB && n_type == 0x0e && n == 0x01 && (i = 1))
	{
		if ((sym->type = 'T') && (f_type == MH_OBJECT || f_type == MH_EXECUTE))
			sym->type = 't';
	}
	return (size_t)(i);
}

t_list			*print_symbol_table_86(t_head *head, char *ptr)
{
	size_t			i;
	t_list			*lst;
	t_symbol		sym;

	i = 0;
	lst = ft_lstnew(NULL, 0);
	head->nlist32 = (void *)ptr + head->sym->symoff;
	while (i < head->sym->nsyms)
	{
		ft_bzero(sym.address, 17);
		if (head->nlist32[i].n_value > 0)
			print_ptr_addr(head->nlist32[i].n_value, sym.address, head->is_x64);
		else
			ft_strcat(sym.address, S_X86);
		sym.name = ptr + head->sym->stroff + head->nlist32[i].n_un.n_strx;
		if (add_line_to_lst(head->nlist32[i].n_type, head->mach32->filetype,
							head->nlist32[i].n_sect, &sym))
			fuc_is_public(&lst, &sym);
		i++;
	}
	return (lst);
}

t_list			*print_symbol_table_64(t_head *head, char *ptr)
{
	size_t			i;
	t_list			*lst;
	t_symbol		sym;

	i = 0;
	lst = ft_lstnew(NULL, 0);
	head->nlist64 = (void *)ptr + head->sym->symoff;
	while (i < head->sym->nsyms)
	{
		ft_bzero(sym.address, 17);
		if (head->nlist64[i].n_value > 0)
			print_ptr_addr(head->nlist64[i].n_value, sym.address, head->is_x64);
		else
			ft_strcat(sym.address, S_X64);
		sym.name = ptr + head->sym->stroff + head->nlist64[i].n_un.n_strx;
		if (add_line_to_lst(head->nlist64[i].n_type, head->mach64->filetype,
							head->nlist64[i].n_sect, &sym))
			fuc_is_public(&lst, &sym);
		i++;
	}
	return (lst);
}
