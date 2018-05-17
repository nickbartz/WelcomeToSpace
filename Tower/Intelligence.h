#pragma once

class Intelligence
{
public: 
	Intelligence(World* input_world, SDL_Renderer* world_renderer, Camera* world_camera , LTexture textures[], bool new_game);

	// CONSOLE COMMANDS
	void Push_Alert(Dot* dot, string alert_text);
	void Erase_Alerts(Dot* dot);

	// INPUT COMMANDS
	void Handle_Non_Console_Click(int current_action, int x_tile, int y_tile, int x, int y, int inventory_item_code = INVENTORY_EMPTY_SLOT);
	void Handle_Non_Console_Click_And_Hold(int current_action, int x_tile, int y_tile, int x, int y, int inventory_item_code = INVENTORY_EMPTY_SLOT);
	void Handle_Non_Console_Unclick(int current_action, int x_tile, int y_tile, int x, int y, int inventory_item_code = INVENTORY_EMPTY_SLOT);
	void Handle_Keyboard_Input(SDL_Event* e);
	void Test_Cursor_Position(int mouse_pos_x, int mouse_pos_y, int tile_x, int tile_y);
	Dot* Return_Clicked_Dot(int mouse_pos_x, int mouse_pos_y);

	// HELPER COMMANDS
	double get_angle_between_two_points(int x_origin, int y_origin, int x_target, int y_target);
	int rotate_point_around_point(int x_position, int y_position, int x_center, int y_center, double angle, bool x_or_y);
	bool rects_are_equal(SDL_Rect* rect_one, SDL_Rect* rect_two);
	int return_point_not_onscreen(bool x_or_y, int range_start = 0, int range_end = LEVEL_WIDTH);
	int Check_if_Point_Inside_Rect(int point_x, int point_y, SDL_Rect target_rect);
	int Check_Distance_Between_Dots(Dot* dot_one, Dot* dot_two);
	int Check_Faction_Score_Between_Dots(Dot* dot_one, Dot* dot_two);


	// DOT COMMANDS
	Tile* get_current_dot_tile(Dot* dot);
	bool check_if_dot_is_on_tile(Dot* dot, Dot* tile);
	bool check_if_dots_adjacent(Dot* dot_one, Dot* dot_two);
	bool check_if_dot_and_tile_are_adjacent(Dot* dot, Dot* tile);


	// ENEMY SHIP COMMANDS
	void Spawn_Enemy_Ships();
	void Update_Enemy_Ship_AI(Ship_Dot* enemy_ship);
	void Update_All_Enemy_Ships_AI();

	// Dot inventory commands
	bool dot_has_item_in_inventory(Dot* dot, int inventory_item_code);
	void Add_Item_To_Dot_Inventory(Dot* dot, int inventory_item_code, int quantity);
	void Remove_Item_From_Dot_Inventory(Dot* dot, int inventory_item_code, int quantity_to_remove);
	void Remove_Building_Items_From_Dot_Inventory(Dot* dot, Multi_Tile_Type built_item);
	void Dot_Drop_Inventory_Item(Dot* dot, int x_pos, int y_pos, int inventory_item_code, int quantity_dropped);
	void Dot_Drop_Inventory(Dot* dot, int x_pos, int y_pos);
	void Add_Container_Items_to_Dot_Inventory(Dot* dot, Dot* container);
	void Delete_Container_by_Pointer(Dot* container_pointer);
	void Dot_Give_Inventory_To_Another_Dot(Dot* dot, Dot* second_dot, int inventory_item_code, int Quantity);
	void Dot_Craft_Item(Dot* dot, int inventory_item_code, int quantity);

	// NPD AI
	void Dot_Choose_Job(NPC_Dot* npc_dot);
	void Manage_Dot_Health(NPC_Dot* dot);
	void Manage_Dot_Equipment(Dot* dot);
	void Manage_Dot_Combat(NPC_Dot* dot);
	void Manage_Priority_Changes(Dot* dot, int dot_priority_name);
	void Respond_To_Dot_Priority_Alarm_Level(NPC_Dot* dot, int dot_priority_name);
	void Respond_To_Dot_Priority_Max_Level(NPC_Dot* dot, int dot_priority_name);
	void Manage_Priority_Delays(Dot* dot, int dot_priority_name);

	void update_player_dot_ai(NPC_Dot* dot);
	void Update_NPD_AI();
	void Process_Most_Recent_Dot_Goal(Dot* dot);
	bool Check_Dot_Path_is_Oxygenated(Dot* dot);
	void set_dot_target(int new_target_x, int new_target_y, Dot* dot);
	void set_dot_tile_target(int new_target_tile_x, int new_target_tile_y, Dot* dot);
	bool Update_Dot_Path(Dot* dot, int target_tile_x, int target_tile_y, bool adjacent = false);
	void Set_Dot_Target_to_Next_Node_on_Path(Dot* dot);

	// DOT SEARCH FUNCTIONS
	vector<vector<Dot*>> Return_Array_of_Pointers_To_All_Dot_Vectors();
	vector<Dot*> return_appropriate_dot_vector(int dot_vector_type);
	vector<Tile*> return_vector_of_all_tiles();
	vector<Dot*> return_array_of_dots_within_radius(Dot* dot, int radius);
	vector<Dot*> return_array_of_tiles_by_type_or_name(bool type_or_name, int search_number);

	Dot* return_nearest_dot_with_faction(Dot* searching_dot, int faction, int search_distance);
	Dot* return_nearest_dot_by_type(Dot* dot, int dot_type, Multi_Tile_Type tile_type = null_tile);
	Dot* return_nearest_container_with_item(Dot* dot, int item_type);
	Dot* return_nearest_container_with_item_type(Dot* dot, int item_type);
	Dot* return_nearest_container_or_storage_tile_with_item(Dot*, int item_type);
	Dot* return_nearest_container_or_storage_tile_with_item_type(Dot* dot, int item_type);
	Dot* return_nearest_tile_by_type_or_name(Dot* dot, bool type_or_name, int search_number);
	vector<Dot*> return_chair_and_table_combo(Dot* dot);
	Dot* Intelligence::return_nearest_oxygenated_tile(Dot* dot);

	// DOT JOB COMMANDS
	float Calculate_Total_Job_Priority();
	bool check_dot_pointer(Dot* npc_dot, Dot* pointer_to_check);
	bool check_dot_type(Dot* dot, int focus_type_category, int focus_type_specific, bool tile_built);
	void change_dot_focus(Dot* dot, Dot* new_focus, int task_type);
	int Number_of_Containers_Not_in_Storage();
	int Amount_of_Inventory_Item_in_Storage(int search_item);

	// ASTEROID COMMANDS
	void Distribute_Asteroids();
	void Spawn_Asteroids();
	void Despawn_Asteroids();
	int Get_Num_Asteroids();
	Asteroid* Get_Asteroid_At_Coord(int x_pos, int y_pos);
	void Update_Asteroid_AI();
	void Create_Asteroid_Mining_Animation(Dot* mining_dot, int t_x, int t_y);

	// CONTAINER COMMANDS
	void Update_Container_AI();

	// PROJECTILE COMMANDS
	void Create_Bolt(int owners_faction, int target_x, int target_y, int sprite_row, int start_location_x, int start_location_y, double speed, bool is_explosion = false);
	void Fire_Weapon(Dot* firing_dot, Dot* target_dot, int sprite_row, double speed, bool specific_point = false, int target_x = 0, int target_y = 0);
	void Fire_Mining_Laser(Dot* firing_dot, Dot* target_dot, bool point_not_dot_target, int target_x, int target_y);
	void Stop_Firing_Mining_Laser(Dot* firing_dot);
	void update_bolt_ai();

	// SCAFFOLDING COMMANDS
	void Create_Scaffolding(Multi_Tile_Type* tile_type, int x_tile, int y_tile);
	void Update_World_Ai();
	void Check_If_Tile_Has_Needs(Tile* tile);
	void Delete_Tile(Dot* tile_to_remove);

	// PHYSICS COMMANDS
	void move_dot(Dot* dot, int* mVelX, int* mVelY);
	void move_object_without_collision(SDL_Rect* object_rect, float mVelX, float mVelY);
	bool check_dot_collision(SDL_Rect* first_object, SDL_Rect* second_object);
	bool check_global_collisions(Dot* dot);
	void test_dot_for_damage(Dot* test_dot, SDL_Rect* object_doing_damage, int damage_radius, int weapon_damage);
	void damage_nearby_dots(Dot* dot_doing_damage, int damage_radius, int weapon_damage);
	void test_dots_for_focii();

	// MAIN COMMANDS
	void Advance_Time(float avgFPS);
	void free();
	void render();

	// TEST OBJECTS
	NPC_Dot* player_dot;
	NPC_Dot* lifepod;

	int delay = 0;

	float total_job_priority = 0.0;
	int current_frenzel_amount = 1;

private: 

	SDL_Renderer* gRenderer;
	Camera* camera;
	World* world;
	Path_Field* iField;

	LTexture* texture_array[NUM_TILESHEETS];
	LTexture* dot_spritesheet_array[6];

	LTexture* bolt_sprites;
	LTexture* dot_spritesheet;
	LTexture* asteroid_spritesheet;
	LTexture* enemy_ship_spritesheet;
	LTexture* container_spritesheet;
	LTexture* inventory_spritesheet;
	LTexture* standard_tilesheet;

	vector<string> console_alerts;

	vector<Bolt*> bolt_array;
	vector<Asteroid*> asteroid_array;
	vector<Ship_Dot*> enemy_ship_array;
	vector<Container*> container_array;
	vector<NPC_Dot*> npc_dot_array;
	vector<Dot_Job> dot_job_array;
	vector<dot_faction_relationship> faction_relationships;

	int max_enemy_ships = 10;

	bool ai_debug = false;
	bool job_debug = false;
	bool player_dot_debug = false;
};

Intelligence::Intelligence(World* input_world, SDL_Renderer* world_renderer, Camera* world_camera, LTexture textures[], bool new_game)
{
	for (int p = 0; p < NUM_TILESHEETS; ++p) { texture_array[p] = &textures[p];}

	dot_spritesheet_array[0] = texture_array[DOT_SPRITESHEET_LEGS];
	dot_spritesheet_array[1] = texture_array[DOT_SPRITESHEET_ARMS];
	dot_spritesheet_array[2] = texture_array[DOT_SPRITESHEET_TORSOS];
	dot_spritesheet_array[3] = texture_array[DOT_SPRITESHEET_HEADS];
	dot_spritesheet_array[4] = texture_array[DOT_SPRITESHEET_EQUIPMENT];
	dot_spritesheet_array[5] = texture_array[DOT_SPRITESHEET_MISC];

	bolt_sprites = texture_array[BOLT_SPRITES];
	dot_spritesheet = texture_array[DOT_SPRITESHEET];
	asteroid_spritesheet = texture_array[ASTEROID_SPRITESHEET];
	enemy_ship_spritesheet = texture_array[ENEMY_SHIP_SPRITESHEET];
	container_spritesheet = texture_array[CONTAINER_SPRITESHEET];
	inventory_spritesheet = texture_array[INVENTORY_SPRITESHEET];
	standard_tilesheet = texture_array[TILESHEET];

	camera = world_camera;

	gRenderer = world_renderer;

	world = input_world;
	iField = new Path_Field(world);

	faction_relationships.push_back({ DOT_FACTION_PLAYER,DOT_FACTION_ENEMY,-1 });
	faction_relationships.push_back({ DOT_FACTION_ENEMY,DOT_FACTION_PLAYER,-1 });

	player_dot = new NPC_Dot(gRenderer, dot_spritesheet_array, 150 * TILE_WIDTH, 150 * TILE_HEIGHT, { 0,0,0,0 });
	player_dot->dot_config[DOT_TYPE] = DOT_PLAYER;
	player_dot->npc_dot_config.dot_stat_speed = 10;
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_SPACESUIT_1, 1);
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_OXYGEN_TANK, 1);
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_MINING_LASER_1, 1);
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_LASER_PISTOL_1, 1);
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_LOCKER_1, 1);
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_FRENZEL_1, 1);
	Add_Item_To_Dot_Inventory(player_dot, INVENTORY_EMITTER_1, 1);
	player_dot->npc_dot_config.dot_equipment_config.Spacesuit = { INVENTORY_SPACESUIT_1,1 };
	player_dot->npc_dot_config.dot_equipment_config.Weapon = { INVENTORY_LASER_PISTOL_1,1 };
	player_dot->npc_dot_config.dot_equipment_config.Mining_Laser = { INVENTORY_MINING_LASER_1,1 };
	player_dot->Check_Craftable_Items();

	lifepod = new NPC_Dot(gRenderer, dot_spritesheet_array, 155 * TILE_WIDTH, 155 * TILE_HEIGHT, { 0,0,0,0,1 });
	lifepod->npc_dot_config.dot_equipment_config.Spacesuit.item_number = 1;
	lifepod->npc_dot_config.bounce = 1;
	lifepod->shadow_offset = 5;

	world->Create_Tile(Return_Tile_By_Name(TILE_LOCKER_1), 151, 150);

	for (int i = 0; i < 5; i++)
	{
		int random_head = rand() % 2;
		npc_dot_array.push_back(new NPC_Dot(gRenderer, dot_spritesheet_array, (154 + i) * TILE_WIDTH, 151 * TILE_HEIGHT, { 0,0,0,1,0 }));
		Add_Item_To_Dot_Inventory(npc_dot_array.back(), INVENTORY_SPACESUIT_1, 1);
		npc_dot_array.back()->npc_dot_config.dot_equipment_config.Spacesuit = { INVENTORY_SPACESUIT_1, 1 };
		npc_dot_array.back()->npc_dot_config.dot_equipment_config.Weapon = { INVENTORY_LASER_PISTOL_1,1 };
		npc_dot_array.back()->npc_dot_config.current_storage_tile = return_nearest_tile_by_type_or_name(npc_dot_array.back(), false, TILE_TYPE_STORAGE_TILE);
	}

	//for (int i = 0; i < 5; i++)
	//{
	//	NPC_Dot* enemy_dot = new NPC_Dot(gRenderer, dot_spritesheet_array, (150+i) * TILE_WIDTH, 145 * TILE_HEIGHT, { 0,0,0,0,0 });
	//	enemy_dot->npc_dot_config.dot_equipment_config.Spacesuit = { INVENTORY_SPACESUIT_1,1 };
	//	enemy_dot->npc_dot_config.dot_equipment_config.Weapon = { INVENTORY_LASER_PISTOL_1,1 };
	//	enemy_dot->npc_dot_config.dot_stat_faction = DOT_FACTION_ENEMY;
	//	npc_dot_array.push_back(enemy_dot);
	//}



}

// CONSOLE_COMMANDS

void Intelligence::Push_Alert(Dot* dot, string alert_text)
{
	dot->dot_alerts.push_back({ alert_text,0 });

	int row_max = 20;
	if (dot->dot_alerts.size() >= row_max)
	{
		dot->dot_alerts.erase(dot->dot_alerts.begin());
	}
}

