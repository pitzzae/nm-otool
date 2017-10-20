/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:38:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/20 12:35:03 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	init_lib_nmotool(t_file *bin)
{
	bin->is_arlib = 0;
	bin->func = ft_otool;
	bin->print_error = OT_DISPLAY;
	bin->pos = 0;
	bin->is_print = 0;
	bin->tdb = NULL;
	bin->nfat_arch = 0;
	bin->mach32 = NULL;
	bin->mach64 = NULL;
	bin->lc = NULL;
	bin->lc_t = NULL;
	bin->seg32_c = NULL;
	bin->seg64_c = NULL;
	bin->sec32 = NULL;
	bin->sec64 = NULL;
	bin->sym = NULL;
	bin->head = NULL;
	bin->arch = NULL;
	bin->fat_l = NULL;
	bin->nlist32 = NULL;
	bin->nlist64 = NULL;
	bin->dump = NULL;
	bin->ncmds = 0;
	bin->mmap = NULL;
}

static void	parse_argv_file(t_file *bin, int ac, char **av)
{
	int			i;

	i = 1;
	bin->ac = ac;
	while (i < ac)
	{
		init_lib_nmotool(bin);
		mmap_file(bin, av[i]);
		if (bin->ptr)
		{
			dump_segments(bin);
			munmap(bin->ptr, (size_t)bin->st.st_size);
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	t_file		bin;
	int			argc;
	char		**argv;
	char		*tmp;

	bin.exename = av[0];
	bin.init_lib = init_lib_nmotool;
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
