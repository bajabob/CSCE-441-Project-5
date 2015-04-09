#ifndef RAY_INTERSECTION_H_
#define RAY_INTERSECTION_H_

#include <armadillo>
using arma::vec;

#include "ray.h"
#include "renderable.h"

class ray_intersection{

public:

	ray_intersection(){}

	///bool operator<(const ray_intersection &ri) const;

	vec normal;
	vec point;
	ray source_ray;
    double distance;
    renderable const *to_render;

    bool operator<(const ray_intersection &ri) const
    {
        return distance < ri.distance;
    }
};

#endif /* RAY_INTERSECTION_H_ */
