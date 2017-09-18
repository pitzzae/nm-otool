/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:31:52 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/18 14:31:54 by gtorresa         ###   ########.fr       */
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

static void	print_filename(char *filename)
{
	ft_putstr(filename);
	ft_putendl(":");
}

void		select_print_sections(t_head *headers, char *filename)
{
	t_sect						s;

	print_filename(filename);
	s.seg_text = SEG_TEXT;
	s.sect_text = SECT_TEXT;
	if (headers->mach64)
		find_section_64(headers, &s);
	else if (headers->mach32)
		find_section_86(headers, &s);
}

void		parse_argv(t_bin *bin, char **av)
{
	size_t 		i;

	i = 1;
	while (av[i])
	{
		read_bin(bin, av[i]);
		get_type_file(bin->ptr, &bin->head);
		select_print_sections(&bin->head, av[i]);
		i++;
	}
}
