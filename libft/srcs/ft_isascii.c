/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:11:43 by gtorresa          #+#    #+#             */
/*   Updated: 2015/11/27 10:55:08 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isascii(int c1)
{
	if (c1 >= 0 && c1 <= 127)
		return (1);
	return (0);
}