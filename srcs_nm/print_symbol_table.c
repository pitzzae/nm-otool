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
	ft_putstr(buff);
	ft_bzero(buff, 16);
}

void		print_symbol_table_86(t_head *head, char *ptr)
{
	int				i;
	char 			buff[16];

	i = 0;
	head->nlist32 = (void *)ptr + head->sym->symoff;
	while (i < head->sym->nsyms)
	{
		if (head->nlist32[i].n_value > 0)
			print_ptr_address(head->nlist32[i].n_value, buff, head->is_x64);
		else
			ft_putstr("        ");
		if ((head->nlist32[i].n_type & N_TYPE) == 14)
			ft_putstr(" T ");
		else
			ft_putstr(" U ");
		ft_putendl(ptr + head->sym->stroff + head->nlist32[i].n_un.n_strx);
		i++;
	}
}

void		print_symbol_table_64(t_head *head, char *ptr)
{
	int				i;
	char 			buff[16];

	i = 0;
	head->nlist64 = (void *)ptr + head->sym->symoff;
	while (i < head->sym->nsyms)
	{
		if (head->nlist64[i].n_value > 0)
			print_ptr_address(head->nlist64[i].n_value, buff, head->is_x64);
		else
			ft_putstr("                ");
		if ((head->nlist64[i].n_type & N_TYPE) == 14)
			ft_putstr(" T ");
		else
			ft_putstr(" U ");
		ft_putendl(ptr + head->sym->stroff + head->nlist64[i].n_un.n_strx);
		i++;
	}
}
