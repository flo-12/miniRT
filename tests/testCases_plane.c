
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

/*
THE FOLLOWING TESTS ARE EXECUTED IN THE FILE:
1) one intersection - orthogonal
2) one intersection - neither orthogonal nor parallel
3) no intersection - parallel & ray not on sphere
4) infinite intersections - parallel & ray on sphere
*/

bool	intersect_plane(t_plane plane, t_vector ray, t_hit *hit);
t_coordinates	vector_normalize(t_coordinates v);

// 1) one intersection - orthogonal
void	oneInter_orthogonal(t_plane plane, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 1 (One intersections -> orthogonal) ----\n");
	printf("expected: P1(1,0,3) & P2(1,0,3)\n");

	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	*plane.v_norm = vector_normalize((t_coordinates){0, 1, 0});
	ray.origin.x = 1; ray.origin.y = 2; ray.origin.z = 3;
	ray.v_norm = vector_normalize((t_coordinates){0, -1, 0});
	if (intersect_plane(plane, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 2) one intersection - neither orthogonal nor parallel
void	oneInter_diffDir(t_plane plane, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 2 (One intersections -> neither orthogonal nor parallel) ----\n");
	printf("expected: P1(-2,0,0) & P2(-2,0,0)\n");

	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	*plane.v_norm = vector_normalize((t_coordinates){0, 1, 0});
	ray.origin.x = -1; ray.origin.y = 1; ray.origin.z = -1;
	ray.v_norm = vector_normalize((t_coordinates){-1, -1, 1});
	if (intersect_plane(plane, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 3) no intersection - parallel & ray not on sphere
void	noInter_parallel_out(t_plane plane, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 3 (No intersections -> parallel & ray not on sphere) ----\n");
	printf("expected: no intersection...\n");

	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	*plane.v_norm = vector_normalize((t_coordinates){0, 1, 0});
	ray.origin.x = -1; ray.origin.y = 1; ray.origin.z = -1;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 1});
	if (intersect_plane(plane, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 4) infinite intersections - parallel & ray on sphere
void	noInter_parallel_in(t_plane plane, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 4 (Infinite intersections -> parallel & ray on sphere) ----\n");
	printf("expected: P1(-1,0,-1) & P2(-1,0,-1)\n");

	plane.point->x = 0; plane.point->y = 0; plane.point->z = 0;
	*plane.v_norm = vector_normalize((t_coordinates){0, 1, 0});
	ray.origin.x = -1; ray.origin.y = 0; ray.origin.z = -1;
	ray.v_norm = vector_normalize((t_coordinates){0.5, 0, 1});
	if (intersect_plane(plane, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

void	tests_plane()
{
	t_plane		plane; plane.point = malloc(sizeof(t_coordinates)); plane.v_norm = malloc(sizeof(t_coordinates));
	t_vector	ray;
	t_hit		hit;

	oneInter_orthogonal(plane, ray, hit);
	oneInter_diffDir(plane, ray, hit);
	noInter_parallel_out(plane, ray, hit);
	noInter_parallel_in(plane, ray, hit);
}
