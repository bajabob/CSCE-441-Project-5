#include "scene.h"

fvec scene::BACKGROUND = fvec( "0 0 0 1" );

mat rotation_matrix( const vec &a, double angle ) {
	// init cross-product
	mat cp( 3, 3 );

	// zero out the response
	cp.zeros( 3, 3 );

	vec na(a);
	// create a new rotation matrix
	mat rm( 3, 3 );
	// zero out the response
	rm.zeros( 3, 3 );
	// calculate cp
	cp( 0, 1 ) = -a( 2 );
	cp( 1, 2 ) = -a( 0 );
	cp( 2, 0 ) = -a( 1 );
	cp( 0, 2 ) = a( 1 );
	cp( 1, 0 ) = a( 2 );
	cp( 2, 1 ) = a( 0 );
	// calculate rotation matrix
	rm = (	cos( angle ) * eye( 3, 3 )
			+ 1 - cos( angle )) * a * a.t()
			+ sin( angle ) * cp;
	return rm;
}

scene::scene( const vec &camera ) :
		camera_width( 3 ), camera_height( 3 ), camera_center( 3 ), camera_slope(
				3 ) {
	camera_center = camera;

	float x = 0.9285;
	float y = 0;
	float z = -0.3714;
	float angle = 1.5;

	camera_slope( 0 ) = x;
	camera_slope( 1 ) = y;
	camera_slope( 2 ) = z;

	vec camera_up( 3 );
	camera_up( 0 ) = -z;
	camera_up( 1 ) = y;
	camera_up( 2 ) = x;

	vec y_cross( 3 );
	y_cross( 0 ) = 0;
	y_cross( 1 ) = -1;
	y_cross( 2 ) = 0;

	camera_width = (rotation_matrix( camera_up, -angle / 2.0 ) * camera_slope)
			- (rotation_matrix( camera_up, angle / 2.0 ) * camera_slope);
	camera_height = (rotation_matrix( y_cross, -angle / 2.0 ) * camera_slope)
			- (rotation_matrix( y_cross, angle / 2.0 ) * camera_slope);
}

void scene::render( float (&framebuffer)[HEIGHT][WIDTH][3] ) {
	for ( int x = 0; x < WIDTH; x++ ) {
		for ( int y = 0; y < HEIGHT; y++ ) {
			// calculate the camera ray vector
			vec comp = ((-(y - HEIGHT / 2.0) / HEIGHT * camera_height)
					+ (-(x - WIDTH / 2.0) / WIDTH * camera_width))
					+ camera_slope;

			// create a new ray based off the camera position and current x/y
			ray r( camera_center, (comp / norm( comp, 2 )) );

			// get all colors of the discovered ray intersections
			fvec points = get_intersection_color( get_ray_intersections( r ) );

			// assign discovered intersection colors
			framebuffer[y][x][0] = points( 0 );
			framebuffer[y][x][1] = points( 1 );
			framebuffer[y][x][2] = points( 2 );

		}
	}
}

priority_queue<ray_intersection> scene::get_ray_intersections( const ray &r ) const {
	priority_queue<ray_intersection> pq;

	// go through the list of rendering objects
	for ( int i = 0; i < surfaces.size(); ++i ) {
		ray_intersection intersection = surfaces.at( i )->shoot_ray( r );

		// only add as an intersection IF less than the MAX render distance
		if (  intersection.get_distance() > 0 ) {
			pq.push( intersection );
		}
	}

	// no intersections?
	if ( pq.empty() ) {
		return (priority_queue<ray_intersection>());
	}

	// provide list of intersections in order of ray-trace
	return (priority_queue<ray_intersection>( pq ));
}

fvec scene::get_intersection_color(
		const priority_queue<ray_intersection> &pq ) const {

	// no intersection found, report back the default background color
	if ( pq.size() == 0 ) {
		return BACKGROUND;
	}

	priority_queue<ray_intersection> rays( pq );

	fvec surface_color;
	surface_color.zeros( 4 );

	// get the closest intersected object
	ray_intersection r = rays.top();
	surface_color += (get_surface_color( r, 1 ));

	return surface_color;
}

fvec scene::get_surface_color( const ray_intersection &r, int reflections ) const {
	fvec surface_color( 4 );
	surface_color( 0 ) = r.to_render->get_color()( 0 ) * 0.3;
	surface_color( 1 ) = r.to_render->get_color()( 1 ) * 0.3;
	surface_color( 2 ) = r.to_render->get_color()( 2 ) * 0.3;
	surface_color( 3 ) = 1.0;

	for ( int i = 0; i < lights.size(); i++ ) {

		// setup lighting calculations
		vec direction( lights.at( i )->get_position() - r.get_point() );
		vec direction_light_source( direction / norm( direction, 2 ) );
		double distance_to_light = norm(
				lights.at( i )->get_position() - r.get_point(), 2 );

		// Detect if casted ray is a shadow
		bool has_shadow = false;
		priority_queue<ray_intersection> shadow_rays = get_ray_intersections(
						ray( r.get_point() + r.get_normal(), direction_light_source ) );
		if ( !shadow_rays.empty() && distance_to_light > shadow_rays.top().get_distance() ) {
			has_shadow = true;
		}

		double dot_light_norm = dot( direction_light_source, r.get_normal() );

		if ( dot_light_norm > 0 ) {

			vec specular(2*dot(r.get_normal(), direction_light_source)
							* r.get_normal() - direction_light_source);

			// add up light values
			for ( int k = 0; k < 3; k++ ) {

				// ambient
				surface_color(k) += lights.at(i)->get_color()(k)
										* r.to_render->get_color()(k);

				if( !has_shadow )
				{
					// fill non-shadows
					surface_color(k) += 0.2 * r.to_render->get_color()(k);

					// specular
					surface_color(k) += r.to_render->get_specular()(k)
											* lights.at(i)->get_color()(k) *
											pow(max(dot(specular, direction), 0.0), 1.0);

					// diffuse
					surface_color(k) += lights.at(i)->get_diffuse()
											* r.to_render->get_diffuse()
											* max(dot(specular, r.get_normal()), 0.0);
				}
			}
		}
	}

	return surface_color;

}

void scene::add_surface( surface* s ) {
	this->surfaces.push_back( s );
}

void scene::add_light( light* l ) {
	this->lights.push_back( l );
}

vector<light*> scene::get_lights() const {
	return this->lights;
}
