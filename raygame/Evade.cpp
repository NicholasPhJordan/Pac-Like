#include "Evade.h"

void Evade::update(Agent* owner, float deltaTime)
{
	//Don't update if disabled or no target
	if (!getEnabled() || !m_target)
		return;

	MathLibrary::Vector2 position = owner->getWorldPosition();
	MathLibrary::Vector2 avoidPosition = m_target->getWorldPosition();

	//Find the direction
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(position - avoidPosition);

	//Calculate the force
	MathLibrary::Vector2 desiredVelocity = direction * owner->getMaxSpeed();
	MathLibrary::Vector2 steeringForce = desiredVelocity - owner->getVelocity();

	//Apply the force
	owner->applyForce(steeringForce);
}