void Intelligence::Erase_Alerts(Dot* dot)
{
	int row_max = 20; 

	if (dot->dot_alerts.size() >= row_max)
	{
		dot->dot_alerts.erase(dot->dot_alerts.begin());
	}
}

// INPUT COMMANDS

void Intelligence::Handle_Non_Console_Click(int current_action, int x_tile, int y_tile, int x, int y, int inventory_item_code)
{
	switch (current_action)
	{
	case BUTTON_ACTION_ACTION:
		break;
	case BUTTON_ACTION_REMOVE_TILE:world->Remove_Tile(x_tile, y_tile);
		break;
	case BUTTON_ACTION_ATTACK:
		Fire_Weapon(player_dot,world->world_tiles[x_tile][y_tile], 0, 10, true, x, y);
		break;
	case BUTTON_ACTION_CREATE_ITEM:
	case BUTTON_ACTION_PLACE_ITEM:
		if (dot_has_item_in_inventory(player_dot, inventory_item_code) && world->Check_If_Can_Be_Placed(&Return_Tile_By_Inventory_Item(inventory_item_code), x_tile, y_tile))
		{
			world->Create_Tile(Return_Tile_By_Inventory_Item(inventory_item_code), x_tile, y_tile);
			Remove_Item_From_Dot_Inventory(player_dot, inventory_item_code, 1);
		}

		break;
	case BUTTON_ACTION_PLACE_SCAFFOLD:
		if (world->Check_If_Scaffold_Can_Be_Placed(&Return_Tile_By_Inventory_Item(inventory_item_code), x_tile, y_tile))
		{
			Create_Scaffolding(&Return_Tile_By_Inventory_Item(inventory_item_code), x_tile, y_tile);
		}
		break;
	}
}

void Intelligence::Handle_Non_Console_Click_And_Hold(int current_action, int x_tile, int y_tile, int x, int y, int inventory_item_code)
{
	switch (current_action)
	{
	case BUTTON_ACTION_ATTACK:
		if (player_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].current_level == 0) Fire_Weapon(player_dot, world->world_tiles[x_tile][y_tile], 0, 20, true, x, y);
		break;
	case BUTTON_ACTION_MINING_LASER:
		Fire_Mining_Laser(player_dot, world->world_tiles[x_tile][y_tile], true, x, y);
		break;
	}
}

void Intelligence::Handle_Non_Console_Unclick(int current_action, int x_tile, int y_tile, int x, int y, int inventory_item_code)
{
	switch (current_action)
	{
	case BUTTON_ACTION_MINING_LASER:
		Stop_Firing_Mining_Laser(player_dot);
		break;
	}
}

void Intelligence::Handle_Keyboard_Input(SDL_Event* e)
{
	if (e->type == (SDL_KEYDOWN))
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_a:
			player_dot->set_player_velocity(true, -5);
			break;
		case SDLK_d:
			player_dot->set_player_velocity(true, 5);
			break;
		case SDLK_w:
			player_dot->set_player_velocity(false, -5);
			break;
		case SDLK_s:
			player_dot->set_player_velocity(false, 5);
			break;
		}
	}
	else if (e->type == (SDL_KEYUP))
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_a:
			player_dot->set_player_velocity(true, 0);
			break;
		case SDLK_d:
			player_dot->set_player_velocity(true, 0);
			break;
		case SDLK_w:
			player_dot->set_player_velocity(false, 0);
			break;
		case SDLK_s:
			player_dot->set_player_velocity(false, 0);
			break;
		}
	}
}

void Intelligence::Test_Cursor_Position(int mouse_pos_x, int mouse_pos_y, int tile_x, int tile_y)
{
	bool found_dot = false;
	for (int i = 0; i < npc_dot_array.size(); i++)
	{
		if (Check_if_Point_Inside_Rect(mouse_pos_x, mouse_pos_y, npc_dot_array[i]->dot_rect)) 
		{
			npc_dot_array[i]->toggle_highlight(true);
			found_dot = true;
		}
	}

	if (found_dot == false)
	{
		if (world->item_tiles[tile_x][tile_y] != NULL) world->item_tiles[tile_x][tile_y]->toggle_highlight(true);
		else if (world->world_tiles[tile_x][tile_y] != NULL && world->world_tiles[tile_x][tile_y]->multi_tile_config.tile_type != VACUUM) world->world_tiles[tile_x][tile_y]->toggle_highlight(true);
	}
}

Dot* Intelligence::Return_Clicked_Dot(int mouse_pos_x, int mouse_pos_y)
{
	vector<vector <Dot*>> search_vector = Return_Array_of_Pointers_To_All_Dot_Vectors();
	int current_x_tile = mouse_pos_x;
	int current_y_tile = mouse_pos_y;

	int closest_x = TILE_NUM_X + 1;
	int closest_y = TILE_NUM_Y + 1;

	Dot* final_dot = NULL;

	for (int x = 0; x < search_vector.size(); x++)
	{
		for (int i = 0; i < search_vector[x].size(); i++)
		{
			Dot* cur_dot = search_vector[x][i];
			unsigned int dist_x = abs(cur_dot->getCenterPosX() - current_x_tile);
			unsigned int dist_y = abs(cur_dot->getCenterPosY() - current_y_tile);

			if ((dist_x + dist_y) < (closest_x + closest_y))
			{
				final_dot = search_vector[x][i];
				closest_x = dist_x;
				closest_y = dist_y;
			}
		}
	}

	for (int i = 0; i < search_vector.size(); i++) search_vector[i].clear();

	return final_dot;
}


// HELPER FUNCTIONS

double Intelligence::get_angle_between_two_points(int x_origin, int y_origin, int x_target, int y_target)
{
	float vector_x = x_target - x_origin;
	float vector_y = y_target - y_origin;
	double angle = atan(vector_y / vector_x)*(180.0 / 3.141592653589793238463);

	if (vector_x >= 0 && vector_y >= 0) angle = -90 + angle;
	else if (vector_x < 0 && vector_y >= 0) angle = 90 + angle;
	else if (vector_x < 0 && vector_y < 0) angle = 90 + angle;
	else if (vector_x >= 0 && vector_y < 0) angle = -90 + angle;
	
	return angle + 180;
}

int Intelligence::rotate_point_around_point(int x_position, int y_position, int x_center, int y_center, double angle, bool x_or_y)
{
	double angle_in_radians = angle * (M_PI / 180);

	int location_1_x = x_position - x_center;
	int location_1_y = y_position - y_center;

	int new_location_1_x = location_1_x*cos(angle_in_radians) - location_1_y*sin(angle_in_radians) + (x_center);
	int new_location_1_y = location_1_y*cos(angle_in_radians) + location_1_x*sin(angle_in_radians) + (y_center);

	if (x_or_y) return new_location_1_x;
	else return new_location_1_y;
}

bool Intelligence::rects_are_equal(SDL_Rect* rect_one, SDL_Rect* rect_two)
{
	if (rect_one->x == rect_two->x && rect_one->y == rect_two->y && rect_one->w == rect_two->w && rect_one->h == rect_two->h) return true;
	else return false;
}

int Intelligence::return_point_not_onscreen(bool x_or_y, int range_start, int range_end)
{
	if (x_or_y)
	{
		int point_x = (rand() % (range_end - range_start)) + range_start;
		if (point_x >= camera->camera_box.x && point_x <= (camera->camera_box.x + camera->camera_box.w))
		{
			return Intelligence::return_point_not_onscreen(x_or_y, range_start, range_end);
		}
		else return point_x;
	}
	else
	{
		int point_y = (rand() % (range_end - range_start)) + range_start;
		if (point_y >= camera->camera_box.y && point_y <= (camera->camera_box.y + camera->camera_box.h))
		{
			return Intelligence::return_point_not_onscreen(x_or_y, range_start, range_end);
		}
		else return point_y;
	}
}

int Intelligence::Check_if_Point_Inside_Rect(int point_x, int point_y, SDL_Rect target_rect)
{
	bool in_rect = true;

	if (point_x < target_rect.x || point_x >(target_rect.x + target_rect.w))
	{
		in_rect = false;
	}
	if (point_y < target_rect.y || point_y >(target_rect.y + target_rect.h))
	{
		in_rect = false;
	}
	return in_rect;
}

int Intelligence::Check_Distance_Between_Dots(Dot* dot_one, Dot* dot_two)
{
	int distance;

	int y_distance = abs(dot_two->getCenterPosY() - dot_one->getCenterPosY());
	int x_distance = abs(dot_two->getCenterPosX() - dot_one->getCenterPosX());

	distance = sqrt(pow(y_distance,2) + pow(x_distance,2));
	return distance;
}

int Intelligence::Check_Faction_Score_Between_Dots(Dot* dot_one, Dot* dot_two)
{
	if (dot_one->npc_dot_config.dot_stat_faction == dot_two->npc_dot_config.dot_stat_faction)
	{
		return 0;
	}
	for (int i = 0; i < faction_relationships.size(); i++)
	{
		if (faction_relationships[i].faction_one == dot_one->npc_dot_config.dot_stat_faction && faction_relationships[i].faction_two == dot_two->npc_dot_config.dot_stat_faction)
		{
			return faction_relationships[i].relationship_index;
		}
	}
	return 0;
}



// DOT COMMANDS

Tile* Intelligence::get_current_dot_tile(Dot* dot)
{
	int current_tile_x = dot->dot_rect.x / TILE_WIDTH;
	int current_tile_y = dot->dot_rect.y / TILE_HEIGHT;

	return world->world_tiles[current_tile_x][current_tile_y];
}

bool Intelligence::check_if_dot_is_on_tile(Dot* dot, Dot* tile)
{
	if (tile != NULL && (dot->getTileX() == tile->getTileX() && dot->getTileY() == tile->getTileY())) return true;
	else return false;
}

bool Intelligence::check_if_dots_adjacent(Dot* dot_one, Dot* dot_two)
{
	bool adjacent = false;
	if ((dot_one->getTileX() >= (dot_two->getTileX() -1) && dot_one->getTileX() <= (dot_two->getTileX() + 1))
		&& (dot_one->getTileY() >= (dot_two->getTileY() - 1) && dot_one->getTileY() <= (dot_two->getTileY() + 1)))
	{
		adjacent = true;
	}
	return adjacent;
}

bool Intelligence::check_if_dot_and_tile_are_adjacent(Dot* dot, Dot* tile)
{
	bool adjacent = false;

	int dot_x = dot->getTileX();
	int dot_y = dot->getTileY();
	int tile_x = tile->getTileX();
	int tile_y = tile->getTileY();

	if (tile != NULL)
	{
		if ((dot_x >= tile_x - 1 && dot_x <= tile_x + 1) && (dot_y >= tile_y - 1 && dot_y <= tile_y + 1))
		{
			if (!(dot_x == tile_x && dot_y == tile_y))
			{
				adjacent = true;
			}
		}
	}
	return adjacent;
}

void Intelligence::Spawn_Enemy_Ships()
{
	int ship_x;
	int ship_y;
	int quadrant = rand() % 4;
	int edge_buffer = 100;

	switch (quadrant)
	{
	case 0:
		ship_x = edge_buffer + rand() % edge_buffer;
		ship_y = rand() % LEVEL_HEIGHT;
		break;
	case 1:
		ship_x = rand() % LEVEL_WIDTH;
		ship_y = edge_buffer + rand() % edge_buffer;
		break;
	case 2:
		ship_x = -edge_buffer + rand() % edge_buffer + (LEVEL_WIDTH - edge_buffer);
		ship_y = rand() % LEVEL_HEIGHT;
		break;
	case 3:
		ship_x = rand() % LEVEL_WIDTH;
		ship_y = -edge_buffer + rand() % edge_buffer + (LEVEL_HEIGHT - edge_buffer);
		break;
	}

	if (enemy_ship_array.size() < max_enemy_ships)
	{
		enemy_ship_array.push_back(new Ship_Dot(gRenderer, enemy_ship_spritesheet, ship_x, ship_y));
	}



}

void Intelligence::Update_Enemy_Ship_AI(Ship_Dot* enemy_ship)
{
	set_dot_target(player_dot->dot_rect.x + player_dot->dot_rect.w / 2, player_dot->dot_rect.y + player_dot->dot_rect.h / 2, enemy_ship);
	enemy_ship->turn_towards_target();
	enemy_ship->set_velocity();
	move_dot(enemy_ship, &enemy_ship->mVelX, &enemy_ship->mVelY);
	if (enemy_ship->target_within_range())
	{
		if (enemy_ship->firing_cooldown == 0)
		{
			int fire_location_1_x = rotate_point_around_point(enemy_ship->dot_rect.x + 10, enemy_ship->dot_rect.y + 20, (enemy_ship->dot_rect.x + 32), (enemy_ship->dot_rect.y + 32), enemy_ship->get_angle(), true);
			int fire_location_1_y = rotate_point_around_point(enemy_ship->dot_rect.x + 10, enemy_ship->dot_rect.y + 20, (enemy_ship->dot_rect.x + 32), (enemy_ship->dot_rect.y + 32), enemy_ship->get_angle(), false);
			int fire_location_2_x = rotate_point_around_point(enemy_ship->dot_rect.x + 54, enemy_ship->dot_rect.y + 20, (enemy_ship->dot_rect.x + 32), (enemy_ship->dot_rect.y + 32), enemy_ship->get_angle(), true);
			int fire_location_2_y = rotate_point_around_point(enemy_ship->dot_rect.x + 54, enemy_ship->dot_rect.y + 20, (enemy_ship->dot_rect.x + 32), (enemy_ship->dot_rect.y + 32), enemy_ship->get_angle(), false);

			Create_Bolt(enemy_ship->npc_dot_config.dot_stat_faction, enemy_ship->targetPosX, enemy_ship->targetPosY, 2, fire_location_1_x, fire_location_1_y, enemy_ship->ship_projectile_speed);
			Create_Bolt(enemy_ship->npc_dot_config.dot_stat_faction, enemy_ship->targetPosX, enemy_ship->targetPosY, 2, fire_location_2_x, fire_location_2_y, enemy_ship->ship_projectile_speed);

			enemy_ship->firing_cooldown = 10;
		}
		else enemy_ship->firing_cooldown--;

	}
}

void Intelligence::Update_All_Enemy_Ships_AI()
{
	for (int p = 0; p < enemy_ship_array.size(); ++p)
	{
		if (enemy_ship_array[p]->is_onscreen(camera, 100))
		{
			Update_Enemy_Ship_AI(enemy_ship_array[p]);
			if (enemy_ship_array[p]->npc_dot_config.dot_stat_health <= 0)
			{
				enemy_ship_array.erase(enemy_ship_array.begin() + p);
			}
		}
	}
}

// Dot inventory commands

