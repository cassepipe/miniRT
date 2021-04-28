# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2021/04/28 18:08:26 by tpouget          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

PHONY			=	all clean fclean re monsieur_propre

SOURCEFILES		=		args.c                \
						bitmap.c              \
						cleanup.c             \
						colors.c              \
						error.c               \
						images.c              \
						init.c                \
						intersect_cylinder.c  \
						intersection_triage.c \
						intersect_plane.c     \
						intersect_sphere.c    \
						intersect_triangle.c  \
						keypress.c            \
						lighting.c            \
						main.c                \
						matrices.c            \
						object_lighting.c     \
						parse.c               \
						parse_colors.c        \
						parse_light.c         \
						parse_objects.c       \
						parse_utils.c         \
						parse_values.c        \
						parse_vec.c           \
						pixel_to_rays.c       \
						render.c              \
						square.c              \
						trace.c               \
						vector_operations.c   \
						vector_products.c     \
						check_vec.c	  

OBJECTFILES		=	$(patsubst %.c,obj/%.o,$(SOURCEFILES))
	
HEADERS			=	bitmap.h \
					defines.h\
					minirt.h \
					parse.h  \
					structs.h\
	
CFLAGS			=	-Wall -Wextra -Werror -g3

CC	  		  	=	clang

SANITIZER		=	-fsanitize=address


#	Rules

all:			miniRT 

miniRT:			${OBJECTFILES} libft/libft.a mlx/mlx.a mlx/mlx_Linux.a
				${CC} ${SANITIZER} ${OBJECTFILES} -Llibft -lft -Lmlx -lmlx -lmlx_Linux -lXext -lX11 -lm -o $@

libft/libft.a:		
				make -C libft libft.a

mlx/mlx.a:
mlx/mlx_Linux.a:
				make -C mlx
				
obj/%.o:		%.c	Makefile ${HEADERS}| obj
				${CC} ${CFLAGS} -c $< -o $@

obj:			
				mkdir obj

clean:			
				rm -rf obj

fclean:			clean
				rm -rf miniRT

monsieur_propre:	fclean
					rm -f minimage*
					make -C mlx clean
					make -C libft fclean

re:				fclean all

.PHONY:			
				${PHONY}	
