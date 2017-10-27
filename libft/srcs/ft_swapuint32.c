/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapuint32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 17:38:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 15:17:34 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t		ft_swapuint32(uint32_t u)
{
	return (((((uint32_t)(u) & 0xff000000) >> 24) |
			(((uint32_t)(u) & 0x00ff0000) >> 8) |
			(((uint32_t)(u) & 0x0000ff00) << 8) |
			(((uint32_t)(u) & 0x000000ff) << 24)));
}
