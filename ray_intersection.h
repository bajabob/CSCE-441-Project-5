#ifndef RAY_INTERSECTION_H_
#define RAY_INTERSECTION_H_

#include <armadillo>
using arma::vec;

#include "ray.h"
#include "renderable.h"

class ray_intersection{

public:

	ray_intersection(){}

	ray_intersection(const vec &normal,
					const ray &source_ray,
					const double &distance,
					const renderable *to_render):
	normal(normal),
	source_ray(source_ray),
	distance(distance),
	to_render(to_render)
	{
		this->point = source_ray.calculate(this->distance);
	}

	vec get_normal(){
		return this->normal;
	}

	vec get_point(){
		return this->point;
	}

	ray get_source_ray(){
		return this->source_ray;
	}

	double get_distance(){
		return this->distance;
	}

	renderable const* get_to_render(){
		return this->to_render;
	}

    bool operator<(const ray_intersection &ri) const
    {
        return distance < ri.distance;
    }

private:
	vec normal;
	vec point;
	ray source_ray;
    double distance;
    renderable const *to_render;
};

#endif /* RAY_INTERSECTION_H_ */
