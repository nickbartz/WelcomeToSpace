#ifndef WORLD_H
#define WORLD_H

struct Coordinate {
	int x, y;
	Coordinate(int x, int y) : x(x), y(y) {}

	bool operator<(const Coordinate& coord) const {
		if (y < coord.y) return true;
		if (y > coord.y) return false;

		if (x < coord.x) return true;
		if (x > coord.x) return false;

		return false;
	}

	bool operator==(const Coordinate& coord) const {
		if (x == coord.x && y == coord.y)
			return true;
		return false;
	}

	inline bool isInRange(Coordinate coord, int range) const {
		if (pow(coord.x - this->x, 2) + pow(coord.y - this->y, 2) <= range*range)
			return true;
		return false;
	}
};

struct auto_room
{
	int center_x;
	int center_y;
	int tile_type_wall;
	int width;
	int height;
	int faction;
	bool is_filled = true;
	int tile_type_floor = TILE_CONSTRUCTION_TUBE_FLOOR_1;
};

class World {
public:

	// Basic Commands
	World(SDL_Renderer* gRenderer, LTexture textures[], bool new_game);
	void Render(Camera* camera, int render_layer);
	void Free();

	struct tile_clip_coords
	{
		int clip_x;
		int clip_y;
	};
	
	// Create Commands
	void Create_Background();
	void Populate_Asteroids();
	void Create_Asteroid_Cluster(int start_x, int start_y, int size);
	void Create_Room_From_Data_File(int x_tile_start, int y_tile_start, string filename, int faction);
	void Create_Test_Room(int x_start, int y_start, int faction);
	void Create_Box_Shape(auto_room room);
	void Connect_Box_Centers(auto_room room_a, auto_room room_b, int hall_breadth);
	
	bool Check_If_Can_Be_Placed(Tile_Template* item, int x_tile, int y_tile);
	bool Check_If_Scaffold_Can_Be_Placed(Tile_Template* item, int x_tile, int y_tile);
	bool Tile_Is_Accessible(int x_tile, int y_tile);
	Tile* Find_Accessible_Adjacent_Tile(Dot* tile);
	Tile* Find_Random_Accessible_Surrounding_Tile(Dot* tile);
	Tile* Find_Accessible_Tile_Away_From_Dot(Dot* dot_to_move, Dot* dot_to_move_away_from);
	void Create_Tile(Tile_Template tile, int x_tile, int y_tile, int faction = DOT_FACTION_NO_FACTION);
	void Add_Scaffold_To_Tile(Tile_Template tile, int x_tile, int y_tile, int faction);


	// Check Commands
	bool is_tile_onscreen(int i, int p, Camera* camera);
	int Check_Tile_Type(int x_tile, int y_tile, bool tile_or_item = true);
	Tile* Return_Tile_Neighbor(int x_tile, int y_tile, int neighbor, bool tile_or_item = true);
	Tile_Init Save_Tile(int tile_x, int tile_y);
	void Load_Tile(Tile_Init loaded_tile);
	bool Is_Tile_Collidable(int x_tile, int y_tile);

	int get_num_scaffolds(bool tile_or_item);
	int get_number_of_tiles_of_type(Tile_Template tile_type);

	bool check_if_dot_in_radius_of_another_dot(Dot* dot_one, Dot* dot_two, int radius);
	Dot* Find_tile_within_radius_of_dot(Dot* dot, int tile_type, int radius, bool tile_or_item);

	// Fix Orientation
	void Update_Surrounding_Tiles(Tile* tile);
	void Fix_Smooth_Tile(Tile* tile);

	// Tile Specific Commands
	void Remove_Tile(int i, int p, bool is_item);
	void Grow_Frenzel(int i, int p, int current_frenzel_amount);

	// Aggregate Commands
	struct oxygenation_check
	{
		bool breach_status;
		vector<Tile*> tile_vector;
	};
	oxygenation_check* Test_All_Tile_Neighbors_For_Leaks(Tile* tile, oxygenation_check* current_breach_check);
	void Toggle_Room_Tiles_Oxygenated(vector<Tile*> vector_to_oxygenate, float oxygen_per_tile);

	// Overall Flow Commands
	void Update_World();

	// Tile Array 
	Tile* world_tiles[TILE_NUM_X][TILE_NUM_Y];	
	Tile* item_tiles[TILE_NUM_X][TILE_NUM_Y];
	map <Coordinate, Light*> light_tiles;

private:
	LTexture* texture_array[NUM_TILESHEETS];
	SDL_Rect* basic_tilesheet_clips[BASIC_TILESHEET_WIDTH][BASIC_TILESHEET_HEIGHT];