bool Intelligence::dot_has_item_in_inventory(Dot* dot, int inventory_item_code)
{
	bool item_in_inventory = false;
	for (int p = 0; p < MAX_DOT_INVENTORY; ++p)
	{
		if (dot->npc_dot_config.inventory_slots[p].inventory_item_code == inventory_item_code && dot->npc_dot_config.inventory_slots[p].item_number > 0)
		{
			item_in_inventory = true;
			break;
		}
	}
	return item_in_inventory;

}

void Intelligence::Add_Item_To_Dot_Inventory(Dot* dot, int inventory_item, int quantity)
{
	// IF ADDING ITEMS TO A CONTAINER, MAKE SURE TO ADD THEM TO THE TILE PARTS LIST SO THAT DOTS KNOW WHAT WAS IN THERE WHEN TRANSFERRING ITEMS BETWEEN PLACES //
	if (dot->dot_config[DOT_TYPE] == DOT_CONTAINER) dot->npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ inventory_item,quantity });
	
	bool item_added = false;
	for (int p = 0; p < MAX_DOT_INVENTORY; ++p)
	{
		if (dot->npc_dot_config.inventory_slots[p].inventory_item_code == inventory_item)
		{
			dot->npc_dot_config.inventory_slots[p].item_number += quantity;
			item_added = true;
			break;
		}
	}
	if (item_added == false)
	{
		for (int p = 0; p < MAX_DOT_INVENTORY; ++p)
		{
			if (dot->npc_dot_config.inventory_slots[p].inventory_item_code== INVENTORY_EMPTY_SLOT)
			{
				dot->npc_dot_config.inventory_slots[p].inventory_item_code = inventory_item;
				dot->npc_dot_config.inventory_slots[p].item_number = quantity;
				break;
			}
		}
	}
}

void Intelligence::Remove_Item_From_Dot_Inventory(Dot* dot, int inventory_item_code, int quantity_to_remove)
{
	int leftover_quantity = quantity_to_remove;
	for (int p = 0; p < MAX_DOT_INVENTORY; ++p)
	{
		if (dot->npc_dot_config.inventory_slots[p].inventory_item_code == inventory_item_code)
		{
			int current_item_quantity = dot->npc_dot_config.inventory_slots[p].item_number;
			if (leftover_quantity >= current_item_quantity)
			{
				dot->npc_dot_config.inventory_slots[p].item_number = dot->npc_dot_config.inventory_slots[p].item_number = 0;
				leftover_quantity = leftover_quantity - current_item_quantity;
			}
			else
			{
				dot->npc_dot_config.inventory_slots[p].item_number = dot->npc_dot_config.inventory_slots[p].item_number = dot->npc_dot_config.inventory_slots[p].item_number = dot->npc_dot_config.inventory_slots[p].item_number - leftover_quantity;
				leftover_quantity = 0;
			}

			if (dot->npc_dot_config.inventory_slots[p].item_number <= 0)
			{
				dot->npc_dot_config.inventory_slots[p].inventory_item_code = INVENTORY_EMPTY_SLOT;
				dot->npc_dot_config.inventory_slots[p].item_number = 0;
			}

			if (leftover_quantity == 0)	break;
		}
	}
}

void Intelligence::Remove_Building_Items_From_Dot_Inventory(Dot* dot, Multi_Tile_Type built_item)
{
	if (built_item.building_specs.Requirement_1.requirement_quantity > 0) Remove_Item_From_Dot_Inventory(dot, built_item.building_specs.Requirement_1.inventory_requirement,built_item.building_specs.Requirement_1.requirement_quantity);
	if (built_item.building_specs.Requirement_2.requirement_quantity > 0) Remove_Item_From_Dot_Inventory(dot, built_item.building_specs.Requirement_2.inventory_requirement, built_item.building_specs.Requirement_2.requirement_quantity);
	if (built_item.building_specs.Requirement_3.requirement_quantity > 0) Remove_Item_From_Dot_Inventory(dot, built_item.building_specs.Requirement_3.inventory_requirement, built_item.building_specs.Requirement_3.requirement_quantity);
	if (built_item.building_specs.Requirement_4.requirement_quantity > 0) Remove_Item_From_Dot_Inventory(dot, built_item.building_specs.Requirement_4.inventory_requirement, built_item.building_specs.Requirement_4.requirement_quantity);
	if (built_item.building_specs.Requirement_5.requirement_quantity > 0) Remove_Item_From_Dot_Inventory(dot, built_item.building_specs.Requirement_5.inventory_requirement, built_item.building_specs.Requirement_5.requirement_quantity);
	if (built_item.building_specs.Requirement_6.requirement_quantity > 0) Remove_Item_From_Dot_Inventory(dot, built_item.building_specs.Requirement_6.inventory_requirement, built_item.building_specs.Requirement_6.requirement_quantity);
}

void Intelligence::Dot_Drop_Inventory_Item(Dot* dot, int x_pos, int y_pos, int inventory_item_code, int quantity_dropped)
{
	if (dot->Check_Inventory_For_Item(inventory_item_code))
	{
		cout << dot->print_coords() << "/ " << x_pos << ", " << y_pos << endl;
		Container* new_container = new Container(gRenderer, inventory_spritesheet, x_pos, y_pos, Fetch_Inventory(inventory_item_code).clip_rect_x, Fetch_Inventory(inventory_item_code).clip_rect_y);
		Add_Item_To_Dot_Inventory(new_container, inventory_item_code, quantity_dropped);
		Remove_Item_From_Dot_Inventory(dot, inventory_item_code, quantity_dropped);
		container_array.push_back(new_container);
	}
}

void Intelligence::Dot_Drop_Inventory(Dot* dot, int x_pos, int y_pos)
{
	Container* new_container = new Container(gRenderer, inventory_spritesheet, x_pos, y_pos, Fetch_Inventory(dot->npc_dot_config.inventory_slots[0].inventory_item_code).clip_rect_x, Fetch_Inventory(dot->npc_dot_config.inventory_slots[0].inventory_item_code).clip_rect_y);
	
	for (int i = 0; i < MAX_DOT_INVENTORY; i++)
	{
		if (dot->npc_dot_config.inventory_slots[i].item_number > 0)
		{
			Add_Item_To_Dot_Inventory(new_container, dot->npc_dot_config.inventory_slots[i].inventory_item_code, dot->npc_dot_config.inventory_slots[i].item_number);
			Remove_Item_From_Dot_Inventory(dot, dot->npc_dot_config.inventory_slots[i].inventory_item_code, dot->npc_dot_config.inventory_slots[i].item_number);
		}
	}

	container_array.push_back(new_container);
}

void Intelligence::Add_Container_Items_to_Dot_Inventory(Dot* dot, Dot* container)
{
	for (int i = 0; i < MAX_DOT_INVENTORY; i++)
	{
		if (container->npc_dot_config.inventory_slots[i].item_number > 0)
		{
			Add_Item_To_Dot_Inventory(dot, container->npc_dot_config.inventory_slots[i].inventory_item_code, container->npc_dot_config.inventory_slots[i].item_number);
		}
	}

	Delete_Container_by_Pointer(container);
}

void Intelligence::Delete_Container_by_Pointer(Dot* container_pointer)
{
	delete container_pointer;
	container_array.erase(find(container_array.begin(), container_array.end(), container_pointer));
}

void Intelligence::Dot_Give_Inventory_To_Another_Dot(Dot* dot, Dot* second_dot, int inventory_item_code, int quantity)
{
	if (second_dot->multi_tile_config.built_percent < 100)
	{
		for (int i = 0; i < second_dot->npc_dot_config.tile_parts_list.size(); i++)
		{
			int item_quantity = dot->Check_Inventory_For_Item(second_dot->npc_dot_config.tile_parts_list[i].inventory_item_code);
			if (item_quantity > 0)
			{
				int quantity = min(second_dot->npc_dot_config.tile_parts_list[i].item_number, item_quantity);
				Add_Item_To_Dot_Inventory(second_dot, second_dot->npc_dot_config.tile_parts_list[i].inventory_item_code, quantity);
				Remove_Item_From_Dot_Inventory(dot, second_dot->npc_dot_config.tile_parts_list[i].inventory_item_code, quantity);
				second_dot->npc_dot_config.tile_parts_list[i].item_number = second_dot->npc_dot_config.tile_parts_list[i].item_number - item_quantity;
				if (second_dot->npc_dot_config.tile_parts_list[i].item_number == 0) second_dot->npc_dot_config.tile_parts_list.erase(second_dot->npc_dot_config.tile_parts_list.begin() + i);
			}
		}
	}
	else
	{
		if (dot->Check_Inventory_For_Item(inventory_item_code) >= quantity)
		{
			Remove_Item_From_Dot_Inventory(dot, inventory_item_code, quantity);
			Add_Item_To_Dot_Inventory(second_dot, inventory_item_code, quantity);
		}
	}
}

void Intelligence::Dot_Craft_Item(Dot* dot, int inventory_item_code, int quantity)
{
	for (int i=0; i < quantity; i++)
	{
		Add_Item_To_Dot_Inventory(dot, inventory_item_code, 1);
		Remove_Building_Items_From_Dot_Inventory(dot, Return_Tile_By_Inventory_Item(inventory_item_code));
	}
}

// DOT AI COMMANDS

// MAJOR

void Intelligence::update_player_dot_ai(NPC_Dot* dot)
{
	// CHEATING
	//dot->npc_dot_config.dot_stat_health = dot->npc_dot_config.dot_stat_max_health;
	dot->npc_dot_config.dot_stat_speed = 3;

	// NON-CHEATING
	if (player_dot_debug) cout << "setting dot speed" << endl;
	dot->previous_mPosX = dot->dot_rect.x;
	dot->previous_mPosY = dot->dot_rect.y;

	if (player_dot_debug) cout << "moving dot" << endl;
	move_dot(dot, &dot->mVelX, &dot->mVelY);

	if (player_dot_debug) cout << "animating dot" << endl;
	dot->animate_movement(dot->previous_mPosX, dot->previous_mPosY);

	Manage_Dot_Equipment(dot);
	
	for (int i = 0; i < dot->npc_dot_config.dot_priority_map.size(); i++)
	{
		Manage_Priority_Delays(dot, i);
		if (dot->npc_dot_config.dot_priority_map[i].current_delay == 0)
		{
			Manage_Priority_Changes(dot, i);
		}
	}

}

void Intelligence::Update_NPD_AI()
{
	player_dot->npc_dot_config.dot_stat_health = 100;
	//Calculate_Individual_Job_Priorities();
	total_job_priority = Calculate_Total_Job_Priority();

	for (int p = 0; p < npc_dot_array.size(); ++p)
	{
		npc_dot_array[p]->x_tile = npc_dot_array[p]->getTileX();
		npc_dot_array[p]->y_tile = npc_dot_array[p]->getTileY();
	
		Erase_Alerts(npc_dot_array[p]);

		// Choose a job if you don't have one already
		if (npc_dot_array[p]->npc_dot_config.current_goal_list.size() == 0)
		{
			npc_dot_array[p]->dot_current_job = Dot_Job{ DOT_JOB_NO_ASSIGNED_JOB };
			npc_dot_array[p]->Set_Carried_item(gRenderer, inventory_spritesheet, INVENTORY_NULL_ITEM);
			if (npc_dot_array[p]->npc_dot_config.dot_stat_faction == DOT_FACTION_PLAYER) Dot_Choose_Job(npc_dot_array[p]);
			npc_dot_array[p]->dot_current_job.Run_Job(npc_dot_array[p]);
		}

		//Run personal jobs
		Manage_Dot_Combat(npc_dot_array[p]);
		Manage_Dot_Equipment(npc_dot_array[p]);
		Manage_Dot_Health(npc_dot_array[p]);

		
		// Run Goals

		if (!empty(npc_dot_array[p]->npc_dot_config.current_goal_list))
		{
			if (job_debug) cout << "dot: " << to_string(int(&npc_dot_array[p])) << " with job type: " << npc_dot_array[p]->dot_current_job.job_type << " starting work on: " << npc_dot_array[p]->npc_dot_config.current_goal_list.back().goal_action << endl;
			Process_Most_Recent_Dot_Goal(npc_dot_array[p]);
			if (job_debug) cout << "dot finished with goal" << endl;
		}		
		
		//HANDLE DOT MOVEMENT
		Set_Dot_Target_to_Next_Node_on_Path(npc_dot_array[p]);

		npc_dot_array[p]->previous_mPosX = npc_dot_array[p]->dot_rect.x;
		npc_dot_array[p]->previous_mPosY = npc_dot_array[p]->dot_rect.y;
		npc_dot_array[p]->set_direction();

		if (npc_dot_array[p]->dot_pause_movement == false)
		{
			npc_dot_array[p]->set_velocity();
			move_dot(npc_dot_array[p], &npc_dot_array[p]->mVelX, &npc_dot_array[p]->mVelY);
			npc_dot_array[p]->animate_movement(npc_dot_array[p]->previous_mPosX, npc_dot_array[p]->previous_mPosY);
		}
		else npc_dot_array[p]->dot_pause_movement = false;
		
		//// HANDLE DOT DEATH
		if (npc_dot_array[p]->npc_dot_config.dot_stat_health <= 0)
		{
			Dot_Drop_Inventory(npc_dot_array[p], npc_dot_array[p]->getPosX(), npc_dot_array[p]->getPosY());
			delete npc_dot_array[p];
			npc_dot_array.erase(npc_dot_array.begin() + p);
		}
		
	}
}

