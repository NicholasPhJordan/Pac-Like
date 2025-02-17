#include "Ghost.h"
#include "Maze.h"
#include "Wall.h"
#include "raylib.h"

Ghost::Ghost(float x, float y, float maxSpeed, int color, Maze* maze)
	: Agent(x, y, Maze::TILE_SIZE / 2.5f, maxSpeed, maxSpeed, color)
{
	m_maze = maze;
	m_pathfindBehavior = new SeekPathBehavior(maze);
	m_pathfindBehavior->setColor(color);
	addBehavior(m_pathfindBehavior);

	m_seekBehavior = new SeekBehavior();
	addBehavior(m_seekBehavior);

	m_wanderBehavior = new WanderBehavior(2, 2);
	addBehavior(m_wanderBehavior);
}

Ghost::~Ghost()
{
	delete m_seekBehavior;
	delete m_pathfindBehavior;
	delete m_wanderBehavior;
}

void Ghost::update(float deltaTime)
{
	m_seekBehavior->getEnabled();
	m_wanderBehavior->getEnabled();

	if (cheackTargetInSight())
	{
		m_wanderBehavior->setEnabled(false);
		m_seekBehavior->setEnabled(true);
	}
	else
	{
		m_wanderBehavior->setEnabled(true);
		m_seekBehavior->setEnabled(false);
	}

	Agent::update(deltaTime);
}

void Ghost::draw()
{
	m_pathfindBehavior->draw(this);
	Agent::draw();
}

void Ghost::onCollision(Actor* other)
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
}

bool Ghost::cheackTargetInSight()
{
	//chack if target is null, if so return false
	if (getTarget() == nullptr)
		return false;

	//find the direction vector that the represetns where the target is relative to the enemy
	float targetPosition = (getTarget()->getWorldPosition() - getWorldPosition()).getMagnitude();

	if (targetPosition <= 3.0f)
		return true;

	return false;
}

void Ghost::setTarget(Actor* target)
{
	m_target = target;
	m_pathfindBehavior->setTarget(target);
}

Actor* Ghost::getTarget()
{
	return m_target;
}