	SDL_Renderer* world_renderer;
	SDL_Rect* current_clip;

	SDL_Texture* shadow_texture;

	int delay_counter = 0;
	int tile_orientation = 0;

};

World::World(SDL_Renderer* gRenderer, LTexture textures[], bool new_game)
{
	for (int p = 0; p < NUM_TILESHEETS; ++p) { texture_array[p] = &textures[p]; }

	world_renderer = gRenderer;
	shadow_texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

	Create_Background();
	
	//Create_Test_Room(150,150, DOT_FACTION_PLAYER);

	Create_Room_From_Data_File(150, 150, "Rooms/test_room.csv", DOT_FACTION_PLAYER);

	Populate_Asteroids();

}

void World::Create_Background()
{
	for (int p = 0; p < TILE_NUM_X; p++)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			Create_Tile(Return_Tile_Template_By_Identifier(TILE_VACUUM), i, p);
		}
	}
}

void World::Populate_Asteroids()
{
	for (int p = 0; p < TILE_NUM_X; p++)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			int asteroid_cluster_chance = rand() % 1000;
			int asteroid_cluster_size = rand() % 10;
			if (asteroid_cluster_chance >= 998) Create_Asteroid_Cluster(i, p, asteroid_cluster_size);
		}
	}
}

void World::Create_Asteroid_Cluster(int start_x, int start_y, int size)
{
	for (int p = start_y; p < min(TILE_NUM_Y,start_y + size); p++)
	{
		for (int i = start_x; i < min(TILE_NUM_X,start_x + size); i++)
		{
			if (world_tiles[i][p]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
			{
				int asteroid_type = rand() % 1000;

				if (asteroid_type >= 990) Create_Tile(Return_Tile_Template_By_Identifier(TILE_ASTEROID_NICKEL), i, p);
				else if (asteroid_type >= 950) Create_Tile(Return_Tile_Template_By_Identifier(TILE_ASTEROID_COBALT), i, p);
				else if (asteroid_type >= 800) Create_Tile(Return_Tile_Template_By_Identifier(TILE_ASTEROID_IRON), i, p);
			}

		}
	}
}

void World::Create_Room_From_Data_File(int x_tile_start, int y_tile_start, string filename, int faction)
{
	ifstream inputFile;
	string line;

	int num_rows = 0;
	int num_columns = 0;

	int y_tile = y_tile_start;
	int x_tile = x_tile_start;

	inputFile.open(filename.c_str(), ios::in);

	if (inputFile.good())
	{
		while (getline(inputFile, line, ','))
		{
			stringstream raw_num(line);


			int tile_num = 0;
			raw_num >> tile_num;

			if (line[0] != '/')
			{
				if (tile_num > 0)
				{
					if (Return_Tile_Template_By_Identifier(tile_num).tile_or_item == 1 && Return_Tile_Template_By_Identifier(tile_num).tile_type != TILE_TYPE_TURRET)
					{
						Create_Tile(Return_Tile_Template_By_Identifier(40), x_tile, y_tile, faction);
						Create_Tile(Return_Tile_Template_By_Identifier(tile_num), x_tile, y_tile, faction);
					}
					else Create_Tile(Return_Tile_Template_By_Identifier(tile_num), x_tile, y_tile, faction);
				}
				x_tile++;
				num_columns++;
			}
			else if (line[0] == '/')
			{
				num_columns = 0;
				num_rows++;
				y_tile++;
				x_tile = x_tile_start;
				x_tile++;
			}

		}

		for (int p = y_tile_start; p < y_tile_start + num_rows; p++)
		{
			for (int i = x_tile_start; i < x_tile_start + num_columns; i++)
			{
				if (world_tiles[i][p] != NULL) Fix_Smooth_Tile(world_tiles[i][p]);
				if (item_tiles[i][p] != NULL) Fix_Smooth_Tile(item_tiles[i][p]);
			}
		}
	}
	else
	{
		cout << "could not open data file for parsing" << endl;
	}

	inputFile.close();
}

void World::Create_Test_Room(int x_start, int y_start, int faction)
{
	auto_room room_a = { x_start, y_start, TILE_CONSTRUCTION_TUBE_WALL_1, 8, 8, faction, true, TILE_CONSTRUCTION_TUBE_FLOOR_1 };
	auto_room room_b = { x_start - 10, y_start + 10, TILE_CONSTRUCTION_TUBE_WALL_1, 8, 8, faction, true, TILE_CONSTRUCTION_TUBE_FLOOR_1 };
	auto_room room_c = { x_start + 10, y_start + 10, TILE_CONSTRUCTION_TUBE_WALL_1, 8, 8, faction, true, TILE_CONSTRUCTION_TUBE_FLOOR_1 };
	auto_room room_d = { x_start, y_start - 10, TILE_CONSTRUCTION_TUBE_WALL_1, 8, 8, faction, true, TILE_CONSTRUCTION_TUBE_FLOOR_1 };

	Create_Box_Shape(room_a);
	Create_Box_Shape(room_b);
	Create_Box_Shape(room_c);
	Create_Box_Shape(room_d);

	Connect_Box_Centers(room_a, room_b, 2);
	Connect_Box_Centers(room_a, room_c, 2);
	Connect_Box_Centers(room_a, room_d, 2);
}

void World::Create_Box_Shape(auto_room room)
{
	SDL_Rect box_specs = { room.center_x - room.width/2, room.center_y - room.height/2, room.width, room.height };
	int tile_name = room.tile_type_wall;
	int faction = room.faction;
	bool is_filled = room.is_filled;
	int fill_tile_name = room.tile_type_floor;
	
	// Create_Corners
	if (world_tiles[box_specs.x][box_specs.y]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), box_specs.x, box_specs.y, faction);
	if (world_tiles[box_specs.x + box_specs.w][box_specs.y]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), box_specs.x + box_specs.w, box_specs.y, faction);
	if (world_tiles[box_specs.x][box_specs.y + box_specs.h-1]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), box_specs.x, box_specs.y + box_specs.h, faction);
	if (world_tiles[box_specs.x + box_specs.w][box_specs.y + box_specs.h-1]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), box_specs.x + box_specs.w, box_specs.y + box_specs.h, faction);

	// Create_Top_And_Bottom_Walls
	for (int i = box_specs.x + 1; i < (box_specs.x + box_specs.w); i++)
	{
		if (world_tiles[i][box_specs.y]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), i, box_specs.y, faction);
		if (world_tiles[i][box_specs.y + box_specs.h]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), i, box_specs.y + box_specs.h, faction);
	}

	// Create_Side_Walls
	for (int i = box_specs.y + 1; i < (box_specs.y + box_specs.h); i++)
	{
		if (world_tiles[box_specs.x][i]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), box_specs.x,i , faction);
		if (world_tiles[box_specs.x + box_specs.w][i]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) Create_Tile(Return_Tile_Template_By_Identifier(tile_name), box_specs.x + box_specs.w, i, faction);
	}

	if (is_filled)
	{
		for (int p = box_specs.y + 1; p < box_specs.y + box_specs.h; p++)
		{
			for (int i = box_specs.x + 1; i < box_specs.x + box_specs.w; i++)
			{
				Create_Tile(Return_Tile_Template_By_Identifier(fill_tile_name), i, p, faction);
			}
		}
	}
}