void Intelligence::Process_Most_Recent_Dot_Goal(Dot* dot)
{
	if (dot->npc_dot_config.current_goal_list.size() == 0) return;
	
	int available_quantity;
	int transfer_quantity;
	Tile* nearest_accessible;
	Carried_Multi_Tile new_carried_item;
	vector<Tile*> oxygenation_search_vector;
	World::oxygenation_check new_check = { false, oxygenation_search_vector };

	Dot* current_dot_goal_pointer = dot->npc_dot_config.current_goal_list.back().pointer_to_dot_pointer;
	int* current_dot_value_pointer = dot->npc_dot_config.current_goal_list.back().pointer_to_quantity_to_change;

	bool goal_complete = false;

	switch (dot->npc_dot_config.current_goal_list.back().goal_action)
	{

	case ACTION_NONE:
		goal_complete = true;
		break;

		// FUNCTIONS THAT DON'T REQUIRE A POINTER OF ANY KIND
	case ACTION_SET_DOT_FOCUS_TO_NEAREST_DOT_OF_TYPE:
		dot->npc_dot_config.current_dot_focus = return_nearest_dot_by_type(dot, dot->npc_dot_config.current_goal_list.back().goal_dot_type, dot->npc_dot_config.current_goal_list.back().tile_type);
		if (check_dot_type(dot->npc_dot_config.current_dot_focus, DOT_FOCUS_DOT_TYPE, dot->npc_dot_config.current_goal_list.back().goal_dot_type, dot->npc_dot_config.current_goal_list.back().tile_built)) goal_complete = true;
		break;
	case ACTION_SET_TILE_FOCUS_TO_NEAREST_TILE_OF_TYPE:
		dot->npc_dot_config.current_dot_focus = return_nearest_tile_by_type_or_name(dot, false, dot->npc_dot_config.current_goal_list.back().tile_type.tile_type);
		if (check_dot_type(dot->npc_dot_config.current_dot_focus, DOT_FOCUS_TILE_TYPE, dot->npc_dot_config.current_goal_list.back().tile_type.tile_type, dot->npc_dot_config.current_goal_list.back().tile_built)) goal_complete = true;
		break;
	case ACTION_DROP_ENTIRE_DOT_INVENTORY:
		Dot_Drop_Inventory(dot, dot->getPosX(), dot->getPosY());
		goal_complete = true;
		break;
	case ACTION_CHANGE_DOT_CONFIG_ATTRIBUTE:
		dot->dot_config[dot->npc_dot_config.current_goal_list.back().goal_dot_type] = dot->npc_dot_config.current_goal_list.back().action_quantity;
		goal_complete = true;
		break;
	case ACTION_OXYGENATE_AIR:
		dot->multi_tile_config.is_oxygenated = 500;
		world->Test_All_Tile_Neighbors_For_Leaks(world->world_tiles[dot->getTileX()][dot->getTileY()], &new_check);
		if (new_check.breach_status == false) world->Toggle_Room_Tiles_Oxygenated(new_check.tile_vector, dot->multi_tile_config.is_oxygenated / new_check.tile_vector.size());
		goal_complete = true;
		break;
	case ACTION_GROW_FRENZEL:
		if (world->Find_tile_within_radius_of_dot(dot, ITEM_TYPE_EMITTER, 5, true))
		{
			dot->npc_dot_config.frenzel_rhomb = dot->npc_dot_config.frenzel_rhomb + 1;
		}
		if (dot->npc_dot_config.frenzel_rhomb >= 500)
		{
			world->Grow_Frenzel(dot->getTileX(), dot->getTileY(), current_frenzel_amount);
			dot->npc_dot_config.frenzel_rhomb = 0;
			bool frenzel_already_on_spot = false;
			for (int i = 0; i < container_array.size(); i++)
			{
				if (container_array[i]->getTileX() == dot->getTileX() && container_array[i]->getTileY() == dot->getTileY()) frenzel_already_on_spot = true;
			}
			if (frenzel_already_on_spot == false)
			{
				Dot_Drop_Inventory(dot, dot->getPosX(), dot->getPosY());
			}
		}
		goal_complete = true;
		break;

		// FUNCTIONS THAT RELY ON A MULTI_TILE_CONFIG
	case ACTION_DROP_ALL_INVENTORY_ITEM_OF_TYPE:
		if (dot->npc_dot_config.current_goal_list.back().tile_built == false)
		{
			Dot_Drop_Inventory_Item(dot, world->Find_Accessible_Adjacent_Tile(dot)->getPosX(), world->Find_Accessible_Adjacent_Tile(dot)->getPosY(), dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer, dot->Check_Inventory_For_Item(dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer));
		}
		else Dot_Drop_Inventory_Item(dot, dot->getPosX(), dot->getPosY(), dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer, dot->Check_Inventory_For_Item(dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer));
		goal_complete = true;
		break;
	case ACTION_ADD_ITEM_TO_DOT_INVENTORY:
		Add_Item_To_Dot_Inventory(current_dot_goal_pointer, dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer, dot->npc_dot_config.current_goal_list.back().action_quantity);
		goal_complete = true;
		break;
	case ACTION_REMOVE_ITEM_FROM_DOT_INVENTORY:
		Remove_Item_From_Dot_Inventory(current_dot_goal_pointer, dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer, dot->npc_dot_config.current_goal_list.back().action_quantity);
		goal_complete = true;
		break;
	case ACTION_REMOVE_BUILDING_ITEMS_FROM_DOT_INVENTORY:
		Remove_Building_Items_From_Dot_Inventory(dot, dot->npc_dot_config.current_goal_list.back().tile_type);
		goal_complete = true;
		break;
	case ACTION_TAKE_INVENTORY_FROM_ANOTHER_DOT:
		available_quantity = current_dot_goal_pointer->Check_Inventory_For_Item(dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer);
		transfer_quantity = min(available_quantity, dot->npc_dot_config.current_goal_list.back().action_quantity);
		Dot_Give_Inventory_To_Another_Dot(current_dot_goal_pointer, dot, dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer, transfer_quantity);
		goal_complete = true;
		break;
	case ACTION_SET_DOT_TO_CARRY_ITEM:
		current_dot_goal_pointer->Set_Carried_item(gRenderer, inventory_spritesheet, dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer);
		goal_complete = true;
		break;
	case ACTION_SET_DOT_TO_NOT_CARRY_ITEM:
		current_dot_goal_pointer->npc_dot_config.dot_carried_item = NULL;
		goal_complete = true;
		break;

		// FUNCTIONS THAT DO REQUIRE A SPECIFIC POINTER
	case ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT:
		if (!check_dot_pointer(dot, current_dot_goal_pointer)) break;
		if (dot->npc_dot_config.current_goal_list.back().tile_built == false)
		{
			Tile* nearest_accessible = world->world_tiles[dot->getTileX()][dot->getTileY()];
			if (current_dot_goal_pointer != NULL) nearest_accessible = world->Find_Accessible_Adjacent_Tile(current_dot_goal_pointer);
			if (nearest_accessible != NULL)
			{
				if (!(dot->getTileX() == nearest_accessible->getTileX() && dot->getTileY() == nearest_accessible->getTileY()))
				{
					if (Update_Dot_Path(dot, nearest_accessible->getTileX(), nearest_accessible->getTileY())) goal_complete = true;
				}
			}
		}
		else if (Update_Dot_Path(dot, current_dot_goal_pointer->getTileX(), current_dot_goal_pointer->getTileY())) goal_complete = true;
		break;
	case ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT:
		if (!check_dot_pointer(dot, current_dot_goal_pointer))
		{
			break;
		}
		if (check_if_dots_adjacent(dot, current_dot_goal_pointer))
		{
			goal_complete = true;
		}
		else if (dot->npc_dot_config.current_goal_path.size() != 0 && dot->npc_dot_config.current_goal_path[0].x_tile == dot->getTileX() && dot->npc_dot_config.current_goal_path[0].y_tile == dot->getTileY())
		{
			dot->targetPosX = current_dot_goal_pointer->getPosX();
			dot->targetPosY = current_dot_goal_pointer->getPosY();
		}
		break;
	case ACTION_CHECK_IF_DOT_IS_ON_SPECIFIC_DOT:
		if (!check_dot_pointer(dot, current_dot_goal_pointer)) break;
		if (check_if_dot_is_on_tile(dot, current_dot_goal_pointer) == true)
		{
			goal_complete = true;
		}
		break;
	case ACTION_CHECK_IF_DOT_IS_IN_RANGE_OF_SPECIFIC_DOT:
		if (!check_dot_pointer(dot, current_dot_goal_pointer)) break;
		if (Check_Distance_Between_Dots(dot, current_dot_goal_pointer) <= dot->npc_dot_config.current_goal_list.back().action_quantity) goal_complete = true;
		else
		{
			if (abs(current_dot_goal_pointer->getTileX() - dot->npc_dot_config.current_goal_path[0].x_tile) >= 2 || abs(current_dot_goal_pointer->getTileY() - dot->npc_dot_config.current_goal_path[0].y_tile) >= 2)
			{
				dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,0,0,0,0,null_tile,0,true,current_dot_goal_pointer });
			}
		}
		break;
	case ACTION_CHANGE_DOT_QUANTITY:
		if (!check_dot_pointer(dot, current_dot_goal_pointer)) break;
		if (!(check_if_dots_adjacent(dot, current_dot_goal_pointer))) dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,0,0,0,0,null_tile,0,true, dot->npc_dot_config.current_dot_focus });
		else
		{
			if (*current_dot_value_pointer != dot->npc_dot_config.current_goal_list.back().goal_complete_quantity)
			{
				*current_dot_value_pointer = *current_dot_value_pointer + dot->npc_dot_config.current_goal_list.back().action_quantity;
			}
			if (*current_dot_value_pointer == dot->npc_dot_config.current_goal_list.back().goal_complete_quantity)	goal_complete = true;
		}
		break;
	case ACTION_GIVE_INVENTORY_TO_ANOTHER_DOT:
		if (!check_dot_pointer(dot, current_dot_goal_pointer)) break;
		Dot_Give_Inventory_To_Another_Dot(dot, current_dot_goal_pointer, dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer, min(dot->Check_Inventory_For_Item(dot->npc_dot_config.current_goal_list.back().tile_type.inventory_pointer), dot->npc_dot_config.current_goal_list.back().action_quantity));
		goal_complete = true;
		break;
	case ACTION_GET_INSIDE_ANOTHER_DOT:
		dot->dot_rect.x = current_dot_goal_pointer->dot_rect.x;
		dot->dot_rect.y = current_dot_goal_pointer->dot_rect.y;
		if (current_dot_goal_pointer->multi_tile_config.tile_type == ITEM_TYPE_BED)
		{
			dot->npc_dot_config.dot_angle = 90;
			dot->dot_rect.x += TILE_WIDTH / 2;
		}
		goal_complete = true;
		break;
	case ACTION_GET_OUT_OF_ANOTHER_DOT:
		nearest_accessible = world->Find_Accessible_Adjacent_Tile(current_dot_goal_pointer);
		dot->dot_rect.x = nearest_accessible->dot_rect.x;
		dot->dot_rect.y = nearest_accessible->dot_rect.y;
		if (current_dot_goal_pointer->multi_tile_config.tile_type == ITEM_TYPE_BED) dot->npc_dot_config.dot_angle = 0;
		goal_complete = true;
		break;
	case ACTION_FIRE_AT_ANOTHER_DOT:
		if (current_dot_goal_pointer->npc_dot_config.dot_stat_health <= 0 || current_dot_goal_pointer == NULL)
		{
			goal_complete = true;
			break;
		}

		int dot_distance = Check_Distance_Between_Dots(dot, current_dot_goal_pointer);
		if (dot_distance < Fetch_Inventory(dot->npc_dot_config.dot_equipment_config.Weapon.inventory_item_code).weapon_range)
		{
			dot->dot_pause_movement = true;
			if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].current_level == 0) Fire_Weapon(dot, current_dot_goal_pointer, 0, 10);
		}
		else (dot->dot_wipe_all_job_tasks());
		break;
	}

	if (goal_complete)
	{
		dot->npc_dot_config.current_goal_list.pop_back();
		//if (dot->current_goal_list.size() != 0 && dot->dot_config[DOT_TYPE] == DOT_NPC)
		//{
		//	cout << "moving on to goal: " << dot->current_goal_list.back().goal_action << endl;
		//	cout << "size of dot tile parts list is: " << dot->tile_parts_list.size() << endl;
		//}
		//else if (dot->dot_config[DOT_TYPE] == DOT_NPC) cout << "no more goals" << endl;
	}
}

// MINOR

void Intelligence::Manage_Dot_Combat(NPC_Dot* dot)
{	
	Dot* combat_target_dot = NULL;

	int closest_static_target = dot->npc_dot_config.search_radius*TILE_WIDTH;
	int closest_dot_target = dot->npc_dot_config.search_radius*TILE_WIDTH;
	int radius = dot->npc_dot_config.search_radius;

	for (int p = dot->getTileY() - radius / 2; p < dot->getTileY() + radius / 2; p++)
	{
		for (int i = dot->getTileX() - radius / 2; i < dot->getTileX() + radius / 2; i++)
		{
			if (world->world_tiles[i][p] != NULL && world->world_tiles[i][p]->multi_tile_config.tile_type != VACUUM && world->world_tiles[i][p]->multi_tile_config.is_collidable == 1 && Check_Faction_Score_Between_Dots(dot, world->world_tiles[i][p]) < 0)
			{
				int target_distance = Check_Distance_Between_Dots(dot, world->world_tiles[i][p]);
				if (target_distance < closest_static_target)
				{
					closest_static_target = target_distance;
					combat_target_dot = world->world_tiles[i][p];
				}				
			}
		}
	}


	for (int i = 0; i < npc_dot_array.size(); i++)
	{
		if (Check_Faction_Score_Between_Dots(dot, npc_dot_array[i]) < 0)
		{
			int target_distance = Check_Distance_Between_Dots(dot, npc_dot_array[i]);
			if (target_distance < closest_dot_target)
			{
				closest_dot_target = target_distance;
				combat_target_dot = npc_dot_array[i];
			}
		}
	}

	//if (Check_Faction_Score_Between_Dots(dot, player_dot) < 0)
	//{
	//	int target_distance = Check_Distance_Between_Dots(dot, player_dot);
	//	if (target_distance < closest_dot_target)
	//	{
	//		cout << target_distance << " : " << closest_dot_target << endl;
	//		combat_target_dot = player_dot;
	//	}
	//}

	if (combat_target_dot != NULL && dot->dot_current_job.job_type > DOT_HEALTH_JOB_ELIMINATE_DOT )
	{
		dot->dot_current_job = Dot_Job{ DOT_HEALTH_JOB_ELIMINATE_DOT,1,combat_target_dot,NULL, null_tile, Fetch_Inventory(dot->npc_dot_config.dot_equipment_config.Weapon.inventory_item_code).weapon_range };
		dot->dot_current_job.Run_Job(dot);
	}
}

void Intelligence::Manage_Dot_Health(NPC_Dot* dot)
{	
	// RUN THROUGH ALL DOT PRIORITIES TO FIGURE OUT IF ANY OF THEM AT ARE LEVELS WHERE WE NEED TO TAKE CORRECTIVE ACTION
	for (int i = 0; i < dot->npc_dot_config.dot_priority_map.size(); i++)
	{
		Manage_Priority_Delays(dot, i);
		if (dot->npc_dot_config.dot_priority_map[i].current_delay == 0)
		{
			Manage_Priority_Changes(dot, i);
			if (dot->npc_dot_config.dot_priority_map[i].current_delay == 0 && dot->npc_dot_config.dot_priority_map[i].current_level >= dot->npc_dot_config.dot_priority_map[i].alarm_level)
			{
				//if (dot->dot_priority_map[i].current_level >= dot->dot_priority_map[i].max_level) Respond_To_Dot_Priority_Max_Level(dot, i);
				//else
				Respond_To_Dot_Priority_Alarm_Level(dot, i);
			}
		}
	}
}

