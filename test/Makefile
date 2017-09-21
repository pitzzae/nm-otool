#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/18 12:10:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/09/18 12:10:23 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

NAME		= test
CC		= gcc
SRC             = ./src/test.c 
SRC1		= ./src/test_facile.c
SRC2		= ./src/test_moins_facile.c
DST             = ./dst/test_x
DST1            = ./dst/test_facile_x
DST2            = ./dst/test_moins_facile_x

all: ${NAME}

$(NAME):
	mkdir -p dst
	$(CC) -c $(SRC) -o $(DST)64.o
	$(CC) -m32 -c $(SRC) -o $(DST)86.o
	$(CC) $(SRC) -o $(DST)64
	$(CC) -m32 $(SRC) -o $(DST)86
	$(CC) -c $(SRC1) -o $(DST1)64.o
	$(CC) -m32 -c $(SRC1) -o $(DST1)86.o
	$(CC) $(SRC1) -o $(DST1)64
	$(CC) -m32 $(SRC1) -o $(DST1)86
	$(CC) -c $(SRC2) -o $(DST2)64.o
	$(CC) -m32 -c $(SRC2) -o $(DST2)86.o
	$(CC) $(SRC2) -o $(DST2)64
	$(CC) -m32 $(SRC2) -o $(DST2)86

fclean: clean
	rm -rf ./dst

clean:
	rm -rf $(DST)*.o

re: fclean all
