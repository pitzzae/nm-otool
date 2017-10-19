#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/17 14:18:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/10/19 12:05:05 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

NAME = libnmotool.a
NAME32 = libnmotool_i386.a
NAME64 = libnmotool_x86_64.a

SRCS = dump_segments.c mmap_file.c dump_fat_header.c dump_mach_header.c \
		dump_load_commands.c dump_static_lib.c check_lib_option.c \
		dump_section_name.c ft_swap_fat.c check_magic_number.c

INCLUDES = -I./includes -I../libft/includes

CFLAGS = -Wall -Wextra -Werror

O_DIR32 = ./obj_32

O_DIR64 = ./obj_64

OBJS32 = $(addprefix $(O_DIR32)/,$(SRCS:.c=.o))

OBJS64 = $(addprefix $(O_DIR64)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(NAME32) $(NAME64)
	@echo "\nCreating $(NAME) fat library."
	@lipo -create -output $@ $^

$(NAME32): $(OBJS32)
	@ar rc $@ $^
	@echo "\nCreating $(NAME32) i386 archive library."
	@ranlib $@
	@echo "Indexing i386 archive library."

$(NAME64): $(OBJS64)
	@ar rc $@ $^
	@echo "\nCreating $(NAME64) x86_64 archive library."
	@ranlib $@
	@echo "Indexing x86_64 archive library."

$(O_DIR64)/%.o: ./srcs/%.c
	@mkdir -p $(O_DIR64)
	@printf "."
	@gcc $(CFLAGS) -m64 -c $< $(INCLUDES) -o $@


$(O_DIR32)/%.o: ./srcs/%.c
	@mkdir -p $(O_DIR32)
	@printf "."
	@gcc $(CFLAGS) -m32 -c $< $(INCLUDES) -o $@

clean:
	@rm -rf $(O_DIR32)
	@rm -rf $(O_DIR64)
	@echo "Delete obj."

fclean: clean
	@rm -rf $(NAME) $(NAME32) $(NAME64)
	@echo "Delete $(NAME) $(NAME32) $(NAME64)."

re: fclean
	@make all
	@echo "Make library."

PHONY: all clean fclean re
