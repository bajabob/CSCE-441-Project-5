#include "sphere.h"

sphere::sphere(	const vec &position,
				const double &radius,
				const fvec &c,
				const fvec &s,
				const double &se)
:	surface(c, s, se),
	position(position),
	radius(radius)
{}


ray_intersection sphere::cast_ray(const ray &r) const
{
    double a = r.dot_slope();
    double b = 2.0*(r.dot_point_slope() - dot(position, r.get_slope()));
    double c = r.dot_point() - 2*dot(position, r.get_point()) +
    			dot(position, position) - pow(radius, 2);
    double d = pow(b,2) - (4*a*c);

    double distance = (pow(d, 0.5) -b) / (2.0 * a);

    vec pos(r.calculate(distance));

    vec n((2*pos - 2*position) / norm(vec(2*pos - 2*position), 2));

	ray_intersection ri(n, r, distance, this);

    return ri;
}
