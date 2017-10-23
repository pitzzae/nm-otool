/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 09:53:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 11:23:25 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	init_option(void (*f)(t_file *bin, char opt), t_file *bin, char c)
{
	f(bin, c);
}

static void	check_option_type(char *opt, t_file *bin)
{
	int				i;

	i = 0;
	while (opt[++i])
		init_option(bin->option_parser, bin, opt[i]);
}

static void	empty_arg_after_option(t_arg *arg)
{
	if (arg->ac == 1)
	{
		arg->av[1] = " a.out";
		arg->ac++;
	}
}

void		read_option_flag(int ac, t_arg *arg, t_file *bin)
{
	char			**new_av;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (++i < ac)
	{
		if (arg->av[i][0] == '-')
		{
			check_option_type(&arg->av[i][0], bin);
			j++;
		}
	}
	arg->ac = i - j;
	new_av = malloc(sizeof(char*) * ((i - j) + 2));
	i = 0;
	j = 0;
	new_av[0] = NULL;
	while (++i < ac)
		if (arg->av[i][0] != '-')
			new_av[++j] = arg->av[i];
	new_av[++j] = NULL;
	arg->av = new_av;
	empty_arg_after_option(arg);
}
