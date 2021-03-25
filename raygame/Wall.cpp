#include "Wall.h"
#include "Maze.h"

Wall::Wall(float x, float y)
	: Actor(x, y, Maze::TILE_SIZE / 2.0f, 0, 0x3333CCFF)
{
	setStatic(true);
}
