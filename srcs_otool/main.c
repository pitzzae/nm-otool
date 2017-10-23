/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:38:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 12:37:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	ft_ot_print_error(t_file *bin, char *msg)
{
	char		*error;
	int			fd;

	fd = 1;
	error = ": is not an object file";
	if (!ft_strcmp(msg, MSG_NM_DIR) || !ft_strcmp(msg, MSG_NM_NOFILE))
	{
		error = MSG_NM_DIR;
		fd = 2;
	}
	ft_putstr_fd(bin->filename, fd);
	ft_putendl_fd(error, fd);
}

static void	ot_option_parser(t_file *bin, char opt)
{
	if (opt == 'f' && !(bin->d_opt & OT_OPT_F))
		bin->d_opt += OT_OPT_F;
	else if (opt == 'a' && !(bin->d_opt & OT_OPT_A))
		bin->d_opt += OT_OPT_A;
	else if (opt == 'h' && !(bin->d_opt & OT_OPT_H))
		bin->d_opt += OT_OPT_H;
	else if (opt == 'l' && !(bin->d_opt & OT_OPT_L))
		bin->d_opt += OT_OPT_L;
	else if (opt == 't' && !(bin->d_opt & OT_OPT_T))
		bin->d_opt += OT_OPT_T;
}

static void	init_lib_nmotool(t_file *bin)
{
	bin->is_arlib = 0;
	bin->func = ft_otool;
	bin->print_error = ft_ot_print_error;
	bin->display = OT_DISPLAY;
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
	bin->option_parser = NULL;
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
	t_arg		arg;

	bin.exename = av[0];
	bin.init_lib = init_lib_nmotool;
	bin.option_parser = ot_option_parser;
	bin.display = OT_DISPLAY;
	arg.ac = ac;
	arg.av = av;
	read_option_flag(ac, &arg, &bin);
	if (arg.ac < 2)
		ft_print_ot_option(&bin);
	else
		parse_argv_file(&bin, arg.ac, arg.av);
	return (0);
}
