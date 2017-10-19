/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_section_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 20:06:40 by gtorresa          #+#    #+#             */
/*   Updated: 2017/10/19 01:59:30 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libnmotool.h>

static int	dump_section_name_64(t_file *bin, char *sect, char *seg)
{
	uint32_t	i;
	uint32_t	j;
	int			n;

	i = 0;
	n = 0;
	while (i < bin->mach64->ncmds)
	{
		if (bin->lc_t[i]->cmd == LC_SEGMENT_64)
		{
			j = 0;
			while (j < bin->seg64_c[i]->nsects)
			{
				if ((ft_strcmp((j + bin->sec64[i])->sectname, sect) == 0)
					&& (ft_strcmp((j + bin->sec64[i])->segname, seg) == 0))
				{
					return (n + 1);
				}
				j++;
				n++;
			}
		}
		i++;
	}
	return (0);
}

static int	dump_section_name_32(t_file *bin, char *sect, char *seg)
{
	uint32_t	i;
	uint32_t	j;
	int			n;

	i = 0;
	n = 0;
	while (i < bin->mach32->ncmds)
	{
		if (bin->lc_t[i]->cmd == LC_SEGMENT)
		{
			j = 0;
			while (j < bin->seg32_c[i]->nsects)
			{
				if ((ft_strcmp((j + bin->sec32[i])->sectname, sect) == 0)
					&& (ft_strcmp((j + bin->sec32[i])->segname, seg) == 0))
				{
					return (n + 1);
				}
				j++;
				n++;
			}
		}
		i++;
	}
	return (0);
}

static void init_section32(t_file *bin)
{
	uint32_t		i;
	void			*ptr;

	i = 0;
	ptr = ((void*)(bin->mach32 + 1) + sizeof(struct segment_command));
	while (i < bin->mach32->ncmds)
	{
		bin->sec32[i] = (ptr + sizeof(struct segment_command));
		ptr += bin->lc_t[i]->cmdsize;
		i++;
	}
}

static void init_section64(t_file *bin)
{
	uint32_t		i;
	void			*ptr;

	i = 0;
	ptr = ((void*)(bin->mach64 + 1) + sizeof(struct segment_command_64));
	while (i < bin->mach64->ncmds)
	{
		bin->sec64[i] = (ptr + sizeof(struct segment_command_64));
		ptr += bin->lc_t[i]->cmdsize;
		i++;
	}
}

void		dump_section_name(t_file *bin)
{
	t_tdb_nsect		tbd;

	bin->tdb = &tbd;
	if (bin->mach64)
	{
		init_section64(bin);
		bin->tdb->text_nsect = dump_section_name_64(bin, SECT_TEXT, SEG_TEXT);
		bin->tdb->data_nsect = dump_section_name_64(bin, SECT_DATA, SEG_DATA);
		bin->tdb->bss_nsect = dump_section_name_64(bin, SECT_BSS, SEG_DATA);
	}
	else if (bin->mach32)
	{
		init_section32(bin);
		bin->tdb->text_nsect = dump_section_name_32(bin, SECT_TEXT, SEG_TEXT);
		bin->tdb->data_nsect = dump_section_name_32(bin, SECT_DATA, SEG_DATA);
		bin->tdb->bss_nsect = dump_section_name_32(bin, SECT_BSS, SEG_DATA);
	}
}
