/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:45:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 21:26:45 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_vec_range(t_vec3 v)
{
	if (v.x < -1 || v.x > 1
		|| v.y < -1 || v.y > 1
		|| v.z < -1 || v.z > 1)
		die("Orientation vector must be normalized");
}
