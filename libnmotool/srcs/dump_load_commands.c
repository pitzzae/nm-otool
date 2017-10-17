/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_load_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 21:28:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/17 21:28:06 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	send_result(t_file *bin, void (*result)(t_file *bin))
{
	result(bin);
}

void		dump_load_commands(t_file *bin)
{
	uint32_t		i;

	i = 0;
	bin->lc_t = malloc(bin->ncmds * sizeof(struct load_command));
	bin->seg32_t = malloc(bin->ncmds * sizeof(struct segment_command));
	bin->seg64_t = malloc(bin->ncmds * sizeof(struct segment_command_64));
	while (i < bin->ncmds)
	{
		bin->lc_t[i] = bin->lc;
		if (bin->dump->is_64)
			bin->seg64_t[i] = (struct segment_command_64*)bin->lc;
		else
			bin->seg32_t[i] = (struct segment_command*)bin->lc;
		bin->lc = ((void*)bin->lc) + bin->lc->cmdsize;
		i++;
	}
	send_result(bin ,bin->func);
	free(bin->lc_t);
	free(bin->seg32_t);
	free(bin->seg64_t);
}

