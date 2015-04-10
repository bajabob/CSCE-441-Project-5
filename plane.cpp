#include "plane.h"

plane::plane(const vec &point,
			const vec &normal,
			const fvec &c,
			const fvec &s,
			const double &se)
: 	surface(c, s, se),
    point(point),
	normal(normal / norm(normal, 2))
{}

ray_intersection plane::shoot_ray(const ray &r) const
{

	/**
	 * Planes go on forever, therefore there will
	 * 	always be an intersection. We will use the
	 * 	Config.MAX_RENDER_DISTANCE to trim plane's
	 * 	extending too far into the distance
	 */
	double distance = dot(normal, point - r.get_point())
                           / dot(normal, r.get_slope());
	ray_intersection ri(normal, r, distance, this);

    return ri;
}