void Intelligence::Manage_Dot_Equipment(Dot* dot)
{
	if (dot->Check_Inventory_For_Item(INVENTORY_OXYGEN_TANK) > 0)
	{
		dot->npc_dot_config.dot_equipment_config.Oxygen_Tank.inventory_item_code = INVENTORY_OXYGEN_TANK;
		dot->npc_dot_config.dot_equipment_config.Oxygen_Tank.item_number = dot->Check_Inventory_For_Item(INVENTORY_OXYGEN_TANK);
	}
	else
	{
		dot->npc_dot_config.dot_equipment_config.Oxygen_Tank.inventory_item_code = INVENTORY_EMPTY_SLOT;
		dot->npc_dot_config.dot_equipment_config.Oxygen_Tank.item_number = 0;
	}

	if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level >= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].alarm_level && dot->Check_Inventory_For_Item(INVENTORY_SPACESUIT_1) > 0 && dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code != INVENTORY_SPACESUIT_1)
	{
		dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code = INVENTORY_SPACESUIT_1;
		dot->npc_dot_config.dot_equipment_config.Spacesuit.item_number = 1;
	}
	else if (get_current_dot_tile(dot)->multi_tile_config.is_oxygenated >= 1  && dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level < dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].alarm_level)
	{
		dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code = INVENTORY_EMPTY_SLOT;
		dot->npc_dot_config.dot_equipment_config.Spacesuit.item_number = 0;
	}
}

void Intelligence::Manage_Priority_Changes(Dot* dot, int dot_priority_name)
{
	switch (dot_priority_name)
	{
	case DOT_PRIORITY_OXYGEN_NEED:
		if (get_current_dot_tile(dot)->multi_tile_config.is_oxygenated >= 1 || 
			dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code == INVENTORY_SPACESUIT_1 && 
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level > 0)
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level--;
			if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level < dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].min_level)
			{
				dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].min_level;
			}
		}
		else
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level++;
			if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level >= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].max_level)
			{
				dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].max_level;
				dot->npc_dot_config.dot_stat_health--;
			}
		}
		break;
	case DOT_PRIORITY_SPACESUIT_OXYGEN:
		if (dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code == INVENTORY_SPACESUIT_1)
		{
			if (get_current_dot_tile(dot)->multi_tile_config.is_oxygenated >= 1)
			{
				if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level < dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].max_level)
				{
					dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level++;
				}
			}
			else
			{
				if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level > dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].min_level)
				{
					dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level--;
				}
			}

			if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level <= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].min_level)
			{
				if (dot->Check_Inventory_For_Item(INVENTORY_OXYGEN_TANK) > 0)
				{
					Remove_Item_From_Dot_Inventory(dot, INVENTORY_OXYGEN_TANK, 1);
					dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level = 100;
				}
			}
		}
		break;
	case DOT_PRIORITY_SLEEP_NEED:
		dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level++;
		if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level >= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].max_level)
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].max_level;
		}
		if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level <= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].min_level)
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].min_level;
		}
		break;
	case DOT_PRIORITY_HUNGER_NEED:
		dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level++;
		if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level >= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].max_level)
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].max_level;
		}
		if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level <= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].min_level)
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].min_level;
		}
		break;
	case DOT_PRIORITY_WEAPON_COOLDOWN:
		dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].current_level--;
		if (dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].current_level <= dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].min_level)
		{
			dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].current_level = dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].min_level;
		}
	}
}

void Intelligence::Manage_Priority_Delays(Dot* dot, int dot_priority_name)
{
	dot->npc_dot_config.dot_priority_map[dot_priority_name].current_delay++;
	if (dot->npc_dot_config.dot_priority_map[dot_priority_name].current_delay > dot->npc_dot_config.dot_priority_map[dot_priority_name].max_delay) dot->npc_dot_config.dot_priority_map[dot_priority_name].current_delay = 0;
}

void Intelligence::Respond_To_Dot_Priority_Alarm_Level(NPC_Dot* dot, int dot_priority_name)
{
	switch (dot_priority_name)
	{
	case DOT_PRIORITY_OXYGEN_NEED:

		if (dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code == INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(INVENTORY_SPACESUIT_1) > 0)
		{
			dot->npc_dot_config.dot_equipment_config.Spacesuit.inventory_item_code = INVENTORY_SPACESUIT_1;
			dot->npc_dot_config.dot_equipment_config.Spacesuit.item_number = 1;
		}
		else if (dot->Check_Inventory_For_Item(INVENTORY_SPACESUIT_1) <= 0 && dot->dot_current_job.job_type > DOT_HEALTH_JOB_GO_GET_SPACESUIT)
		{
			
			dot->dot_wipe_goals();
			Dot* nearest_space_suit_closet = return_nearest_container_or_storage_tile_with_item(dot, INVENTORY_SPACESUIT_1);
			if (nearest_space_suit_closet != NULL)
			{
				dot->dot_current_job = Dot_Job{ DOT_HEALTH_JOB_GO_GET_SPACESUIT, 1.0 , nearest_space_suit_closet, NULL, Return_Tile_By_Inventory_Item(INVENTORY_SPACESUIT_1), 1 };
				dot->dot_current_job.Run_Job(dot);
			}
			else if (world->world_tiles[dot->getTileX()][dot->getTileY()]->multi_tile_config.is_oxygenated == 0 && dot->dot_current_job.job_type > DOT_HEALTH_JOB_GO_FIND_OXYGENATED_TILE)
			{
				dot->dot_current_job = Dot_Job{ DOT_HEALTH_JOB_GO_FIND_OXYGENATED_TILE, 1.0 , return_nearest_oxygenated_tile(dot), NULL, null_tile, 1 };
				dot->dot_current_job.Run_Job(dot);
			}
		}
		break;
	case DOT_PRIORITY_SLEEP_NEED:
		if (dot->dot_current_job.job_type > DOT_HEALTH_JOB_GO_TO_BED)
		{
			dot->dot_wipe_goals();
			Dot* nearest_bed = return_nearest_tile_by_type_or_name(dot, false, ITEM_TYPE_BED);
			if (nearest_bed != NULL)
			{
				dot->dot_current_job = Dot_Job{ DOT_HEALTH_JOB_GO_TO_BED, 1.0 , nearest_bed, NULL, null_tile, -1, 0, &dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level };
				dot->dot_current_job.Run_Job(dot);
			}
		}
		break;
	case DOT_PRIORITY_HUNGER_NEED:
		if (dot->dot_current_job.job_type > DOT_HEALTH_JOB_GO_EAT_FOOD && dot->Check_Inventory_For_Item_Type(ITEM_TYPE_FOOD).item_code != INVENTORY_EMPTY_SLOT)
		{
			dot->dot_wipe_goals();
			vector<Dot*> chair_and_table_combo = return_chair_and_table_combo(dot);
			if (chair_and_table_combo.size() == 2)
			{
				dot->dot_current_job = Dot_Job{ DOT_HEALTH_JOB_GO_EAT_FOOD, 1.0 , chair_and_table_combo[0], chair_and_table_combo[1], Return_Tile_By_Inventory_Item(dot->Check_Inventory_For_Item_Type(INVENTORY_TYPE_FOOD).item_code), -1, 0, &dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level };
				dot->dot_current_job.Run_Job(dot);
			}
		}
		else if (dot->dot_current_job.job_type > DOT_HEALTH_JOB_GO_FIND_FOOD)
		{
			dot->dot_wipe_goals();
			Dot* nearest_soylent_meal = return_nearest_container_or_storage_tile_with_item_type(dot, INVENTORY_TYPE_FOOD);
			if (nearest_soylent_meal != NULL)
			{
				dot->dot_current_job = Dot_Job{ DOT_HEALTH_JOB_GO_FIND_FOOD, 1.0 , nearest_soylent_meal, NULL, Return_Tile_By_Inventory_Item(nearest_soylent_meal->Check_Inventory_For_Item_Type(ITEM_TYPE_FOOD).item_code), 1, 0, &dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level };
				dot->dot_current_job.Run_Job(dot);
			}
		}
		break;
	}
}

void Intelligence::Respond_To_Dot_Priority_Max_Level(NPC_Dot* dot, int dot_priority_name)
{
	switch (dot_priority_name)
	{
	case DOT_PRIORITY_OXYGEN_NEED:
		break;
	case DOT_PRIORITY_SLEEP_NEED:
		break;
	case DOT_PRIORITY_HUNGER_NEED:
		break;
	}
}

bool Intelligence::Check_Dot_Path_is_Oxygenated(Dot* dot)
{
	if (dot->npc_dot_config.current_goal_path.size() != 0)
	{
		for (int i = 0; i < dot->npc_dot_config.current_goal_path.size(); i++)
		{
			if (world->world_tiles[dot->npc_dot_config.current_goal_path[i].x_tile][dot->npc_dot_config.current_goal_path[i].y_tile]->multi_tile_config.is_oxygenated == 0) return false;
		}
	}
	else if (world->world_tiles[dot->getTileX()][dot->getTileY()]->multi_tile_config.is_oxygenated == 0) return false;
	else return true;
}

bool Intelligence::Update_Dot_Path(Dot* dot, int target_tile_x, int target_tile_y, bool adjacent)
{
	if (target_tile_x >= 0 && target_tile_y >= 0)
	{
		dot->npc_dot_config.current_goal_path = iField->pathFind(dot->getTileX(), dot->getTileY(), target_tile_x, target_tile_y, adjacent);
		if (dot->npc_dot_config.current_goal_path.size() == 0) return false;
		else return true;
	}
	else
	{
		Push_Alert(dot, "couldn't chart path to: " + to_string(target_tile_x) + ", " + to_string(target_tile_y));
		return false;
	}
}

void Intelligence::Set_Dot_Target_to_Next_Node_on_Path(Dot* dot)
{
	for (int i = dot->npc_dot_config.current_goal_path.size() - 1; i >= 1; i--)
	{
		if (dot->getTileX() == dot->npc_dot_config.current_goal_path[i].x_tile && dot->getTileY() == dot->npc_dot_config.current_goal_path[i].y_tile)
		{
			bool skip_diagonally = false;
			if (i >= 2)
			{

				int current_x_tile = dot->getTileX();
				int next_x_tile = dot->npc_dot_config.current_goal_path[i - 1].x_tile;
				int next_next_x_tile = dot->npc_dot_config.current_goal_path[i - 2].x_tile;
				int current_y_tile = dot->getTileY();
				int next_y_tile = dot->npc_dot_config.current_goal_path[i - 1].y_tile;
				int next_next_y_tile = dot->npc_dot_config.current_goal_path[i - 2].y_tile;

				// Diagonal skips
				// Case 1
				if (next_x_tile == current_x_tile && next_next_x_tile == next_x_tile + 1 && next_y_tile == current_y_tile - 1 && next_next_y_tile == next_y_tile) skip_diagonally = true;
				// Case 2
				else if (next_x_tile == current_x_tile && next_next_x_tile == next_x_tile - 1 && next_y_tile == current_y_tile - 1 && next_next_y_tile == next_y_tile) skip_diagonally = true;
				// Case 3
				else if (next_x_tile == current_x_tile && next_next_x_tile == next_x_tile + 1 && next_y_tile == current_y_tile + 1 && next_next_y_tile == next_y_tile) skip_diagonally = true;
				// Case 4
				else if (next_x_tile == current_x_tile && next_next_x_tile == next_x_tile - 1 && next_y_tile == current_y_tile + 1 && next_next_y_tile == next_y_tile) skip_diagonally = true;
			}

			if (skip_diagonally)
			{
				set_dot_tile_target(dot->npc_dot_config.current_goal_path[i - 2].x_tile, dot->npc_dot_config.current_goal_path[i - 2].y_tile, dot);
			}
			else set_dot_tile_target(dot->npc_dot_config.current_goal_path[i - 1].x_tile, dot->npc_dot_config.current_goal_path[i - 1].y_tile, dot);
			break;
		}
	}
}

void Intelligence::set_dot_target(int new_target_x, int new_target_y, Dot* dot)
{
	dot->targetPosX = new_target_x;
	dot->targetPosY = new_target_y;
}

void Intelligence::set_dot_tile_target(int new_target_tile_x, int new_target_tile_y, Dot* dot)
{
	dot->targetPosX = new_target_tile_x*TILE_WIDTH + TILE_WIDTH / 2;
	dot->targetPosY = new_target_tile_y*TILE_HEIGHT + TILE_HEIGHT / 2;
}


// DOT_JOB COMMANDS

void Intelligence::Dot_Choose_Job(NPC_Dot* npc_dot)
{


	for (int i = 0; i < dot_job_array.size(); i++)
	{
		float dot_quotient = float(dot_job_array[i].currently_assigned_dots.size()) / float(npc_dot_array.size());
		float join_quotient = (dot_job_array[i].job_priority) / (total_job_priority);

		if (dot_quotient < join_quotient)
		{
			npc_dot->dot_current_job = dot_job_array[i];
			dot_job_array[i].currently_assigned_dots.push_back(npc_dot);
			break;
		}
	}
}

float Intelligence::Calculate_Total_Job_Priority()
{
	int total_job_priority = 0;
	for (int i = 0; i < dot_job_array.size(); i++)
	{
		total_job_priority = total_job_priority + dot_job_array[i].job_priority;
	}
	return total_job_priority;
}

bool Intelligence::check_dot_pointer(Dot* npc_dot, Dot* pointer_to_check)
{
	if (pointer_to_check != NULL)
	{
		if (pointer_to_check->dot_config[IS_NOT_NULL] == 9)
		{
			return true;
		}
		else
		{
			npc_dot->dot_wipe_all_job_tasks();
			return false;
		}
	}
	else
	{
		npc_dot->dot_wipe_all_job_tasks();
		return false;
	}
}

bool Intelligence::check_dot_type(Dot* test_dot, int focus_type_category, int focus_type_specific, bool tile_built)
{
	bool dot_focus_match = false;
	if (test_dot == NULL) return dot_focus_match;
	int test_focus = 100;
	switch (focus_type_category)
	{
	case DOT_FOCUS_DOT_TYPE:
		test_focus = test_dot->dot_config[DOT_TYPE];
		if (test_focus == focus_type_specific) dot_focus_match = true;
		break;
	case DOT_FOCUS_TILE_TYPE:
		test_focus = test_dot->multi_tile_config.tile_type;
		if (test_focus == focus_type_specific) dot_focus_match = true;
		break;
	case DOT_FOCUS_INVENTORY_TYPE:
		test_focus = test_dot->multi_tile_config.inventory_pointer;
		if (test_focus == focus_type_specific) dot_focus_match = true;
		break;
	}
	if (dot_focus_match == false && tile_built == false && test_dot->multi_tile_config.built_percent < 100) dot_focus_match = true;
	return dot_focus_match;
}

void Intelligence::change_dot_focus(Dot* dot, Dot* new_focus, int task_type)
{
	if (new_focus != NULL) dot->npc_dot_config.current_dot_focus = new_focus;
	else dot->npc_dot_config.current_dot_focus = NULL;
}

int Intelligence::Number_of_Containers_Not_in_Storage()
{
	return container_array.size();
}

int Intelligence::Amount_of_Inventory_Item_in_Storage(int search_item)
{
	vector<Dot*> search_vector = return_array_of_tiles_by_type_or_name(false, TILE_TYPE_STORAGE_TILE);
	int count = 0;
	for (int i = 0; i < search_vector.size(); i++) count = count + search_vector[i]->Check_Inventory_For_Item(search_item);
	return count;
}

// Dot Search Functions

