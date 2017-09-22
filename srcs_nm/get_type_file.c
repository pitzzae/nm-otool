/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:39:54 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 17:18:35 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nmotool.h>

static void	print_file_lib(char *ptr, int size)
{
	struct fat_header	*fat_header;
	t_bin				bin;

	bin.ptr = ptr;
	bin.st.st_size = size;
	fat_header = (struct fat_header *)bin.ptr;
	if (fat_header->magic == MH_MAGIC_64)
	{
		bin.head.mach64 = (struct mach_header_64 *)bin.ptr;
		bin.head.lc = bin.ptr + sizeof(*bin.head.mach64);
		bin.head.is_x64 = TRUE;
		find_symbol_table(ptr, &bin.head);
	}
	else if (fat_header->magic == MH_MAGIC)
	{
		bin.head.mach32 = (struct mach_header *)bin.ptr;
		bin.head.lc = bin.ptr + sizeof(*bin.head.mach32);
		bin.head.is_x64 = FALSE;
		find_symbol_table(ptr, &bin.head);
	}
}

static void	print_file_lib_path(char *path, char *obj)
{
	ft_putendl("");
	ft_putstr(path);
	ft_putchar('(');
	ft_putstr(obj);
	ft_putendl("):");
}

static void	print_error_filetype(char *name, char *filename)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(": The file was not recognized as a valid object file", 2);
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
	{
		bin->head.mach64 = (struct mach_header_64 *)bin->ptr;
		bin->head.lc = bin->ptr + sizeof(*bin->head.mach64);
		bin->head.is_x64 = TRUE;
	}
	else if (fat_header->magic == MH_MAGIC)
	{
		bin->head.mach32 = (struct mach_header *)bin->ptr;
		bin->head.lc = bin->ptr + sizeof(*bin->head.mach32);
		bin->head.is_x64 = FALSE;
	}
	else if (!ft_strncmp((char*)bin->ptr, ARMAG, SARMAG))
		get_type_file_lib(bin, filename);
	else if (parse_universel_binary(bin))
		get_type_file_lib(bin, filename);
	else
		print_error_filetype(name, filename);
}