void World::Connect_Box_Centers(auto_room room_a, auto_room room_b, int hall_breadth)
{	
	Coordinate center_a = { room_a.center_x , room_a.center_y };
	Coordinate center_b = { room_b.center_x , room_b.center_y };
	Coordinate center_ab = { room_a.center_x, room_b.center_y};
	Coordinate center_ba = { room_b.center_x, room_a.center_y};
		
	// Eventually need to fill out hallway_baa and hallway aba so we can make it random which type of elbow join is chosen
	
	auto_room hallway_aab = { center_a.x, (center_a.y + center_ab.y)/2, room_a.tile_type_wall, hall_breadth, abs(center_a.y - center_ab.y) + 1, room_a.faction, room_a.is_filled, room_a.tile_type_floor };
	auto_room hallway_abb = { (center_ab.x + center_b.x)/2, center_ab.y, room_a.tile_type_wall, abs(center_ab.x - center_b.x) + 1, hall_breadth , room_a.faction, room_a.is_filled, room_a.tile_type_floor };

	int faction = room_a.faction;
	bool is_filled = room_a.is_filled;
	int fill_tile_name = room_a.tile_type_floor;


	Create_Box_Shape(hallway_aab);
	Create_Box_Shape(hallway_abb);
}

/// Create Commands

