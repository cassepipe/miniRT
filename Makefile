# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2021/04/13 18:20:04 by tpouget          ###   ########.fr        #
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

miniRT:			${OBJECTFILES} ${HEADERS} libft/libft.a Makefile
				${CC} ${SANITIZER} ${OBJECTFILES} -Llibft -lft -lm -lmlx -lXext -lX11 -o $@

test:			${HEADERS} ${TEST_OBJECTS} libft/libft.a tests/tests.c
				${CC} ${TEST_OBJECTS} tests/tests.c -Llibft -lft -lm -lmlx -lXext - lX11 -lcriterion -o $@

libft/libft.a:		
				make -C libft libft.a
				
obj/%.o:		%.c	| obj
				${CC} ${CFLAGS} -c $< -o $@

obj:			
				mkdir obj

clean:			
				rm -rf obj/*.o

fclean:			clean
				rm -rf miniRT
				rm -rf test

re:				fclean all

.PHONY:			
				${PHONY}	
