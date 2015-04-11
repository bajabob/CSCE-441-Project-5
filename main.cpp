
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using std::cout;
using std::endl;

#include <armadillo>
using arma::vec;

#include "ray.h"
#include "scene.h"
#include "plane.h"
#include "sphere.h"
#include "config.h"

int window;

float framebuffer[HEIGHT][WIDTH][3];

void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels( WIDTH, HEIGHT, GL_RGB, GL_FLOAT, framebuffer );
    glFlush();
}

// Clears framebuffer to black
void onClearFramebuffer() {
	// init frame buffer to black
	for ( int i = 0; i < HEIGHT; i++ ) {
		for ( int j = 0; j < WIDTH; j++ ) {
			framebuffer[i][j][0] = 0.0;
			framebuffer[i][j][1] = 0.0;
			framebuffer[i][j][2] = 0.0;
		}
	}
}

void onRenderSceneOne()
{
	onClearFramebuffer();

	cout << "Rendering Scene 1... " << endl;

	scene scene(vec("-18 0 3"));

	// plane
	plane plane(	vec("0 0 -5"),
					vec("0 0 1"),
					fvec("0.3 0.3 0.3"),
					fvec("0.01 0.01 0.01"),
					1.0, 0.0);
	scene.add_surface(&plane);


	// lights
	light light_forward(vec("-10 0 18"),
						fvec("0.0 0.0 0.5"),
						0.2);
	scene.add_light(&light_forward);

	light light_back_left(	vec("18 -6 18"),
							fvec("0.5 0.0 0.0"),
							0.0);
	scene.add_light(&light_back_left);

	light light_back_right(	vec("18 6 18"),
							fvec("0.0 0.5 0.0"),
							0.0);
	scene.add_light(&light_back_right);

	// spheres
	sphere sphere_center(	vec("6 0 1"),
							1.0,
							fvec("0.0 0.8 0.0"),
							fvec("0.0 0.0 0.0"),
							0.0, 1.0);
	scene.add_surface(&sphere_center);

	sphere sphere_center_bottom(vec("-6 0 0"),
								1.0,
								fvec("1.0 0.0 0.0"),
								fvec("0.2 0.2 0.2"),
								1.0, 1.0);
	scene.add_surface(&sphere_center_bottom);

	sphere sphere_left(		vec("0 -7 0"),
							2.0,
							fvec("0.0 0.0 1.0"),
							fvec("0.0 0.0 0.0"),
							0.0, 0.5);
	scene.add_surface(&sphere_left);

	sphere sphere_right(	vec("0 7 0"),
							2.0,
							fvec("0.0 0.0 1.0"),
							fvec("0.0 0.0 0.0"),
							0.0, 0.5);
	scene.add_surface(&sphere_right);

	scene.render(framebuffer);

    glutPostRedisplay();
}

void onRenderSceneTwo()
{
	onClearFramebuffer();

	cout << "Rendering Scene 2... " << endl;

	scene scene(vec("-18 0 3"));

	// plane
	plane plane(	vec("0 0 -5"),
					vec("0 0 1"),
					fvec("1.0 0.0 0.0"),
					fvec("0.02 0.02 0.02"),
					0.2, 0.2);
	scene.add_surface(&plane);


	// lights
	light light1(	vec("40 0 18"),
					fvec("0.01 0.01 0.01"),
					1.0);
	scene.add_light(&light1);

	light light2(	vec("40 -16 18"),
					fvec("0.01 0.01 0.01"),
					1.0);
	scene.add_light(&light2);

	light light3(	vec("40 16 18"),
					fvec("0.01 0.01 0.01"),
					1.0);
	scene.add_light(&light3);

	// spheres
	sphere sphere_center(	vec("0 0 0"),
							4.0,
							fvec("0.0 0.8 0.0"),
							fvec("0.0 0.01 0.0"),
							1.0, 1.0);
	scene.add_surface(&sphere_center);


	scene.render(framebuffer);

    glutPostRedisplay();
}

