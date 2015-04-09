
#include <armadillo>
using arma::norm;

#include "plane.h"

plane::plane(const vec &point, const vec &normal)
:
    point(point),
	normal(normal / norm(normal, 2))
{
}

ray_intersection plane::cast_ray(const ray &r) const
{
	double distance = dot(normal, point - r.get_point())
                           / dot(normal, r.get_slope());
	ray_intersection ri(normal, r, distance, this);

    return ri;
}
