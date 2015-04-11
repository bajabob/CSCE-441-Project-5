#ifndef SPHERE_H_
#define SPHERE_H_

#include <cmath>
using std::pow;
using std::sqrt;

#include <armadillo>
using arma::vec;
using arma::dot;
using arma::norm;
using arma::fvec;
using arma::norm;

#include "surface.h"

class sphere : public surface {
public:

	sphere(const vec &position, const double &radius,
			const fvec &c, const fvec &s, const double &se,
			const double &d);

	virtual ray_intersection shoot_ray(const ray &viewer) const;

private:

	vec position;
	double radius;

};

#endif /* SPHERE_H_ */
