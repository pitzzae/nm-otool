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

void	*ft_strcat_chr(char *dst, const char c)
{
    size_t	j;

    j = 0;
    while (dst[j] != '\0')
        j++;
    dst[j++] = c;
    dst[j] = '\0';
    return (dst);
}


static void		ft_putbase(unsigned long n, char *buf, int base)
{
    char		c;

    if (n / base > 0)
    {
        ft_putbase((n / base), buf, base);
        n = n % base;
    }
    c = (char) (n < 10 ? '0' : 'a' - 10);
    c = (char) (c + n);
    ft_strcat_chr(buf, c);
}


int		main(int ac, char **av)
{
	int			fd;
	char		buf[16];
    char        r[2048000];

	if (ac < 2)
		return (0);
	else
	{
		fd = open(av[1], O_RDONLY);
		while (read(fd, buf, 1))
		{
            ft_putbase(buf[0], r, 16);
		}
        printf("%s\n", buf);
	}
}