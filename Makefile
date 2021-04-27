# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2021/04/27 12:07:38 by tpouget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

PHONY			=	all clean fclean re

SOURCEFILES		=	$(wildcard *.c)	

OBJECTFILES		=	$(patsubst %.c,obj/%.o,$(SOURCEFILES))
	
HEADERS			=	$(wildcard *.h)
	
CFLAGS			=	-Wall -Wextra -g3

CC	  		  	=	clang

SANITIZER		=	-fsanitize=address


#	Rules

all:			miniRT 

miniRT:			${OBJECTFILES} libft/libft.a 
				${CC} ${SANITIZER} ${OBJECTFILES} -Llibft -lft -lm -lmlx -lXext -lX11 -o $@

libft/libft.a:		
				make -C libft libft.a
				
obj/%.o:		%.c	Makefile ${HEADERS}| obj
				${CC} ${CFLAGS} -c $< -o $@

obj:			
				mkdir obj

clean:			
				rm -rf obj/*.o

fclean:			clean
				rm -rf miniRT

re:				fclean all

.PHONY:			
				${PHONY}	
