/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 09:53:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/24 17:46:09 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	check_option_type(char *opt, t_file *bin)
{
	int				i;
	void			(*init_option)(t_file *, char);

	i = 0;
	init_option = bin->option_parser;
	if (!ft_strncmp(opt, "-arch=", 6) && !(bin->d_opt & OT_OPT_F))
	{
		if (!ft_strcmp(&opt[6], "x86_64"))
			bin->arch_opt = CPU_TYPE_X86_64;
		else if (!ft_strcmp(&opt[6], "i386"))
			bin->arch_opt = CPU_TYPE_I386;
		else if (!ft_strcmp(&opt[6], "all"))
			bin->arch_all = 1;
	}
	else
		while (opt[++i])
			init_option(bin, opt[i]);
}

static void	empty_arg_after_option(t_file *bin, t_arg *arg)
{
	if (arg->ac == 1 && bin->display == NM_DISPLAY)
	{
		arg->av[1] = " a.out";
		arg->ac++;
	}
}

static char	**create_new_argv(int ac, t_arg *arg,int i, int j)
{
	char			**new_av;

	arg->ac = i - j;
	new_av = malloc(sizeof(char*) * ((i - j) + 2));
	i = 0;
	j = 0;
	new_av[0] = NULL;
	while (++i < ac)
		if (arg->av[i][0] != '-')
			new_av[++j] = arg->av[i];
	new_av[++j] = NULL;
	return (new_av);
}

void		read_option_flag(int ac, t_arg *arg, t_file *bin)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	bin->d_opt = OT_OPT_NO;
	bin->arch_all = 0;
	while (++i < ac)
	{
		if (arg->av[i][0] == '-')
		{
			check_option_type(&arg->av[i][0], bin);
			j++;
		}
	}
	arg->av = create_new_argv(ac, arg, i, j);
	empty_arg_after_option(bin, arg);
}
