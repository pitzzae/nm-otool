/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:06:02 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 21:51:04 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	parse_argv_file(t_file *bin, int ac, char **av)
{
	int			i;

	i = 1;
	while (i < ac)
	{
		mmap_file(bin, av[i]);
		if (bin->ptr)
		{
			dump_segments(bin);
			munmap(bin->ptr, (size_t)bin->st.st_size);
		}
		i++;
	}
}

static void	init_lib_nmotool(t_file *bin)
{
	bin->is_arlib = 0;
	bin->func = ft_nm;
	bin->print_error = NM_DISPLAY;
	bin->pos = 0;
	bin->is_print = 0;
	bin->tdb = NULL;
	bin->nfat_arch = 0;
}

int			main(int ac, char **av)
{
	t_file		bin;
	int			argc;
	char		**argv;
	char		*tmp;

	bin.exename = av[0];
	init_lib_nmotool(&bin);
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
		parse_argv_file(&bin, argc, argv);
	return (0);
}
