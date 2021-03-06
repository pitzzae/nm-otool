/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/03 15:22:10 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMOTOOL_H
# define FT_NMOTOOL_H
# define S_X64 "                "
# define S_X32 "        "

# include <stdio.h>
# include <libft.h>
# include <libnmotool.h>

typedef struct		s_symbol
{
	char						address[17];
	char						type;
	char						*name;
	uint8_t						n_type;
	uint8_t						n_sect;
	uint64_t					n_value;
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
void				ft_print_ot_option(t_file *bin);
void				ft_otool_h(t_file *bin);
void				ft_otool_a(t_file *bin);
void				ft_otool_t(t_file *bin);
void				ft_otool_f(t_file *bin);
void				ft_otool(t_file *bin);

void				ft_nm(t_file *bin);
void				ft_print_nm_option(t_file *bin);
t_list				*print_symbol_table(t_file *bin);
void				add_line_to_lst(t_file *bin, t_symbol *sym, t_list **lst);
void				order_lst(t_file *bin, t_list *lst);
int					is_symtab(uint8_t n_type);

#endif
