/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_static_lib.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 23:37:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/18 11:45:23 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	print_file_lib(t_file *bin, char *ptr, int size)
{
	t_file				bin_tmp;

	bin_tmp.ptr = ptr;
	bin_tmp.st.st_size = size;
	bin_tmp.func = bin->func;
	bin_tmp.filename = bin->filename;
	bin_tmp.is_arlib = 1;
	dump_segments(&bin_tmp);
}

static void	print_file_lib_path(char *path, char *obj)
{
	ft_putstr(path);
	ft_putchar('(');
	ft_putstr(obj);
	ft_putendl("):");
}

static void	init_arlib(t_file *bin, t_arlib *l)
{
	char				*ptr;

	if (bin->dump->is_64)
		ptr = (char*)bin->mach64;
	else
		ptr = (char*)bin->mach32;
	l->start = ptr + sizeof(struct ar_hdr) + SARMAG + 20;
	l->st_len = *(unsigned int*)l->start / sizeof(struct ranlib);
	l->lib = (struct ranlib*)(l->start + 4);
	l->str = (void*)l->lib + l->st_len * sizeof(struct ranlib) + 4;
	l->arr_len = *(unsigned int*)(l->str - 4);
	l->str += l->arr_len;
	ft_putstr("Archive : ");
	ft_putendl(bin->filename);
}

void	dump_static_lib(t_file *bin)
{
	t_arlib				l;
	int					i;
	int					j;

	i = 0;
	init_arlib(bin, &l);
	while (++i < (int)l.arr_len && l.str)
	{
		if (ft_strstr(l.str, "SYMDEF") != NULL)
			continue;
		l.ar = (struct ar_hdr*)l.str;
		l.str += sizeof(struct ar_hdr);
		if (ft_strlen(l.ar->ar_name) > 0)
		{
			j = ft_atoi(ft_strchr(l.ar->ar_name, '/') + 1);
			print_file_lib_path(bin->filename, l.str);
			print_file_lib(bin, l.str + j, ft_atoi(l.ar->ar_size));
			l.str += j;
			l.str += ft_atoi(l.ar->ar_size) - j;
		}
		else
			l.str = NULL;
	}
}
