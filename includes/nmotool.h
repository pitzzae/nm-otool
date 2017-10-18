/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/20 17:10:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMOTOOL_H
# define FT_NMOTOOL_H
# define S_X64 "                "
# define S_X86 "        "

# include <stdio.h>
# include <libft.h>
# include <libnmotool.h>

typedef struct		s_symbol
{
	char						address[17];
	char						type;
	char						*name;
}					t_symbol;

typedef struct		s_seg_x64
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
}					t_seg_x64;

typedef struct		s_seg_x86
{
	struct segment_command		*seg;
	struct section				*sec;
}					t_seg_x86;

typedef struct		s_sect
{
	char						*start;
	char						*end;
	uint64_t					offset;
	boolean_t					len64;
	char						*seg_text;
	char						*sect_text;
	t_seg_x64					x64;
	t_seg_x86					x86;
}					t_sect;

void				find_section_64(t_file *bin, t_sect *s);
void				find_section_32(t_file *bin, t_sect *s);
void				print_section(t_sect *s);
void				ft_otool(t_file *bin);

void				ft_nm(t_file *bin);
t_list				*print_symbol_table(t_file *bin);
size_t				add_line_to_lst(void *nlst, t_file *bin, t_symbol *sym);
void				order_lst(t_list *lst);

#endif