void World::Create_Tile(Tile_Template tile, int x_tile, int y_tile, int faction)
{
	if (tile.tile_or_item == 0)
	{
		if (world_tiles[x_tile][y_tile] != NULL) delete world_tiles[x_tile][y_tile];
		world_tiles[x_tile][y_tile] = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile, tile.build_time);
		world_tiles[x_tile][y_tile]->npc_dot_config.dot_stat_faction = faction;

		if (tile.is_smooth == 1)
		{
			Update_Surrounding_Tiles(world_tiles[x_tile][y_tile]);
			Fix_Smooth_Tile(world_tiles[x_tile][y_tile]);
		}
	}
	else if (tile.tile_or_item == 1 && world_tiles[x_tile][y_tile]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		if (item_tiles[x_tile][y_tile] != NULL && item_tiles[x_tile][y_tile]->multi_tile_config.inventory_pointer != tile.inventory_pointer) delete item_tiles[x_tile][y_tile];
		item_tiles[x_tile][y_tile] = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile, tile.build_time);
		item_tiles[x_tile][y_tile]->npc_dot_config.dot_stat_faction = faction;

		if (tile.light_specs.is_light_source == 1 && light_tiles[{x_tile, y_tile}] == NULL)
		{
			light_tiles[{x_tile, y_tile}] = new Light{ world_renderer, texture_array[SPRITESHEET_LIGHTS],x_tile*TILE_WIDTH,y_tile*TILE_HEIGHT,tile.light_specs.light_color,tile.light_specs.radius,tile.light_specs.brightness,tile.light_specs.attenuation };
		}

	}
}

bool World::Check_If_Can_Be_Placed(Tile_Template* item, int x_tile, int y_tile)
{
	bool can_be_placed = true;
	if (item->tile_or_item == 0)
	{
		if (item_tiles[x_tile][y_tile] != NULL)
		{
			can_be_placed = false;
		}
	}
	else if (item->tile_or_item == 1)
	{
		if (item_tiles[x_tile][y_tile] != NULL) can_be_placed = false, cout << "there's an item" << endl;
		//if (world_tiles[x_tile][y_tile]->multi_tile_config.tile_type != FLOOR_TILE_1 || world_tiles[x_tile][y_tile]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING && item->can_be_placed_in_vacuum == 0) can_be_placed = false, cout << "item isn't right type" << endl;
	}
	return can_be_placed;
}

bool World::Check_If_Scaffold_Can_Be_Placed(Tile_Template* item, int x_tile, int y_tile)
{
	bool can_be_placed = false;
	if (item->tile_or_item == 0) // trying to place a scaffold for a tile
	{
		if (world_tiles[x_tile][y_tile]->multi_tile_config.build_time >= 100 && item_tiles[x_tile][y_tile] == NULL) can_be_placed = true;
	}
	else if (item->tile_or_item == 1)
	{
		if (item_tiles[x_tile][y_tile] == NULL)
		{
			can_be_placed = true;
		}
	}
	return can_be_placed;
}

bool World::Tile_Is_Accessible(int x_tile, int y_tile)
{
	bool accessible = true;
	if (world_tiles[x_tile][y_tile]->multi_tile_config.is_collidable == 1) accessible = false;
	if (item_tiles[x_tile][y_tile] != NULL && item_tiles[x_tile][y_tile]->multi_tile_config.is_collidable == 1) accessible = false;
	return accessible;
}

Tile* World::Find_Accessible_Adjacent_Tile(Dot* tile)
{
	int x_tile = tile->getTileX();
	int y_tile = tile->getTileY();

	if (Tile_Is_Accessible(x_tile - 1, y_tile)) return world_tiles[x_tile - 1][y_tile];
	else if (Tile_Is_Accessible(x_tile + 1, y_tile)) return world_tiles[x_tile + 1][y_tile];
	else if (Tile_Is_Accessible(x_tile, y_tile - 1)) return world_tiles[x_tile][y_tile - 1];
	else if (Tile_Is_Accessible(x_tile, y_tile + 1)) return world_tiles[x_tile][y_tile + 1];
	else
	{
		cout << "found no accessible tiles" << endl;
		return world_tiles[x_tile][y_tile];
	}
}

