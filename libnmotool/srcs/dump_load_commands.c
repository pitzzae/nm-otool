/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_load_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 21:28:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/11/03 14:58:45 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static void	send_result(t_file *bin, void (*result)(t_file *))
{
	result(bin);
}

static void	init_load_command(t_file *bin)
{
	bin->lc_t = malloc(bin->ncmds * sizeof(struct load_command));
	bin->seg32_c = malloc(bin->ncmds * sizeof(struct segment_command));
	bin->seg64_c = malloc(bin->ncmds * sizeof(struct segment_command_64));
	bin->sec32 = malloc(bin->ncmds * sizeof(struct section));
	bin->sec64 = malloc(bin->ncmds * sizeof(struct section_64));
}

static void	free_load_command(t_file *bin)
{
	free(bin->lc_t);
	free(bin->seg32_c);
	free(bin->seg64_c);
	free(bin->sec32);
	free(bin->sec64);
}

static void	check_next_lc(t_file *bin)
{
	int				i;
	void			(*ft_nm_print_error)(t_file *, char *);

	ft_nm_print_error = bin->print_error;
	i = (int)((void*)bin->lc) + bin->lc->cmdsize;
	if (i > 0)
		bin->lc = ((void*)bin->lc) + bin->lc->cmdsize;
	else
	{
		bin->lc = NULL;
		ft_nm_print_error(bin, MSG_NM_TRUNC);
	}
}

void		dump_load_commands(t_file *bin)
{
	t_tdb_nsect		tbd;
	uint32_t		i;

	i = 0;
	bin->tdb = &tbd;
	init_load_command(bin);
	while (i < bin->ncmds && bin->lc)
	{
		bin->lc_t[i] = bin->lc;
		if (bin->dump->is_64)
			bin->seg64_c[i] = (struct segment_command_64*)bin->lc;
		else
			bin->seg32_c[i] = (struct segment_command*)bin->lc;
		check_next_lc(bin);
		i++;
	}
	dump_section_name(bin);
	send_result(bin, bin->func);
	free_load_command(bin);
}
