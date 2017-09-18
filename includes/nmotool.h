/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/18 14:47:29 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_NMOTOOL_H_H
#define FT_OTOOL_NMOTOOL_H_H

# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

typedef struct				s_head
{
    struct mach_header			*mach32;
    struct mach_header_64		*mach64;
} t_head;


typedef struct				s_seg_x64
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
} t_seg_x64;

typedef struct				s_sect
{
	char						*start;
	char						*end;
	uint64_t					offset;
	boolean_t					len64;
	char 						*seg_text;
	char 						*sect_text;
	t_seg_x64					x64;
} t_sect;

typedef struct				s_bin
{
    int							fd;
    struct stat					st;
    void						*ptr;
    t_head                  	head;
}                           	t_bin;

void		parse_argv(t_bin *bin, char **av);
void		get_type_file(void *ptr, t_head *head);
void		find_section_64(t_head *head, t_sect *s);
void		print_section(t_sect *s);

#endif //FT_OTOOL_NMOTOOL_H_H