vector<vector<Dot*>> Intelligence::Return_Array_of_Pointers_To_All_Dot_Vectors()
{
	vector<vector<Dot*>> my_vector;
	my_vector.resize(10);
	my_vector[DOT_ASTEROID] = { asteroid_array.begin(),asteroid_array.end() };
	my_vector[DOT_NPC] = { npc_dot_array.begin(),npc_dot_array.end() };
	my_vector[DOT_CONTAINER] = { container_array.begin(),container_array.end() };
	my_vector[DOT_BOLT] = { bolt_array.begin(),bolt_array.end() };
	my_vector[DOT_ENEMY_SHIP] = { enemy_ship_array.begin(),enemy_ship_array.end() };
	my_vector[DOT_TILE] = {};
	my_vector[DOT_PLAYER].push_back(player_dot);

	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (world->item_tiles[i][p] != NULL) my_vector[DOT_TILE].push_back(world->item_tiles[i][p]);
			else my_vector[DOT_TILE].push_back(world->world_tiles[i][p]);
		}
	}

	return my_vector;
}

vector<Dot*> Intelligence::return_appropriate_dot_vector(int dot_vector_type)
{
	vector<Dot*> temp_vector;
	switch (dot_vector_type)
	{

	case DOT_NPC:
		temp_vector = { npc_dot_array.begin(), npc_dot_array.end()};
		break;
	case DOT_ENEMY_SHIP:
		temp_vector = { enemy_ship_array.begin(), enemy_ship_array.end() };
		break;
	case DOT_ASTEROID:
		temp_vector = { asteroid_array.begin(), asteroid_array.end() };
		break;
	case DOT_CONTAINER:
		temp_vector = { container_array.begin(), container_array.end() };
		break;
	case DOT_BOLT:
		temp_vector = { bolt_array.begin(), bolt_array.end() };
		break;
	case DOT_TILE:
		for (int p = 0; p < TILE_NUM_Y; p++)
		{
			for (int i = 0; i < TILE_NUM_X; i++)
			{
				if (world->world_tiles[i][p]->multi_tile_config.tile_type != VACUUM) temp_vector.push_back(world->world_tiles[i][p]);
				if (world->item_tiles[i][p] != NULL) temp_vector.push_back(world->item_tiles[i][p]);
			}
		}
		break;
	case DOT_GENERIC:
	case DOT_PLAYER:
	case DOT_SCAFFOLD:
		cout << "not a valid vector choice" << endl;
		break;
	}
	return temp_vector;
}

vector<Tile*> Intelligence::return_vector_of_all_tiles()
{
	vector<Tile*> temp_vector;
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (world->world_tiles[i][p]->multi_tile_config.tile_type != VACUUM) temp_vector.push_back(world->world_tiles[i][p]);
			if (world->item_tiles[i][p] != NULL) temp_vector.push_back(world->item_tiles[i][p]);
		}
	}
	return temp_vector;
}

vector<Dot*> Intelligence::return_array_of_tiles_by_type_or_name(bool type_or_name, int search_number)
{
	vector<Dot*> search_vector;

	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (type_or_name)
			{
				if (world->item_tiles[i][p] != NULL && world->item_tiles[i][p]->multi_tile_config.tile_name == search_number) search_vector.push_back(world->item_tiles[i][p]);
				if (world->world_tiles[i][p]->multi_tile_config.tile_name == search_number) search_vector.push_back(world->world_tiles[i][p]);
			}
			else
			{
				if (world->item_tiles[i][p] != NULL && world->item_tiles[i][p]->multi_tile_config.tile_type == search_number) search_vector.push_back(world->item_tiles[i][p]);
				if (world->world_tiles[i][p]->multi_tile_config.tile_type == search_number) search_vector.push_back(world->world_tiles[i][p]);
			}
		}
	}
	return search_vector;
}

Dot* Intelligence::return_nearest_dot_with_faction(Dot* searching_dot, int faction, int search_distance)
{
	int closest_x = 9999;
	int closest_y = 9999;

	Dot* final_dot = NULL;

	for (int i = 0; i < npc_dot_array.size(); i++)
	{
		if (npc_dot_array[i]->npc_dot_config.dot_stat_faction == faction)
		{
			Dot* cur_dot = npc_dot_array[i];
			unsigned int dist_x = abs(cur_dot->getTileX() - searching_dot->getTileX());
			unsigned int dist_y = abs(cur_dot->getTileY() - searching_dot->getTileY());

			if (cur_dot->npc_dot_config.dot_stat_faction == faction && pow((dist_x + dist_y), 2) < pow(search_distance, 2) && (dist_x + dist_y) < (closest_x + closest_y))
			{
				final_dot = cur_dot;
				closest_x = dist_x;
				closest_y = dist_y;
			}
		}
	}
	return final_dot;
}

vector<Dot*> Intelligence::return_array_of_dots_within_radius(Dot* dot, int radius)
{
	vector<Dot*> search_vector;

	for (int i = 0; i < npc_dot_array.size(); i++)
	{
		if (Check_Distance_Between_Dots(dot, npc_dot_array[i]) <= radius)
		{
			search_vector.push_back(npc_dot_array[i]);
		}
	}

	for (int p = dot->getTileY() - radius / 2; p < dot->getTileY() + radius / 2; p++)
	{
		for (int i = dot->getTileX() - radius / 2; i < dot->getTileX() + radius / 2; i++)
		{
			if (world->world_tiles[i][p] != NULL && world->world_tiles[i][p]->multi_tile_config.tile_type != VACUUM) search_vector.push_back(world->world_tiles[i][p]);
			if (world->item_tiles[i][p] != NULL) search_vector.push_back(world->item_tiles[i][p]);
		}
	}

	return search_vector;
}

Dot* Intelligence::return_nearest_dot_by_type(Dot* dot, int dot_vector_type, Multi_Tile_Type tile_type)
{
	vector <Dot*> search_vector = return_appropriate_dot_vector(dot_vector_type);
	int current_x_tile = dot->getTileX();
	int current_y_tile = dot->getTileY();

	int closest_x = TILE_NUM_X + 1;
	int closest_y = TILE_NUM_Y + 1;

	Dot* final_dot = NULL;

	for (int i = 0; i < search_vector.size(); i++)
	{
		Dot* cur_dot = search_vector[i];
		unsigned int dist_x = abs(cur_dot->getTileX() - current_x_tile);
		unsigned int dist_y = abs(cur_dot->getTileY() - current_y_tile);

		if ((dist_x + dist_y) < (closest_x + closest_y) && (tile_type.tile_name == null_tile.tile_name || tile_type.tile_name == cur_dot->multi_tile_config.tile_name))
		{
			final_dot = search_vector[i];
			closest_x = dist_x;
			closest_y = dist_y;
		}
	}

	search_vector.erase(search_vector.begin(), search_vector.end());
	return final_dot;
}

Dot* Intelligence::return_nearest_container_with_item(Dot* dot, int inventory_item_code)
{
	double dot_distance = 9999;
	int dot_number = -1;

	for (int i = 0; i < container_array.size(); i++)
	{
		if (container_array[i]->Check_Inventory_For_Item(inventory_item_code) > 0)
		{

			int distance_x = abs(dot->getTileX() - container_array[i]->getTileX());
			int distance_y = abs(dot->getTileY() - container_array[i]->getTileY());
			if (distance_x + distance_y < dot_distance)
			{
				dot_distance = distance_x + distance_y;
				dot_number = i;
			}
		}
	}

	if (dot_number != -1) return container_array[dot_number];
	else
	{
		return NULL;
	}
}

Dot* Intelligence::return_nearest_container_with_item_type(Dot* dot, int item_type)
{
	double dot_distance = 9999;
	int dot_number = -1;

	for (int i = 0; i < container_array.size(); i++)
	{
		if (container_array[i]->Check_Inventory_For_Item_Type(item_type).item_type == item_type)
		{

			int distance_x = abs(dot->getTileX() - container_array[i]->getTileX());
			int distance_y = abs(dot->getTileY() - container_array[i]->getTileY());
			if (distance_x + distance_y < dot_distance)
			{
				dot_distance = distance_x + distance_y;
				dot_number = i;
			}
		}
	}

	if (dot_number != -1) return container_array[dot_number];
	else
	{
		return NULL;
	}
}

Dot* Intelligence::return_nearest_container_or_storage_tile_with_item(Dot* dot, int item_type)
{
	vector<Dot*> search_array = return_array_of_tiles_by_type_or_name(false, TILE_TYPE_STORAGE_TILE);

	for (int i = 0; i < container_array.size(); i++) search_array.push_back(container_array[i]);

	double dot_distance = 9999;
	int dot_number = -1;

	for (int i = 0; i < search_array.size(); i++)
	{
		if (search_array[i]->Check_Inventory_For_Item(item_type) > 0)
		{

			int distance_x = abs(dot->getTileX() - search_array[i]->getTileX());
			int distance_y = abs(dot->getTileY() - search_array[i]->getTileY());
			if (distance_x + distance_y < dot_distance)
			{
				dot_distance = distance_x + distance_y;
				dot_number = i;
			}
		}
	}

	if (dot_number != -1) return search_array[dot_number];
	else
	{
		return NULL;
	}
}

Dot* Intelligence::return_nearest_container_or_storage_tile_with_item_type(Dot* dot, int item_type)
{
	vector<Dot*> search_array = return_array_of_tiles_by_type_or_name(false, TILE_TYPE_STORAGE_TILE);

	for (int i = 0; i < container_array.size(); i++) search_array.push_back(container_array[i]);

	double dot_distance = 9999;
	int dot_number = -1;

	for (int i = 0; i < search_array.size(); i++)
	{
		if (search_array[i]->Check_Inventory_For_Item_Type(item_type).item_code != INVENTORY_EMPTY_SLOT)
		{

			int distance_x = abs(dot->getTileX() - search_array[i]->getTileX());
			int distance_y = abs(dot->getTileY() - search_array[i]->getTileY());
			if (distance_x + distance_y < dot_distance)
			{
				dot_distance = distance_x + distance_y;
				dot_number = i;
			}
		}
	}

	if (dot_number != -1) return search_array[dot_number];
	else
	{
		return NULL;
	}
}

Dot* Intelligence::return_nearest_tile_by_type_or_name(Dot* dot, bool type_or_name, int search_number)
{
	vector<Dot*> search_vector = return_array_of_tiles_by_type_or_name(type_or_name, search_number);

	int tile_distance = 9999;
	int tile_num_x = -1;
	int tile_num_y = -1;
	bool tile_found = false;

	Dot* found_tile = NULL;

	for (int i = 0; i < search_vector.size(); i++)
	{
		int distance_x = abs(dot->getTileX() - search_vector[i]->getTileX());
		int distance_y = abs(dot->getTileY() - search_vector[i]->getTileY());

		if (distance_x + distance_y < tile_distance)
		{
			tile_distance = distance_x + distance_y;
			found_tile = search_vector[i];
		}
	}

	//if (found_tile == NULL)	cout << "could not find tile, returning null pointer" << endl; 
	return found_tile;
}

Dot* Intelligence::return_nearest_oxygenated_tile(Dot* dot)
{
	int tile_distance = 9999;
	int tile_num_x = -1;
	int tile_num_y = -1;

	Dot* found_tile = NULL;

	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (world->item_tiles[i][p] == NULL && world->world_tiles[i][p]->multi_tile_config.is_oxygenated == 1)
			{
				int distance_x = abs(dot->getTileX() - world->world_tiles[i][p]->getTileX());
				int distance_y = abs(dot->getTileY() - world->world_tiles[i][p]->getTileY());

				if (distance_x + distance_y < tile_distance)
				{
					tile_distance = distance_x + distance_y;
					found_tile = world->world_tiles[i][p];
				}
			}

		}
	}


	//if (found_tile == NULL)	cout << "could not find tile, returning null pointer" << endl; 
	return found_tile;
}

vector<Dot*> Intelligence::return_chair_and_table_combo(Dot* dot)
{
	vector<Dot*> chair_array = return_array_of_tiles_by_type_or_name(false, ITEM_TYPE_CHAIR);
	vector<Dot*> combo;
	for (int i = 0; i < chair_array.size(); i++)
	{
		for (int p = 2; p < 9; p += 2)
		{
			Tile* neighboring_tile = world->Return_Tile_Neighbor(chair_array[i]->getTileX(), chair_array[i]->getTileY(), p);
			if (neighboring_tile->multi_tile_config.tile_type == ITEM_TYPE_TABLE)
			{
				combo.push_back(chair_array[i]);
				combo.push_back(neighboring_tile);
				break;
			}
		}
		if (combo.size() == 2) break;
	}
	return combo;
}




// ASTEROID COMMANDS1

void Intelligence::Distribute_Asteroids()
{
	for (int p = 0; p < TILE_NUM_Y; ++p)
	{
		for (int i = 0; i < TILE_NUM_X; ++i)
		{
			int randomizer = rand() % 100;

			if (randomizer > 98)
			{
				if (world->world_tiles[i][p]->multi_tile_config.tile_type == VACUUM)
				{
					asteroid_array.push_back(new Asteroid(gRenderer, asteroid_spritesheet, i*TILE_WIDTH, p*TILE_WIDTH, 0));
				}
			}
		}
	}
}

void Intelligence::Spawn_Asteroids()
{	
	while (asteroid_array.size() < MAX_NUM_ASTEROIDS)
	{
		int start_range_x = max(0,(camera->camera_box.x) - (SCREEN_WIDTH / 2));
		int end_range_x = min(LEVEL_WIDTH, (camera->camera_box.x + camera->camera_box.w) + SCREEN_WIDTH / 2);
		int start_range_y = max(0, (camera->camera_box.y) - SCREEN_HEIGHT / 2);
		int end_range_y = min(LEVEL_HEIGHT, (camera->camera_box.y + camera->camera_box.h) + SCREEN_HEIGHT / 2);

		int asteroid_x = return_point_not_onscreen(true, start_range_x, end_range_x);
		int asteroid_y = return_point_not_onscreen(false,start_range_y, end_range_y);

		if (world->world_tiles[asteroid_x / TILE_WIDTH][asteroid_y / TILE_HEIGHT] != NULL && world->world_tiles[asteroid_x / TILE_WIDTH][asteroid_y / TILE_HEIGHT]->multi_tile_config.tile_type == VACUUM)
		{
			asteroid_array.push_back(new Asteroid(gRenderer, asteroid_spritesheet, asteroid_x, asteroid_y, 0));
		}

	}
}

void Intelligence::Despawn_Asteroids()
{
	for (int p = 0; p < asteroid_array.size(); p++) 
	{
		if (p < asteroid_array.size())
		{
			if (abs(player_dot->dot_rect.x - asteroid_array[p]->dot_rect.x) > ASTEROID_DESPAWN_RADIUS && abs(player_dot->dot_rect.y - asteroid_array[p]->dot_rect.y) > ASTEROID_DESPAWN_RADIUS)
			{
				delete asteroid_array[p];
				asteroid_array.erase(asteroid_array.begin() + p);
			}
		}
	}
}

