/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:06:28 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 10:44:59 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"

char	*read_scene_file();

void	parse_ambl(char **input);
void	parse_res(char **input);
void	parse_cam(char **input);
void	parse_light(char **input);

void	parse_sp(char **input);
void	parse_pl(char **input);
void	parse_sq(char **input);
void	parse_cy(char **input);
void	parse_tr(char **input);

void	parse_file_into_env();
t_vec3	parse_vec(char **input);
t_color	parse_color(char **input);
double	parse_double(char **input);
double	parse_double_or_die(char **input);
int		parse_int(char **input);
int		parse_int_or_die(char **input);

void	skip_blank(char **input);
void	skip_blank_and_one_comma(char **input);
void	skip_set(char **input, const char *set);

#endif
