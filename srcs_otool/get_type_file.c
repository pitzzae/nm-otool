/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:39:54 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/18 14:39:57 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nmotool.h>

void		get_type_file(void *ptr, t_head *head)
{
	struct fat_header *fat_header;

	head->mach64 = NULL;
	head->mach32 = NULL;
	fat_header = (struct fat_header *)ptr;
	if (fat_header->magic == MH_MAGIC_64)
		head->mach64 = (struct mach_header_64 *)ptr;
	else
		head->mach32 = (struct mach_header *)ptr;
}