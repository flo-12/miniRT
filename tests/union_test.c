#include "../includes/miniRT.h"
#include "../includes/miniRT_define.h"

void render_sphere(t_object *obj)
{
    t_sphere sphere;

    sphere = (t_sphere) obj->u_obj.sphere;
    printf("the diameter of the sphere is %f\n", sphere.d);
}

void render_plane(t_object *obj)
{
    t_plane plane;

    plane = obj->u_obj.plane;
    printf("the x coordinate of the plane is %f\n", plane.point.x);
}

int main()
{
    t_object    *obj1;
    t_object    *obj2;

    obj1 = malloc(sizeof(t_object) * 1);
    obj2 = malloc(sizeof(t_object) * 1);

    obj1->identifier = SPHERE;  
    obj2->identifier = PLANE;
    obj1->u_obj.sphere.d = 3;
    obj2->u_obj.plane.point.x = 2;
    obj1->next = obj2;
    obj2->next = NULL;

    while (obj1)
    {
        if (obj1->identifier == SPHERE)
            render_sphere(obj1);
        if (obj1->identifier == PLANE)
            render_plane(obj2);
        obj1 = obj1->next;
    }
}
