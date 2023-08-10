
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

bool	intersect_cylinder(t_cylinder cyl, t_vector ray, t_hit *hit);
t_coordinates	vector_normalize(t_coordinates v);

/*
THE FOLLOWING TESTS ARE EXECUTED IN THE FILE:
1) two intersections with tube - none with caps
2) two intersections with caps - none with tube
3) two intersections - one with tube and one with cap
4) one intersection with tube (tangent) and none with caps
5) one intersection with tube at the point, where cap ends (P1==P2)
6) one intersection with tube (none with caps) - origin ray in cylinder
7) one intersection with cap (none with tube) - origin ray in cylinder
8) no intersection (different v_norm)
9) no intersection (v_norm ray == v_norm tube)
10) no intersection (v_norm ray orthogonal v_norm tube)
11) infinite intersections -> ray lies on tube (origin out of range of tube)
12) infinite intersections -> ray lies on tube (origin on tube)
13) infinite intersections -> ray lies on cap (origin out of range of cap)
14) infinite intersections -> ray lies on cap (origin on cap)
*/

// 1) two intersections with tube - none with caps
void	twoInter_tube(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 1 (2 intersections with tube - none with cap) ----\n");
	printf("expected: P1(1,0,0) & P2(-1,0,0)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -2; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm.x = 1; ray.v_norm.y = 0; ray.v_norm.z = 0;
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 2) two intersections with caps - none with tube
void	twoInter_caps(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 2 (2 intersections with caps - none with tube) ----\n");
	printf("expected: P1(0,0,-1) & P2(0,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 0; ray.origin.y = 0; ray.origin.z = -2;
	ray.v_norm.x = 0; ray.v_norm.y = 0; ray.v_norm.z = 1;
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 3) two intersections - one with tube and one with cap
void	twoInter_tubeCap(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 3 (2 intersections - one with tube and one with cap) ----\n");
	printf("expected: P1(-1,0,0.5) & P2(-0.5,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -1.5; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 1});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 4) one intersection with tube (tangent) and none with caps
void	oneInter_tanTube(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 4 (1 intersection with tube and none with caps) ----\n");
	printf("expected: P1(0,1,0) & P2(0,1,0)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -2; ray.origin.y = 1; ray.origin.z = 0;
	ray.v_norm.x = 1; ray.v_norm.y = 0; ray.v_norm.z = 0;
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 5) one intersection with tube at the point, where cap ends (P1==P2)
void	oneInter_tubeCap(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 5 (1 intersection with tube at the point, where cap ends) ----\n");
	printf("expected: P1(-1,0,1) & P2(-1,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -1.5; ray.origin.y = 0; ray.origin.z = 0.5;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 1});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 6) one intersection with tube (none with caps) - origin ray in cylinder
void	oneInter_tube_in(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 6 (1 intersection with tube (none with caps) - origin ray in cylinder) ----\n");
	printf("expected: P1(1,0,0) & P2(1,0,0)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 0; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, });
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 7) one intersection with cap (none with tube) - origin ray in cylinder
void	oneInter_cap_in(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 7 (1 intersection with cap (none with tube) - origin ray in cylinder) ----\n");
	printf("expected: P1(0.5,0,1) & P2(0.5,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 0.5; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm = vector_normalize((t_coordinates){0, 0, 1});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 8) no intersection (different v_norm)
void	noInter_dirDifferent(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 8 (no intersection (different v_norm)) ----\n");
	printf("expected: no intersection...\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 15; ray.origin.y = 8; ray.origin.z = 2;
	ray.v_norm = vector_normalize((t_coordinates){1, 2, 3});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 9) no intersection (v_norm ray == v_norm tube)
void	noInter_dirEql(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 9 (no intersection (v_norm ray == v_norm tube)) ----\n");
	printf("expected: no intersection...\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -2; ray.origin.y = 0; ray.origin.z = -1;
	ray.v_norm = vector_normalize((t_coordinates){0, 0, 1});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 10) no intersection (v_norm ray orthogonal v_norm tube)
void	noInter_dirOrth(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 10 (no intersection (v_norm ray orthogonal v_norm tube)) ----\n");
	printf("expected: no intersection...\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -2; ray.origin.y = 0; ray.origin.z = -2;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 0});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 11) infinite intersections -> ray lies on tube (origin out of range of tube)
void	infInter_tubeEqlRay_out(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 11 (Infinite intersections -> ray lies on tube (origin out of range of tube)) ----\n");
	printf("expected: P1(-1,0,-1) & P2(-1,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -1; ray.origin.y = 0; ray.origin.z = -2;
	ray.v_norm = vector_normalize((t_coordinates){0, 0, 1});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 12) infinite intersections -> ray lies on tube (origin on tube)
void	infInter_tubeEqlRay_in(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 12 (Infinite intersections -> ray lies on tube (origin on tube)) ----\n");
	printf("expected: P1/P2(-1,0,1) OR P1/P2(-1,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -1; ray.origin.y = 0; ray.origin.z = 0;
	ray.v_norm = vector_normalize((t_coordinates){0, 0, 1});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 13) infinite intersections -> ray lies on cap (origin out of range of cap)
void	infInter_capEqlRay_out(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 13 (Infinite intersections -> ray lies on cap (origin out of range of cap)) ----\n");
	printf("expected: P1(1,0,1) & P2(-1,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = -2; ray.origin.y = 0; ray.origin.z = 1;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 0});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

// 14) infinite intersections -> ray lies on cap (origin on cap)
void	infInter_capEqlRay_in(t_cylinder cylinder, t_vector ray, t_hit hit)
{
	printf("\n---- TEST 14 (Infinite intersections -> ray lies on cap (origin on cap)) ----\n");
	printf("expected: P1/P2(0,0,1) OR P1/P2(1,0,1)\n");

	cylinder.center->x = 0; cylinder.center->y = 0; cylinder.center->z = -1;
	cylinder.d = 2;
	cylinder.h = 2;
	cylinder.v_norm->x = 0; cylinder.v_norm->y = 0; cylinder.v_norm->z = 1;
	ray.origin.x = 0; ray.origin.y = 0; ray.origin.z = 1;
	ray.v_norm = vector_normalize((t_coordinates){1, 0, 0});
	if (intersect_cylinder(cylinder, ray, &hit))
		printf("result: P1=(%f, %f, %f) & P2=(%f, %f, %f)\n", 
			hit.p1.x, hit.p1.y, hit.p1.z, hit.p2.x, hit.p2.y, hit.p2.z);
	else
		printf("result: no intersection...\n");
}

void	tests_cylinder()
{
	t_cylinder	cylinder; cylinder.center = malloc(sizeof(t_coordinates)); cylinder.v_norm = malloc(sizeof(t_coordinates));
	t_vector	ray;
	t_hit		hit;

	twoInter_tube(cylinder, ray, hit);
	twoInter_caps(cylinder, ray, hit);
	twoInter_tubeCap(cylinder, ray, hit);
	
	oneInter_tanTube(cylinder, ray, hit);
	oneInter_tubeCap(cylinder, ray, hit);
	oneInter_tube_in(cylinder, ray, hit);
	oneInter_cap_in(cylinder, ray, hit);

	noInter_dirDifferent(cylinder, ray, hit);
	noInter_dirEql(cylinder, ray, hit);
	noInter_dirOrth(cylinder, ray, hit);

	infInter_tubeEqlRay_out(cylinder, ray, hit);
	infInter_tubeEqlRay_in(cylinder, ray, hit);
	infInter_capEqlRay_out(cylinder, ray, hit);
	infInter_capEqlRay_in(cylinder, ray, hit);
}
