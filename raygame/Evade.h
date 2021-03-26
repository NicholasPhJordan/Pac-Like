#pragma once
#include "Behavior.h"
#include "raylib.h"

class Evade : public Behavior
{
public: 
	Evade() {}

	/// <summary>
	/// Update the Behavior, affecting its owning Agent where necessary.
	/// </summary>
	/// <param name="owner">The Agent to which this Behavior belongs</param>
	/// <param name="deltaTime"></param>
	virtual void update(Agent* owner, float deltaTime) override;

	void setTarget(Actor* target) { m_target = target; }
	Actor* getTarget() { return m_target; }

private:
	Actor* m_target = nullptr;
};

