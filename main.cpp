
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

#include "config.h"
#include "ray.h"
#include "scene.h"
#include "plane.h"

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

	scene s(vec("-20 0 5"));

	// create a plane
	plane p(vec("0 0 0"), vec("0 0 1"));

	s.renderables.push_back(&p);

	s.render(framebuffer);

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
