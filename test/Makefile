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

NAME			= test
CC				= gcc
SRC             = ./src/test.c
DST             = ./dst/test_x

all: ${NAME}

$(NAME):
	mkdir -p dst
	$(CC) -c $(SRC) -o $(DST)64.o
	$(CC) -m32 -c $(SRC) -o $(DST)86.o
	$(CC) $(SRC) -o $(DST)64
	$(CC) -m32 $(SRC) -o $(DST)86

fclean: clean
	rm -rf ./dst

clean:
	rm -rf $(DST)*.o

re: fclean all
