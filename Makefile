# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2020/12/01 12:42:11 by tpouget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

PHONY			=	all clean fclean re 

SOURCEFILES		=	$(wildcard *.c)	

TEST_SOURCES	=	$(filter-out ${PHONY} test, $(MAKECMDGOALS))

OBJECTFILES		=	$(patsubst %.c,obj/%.o,$(SOURCEFILES))

TEST_OBJECTS	=	$(patsubst %.c,obj/%.o,$(TEST_SOURCES))
	
HEADERS			=	$(wildcard *.h)
	
CFLAGS			=	-Wall -Wextra 

CC	  		  	= 	 gcc

DEBUG			=	 -g3


#	Rules

all:			miniRT

miniRT:			${OBJECTFILES} ${HEADERS} libft/lift.a
				${CC} ${OBJECTFILES} -Llibft -lft -o $@

test:			${HEADERS} ${TEST_OBJECTS} libft/libft.a tests/tests.c
				${CC} ${TEST_OBJECTS} tests/tests.c -Llibft -lft -lcriterion -o $@

libft/libft.a:		
				make -C libft
				
obj/%.o:		%.c	
				${CC} -g3 ${CFLAGS} -c $< -o $@

clean:			
				rm -rf obj/*.o

fclean:			clean
				rm -rf miniRT
				rm -rf test

re:				fclean ${RE_ARGV}

.PHONY:			${PHONY}	
