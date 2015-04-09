
#include <armadillo>
using arma::norm;

#include "plane.h"

plane::plane(const vec &point, const vec &normal)
:
    point(point),
	normal(normal / norm(normal, 2))
{
}

ray_intersection plane::cast_ray(const ray &viewer) const
{
	ray_intersection sol;

    sol.distance = dot(normal, point - viewer.get_point())
                   / dot(normal, viewer.get_slope());
    sol.source_ray = viewer;
    sol.to_render    = this;
    sol.normal       = normal;
    sol.point        = viewer.calculate(sol.distance);

    return sol;
}
