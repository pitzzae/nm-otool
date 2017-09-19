/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:31:52 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/19 15:19:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nmotool.h>

static void	read_bin(t_bin *bin, char *source)
{
	bin->fd = open(source, O_RDONLY);
	if (bin->fd > 2)
	{
		if (!fstat(bin->fd, &bin->st))
		{
			bin->ptr = mmap(0, bin->st.st_size, PROT_READ, MAP_PRIVATE, bin
					->fd, 0);
		}
		if (bin->st.st_mode & S_IFDIR)
		{
			ft_putstr(source);
			ft_putendl(" Is a directory.");
		}
	}
}

static void	parse_result(t_list *lst)
{
	size_t					i;
	t_symbol				*sym;

	i = 0;
	order_lst(lst);
	while (lst != NULL && (sym = (t_symbol*)lst->content) != NULL)
	{
		ft_putstr(sym->address);
		ft_putchar(' ');
		ft_putchar(sym->type);
		ft_putchar(' ');
		ft_putendl(sym->name);
		lst = lst->next;
		i++;
	}
}

static void	find_symbol_table(char *ptr, t_head *header)
{
	int						i;
	int						j;

	i = 0;
	if (header->mach64)
		j = header->mach64->ncmds;
	else
		j = header->mach32->ncmds;
	while (i < j)
	{
		if (header->lc->cmd == LC_SYMTAB)
		{
			header->sym = (struct symtab_command *)header->lc;
			if (header->mach64)
				parse_result(print_symbol_table_64(header, ptr));
			else
				parse_result(print_symbol_table_86(header, ptr));
			break ;
		}
		header->lc = (void *)header->lc + header->lc->cmdsize;
		i++;
	}
}

void		parse_argv(t_bin *bin, char **av)
{
	size_t 					i;

	i = 1;
	while (av[i])
	{
		read_bin(bin, av[i]);
		get_type_file(bin->ptr, &bin->head);
		find_symbol_table(bin->ptr, &bin->head);
		i++;
	}
}
