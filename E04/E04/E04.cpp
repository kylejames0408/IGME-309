#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif


// the window's width and height
int width, height;

// global parameters for defining the light and shading effects
GLfloat light0_pos[] = { 0.0f, 5.0f, 5.0f, 0.0f };

void init(void)
{
	// initialize the size of the window
	width = 1024;
	height = 512;
}

// called when the GL context need to be rendered
void display(void)
{
	// clear the screen to white, which is the background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// clear the buffer stored for drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the specified lighting and shading properties to render the scene
	// this will bypass the default flat shading mode
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

#pragma region Grid Drawing
	int size = 24;              // number of cells in a row/col
	if (size % 2 != 0) ++size;     // calculate # of lines if grid size is even

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glBegin(GL_LINES);
	for (int i = 0; i < size + 1; i++) {
		if ((float)i == size / 2.0f) {
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		else {
			glColor3f(0.8f, 0.8f, 0.8f);
		}
		glVertex3f(-size / 2.0f, 0.0f, -size / 2.0f + i);
		glVertex3f(size / 2.0f, 0.0f, -size / 2.0f + i);
		glVertex3f(-size / 2.0f + i, 0.0f, -size / 2.0f);
		glVertex3f(-size / 2.0f + i, 0.0f, size / 2.0f);
	}
	glEnd();
	glPopMatrix();
#pragma endregion

	glutSwapBuffers(); // This example uses double framebuffers. This instructs the app that the current frame is finished and ready to display.
					   // The app then knows to swap it with the other buffer which was just displayed so that the display function can begin working on that buffer
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
	// update thescreen dimensions
	width = w;
	height = h;
	if (h == 0) {
		h = 1;
	}


	//do an orthographic parallel projection, limited by screen/window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 1 - Set gluPerspective() in the reshape callback function
	//	FOV: 45 | Aspect of Projection: 2.0 | Near Plane: 0.1 | Far Plane: 1000
	gluPerspective(45, 2.0, 0.1, 1000);

	// 1 - Set gluLookAt() in the reshape callback function
	//	Eye Pos: (20, 20, 20) | LookAt Pos: (0, 0, 0) | World Pos: (0, 1, 0)
	gluLookAt(20.0, 20.0, -20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	/* tell OpenGL to use the whole window for drawing */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

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
	glutCreateWindow("E04 - Kyle James");

	/* --- register callbacks with GLUT --- */

	//register function to handle window resizes
	glutReshapeFunc(reshape);

	//register function that draws in the window
	glutDisplayFunc(display);

	//start the glut main loop
	glutMainLoop();

	return 0;
}