Tile* World::Find_Random_Accessible_Surrounding_Tile(Dot* tile)
{
	int x_tile = tile->getTileX();
	int y_tile = tile->getTileY();
	
	for (int i = 0; i < 9; i++)
	{
		int x_offset = rand() % 4 - 2;
		int y_offset = rand() % 4 - 2;

		if (!(x_offset == 0 && y_offset == 0) && (Tile_Is_Accessible(x_tile - x_offset, y_tile - y_offset))) return world_tiles[x_tile - x_offset][y_tile - y_offset];
	}
	
	cout << "found no accessible random surrounding tile" << endl;
	return NULL;
	
}

Tile* World::Find_Accessible_Tile_Away_From_Dot(Dot* dot_to_move, Dot* dot_to_move_away_from)
{
	int x_tile = dot_to_move->getTileX();
	int y_tile = dot_to_move->getTileY();
	int x_difference = dot_to_move_away_from->getTileX() - x_tile;
	int y_difference = dot_to_move_away_from->getTileY() - y_tile;
	int direction = 0; // 0-7 clockwise from top left hand corner

	if (abs(x_difference) > abs(y_difference))
	{
		if (x_difference >= 0) direction = 7;
		else direction = 3;
	}
	else if (abs(y_difference) > abs(x_difference))
	{
		if (y_difference >= 0) direction = 1;
		else direction = 5;
	}
	else if (abs(x_difference) == abs(y_difference))
	{
		if (x_difference > 0 && y_difference > 0) direction = 0;
		else if (x_difference > 0 && y_difference < 0) direction = 6;
		else if (x_difference < 0 && y_difference > 0) direction = 2;
		else if (x_difference < 0 && y_difference < 0) direction = 4;
	}

	switch (direction)
	{
	case 0:
		return world_tiles[x_tile-1][y_tile-1];
		break;
	case 1:
		return world_tiles[x_tile ][y_tile - 1];
		break;
	case 2:
		return world_tiles[x_tile+1][y_tile - 1];
		break;
	case 3:
		return world_tiles[x_tile + 1][y_tile];
		break;
	case 4:
		return world_tiles[x_tile + 1][y_tile + 1];
		break;
	case 5: 
		return world_tiles[x_tile][y_tile + 1];
		break;
	case 6: 
		return world_tiles[x_tile-1][y_tile + 1];
		break;
	case 7: 
		return world_tiles[x_tile - 1][y_tile];
		break;
	}

	cout << "found no accessible tile away from dot" << endl;
	return NULL;
}

void World::Add_Scaffold_To_Tile(Tile_Template tile, int x_tile, int y_tile, int faction)
{
	if (tile.tile_or_item == 0 && world_tiles[x_tile][y_tile] != NULL)
	{
		world_tiles[x_tile][y_tile]->scaffold_on_tile = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile,0);
		world_tiles[x_tile][y_tile]->scaffold_on_tile->handle_smooth_tiles(VACUUM, VACUUM, VACUUM, VACUUM, VACUUM, VACUUM, VACUUM, VACUUM);
	}
	else if (tile.tile_or_item == 1)
	{
		if (item_tiles[x_tile][y_tile] != NULL) item_tiles[x_tile][y_tile]->scaffold_on_tile = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile);
		else
		{
			item_tiles[x_tile][y_tile] = new Tile(world_renderer, texture_array[Return_Tile_Template_By_Identifier(TILE_GENERIC_ITEM).spritesheet_num], x_tile, y_tile, Return_Tile_Template_By_Identifier(TILE_GENERIC_ITEM));
			item_tiles[x_tile][y_tile]->scaffold_on_tile = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile);
		}
	}
}

// Check Commands

bool World::is_tile_onscreen(int i, int p, Camera* camera)
{
	bool onscreen = true;
	if (i < ((camera->camera_box.x - TILE_WIDTH)/TILE_WIDTH))
	{
		onscreen = false;
	}
	if (i >((camera->camera_box.x + camera->camera_box.w + TILE_WIDTH)/TILE_WIDTH))
	{
		onscreen = false;
	}
	if (p < ((camera->camera_box.y - TILE_HEIGHT)/TILE_HEIGHT))
	{
		onscreen = false;
	}
	if (p >((camera->camera_box.y + camera->camera_box.h + TILE_HEIGHT))/TILE_HEIGHT)
	{
		onscreen = false;
	}
	return onscreen;
}

