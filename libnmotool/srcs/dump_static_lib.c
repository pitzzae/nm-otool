/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_static_lib.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 23:37:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 16:40:07 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	print_file_lib(t_file *bin, char *ptr, int size)
{
	void				(*init_lib_nmotool)(t_file *);
	t_file				bin_tmp;
	uint32_t			tmp;

	tmp = bin->nfat_arch;
	init_lib_nmotool = bin->init_lib;
	init_lib_nmotool(&bin_tmp);
	bin_tmp.init_lib = bin->init_lib;
	bin_tmp.ptr = ptr;
	bin_tmp.st.st_size = size;
	bin_tmp.func = bin->func;
	bin_tmp.filename = bin->filename;
	bin_tmp.is_arlib = 1;
	bin_tmp.is_print = 0;
	bin_tmp.d_opt = bin->d_opt;
	bin_tmp.ar_lib = bin->ar_lib;
	bin_tmp.arch_opt = bin->arch_opt;
	bin_tmp.arch_all = bin->arch_all;
	bin_tmp.nfat_arch = tmp;
	dump_segments(&bin_tmp, bin_tmp.d_opt);
}

static void	print_file_lib_path(t_file *bin, char *obj)
{
	if (bin->display == NM_DISPLAY)
		ft_putendl("");
	if (bin->display == NM_DISPLAY || bin->d_opt & OT_OPT_T)
	{
		ft_putstr(bin->filename);
		ft_putchar('(');
		ft_putstr(obj);
		ft_putendl("):");
	}
}

static void	print_archive_header(t_file *bin, t_arlib *l, void *ptr)
{
	void				(*ft_otool)(t_file *bin);

	ft_otool = bin->func;
	l->ar = (struct ar_hdr*)ptr;
	ft_otool(bin);
}

static void	init_arlib(t_file *bin, t_arlib *l)
{
	char				*ptr;

	if (bin->dump->is_64)
		ptr = (char*)bin->mach64;
	else if (bin->mach32)
		ptr = (char*)bin->mach32;
	else
		ptr = (char*)((bin->ptr) + bin->arch->offset);
	l->start = ptr + sizeof(struct ar_hdr) + SARMAG + 20;
	if (bin->display == OT_DISPLAY)
	{
		if (bin->d_opt & OT_OPT_F)
			print_archive_header(bin, l, ptr + SARMAG);
		ft_putstr("Archive : ");
		ft_putendl(bin->filename);
		if (bin->d_opt & OT_OPT_A)
			print_archive_header(bin, l, ptr + SARMAG);
	}
	l->st_len = *(unsigned int*)l->start / sizeof(struct ranlib);
	l->lib = (struct ranlib*)(l->start + 4);
	l->str = (void*)l->lib + l->st_len * sizeof(struct ranlib) + 4;
	l->arr_len = *(unsigned int*)(l->str - 4);
	l->str += l->arr_len;
}

void		dump_static_lib(t_file *bin)
{
	t_arlib				l;
	int					j;

	bin->ar_lib = &l;
	init_arlib(bin, &l);
	while (l.str)
	{
		if (ft_strstr(l.str, "SYMDEF") != NULL)
		{
			l.str = NULL;
			continue ;
		}
		l.ar = (struct ar_hdr*)l.str;
		l.str += sizeof(struct ar_hdr);
		if (ft_strlen(l.ar->ar_name) > 0)
		{
			j = ft_atoi(ft_strchr(l.ar->ar_name, '/') + 1);
			print_file_lib_path(bin, l.str);
			print_file_lib(bin, l.str + j, ft_atoi(l.ar->ar_size));
			l.str += ft_atoi(l.ar->ar_size);
		}
		else
			l.str = NULL;
	}
}
