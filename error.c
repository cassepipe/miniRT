/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:50 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/28 17:07:02 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	die(const char *error_text)
{
	if (g_env.mlx_session && g_env.window)
		mlx_destroy_window(g_env.mlx_session, g_env.window);
	if (g_env.mlx_session)
		mlx_destroy_display(g_env.mlx_session);
	free_env(&g_env);
	ft_dprintf(STDERR_FILENO, "\033[31;1;4mError\033[0m\n%s\n", error_text);
	exit(EXIT_FAILURE);
}
