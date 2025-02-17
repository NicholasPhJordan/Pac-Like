#include "NodeGraph.h"
#include <raylib.h>

std::deque<NodeGraph::Node*> NodeGraph::findPath(Node* start, Node* end)
{
	// Find a path from start to end (The current implementation is obviously insufficient)
	//if start or end are null return 
	/*if (!start || !end)
		return;*/

	//Check if the start or the goal pointer is null
	if (!start || !end)
	{
		//return an empty list
		return;
		//end if statement
	}

	start->visted = true;

	//Create a node pointer that will act as an iterator for the graph
	Node* currentNode;
	//Create an open list
	std::deque<Node*> open;

	//Create a closed list
	std::deque<Node*> close;

	//Add start to the open list
	open.push_front(start);

	//Loop while the open list is not empty
	while (!open.empty())
	{
		//Sort the items in the open list by the f score
		for (int i = 0; i < open.size(); i++)
		{
			for (int j = open.size() - 1; j > i; j--)
			{
				if (open[j] < open[j - 1])
				{
					Node* newArr = open[j];
					open[j] = open[j - 1];
					open[j - 1] = newArr;
				}
			}
		}

		//Set the iterator to be the first item in the open list
		currentNode = open[0];

		//Check if the iterator is pointing to the goal node
		if (currentNode == end)
		{
			//Return the new path found
			return;

			//end if statement
		}

		//Pop the first item off the open list
		open.pop_front();
		//Add the first item to the closed list
		close.push_back(currentNode);

		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = currentNode->connections[i].target;

			//Check if node at the end of the edge is in the closed list
			for (int i = 0; i < close.size(); i++)
				if (currentEdgeEnd == close[i])
				{
					//Create a float and set it to be the g score of the iterator plus the cost of the edge
					float gScorePlus = currentNode->gScore + currentEdgeEnd->connections[i].cost;
					//Create a float and set it to be the h score of the node at the end of the edge
					float hScore = end->gScore;
					//Create a float for the f score and set it to be the g score combined with the h score
					float fScore = hScore + gScorePlus;

					currentNode->visted = true;
					currentNode->gScore = gScorePlus;
					currentNode = currentNode->previous;
					open.push_back(currentNode);
				}
			//end loop
		}
		//end loop
		return ;
	}
}

void NodeGraph::drawGraph(Node* start)
{
	std::deque<Node*>* drawnList = new std::deque<Node*>();
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void NodeGraph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void NodeGraph::drawConnectedNodes(Node* node, std::deque<Node*>* drawnList)
{
	//drawNode(node);
	drawnList->push_back(node);

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}
