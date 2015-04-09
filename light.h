#ifndef LIGHT_H_
#define LIGHT_H_

#include <armadillo>
using arma::vec;
using arma::fvec;

class light{

public:
	light(const vec &position, const fvec &color)
	: position(position), color(color)
	{}

	vec get_position() const{
		return position;
	}

	fvec get_color() const{
		return color;
	}

private:

	vec position;
	fvec color;

};

#endif /* LIGHT_H_ */
