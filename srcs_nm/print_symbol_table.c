/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 22:47:27 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 18:16:11 by gtorresa         ###   ########.fr       */
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

static int		is_print_addr(uint64_t n_value, uint8_t n_sect, t_symbol *sym)
{
	int				i;

	i = 0;
	if (n_value > 0 || ((sym->n_type & N_TYPE) == N_SECT && n_sect == 0x01))
		i = 1;
	if (n_value == 0 && ((sym->n_type & N_TYPE) == N_ABS && n_sect == 0x00))
		i = 1;
	return (i);
}

static t_list	*print_symbol_table_32(t_file *bin, void *ptr, t_symbol *sym)
{
	size_t			i;
	t_list			*lst;

	i = 0;
	lst = ft_lstnew(NULL, 0);
	bin->nlist32 = (struct nlist*)(ptr + bin->sym->symoff);
	while (i < bin->sym->nsyms)
	{
		sym->n_type = bin->nlist32[i].n_type;
		sym->n_sect = bin->nlist32[i].n_sect;
		sym->n_value = bin->nlist32[i].n_value;
		sym->name = (void *)(bin->mach32) + bin->sym->stroff +
					bin->nlist32[i].n_un.n_strx;
		ft_bzero(sym->address, 17);
		if (is_print_addr(bin->nlist32[i].n_value, bin->nlist32[i].n_sect, sym))
			print_ptr_addr(bin->nlist32[i].n_value, sym->address,
						bin->dump->is_64);
		else
			ft_strcat(sym->address, S_X32);
		if (is_symtab(sym->n_type))
			add_line_to_lst(bin, sym, &lst);
		i++;
	}
	return (lst);
}

static t_list	*print_symbol_table_64(t_file *bin, void *ptr, t_symbol *sym)
{
	size_t			i;
	t_list			*lst;

	i = 0;
	lst = ft_lstnew(NULL, 0);
	bin->nlist64 = (struct nlist_64*)(ptr + bin->sym->symoff);
	while (i < bin->sym->nsyms)
	{
		sym->name = (void *)(bin->mach64) + bin->sym->stroff +
					bin->nlist64[i].n_un.n_strx;
		sym->n_type = bin->nlist64[i].n_type;
		sym->n_sect = bin->nlist64[i].n_sect;
		sym->n_value = bin->nlist64[i].n_value;
		ft_bzero(sym->address, 17);
		if (is_print_addr(bin->nlist64[i].n_value, bin->nlist64[i].n_sect, sym))
			print_ptr_addr(bin->nlist64[i].n_value, sym->address,
						bin->dump->is_64);
		else
			ft_strcat(sym->address, S_X64);
		if (is_symtab(sym->n_type))
			add_line_to_lst(bin, sym, &lst);
		i++;
	}
	return (lst);
}

t_list			*print_symbol_table(t_file *bin)
{
	t_list			*lst;
	t_symbol		sym;

	if (bin->mach64)
		lst = print_symbol_table_64(bin, (void*)bin->mach64, &sym);
	else
		lst = print_symbol_table_32(bin, (void*)bin->mach32, &sym);
	return (lst);
}