int World::Check_Tile_Type(int x_tile,int y_tile, bool tile_or_item)
{
	if (tile_or_item)
	{
		return world_tiles[x_tile][y_tile]->multi_tile_config.tile_type;
	}
	else if (tile_or_item == false && item_tiles[x_tile][y_tile] != NULL)
	{
		return item_tiles[x_tile][y_tile]->multi_tile_config.tile_type;
	}
}

Tile* World::Return_Tile_Neighbor(int x_tile, int y_tile, int neighbor, bool tile_or_item)
{
	if (x_tile != 0 && y_tile != 0)
	{
		// tile neighbors run clockwise from 1-8 with 1 in the top-left corner
		int x_offset = 0;
		int y_offset = 0;

		if (neighbor == 1 || neighbor == 8 || neighbor == 7) { x_offset = -1; }
		else if (neighbor == 2 || neighbor == 6) { x_offset = 0; }
		else if (neighbor == 3 || neighbor == 4 || neighbor == 5) { x_offset = 1; }

		if (neighbor == 1 || neighbor == 2 || neighbor == 3) { y_offset = -1; }
		else if (neighbor == 8 || neighbor == 4) { y_offset = 0; }
		else if (neighbor == 7 || neighbor == 6 || neighbor == 5) { y_offset = 1; }

		if (tile_or_item == false)
		{ 
			return world_tiles[x_tile + x_offset][y_tile + y_offset];
		}
		else if (tile_or_item == true && item_tiles[x_tile + x_offset][y_tile + y_offset] != NULL) 
		{ 
			return item_tiles[x_tile + x_offset][y_tile + y_offset];
		}
	}
	else { return 0;}
}

bool World::Is_Tile_Collidable(int x_tile, int y_tile)
{
	if (world_tiles[x_tile][y_tile]->multi_tile_config.is_collidable == 1 || (item_tiles[x_tile][y_tile] != NULL && item_tiles[x_tile][y_tile]->multi_tile_config.is_collidable == 1)) return true;
	else return false;
}

Tile_Init World::Save_Tile(int tile_x, int tile_y)
{
	Tile_Init tile_save;

	tile_save.tile_x_num = tile_x;
	tile_save.tile_y_num = tile_y;
	tile_save.world_tile_type = world_tiles[tile_x][tile_y]->multi_tile_config;

	if (item_tiles[tile_x][tile_y] != NULL)
	{
		tile_save.item_tile_type = item_tiles[tile_x][tile_y]->multi_tile_config;
		tile_save.item_on_tile = true;
	}
	return tile_save;
}

void World::Load_Tile(Tile_Init loaded_tile)
{
	Create_Tile(loaded_tile.world_tile_type, loaded_tile.tile_x_num, loaded_tile.tile_y_num);

	if (loaded_tile.item_on_tile)
	{
		Create_Tile(loaded_tile.item_tile_type, loaded_tile.tile_x_num, loaded_tile.tile_y_num);
	}
}

int World::get_num_scaffolds(bool tile_or_item)
{
	int count = 0;
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (tile_or_item)
			{
				if (world_tiles[i][p]->multi_tile_config.build_time < 100) count++;
			}
			else
			{
				if (item_tiles[i][p] != NULL && item_tiles[i][p]->multi_tile_config.build_time < 100) count++;
			}
		}
	}
	return count;
}

int World::get_number_of_tiles_of_type(Tile_Template tile_type)
{
	int count = 0;
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (tile_type.tile_or_item == 0)
			{
				if (world_tiles[i][p]->multi_tile_config.tile_name == tile_type.tile_name) count++;
			}
			else
			{
				if (item_tiles[i][p] != NULL && item_tiles[i][p]->multi_tile_config.tile_name == tile_type.tile_name) count++;
			}
		}
	}
	return count;
}

bool World::check_if_dot_in_radius_of_another_dot(Dot* dot_one, Dot* dot_two, int radius)
{
	int dot_one_x = dot_one->getTileX();
	int dot_one_y = dot_one->getTileY();
	int dot_two_x = dot_two->getTileX();
	int dot_two_y = dot_two->getTileY();

	int x_distance = abs(dot_two_x - dot_one_x);
	int y_distance = abs(dot_two_y - dot_one_y);

	if (x_distance*x_distance + y_distance*y_distance <= radius*radius) return true;
	else return false;
}

