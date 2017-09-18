cmake_minimum_required(VERSION 3.7)
project(ft_otool)


include_directories(includes)
set(HEADER_FILES includes/libft.h includes/nmotool.h)

set(SOURCE_LIBFT libft/srcs/ft_atoi.c libft/srcs/ft_bzero.c
        libft/srcs/ft_isalnum.c libft/srcs/ft_isalpha.c
        libft/srcs/ft_isascii.c libft/srcs/ft_isdigit.c
        libft/srcs/ft_isprint.c libft/srcs/ft_memalloc.c
        libft/srcs/ft_memccpy.c libft/srcs/ft_memchr.c libft/srcs/ft_memcmp.c
        libft/srcs/ft_memcpy.c libft/srcs/ft_memmove.c libft/srcs/ft_memset.c
        libft/srcs/ft_strcat.c libft/srcs/ft_strchr.c libft/srcs/ft_strcmp.c
        libft/srcs/ft_strcpy.c libft/srcs/ft_strdup.c libft/srcs/ft_strlcat.c
        libft/srcs/ft_strlen.c libft/srcs/ft_strncat.c libft/srcs/ft_strncmp.c
        libft/srcs/ft_strncpy.c libft/srcs/ft_strnstr.c libft/srcs/ft_strrchr.c
        libft/srcs/ft_strstr.c libft/srcs/ft_tolower.c libft/srcs/ft_toupper.c
        libft/srcs/ft_memdel.c libft/srcs/ft_strnew.c libft/srcs/ft_strdel.c
        libft/srcs/ft_strclr.c libft/srcs/ft_striter.c libft/srcs/ft_striteri.c
        libft/srcs/ft_strmap.c libft/srcs/ft_strmapi.c libft/srcs/ft_strequ.c
        libft/srcs/ft_strnequ.c libft/srcs/ft_strsub.c libft/srcs/ft_strjoin.c
        libft/srcs/ft_strtrim.c libft/srcs/ft_strsplit.c libft/srcs/ft_itoa.c
        libft/srcs/ft_putchar.c libft/srcs/ft_putstr.c libft/srcs/ft_putendl.c
        libft/srcs/ft_putnbr.c libft/srcs/ft_putchar_fd.c
        libft/srcs/ft_putstr_fd.c libft/srcs/ft_putendl_fd.c
        libft/srcs/ft_putnbr_fd.c libft/srcs/ft_lstnew.c
        libft/srcs/ft_lstdelone.c libft/srcs/ft_lstdel.c libft/srcs/ft_lstadd.c
        libft/srcs/ft_lstaddend.c libft/srcs/ft_lstiter.c libft/srcs/ft_lstmap.c
        libft/srcs/ft_lstsplit.c libft/srcs/ft_lstprintstr.c
        libft/srcs/ft_lstprintnbr.c libft/srcs/ft_str_replace_chr.c
        libft/srcs/ft_lstlen.c libft/srcs/ft_lstring.c libft/srcs/ft_lstdup.c
        libft/srcs/ft_strfocur.c libft/srcs/get_next_line.c
        libft/srcs/ft_strjoin_free.c libft/srcs/ft_realloc.c
        libft/srcs/ft_tab_realloc.c libft/srcs/ft_strocur.c
        libft/srcs/ft_strlocur.c libft/srcs/ft_strcat_l.c libft/srcs/ft_bufcpy.c
        libft/srcs/ft_strisprint.c libft/srcs/ft_strswap.c
        libft/srcs/ft_date_time.c libft/srcs/ft_lst_env_new.c
        libft/srcs/ft_lst_to_env.c libft/srcs/ft_lst_get_env.c
        libft/srcs/ft_lst_edit_env.c libft/srcs/ft_lst_add_env.c
        libft/srcs/ft_lst_rm_env.c libft/srcs/ft_strsplit_len.c
        libft/srcs/ft_str_replace_str.c libft/srcs/ft_strsub_free.c
        libft/srcs/ft_myputchar.c libft/srcs/ft_lstaddend_free.c
        libft/srcs/ft_udel.c libft/srcs/ft_strocur_slash.c
        libft/srcs/ft_stradd_slash.c libft/srcs/ft_tabdup.c
        libft/srcs/ft_putbase.c libft/srcs/ft_puthex.c)
add_library(ft ${SOURCE_LIBFT} ${HEADER_FILES})


set(SOURCE_OTOOL_FILES srcs_otool/main.c srcs_otool/get_type_file.c
        srcs_otool/parse_argv.c srcs_otool/print_sections.c
        srcs_otool/find_section_64.c srcs_otool/find_section_86.c)
set(SOURCE_NM_FILES srcs_nm/main.c srcs_nm/get_type_file.c
        srcs_nm/parse_argv.c srcs_nm/print_symbol_table.c
        )

add_executable(ft_otool ${SOURCE_OTOOL_FILES} ${SOURCE_LIBFT} ${HEADER_FILES})
add_executable(ft_nm ${SOURCE_NM_FILES} ${SOURCE_LIBFT} ${HEADER_FILES})