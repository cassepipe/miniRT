/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:50 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 10:57:13 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	die(const char *error_text)
{
	if (env.mlx_session && env.window)
		mlx_destroy_window(env.mlx_session, env.window);
	free_env(&env);
	ft_dprintf(STDERR_FILENO, "\033[31;1;4mError\033[0m\n%s\n", error_text);
	exit(EXIT_FAILURE);
}
