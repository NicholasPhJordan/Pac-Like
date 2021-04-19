#pragma once
#include "Agent.h"
#include "KeyboardBehavior.h"
#include "WanderBehavior.h"
#include "Evade.h"

class Pac : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	Pac(float x, float y, float speed);
	~Pac();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

	virtual bool cheackTargetInSight();

	/// <returns>The current target</returns>
	Actor* getTarget();
	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

private:
	//KeyboardBehavior* m_keyboardBehavior;
	WanderBehavior* m_wanderBehavior;
	Evade* m_evadeBehavior;

	Actor* m_target = nullptr;
};