Dot* World::Find_tile_within_radius_of_dot(Dot* dot, int tile_type, int radius, bool tile_or_item)
{
	for (int p = max(0,dot->getTileY() - radius); p < min(dot->getTileY() + radius,TILE_NUM_Y); p++)
	{
		for (int i = max(0, dot->getTileX() - radius); i < min(dot->getTileX() + radius, TILE_NUM_X); i++)
		{
			if (tile_or_item == 0)
			{
				if (world_tiles[i][p]->multi_tile_config.tile_type = tile_type)
				{
					if (check_if_dot_in_radius_of_another_dot(dot, world_tiles[i][p],radius)) return world_tiles[i][p];
				}
			}
			else if (tile_or_item == 1)
			{

				if (item_tiles[i][p] != NULL && item_tiles[i][p]->multi_tile_config.tile_type == tile_type)
				{
					if (check_if_dot_in_radius_of_another_dot(dot, world_tiles[i][p], radius)) return item_tiles[i][p];
				}
			}
		}
	}
	return NULL;
}


// Fix Tile Orientation

void World::Update_Surrounding_Tiles(Tile* tile)
{
	int x_tile = tile->getTileX();
	int y_tile = tile->getTileY();
	
	// SMOOTH ALL THE TILES AROUND THE FLOOR TILE
	for (int i = 0; i < 9; i++)
	{
		Tile* neighbor_tile = Return_Tile_Neighbor(x_tile, y_tile, i, false);
		if (neighbor_tile != NULL && neighbor_tile->multi_tile_config.is_smooth == 1)
		{
			Fix_Smooth_Tile(neighbor_tile);
			for (int p = 0; p < 9; p++)
			{
				Tile* neighbor_tile_2 = Return_Tile_Neighbor(neighbor_tile->getTileX(), neighbor_tile->getTileY(), p, false);
				if (neighbor_tile_2 != NULL && neighbor_tile_2->multi_tile_config.is_smooth == 1)
				{
					Fix_Smooth_Tile(neighbor_tile_2);
				}
			}
		}
	}
}

