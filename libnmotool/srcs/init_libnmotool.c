/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_libnmotool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:38:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/27 15:40:40 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

void		init_libnmotool(t_file *bin)
{
	bin->pos = 0;
	bin->is_print = 0;
	bin->tdb = NULL;
	bin->nfat_arch = 0;
	bin->mach32 = NULL;
	bin->mach64 = NULL;
	bin->lc = NULL;
	bin->lc_t = NULL;
	bin->seg32_c = NULL;
	bin->seg64_c = NULL;
	bin->sec32 = NULL;
	bin->sec64 = NULL;
	bin->sym = NULL;
	bin->head = NULL;
	bin->arch = NULL;
	bin->fat_l = NULL;
	bin->nlist32 = NULL;
	bin->nlist64 = NULL;
	bin->dump = NULL;
	bin->ncmds = 0;
	bin->mmap = NULL;
	bin->option_parser = NULL;
	bin->error_order = 0;
}
