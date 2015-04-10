#ifndef RAY_INTERSECTION_H_
#define RAY_INTERSECTION_H_

#include <armadillo>
using arma::vec;

#include "ray.h"
#include "surface.h"

class ray_intersection{

public:

	ray_intersection(){}

	ray_intersection(const vec &normal,
					const ray &source_ray,
					const double &distance,
					const surface *to_render):
	normal(normal),
	source_ray(source_ray),
	distance(distance),
	to_render(to_render)
	{
		this->point = source_ray.calculate(this->distance);
	}

	vec get_normal() const{
		return this->normal;
	}

	vec get_point() const{
		return this->point;
	}

	ray get_source_ray() const{
		return this->source_ray;
	}

	double get_distance() const{
		return this->distance;
	}

    bool operator<(const ray_intersection &ri) const
    {
        return distance > ri.distance;
    }

    /**
     * pointer to the object to render so we can calculate colors
     */
    surface const *to_render;

private:
	vec normal;
	vec point;
	ray source_ray;
    double distance;
};

#endif /* RAY_INTERSECTION_H_ */
