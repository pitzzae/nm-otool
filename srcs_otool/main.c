/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/19 15:59:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

int		main(int ac, char **av)
{
	t_bin		bin;

	if (ac < 2)
	{
		ft_putstr(av[0]);
		ft_putendl(": at least one file must be specified");
		return (0);
	}
	else
		parse_argv(&bin, ac, av);
	return (0);
}
