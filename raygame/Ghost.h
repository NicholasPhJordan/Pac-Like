#pragma once
#include "Agent.h"
#include "SeekPathBehavior.h"
#include "WanderBehavior.h"
#include "SeekBehavior.h"

class Maze;

class Ghost : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	/// <param name="color">The color in 0xRRGGBBAA</param>
	/// <param name="maze">The maze used for pathfinding</param>
	Ghost(float x, float y, float speed, int color, Maze* maze);
	~Ghost();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

	bool cheackTargetInSight();

	/// <returns>The current target</returns>
	Actor* getTarget();
	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

private:
	SeekPathBehavior* m_pathfindBehavior;
	WanderBehavior* m_wanderBehavior;
	SeekBehavior* m_seekBehavior;
	Maze* m_maze;

	Actor* m_target = nullptr;
};

