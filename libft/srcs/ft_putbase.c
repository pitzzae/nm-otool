/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:01:43 by gtorresa          #+#    #+#             */
/*   Updated: 2017/09/18 15:01:45 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putbase(unsigned long n, char *buf, int base)
{
	char		c;

	if (n / base > 0)
	{
		ft_putbase((n / base), buf, base);
		n = n % base;
	}
	c = (char) (n < 10 ? '0' : 'a' - 10);
	c = (char) (c + n);
	ft_strcat(buf, &c);
}
