#include "Pac.h"
#include "Maze.h"
#include "Wall.h"
#include "raylib.h"

Pac::Pac(float x, float y, float maxSpeed)
	: Agent(x, y, Maze::TILE_SIZE / 2.5f, maxSpeed, maxSpeed, (int)0xFFFF66FF)
{
	/*m_wanderBehavior = new WanderBehavior(5, 5);
	addBehavior(m_wanderBehavior);*/

	m_evadeBehavior = new Evade();
	addBehavior(m_evadeBehavior);
}

Pac::~Pac()
{
	//delete m_keyboardBehavior;
	delete m_wanderBehavior;
	delete m_evadeBehavior;
}

void Pac::draw()
{
	Agent::draw();
}

void Pac::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		setWorldPostion(tilePosition);

		setVelocity({ 0, 0 });
	}

	if (Agent* ghost = dynamic_cast<Agent*>(other)) {
		setColor((int)0xC14242FF);
		setMaxSpeed(0);
		setMaxForce(0);
		setVelocity({ 0, 0 });
	}
}

void Pac::setTarget(Actor* target)
{
	m_target = target;
	m_evadeBehavior->setTarget(target);
}

Actor* Pac::getTarget()
{
	return m_target;
}
