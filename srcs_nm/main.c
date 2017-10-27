/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:06:02 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 18:16:14 by gtorresa         ###   ########.fr       */
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
	init_libnmotool(bin);
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
		if (bin->mmap)
		{
			if (bin->ptr)
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
	if (sizeof(int*) == 8)
		bin.arch_opt = CPU_TYPE_X86_64;
	else if (sizeof(int*) == 4)
		bin.arch_opt = CPU_TYPE_I386;
	arg.ac = ac;
	arg.av = av;
	read_option_flag(ac, &arg, &bin);
	if (arg.ac >= 2 && bin.arch_opt != 0)
		parse_argv_file(&bin, arg.ac, arg.av);
	else
		ft_print_nm_option(&bin);
	free(arg.av);
	return (0);
}
