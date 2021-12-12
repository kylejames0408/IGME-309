#pragma region Inclusions
// GLEW inclusions
#include <GL/glew.h>

// GLUT inclusions
#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

// GL math library inclusions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>

// Built-in inclusions
#include <vector>

// Custom classes
#include "Bullet.h"
#pragma endregion

#pragma region Namespaces
using namespace std; // standard namespace
using namespace glm; // GL math library namespace
#pragma endregion

#pragma region Fields
// OpenGL Window Fields
int width, height;

// Game Object Fields
vec2 floorA, floorB; // floor vertices
vec3 floorC; // floor color
vec2 body; // cannon vertex
vec3 cannonC; // cannon color
float bodyR, bodyV, launcherR, launcherV, launcherL; // cannon radius, velocity, launch rotation, velocity, length
vec2 target; // target position
vec3 targetC; // target color
float targetR; // target radius
vector<Bullet> bullets; // array of bullets
vec3 bulletC; // bullet color

// Time Fields
unsigned int curTime, preTime; // current time, last frame time
#pragma endregion

#pragma region Helper Functions
/// <summary>
/// Sets a random position for the target.
/// </summary>
void generateRandomVertex()
{
	target = vec2(0.5f - (float)rand() / RAND_MAX * 3.5f, (float)rand() / RAND_MAX * 4.0f);
}

/// <summary>
/// Initialize variables.
/// </summary>
/// <param name="">Nothing.</param>
void init(void)
{
	// initialize window size
	width = 600;
	height = 600;

	// initialize floor bar
	floorA = vec2(-2.0f, -3.0f);
	floorB = vec2(2.0f, -3.0f);
	floorC = vec3(0.0f, 0.0f, 1.0f);

	// initialize cannon
	body = vec2(0.0f, -3.0f);
	bodyR = 0.4f;
	bodyV = 0.0f;
	launcherR = 1.57f;
	launcherV = 0.0f;
	launcherL = 1.0f;
	cannonC = vec3(0.5f, 0.5f, 0.0f);

	// initialize target
	generateRandomVertex(); // sets random position
	targetR = 0.2f;
	targetC = vec3(0.2f, 0.0f, 0.0f);

	// initialize bullet
	bulletC = vec3(1.0f, 0.0f, 0.0f);

	// initialize time
	curTime = 0; preTime = 0;
}
#pragma endregion

#pragma region GLUT Callbacks
/// <summary>
/// Draws the scene.
/// </summary>
/// <param name="">Nothing.</param>
void display(void)
{
	// clear the screen to white
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// clear the buffer stored for drawing
	glClear(GL_COLOR_BUFFER_BIT);

	// define coordinate system that objects will be drawn
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// DRAW HERE
	// draw floor bar
	glLineWidth(3);
	glColor3f(floorC.x, floorC.y, floorC.z);
	glBegin(GL_LINES);
	glVertex2f(-2.0f, -3.0f);
	glVertex2f(2.0f, -3.0f);
	glEnd();

	// draw cannon circle
	glLineWidth(1);
	glColor3f(cannonC.x, cannonC.y, cannonC.z);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++) {
		float t = (float)i / 100 * 2.0f * 3.14f;
		glVertex2f(body.x + bodyR * cos(t), body.y + bodyR * sin(t));
	}
	glEnd();

	// draw cannon launcher
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(body.x, body.y);
	glVertex2f(body.x - launcherL * cos(launcherR), body.y + launcherL * sin(launcherR));
	glEnd();

	// draw target
	glLineWidth(1);
	glColor3f(targetC.x, targetC.y, targetC.z);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(target.x, target.y);
	for (int i = 0; i < 200; i++) {
		glVertex2f(target.x + std::sin(i) * targetR, target.y + std::cos(i) * targetR);
	}
	glEnd();

	// draw bullets
	glColor3f(bulletC.x, bulletC.y, bulletC.z);
	for (int i = 0; i < bullets.size(); i++) {
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < 100; j++) {
			float t = (float)j / 100 * 2.0f * 3.14f;
			glVertex2f(bullets[i].position.x + 0.1f * cos(t), bullets[i].position.y + 0.1f * sin(t));
		}
		glEnd();
	}

	// swap double buffers
	glutSwapBuffers();
}

