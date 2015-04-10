#ifndef LIGHT_H_
#define LIGHT_H_

#include <armadillo>
using arma::vec;
using arma::fvec;

class light{

public:
	light(const vec &position, const fvec &color, const double &diffuse)
	: position(position), color(color), diffuse(diffuse)
	{}

	vec get_position() const{
		return position;
	}

	fvec get_color() const{
		return color;
	}

	double get_diffuse() const{
		return diffuse;
	}

private:

	vec position;
	fvec color;
	double diffuse;

};

#endif /* LIGHT_H_ */
