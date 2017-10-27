/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:44:33 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 18:16:11 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void		ft_otool_a(t_file *bin)
{
	char			**tmp;
	int				i;

	i = 0;
	tmp = ft_strsplit(bin->ar_lib->ar->ar_name, ' ');
	ft_putstr_whsp(tmp[4], '0', 7);
	ft_putstr(" ");
	ft_putstr(tmp[2]);
	ft_putstr("/");
	ft_putstr(tmp[3]);
	ft_putstr(" ");
	ft_putstr_whsp(tmp[5], ' ', 5);
	ft_putstr(" ");
	ft_putstr(tmp[1]);
	ft_putstr(" ");
	ft_putstr(tmp[0]);
	ft_putstr("\n");
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}