void onRenderSceneThree()
{
	onClearFramebuffer();

	cout << "Rendering Scene 3... " << endl;

	scene scene(vec("-18 0 3"));

	// plane
	plane plane(	vec("0 0 -5"),
					vec("0 0 1"),
					fvec("0.0 0.0 0.8"),
					fvec("0.01 0.01 0.01"),
					1.0, 0.0);
	scene.add_surface(&plane);


	// lights
	light light1(	vec("40 0 18"),
					fvec("0.1 0.0 0.0"),
					0.3);
	scene.add_light(&light1);


	// spheres
	sphere sphere_center(	vec("0 0 0"),
							4.0,
							fvec("0.8 0.0 0.0"),
							fvec("0.0 0.0 0.0"),
							0.0, 1.0);
	scene.add_surface(&sphere_center);


	scene.render(framebuffer);

    glutPostRedisplay();
}

void onRenderSceneFour()
{
	onClearFramebuffer();

	cout << "Rendering Scene 4... " << endl;

	scene scene(vec("-18 0 3"));

	// plane
	plane plane(	vec("0 0 -5"),
					vec("0 0 1"),
					fvec("0.3 0.3 0.3"),
					fvec("0.01 0.01 0.01"),
					1.0, 0.0);
	scene.add_surface(&plane);


	// lights
	light light_forward(vec("-10 0 18"),
						fvec("0.0 0.0 0.5"),
						0.2);
	scene.add_light(&light_forward);

	light light_back_left(	vec("18 -6 18"),
							fvec("0.5 0.0 0.0"),
							0.0);
	scene.add_light(&light_back_left);

	light light_back_right(	vec("18 6 18"),
							fvec("0.0 0.5 0.0"),
							0.0);
	scene.add_light(&light_back_right);



	// spheres
	sphere s1(	vec("0 -6 0"),
				1.0,
				fvec("0.0 0.0 0.2"),
				fvec("0.0 0.0 0.02"),
				0.0, 0.0);
	scene.add_surface(&s1);

	sphere s2(	vec("0 -3 0"),
				1.0,
				fvec("0.2 0.0 0.0"),
				fvec("0.02 0.0 0.0"),
				0.0, 0.0);
	scene.add_surface(&s2);

	sphere s3(	vec("0 0 0"),
				1.0,
				fvec("0.0 0.2 0.0"),
				fvec("0.0 0.01 0.0"),
				0.0, 0.0);
	scene.add_surface(&s3);

	sphere s4(	vec("0 3 0"),
				1.0,
				fvec("0.2 0.0 0.0"),
				fvec("0.02 0.0 0.0"),
				0.0, 0.0);
	scene.add_surface(&s4);

	sphere s5(	vec("0 6 0"),
				1.0,
				fvec("0.0 0.0 0.2"),
				fvec("0.0 0.0 0.02"),
				0.0, 0.0);
	scene.add_surface(&s5);

	sphere s6(	vec("-6 6 0"),
				1.0,
				fvec("0.8 0.0 0.0"),
				fvec("0.02 0.0 0.0"),
				1.0, 0.0);
	scene.add_surface(&s6);

	sphere s7(	vec("-6 -6 0"),
				1.0,
				fvec("0.8 0.0 0.0"),
				fvec("0.02 0.0 0.0"),
				1.0, 0.0);
	scene.add_surface(&s7);


	scene.render(framebuffer);

    glutPostRedisplay();
}


void onKeyPress( unsigned char key, int x, int y ) {
	switch ((char) key) {
	case 'q':
	case 27: // esc key
		cout << "Exiting..." << endl;
		glutDestroyWindow( window );
		exit( 0 );
		break;
	case '1':
		onClearFramebuffer();
		onRenderSceneOne();
		glutPostRedisplay();
		break;
	case '2':
		onClearFramebuffer();
		onRenderSceneTwo();
		glutPostRedisplay();
		break;
	case '3':
		onClearFramebuffer();
		onRenderSceneThree();
		glutPostRedisplay();
		break;
	case '4':
		onClearFramebuffer();
		onRenderSceneFour();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);

    window = glutCreateWindow("Robert Timm - Homework 5");

    glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutKeyboardFunc( onKeyPress );
    glutDisplayFunc( onDisplay );

    cout << "Controls:" << endl;
    cout << "\t 'q' to quit" << endl;
    cout << "\t '1' to render plane & 4 objects" << endl;
    cout << "\t '2' to render specular example" << endl;
    cout << "\t '3' to render diffuse example" << endl;
    cout << "\t '4' to render 8 objects" << endl;

    onRenderSceneOne();

    glutMainLoop();
    return 0;
}
