/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2016/11/02 15:53:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

int		main(int ac, char **av)
{
	int			fd;
	char		*buf;

	if (ac < 2)
		return (0);
	else
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &buf) == 1)
		{
			printf("%s\n", buf);
		}
	}
}