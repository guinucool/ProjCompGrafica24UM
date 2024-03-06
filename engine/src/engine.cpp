#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../inc/drawables/primitive.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

int cameraVertical = 0;
int cameraHorizontal = 0;

void keyboardRegular(unsigned char key, int x, int y) {

    if (key == 'a')
        cameraHorizontal--;

    if (key == 'd')
        cameraHorizontal++;

    if (cameraVertical < 30 && key == 'w')
        cameraVertical++;
    
    if (cameraVertical > -30 && key == 's')
        cameraVertical--;

	glutPostRedisplay();
}

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void explorerCamera(double radius) {

    double angleH = (2 * M_PI) / 120;
    double angleV = (M_PI / 2) / 30;

    double px = radius * cos(cameraVertical * angleV) * sin((cameraHorizontal * angleV));
    double py = radius * sin(cameraVertical * angleV);
    double pz = radius * cos(cameraVertical * angleV) * cos((cameraHorizontal * angleV));

    // Define a camera
	gluLookAt(px, py, pz,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);
}

void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode( GL_FRONT, GL_LINE );
	
	// set camera
	glLoadIdentity();
    explorerCamera(10.0f);

	glPushMatrix();
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f, 100.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
	glPopMatrix();
		
	// put drawing instructions here
	glColor3f(1.0f, 1.0f, 1.0f);
    drawables::Primitive primitive("object.3d");
    primitive.draw();
	
	// End of frame
	glutSwapBuffers();
}

int main(int argc, char** argv) {

    // put GLUT�s init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI");
	
	// put callback registry here
	glutKeyboardFunc(keyboardRegular);
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	
	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// enter GLUT�s main cycle
	glutMainLoop();
	
	return 1;
}