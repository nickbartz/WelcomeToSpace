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

class World {
public:

	// Basic Commands
	World(SDL_Renderer* gRenderer, LTexture textures[], SDL_Rect* tilesheet_clips[][BASIC_TILESHEET_HEIGHT], bool new_game);
	void Render(Camera* camera, int render_layer);
	void Free();

	struct tile_clip_coords
	{
		int clip_x;
		int clip_y;
	};
	
	// Create Commands
	void Create_Background();
	void Create_Test_Room(int x_start, int y_start);
	bool Check_If_Can_Be_Placed(Multi_Tile_Type* item, int x_tile, int y_tile);
	bool Check_If_Scaffold_Can_Be_Placed(Multi_Tile_Type* item, int x_tile, int y_tile);
	bool World::Tile_Is_Accessible(int x_tile, int y_tile);
	Tile* World::Find_Accessible_Adjacent_Tile(Dot* tile);
	void Create_Tile(Multi_Tile_Type tile, int x_tile, int y_tile);


	// Check Commands
	bool is_tile_onscreen(int i, int p, Camera* camera);
	int Check_Tile_Type(int x_tile, int y_tile, bool tile_or_item = true);
	Tile* Return_Tile_Neighbor(int x_tile, int y_tile, int neighbor, bool tile_or_item = true);
	int Return_Tile_Orientation(bool top_edge, bool bottom_edge, bool left_edge, bool right_edge);
	Tile_Init Save_Tile(int tile_x, int tile_y);
	void Load_Tile(Tile_Init loaded_tile);
	bool Is_Tile_Collidable(int x_tile, int y_tile);

	int get_num_scaffolds(bool tile_or_item);
	int get_number_of_tiles_of_type(Multi_Tile_Type tile_type);

	bool check_if_dot_in_radius_of_another_dot(Dot* dot_one, Dot* dot_two, int radius);
	Dot* Find_tile_within_radius_of_dot(Dot* dot, int tile_type, int radius, bool tile_or_item);

	// Fix Orientation
	void fix_wall_tile_orientation(int i, int p, int tile_type, bool tile_or_item);
	void Update_Surrounding_Tiles(Tile* tile);
	void Fix_Smooth_Tile(Tile* tile);

	// Tile Texture Clip Commands
	tile_clip_coords World::Return_Tile_Clip_Offset(int tile_orientation);
	void Update_Tile_Texture_Clip(int x_tile, int y_tile, int tile_clip_x, int tile_clip_y, bool tile_or_item);

	// Tile Specific Commands
	void Remove_Tile(int i, int p);
	void Grow_Frenzel(int i, int p, int current_frenzel_amount);

	// Aggregate Commands
	bool Test_All_Tile_Neighbors_For_Leaks(int i, int p, bool breached);
	void Toggle_Room_Tiles_Oxygenated(int i, int p, bool oxygenated);

	// Overall Flow Commands
	void Update_World();

	// Tile Array 
	Tile* world_tiles[TILE_NUM_X][TILE_NUM_Y];	
	Tile* item_tiles[TILE_NUM_X][TILE_NUM_Y];

private:
	LTexture* texture_array[NUM_TILESHEETS];
	SDL_Rect* basic_tilesheet_clips[BASIC_TILESHEET_WIDTH][BASIC_TILESHEET_HEIGHT];

	SDL_Renderer* world_renderer;
	SDL_Rect* current_clip;

	int delay_counter = 0;
	int tile_orientation = 0;

};

World::World(SDL_Renderer* gRenderer, LTexture textures[], SDL_Rect* tilesheet_clips[][BASIC_TILESHEET_HEIGHT], bool new_game)
{
	for (int p = 0; p < NUM_TILESHEETS; ++p) { texture_array[p] = &textures[p]; }

	world_renderer = gRenderer;

	Create_Background();
	Create_Test_Room(45,45);
}

void World::Create_Background()
{
	for (int p = 0; p < TILE_NUM_X; p++)
	{
		for (int i = 0; i < TILE_NUM_Y; i++)
		{
			if (rand() % 100 < 95) Create_Tile(Return_Tile_By_Name(TILE_VACUUM), i, p);
			else  Create_Tile(Return_Tile_By_Name(TILE_VACUUM_2), i, p);
		}
	}

}

