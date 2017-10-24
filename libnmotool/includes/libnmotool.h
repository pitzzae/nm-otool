/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnmotool.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:02:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/24 14:57:38 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNMOTOOL_H
# define LIBNMOTOOL_H
# define NM_DISPLAY 0
# define OT_DISPLAY 1

# define OT_OPT_NO 0x00
# define OT_OPT_F 0x01
# define OT_OPT_A 0x02
# define OT_OPT_H 0x04
# define OT_OPT_T 0x10

# define MSG_NM_DIR ": Is a directory."
# define MSG_NM_NOOBJ ": The file was not recognized as a valid object file"
# define MSG_NM_NOFILE ": No such file or directory."

# include <libft.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <ar.h>
# include <sys/mman.h>

typedef struct		s_arg
{
	char						**av;
	int							ac;
}					t_arg;

typedef struct		s_dump
{
	int							is_64;
	int							is_swap;
	int							fat;
}					t_dump;

typedef struct		s_arlib
{
	struct ranlib				*lib;
	struct ar_hdr				*ar;
	char						*start;
	unsigned int				st_len;
	unsigned int				arr_len;
	char						*str;
}					t_arlib;

typedef struct		s_tdb_nsect
{
	unsigned char				text_nsect;
	unsigned char				data_nsect;
	unsigned char				bss_nsect;
}					t_tdb_nsect;

typedef struct		s_file
{
	char						*filename;
	char						*exename;
	int							ac;
	int							is_arlib;
	int							fd;
	struct stat					st;
	void						*ptr;
	void						*mmap;
	void						*func;
	void						*init_lib;
	void						*print_error;
	void						*option_parser;
	int							display;
	uint32_t					d_opt;
	int							arch_opt;
	int							arch_all;
	struct fat_header			*head;
	struct fat_arch				*arch;
	int							*fat_l;
	uint32_t					nfat_arch;
	uint32_t					ncmds;
	uint32_t					pos;
	struct mach_header			*mach32;
	struct mach_header_64		*mach64;
	struct load_command			*lc;
	struct load_command			**lc_t;
	struct segment_command		**seg32_c;
	struct segment_command_64	**seg64_c;
	struct section				**sec32;
	struct section_64			**sec64;
	struct symtab_command		*sym;
	struct nlist_64				*nlist64;
	struct nlist				*nlist32;
	t_dump						*dump;
	t_tdb_nsect					*tdb;
	t_arlib						*ar_lib;
	int							is_print;
}					t_file;

void		read_option_flag(int ac, t_arg *arg, t_file *bin);
void		mmap_file(t_file *bin, char *path);
void		dump_segments(t_file *bin, uint32_t d_opt);
void		dump_fat_header(t_file *bin);
void		dump_mach_header(t_file *bin);
void		dump_load_commands(t_file *bin);
void		dump_static_lib(t_file *bin);
int			check_lib_option(t_file *bin, int pos);
int			check_magic_number(t_file *bin);
void		dump_section_name(t_file *bin);
void		ft_swap_fat_header(t_file *bin, struct fat_header *header);
void		ft_swap_fat_arch(t_file *bin, struct fat_arch *arch);

#endif
