
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

	// lights
	light light(	vec("5 3 20"),
					fvec("1 1 1"));
	scene.add_light(&light);

	// plane
	plane plane(	vec("0 0 -5"),
					vec("0 0 1"),
					fvec("0.7 0.3 0.1"),
					fvec("0.2 0.7 0.1"),
					12.0, 0.0, 0.0, 3.0);
	scene.add_surface(&plane);

	// spheres
	sphere sphere(	vec("0 0 0"),
					1.0,
					fvec("0.1 0.8 0.1"),
					fvec("0.2 0.7 0.1"),
					12.0, 0.0, 0.0, 3.0);

	scene.add_surface(&sphere);

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
    cout << "\t '1' to render scene 1" << endl;

    onRenderSceneOne();

    glutMainLoop();
    return 0;
}
