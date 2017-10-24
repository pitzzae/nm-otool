/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:06:02 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:06:01 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static void	ft_nm_print_error(t_file *bin, char *msg)
{
	ft_putstr_fd(bin->exename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(bin->filename, 2);
	ft_putendl_fd(msg, 2);
}

static void	nm_option_parser(t_file *bin, char opt)
{
	(void)bin;
	(void)opt;
}

static void	init_lib_nmotool(t_file *bin)
{
	bin->is_arlib = 0;
	bin->func = ft_nm;
	bin->print_error = ft_nm_print_error;
	bin->display = NM_DISPLAY;
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
		bin->mmap = bin->ptr;
		if (bin->ptr)
		{
			dump_segments(bin, bin->d_opt);
			munmap(bin->mmap, (size_t)bin->st.st_size);
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	t_file		bin;
	t_arg		arg;

	bin.exename = av[0];
	bin.init_lib = &(init_lib_nmotool);
	bin.option_parser = nm_option_parser;
	bin.display = NM_DISPLAY;
	bin.arch_opt = CPU_TYPE_X86_64;
	arg.ac = ac;
	arg.av = av;
	read_option_flag(ac, &arg, &bin);
	if (arg.ac >= 2)
		parse_argv_file(&bin, arg.ac, arg.av);
	free(arg.av);
	return (0);
}
