/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_symtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 16:23:09 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/23 19:03:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

int			is_symtab(uint8_t n_type)
{
	if ((n_type & N_STAB))
		return (0);
	if ((n_type & N_SECT))
		return (1);
	else if ((n_type & N_SECT) && (n_type & N_PEXT))
		return (1);
	else if ((n_type & N_SECT) && (n_type & N_EXT))
		return (1);
	else if (n_type & N_EXT)
		return (1);
	else if ((n_type & N_STAB) && (n_type & N_PEXT))
		return (1);
	else if ((n_type & N_SECT) && (n_type & N_PEXT) && (n_type & N_EXT))
		return (1);
	else if ((n_type & N_UNDF) && (n_type & N_PEXT) && (n_type & N_EXT))
		return (1);
	return (0);
}
