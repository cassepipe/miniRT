#include "minirt.h"

void prints(struct s_object *object)
{
	if (!object)
		printf("The object points to NULL\n");
	else if (!(object->data))
		printf("No data to print in this object\n");
	else if (object->id == SQUARE)
	{
		t_square* square;
		square = object->data;

		printf("Square:\t\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", square->center.x, square->center.y, square->center.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", square->normal.x, square->normal.y, square->normal.z);
		printf("Side lenght is %.1f\t", square->side_len);
		printf("RGB is (%d, %d, %d)\t", square->color.red, square->color.green, square->color.blue);
		printf("\n");
	}
	else if (object->id == CYLINDER)
	{
		t_cylinder* cyl;
		cyl = object->data;

		printf("Cylinder:\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", cyl->base.x, cyl->base.y, cyl->base.z);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", cyl->dir.x, cyl->dir.y, cyl->dir.z);
		printf("Diameter is %.1f\t", cyl->diameter);
		printf("Height is %.1f\t", cyl->height);
		printf("RGB is (%d, %d, %d)\t", cyl->color.red, cyl->color.green, cyl->color.blue);
		printf("\n");
	}
	else if (object->id == PLANE)
	{
		t_plane* plane;
		plane = object->data;

		printf("Plane:\t\t");
		printf("Point is at (%.1f, %.1f, %.1f)\t", plane->some_point.x, plane->some_point.y, plane->some_point.x);
		printf("Orientation vector is (%.1f, %.1f, %.1f)\t", plane->normal.x, plane->normal.y, plane->normal.z);
		printf("RGB is (%d, %d, %d)\t", plane->color.red, plane->color.green, plane->color.blue);
		printf("\n");
	}
	else if (object->id == SPHERE)
	{
		t_sphere* sphere;
		sphere = object->data;

		printf("Sphere:\t\t");
		printf("Center is at (%.1f, %.1f, %.1f)\t", sphere->center.x, sphere->center.y, sphere->center.z);
		printf("Diameter is %.1f\t", sphere->diameter);
		printf("RGB is (%d, %d, %d)\t", sphere->color.red, sphere->color.green, sphere->color.blue);
		printf("\n");
	}
	else if (object->id == TRIANGLE)
	{
		t_triangle* triangle;
		triangle = object->data;

		printf("Triangle:\t\t\n");
		printf("Point 1 is at (%.1f, %.1f, %.1f)\t\n", triangle->p1.x, triangle->p1.y, triangle->p1.z);
		printf("Point 2 is at (%.1f, %.1f, %.1f)\t\n", triangle->p2.x, triangle->p2.y, triangle->p2.z);
		printf("Point 3 is at (%.1f, %.1f, %.1f)\t\n", triangle->p3.x, triangle->p3.y, triangle->p3.z);
		printf("RGB is (%d, %d, %d)\t", triangle->color.red, triangle->color.green, triangle->color.blue);
		printf("\n");
	}
}
