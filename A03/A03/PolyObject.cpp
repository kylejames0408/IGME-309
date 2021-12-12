// Course: IGME 309-05
// Student Name: Kyle James
// Assignment Number: 03

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "PolyObject.h"

/// <summary>
/// Constructs new PolyObject.
/// </summary>
PolyObject::PolyObject()
{
	vertices = vector<vec2>();
	color = vec3(0, 0, 0);
}

/// <summary>
/// Destructs old PolyObject.
/// </summary>
PolyObject::~PolyObject()
{
    vertices.clear();
}

/// <summary>
/// Adds a vertex to the polygon.
/// </summary>
/// <param name="p_vert">Vertex to add.</param>
void PolyObject::addVertex(vec2 p_vert)
{
	vertices.push_back(p_vert);
}

/// <summary>
/// Sets the color of the polygon.
/// </summary>
/// <param name="p_color">Desired polygon color.</param>
void PolyObject::setColor(vec3 p_color)
{
	color = p_color;
}

/// <summary>
/// Gets the number of vertices in the polygon.
/// </summary>
/// <returns>The number of vertices in the polygon.</returns>
unsigned int PolyObject::getVertNum()
{
	return vertices.size();
}

/// <summary>
/// Draws a polygon no longer in the active state.
/// </summary>
void PolyObject::draw()
{
    // Set the draw color
    glColor3f(color.x, color.y, color.z);

    if (getVertNum() == 1) {
        // Draw a point if there's only one vertex
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        glVertex2f(vertices[0].x, vertices[0].y);
        glEnd();
        glPointSize(1.0f);
    }
    else if (getVertNum() == 2) {
        // Draw a line if there's only two vertices
        glBegin(GL_LINES);
        for (int i = 0; i < getVertNum(); i++) {
            glVertex2f(vertices[i].x, vertices[i].y);
        }
        glEnd();
    }
    else if (getVertNum() > 2) {
        // Draw a polygon if there's only two vertices
        glBegin(GL_POLYGON);
        for (int i = 0; i < getVertNum(); i++) {
            glVertex2f(vertices[i].x, vertices[i].y);
        }
        glEnd();
    }
}

/// <summary>
/// Actively draws a new polygon.
/// </summary>
/// <param name="p_mousePos">The mouse position.</param>
void PolyObject::draw(vec2 p_mousePos)
{
    // Set the draw color
    glColor3f(color.x, color.y, color.z);

    if (getVertNum() == 1) {
        // Draw the first line
        glBegin(GL_LINES);
        glVertex2f(vertices[0].x, vertices[0].y);
        glVertex2f(p_mousePos.x, p_mousePos.y);
        glEnd();
    }
    else if (getVertNum() > 1) {
        // Draw the remainder of the shape
        glBegin(GL_POLYGON);
        for (int i = 0; i < getVertNum(); i++) {
            glVertex2f(vertices[i].x, vertices[i].y);
        }
        glVertex2f(p_mousePos.x, p_mousePos.y);
        glEnd();
    }
}
