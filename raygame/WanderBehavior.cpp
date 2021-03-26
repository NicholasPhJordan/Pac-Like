#include "WanderBehavior.h"
#include "Maze.h"
#include "raylib.h"
#include <Vector2.h>

WanderBehavior::WanderBehavior(float circleDistance, float circleRadius)
{
	m_circleDistance = circleDistance;
	m_circleRadius = circleRadius;
}

MathLibrary::Vector2 WanderBehavior::getRandomPosition()
{
	int rando = rand() % 760 + 1;
	int rando2 = rand() % 760 + 1;
	MathLibrary::Vector2 randPosition = MathLibrary::Vector2(cos(rando), sin(rando2));
	return randPosition;
}

void WanderBehavior::update(Agent* owner, float deltaTime)
{
	//dont update if disabled 
	if (!getEnabled())
		return;
	//gets the direction the owner is facing 
	MathLibrary::Vector2 facing = owner->getVelocity();
	facing.getNormalized();

	//sacled direction to get circle distance
	MathLibrary::Vector2 circleLocation = facing * m_circleDistance;

	//the displacement from the current direction
	MathLibrary::Vector2 displacement = getRandomPosition() * m_circleRadius;
	
	//the new direction and force 
	MathLibrary::Vector2 wanderForce = displacement + circleLocation;

	//Apply the force
	owner->applyForce(wanderForce);
}