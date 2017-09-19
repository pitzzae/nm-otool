/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:31:52 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/19 17:47:24 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nmotool.h>

static int	read_bin(t_bin *bin, char *source)
{
	int			i;

	i = 1;
	bin->fd = open(source, O_RDONLY);
	if (bin->fd > 2 && !fstat(bin->fd, &bin->st))
	{
		bin->ptr = mmap(0, (size_t) bin->st.st_size,
						PROT_READ,	MAP_PRIVATE, bin->fd, 0);
		if (bin->st.st_mode & S_IFDIR)
		{
			ft_putstr(source);
			ft_putendl(": Is a directory.");
			i = 0;
		}
		if (bin->st.st_size == 0)
			i = 0;
	}
	else
	{
		ft_putstr(source);
		ft_putendl(": No such file or directory.");
		i = 0;
	}
	close(bin->fd);
	return (i);
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
		free(lst->content);
		free(lst);
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

static void	print_filename(int ac, char *filename)
{
	if (ac > 2)
	{
		ft_putendl("");
		ft_putstr(filename);
		ft_putendl(":");
	}
}

void		parse_argv(t_bin *bin, int ac, char **av)
{
	int						i;

	i = 1;
	while (i < ac && av[i])
	{
		if (read_bin(bin, av[i]))
		{
			get_type_file(bin->ptr, &bin->head, av[i]);
			print_filename(ac, av[i]);
			if (bin->head.mach64 || bin->head.mach32)
				find_symbol_table(bin->ptr, &bin->head);
			if (munmap(bin->ptr, (size_t) bin->st.st_size) < 0)
				return ;
		}
		i++;
	}
}
