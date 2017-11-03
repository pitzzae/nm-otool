/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/03 17:31:26 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	fat_is_select(t_file *bin, int pos)
{
	uint32_t		i;
	int				find_64;

	i = 0;
	find_64 = 0;
	if (bin->arch_all)
		return (1);
	while (i < bin->nfat_arch)
	{
		if (bin->fat_l[i] == bin->arch_opt)
			find_64 = bin->arch_opt;
		i++;
	}
	if (bin->fat_l[pos] == find_64)
		return (1);
	else
		return (0);
}

int			check_lib_option(t_file *bin, int pos)
{
	int				i;

	if (bin->nfat_arch)
		i = fat_is_select(bin, pos);
	else
		i = 1;
	if (i && (!bin->is_print || bin->arch_all))
	{
		bin->is_print = i;
		return (i);
	}
	else
		return (0);
}

static void	char_ar_lib2(t_file *bin, t_arlib *l)
{
	char			tmp1[16];
	char			tmp2[16];
	void			(*ft_nm_print_error)(t_file *, char *);

	ft_bzero(tmp1, 16);
	ft_bzero(tmp2, 16);
	ft_putadd((void*)(l->str - 4), &tmp1[0]);
	ft_putadd(bin->ptr + bin->st.st_size, &tmp2[0]);
	ft_nm_print_error = bin->print_error;
	if (ft_strcmp(tmp1, tmp2) <= 0)
	{
		l->arr_len = *(unsigned int*)(l->str - 4);
		l->str += l->arr_len;
	}
	else
	{
		ft_nm_print_error(bin, MSG_NM_TRUNC);
		bin->error_order = 1;
		l->str = NULL;
	}
}

void		char_ar_lib(t_file *bin, t_arlib *l)
{
	char			tmp1[16];
	char			tmp2[16];
	void			(*ft_nm_print_error)(t_file *, char *);

	ft_bzero(tmp1, 16);
	ft_bzero(tmp2, 16);
	ft_putadd((void*)(l->str - 4), &tmp1[0]);
	ft_putadd(bin->ptr + bin->st.st_size, &tmp2[0]);
	ft_nm_print_error = bin->print_error;
	if (ft_strcmp(tmp1, tmp2) <= 0)
	{
		l->arr_len = *(unsigned int*)(l->str - 4);
		l->str += l->arr_len;
		char_ar_lib2(bin, l);
	}
	else
	{
		ft_nm_print_error(bin, MSG_NM_TRUNC);
		bin->error_order = 1;
		l->str = NULL;
	}
}
