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
		if (s && ft_strcmp(s->name, sym->name) == 0 && sym->type == 't' &&
			ft_strcmp(s->address, sym->address) == 0)
		{
			s->type = 'T';
			return ;
		}
		l = l->next;
	}
	ft_lstadd(lst, ft_lstnew(sym, sizeof(*sym)));
}

static t_list	*print_symbol_table_32(t_file *bin, void *ptr)
{
	size_t			i;
	t_list			*lst;
	t_symbol		sym;

	i = 0;
	(void)ptr;
	lst = ft_lstnew(NULL, 0);
	bin->nlist32 = (struct nlist*)(ptr + bin->sym->symoff);
	while (i < bin->sym->nsyms)
	{
		ft_bzero(sym.address, 17);
		if (bin->nlist32[i].n_value > 0)
			print_ptr_addr(bin->nlist32[i].n_value, sym.address,
						   bin->dump->is_64);
		else
			ft_strcat(sym.address, S_X86);
		sym.name = (void *)(bin->mach32) + bin->sym->stroff +
				bin->nlist32[i].n_un.n_strx;
		if (add_line_to_lst((void*)(&bin->nlist64[i]), bin, &sym))
			fuc_is_public(&lst, &sym);
		i++;
	}
	return (lst);
}

static t_list	*print_symbol_table_64(t_file *bin, void *ptr)
{
	size_t			i;
	t_list			*lst;
	t_symbol		sym;


	i = 0;
	lst = ft_lstnew(NULL, 0);
	bin->nlist64 = (struct nlist_64*)(ptr + bin->sym->symoff);
	while (i < bin->sym->nsyms)
	{
		/*
		uint8_t io1;
		uint8_t io2;

		uint8_t io3 = N_UNDF;
		uint8_t io4 = N_PBUD;
		uint8_t io5 = N_ABS;
		uint8_t io6 = N_SECT;
		uint8_t io7 = N_INDR;

		io1 = bin->nlist64[i].n_type & N_TYPE;
		io2 = bin->nlist64[i].n_type & N_EXT;

		struct nlist_64	s = bin->nlist64[i];
		*/
		ft_bzero(sym.address, 17);
		if (bin->nlist64[i].n_value > 0)
			print_ptr_addr(bin->nlist64[i].n_value, sym.address,
						   bin->dump->is_64);
		else
			ft_strcat(sym.address, S_X64);
		sym.name = (void *)(bin->mach64) + bin->sym->stroff +
				bin->nlist64[i].n_un.n_strx;
		if (ft_strcmp(sym.name, "_CentSigMsg") == 0)
			;
		if (add_line_to_lst((void*)(&bin->nlist64[i]), bin, &sym))
			fuc_is_public(&lst, &sym);
		i++;
	}
	return (lst);
}

t_list		*print_symbol_table(t_file *bin)
{
	t_list			*lst;

	if (bin->mach64)
		lst = print_symbol_table_64(bin, (void*)bin->mach64);
	else
		lst = print_symbol_table_32(bin, (void*)bin->mach32);
	return (lst);
}