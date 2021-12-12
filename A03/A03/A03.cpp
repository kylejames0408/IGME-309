// Course: IGME 309-05
// Student Name: Kyle James
// Assignment Number: 03

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

// Memory Leak Detection Inclusions
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "PolyObject.h"

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };

vector<PolyObject*> polygons = vector<PolyObject*>();
PolyObject* curObj;
vec3 curColor;

vec2 mousePos;

void init(void)
{
    curColor = vec3(0, 0, 0);
    mousePos = vec2(0, 0);
    curObj = new PolyObject();
    polygons.push_back(curObj);
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int i = 0; i < polygons.size() - 1; i++) {
        polygons[i]->draw();
    }

    curObj->draw(mousePos);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];
        curObj->addVertex(mousePos);

        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 13: // enter
        curObj = new PolyObject();
        polygons.push_back(curObj);
        curObj->setColor(curColor); // ensure that the same color is used
        break;
    case 27: // esc
        // Clear memory
        for (int i = 0; i < polygons.size(); i++) {
            delete polygons[i];
            polygons[i] = NULL;
        }
        curObj = NULL;

        exit(0);
        break;
    }
}

void menu(int value)
{
    switch (value) {
    case 0: // clear
        // Clear memory
        for (int i = 0; i < polygons.size(); i++) {
            delete polygons[i];
            polygons[i] = NULL;
        }
        curObj = NULL;

        // Create new spaces in memory for objects
        polygons = vector<PolyObject*>();
        curObj = new PolyObject();
        polygons.push_back(curObj);

        glutPostRedisplay();
        break;
    case 1: //exit
        // Clear memory
        for (int i = 0; i < polygons.size(); i++) {
            delete polygons[i];
            polygons[i] = NULL;
        }
        curObj = NULL;

        exit(0);
    case 2: // red
        curColor = vec3(1, 0, 0);
        curObj->setColor(curColor);
        glutPostRedisplay();
        break;
    case 3: // green
        curColor = vec3(0, 1, 0);
        curObj->setColor(curColor);
        glutPostRedisplay();
        break;
    case 4: // blue
        curColor = vec3(0, 0, 1);
        curObj->setColor(curColor);
        glutPostRedisplay();
        break;
    case 5: // black
        curColor = vec3(0, 0, 0);
        curObj->setColor(curColor);
        glutPostRedisplay();
    default:
        break;
    }
}
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);
    glutAddMenuEntry("Black", 5);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("A03 - Kyle James");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();

    // Check for memory leaks
    _CrtDumpMemoryLeaks();
    return 0;
}