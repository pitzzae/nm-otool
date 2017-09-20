/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:39:54 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 20:12:43 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nmotool.h>

static void	print_file_lib(char *ptr, int size)
{
	struct fat_header	*fat_header;
	t_bin				bin;
	t_sect				s;

	s.seg_text = SEG_TEXT;
	s.sect_text = SECT_TEXT;
	bin.ptr = ptr;
	bin.st.st_size = size;
	fat_header = (struct fat_header *)bin.ptr;
	if (fat_header->magic == MH_MAGIC_64)
	{
		bin.head.mach64 = (struct mach_header_64 *)bin.ptr;
		find_section_64(&bin.head, &s);
	}
	else if (fat_header->magic == MH_MAGIC)
	{
		bin.head.mach32 = (struct mach_header *)bin.ptr;
		find_section_86(&bin.head, &s);
	}
}

static void	print_file_lib_path(char *path, char *obj)
{
	ft_putstr(path);
	ft_putchar('(');
	ft_putstr(obj);
	ft_putendl("):");
}

static void	get_type_file_lib(t_bin *bin, char *filename)
{
	t_libar				l;
	int					i;
	int					j;

	l.start = bin->ptr + sizeof(struct ar_hdr) + SARMAG + 20;
	l.st_len = *(unsigned int*)l.start / sizeof(struct ranlib);
	l.lib = (struct ranlib*)(l.start + 4);
	l.str = (void*)l.lib + l.st_len * sizeof(struct ranlib) + 4;
	l.arr_len = *(unsigned int*)(l.str - 4);
	l.str += l.arr_len;
	ft_putstr("Archive : ");
	ft_putendl(filename);
	i = 0;
	while (++i < (int)l.arr_len && l.str - (char *)bin->ptr < bin->st.st_size)
	{
		if (ft_strstr(l.str, "SYMDEF") != NULL)
			continue;
		l.ar = (struct ar_hdr*)l.str;
		l.str += sizeof(struct ar_hdr);
		j = ft_atoi(ft_strchr(l.ar->ar_name, '/') + 1);
		print_file_lib_path(filename, l.str);
		print_file_lib(l.str + j, ft_atoi(l.ar->ar_size));
		l.str += j;
		l.str += ft_atoi(l.ar->ar_size) - j;
	}
}

void		get_type_file(t_bin *bin, char *filename, char *name)
{
	struct fat_header	*fat_header;

	bin->head.mach64 = NULL;
	bin->head.mach32 = NULL;
	fat_header = (struct fat_header *)bin->ptr;
	if (fat_header->magic == MH_MAGIC_64)
		bin->head.mach64 = (struct mach_header_64 *)bin->ptr;
	else if (fat_header->magic == MH_MAGIC)
		bin->head.mach32 = (struct mach_header *)bin->ptr;
	else if (!ft_strncmp((char*)bin->ptr, ARMAG, SARMAG))
		get_type_file_lib(bin, filename);
	else
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": The file was not recognized", 2);
		ft_putendl_fd(" as a valid object file", 2);
	}
}