/// <summary>
/// Reshapes the screen on window resize.
/// </summary>
/// <param name="w">Width of the new window size.</param>
/// <param name="h">Height of the new window size.</param>
void reshape(int w, int h)
{
	// update screen dimensions
	width = w;
	height = h;

	// orthographic parallel projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // size of canvas, origin is centered

	// use whole window for drawing
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// redisplay
	glutPostRedisplay();
}

/// <summary>
/// Gets keyboard input to interact with the scene.
/// </summary>
/// <param name="key">The key pressed.</param>
/// <param name="x"></param>
/// <param name="y"></param>
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		bodyV = -5.0f;
		break;
	case 'd':
		bodyV = 5.0f;
		break;
	case 'k':
		launcherV = -1.57f;
		break;
	case 'l':
		launcherV = 1.57f;
		break;
	case ' ':
		bullets.push_back(Bullet(vec2(body.x - launcherL * cos(launcherR), body.y + launcherL * sin(launcherR)), launcherR));
		break;
	}
}

/// <summary>
/// Gets keyboard key release to interact with the scene.
/// </summary>
/// <param name="key">The key released.</param>
/// <param name="x"></param>
/// <param name="y"></param>
void keyup(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
	case 'd':
		bodyV = 0.0f;
		break;
	case 'k':
	case 'l':
		launcherV = 0.0f;
		break;
	}
}

/// <summary>
/// Updates the scene every frame.
/// </summary>
void update()
{
	// get current time
	curTime = glutGet(GLUT_ELAPSED_TIME);

	// get change since last frame
	float deltaTime = (float)(curTime - preTime) / 1000.0f;

	// update player position
	body.x += bodyV * deltaTime;
	if (body.x >= 2.0f) {
		body.x = 2.0f;
	}
	else if (body.x <= -2.0f) {
		body.x = -2.0f;
	}

	// update cannon position
	launcherR += launcherV * deltaTime;
	if (launcherR >= 3.14f) {
		launcherR = 3.14f;
	}
	else if (launcherR <= 0.0f) {
		launcherR = 0.0f;
	}

	// update bullets
	for (int i = 0; i < bullets.size(); i++) {
		// move the bullets
		bullets[i].position.y += 3.0f * deltaTime * sin(bullets[i].rotation);
		bullets[i].position.x += 3.0f * deltaTime * -cos(bullets[i].rotation);

		// check collision with target (AABB)
		if (bullets[i].position.x - bullets[i].radius < target.x + targetR &&
			bullets[i].position.x + bullets[i].radius > target.x - targetR &&
			bullets[i].position.y - bullets[i].radius < target.y + targetR &&
			bullets[i].position.y + bullets[i].radius > target.y - targetR)
		{
			// increase target size
			targetR += 0.01f;
			targetC.x += 0.02f;

			// if hit 30 times, reset
			if (targetR >= 0.5f) {
				targetR = 0.2f;
				targetC.x = 0.2f;
				generateRandomVertex();
			}

			// clear collided bullets
			vector<Bullet>::iterator it = bullets.begin() + i;
			bullets.erase(it);

			// continue to next item
			continue;
		}

		// check and update their lifetime
		bullets[i].lifeTime += deltaTime;
		if (bullets[i].lifeTime >= 2.0f) {
			vector<Bullet>::iterator it = bullets.begin() + i;
			bullets.erase(it);
		}
	}

	// update pretime
	preTime = curTime;

	// redisplay changes
	glutPostRedisplay();
}
#pragma endregion

int main(int argc, char* argv[])
{
	// initialize
	init();

	// initialize GLUT
	glutInit(&argc, argv);

	// specify double buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// set window size
	glutInitWindowSize((int)width, (int)height);

	// create window w/ title
	glutCreateWindow("A05 - Kyle James");

	// register callbacks with GLUT

	// GLUT resize
	glutReshapeFunc(reshape);

	// GLUT display
	glutDisplayFunc(display);

	// GLUT key up
	glutKeyboardUpFunc(keyup);

	// GLUT keyboard
	glutKeyboardFunc(keyboard);

	// GLUT idle
	glutIdleFunc(update);

	// GLUT loop
	glutMainLoop();

	return 0;
}