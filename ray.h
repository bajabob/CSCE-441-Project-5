
#ifndef RAY
#define RAY

#include <armadillo>
using arma::vec;
using arma::dot;

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

    double dot_point() const{
    	return dot(point, point);
    }

    double dot_slope() const{
    	return dot(slope, slope);
    }

    double dot_point_slope() const{
    	return dot(point, slope);
    }


private:
    vec point;
    vec slope;
};

#endif