void World::Create_Test_Room(int x_start, int y_start)
{
	string room =


		"F(B)FFFFFFF(X)FFF;\
		 FFFFFFFFFFF;\
		 FFFFFFFFFFF;\
		 FFFFFFFFFFF;\
		 FFFFFFFFFFFDFFF;\
		 FFFFFFFFFFF;\
		 FF(O)FFFFF(P)FFFF;\
		 FFFFFFF(Q)FFFF;";

	int column = x_start;
	int row = y_start;

	for (int i = 0; i < room.size(); i++)
	{
		if (room[i] == 'F') Create_Tile(Return_Tile_By_Name(TILE_CONSTRUCTION_TUBE_FLOOR_1), column, row);
		else if (room[i] == 'W') Create_Tile(Return_Tile_By_Name(TILE_WALL_TILE_2), column, row);
		else if (room[i] == 'D') Create_Tile(Return_Tile_By_Name(TILE_DOOR_1), column, row);
		else if (room[i] == 'S') Create_Tile(Return_Tile_By_Name(TILE_STORAGE_TILE_1), column, row);
		else if (room[i] == 'X') Create_Tile(Return_Tile_By_Name(TILE_LOCKER_1), column, row);
		else if (room[i] == 'O') Create_Tile(Return_Tile_By_Name(TILE_OXYGEN_MACHINE), column, row);
		else if (room[i] == 'P') Create_Tile(Return_Tile_By_Name(TILE_TABLE_1), column, row);
		else if (room[i] == 'Q') Create_Tile(Return_Tile_By_Name(TILE_CHAIR_1), column, row);
		else if (room[i] == 'B') Create_Tile(Return_Tile_By_Name(TILE_BED_1), column, row);
		else if (room[i] == '(') column = column -2;
		else if (room[i] == ')') column = column - 1;

		if (room[i] == ';')
		{
			row++;
			column = x_start;
		}
		else column++;
	}

}

/// Create Commands

bool World::Check_If_Can_Be_Placed(Multi_Tile_Type* item, int x_tile, int y_tile)
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

