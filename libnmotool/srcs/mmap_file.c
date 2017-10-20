/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:21:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/20 14:22:35 by gtorresa         ###   ########.fr       */
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

static int	is_recognized_file(t_file *bin)
{
	unsigned char			buffer[9];
	struct fat_header		*header;
	int						bytes_read;

	buffer[8] = '\0';
	bytes_read = read(bin->fd, buffer, 8);
	if (bytes_read != 8)
		return (1);
	header = (struct fat_header*)buffer;
	if (is_magic_header(header->magic))
		return (0);
	if (!ft_strcmp((char*)buffer, ARMAG))
		return (0);
	return (1);
}

static void	ft_print_error(void (*print_error)(t_file *bin, char *msg),
							t_file *bin, char *msg)
{
	print_error(bin, msg);
}

void		mmap_file(t_file *bin, char *file)
{
	bin->ptr = NULL;
	bin->filename = file;
	bin->fd = open(bin->filename, O_RDONLY);
	if (bin->fd > 2 && !fstat(bin->fd, &bin->st))
	{
		if (bin->st.st_mode & S_IFDIR)
			ft_print_error(bin->print_error, bin, MSG_NM_DIR);
		else if (is_recognized_file(bin))
			ft_print_error(bin->print_error, bin, MSG_NM_NOOBJ);
		else
			bin->ptr = mmap(0, (size_t)bin->st.st_size,
						PROT_READ, MAP_PRIVATE, bin->fd, 0);
	}
	else
		ft_print_error(bin->print_error, bin, MSG_NM_NOFILE);
	close(bin->fd);
}
