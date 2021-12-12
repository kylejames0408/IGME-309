#pragma once
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
#pragma endregion

#pragma region Namespaces
using namespace std; // standard namespace
using namespace glm; // GL math library namespace
#pragma endregion

/// <summary>
/// Class to store basic bullet information.
/// </summary>
class Bullet
{
public:
	vec2 position; // position
	float radius, lifeTime, velocity, rotation; // radius, time alive, velocity, and rotation of the bullet
	
	/// <summary>
	/// Default constructor.
	/// </summary>
	Bullet();

	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="_position">Position of bullet.</param>
	/// <param name="_rotation">Rotation of the cannon on launch.</param>
	Bullet(vec2 _position, float _rotation);

	/// <summary>
	/// Default destructor.
	/// </summary>
	~Bullet();
};