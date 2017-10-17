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
# define I(p)		(int)p

# include <stdio.h>
# include <libft.h>
# include <libnmotool.h>

typedef struct		s_symbol
{
	char						address[17];
	char						type;
	char						*name;
}					t_symbol;

typedef struct		s_libar
{
	struct ranlib				*lib;
	struct ar_hdr				*ar;
	char						*start;
	unsigned int				st_len;
	unsigned int				arr_len;
	char						*str;
}					t_libar;

typedef struct		s_seg_com
{
	unsigned char				text;
	unsigned char				data;
	unsigned char				bss;
}					t_seg_com;

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
	t_seg_com					segcom;
}					t_sect;

typedef struct		s_head
{
	struct mach_header			*mach32;
	struct mach_header_64		*mach64;
	struct fat_arch				*arch32;
	struct fat_arch				*arch64;
	struct load_command			*lc;
	struct symtab_command		*sym;
	struct nlist_64				*nlist64;
	struct nlist				*nlist32;
	boolean_t					is_x64;
	t_sect						sect;
}					t_head;

typedef struct		s_bin
{
	int							fd;
	struct stat					st;
	void						*ptr;
	t_head						head;
}					t_bin;

void				parse_argv(t_bin *bin, int ac, char **av);
void				get_type_file(t_bin *bin, char *filename, char *name);
void				find_section_64(t_head *head, t_sect *s);
void				find_section_86(t_head *head, t_sect *s);
void				find_symbol_table(char *ptr, t_head *header);
void				print_section(t_sect *s);
t_list				*print_symbol_table_64(t_head *head, char *ptr);
t_list				*print_symbol_table_86(t_head *head, char *ptr);
void				order_lst(t_list *lst);
void				ft_putargv_error(char *name, char *source, char *msg);
size_t				parse_universel_binary(t_bin *bin);
uint32_t			ft_swapuint32(uint32_t u);
void				get_segment_command(t_head *head);
size_t				add_line_to_lst(void *nlst, t_head *head, t_symbol *sym);

#endif
