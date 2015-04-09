
#ifndef RAY
#define RAY

#include <armadillo>
using arma::vec;

class ray
{
public:

    ray(){}

    ray(const vec &point, const vec &slope):point(point), slope(slope){}

    vec calculate(const double &a) const{
    	return (a*slope) + point;
    }

    vec get_point() const{
    	return point;
    }

    vec get_slope() const{
    	return slope;
    }

private:
    vec point;
    vec slope;
};

#endif
