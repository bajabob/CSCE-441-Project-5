
#include "scene.h"

fvec scene::BACKGROUND = fvec("0 0 0 1");

mat cross_product_matrix( const vec &in ) {
	// init cross-product
	mat cp( 3, 3 );

	// zero out the response
	cp.zeros( 3, 3 );

	// calculate
	cp( 0, 1 ) = -in( 2 );
	cp( 0, 2 ) = in( 1 );
	cp( 1, 0 ) = in( 2 );
	cp( 1, 2 ) = -in( 0 );
	cp( 2, 0 ) = -in( 1 );
	cp( 2, 1 ) = in( 0 );

	return cp;
}

mat rotation_matrix( const vec &a, double angle ) {
	vec na = a / norm( a, 2 );

	// create a new rotation matrix
	mat rm( 3, 3 );
	// zero out the response
	rm.zeros( 3, 3 );
	// calculate rotation matrix
	rm = (1 - cos( angle )) * na * na.t()
			+ sin( angle ) * cross_product_matrix( na )
			+ eye( 3, 3 ) * cos( angle );
	return rm;
}

scene::scene(const vec &camera):
		camera_width(3),
		camera_height(3),
		camera_center(3),
		camera_slope(3)
{
	camera_center = camera;

	float x = 0.9285;
	float y = 0;
	float z = -0.3714;
	float angle = 1.5;

	camera_slope(0) = x;
	camera_slope(1) = y;
	camera_slope(2) = z;

	vec camera_up(3);
	camera_up(0) = -z;
	camera_up(1) = y;
	camera_up(2) = x;

	vec y_cross(3);
	y_cross(0) = 0;
	y_cross(1) = -1;
	y_cross(2) = 0;

	camera_width = (rotation_matrix(camera_up, -angle/2.0) * camera_slope) -
			(rotation_matrix(camera_up, angle/2.0) * camera_slope);
	camera_height = (rotation_matrix(y_cross, -angle/2.0) * camera_slope) -
			(rotation_matrix(y_cross, angle/2.0) * camera_slope);
}

void scene::render( float (&framebuffer)[HEIGHT][WIDTH][3])
{
	for(int x = 0; x < WIDTH; x++)
    {
		for(int y = 0; y < HEIGHT; y++)
        {
			// calculate the camera ray vector
        	vec comp = ((-(y - HEIGHT/2.0) / HEIGHT * camera_height) +
        				(-(x - WIDTH/2.0) / WIDTH * camera_width)) +
        				camera_slope;

        	// create a new ray based off the camera position and current x/y
        	ray r(camera_center, (comp / norm(comp, 2)));

        	// get all colors of the discovered ray intersections
            fvec points = get_intersection_color(get_ray_intersections(r));

            // assign discovered intersection colors
            framebuffer[y][x][0] = points(0);
            framebuffer[y][x][1] = points(1);
            framebuffer[y][x][2] = points(2);

        }
    }
}


priority_queue<ray_intersection> scene::get_ray_intersections(const ray &r) const
{
    priority_queue<ray_intersection> pq;

    // go through the list of rendering objects
    for(int i = 0; i < surfaces.size(); ++i)
    {
    	ray_intersection intersection = surfaces.at(i)->cast_ray(r);

    	// only add as an intersection IF less than the MAX render distance
    	if(intersection.get_distance() < MAX_RENDER_DISTANCE && intersection.get_distance() > 0){
    		pq.push(intersection);
    	}
    }

    // no intersections?
    if(pq.empty())
    {
        return (priority_queue<ray_intersection>());
    }

    // provide list of intersections in order of ray-trace
    return (priority_queue<ray_intersection>(pq));
}

fvec scene::get_intersection_color(const priority_queue<ray_intersection> &pq) const
{

	// no intersection found, report back the default background color
	if(pq.size() == 0)
	{
		return BACKGROUND;
	}

	priority_queue<ray_intersection> rays(pq);

	int total_rays = rays.size();

	fvec surface_color;
	surface_color.zeros(4);

	// add up all the colors from the various intersections
	while(!rays.empty())
	{
		ray_intersection r = rays.top();
		surface_color += (get_surface_color(r));
		rays.pop();
	}

	// take average of all colors
	surface_color /= (double) total_rays;

    return surface_color;
}


fvec scene::get_surface_color(const ray_intersection &r) const
   {
       fvec surface_color(4);
       surface_color(0) = r.to_render->get_color()(0)*0.2;
       surface_color(1) = r.to_render->get_color()(1)*0.2;
       surface_color(2) = r.to_render->get_color()(2)*0.2;
       surface_color(3) = 1.0;

       for(int i = 0; i < lights.size(); i++)
       {

       	double distance = norm(lights.at(i)->get_position() - r.get_point(), 2);

       	fvec intensity(r.to_render->get_color());

       	if(distance < 15.0){
       		intensity = 225.0 * r.to_render->get_color() / pow(distance, 2);
       	}

       	vec direction(lights.at(i)->get_position() - r.get_point());
       	vec direction_light_source(direction / norm(direction, 2));
       	double distance_to_light = norm(lights.at(i)->get_position() - r.get_point(), 2);

       	ray ray_to_light(r.get_point() + r.get_normal() * 0.05, direction_light_source);
       	priority_queue<ray_intersection> shad_cast = get_ray_intersections(ray_to_light);

       	bool has_shadow = false;
       	if(!shad_cast.empty() && shad_cast.top().get_distance() < distance_to_light){
       		has_shadow = true;
       	}

       	double dot_ln = dot(direction_light_source, r.get_normal());

       	vec reflected = 2*dot_ln*r.get_normal() - direction_light_source;

			double dot_rv = dot(reflected, r.get_source_ray().get_slope());


			// If the light is in front of the surface, apply lighting
			if(dot_ln >= 0.0 && !has_shadow)
			{
				for(int channel = 0; channel < 3; channel++)
				{
					// Add in diffuse term
					surface_color(channel)
						+= r.to_render->get_color()(channel)*dot_ln*intensity(channel);

					// Add in specular term
					if(dot_rv >= 0.0)
					{
						surface_color(channel)
							+= r.to_render->get_specular()(channel)
							* pow(dot_rv, r.to_render->get_specular_exponent())
							* intensity(channel);
					}
				}
			}
       }

       return surface_color;

   }

void scene::add_surface(surface* s)
{
	this->surfaces.push_back(s);
}

void scene::add_light(light* l)
{
	this->lights.push_back(l);
}

vector<light*> scene::get_lights() const{
	return this->lights;
}
