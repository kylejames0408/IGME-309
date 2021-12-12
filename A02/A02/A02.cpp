// Course: IGME 309-05
// Student Name: Kyle James
// Assignment Number: 02

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

// Inclusions
#include <math.h>
#include <iostream>

// Namespaces
using namespace std;

// the window's width and height
int width, height;

// global parameters defining the circle
const int MAX_VERT = 100; // maximum number of vertices
const int MIN_VERT = 3; // minimum number of vertices
int vertNum = 50; // the total number of vertices for the circle

void init(void)
{
	// initialize the size of the window
	width = 600;
	height = 600;
}

/// <summary>
/// Draws a solid-colored circle.
/// </summary>
/// <param name="red">Value of red</param>
/// <param name="green">Value of green</param>
/// <param name="blue">Value of blue</param>
/// <param name="center_x">Center x position of the circle</param>
/// <param name="center_y">Center y position of the circle</param>
/// <param name="radius">Circle's radius</param>
void drawFilledCircle(float red, float green, float blue, float center_x, float center_y, float radius)
{
	// Specify a color for the following object(s) that will be drawn 
	glColor3f(red, green, blue); // The color is RGB, each color channel is defined in [0, 1].

	// Draw a filled circle
	glBegin(GL_POLYGON);
	for (int i = 0; i < vertNum; i++) {
		float t = (float)i / vertNum * 2.0f * 3.14f;
		glVertex2f(center_x + radius * cos(t), center_y + radius * sin(t));
	}
	glEnd();
}

/// <summary>
/// Draws a wire frame circle.
/// </summary>
/// <param name="red">Value of red</param>
/// <param name="green">Value of green</param>
/// <param name="blue">Value of blue</param>
/// <param name="center_x">Center x position of the circle</param>
/// <param name="center_y">Center y position of the circle</param>
/// <param name="radius">Circle's radius</param>
void drawWireFrameCircle(float red, float green, float blue, float center_x, float center_y, float radius)
{
	// Specify a color for the following object(s) that will be drawn 
	glColor3f(red, green, blue); // The color is RGB, each color channel is defined in [0, 1].

	// Draw a wire frame circle
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertNum; i++) {
		float t = (float)i / vertNum * 2.0f * 3.14f;
		glVertex2f(center_x + radius * cos(t), center_y + radius * sin(t));
	}
	glEnd();
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

	// Draw panda
	//BODY
	drawFilledCircle(1, 1, 1, 0, 0, 2);
	drawWireFrameCircle(0, 0, 0, 0, 0, 2);
	//EARS
	drawFilledCircle(0, 0, 0, -0.75, 3.25, 0.4);
	drawFilledCircle(0.5, 0.5, 0.5, -0.75, 3.25, 0.2);
	drawFilledCircle(0, 0, 0, 0.75, 3.25, 0.4);
	drawFilledCircle(0.5, 0.5, 0.5, 0.75, 3.25, 0.2);
	//HEAD
	drawFilledCircle(1, 1, 1, 0, 2.25, 1.25);
	drawWireFrameCircle(0, 0, 0, 0, 2.25, 1.25);
	//EYES
	drawFilledCircle(0, 0, 0, -0.5, 2.45, 0.4);
	drawFilledCircle(0.627, 0.322, 0.176, -0.45, 2.45, 0.15);
	drawFilledCircle(0, 0, 0, -0.45, 2.45, 0.1);
	drawFilledCircle(1, 1, 1, -0.425, 2.425, 0.05);
	drawFilledCircle(0, 0, 0, 0.5, 2.45, 0.4);
	drawFilledCircle(0.627, 0.322, 0.176, 0.45, 2.45, 0.15);
	drawFilledCircle(0, 0, 0, 0.45, 2.45, 0.1);
	drawFilledCircle(1, 1, 1, 0.425, 2.425, 0.05);
	//NOSE
	drawFilledCircle(0, 0, 0, 0, 1.85, 0.2);
	//MOUTH
	drawWireFrameCircle(0, 0, 0, -0.2, 1.65, 0.2);
	drawWireFrameCircle(0, 0, 0, 0.2, 1.65, 0.2);
	//ARMS/LEGS
	for (int i = 0; i < 5; i++) {
		drawFilledCircle(0, 0, 0, -0.25 * i - 1.75, 0.15 * i + .45, 0.5);
		drawFilledCircle(0, 0, 0, -0.25 * i - 1, -0.15 * i - 1.5, 0.5);
		drawFilledCircle(0, 0, 0, 0.25 * i + 1.75, 0.15 * i + .45, 0.5);
		drawFilledCircle(0, 0, 0, 0.25 * i + 1, -0.15 * i - 1.5, 0.5);
	}
	//HAND/FOOT PADS
	drawFilledCircle(0.5, 0.5, 0.5, -2.85, 1.15, 0.3);
	drawFilledCircle(0.5, 0.5, 0.5, -2.1, -2.2, 0.3);
	drawFilledCircle(0.5, 0.5, 0.5, 2.85, 1.15, 0.3);
	drawFilledCircle(0.5, 0.5, 0.5, 2.1, -2.2, 0.3);
	//BAMBOO
	for (int i = 0; i < 10; i++) {
		drawFilledCircle(0, 0.5, 0, 3.25, 0.2 * i + 1, 0.25);
		drawWireFrameCircle(0, 0, 0, 3.25, 0.2 * i + 1, 0.25);
	}

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
	glutCreateWindow("A02 - Kyle James");

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