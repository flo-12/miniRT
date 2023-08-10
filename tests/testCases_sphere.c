
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
1) two intersections with ray being orhogonal to a sphere
2) two intersections with ray intersecting a sphere (not orthogonal)
3) one intersection with ray (tangent)
4) one intersection with sphere - origin ray in sphere
5) no intersection (different v_norm)
6) no intersection with ray pointing in wrong direction
*/

bool	intersect_sphere(t_sphere sphere, t_vector ray, t_hit *hit);
t_coordinates	vector_normalize(t_coordinates v);

// 1) two intersections with ray being orhogonal to a sphere
void	twoInter_rayOrthogonal(t_sphere sphere, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 1 (Two intersections -> ray being orhogonal to a sphere) ----\n");
	printf("expected: P1(-1,0,0) & P2(1,0,0)\n");

	sphere.center->x = 0; sphere.center->y = 0; sphere.center->z = 0;
	sphere.d = 2;
	ray.origin.x = 10; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm = vector_normalize((t_coordinates){-1, 0, 0});
	if (intersect_sphere(sphere, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 2) two intersections with ray intersecting a sphere (not orthogonal)
void	twoInter_rayRandom(t_sphere sphere, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 2 (Two intersections -> ray intersecting a sphere random) ----\n");
	printf("expected: P1 & P2 different...\n");

	sphere.center->x = 1; sphere.center->y = 1; sphere.center->z = 1;
	sphere.d = 2;
	ray.origin.x = -1; ray.origin.y = -1; ray.origin.z = -1;
	ray.v_norm = vector_normalize((t_coordinates){1, 1, 1});
	if (intersect_sphere(sphere, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 3) one intersection with ray (tangent)
void	oneInter_tangent(t_sphere sphere, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 3 (One intersection with ray (tangent)) ----\n");
	printf("expected: P1(1.5,0,-0.5) & P2(1.5,0,-0.5)\n");

	sphere.center->x = 1.5; sphere.center->y = 0; sphere.center->z = 1;
	sphere.d = 3;
	ray.origin.x = 0; ray.origin.y = 0; ray.origin.z = -0.5;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 0});
	if (intersect_sphere(sphere, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 4) one intersection with sphere - origin ray in sphere
void	oneInter_rayInSphere(t_sphere sphere, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 4 (One intersection with sphere - origin ray in sphere) ----\n");
	printf("expected: P1(1,0,2.5) & P2(1,0,2.5)\n");

	sphere.center->x = 1; sphere.center->y = 0; sphere.center->z = 1;
	sphere.d = 3;
	ray.origin.x = 1; ray.origin.y = 0; ray.origin.z = 0.5;
	ray.v_norm = vector_normalize((t_coordinates){0, 0, 1});
	if (intersect_sphere(sphere, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 5) no intersection (different v_norm)
void	noInter_dirDiff(t_sphere sphere, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 5 (no intersection (different v_norm)) ----\n");
	printf("expected: no intersection...\n");

	sphere.center->x = 1; sphere.center->y = 0; sphere.center->z = 1;
	sphere.d = 2;
	ray.origin.x = -2; ray.origin.y = 0; ray.origin.z = 0.5;
	ray.v_norm = vector_normalize((t_coordinates){-1, 1, 1});
	if (intersect_sphere(sphere, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 6) no intersection with ray pointing in wrong direction
void	noInter_wrongDir(t_sphere sphere, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 6 (no intersection with ray wrong direction) ----\n");
	printf("expected: no intersection...\n");

	sphere.center->x = 0; sphere.center->y = 0; sphere.center->z = 1;
	sphere.d = 2;
	ray.origin.x = -0.5; ray.origin.y = 0; ray.origin.z = -0.5;
	ray.v_norm = vector_normalize((t_coordinates){0, 0, -1});
	if (intersect_sphere(sphere, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

void	tests_sphere()
{
	t_sphere	sphere; sphere.center = malloc(sizeof(t_coordinates));
	t_vector	ray;
	t_hit		hit;

	twoInter_rayOrthogonal(sphere, ray, hit);
	twoInter_rayRandom(sphere, ray, hit);

	oneInter_tangent(sphere, ray, hit);
	oneInter_rayInSphere(sphere, ray, hit);

	noInter_dirDiff(sphere, ray, hit);
	noInter_wrongDir(sphere, ray, hit);
}
