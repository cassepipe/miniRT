#include "minirt.h"

t_env	env;

void prints(struct s_node*);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("You have not provided any arguments");
		return (0);
	}

	env.scene_path = argv[1];

	parse_file_into_env();

	struct s_node *cur = env.objects;
	while (cur)
	{
		prints(cur);
		cur = cur->next;
	}


	return (0);
}

void prints(struct s_node *node)
{
	if (!node)
		printf("The node points to NULL\n");
	else if (!(node->object))
		printf("No object to print in this node\n");
	else if (node->id == SQUARE)
	{
		t_square* square;
		square = node->object;

		printf("Square:\t\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", square->center.x, square->center.y, square->center.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", square->orientation.x, square->orientation.y, square->orientation.z);
		printf("Side lenght is %.1f\t", square->side_len);
		printf("RGB is (%.1f, %.1f, %.1f)\t", square->color.x, square->color.y, square->color.z);
		printf("\n");
	}
	else if (node->id == CYLINDER)
	{
		t_cylinder* cyl;
		cyl = node->object;

		printf("Cylinder:\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", cyl->center.x, cyl->center.y, cyl->center.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", cyl->orientation.x, cyl->orientation.y, cyl->orientation.z);
		printf("Diameter is %.1f\t", cyl->diameter);
		printf("Height is %.1f\t", cyl->height);
		printf("RGB is (%.1f, %.1f, %.1f)\t", cyl->color.x, cyl->color.y, cyl->color.z);
		printf("\n");
	}
	else if (node->id == PLANE)
	{
		t_plane* plane;
		plane = node->object;

		printf("Plane:\t\t");
		printf("Point is at (%.1f, %.1f, %.1f)\t", plane->some_point.x, plane->some_point.y, plane->some_point.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", plane->orientation.x, plane->orientation.y, plane->orientation.z);
		printf("RGB is (%.1f, %.1f, %.1f)\t", plane->color.x, plane->color.y, plane->color.z);
		printf("\n");
	}
}
