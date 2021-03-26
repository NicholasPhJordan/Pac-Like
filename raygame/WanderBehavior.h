#pragma once
#include "Behavior.h"

class WanderBehavior : public Behavior
{
public:
	WanderBehavior(float circleDistance, float circleRadius);

	/// <summary>
	/// Get a Random x and y coordinate 
	/// </summary>
	MathLibrary::Vector2 getRandomPosition();

	/// <summary>
	/// Update the Behavior, affecting its owning Agent where necessary.
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	/// <param name="deltaTime"></param>
	virtual void update(Agent* owner, float deltaTime) override;

private:
	float m_circleDistance;
	float m_circleRadius;
};

