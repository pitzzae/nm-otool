/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:21:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 19:13:57 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	is_magic_header(uint32_t magic)
{
	if (magic == MH_MAGIC ||
		magic == MH_MAGIC_64 ||
		magic == MH_CIGAM ||
		magic == MH_CIGAM_64 ||
		magic == FAT_MAGIC ||
		magic == FAT_CIGAM)
		return (1);
	return (0);
}

static int	isnt_recognized_file(t_file *bin)
{
	unsigned char			buffer[9];
	struct fat_header		*header;

	header = (struct fat_header*)bin->mmap;
	ft_strncat((char*)(&buffer[0]), (char*)bin->mmap, 8);
	if (is_magic_header(header->magic))
		return (0);
	if (!ft_strcmp((char*)buffer, ARMAG))
		return (0);
	return (1);
}

void		mmap_file(t_file *bin, char *file)
{
	void					(*print_error)(t_file *, char *);

	print_error = bin->print_error;
	bin->ptr = NULL;
	bin->mmap = NULL;
	bin->filename = file;
	bin->fd = open(bin->filename, O_RDONLY);
	if (bin->fd > 2 && !fstat(bin->fd, &bin->st))
	{
		if (bin->st.st_mode & S_IFDIR)
			print_error(bin, MSG_NM_DIR);
		else
		{
			bin->mmap = mmap(0, (size_t) bin->st.st_size,
						PROT_READ, MAP_PRIVATE, bin->fd, 0);
			if (isnt_recognized_file(bin))
				print_error(bin, MSG_NM_NOOBJ);
			else
				bin->ptr = bin->mmap;
		}
	}
	else
		print_error(bin, MSG_NM_NOFILE);
	close(bin->fd);
}
