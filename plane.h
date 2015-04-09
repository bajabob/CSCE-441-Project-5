
#ifndef INFINITE_PLANE
#define INFINITE_PLANE

#include <armadillo>
using arma::vec;

#include "renderable.h"

class plane : public renderable
{
public:
	plane(const vec &point, const vec& normal);

    virtual ray_intersection cast_ray(const ray &viewer) const;

private:
    vec point;
    vec normal;
};

#endif