Asteroid* Intelligence::Get_Asteroid_At_Coord(int x_coord, int y_coord)
{
	Asteroid* asteroid = NULL;
	for (int p = 0; p < asteroid_array.size(); ++p)
	{
		if (asteroid_array[p]->is_onscreen(camera))
		{
			if (x_coord >= asteroid_array[p]->dot_rect.x && x_coord <= (asteroid_array[p]->dot_rect.x + asteroid_array[p]->dot_rect.w)
				&& y_coord >= asteroid_array[p]->dot_rect.y && y_coord <= (asteroid_array[p]->dot_rect.y + asteroid_array[p]->dot_rect.h))
			{
				asteroid = asteroid_array[p];
				return asteroid;
			}
		}
	}
	return asteroid;
}

int Intelligence::Get_Num_Asteroids()
{
	return asteroid_array.size();
}

void Intelligence::Update_Asteroid_AI()
{
	for (int p = 0; p < asteroid_array.size(); ++p)
	{
		if (asteroid_array[p]->npc_dot_config.dot_stat_health <= 0)
		{
			Dot_Drop_Inventory(asteroid_array[p], asteroid_array[p]->getPosX(), asteroid_array[p]->getPosY());
			delete asteroid_array[p];
			asteroid_array.erase(asteroid_array.begin() + p);
		}
		else if (asteroid_array[p]->is_onscreen(camera) && (asteroid_array[p]->mVelX != 0 || asteroid_array[p]->mVelY != 0))
		{
			move_dot(asteroid_array[p], &asteroid_array[p]->mVelX, &asteroid_array[p]->mVelY);
		}
	}
}

void Intelligence::Create_Asteroid_Mining_Animation(Dot* mining_dot, int t_x, int t_y)
{
	int target_x = t_x;
	int target_y = t_y;
	Create_Bolt(mining_dot->npc_dot_config.dot_stat_faction,t_x + 1,t_y + 1, 1, t_x, t_y, 0, true);
}

// CONTAINER COMMANDS

void Intelligence::Update_Container_AI()
{
	for (int i = 0; i < container_array.size(); i++)
	{
		if (container_array[i]->return_inventory_as_vector().size() == 0)
		{
			delete container_array[i];
			container_array.erase(container_array.begin() + i);
		}
	}
	
	if (container_array.size() > 0)
	{
		for (int i = 0; i < container_array.size(); i++)
		{
			dot_job_array.push_back(Dot_Job{ SPECIFIC_DOT_JOB_STORE_CONTAINER, 1 , container_array[i], NULL, null_tile, 1,100, NULL });
		}
	}
}

// PROJECTILE COMMANDS

void Intelligence::Create_Bolt(int owners_faction, int target_x, int target_y, int sprite_row, int start_location_x, int start_location_y, double speed, bool is_explosion)
{
	if (bolt_array.size() < MAX_PROJECTILES)
	{
		float vector_x = target_x - start_location_x;
		float vector_y = target_y - start_location_y;
		float angle = atan(vector_y / vector_x)*(180.0 / 3.141592653589793238463);

		if (vector_x >= 0 && vector_y >= 0) angle = -90 + angle;
		else if (vector_x < 0 && vector_y >= 0) angle = 90 + angle;
		else if (vector_x < 0 && vector_y < 0) angle = 90 + angle;
		else if (vector_x >= 0 && vector_y < 0) angle = -90 + angle;

		angle = angle / (180.0 / 3.141592653589793238463);

		bolt_array.push_back(new Bolt(gRenderer, bolt_sprites, owners_faction, sprite_row, start_location_x - TILE_WIDTH / 2, start_location_y - TILE_HEIGHT / 2, speed, angle, is_explosion));
	}

}

void Intelligence::Fire_Weapon(Dot* firing_dot, Dot* target_dot, int sprite_row, double speed, bool specific_point, int target_x, int target_y)
{
	firing_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_WEAPON_COOLDOWN].current_level = 1;
	
	int target_pos_x = 0;
	int target_pos_y = 0;
	
	if (specific_point)
	{
		target_pos_x = target_x;
		target_pos_y = target_y;
	}
	else
	{
		target_pos_x = target_dot->getCenterPosX();
		target_pos_y = target_dot->getCenterPosY();
	}

	int diff_x = target_pos_x - firing_dot->getCenterPosX();
	int diff_y = target_pos_y - firing_dot->getCenterPosY();

	if (diff_x > 0) firing_dot->targetPosX = firing_dot->dot_rect.x + firing_dot->dot_rect.w;
	else firing_dot->targetPosX = firing_dot->dot_rect.x;

	if (diff_y > 0) firing_dot->targetPosY = firing_dot->dot_rect.y + firing_dot->dot_rect.h;
	else firing_dot->targetPosY = firing_dot->dot_rect.y;

	Create_Bolt(
		firing_dot->npc_dot_config.dot_stat_faction,
		target_pos_x,
		target_pos_y,
		sprite_row,
		rotate_point_around_point(
			firing_dot->dot_rect.x + firing_dot->dot_rect.w / 2,
			firing_dot->dot_rect.y - 10,
			firing_dot->dot_rect.x + firing_dot->dot_rect.w / 2,
			firing_dot->dot_rect.y + firing_dot->dot_rect.h / 2,
			get_angle_between_two_points(
				firing_dot->dot_rect.x + firing_dot->dot_rect.w / 2,
				firing_dot->dot_rect.y + firing_dot->dot_rect.h / 2,
				target_pos_x,
				target_pos_y),
			true),
		rotate_point_around_point(
			firing_dot->dot_rect.x + firing_dot->dot_rect.w / 2,
			firing_dot->dot_rect.y - 10,
			firing_dot->dot_rect.x + firing_dot->dot_rect.w / 2,
			firing_dot->dot_rect.y + firing_dot->dot_rect.h / 2,
			get_angle_between_two_points(
				firing_dot->dot_rect.x + firing_dot->dot_rect.w / 2,
				firing_dot->dot_rect.y + firing_dot->dot_rect.h / 2,
				target_pos_x,
				target_pos_y),
			false)
			, speed);
}

void Intelligence::Fire_Mining_Laser(Dot* firing_dot, Dot* target_dot, bool point_not_dot_target, int target_x, int target_y)
{
	if (point_not_dot_target) firing_dot->npc_dot_config.dot_mining_config.target_rect = { target_x, target_y, 0,0 };
	else firing_dot->npc_dot_config.dot_mining_config.target_rect = target_dot->dot_rect;

	firing_dot->npc_dot_config.dot_mining_config.laser_on = true;

	if (target_dot->dot_config[DOT_TYPE] == DOT_ASTEROID)
	{
		target_dot->npc_dot_config.dot_stat_health--;
		if (firing_dot->npc_dot_config.dot_mining_config.animation_delay == 10) Create_Asteroid_Mining_Animation(firing_dot, target_dot->dot_rect.x + target_dot->dot_rect.w/2, target_dot->dot_rect.y + target_dot->dot_rect.h / 2);
	}
	else 
	{
		for (int i = 0; i < asteroid_array.size(); i++)
		{
			SDL_Rect target_rect = asteroid_array[i]->dot_rect;
			if (Check_if_Point_Inside_Rect(target_x, target_y, target_rect))
			{
				asteroid_array[i]->npc_dot_config.dot_stat_health--;
				if (firing_dot->npc_dot_config.dot_mining_config.animation_delay == 10) Create_Asteroid_Mining_Animation(firing_dot, target_x, target_y);
			}
		}
	}

	firing_dot->npc_dot_config.dot_mining_config.animation_delay++;
	if (firing_dot->npc_dot_config.dot_mining_config.animation_delay > 10) firing_dot->npc_dot_config.dot_mining_config.animation_delay = 0;
}

void Intelligence::Stop_Firing_Mining_Laser(Dot* firing_dot)
{
	firing_dot->npc_dot_config.dot_mining_config.laser_on = false;

}

void Intelligence::update_bolt_ai()
{
	for (int p = 0; p < bolt_array.size(); ++p)
	{
		if (bolt_array[p]->is_explosion == false)
		{
			move_object_without_collision(&bolt_array[p]->dot_rect, bolt_array[p]->mVelX, bolt_array[p]->mVelY);
			if (check_global_collisions(bolt_array[p]))
			{
				damage_nearby_dots(bolt_array[p], bolt_array[p]->bolt_radius, bolt_array[p]->bolt_damage);
				delete bolt_array[p];
				bolt_array.erase(bolt_array.begin() + p);
			}
			else
			{
				bolt_array[p]->bolt_range++;
				if (bolt_array[p]->bolt_range > bolt_array[p]->bolt_max_range)
				{
					delete bolt_array[p];
					bolt_array.erase(bolt_array.begin() + p);
				}
			}
		}
		else
		{
			if (bolt_array[p]->frame >= 7)
			{
				delete bolt_array[p];
				bolt_array.erase(bolt_array.begin() + p);
			}
		}
	}
}

// WORLD COMMANDS

void Intelligence::Create_Scaffolding(Multi_Tile_Type* tile_type, int x_tile, int y_tile)
{
	Multi_Tile_Type Scaffolding_Tile = *tile_type;
	Scaffolding_Tile.built_percent = 0;
	world->Create_Tile(Scaffolding_Tile, x_tile, y_tile);
}

void Intelligence::Update_World_Ai()
{
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			if (world->item_tiles[i][p] != NULL && world->item_tiles[i][p]->multi_tile_config.item_job_type != DOT_JOB_NO_ASSIGNED_JOB && world->item_tiles[i][p]->npc_dot_config.current_goal_list.size() == 0)
			{
				world->item_tiles[i][p]->item_job.Run_Job(world->item_tiles[i][p]);
				Process_Most_Recent_Dot_Goal(world->item_tiles[i][p]);
				Check_If_Tile_Has_Needs(world->item_tiles[i][p]);

				if (world->item_tiles[i][p]->multi_tile_config.current_health <= 0)
				{
					Dot_Drop_Inventory(world->item_tiles[i][p], world->item_tiles[i][p]->getPosX(), world->item_tiles[i][p]->getPosY());
					world->Create_Tile(Return_Tile_By_Name(TILE_VACUUM), world->item_tiles[i][p]->getTileX(), world->item_tiles[i][p]->getTileY());
				}
			}
			if (world->world_tiles[i][p] != NULL && world->world_tiles[i][p]->multi_tile_config.tile_type != VACUUM)
			{
				world->world_tiles[i][p]->item_job.Run_Job(world->world_tiles[i][p]);
				Process_Most_Recent_Dot_Goal(world->world_tiles[i][p]);
				Check_If_Tile_Has_Needs(world->world_tiles[i][p]);
				
				if (world->world_tiles[i][p]->multi_tile_config.current_health <= 0)
				{
					Dot_Drop_Inventory(world->world_tiles[i][p], world->world_tiles[i][p]->getPosX(), world->world_tiles[i][p]->getPosY());
					world->Create_Tile(Return_Tile_By_Name(TILE_VACUUM), world->world_tiles[i][p]->getTileX(), world->world_tiles[i][p]->getTileY());
				}
			}

			if (world->world_tiles[i][p] != NULL && world->world_tiles[i][p]->npc_dot_config.dot_stat_health <= 0)
			{
				//Dot_Drop_Inventory(world->world_tiles[i][p], world->world_tiles[i][p]->getPosX(), world->world_tiles[i][p]->getPosY());
				Delete_Tile(world->world_tiles[i][p]);
			}
			if (world->item_tiles[i][p] != NULL && world->item_tiles[i][p]->npc_dot_config.dot_stat_health <= 0)
			{
				//Dot_Drop_Inventory(world->item_tiles[i][p], world->item_tiles[i][p]->getPosX(), world->item_tiles[i][p]->getPosY());
				Delete_Tile(world->item_tiles[i][p]);
			}
		}
	}
}

void Intelligence::Check_If_Tile_Has_Needs(Tile* tile)
{
	// CHECK IF THE TILE HAS ANY NEEDED SCAFFOLD PARTS
	tile->Check_if_Dot_Can_Pop_Tile_List_Items();
	
	//IF THE TILE NEEDS PARTS, SEND OUT A FETCH TILES REQUEST
	for (int i = 0; i < tile->npc_dot_config.tile_parts_list.size(); i++)
	{
		Dot* project_dot = tile;
		Dot* dot_with_item = return_nearest_container_or_storage_tile_with_item(tile, tile->npc_dot_config.tile_parts_list[i].inventory_item_code);
		Multi_Tile_Type item_to_transport = Return_Tile_By_Inventory_Item(tile->npc_dot_config.tile_parts_list[i].inventory_item_code);

		if (dot_with_item != NULL)
		{
			int quantity = max(dot_with_item->Check_Inventory_For_Item(tile->npc_dot_config.tile_parts_list[i].inventory_item_code), tile->npc_dot_config.tile_parts_list[i].item_number);
			dot_job_array.push_back(Dot_Job{ SPECIFIC_DOT_JOB_SHUTTLE_ITEM_TO_PROJECT, 1 , project_dot, dot_with_item, item_to_transport, tile->npc_dot_config.tile_parts_list[i].item_number });
		}
	}

	// IF THE TILE IS AN ITEM THAT NEEDS TO BE ACTIVATED, SEND OUT COMPILING REQUEST
	if (tile->npc_dot_config.dot_produced_item.tile_name != TILE_NULL && tile->npc_dot_config.tile_parts_list.size() == 0 && tile->npc_dot_config.production_current < 100)
	{
		dot_job_array.push_back(Dot_Job{ SPECIFIC_DOT_JOB_COMPILE_PROJECT, 1 , tile, NULL, null_tile, 1,100, &tile->npc_dot_config.production_current });
	}

	// IF THE TILE ISN'T BUILT, SEND OUT A BUILDING REQUEST
	if (tile->multi_tile_config.built_percent < 100 && tile->npc_dot_config.tile_parts_list.size() == 0)
	{
		dot_job_array.push_back(Dot_Job{ SPECIFIC_DOT_JOB_BUILD_SCAFFOLD, 1 , tile, NULL, null_tile, 1,100, &tile->multi_tile_config.built_percent });
	}
}

void Intelligence::Delete_Tile(Dot* tile_to_remove)
{
	world->Remove_Tile(tile_to_remove->getTileX(), tile_to_remove->getTileY());
}

// PHYSICS COMMANDS				

void Intelligence::move_dot(Dot* dot, int* mVelX, int* mVelY)
{
	//Move the dot left or right
	dot->dot_rect.x += *mVelX;

	//If the dot went too far to the left or right
	if ((dot->dot_rect.x < 0) || (dot->dot_rect.x + dot->dot_rect.w > LEVEL_WIDTH) || check_global_collisions(dot))
	{
	
		//Move back
		dot->dot_rect.x -= *mVelX;
	}

	//Move the dot up or down
	dot->dot_rect.y += *mVelY;

	//If the dot went too far up or down
	if ((dot->dot_rect.y < 0) || (dot->dot_rect.y + dot->dot_rect.h> LEVEL_HEIGHT) || check_global_collisions(dot))
	{	
		//Move back
		dot->dot_rect.y -= *mVelY;
	}
}

