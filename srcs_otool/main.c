/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/18 15:53:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "nmotool.h"
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

static void	print_section_name(char *segname, char *sectname, int custom)
{
	if (custom)
		ft_putstr("Contents of ");
	ft_putchar('(');
	ft_putstr(segname);
	ft_putchar(',');
	ft_putstr(sectname);
	ft_putendl(") section");
}

void	print_byte_to_hex(char byte)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
}

void	print_ptr_to_hex(size_t ptr, boolean_t prefix, boolean_t len64)
{
	char	str[16];
	short	count;
	short	char_hex;

	count = -1;
	while (++count != 16)
	{
		char_hex = ptr % 16;
		ptr /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex % 10) + 'a';
	}
	count--;
	if (!len64)
		count -= 8;
	if (prefix)
		ft_putstr("0x");
	while (count >= 0)
		ft_putchar(str[count--]);
}

void		print_section(t_sect *section, char *seg, char *sect, int cust)
{
	size_t	offset;
	short	count;
	char	delim;

	offset = 0;
	print_section_name(seg, sect, cust);
	if (!ft_strcmp(seg, "__TEXT") && !ft_strcmp(sect, "__text"))
		delim = ' ';
	else
		delim = '\t';
	while (section->start + offset != section->end)
	{
		count = 0;
		print_ptr_to_hex(section->offset + offset, FALSE, section->len64);
		ft_putchar(delim);
		while (count++ != 16)
		{
			print_byte_to_hex(*(section->start + offset));
			offset++;
			ft_putchar(' ');
			if (section->start + offset == section->end)
				break ;
		}
		ft_putchar('\n');
	}
}


static void	print_filename_arch(char *filename, char *arch)
{
	ft_putstr(filename);
	if (arch)
		ft_putstr(arch);
	ft_putendl(":");
}


static void	*get_section_offset_64(char *sectname, void *ptr)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	size_t						count;

	count = 0;
	if (ptr)
	{
		seg = (struct segment_command_64 *)ptr;
		sec = (struct section_64 *)(seg + 1);
		while (count < seg->nsects)
		{
			if (ft_strcmp(sec->sectname, sectname) == 0)
				return (sec);
			sec += 1;
			count++;
		}
	}
	return (NULL);
}

static void	*get_segment_offset_64(t_head *headers, char *segname)
{
	struct segment_command_64	*seg;
	size_t						count;

	count = 0;
	seg = (struct segment_command_64 *)(headers->mach64 + 1);
	while (count < headers->mach64->ncmds)
	{
		if (ft_strcmp(seg->segname, segname) == 0)
			return (seg);
		seg = (struct segment_command_64 *)((char *)seg + seg->cmdsize);
		count++;
	}
	return (NULL);
}

void		find_section_64(t_head *head, char *seg_n, char *sect_n, int cust)
{
	struct segment_command_64	*seg_l;
	struct section_64			*sec_l;
	t_sect						section;

	if (head->mach64->filetype == MH_OBJECT)
		seg_l = (struct segment_command_64 *)(head->mach64 + 1);
	else
		seg_l = get_segment_offset_64(head, seg_n);
	sec_l = (struct section_64 *)get_section_offset_64(sect_n, seg_l);
	if (sec_l)
	{
		section.start = (char *)head->mach64 + sec_l->offset;
		section.end = section.start + sec_l->size;
		section.offset = sec_l->addr;
		section.len64 = TRUE;
		print_section(&section, seg_n, sect_n, cust);
	}
}

static void	print_sections(t_head *headers, char *filename)
{
	if (headers->mach64)
	{
		if (headers->mach64)
		{
			print_filename_arch(filename, " (architecture x86_64)");
			find_section_64(headers, SEG_TEXT, SECT_TEXT, 0);
			find_section_64(headers, SEG_DATA, SECT_DATA, 0);
		}
	}
}

void	read_bin(t_bin *bin, char *source)
{
	bin->fd = open(source, O_RDONLY);
	if (bin->fd > 2)
	{
		if (!fstat(bin->fd, &bin->st))
		{
			bin->ptr = mmap(0, bin->st.st_size, PROT_READ, MAP_PRIVATE, bin
					->fd, 0);
		}
		if (bin->st.st_mode & S_IFDIR)
		{
			ft_putstr(source);
			ft_putendl(" Is a directory.");
		}
	}
}

int 	main(int ac, char **av)
{
	t_bin       bin;

	if (ac < 2)
		return (0);
	else
	{

		read_bin(&bin, av[1]);
		get_binary_headers(bin.ptr, &bin.head);
		if (bin.head.mach64)
		{
			print_sections(&bin.head, av[1]);
		}
	}
	return (0);
}