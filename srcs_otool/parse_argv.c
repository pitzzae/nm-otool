/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:31:52 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 17:26:54 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nmotool.h>

static void	ft_putargv_error(char *name, char *source, char *msg)
{
	ft_putstr(name);
	ft_putstr(": ");
	ft_putstr(source);
	ft_putendl(msg);
}

static int	read_bin(t_bin *bin, char *source, char *name)
{
	int			i;

	i = 1;
	bin->fd = open(source, O_RDONLY);
	if (bin->fd > 2 && !fstat(bin->fd, &bin->st))
	{
		bin->ptr = mmap(0, (size_t)bin->st.st_size,
						PROT_READ, MAP_PRIVATE, bin->fd, 0);
		if (bin->st.st_mode & S_IFDIR)
		{
			ft_putargv_error(name, source, ": Is a directory.");
			i = 0;
		}
		if (bin->st.st_size == 0)
			i = 0;
	}
	else
	{
		ft_putargv_error(name, source, ": No such file or directory.");
		i = 0;
	}
	close(bin->fd);
	return (i);
}

static void	print_filename(char *filename)
{
	ft_putstr(filename);
	ft_putendl(":");
}

static void	select_print_sections(t_head *headers, char *filename)
{
	t_sect		s;

	print_filename(filename);
	s.seg_text = SEG_TEXT;
	s.sect_text = SECT_TEXT;
	if (headers->mach64)
		find_section_64(headers, &s);
	else if (headers->mach32)
		find_section_86(headers, &s);
}

void		parse_argv(t_bin *bin, int ac, char **av)
{
	int			i;

	i = 1;
	while (i < ac && av[i])
	{
		if (read_bin(bin, av[i], av[0]))
		{
			get_type_file(bin, av[i], av[0]);
			if (bin->head.mach64 || bin->head.mach32)
				select_print_sections(&bin->head, av[i]);
			if (munmap(bin->ptr, (size_t)bin->st.st_size) < 0)
				return ;
		}
		i++;
	}
}
