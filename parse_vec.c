/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 10:53:09 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/26 10:53:19 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	parse_vec(char **input)
{
	t_vec3 vector;

	vector.x = parse_double(input);
	vector.y = parse_double(input);
	vector.z = parse_double(input);
	return (vector);
}
