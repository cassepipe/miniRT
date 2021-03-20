#include "minirt.h"

extern t_env env;

void free_env(t_env *env);
void free_object_list(t_object *objects);
void free_light_list(t_light *lights);
void free_camera_list(t_cam *cameras);

void free_camera_list(t_cam *camera)
{
	t_cam *next_object;

	while (camera != NULL)
	{
		next_object = camera->next;
		free(camera);
		camera = next_object;
	}
}

void free_light_list(t_light *light)
{
	t_light *next_object;

	while (light != NULL)
	{
		next_object = light->next;
		free(light);
		light = next_object;
	}
}

void free_object_list(t_object *object)
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

void free_env(t_env *env)
{
	free_object_list(env->objects);
	free_light_list(env->lights);
	free_camera_list(env->cameras);
}


void die(const char* error_text)
{
	free_env(&env);
	fprintf(stderr, error_text);
	exit(EXIT_FAILURE);
}