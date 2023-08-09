
#include "../includes/miniRT_define.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

void	tests_cylinder();
void	tests_sphere();
//void	tests_plane();

int	main()
{
	t_sphere	sphere;
	t_plane		plane; plane.point = malloc(sizeof(t_coordinates)); plane.v_norm = malloc(sizeof(t_coordinates));
	t_vector	ray;
	t_hit		hit;

	printf("\n**** SPHERE ****\n");
	tests_sphere();

	/* printf("\n**** PLANE (intersection) ****\n");
	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	plane.v_norm->x = 0; plane.v_norm->y = 1; plane.v_norm->z = 0;
	ray.origin.x = 1; ray.origin.y = 2; ray.origin.z = 3;
	ray.v_norm.x = 0.5; ray.v_norm.y = 0.5; ray.v_norm.z = -0.5;
	if (intersect_plane(plane, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n");

	printf("\n**** PLANE (overlapping) ****\n");
	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	plane.v_norm->x = 0; plane.v_norm->y = 1; plane.v_norm->z = 0;
	ray.origin.x = 0.5; ray.origin.y = 0; ray.origin.z = 0.5;
	ray.v_norm.x = 0.5; ray.v_norm.y = 0; ray.v_norm.z = 0.5;
	if (intersect_plane(plane, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n");

	printf("\n**** PLANE (parallel) ****\n");
	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	plane.v_norm->x = 0; plane.v_norm->y = 1; plane.v_norm->z = 0;
	ray.origin.x = 1; ray.origin.y = 2; ray.origin.z = 3;
	ray.v_norm.x = 0.5; ray.v_norm.y = 0; ray.v_norm.z = 0.5;
	if (intersect_plane(plane, ray, &hit))
		printf("Intersection Points P1=(%f, %f, %f) and P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("No intersection...\n"); */

	printf("\n**** CYLINDER (intersection) ****\n");
	tests_cylinder();

	printf("\n");
	return (0);
}
