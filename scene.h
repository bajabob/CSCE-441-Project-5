
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

using std::max;

class scene;

#include "light.h"
#include "config.h"
#include "surface.h"
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

    fvec get_intersection_color(const priority_queue<ray_intersection> &pq) const;

    fvec get_surface_color(const ray_intersection &r) const;

    void add_surface(surface* s);

    void add_light(light* l);
    vector<light*> get_lights() const;


private:

    vector<surface*> surfaces;
    vector<light*> lights;

    vec camera_width;
    vec camera_height;
    vec camera_center;
    vec camera_slope;

};

#endif
