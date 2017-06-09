#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 10:25:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/06/09 10:48:14 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

NM_NAME			= ft_nm
OTOOL_NAME		= ft_otool
CC				= gcc

LIB_DIR			= ./libft
LIB_NAME		= $(LIB_DIR)/libft.a

CFLAGS			= -Wall -Wextra -Werror

NM_DIR			= srcs_nm
OTOOL_DIR		= srcs_otool
NM_OBJS			= objs_nm
OTOOL_OBJS		= objs_otool
INCL_DIR		= includes

NM_SRCS			= main.c
OTOOL_SRCS		= main.c

NM_OBJECTS		= $(patsubst %.c, $(NM_OBJS)/%.o, $(NM_SRCS))
OTOOL_OBJECTS	= $(patsubst %.c, $(OTOOL_OBJS)/%.o, $(OTOOL_SRCS))

.PHONY: all

all: ${NM_NAME} ${OTOOL_NAME}

$(NM_NAME): $(NM_OBJECTS)
	@make -j 8 -C $(LIB_DIR)
	@$(CC) $(CFLAGS) -o $@ $(NM_OBJECTS) -I $(INCL_DIR)/ -L$(LIB_DIR) -lft

$(NM_OBJS)/%.o: $(addprefix $(NM_DIR)/,%.c)
	@mkdir -p $(NM_OBJS)
	$(CC) -c -o $@ $(CFLAGS) $^ -I $(INCL_DIR)/ -L$(LIB_DIR) -lft

$(OTOOL_NAME): $(OTOOL_OBJECTS)
	@make -j 8 -C $(LIB_DIR)
	@$(CC) $(CFLAGS) -o $@ $(OTOOL_OBJECTS) -I $(INCL_DIR)/ -L$(LIB_DIR) -lft

$(OTOOL_OBJS)/%.o: $(addprefix $(OTOOL_DIR)/,%.c)
	@mkdir -p $(OTOOL_OBJS)
	$(CC) -c -o $@ $(CFLAGS) $^ -I $(INCL_DIR)/ -L$(LIB_DIR) -lft

fclean: clean
	@rm -f $(NM_NAME) $(OTOOL_NAME)
	@echo "Delete $(NM_NAME) $(OTOOL_NAME)"

clean:
	@make -C $(LIB_DIR) fclean
	@rm -f $(LIB_NAME)
	@rm -rf $(NM_OBJS) $(OTOOL_OBJS)

re: fclean all
