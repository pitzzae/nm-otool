/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/18 15:53:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_NMOTOOL_H_H
#define FT_OTOOL_NMOTOOL_H_H

# include <sys/stat.h>
# include <mach/boolean.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>

typedef struct				s_head
{
    struct mach_header		*mach32;
    struct mach_header_64	*mach64;
} t_head;

typedef struct				s_sect
{
	char					*start;
	char					*end;
	uint64_t				offset;
	boolean_t				len64;
} t_sect;

typedef struct				s_bin
{
    int						fd;
    struct stat				st;
    void					*ptr;
    t_head                  head;
}                           t_bin;

void		get_binary_headers(void *ptr, t_head *head);

#endif //FT_OTOOL_NMOTOOL_H_H
