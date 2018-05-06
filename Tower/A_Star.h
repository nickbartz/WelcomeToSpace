#pragma once

// USED FOR PATHFINDING 
int obstacle_map[SEARCH_WIDTH][SEARCH_WIDTH];
int closed_nodes_map[SEARCH_WIDTH][SEARCH_HEIGHT];
int open_nodes_map[SEARCH_WIDTH][SEARCH_HEIGHT];
int dir_map[SEARCH_WIDTH][SEARCH_HEIGHT];

class Path_Field {
public:
	Path_Field(World* world);
	vector<Tile_Queue> pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish, int recursion);
	void run_A_star(int xA, int yA, int xB, int yB);
	bool Path_Field::check_if_tile_is_inaccessible(int xdx, int ydy, int finish_x, int finish_y);

	World* world_pointer;

	const int dx[4] = { 1, 0, -1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };

};

Path_Field::Path_Field(World* world)
{
	world_pointer = world;
}

class node
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

public:
	node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest)
	{
	priority = level + estimate(xDest, yDest) * 10; //A*
	}

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i) // i: direction
	{
		level += 10;
	}

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		// Euclidian Distance
		//d = static_cast<int>(sqrt(xd*xd + yd*yd));

		// Manhattan distance
		//d=abs(xd)+abs(yd);

		// Chebyshev distance
		d = max(abs(xd), abs(yd));

		return(d);
	}
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
	return a.getPriority() > b.getPriority();
}

vector<Tile_Queue> Path_Field::pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish, int recursion)
{
	int start_x = xStart;
	int start_y = yStart;
	int finish_x = xFinish;
	int finish_y = yFinish;

	vector<Tile_Queue> vector_path;
	static priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static node* n0;
	static node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	// reset the node maps
	for (y = 0; y < SEARCH_HEIGHT; y++)
	{
		for (x = 0; x < SEARCH_WIDTH; x++)
		{
			obstacle_map[x][y] = 0;
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	//obstacle_map[50][45] = 1;

	// create the start node and push into list of open nodes
	n0 = new node(start_x, start_y, 0, 0);
	n0->updatePriority(finish_x, finish_y);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->getPriority(); // mark it on the open nodes map

	// A* search
	while (!pq[pqi].empty())
	{
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x][y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x][y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == finish_x && y == finish_y)
		{
			// generate the path from finish to start
			// by following the directions
			int counter = 0;

			while (!(x == start_x && y == start_y))
			{
				j = dir_map[x][y];

				vector_path.push_back({ x, y,counter });
				x += dx[j];
				y += dy[j];
				counter++;
			}

			vector_path.push_back({ start_x, start_y,counter });

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return vector_path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i<4; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>SEARCH_WIDTH - 1 || ydy<0 || ydy>SEARCH_HEIGHT - 1 || check_if_tile_is_inaccessible(xdx, ydy, finish_x, finish_y) || closed_nodes_map[xdx][ydy] == 1))
			{
				// generate a child node
				m0 = new node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(finish_x, finish_y);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx][ydy] = (i + 4 / 2) % 4;
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					// update the priority info
					open_nodes_map[xdx][ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx][ydy] = (i + 4 / 2) % 4;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

					// empty the larger size pq to the smaller one
					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	cout << "did not find path" << endl;
	return vector_path; // no route found
}

bool Path_Field::check_if_tile_is_inaccessible(int xdx, int ydy, int finish_x, int finish_y)
{
	bool inaccessible = false;
	if (!(xdx == finish_x && ydy == finish_y))
	{
		if (world_pointer->world_tiles[xdx][ydy]->multi_tile_config.is_collidable == 1)
		{
			if (world_pointer->world_tiles[xdx][ydy]->multi_tile_config.built_percent >= 100 && world_pointer->world_tiles[xdx][ydy]->multi_tile_config.door_state == 0) inaccessible = true;
		}
		if (world_pointer->item_tiles[xdx][ydy] != NULL && world_pointer->item_tiles[xdx][ydy]->multi_tile_config.is_collidable == 1)
		{
			if (world_pointer->item_tiles[xdx][ydy]->multi_tile_config.built_percent >= 100) inaccessible = true;
		}
	}
	return inaccessible;
}

void Path_Field::run_A_star(int xA, int yA, int xB, int yB)
{
	srand(time(NULL));

	cout << "Map Size (X,Y): " << SEARCH_WIDTH << "," << SEARCH_HEIGHT << endl;
	cout << "Start: " << xA << "," << yA << endl;
	cout << "Finish: " << xB << "," << yB << endl;
	
	vector<Tile_Queue> route = pathFind(xA, yA, xB, yB, 0);

	for (int i = 0; i < route.size(); i++)
	{
		cout << route[i].x_tile << ", " << route[i].y_tile << endl;
	}
	
	return;
}