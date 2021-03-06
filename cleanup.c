/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:04:50 by tpouget           #+#    #+#             */
/*   Updated: 2021/04/24 14:34:28 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_camera_list(t_cam *camera)
{
	t_cam *next_object;

	while (camera != NULL)
	{
		next_object = camera->next;
		free(camera);
		camera = next_object;
	}
}

void	free_light_list(void)
{
	t_light *light;
	t_light *next_object;

	light = g_env.lights;
	while (light != NULL)
	{
		next_object = light->next;
		free(light);
		light = next_object;
	}
}

void	free_image_list(struct s_image *image)
{
	struct s_image *next_object;

	if (g_env.images)
	{
		while (g_env.number_of_cams--)
		{
			next_object = image->next;
			mlx_destroy_image(g_env.mlx_session, image->mlx_handle);
			image = next_object;
		}
		free(g_env.images);
	}
}

void	free_object_list(t_object *object)
{
	t_object *next_object;

	while (object != NULL)
	{
		next_object = object->next;
		free(object->data);
		free(object);
		object = next_object;
	}
}

void	free_env(t_env *env)
{
	free_object_list(env->objects);
	free_light_list();
	free_camera_list(env->cameras);
	free_image_list(env->images);
}
