
#ifndef SCENE
#define SCENE

#include <armadillo>
using arma::fvec;
using arma::mat;
using arma::eye;

#include <queue>
using std::priority_queue;
#include <map>
using std::map;
#include <set>
using std::set;
#include <vector>
using std::vector;

class scene;

#include "config.h"
#include "renderable.h"
#include "ray_intersection.h"

class scene
{
public:

	/**
	 * Set any non-rendered pixels to a standard color
	 */
	static fvec BACKGROUND;

	scene(const vec &camera);

    void render( float (&framebuffer)[HEIGHT][WIDTH][3]);

    priority_queue<ray_intersection> get_ray_intersections(const ray &r) const;
    fvec get_intersection_color(const priority_queue<ray_intersection> &pq, int depth) const;

    vector<renderable*> renderables;

private:

    vec camera_width;
    vec camera_height;
    vec camera_center;
    vec camera_slope;

};

#endif
