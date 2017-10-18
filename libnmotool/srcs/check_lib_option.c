/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lib_option.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/18 15:31:27 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

int 		check_lib_option(t_file *bin)
{
	if ((bin->fat_opt & 0x01) == 1 && bin->dump->is_64)
		return (1);
	return (0);
}