void World::Fix_Smooth_Tile(Tile* tile)
{
	int i = tile->getTileX();
	int p = tile->getTileY();
	bool tile_or_item = tile->multi_tile_config.tile_or_item;
	int tile_type = tile->multi_tile_config.tile_type;
	
	int top_edge = VACUUM;
	int bottom_edge = VACUUM;
	int left_edge = VACUUM;
	int right_edge = VACUUM;

	int top_left_edge = VACUUM;
	int top_right_edge = VACUUM;
	int bottom_right_edge = VACUUM;
	int bottom_left_edge = VACUUM;

	left_edge = Return_Tile_Neighbor(i, p, 8, tile_or_item)->multi_tile_config.tile_type;
	top_edge = Return_Tile_Neighbor(i, p, 2, tile_or_item)->multi_tile_config.tile_type;
	right_edge = Return_Tile_Neighbor(i, p, 4, tile_or_item)->multi_tile_config.tile_type;
	bottom_edge = Return_Tile_Neighbor(i, p, 6, tile_or_item)->multi_tile_config.tile_type;

	top_left_edge = Return_Tile_Neighbor(i, p, 1, tile_or_item)->multi_tile_config.tile_type;
	top_right_edge = Return_Tile_Neighbor(i, p, 3, tile_or_item)->multi_tile_config.tile_type;
	bottom_right_edge = Return_Tile_Neighbor(i, p, 5, tile_or_item)->multi_tile_config.tile_type;
	bottom_left_edge = Return_Tile_Neighbor(i, p, 7, tile_or_item)->multi_tile_config.tile_type;

	if (tile_or_item && item_tiles[i][p]!= NULL) item_tiles[i][p]->handle_smooth_tiles(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
	else if (world_tiles[i][p] != NULL) world_tiles[i][p]->handle_smooth_tiles(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
}


// Tile Action Commands

void World::Remove_Tile(int i, int p, bool is_item)
{
	if (is_item & item_tiles[i][p] != NULL)
	{
		if (item_tiles[i][p]->multi_tile_config.tile_type == TILE_TYPE_LIGHT)
		{
			delete light_tiles[{i, p}];
			light_tiles.erase({i, p});
		}

		delete item_tiles[i][p];
		item_tiles[i][p] = NULL;

	}
	else if (world_tiles[i][p]->multi_tile_config.tile_type != VACUUM)
	{
		Create_Tile(Return_Tile_Template_By_Identifier(TILE_VACUUM), i, p);
		Update_Surrounding_Tiles(world_tiles[i][p]);
	}
}

void World::Grow_Frenzel(int i, int p, int current_frenzel_amount)
{
	int direction = rand() % 4;
	int x_offset = 0;
	int y_offset = 0;

	if (direction == 0) x_offset = 1, y_offset = 0;
	if (direction == 1) x_offset = 0, y_offset = -1;
	if (direction == 2) x_offset = 0, y_offset = 1;
	if (direction == 3) x_offset = -1, y_offset = 0;

	int adjacent_x = i + x_offset;
	int adjacent_y = p + y_offset;

	if (item_tiles[adjacent_x][adjacent_y] == NULL && world_tiles[adjacent_x][adjacent_y]->multi_tile_config.tile_type == VACUUM)
	{
		Create_Tile(Return_Tile_Template_By_Identifier(TILE_FRENZEL_1), adjacent_x, adjacent_y);
	}
}


// Aggregate Commands

World::oxygenation_check* World::Test_All_Tile_Neighbors_For_Leaks(Tile* tile, oxygenation_check* current_breach_check)
{
	int i = tile->getTileX(); 
	int p = tile->getTileY();
	
	tile->multi_tile_config.leak_check = 1;

	if (tile->multi_tile_config.tile_type == VACUUM)
	{
		current_breach_check->breach_status = true;
		return current_breach_check;
	}
	else 
	{
		tile->multi_tile_config.leak_check = 1;
		current_breach_check->tile_vector.push_back(tile);
		for (int q = 2; q < 9; q += 2)
		{
			Tile* neighboring_tile = Return_Tile_Neighbor(i, p, q, false);
			if (neighboring_tile == NULL || neighboring_tile->multi_tile_config.tile_type == VACUUM)
			{
				current_breach_check->breach_status = true;
				return current_breach_check;
			}
			else if ((neighboring_tile->multi_tile_config.tile_type == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || neighboring_tile->multi_tile_config.door_state == 1) && neighboring_tile->multi_tile_config.leak_check == 0)
			{	
				current_breach_check = Test_All_Tile_Neighbors_For_Leaks(neighboring_tile, current_breach_check);
			}
		}
	}
	return current_breach_check;
}

void World::Toggle_Room_Tiles_Oxygenated(vector<Tile*> vector_to_oxygenate, float oxygen_per_tile)
{
	for (int i = 0; i < vector_to_oxygenate.size(); i++)
	{
		vector_to_oxygenate[i]->multi_tile_config.is_oxygenated += oxygen_per_tile;
		vector_to_oxygenate[i]->multi_tile_config.leak_check = 0;
	}	
}

// Basic Functions

void World::Render(Camera* camera, int render_layer)
{
	for (int p = camera->camera_box.y / TILE_HEIGHT; p < (camera->camera_box.y + camera->camera_box.h) / TILE_HEIGHT + 1; ++p)
	{
		for (int i = camera->camera_box.x / TILE_WIDTH; i < (camera->camera_box.x + camera->camera_box.w) / TILE_WIDTH + 1; ++i)
		{
			if (world_tiles[i][p] != NULL)
			{
				world_tiles[i][p]->render(world_renderer, camera, render_layer);
			}
			if (item_tiles[i][p] != NULL)
			{
				item_tiles[i][p]->render(world_renderer, camera, render_layer);
			}	
		}
	}

	if (render_layer == RENDER_LIGHTS)
	{	
		SDL_SetRenderTarget(world_renderer, shadow_texture);
		SDL_SetRenderDrawColor(world_renderer, 100, 100, 100, 255);
		SDL_RenderFillRect(world_renderer, new SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT });

		for (std::map<Coordinate, Light*>::iterator it = light_tiles.begin(); it != light_tiles.end(); ++it)
		{
			it->second->render(world_renderer, camera);
		}
		
		SDL_SetRenderTarget(world_renderer, NULL);

		SDL_SetTextureBlendMode(shadow_texture, SDL_BLENDMODE_MOD);
		SDL_RenderCopyEx(world_renderer, shadow_texture, NULL,NULL,0,NULL,SDL_FLIP_NONE);
		
	}
}

void World::Free()
{
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (world_tiles[i][p] != NULL)
			{
				world_tiles[i][p]->free();
				delete world_tiles[i][p];
			}
			if (item_tiles[i][p] != NULL)
			{
				item_tiles[i][p]->free();
				delete item_tiles[i][p];
			}
		}
	}
}


// Overall Function Flow 

void World::Update_World()
{
}




#endif 