/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:45:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/28 12:33:30 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_vec_range(t_vec3 v)
{
	if (v.x < -1 || v.x > 1
		|| v.y < -1 || v.y > 1
		|| v.z < -1 || v.z > 1)
		die("Orientation vector must have its coordinates in the range [-1,1]");
}
