/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/19 15:59:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

int		main(int ac, char **av)
{
	t_bin		bin;
	int			argc;
	char		**argv;
	char		*tmp;

	if (ac == 1)
	{
		tmp = ft_strjoin(av[0], " a.out");
		argv = ft_strsplit(tmp, ' ');
		free(tmp);
		argc = 2;
	}
	else
	{
		argv = av;
		argc = ac;
	}
	if (argc < 2)
		return (0);
	else
		parse_argv(&bin, argc, argv);
	return (0);
}
