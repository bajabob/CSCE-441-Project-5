
#ifndef PLANE_H_
#define PLANE_H_

#include <armadillo>
using arma::vec;
using arma::norm;

#include "surface.h"

class plane : public surface
{
public:
	plane(const vec &point, const vec& normal,
			const fvec &c, const fvec &s, const double &se,
			const double &d);

    virtual ray_intersection shoot_ray(const ray &viewer) const;

private:
    vec point;
    vec normal;
};

#endif
