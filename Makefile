# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2021/03/08 18:08:49 by tpouget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

PHONY			=	all clean fclean re libft

SOURCEFILES		=	$(wildcard *.c)	

TEST_SOURCES	=	$(filter-out ${PHONY} test, $(MAKECMDGOALS))

OBJECTFILES		=	$(patsubst %.c,obj/%.o,$(SOURCEFILES))

TEST_OBJECTS	=	$(patsubst %.c,obj/%.o,$(TEST_SOURCES))
	
HEADERS			=	$(wildcard *.h)
	
CFLAGS			=	-Wall -Wextra -g3

CC	  		  	= 	 clang

SANITIZER		=	 -fsanitize=address


#	Rules

all:			miniRT

miniRT:			${OBJECTFILES} ${HEADERS} libft Makefile
				${CC} ${SANITIZER} ${OBJECTFILES} -Llibft -lft -lm -lmlx -lXext -lX11 -o $@

test:			${HEADERS} ${TEST_OBJECTS} libft tests/tests.c
				${CC} ${TEST_OBJECTS} tests/tests.c -Llibft -lft -lm -lmlx -lXext - lX11 -lcriterion -o $@

libft:		
				make -C libft libft.a
				
obj/%.o:		%.c	
				${CC} ${CFLAGS} -c $< -o $@

clean:			
				rm -rf obj/*.o

fclean:			clean
				rm -rf miniRT
				rm -rf test

re:				fclean $(filter-out re, $(MAKECMDGOALS))

.PHONY:			
				${PHONY}	
