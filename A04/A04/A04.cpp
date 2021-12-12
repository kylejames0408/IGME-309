// Course: IGME 309-05
// Student Name: Kyle James
// Assignment Number: 04

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

#define MAX_NUM_RECTANGLE 16

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;

float colors[3 * MAX_NUM_RECTANGLE];
float rotations[MAX_NUM_RECTANGLE];

int selected;

void init(void)
{
    for (int i = 0; i < MAX_NUM_RECTANGLE; i++) {
        colors[i * 3 + 0] = 0.0f; // red
        colors[i * 3 + 1] = 0.0f; // green
        colors[i * 3 + 2] = 0.0f; // blue

        rotations[i] = 0.0f;
    }

    selected = 0;
    colors[selected * 3 + 0] = 1.0f;
}

/// <summary>
/// Draws a rectangle from (0, 0) using width and height to determine dimensions, and color to determine outline coloring.
/// </summary>
/// <param name="width">The width of the rectangle.</param>
/// <param name="height">The height of the rectangle.</param>
/// <param name="c">The color of the rectangle.</param>
void drawRectangle(float width, float height, const float* c)
{
    glColor3fv(c);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(width, height);
    glVertex2f(0, height);
    glEnd();
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix(); // push the original coordinate system to return to

    // Body Drawing Structure
    //  - set the rectangle id
    //  - set the pivot point
    //  - rotate
    //  - translate to proper position
    //  - draw the rectangle
    //  - push/pop where necessary

    int rid = -1; // the index of current rectangle

    // lower body
    rid = 0;
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, 0.0f, 0.0f);
    drawRectangle(2, 1, colors + rid * 3);

    glPushMatrix(); // push the lower body CS to the modelview stack

    // upper body
    rid = 1;
    glTranslatef(1.0f, 1.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.5f, 0.0f, 0.0f);
    drawRectangle(3, 2, colors + rid * 3);

    glPushMatrix(); // push the upper body CS to the modelview stack

    // right arm
    rid = 2;
    glTranslatef(3.0f, 1.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -0.25, 0.0f);
    drawRectangle(1, 0.5, colors + rid * 3);
    
    // right forearm
    rid = 3;
    glTranslatef(1.0f, 0.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -0.25f, 0.0f);
    drawRectangle(1, 0.5, colors + rid * 3);

    // right hand
    rid = 4;
    glTranslatef(1.0f, 0.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    drawRectangle(1, 1, colors + rid * 3);

    glPopMatrix(); // pop the right arm off the stack to the upper
    glPushMatrix(); // push the upper body CS to the modelview stack

    // left arm
    rid = 5;
    glTranslatef(0.0f, 1.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, -0.25f, 0.0f);
    drawRectangle(1, 0.5, colors + rid * 3);

    // left forearm
    rid = 6;
    glTranslatef(0.0f, 0.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, -0.25f, 0.0f);
    drawRectangle(1, 0.5, colors + rid * 3);
    
    // left hand
    rid = 7;
    glTranslatef(0.0f, 0.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, -0.5f, 0.0f);
    drawRectangle(1, 1, colors + rid * 3);
    
    glPopMatrix(); // pop the left arm off the stack to the upper copy

    // neck
    rid = 8;
    glTranslatef(1.5f, 2.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.125f, 0.0f, 0.0f);
    drawRectangle(0.25, 1, colors + rid * 3);
    
    // head
    rid = 9;
    glTranslatef(0.125f, 1.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, 0.0f, 0.0f);
    drawRectangle(2, 2, colors + rid * 3);
    
    glPopMatrix(); // pop the upper body off the stack
    glPushMatrix(); // push the lower body CS to the modelview stack
    
    // right thigh
    rid = 10;
    glTranslatef(0.25f, 0.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.25f, -1.5f, 0.0f);
    drawRectangle(0.5, 1.5, colors + rid * 3);
    
    // right leg
    rid = 11;
    glTranslatef(0.25f, 0.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.25f, -1.5f, 0.0f);
    drawRectangle(0.5, 1.5, colors + rid * 3);

    // right foot
    rid = 12;
    glTranslatef(0.0f, 0.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.0f, -0.25f, 0.0f);
    drawRectangle(1, 0.5, colors + rid * 3);

    glPopMatrix(); // pop the right leg

    // left thigh
    rid = 13;
    glTranslatef(1.75f, 0.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.25f, -1.5f, 0.0f);
    drawRectangle(0.5, 1.5, colors + rid * 3);

    // left leg
    rid = 14;
    glTranslatef(0.25f, 0.0f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.25f, -1.5f, 0.0f);
    drawRectangle(0.5, 1.5, colors + rid * 3);

    // left foot
    rid = 15;
    glTranslatef(0.5f, 0.25f, 0.0f);
    glRotatef(rotations[rid], 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -0.25f, 0.0f);
    drawRectangle(1, 0.5, colors + rid * 3);

    glPopMatrix(); // pop the left leg off the stack - return to orignal CS

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);
    if (key == 65 || key == 97) { // a key - rotate left 5 degrees
        rotations[selected] += 5;
    }
    if (key == 68 || key == 100) { // d key - rotate right 5 degrees
        rotations[selected] -= 5;
    }
    if (key == 83 || key == 115) { // s key - change selection down
        if (selected > 0 ) {
            // change current selection to black
            colors[selected * 3 + 0] = 0.0f;

            // update selection
            selected--;

            // change new selection to red
            colors[selected * 3 + 0] = 1.0f;
        }
    }
    if (key == 87 || key == 119) { // w key - change selection up
        if (selected < MAX_NUM_RECTANGLE - 1) {
            // change current selection to black
            colors[selected * 3 + 0] = 0.0f;

            // update selection
            selected++;

            // change new selection to red
            colors[selected * 3 + 0] = 1.0f;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("A04 - Kyle James");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}