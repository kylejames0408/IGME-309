#pragma region Inclusions
#include "Bullet.h"
#pragma endregion

/// <summary>
/// Default constructor.
/// </summary>
Bullet::Bullet()
{
	// initialize variables
	position = vec2(0.0f);
	radius = 0.1f;
	lifeTime = 0.0f;
	velocity = 3.0f;
	rotation = 1.57f;
}

/// <summary>
/// Constructor.
/// </summary>
/// <param name="_position">Position of bullet.</param>
/// <param name="_rotation">Rotation of the cannon on launch.</param>
Bullet::Bullet(vec2 _position, float _rotation)
{
	// initialize variables
	position = _position;
	radius = 0.1f;
	lifeTime = 0.0f;
	velocity = 3.0f;
	rotation = _rotation;
}

/// <summary>
/// Default destructor.
/// </summary>
Bullet::~Bullet()
{
	// nullify variables
	radius = 0.0f;
	lifeTime = 0.0f;
	velocity = 0.0f;
}
