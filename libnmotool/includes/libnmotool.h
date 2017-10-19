/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnmotool.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:02:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 17:34:09 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBNMOTOOL_H
# define LIBNMOTOOL_H

# include <libft.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <ar.h>
# include <sys/mman.h>

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
	char 						*filename;
	char 						*exename;
	int 						is_arlib;
	int							fd;
	struct stat					st;
	void						*ptr;
	void						*func;
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
	int 						is_print;
}					t_file;

void		dump_segments(t_file *bin);
void		dump_fat_header(t_file *bin);
void		dump_mach_header(t_file *bin);
void		dump_load_commands(t_file *bin);
void		dump_static_lib(t_file *bin);
int 		check_lib_option(t_file *bin, int pos);
int 		check_magic_number(t_file *bin);
void		dump_section_name(t_file *bin);
void		mmap_file(t_file *bin, char *path);
void		ft_swap_fat_header(t_file *bin, struct fat_header *header);
void		ft_swap_fat_arch(t_file *bin, struct fat_arch *arch);

#endif
