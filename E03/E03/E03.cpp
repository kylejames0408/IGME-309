#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <math.h>
#include <iostream>

using namespace std;


// the window's width and height
int width, height;

// global parameters defining the circle
const int MAX_VERT = 100; // maximum number of vertices
const int MIN_VERT = 3; // minimum number of vertices
int vertNum = 50; // the total number of vertices for the circle
float x = 0.0f, y = 0.0f; // center position of the circle
float r = 3.0f; // circle's radius

void init(void)
{
	// initialize the size of the window
	width = 600;
	height = 600;
}

// called when the GL context need to be rendered
void display(void)
{
	// clear the screen to white, which is the background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// clear the buffer stored for drawing
	glClear(GL_COLOR_BUFFER_BIT);

	// this is to define in which transformed space / coordinate system (in a matrix form) the objects will be drawn. 
	// (we'll learn matrix-based transformation in later classes.) 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Specify a color for the following object(s) that will be drawn 
	glColor3f(1.0, 0.0, 0.0); // The color is RGB, each color channel is defined in [0, 1].

	// draw a circle as the ball
	//glColor3f(1.0, 0.0, 0.0);
	//glBegin(GL_LINE_LOOP);
	//for (int i = 0; i < vertNum; ++i) {
	//	float t = (float)i / vertNum * 2.0f * 3.14f;
	//	glVertex2f(x + r * cos(t), y + r * sin(t));
	//}
	//glEnd();
	const float points[6][2] = { {0.5, 1.0}, {1.5, 1.0}, {2.0, 1.0}, {3.0, 3.0}, {3.0, 4.0}, {4.0, 1.0} };
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2fv(points[0]);
	glVertex2fv(points[1]);
	glVertex2fv(points[4]);
	glVertex2fv(points[3]);
	glVertex2fv(points[5]);
	glVertex2fv(points[2]);
	glEnd();

	glutSwapBuffers(); // This example uses double framebuffers. This instructs the app that the current frame is finished and ready to display.
					   // The app then knows to swap it with the other buffer which was just displayed so that the display function can begin working on that buffer
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
	// update thescreen dimensions
	width = w;
	height = h;

	//do an orthographic parallel projection, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // Define the size of the canvas left =-5, right =-5, bottom =-5, top=5,
									  // so the orgin is at the center of the canvas.  

	/* tell OpenGL to use the whole window for drawing */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}

	if (key == '+') {
		if (vertNum < MAX_VERT) {
			vertNum++;
		}

		cout << "# of vertices = " << vertNum << endl;
	}
	else if (key == '-') {
		if (vertNum > MIN_VERT) {
			vertNum--;
		}

		cout << "# of vertices = " << vertNum << endl;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	// before create a glut window,
	// initialize stuff not opengl/glut dependent
	init();

	//initialize GLUT, let it extract command-line GLUT options that you may provide
	//NOTE that the '&' before argc
	glutInit(&argc, argv);

	// specify as double bufferred can make the display faster
	// Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//set the initial window size */
	glutInitWindowSize((int)width, (int)height);

	// create the window with a title
	glutCreateWindow("E03 - Kyle James");

	/* --- register callbacks with GLUT --- */

	//register function to handle window resizes
	glutReshapeFunc(reshape);

	//register function that draws in the window
	glutDisplayFunc(display);

	glutKeyboardFunc(keyboard);

	//start the glut main loop
	glutMainLoop();

	return 0;
}