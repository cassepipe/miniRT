/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_normalized.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:45:51 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/27 16:48:34 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_vec_norm(t_vec3 v)
{
	if (vec_len(v) != 1.0)
		die("Orientation vector must be normalized");
}
