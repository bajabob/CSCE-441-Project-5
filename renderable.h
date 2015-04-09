
#ifndef RENDERABLE
#define RENDERABLE

#include <vector>
using std::vector;

#include <armadillo>
using arma::vec;
using arma::fvec;

class renderable;

#include "ray.h"
#include "ray_intersection.h"

class renderable
{
public:
    virtual ray_intersection cast_ray(const ray &viewer) const = 0;
};

#endif
