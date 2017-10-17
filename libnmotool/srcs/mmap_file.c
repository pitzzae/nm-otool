/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 16:21:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/17 16:21:18 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	ft_putargv_error(t_file *bin, char *msg)
{
	ft_putstr_fd(bin->exename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(bin->filename, 2);
	ft_putendl_fd(msg, 2);
}

void 		mmap_file(t_file *bin, char *file)
{
	bin->ptr = NULL;
	bin->filename = file;
	bin->fd = open(bin->filename, O_RDONLY);
	if (bin->fd > 2 && !fstat(bin->fd, &bin->st))
		bin->ptr = mmap(0, (size_t)bin->st.st_size,
						PROT_READ, MAP_PRIVATE, bin->fd, 0);
	else
		ft_putargv_error(bin, ": No such file or directory.");
	close(bin->fd);
}
