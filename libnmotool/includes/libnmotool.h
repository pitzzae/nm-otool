/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libnmotool.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:02:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/17 15:02:21 by gtorresa         ###   ########.fr       */
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

typedef struct		s_file
{
	char 						*filename;
	char 						*exename;
	int							fd;
	struct stat					st;
	void						*ptr;
	struct fat_header			*head;
	struct fat_arch				*arch;
	struct mach_header			*mach32;
	struct mach_header_64		*mach64;
	t_dump						*dump;
}					t_file;

void		dump_segments(t_file *bin);
void		dump_fat_header(t_file *bin);
void		dump_mach_header(t_file *bin);
void 		mmap_file(t_file *bin, char *path);

#endif
