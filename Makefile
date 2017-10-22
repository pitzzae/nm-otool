#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 10:25:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/10/18 12:06:45 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

NM_NAME			= ft_nm
OTOOL_NAME		= ft_otool
CC				= gcc

LIBFT_DIR		= ./libft
LIBFT_NAME		= $(LIBFT_DIR)/libft.a

LIBNMOTOOL_DIR		= ./libnmotool
LIBFT_NAME		= $(LIBNMTOOL_DIR)/libnmotool.a

CFLAGS			= -Wall -Wextra -Werror

NM_DIR			= srcs_nm
OTOOL_DIR		= srcs_otool
NM_OBJS32		= objs_nm32
NM_OBJS64		= objs_nm64
OTOOL_OBJS32	= objs_otool32
OTOOL_OBJS64	= objs_otool64
INCL_DIR		= -I./includes -I$(LIBFT_DIR)/includes -I$(LIBNMOTOOL_DIR)/includes
LIB_DIR			= -L$(LIBFT_DIR) -lft -L$(LIBNMOTOOL_DIR) -lnmotool

NM_SRCS			= main.c ft_nm.c print_symbol_table.c order_lst.c \
				add_line_to_lst.c is_symtab.c

OTOOL_SRCS		= main.c ft_otool.c find_section_32.c find_section_64.c \
				print_sections.c

NM_OBJECTS32	= $(patsubst %.c, $(NM_OBJS32)/%.o, $(NM_SRCS))
NM_OBJECTS64	= $(patsubst %.c, $(NM_OBJS64)/%.o, $(NM_SRCS))
OTOOL_OBJECTS32	= $(patsubst %.c, $(OTOOL_OBJS32)/%.o, $(OTOOL_SRCS))
OTOOL_OBJECTS64	= $(patsubst %.c, $(OTOOL_OBJS64)/%.o, $(OTOOL_SRCS))

.PHONY: all

all: makelib ${NM_NAME} ${OTOOL_NAME}
	@echo "\nAll Done"

makelib: 
	@echo "Make libft"
	@make -j 8 -C $(LIBFT_DIR)
	@echo "Make libnmotool"
	@make -j 8 -C $(LIBNMOTOOL_DIR)

$(NM_NAME): $(NM_OBJECTS32) $(NM_OBJECTS64)
	@$(CC) $(NM_OBJECTS32) -o $@_i386 $(CFLAGS) -m32 $(INCL_DIR) $(LIB_DIR)
	@$(CC) $(NM_OBJECTS64) -o $@_x86_64 $(CFLAGS) -m64 $(INCL_DIR) $(LIB_DIR)
	@lipo -create -output $@ $@_i386 $@_x86_64

$(NM_OBJS32)/%.o: $(addprefix $(NM_DIR)/,%.c)
	@mkdir -p $(NM_OBJS32)
	@$(CC) $(CFLAGS) -m32 $(INCL_DIR) -o $@ -c $^
	@printf "."

$(NM_OBJS64)/%.o: $(addprefix $(NM_DIR)/,%.c)
	@mkdir -p $(NM_OBJS64)
	@$(CC) $(CFLAGS) -m64 $(INCL_DIR) -o $@ -c $^
	@printf "."

$(OTOOL_NAME): $(OTOOL_OBJECTS32) $(OTOOL_OBJECTS64)
	@$(CC) $(OTOOL_OBJECTS32) -o $@_i386 $(CFLAGS) -m32 $(INCL_DIR) $(LIB_DIR)
	@$(CC) $(OTOOL_OBJECTS64) -o $@_x86_64 $(CFLAGS) -m64 $(INCL_DIR) $(LIB_DIR)
	@lipo -create -output $@ $@_i386 $@_x86_64

$(OTOOL_OBJS32)/%.o: $(addprefix $(OTOOL_DIR)/,%.c)
	@mkdir -p $(OTOOL_OBJS32)
	@$(CC) $(CFLAGS) -m32 $(INCL_DIR) -o $@ -c $^
	@printf "."

$(OTOOL_OBJS64)/%.o: $(addprefix $(OTOOL_DIR)/,%.c)
	@mkdir -p $(OTOOL_OBJS64)
	@$(CC) $(CFLAGS) -m64 $(INCL_DIR) -o $@ -c $^
	@printf "."

fclean: clean
	@rm -f	$(NM_NAME) $(NM_NAME)_i386 $(NM_NAME)_x86_64 \
			$(OTOOL_NAME) $(OTOOL_NAME)_i386 $(OTOOL_NAME)_x86_64
	@echo "Delete $(NM_NAME) $(OTOOL_NAME)"
	@make -C $(LIBFT_DIR) fclean
	@make -C $(LIBNMOTOOL_DIR) fclean

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(LIBNMOTOOL_DIR) clean
	@rm -rf $(NM_OBJS32) $(NM_OBJS64) $(OTOOL_OBJS32) $(OTOOL_OBJS64)

re: fclean all