void Intelligence::move_object_without_collision(SDL_Rect* object_rect, float mVelX, float mVelY)
{
	//Move the dot left or right
	object_rect->x += mVelX;

	//Move the dot up or down
	object_rect->y += mVelY;
}

bool Intelligence::check_dot_collision(SDL_Rect* first_object, SDL_Rect* second_object)
{
	bool collision = true;
	int buffer = 5;

	int first_left = first_object->x;
	int first_right = first_object->x + first_object->w;
	int first_top = first_object->y;
	int first_bottom = first_object->y + first_object->h;
	
	int second_left = second_object->x;
	int second_right = second_object->x + second_object->w;
	int second_top = second_object->y;
	int second_bottom = second_object->y + second_object->h;

	// check for situations in which there is no collision
	if (first_right <= second_left + buffer)
	{
		collision = false;
	}
	if (first_left >= second_right - buffer)
	{
		collision = false;
	}

	if (first_top >= second_bottom - buffer)
	{
		collision = false;
	}

	if (first_bottom <= second_top + buffer)
	{
		collision = false;
	}

	if (first_bottom == second_bottom && first_top == second_top && first_left == second_left && first_right == second_right)
	{
		collision = false;
	}

	return collision;
}

bool Intelligence::check_global_collisions(Dot* dot)
{
	SDL_Rect* object = &dot->dot_rect;

	bool collision = false;

	// LOOK FOR COLLISIONS with WORLD TILES AND ITEM TILES

	for (int p = max(0, (object->y / TILE_HEIGHT) - 2); p < min((object->y / TILE_HEIGHT) + 2, TILE_NUM_Y); ++p)
	{
		for (int i = max(0, (object->x / TILE_WIDTH) - 2); i < min((object->x / TILE_WIDTH) + 2, TILE_NUM_X); i++)
		{
			if (world->world_tiles[i][p] != NULL &&  world->world_tiles[i][p]->multi_tile_config.is_collidable == 1 && world->world_tiles[i][p]->multi_tile_config.built_percent == 100)
			{
				if (check_dot_collision(&dot->dot_rect, &world->world_tiles[i][p]->dot_rect) == true) collision = true, world->world_tiles[i][p]->respond_to_collision();
			}
			if (world->item_tiles[i][p] != NULL && world->item_tiles[i][p]->multi_tile_config.is_collidable == 1 && world->item_tiles[i][p]->multi_tile_config.built_percent == 100)
			{
				if (check_dot_collision(&dot->dot_rect, &world->item_tiles[i][p]->dot_rect) == true) collision = true, world->item_tiles[i][p]->respond_to_collision();
			}
		}
	}

	// LOOK FOR COLLISIONS WITH ASTEROIDS
	for (int p = 0; p < asteroid_array.size(); ++p)
	{
		// CHECK TO SEE IF THE OBJECT IS EVEN NEAR THE ASTEROID
		if (abs(object->x - asteroid_array[p]->dot_rect.x) < COLLISION_CHECK_RADIUS && abs(object->y - asteroid_array[p]->dot_rect.y) < COLLISION_CHECK_RADIUS)
		{
			if (check_dot_collision(object, &asteroid_array[p]->dot_rect) == true)
			{
				collision = true;
				int repulsion_x = dot->mVelX;
				int repulsion_y = dot->mVelY;
				asteroid_array[p]->dot_rect.x = asteroid_array[p]->dot_rect.x + repulsion_x;
				asteroid_array[p]->dot_rect.y = asteroid_array[p]->dot_rect.y + repulsion_y;
			}
		}
	}

	// LOOK FOR COLLISIONS WITH DOTS
	for (int p = 0; p < npc_dot_array.size(); ++p)
	{
		// CHECK TO SEE IF THE OBJECT IS EVEN NEAR THE DOT
		if (abs(object->x - npc_dot_array[p]->dot_rect.x) < COLLISION_CHECK_RADIUS && abs(object->y - npc_dot_array[p]->dot_rect.y) < COLLISION_CHECK_RADIUS)
		{
			if (check_dot_collision(object, &npc_dot_array[p]->dot_rect) == true)
			{
				if (dot->dot_config[DOT_TYPE] != DOT_NPC)
				{
					if (dot->dot_config[DOT_TYPE] == DOT_BOLT)
					{
						if (dot->npc_dot_config.dot_stat_faction != npc_dot_array[p]->npc_dot_config.dot_stat_faction) collision = true;
					}
				}

			}
		}
	}

	if (dot->dot_config[DOT_TYPE] == DOT_PLAYER)
	{
		// LOOK FOR COLLISIONS WITH CONTAINERS
		for (int p = 0; p < container_array.size(); ++p)
		{
			// CHECK TO SEE IF THE OBJECT IS EVEN NEAR THE CONTAINER
			if ((dot->dot_config[DOT_TYPE] == DOT_PLAYER || dot->dot_config[DOT_TYPE] == DOT_NPC) && abs(object->x - container_array[p]->dot_rect.x) < COLLISION_CHECK_RADIUS && abs(object->y - container_array[p]->dot_rect.y) < COLLISION_CHECK_RADIUS)
			{
				if (check_dot_collision(object, &container_array[p]->dot_rect) == true)
				{
					Add_Container_Items_to_Dot_Inventory(dot, container_array[p]);
				}
			}
		}
	}


	for (int p = 0; p < enemy_ship_array.size(); ++p)
	{
		// CHECK TO SEE IF THE OBJECT IS EVEN NEAR THE ENEMY SHIP
		if (abs(object->x - enemy_ship_array[p]->dot_rect.x) < COLLISION_CHECK_RADIUS && abs(object->y - enemy_ship_array[p]->dot_rect.y) < COLLISION_CHECK_RADIUS)
		{
			if (check_dot_collision(object, &enemy_ship_array[p]->dot_rect) == true)
			{
				if (dot->npc_dot_config.dot_stat_faction != enemy_ship_array[p]->npc_dot_config.dot_stat_faction) collision = true;
			}
		}
	}

	// LOOK FOR COLLISIONS WITH PLAYER
	if (check_dot_collision(object, &player_dot->dot_rect))
	{
		if (dot->dot_config[DOT_TYPE] != DOT_NPC || dot->npc_dot_config.dot_stat_faction != player_dot->npc_dot_config.dot_stat_faction)
		{
			collision = true;
		}
	}

	return collision;
}

void Intelligence::damage_nearby_dots(Dot* dot_doing_damage, int damage_radius, int weapon_damage)
{
	SDL_Rect* dot_doing_damage_rect = &dot_doing_damage->dot_rect;
	
	int x_tile = (dot_doing_damage_rect->x + (dot_doing_damage_rect->w/2)) / TILE_WIDTH;
	int y_tile = (dot_doing_damage_rect->y + (dot_doing_damage_rect->h/2)) / TILE_HEIGHT;

	if (player_dot->npc_dot_config.dot_stat_faction != dot_doing_damage->npc_dot_config.dot_stat_faction) test_dot_for_damage(player_dot, dot_doing_damage_rect, damage_radius, weapon_damage);

	for (int p = -damage_radius / TILE_HEIGHT; p < damage_radius / TILE_HEIGHT + 1; p++)
	{
		for (int i = -damage_radius / TILE_WIDTH; i < damage_radius / TILE_WIDTH; i++)
		{
			if (world->world_tiles[x_tile + i][y_tile + p] != NULL && world->world_tiles[x_tile + i][y_tile + p]->multi_tile_config.tile_type != VACUUM && world->world_tiles[x_tile + i][y_tile + p]->multi_tile_config.tile_type != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
			{
				if (world->world_tiles[x_tile + i][y_tile + p]->npc_dot_config.dot_stat_faction != dot_doing_damage->npc_dot_config.dot_stat_faction) test_dot_for_damage(world->world_tiles[x_tile + i][y_tile + p], dot_doing_damage_rect, damage_radius, weapon_damage);
			}
			if (world->item_tiles[x_tile + i][y_tile + p] != NULL)
			{
				if (world->item_tiles[x_tile + i][y_tile + p]->npc_dot_config.dot_stat_faction != dot_doing_damage->npc_dot_config.dot_stat_faction) test_dot_for_damage(world->item_tiles[x_tile + i][y_tile + p], dot_doing_damage_rect, damage_radius, weapon_damage);
			}
		}
	}
	
	for (int p = 0; p < npc_dot_array.size(); p++)
	{
		if (npc_dot_array[p]->npc_dot_config.dot_stat_faction != dot_doing_damage->npc_dot_config.dot_stat_faction) test_dot_for_damage(npc_dot_array[p], dot_doing_damage_rect, damage_radius, weapon_damage);
	}

	for (int p = 0; p < asteroid_array.size(); p++)
	{
		if (asteroid_array[p]->npc_dot_config.dot_stat_faction != dot_doing_damage->npc_dot_config.dot_stat_faction) test_dot_for_damage(asteroid_array[p], dot_doing_damage_rect, damage_radius, weapon_damage);
	}

	for (int p = 0; p < enemy_ship_array.size(); p++)
	{
		if (enemy_ship_array[p]->npc_dot_config.dot_stat_faction != dot_doing_damage->npc_dot_config.dot_stat_faction) test_dot_for_damage(enemy_ship_array[p], dot_doing_damage_rect, damage_radius, weapon_damage);
	}
}

void Intelligence::test_dot_for_damage(Dot* test_dot, SDL_Rect* object_doing_damage, int damage_radius, int weapon_damage)
{
	SDL_Rect temp_rect = test_dot->dot_rect;
	int difference_x = (temp_rect.x + temp_rect.w / 2) - (object_doing_damage->x + object_doing_damage->w / 2);
	int difference_y = (temp_rect.y + temp_rect.h / 2) - (object_doing_damage->y + object_doing_damage->h / 2);
	if (abs(difference_x) < damage_radius && abs(difference_y) < damage_radius)
	{
		test_dot->npc_dot_config.dot_stat_health -= weapon_damage;
		Create_Bolt(0,
			(object_doing_damage->x) + difference_x / 2 + 1,
			(object_doing_damage->y) + difference_y / 2 + 1,
			1,
			(object_doing_damage->x) + difference_x / 2,
			(object_doing_damage->y) + difference_y / 2,
			0, true);
	}
}

void Intelligence::test_dots_for_focii()
{
	for (int i = 0; i < npc_dot_array.size(); i++)
	{
		if (npc_dot_array[i]->npc_dot_config.current_dot_focus != NULL)
		{
			cout << npc_dot_array[i]->npc_dot_config.current_dot_focus->dot_config[DOT_TYPE] << endl;
		};
	}
}

// MAIN COMMANDS

void Intelligence::Advance_Time(float avgFPS)
{
	dot_job_array.clear();

	if (ai_debug) cout << "advancing world" << endl;
	Update_World_Ai();

	if (ai_debug) cout << "updating container ai" << endl;
	Update_Container_AI();

	if (ai_debug) cout << "updating asteroid ai" << endl;
	Despawn_Asteroids();
	Spawn_Asteroids();
	Update_Asteroid_AI();

	if (ai_debug) cout << "updating NPD ai" << endl;
	Update_NPD_AI();
	
	if (ai_debug) cout << "updating player dot ai" << endl;
	update_player_dot_ai(player_dot);

	if (ai_debug) cout << "Spawn Enemy Ships" << endl;
	Spawn_Enemy_Ships();
	
	if (ai_debug) cout << "updating Enemy_ship ai" << endl;
	Update_All_Enemy_Ships_AI();

	if (ai_debug) cout << "updating bolt ai" << endl;
	update_bolt_ai();

	delay++;

	if (delay > 1)
	{
		delay = 0;
	}

	player_dot->dot_config[FPS] = avgFPS;

}

void Intelligence::render()
{
	int npc_dot_size = npc_dot_array.size();

	int p_min = camera->camera_box.y / TILE_HEIGHT;
	int p_max = (camera->camera_box.y + camera->camera_box.h) / TILE_HEIGHT + 1;
	int i_min = camera->camera_box.x / TILE_WIDTH;
	int i_max = (camera->camera_box.x + camera->camera_box.w) / TILE_WIDTH + 1;

	for (int p = p_min; p < p_max ; ++p)
	{
		for (int i = i_min ; i < i_max ; ++i)
		{
			if (world->world_tiles[i][p] != NULL)
			{
				world->world_tiles[i][p]->render(gRenderer, camera, RENDER_TILES);
			}		
		}
		for (int i = i_min; i < i_max; ++i)
		{
			if (world->world_tiles[i][p] != NULL)
			{
				if (world->item_tiles[i][p] != NULL) world->item_tiles[i][p]->render(gRenderer, camera, RENDER_UNDER_PLAYER_ITEMS);
				if (world->item_tiles[i][p] != NULL) world->item_tiles[i][p]->render(gRenderer, camera, RENDER_ITEMS);
			}
		}
	}

	player_dot->render(gRenderer, camera);
	lifepod->render(gRenderer, camera);

	for (int p = 0; p < npc_dot_array.size(); p++) if (npc_dot_array[p]->is_onscreen(camera)) npc_dot_array[p]->render(gRenderer, camera);

	for (int p = 0; p < asteroid_array.size(); p++) if (asteroid_array[p]->is_onscreen(camera))
	{
		asteroid_array[p]->render(gRenderer, camera);
	}

	for (int p = 0; p < container_array.size(); p++) if (container_array[p]->is_onscreen(camera)) container_array[p]->render(gRenderer, camera);

	for (int p = 0; p < bolt_array.size(); p++) bolt_array[p]->render(gRenderer, camera);

	for (int p = 0; p < enemy_ship_array.size(); p++) if (enemy_ship_array[p]->is_onscreen(camera)) enemy_ship_array[p]->render(gRenderer, camera);

	//world->Render(camera, RENDER_ROOF);

}

void Intelligence::free()
{
	delete player_dot;

	for (int i = 0; i < npc_dot_array.size(); i++) delete npc_dot_array[i];
	npc_dot_array.erase(npc_dot_array.begin(), npc_dot_array.begin() + npc_dot_array.size());

	for (int i = 0; i < bolt_array.size(); i++) delete bolt_array[i];
	bolt_array.erase(bolt_array.begin(), bolt_array.begin() + bolt_array.size());

	for (int i = 0; i < asteroid_array.size(); i++) delete asteroid_array[i];
	asteroid_array.erase(asteroid_array.begin(), asteroid_array.begin() + asteroid_array.size());

	for (int i = 0; i < enemy_ship_array.size(); i++) delete enemy_ship_array[i];
	enemy_ship_array.erase(enemy_ship_array.begin(), enemy_ship_array.begin() + enemy_ship_array.size());

	for (int i = 0; i < container_array.size(); i++) delete container_array[i];
	container_array.erase(container_array.begin(), container_array.begin() + container_array.size());

	delete iField;
}