bool World::Check_If_Scaffold_Can_Be_Placed(Multi_Tile_Type* item, int x_tile, int y_tile)
{
	bool can_be_placed = false;
	if (item->tile_or_item == 0) // trying to place a scaffold for a tile
	{
		if (world_tiles[x_tile][y_tile]->multi_tile_config.built_percent >= 100 && item_tiles[x_tile][y_tile] == NULL) can_be_placed = true;
	}
	else if (item->tile_or_item == 1)
	{
		if (item_tiles[x_tile][y_tile] == NULL)
		{
			if (world_tiles[x_tile][y_tile]->multi_tile_config.tile_type == FLOOR_TILE_1)
			{
				can_be_placed = true;
			}
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

void World::Create_Tile(Multi_Tile_Type tile, int x_tile, int y_tile)
{
	if (tile.tile_name == TILE_CONSTRUCTION_TUBE_FLOOR_1)
	{
		if (world_tiles[x_tile][y_tile] != NULL && world_tiles[x_tile][y_tile]->multi_tile_config.tile_type != tile.tile_type)
		{
			delete world_tiles[x_tile][y_tile];
			world_tiles[x_tile][y_tile] = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile);
			world_tiles[x_tile][y_tile]->handle_floor_tiling();

			// IF THERE ARE NO WALLS AROUND THE FLOOR, MAKE THEM
			for (int i = 0; i < 9; i++)
			{
				Tile* neighbor_tile = Return_Tile_Neighbor(x_tile, y_tile, i, false);
				if (neighbor_tile != NULL && neighbor_tile->multi_tile_config.tile_type == VACUUM)
				{
					int neighbor_x = neighbor_tile->x_tile;
					int neighbor_y = neighbor_tile->y_tile;
					neighbor_tile->Tile::Tile(world_renderer, texture_array[tile.spritesheet_num], neighbor_x, neighbor_y, Return_Tile_By_Name(TILE_CONSTRUCTION_TUBE_WALL_1));
				}
			}

			// SMOOTH THE WALLS AROUND THE NEW TILE
			for (int i = 0; i < 9; i++)
			{
				Tile* neighbor_tile = Return_Tile_Neighbor(x_tile, y_tile, i, false);
				if (neighbor_tile != NULL && neighbor_tile->multi_tile_config.is_smooth == 1 && (neighbor_tile->multi_tile_config.tile_type == TILE_TYPE_CONSTRUCTION_TUBING_WALL || neighbor_tile->multi_tile_config.tile_type == TILE_TYPE_CONSTRUCTION_TUBING_DOOR))
				{
					Fix_Smooth_Tile(neighbor_tile);
					for (int p = 0; p < 9; p++)
					{
						Tile* neighbor_tile_2 = Return_Tile_Neighbor(neighbor_tile->getTileX(), neighbor_tile->getTileY(), p, false);
						if (neighbor_tile_2 != NULL && neighbor_tile_2->multi_tile_config.is_smooth == 1 && neighbor_tile_2->multi_tile_config.tile_type == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
						{
							Fix_Smooth_Tile(neighbor_tile_2);
						}
					}
				}
			}
			
		}
	}
	else
	{
		if (tile.tile_or_item == 0)
		{
			if (world_tiles[x_tile][y_tile] != NULL && world_tiles[x_tile][y_tile]->multi_tile_config.inventory_pointer.item_code != tile.inventory_pointer.item_code) delete world_tiles[x_tile][y_tile];
			world_tiles[x_tile][y_tile] = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile);
		}
		if (tile.tile_or_item == 1)
		{
			if (item_tiles[x_tile][y_tile] != NULL && item_tiles[x_tile][y_tile]->multi_tile_config.inventory_pointer.item_code != tile.inventory_pointer.item_code) delete item_tiles[x_tile][y_tile];
			item_tiles[x_tile][y_tile] = new Tile(world_renderer, texture_array[tile.spritesheet_num], x_tile, y_tile, tile);
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
				if (world_tiles[i][p]->multi_tile_config.built_percent < 100) count++;
			}
			else
			{
				if (item_tiles[i][p] != NULL && item_tiles[i][p]->multi_tile_config.built_percent < 100) count++;
			}
		}
	}
	return count;
}

int World::get_number_of_tiles_of_type(Multi_Tile_Type tile_type)
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

int World::Return_Tile_Orientation(bool top_edge, bool bottom_edge, bool left_edge, bool right_edge)
{
	tile_orientation = NO_EDGE;

	// Single
	if ((top_edge == true && bottom_edge == true) && right_edge == true && left_edge == false) tile_orientation = JUST_RIGHT_EDGE;
	if ((top_edge == true && bottom_edge == true) && right_edge == false && left_edge == true) tile_orientation = JUST_LEFT_EDGE;
	if ((right_edge == true && left_edge == true) && top_edge == true && bottom_edge == false) tile_orientation = JUST_TOP_EDGE;
	if ((right_edge == true && left_edge == true) && top_edge == false && bottom_edge == true) tile_orientation = JUST_BOTTOM_EDGE;

	if ((top_edge == true && bottom_edge == true) && right_edge == false && left_edge == false) tile_orientation = TOP_OR_BOTTOM_EDGE;
	if ((right_edge == true && left_edge == true) && top_edge == false && bottom_edge == false) tile_orientation = LEFT_OR_RIGHT_EDGE;

	// Corners
	if (top_edge == true && bottom_edge == false && right_edge == false && left_edge == true) tile_orientation = TOP_LEFT_CORNER;
	if (top_edge == true && bottom_edge == false && right_edge == true && left_edge == false) tile_orientation = TOP_RIGHT_CORNER;
	if (top_edge == false && bottom_edge == true && right_edge == false && left_edge == true) tile_orientation = BOTTOM_LEFT_CORNER;
	if (top_edge == false && bottom_edge == true && right_edge == true && left_edge == false) tile_orientation = BOTTOM_RIGHT_CORNER;

	//Complex 
	if (top_edge == false && bottom_edge == true && right_edge == false && left_edge == false) tile_orientation = UPSIDE_DOWN_T;
	if (top_edge == true && bottom_edge == false && right_edge == false && left_edge == false) tile_orientation = UPRIGHT_T;
	if (top_edge == false && bottom_edge == false && right_edge == false && left_edge == true) tile_orientation = T_BAR_ON_LEFT;
	if (top_edge == false && bottom_edge == false && right_edge == true && left_edge == false) tile_orientation = T_BAR_ON_RIGHT;

	if (top_edge == true && bottom_edge == true && right_edge == true && left_edge == true) tile_orientation = ALL_EDGE;

	return tile_orientation;
}

void World::fix_wall_tile_orientation(int i, int p, int tile_type, bool tile_or_item)
{
	bool top_edge = false;
	bool bottom_edge = false;
	bool left_edge = false;
	bool right_edge = false;


	if (Return_Tile_Neighbor(i, p, 8, tile_or_item)->multi_tile_config.tile_type != (tile_type) && Return_Tile_Neighbor(i, p, 8, true)->multi_tile_config.tile_type != DOOR_TILE)
	{
		left_edge = true;
	}
	if (Return_Tile_Neighbor(i, p, 2, tile_or_item)->multi_tile_config.tile_type != (tile_type) && Return_Tile_Neighbor(i, p, 2, true)->multi_tile_config.tile_type != DOOR_TILE)
	{
		top_edge = true;
	}
	if (Return_Tile_Neighbor(i, p, 4, tile_or_item)->multi_tile_config.tile_type != (tile_type) && Return_Tile_Neighbor(i, p, 4, true)->multi_tile_config.tile_type != DOOR_TILE)
	{
		right_edge = true;
	}
	if (Return_Tile_Neighbor(i, p, 6, tile_or_item)->multi_tile_config.tile_type != (tile_type) && Return_Tile_Neighbor(i, p, 6, true)->multi_tile_config.tile_type != DOOR_TILE)
	{
		bottom_edge = true;
	}

	tile_orientation = Return_Tile_Orientation(top_edge, bottom_edge, left_edge, right_edge);
	tile_clip_coords clip_coords = Return_Tile_Clip_Offset(tile_orientation);
	Update_Tile_Texture_Clip(i, p, clip_coords.clip_x, clip_coords.clip_y, tile_or_item);
}

World::tile_clip_coords World::Return_Tile_Clip_Offset(int tile_orientation)
{
	tile_clip_coords clips;

	if (tile_orientation == NO_EDGE) clips.clip_x = 1, clips.clip_y = 1;
	if (tile_orientation == ALL_EDGE) clips.clip_x = 0, clips.clip_y = 0;

	if (tile_orientation == JUST_LEFT_EDGE) clips.clip_x = 0, clips.clip_y = 2;
	if (tile_orientation == JUST_RIGHT_EDGE) clips.clip_x = 0, clips.clip_y = 1;
	if (tile_orientation == JUST_TOP_EDGE) clips.clip_x = 2, clips.clip_y = 0;
	if (tile_orientation == JUST_BOTTOM_EDGE) clips.clip_x = 1, clips.clip_y = 0;
	
	if (tile_orientation == TOP_OR_BOTTOM_EDGE) clips.clip_x = 0, clips.clip_y = -1;
	if (tile_orientation == LEFT_OR_RIGHT_EDGE) clips.clip_x = -1, clips.clip_y = 0;

	if (tile_orientation == TOP_LEFT_CORNER) clips.clip_x = -1, clips.clip_y = -1;
	if (tile_orientation == TOP_RIGHT_CORNER) clips.clip_x = 2, clips.clip_y = -1;
	if (tile_orientation == BOTTOM_LEFT_CORNER) clips.clip_x = -1, clips.clip_y = 2;
	if (tile_orientation == BOTTOM_RIGHT_CORNER) clips.clip_x = 2, clips.clip_y = 2;

	if (tile_orientation == UPSIDE_DOWN_T)  clips.clip_x = 1, clips.clip_y = 2;
	if (tile_orientation == UPRIGHT_T)  clips.clip_x = 1, clips.clip_y = -1;
	if (tile_orientation == T_BAR_ON_LEFT)  clips.clip_x = -1, clips.clip_y = 1;
	if (tile_orientation == T_BAR_ON_RIGHT)  clips.clip_x = 2, clips.clip_y = 1;

	return clips;
}

void World::Update_Tile_Texture_Clip(int x_tile, int y_tile, int tile_clip_x, int tile_clip_y, bool tile_or_item)
{
	if (tile_or_item == false)
	{
		world_tiles[x_tile][y_tile]->update_texture_clip(world_tiles[x_tile][y_tile]->multi_tile_config.sprite_specs.sprite_column + tile_clip_x, world_tiles[x_tile][y_tile]->multi_tile_config.sprite_specs.sprite_row + tile_clip_y);
	}
	else if (tile_or_item == true)
	{
		item_tiles[x_tile][y_tile]->update_texture_clip(item_tiles[x_tile][y_tile]->multi_tile_config.sprite_specs.sprite_column + tile_clip_x, item_tiles[x_tile][y_tile]->multi_tile_config.sprite_specs.sprite_row + tile_clip_y);
	}
}

void World::Update_Surrounding_Tiles(Tile* tile)
{
	int i = tile->getTileX();
	int p = tile->getTileY();

	for (int x = 0; x < 9; x++)
	{
		Tile* neighbor_tile = Return_Tile_Neighbor(i, p, x, false);
		if (neighbor_tile->multi_tile_config.tile_type == TILE_TYPE_CONSTRUCTION_TUBING_WALL) Fix_Smooth_Tile(neighbor_tile);
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

void World::Remove_Tile(int i, int p)
{
	if (item_tiles[i][p] != NULL && item_tiles[i][p]->multi_tile_config.tile_type != 4)
	{
		delete item_tiles[i][p];
		item_tiles[i][p] = NULL;
	}
	if (world_tiles[i][p]->multi_tile_config.tile_type != VACUUM)
	{
		if (world_tiles[i][p]->multi_tile_config.tile_type == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
		{
			Create_Tile(Return_Tile_By_Name(TILE_VACUUM), i, p);
			Update_Surrounding_Tiles(world_tiles[i][p]);
		}
		else Create_Tile(Return_Tile_By_Name(TILE_VACUUM), i, p);
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
		Create_Tile(Return_Tile_By_Name(TILE_FRENZEL_1), adjacent_x, adjacent_y);
	}
}

// Aggregate Commands

bool World::Test_All_Tile_Neighbors_For_Leaks(int i, int p, bool breached)
{
	bool current_breach_status = breached;
	if (world_tiles[i][p]->multi_tile_config.tile_type == VACUUM)
	{
		current_breach_status = true;
		return current_breach_status;
	}
	else 
	{
		world_tiles[i][p]->multi_tile_config.leak_check = 1;
		for (int q = 1; q < 9; q++)
		{
			Tile* neighboring_tile = Return_Tile_Neighbor(i, p, q, false);
			Tile* neighboring_item = Return_Tile_Neighbor(i, p, q, true);
			if (neighboring_tile->multi_tile_config.tile_type == VACUUM && neighboring_item != NULL && neighboring_item->multi_tile_config.tile_type != WALL_TILE && neighboring_item->multi_tile_config.tile_type != DOOR_TILE)
			{
				current_breach_status = true;
				return current_breach_status;
			}
			else if (neighboring_item != NULL && neighboring_item->multi_tile_config.tile_type != WALL_TILE && neighboring_tile->multi_tile_config.tile_type == FLOOR_TILE_1 && neighboring_tile->multi_tile_config.leak_check == 0)
			{
				if (neighboring_item != NULL && neighboring_item->multi_tile_config.door_state != 0)
				{
				}
				else 
				{
					current_breach_status = Test_All_Tile_Neighbors_For_Leaks(neighboring_tile->getTileX(), neighboring_tile->getTileY(), current_breach_status);
				}
			}
		}
	}
	return current_breach_status;
}

void World::Toggle_Room_Tiles_Oxygenated(int i, int p, bool oxygenate)
{
	for (int q = 1; q < 9; ++q)
	{
		Tile* neighboring_item = Return_Tile_Neighbor(i, p, q, true);
		Tile* neighboring_tile = Return_Tile_Neighbor(i, p, q, false);
		if (oxygenate == true)
		{
			if (neighboring_tile->multi_tile_config.tile_type == FLOOR_TILE_1 && neighboring_tile->multi_tile_config.oxygenation_check == 0)
			{
				if (!(neighboring_item != NULL
					&& neighboring_item->multi_tile_config.door_state == 2))
				{
					neighboring_tile->multi_tile_config.oxygenation_check = 1;
					neighboring_tile->multi_tile_config.is_oxygenated = 1;
					Toggle_Room_Tiles_Oxygenated(neighboring_tile->getTileX(), neighboring_tile->getTileY(), true);
				}
			}
		}
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