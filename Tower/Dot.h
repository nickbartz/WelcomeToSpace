#ifndef DOT_H
#define DOT_H

class Carried_Multi_Tile
{
public:
	Carried_Multi_Tile(SDL_Renderer* gRenderer = NULL, LTexture* inventory_spritesheet = NULL, int* linked_x_coordinate = NULL, int* linked_y_coordinate = NULL, int inventory_item = INVENTORY_EMPTY_SLOT);

	LTexture* spritesheet;
	Inventory_Item carried_item;
	void render(SDL_Renderer* gRenderer, Camera* camera);

	int* linked_x_coord;
	int* linked_y_coord;

	SDL_Rect item_pos;
	SDL_Rect item_clip;

	int sprite_clip_x;
	int sprite_clip_y; 
};

Carried_Multi_Tile::Carried_Multi_Tile(SDL_Renderer* gRenderer, LTexture* inventory_spritesheet, int* linked_x_coordinate, int* linked_y_coordinate, int inventory_item)
{
	carried_item = Fetch_Inventory(inventory_item);
	spritesheet = inventory_spritesheet;
	linked_x_coord = linked_x_coordinate;
	linked_y_coord = linked_y_coordinate;
	sprite_clip_x = carried_item.clip_rect_x;
	sprite_clip_y = carried_item.clip_rect_y;
	item_clip = {  sprite_clip_x*SPRITESHEET_W, sprite_clip_y * SPRITESHEET_H, TILE_WIDTH, TILE_HEIGHT };
}

void Carried_Multi_Tile::render(SDL_Renderer* gRenderer, Camera* camera)
{
	item_pos = { *linked_x_coord - camera->camera_box.x , *linked_y_coord - camera->camera_box.y, TILE_WIDTH, TILE_HEIGHT };
	spritesheet->render(gRenderer, &item_pos, &item_clip);
}


class Dot {
public:
	//Initializes the variables
	Dot(SDL_Renderer* gRenderer, LTexture* dot_spritesheet, int x_pos, int y_pos);
	void free();

	//Shows the dot on the screen
	virtual void Dot::render(SDL_Renderer* gRenderer, Camera* camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_status_bar(SDL_Renderer* gRenderer, Camera* camera, int quantity_of_interest);
	void render_circle(SDL_Renderer* gRenderer, Camera* camera, int tile_x, int tile_y, int radius, int R, int G, int B, int alpha);

	bool is_onscreen(Camera* camera, int buffer = 0);

	//Accessors
	int x_tile;
	int y_tile;
	int Dot::getWidth();
	int Dot::getHeight();
	int Dot::getPosX();
	int Dot::getPosY();
	int Dot::getCenterPosX();
	int Dot::getCenterPosY();
	int Dot::getTileX();
	int Dot::getTileY();
	int Dot::getCamera_x();
	int Dot::getCamera_y();
	string Dot::print_coords();
	void Dot::respond_to_collision();

	// DOT BASIC PLACEMENT AND MOVEMENT
	SDL_Rect dot_rect;

	//Movement trackers
	int delta_x, delta_y;
	int distance_x, distance_y;
	int mVelX, mVelY;
	int previous_mPosX, previous_mPosY;
	double targetPosX, targetPosY;
	bool dot_pause_movement = false;

	//Clipped Dimensions
	int sWidth;
	int sHeight;

	void Dot::toggle_highlight(bool on_or_off);

	// Structs
	struct Dot_Goal
	{
		int goal_action = ACTION_NONE;

		int x_tile = 0;
		int y_tile = 0;
		int tile_or_item = 0;

		int goal_dot_type = NULL;
		Multi_Tile_Type tile_type;

		int action_quantity;
		bool tile_built = true;
		Dot* pointer_to_dot_pointer = NULL;
		int* pointer_to_quantity_to_change = NULL;
		int goal_complete_quantity = 0;
	};

	struct Dot_Priority
	{
		int dot_priority_name;
		int current_level;
		int min_level;
		int alarm_level;
		int max_level;
		int current_delay;
		int max_delay;
	};

	struct Dot_Relationship
	{
		Dot* related_dot;
		string relationship_signifier;
		int relationship_value;
	};

	struct Mining_Laser_Config
	{
		SDL_Rect target_rect = { 0,0,0,0 };
		bool laser_on = false;
		int animation_delay = 0;
		SDL_Color laser_color = { 255, 0, 0, 255 };
	};

	struct NPC_Dot_Equipment_Struct
	{
		Dot_Inventory_Slot Spacesuit = { INVENTORY_EMPTY_SLOT,0 };
		Dot_Inventory_Slot Weapon = { INVENTORY_EMPTY_SLOT,0 };
		Dot_Inventory_Slot Oxygen_Tank = { INVENTORY_EMPTY_SLOT,0 };
		Dot_Inventory_Slot Mining_Laser = { INVENTORY_EMPTY_SLOT,0 };
	};

	struct NPC_Dot_Config_Struct
	{
		string dot_last_name = "";
		string dot_first_name = "";
		string dot_full_name = "";
		int dot_stat_health = 100;
		int dot_stat_max_health = 100;
		int dot_stat_speed = 3;
		int dot_stat_faction = 0;
		int dot_sprite_row = 1;
		vector<Dot_Relationship> dot_relationships;
		vector<Dot_Inventory_Slot> dot_starting_inventory;
		map <int, Dot_Priority> dot_priority_map;
		int frenzel_rhomb = 0;
		Mining_Laser_Config dot_mining_config;
		NPC_Dot_Equipment_Struct dot_equipment_config;
		Carried_Multi_Tile* dot_carried_item = NULL;
		Dot* current_storage_tile = NULL;
		int dot_init = 1;
		SDL_Color dot_color = { 255,255,255,255 };
		int dot_angle = 0;
		Dot_Inventory_Slot inventory_slots[MAX_DOT_INVENTORY];
		vector<Dot_Inventory_Slot> craftable_items;
		int bounce = 0;
		int search_radius = 10;

		// EVENTUALLY WANT TO SPLIT THESE OUT INTO THEIR OWN STRUCT
		Dot* current_dot_focus;
		vector<Tile_Queue> current_goal_path;
		vector<Dot_Goal> current_goal_list;
		vector<Dot_Inventory_Slot> tile_parts_list;
		Multi_Tile_Type dot_produced_item;
		int production_current;
		int number_of_jobs_requested = 0;



	};

	//Set Dot Configuration

	int dot_config[NUM_DOT_STATS];
	NPC_Dot_Config_Struct npc_dot_config;
	Multi_Tile_Type multi_tile_config;

	// Dot Job 

	void dot_wipe_goals();
	void dot_wipe_current_path();
	void dot_wipe_all_job_tasks();

	// Dot Alerts
	struct dot_alert
	{
		string alert_text;
		int age;
	};
	vector<dot_alert> dot_alerts;

	// High Level Dot Functions
	string Create_Name();
	string Create_Dot_Name();
	void Set_Carried_item(SDL_Renderer* gRenderer, LTexture* inventory_spritesheet, int carried_item_type);
	int Check_Inventory_For_Item(int inventory_item_code);
	Inventory_Item Check_Inventory_For_Item_Type(int item_type);
	void Create_Default_Dot_Priorities();
	void Check_Craftable_Items();
	void Return_Parts_List(Multi_Tile_Type tile_type);
	bool Check_If_Tile_Needs_Parts(Multi_Tile_Type tile_type);
	bool Check_if_Dot_Has_All_Needed_Scaffold_Parts(Dot* dot, Multi_Tile_Type tile_type);
	int Check_How_Much_Dot_Can_Craft_Of_Item(Multi_Tile_Type tile_type);
	void Check_if_Dot_Can_Pop_Tile_List_Items();
	vector<Dot_Inventory_Slot> return_inventory_as_vector();

	bool debug = false;
	bool show_collision_box = false;
	
private:
	LTexture* dot_sprite_sheet;
};

Dot::Dot(SDL_Renderer* gRenderer, LTexture* dot_spritesheet, int x_pos, int y_pos)
{	
	dot_sprite_sheet = dot_spritesheet;
	
	//Initialize the offsets
	dot_rect.x = x_pos;
	dot_rect.y = y_pos;
	dot_rect.w = TILE_WIDTH;
	dot_rect.h = TILE_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
	
	dot_config[FPS] = 60;
	dot_config[DOT_TYPE] = DOT_GENERIC;
	dot_config[IS_NOT_NULL] = 9;
	
	string dot_last_name;

	multi_tile_config = null_tile;

	targetPosX = dot_rect.x + dot_rect.w/2;
	targetPosY = dot_rect.y + dot_rect.h/2 + 1;

	for (int i = 0; i < MAX_DOT_INVENTORY; ++i)
	{
		npc_dot_config.inventory_slots[i].inventory_item_code = INVENTORY_EMPTY_SLOT;
		npc_dot_config.inventory_slots[i].item_number = 0;
	}
}

void Dot::free()
{

}

void Dot::render(SDL_Renderer* gRenderer, Camera* camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{		 
	if (npc_dot_config.dot_mining_config.laser_on == true) Draw_Laser(gRenderer, camera, &dot_rect, &npc_dot_config.dot_mining_config.target_rect, npc_dot_config.dot_mining_config.laser_color);

	if (show_collision_box)
	{
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, new SDL_Rect{ dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, dot_rect.w, dot_rect.h });
	}
	
	if (npc_dot_config.dot_carried_item != NULL && npc_dot_config.dot_carried_item->carried_item.item_type != INVENTORY_TYPE_EMPTY)
	{
		npc_dot_config.dot_carried_item->render(gRenderer, camera);
	}

	if (npc_dot_config.dot_stat_health < npc_dot_config.dot_stat_max_health) 
	{
		render_status_bar(gRenderer, camera, npc_dot_config.dot_stat_health);
	}

}

void Dot::render_status_bar(SDL_Renderer* gRenderer, Camera* camera, int quantity_of_interest)
{
	SDL_Rect status_bar = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y -5, quantity_of_interest * TILE_WIDTH / 100, 2 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &status_bar);
}

void Dot::render_circle(SDL_Renderer* gRenderer, Camera* camera, int tile_x, int tile_y, int radius, int R, int G, int B, int alpha)
{
	int pos_x = tile_x*TILE_WIDTH + TILE_WIDTH / 2 - camera->camera_box.x;
	int pos_y = tile_y*TILE_HEIGHT + TILE_HEIGHT / 2 - camera->camera_box.y;

	SDL_SetRenderDrawColor(gRenderer, R, G, B, alpha);
	DrawCircle(gRenderer, pos_x, pos_y, radius*TILE_WIDTH);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
}

bool Dot::is_onscreen(Camera* camera, int buffer)
{
	bool onscreen = true;
	if (dot_rect.x < (camera->camera_box.x - TILE_WIDTH - buffer))
	{
		onscreen = false;
	}
	if (dot_rect.x >(camera->camera_box.x + camera->camera_box.w + TILE_WIDTH + buffer))
	{
		onscreen = false;
	}
	if (dot_rect.y < (camera->camera_box.y - TILE_HEIGHT - buffer))
	{
		onscreen = false;
	}
	if (dot_rect.y >(camera->camera_box.y + camera->camera_box.h + TILE_HEIGHT + buffer))
	{
		onscreen = false;
	}
	return onscreen;
}

void Dot::toggle_highlight(bool on_or_off)
{
	if (on_or_off == true)
	{
		npc_dot_config.dot_color.g = 155;
		npc_dot_config.dot_color.r = 155;
	}
	else
	{
		npc_dot_config.dot_color.g = 255;
		npc_dot_config.dot_color.r = 255;
	}
}

int Dot::getPosX()
{
	return dot_rect.x;
}

int Dot::getPosY()
{
	return dot_rect.y;
}

int Dot::getCenterPosX()
{
	return (dot_rect.x + dot_rect.w / 2);
}

int Dot::getCenterPosY()
{
	return (dot_rect.y + dot_rect.h / 2);
}

int Dot::getTileX()
{
	return ((getPosX() + (getWidth() / 2)) / TILE_WIDTH);
}

int Dot::getTileY()
{
	return ((getPosY() + (getHeight() / 2)) / TILE_HEIGHT);
}

int Dot::getWidth()
{
	return dot_rect.w;
}

int Dot::getHeight()
{
	return dot_rect.h;
}

int Dot::getCamera_x()
{
	return (getPosX() + getWidth() / 2) - SCREEN_WIDTH / 2;
}

int Dot::getCamera_y()
{
	return (getPosY() + getHeight() / 2) - SCREEN_HEIGHT / 2;
}

string Dot::print_coords()
{
	string coords;
	coords = to_string(getTileX()) + ", " + to_string(getTileY());
	return coords;
}

void Dot::respond_to_collision()
{
	// MANAGE DOOR COLLISIONS
	if (multi_tile_config.door_state == 2) multi_tile_config.door_state = 1;
	else if (multi_tile_config.door_state == 1) multi_tile_config.door_open_length = 0;
}


// HIGH-LEVEL DOT COMMANDS

string Dot::Create_Name()
{
	int num_letters = rand() % 5 + 5;

	string name;

	string consonants = "cdfghjklmnpqrstvwxyz";
	string capital_consonants = "CDFGHJKLMNPQRSTVWXYZ";
	string vowels = "aeiou";
	string capital_vowels = "AEOIU";

	int last_letter = 2;

	for (int i = 0; i < num_letters; i++)
	{
		char new_letter;
		int vowel_or_consonant = rand() % 2;

		if (last_letter == 0) vowel_or_consonant = 1;
		else if (last_letter == 1) vowel_or_consonant = 0;
		else vowel_or_consonant = rand() % 2;

		if (vowel_or_consonant == 1)
		{
			int letter = rand() % 19;
			if (i == 0) new_letter = capital_consonants[letter];
			else new_letter = consonants[letter];
			last_letter = 1;
		}
		else
		{
			int letter = rand() % 5;
			if (i == 0) new_letter = capital_vowels[letter];
			else new_letter = vowels[letter];
			last_letter = 0;
		}

		name.push_back(new_letter);
	}
	return name;

}

string Dot::Create_Dot_Name()
{
	string last_name = Create_Name();
	string first_name = Create_Name();
	string comma = ", ";

	last_name.push_back(comma[0]);
	last_name.push_back(comma[1]);
	for (int i = 0; i < first_name.size(); i++)
	{
		last_name.push_back(first_name[i]);
	}

	return last_name;
}

void Dot::Set_Carried_item(SDL_Renderer* gRenderer, LTexture* inventory_spritesheet, int carried_item_type)
{
	npc_dot_config.dot_carried_item = new Carried_Multi_Tile(gRenderer, inventory_spritesheet, &dot_rect.x, &dot_rect.y, carried_item_type);
}

void Dot::Create_Default_Dot_Priorities()
{
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_WEAPON_COOLDOWN, { DOT_PRIORITY_WEAPON_COOLDOWN,0,0,0,1,0,20 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_OXYGEN_NEED, { DOT_PRIORITY_OXYGEN_NEED, 0,0,50,100,0,1 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_SLEEP_NEED, { DOT_PRIORITY_SLEEP_NEED, 0,0,50,100,0,300 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_HUNGER_NEED, { DOT_PRIORITY_HUNGER_NEED, 0,0,50,100,0,200 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_SPACESUIT_OXYGEN, { DOT_PRIORITY_SPACESUIT_OXYGEN, 100,0,50,100,0,100 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_ENNUI, { DOT_PRIORITY_ENNUI, 0,0,50,100,0,200 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_HAPPINESS, { DOT_PRIORITY_HAPPINESS, 100,0,50,100,0,100 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_SANITY, { DOT_PRIORITY_SANITY, 100,0,50,100,0,100 }));
}

// CRAFTING COMMANDS

void Dot::Check_Craftable_Items()
{
	npc_dot_config.craftable_items.clear();
	
	for (int i = 0; i < tile_vector.size(); i++)
	{
		int craftable_amount = Check_How_Much_Dot_Can_Craft_Of_Item(tile_vector[i]);
		if (craftable_amount > 0)
		{
			npc_dot_config.craftable_items.push_back(Dot_Inventory_Slot{ tile_vector[i].inventory_pointer,craftable_amount });
		}
	}
}

int Dot::Check_How_Much_Dot_Can_Craft_Of_Item(Multi_Tile_Type tile_type)
{
	int lowest_craftable_quantity = 99;

	Building_Spec item_spec = tile_type.building_specs;

	if (item_spec.Requirement_1.inventory_requirement != INVENTORY_EMPTY_SLOT) if ((Check_Inventory_For_Item(item_spec.Requirement_1.inventory_requirement) / item_spec.Requirement_1.requirement_quantity) < lowest_craftable_quantity) lowest_craftable_quantity = (Check_Inventory_For_Item(item_spec.Requirement_1.inventory_requirement) / item_spec.Requirement_1.requirement_quantity);
	if (item_spec.Requirement_2.inventory_requirement != INVENTORY_EMPTY_SLOT) if ((Check_Inventory_For_Item(item_spec.Requirement_2.inventory_requirement) / item_spec.Requirement_2.requirement_quantity) < lowest_craftable_quantity) lowest_craftable_quantity = (Check_Inventory_For_Item(item_spec.Requirement_2.inventory_requirement) / item_spec.Requirement_2.requirement_quantity);
	if (item_spec.Requirement_3.inventory_requirement != INVENTORY_EMPTY_SLOT) if ((Check_Inventory_For_Item(item_spec.Requirement_3.inventory_requirement) / item_spec.Requirement_3.requirement_quantity) < lowest_craftable_quantity) lowest_craftable_quantity = (Check_Inventory_For_Item(item_spec.Requirement_3.inventory_requirement) / item_spec.Requirement_3.requirement_quantity);
	if (item_spec.Requirement_4.inventory_requirement != INVENTORY_EMPTY_SLOT) if ((Check_Inventory_For_Item(item_spec.Requirement_4.inventory_requirement) / item_spec.Requirement_4.requirement_quantity) < lowest_craftable_quantity) lowest_craftable_quantity = (Check_Inventory_For_Item(item_spec.Requirement_4.inventory_requirement) / item_spec.Requirement_4.requirement_quantity);
	if (item_spec.Requirement_5.inventory_requirement != INVENTORY_EMPTY_SLOT) if ((Check_Inventory_For_Item(item_spec.Requirement_5.inventory_requirement) / item_spec.Requirement_5.requirement_quantity) < lowest_craftable_quantity) lowest_craftable_quantity = (Check_Inventory_For_Item(item_spec.Requirement_5.inventory_requirement) / item_spec.Requirement_5.requirement_quantity);
	if (item_spec.Requirement_6.inventory_requirement != INVENTORY_EMPTY_SLOT) if ((Check_Inventory_For_Item(item_spec.Requirement_6.inventory_requirement) / item_spec.Requirement_6.requirement_quantity) < lowest_craftable_quantity) lowest_craftable_quantity = (Check_Inventory_For_Item(item_spec.Requirement_6.inventory_requirement) / item_spec.Requirement_6.requirement_quantity);

	return lowest_craftable_quantity;
}

// INVENTORY_COMMANDS

int Dot::Check_Inventory_For_Item(int inventory_item_code)
{
	int inventory_count = 0;
	for (int i = 0; i < MAX_DOT_INVENTORY; i++)
	{
		if (npc_dot_config.inventory_slots[i].inventory_item_code == inventory_item_code)
		{
			inventory_count = inventory_count + npc_dot_config.inventory_slots[i].item_number;
		}
	}
	return inventory_count;
}

Inventory_Item Dot::Check_Inventory_For_Item_Type(int item_type)
{
	for (int i = 0; i < MAX_DOT_INVENTORY; i++)
	{
		if (npc_dot_config.inventory_slots[i].inventory_item_code == item_type)
		{
			return Fetch_Inventory(npc_dot_config.inventory_slots[i].inventory_item_code);
		}
	}
	return Fetch_Inventory(INVENTORY_NULL_ITEM);
}

void Dot::Return_Parts_List(Multi_Tile_Type tile_type)
{
	if (tile_type.building_specs.Requirement_1.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_1.inventory_requirement, tile_type.building_specs.Requirement_1.requirement_quantity});
	if (tile_type.building_specs.Requirement_2.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_2.inventory_requirement, tile_type.building_specs.Requirement_2.requirement_quantity});
	if (tile_type.building_specs.Requirement_3.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_3.inventory_requirement, tile_type.building_specs.Requirement_3.requirement_quantity});
	if (tile_type.building_specs.Requirement_4.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_4.inventory_requirement, tile_type.building_specs.Requirement_3.requirement_quantity});
	if (tile_type.building_specs.Requirement_5.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_5.inventory_requirement, tile_type.building_specs.Requirement_4.requirement_quantity});
	if (tile_type.building_specs.Requirement_6.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_6.inventory_requirement, tile_type.building_specs.Requirement_5.requirement_quantity});
}

bool Dot::Check_If_Tile_Needs_Parts(Multi_Tile_Type tile_type)
{
	
	bool needs_parts = false;
	if (tile_type.building_specs.Requirement_1.inventory_requirement != INVENTORY_EMPTY_SLOT && Check_Inventory_For_Item(tile_type.building_specs.Requirement_1.inventory_requirement) < tile_type.building_specs.Requirement_1.requirement_quantity) needs_parts = true;
	else if (tile_type.building_specs.Requirement_2.inventory_requirement != INVENTORY_EMPTY_SLOT && Check_Inventory_For_Item(tile_type.building_specs.Requirement_2.inventory_requirement) < tile_type.building_specs.Requirement_2.requirement_quantity) needs_parts = true;
	else if (tile_type.building_specs.Requirement_3.inventory_requirement != INVENTORY_EMPTY_SLOT && Check_Inventory_For_Item(tile_type.building_specs.Requirement_3.inventory_requirement) < tile_type.building_specs.Requirement_3.requirement_quantity) needs_parts = true;
	else if (tile_type.building_specs.Requirement_4.inventory_requirement != INVENTORY_EMPTY_SLOT && Check_Inventory_For_Item(tile_type.building_specs.Requirement_4.inventory_requirement) < tile_type.building_specs.Requirement_4.requirement_quantity) needs_parts = true;
	else if (tile_type.building_specs.Requirement_5.inventory_requirement != INVENTORY_EMPTY_SLOT && Check_Inventory_For_Item(tile_type.building_specs.Requirement_5.inventory_requirement) < tile_type.building_specs.Requirement_5.requirement_quantity) needs_parts = true;
	else if (tile_type.building_specs.Requirement_6.inventory_requirement != INVENTORY_EMPTY_SLOT && Check_Inventory_For_Item(tile_type.building_specs.Requirement_6.inventory_requirement) < tile_type.building_specs.Requirement_6.requirement_quantity) needs_parts = true;
	return needs_parts;
}

bool Dot::Check_if_Dot_Has_All_Needed_Scaffold_Parts(Dot* dot, Multi_Tile_Type tile_type)
{
	bool has_parts = true;
	if (tile_type.building_specs.Requirement_1.inventory_requirement != INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(tile_type.building_specs.Requirement_1.inventory_requirement) < tile_type.building_specs.Requirement_1.requirement_quantity) has_parts = false;
	else if (tile_type.building_specs.Requirement_2.inventory_requirement != INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(tile_type.building_specs.Requirement_2.inventory_requirement) < tile_type.building_specs.Requirement_2.requirement_quantity) has_parts = false;
	else if (tile_type.building_specs.Requirement_3.inventory_requirement != INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(tile_type.building_specs.Requirement_3.inventory_requirement) < tile_type.building_specs.Requirement_3.requirement_quantity) has_parts = false;
	else if (tile_type.building_specs.Requirement_4.inventory_requirement != INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(tile_type.building_specs.Requirement_4.inventory_requirement) < tile_type.building_specs.Requirement_4.requirement_quantity) has_parts = false;
	else if (tile_type.building_specs.Requirement_5.inventory_requirement != INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(tile_type.building_specs.Requirement_5.inventory_requirement) < tile_type.building_specs.Requirement_5.requirement_quantity) has_parts = false;
	else if (tile_type.building_specs.Requirement_6.inventory_requirement != INVENTORY_EMPTY_SLOT && dot->Check_Inventory_For_Item(tile_type.building_specs.Requirement_6.inventory_requirement) < tile_type.building_specs.Requirement_6.requirement_quantity) has_parts = false;
	return has_parts;
}

void Dot::Check_if_Dot_Can_Pop_Tile_List_Items()
{
	for (int i = 0; i < npc_dot_config.tile_parts_list.size(); i++)
	{
		if (Check_Inventory_For_Item(npc_dot_config.tile_parts_list[i].inventory_item_code) >= npc_dot_config.tile_parts_list[i].item_number)
		{
			cout << "erasing item on list" << endl;
			npc_dot_config.tile_parts_list.erase(npc_dot_config.tile_parts_list.begin() + i);
		}
	}
}

vector<Dot_Inventory_Slot> Dot::return_inventory_as_vector()
{
	vector<Dot_Inventory_Slot> temp_vector;
	for (int i = 0; i < MAX_DOT_INVENTORY; i++) if (npc_dot_config.inventory_slots[i].item_number > 0)
	{
		temp_vector.push_back({ npc_dot_config.inventory_slots[i].inventory_item_code, npc_dot_config.inventory_slots[i].item_number });
	}
	return temp_vector;
}



// GOAL_COMMANDS

void Dot::dot_wipe_goals()
{
	//cout << "trying to wipe goals list of lenght: " << current_goal_list.size() << endl;
	if (npc_dot_config.current_goal_list.size() != 0)
	{
		//cout << "successfully able to wipe goals list" << endl;
		npc_dot_config.current_goal_list.erase(npc_dot_config.current_goal_list.begin(), npc_dot_config.current_goal_list.begin() + npc_dot_config.current_goal_list.size());
	}
}

void Dot::dot_wipe_current_path()
{
	if (npc_dot_config.current_goal_path.size() != 0) npc_dot_config.current_goal_path.erase(npc_dot_config.current_goal_path.begin(), npc_dot_config.current_goal_path.begin() + npc_dot_config.current_goal_path.size());
}

void Dot::dot_wipe_all_job_tasks()
{
	//cout << "wiping all job tasks" << endl;
	dot_wipe_goals();
	dot_wipe_current_path();
	npc_dot_config.current_dot_focus == NULL;
}


#include <Dot_Job.h>


struct clip_and_rotation
{
	SDL_Rect rect;
	SDL_Rect clip;
	double angle;
	SDL_RendererFlip flip;
	int render_layer = RENDER_ITEMS;
};

// TILE 

class Tile : public Dot
{
public:
	//Initializes the variables
	Tile(SDL_Renderer* gRenderer = NULL, LTexture* tile_texture = NULL, int x_coordinate = NULL, int y_coordinate = NULL, Multi_Tile_Type multi_config = Return_Tile_By_Name(TILE_GENERIC_TILE)) :Dot(gRenderer, tile_texture, x_coordinate, y_coordinate)
	{
		multi_tile_config = multi_config;
		dot_rect = { x_coordinate * TILE_WIDTH,y_coordinate * TILE_HEIGHT,TILE_WIDTH*multi_config.sprite_specs.rect_columns, TILE_HEIGHT*multi_config.sprite_specs.rect_rows };
		mTexture = tile_texture;

		int render_offset_x = 0;
		int render_offset_y = 0;

		if (multi_config.sprite_specs.sprite_rows < 0)  render_offset_y = multi_config.sprite_specs.sprite_rows/2;
		if (multi_config.sprite_specs.sprite_columns < 0)  render_offset_x = multi_config.sprite_specs.sprite_columns/2;

		render_rect =  { (x_coordinate + render_offset_x)*TILE_WIDTH,(y_coordinate + render_offset_y)*TILE_HEIGHT, (TILE_WIDTH*abs(multi_tile_config.sprite_specs.sprite_columns)), (TILE_HEIGHT*abs(multi_tile_config.sprite_specs.sprite_rows)) };
		current_clip = { (1 + multi_tile_config.sprite_specs.sprite_column*SPRITESHEET_W),(1 + multi_tile_config.sprite_specs.sprite_row*SPRITESHEET_H) + SPRITESHEET_H * tile_orientation, (TILE_WIDTH*abs(multi_tile_config.sprite_specs.sprite_columns)), (TILE_HEIGHT*abs(multi_tile_config.sprite_specs.sprite_rows)) };
		
		dot_config[DOT_TYPE] = DOT_TILE;
		item_job_type = multi_config.item_job_type;
		item_job = Dot_Job{ item_job_type };

		x_tile = getTileX();
		y_tile = getTileY();

		if (multi_config.built_percent < 100) Return_Parts_List(multi_config);

		if (multi_tile_config.is_smooth == 1) handle_smooth_tiles(2, 2, 2, 2, 2, 2, 2, 2);

	}

	//Shows the Tile on the screen
	bool is_onscreen(Camera* camera);
	void update_texture_clip(int clip_row_x, int clip_row_y);
	virtual void render(SDL_Renderer* gRenderer, Camera* camera, int render_layer);
	void Tile::change_door_orientation();
	void Tile::handle_door_animation();
	void Tile::handle_animation();
	void Tile::handle_floor_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_smooth_tiles(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_wall_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_door_orientation(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_frenzel_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	
	void Tile::Set_Color(Uint8 R, Uint8 G, Uint8 B);

	// The tile's position on the screen
	SDL_Rect* Tile::get_tile_rect(bool camera_rect = false);

	clip_and_rotation Tile::Create_Clip_And_Rotation(int base_sprite_x, int base_sprite_y, int offset_tile_x, int offset_tile_y, int component_x, int component_y, double rotation, SDL_RendererFlip flip = SDL_FLIP_NONE, int render_layer = RENDER_TILES);

	SDL_Rect current_clip;

	vector<clip_and_rotation> multi_clip;
	SDL_Rect render_rect;
	SDL_Rect status_bar;
	SDL_Rect construction_bar;


	// set initially not as an animated item
	int animation_ticker = 0;
	int max_animation_ticker = 32;
	int tile_orientation = 0;

	// Item Jobs
	int item_job_type;
	Dot_Job item_job;



private:

	SDL_Rect dot_rect_camera;

	//Set Texture Color Mods
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;

	//The tile's hardware texture and clip from sprite_sheet
	LTexture* mTexture;
};

void Tile::update_texture_clip(int clip_column, int clip_row)
{
	current_clip.x = 1 + clip_column*SPRITESHEET_W;
	current_clip.y = 1 + clip_row*SPRITESHEET_H;
}

SDL_Rect* Tile::get_tile_rect(bool camera_rect)
{
	if (!camera_rect)
	{
		return &dot_rect;
	}
	else
	{
		return &dot_rect_camera;
	}
}

void Tile::change_door_orientation()
{

}

bool Tile::is_onscreen(Camera* camera)
{
	bool onscreen = true;
	if (dot_rect.x < (camera->camera_box.x - TILE_WIDTH))
	{
		onscreen = false;
	}
	if (dot_rect.x >(camera->camera_box.x + camera->camera_box.w + TILE_WIDTH))
	{
		onscreen = false;
	}
	if (dot_rect.y < (camera->camera_box.y - TILE_HEIGHT))
	{
		onscreen = false;
	}
	if (dot_rect.y >(camera->camera_box.y + camera->camera_box.h + TILE_HEIGHT))
	{
		onscreen = false;
	}
	return onscreen;
}

void Tile::render(SDL_Renderer* gRenderer, Camera* camera, int render_layer)
{
	if (multi_tile_config.is_animated > 0) handle_animation();

	dot_rect_camera.x = render_rect.x - camera->camera_box.x;
	dot_rect_camera.y = render_rect.y - camera->camera_box.y;
	dot_rect_camera.w = render_rect.w;
	dot_rect_camera.h = render_rect.h;

	//Render to screen

	if (multi_tile_config.built_percent < 100)
	{
		mTexture->setAlpha(50);
		mTexture->setColor(0, 255, 200);
		render_status_bar(gRenderer, camera, multi_tile_config.built_percent);
	}
	else
	{
		mTexture->setColor(npc_dot_config.dot_color.r - multi_tile_config.is_oxygenated * 10, npc_dot_config.dot_color.g - multi_tile_config.is_oxygenated * 10, npc_dot_config.dot_color.b);
	}


	SDL_Rect render_clip = { current_clip.x, current_clip.y + tile_orientation * SPRITESHEET_H, current_clip.w, current_clip.h };
	if (multi_tile_config.tile_type == ITEM_TYPE_EMITTER) render_circle(gRenderer, camera, getTileX(), getTileY(), 5, 255, 0, 0, 50);

	SDL_Point rotate_angle{ 16,16 };
	
	if ((multi_tile_config.is_smooth == 0 || multi_tile_config.door_state >=1 ) && multi_tile_config.render_layer == render_layer) mTexture->render(gRenderer, &dot_rect_camera, &render_clip);
	else
	{

		for (int i = 0; i < multi_clip.size(); i++)
		{
			SDL_Rect draw_rect = { multi_clip[i].rect.x - camera->camera_box.x ,multi_clip[i].rect.y - camera->camera_box.y ,TILE_WIDTH,TILE_HEIGHT };
			if (multi_clip[i].render_layer == render_layer) mTexture->render(gRenderer, &draw_rect, &multi_clip[i].clip, multi_clip[i].angle, &rotate_angle, multi_clip[i].flip);
		}
	}

	
	if (npc_dot_config.dot_carried_item != NULL && npc_dot_config.dot_carried_item->carried_item.item_code != INVENTORY_EMPTY_SLOT)
	{
		npc_dot_config.dot_carried_item->render(gRenderer, camera);
	}
	
	if (npc_dot_config.dot_stat_health < 100) render_status_bar(gRenderer, camera, npc_dot_config.dot_stat_health);
	if (npc_dot_config.production_current > 0) render_status_bar(gRenderer, camera, npc_dot_config.production_current);

	mTexture->setAlpha(255);
	mTexture->setColor(255, 255, 255);

	// RESET CYCLICAL TILE PROPERTIES
	multi_tile_config.leak_check = 0;
	multi_tile_config.oxygenation_check = 0;
	multi_tile_config.is_oxygenated = 0;
	npc_dot_config.dot_color = { 255,255,255,255 };
}

void Tile::Set_Color(Uint8 R, Uint8 G, Uint8 B)
{
	r = R;
	g = G;
	b = B;
}

void Tile::handle_animation()
{
	if (multi_tile_config.door_state > 0)
	{
		handle_door_animation();
		return;
	}

	int animation_clip_offset_x = multi_tile_config.sprite_specs.sprite_columns * SPRITESHEET_W;
	int animation_frames = multi_tile_config.is_animated;

	animation_ticker++;
	if (animation_ticker >= max_animation_ticker) animation_ticker = 0;

	current_clip.x = (1+ animation_clip_offset_x*(animation_ticker / (max_animation_ticker/animation_frames)));

}

void Tile::handle_door_animation()
{
	int animation_clip_offset_x = multi_tile_config.sprite_specs.sprite_columns * SPRITESHEET_W;
	int animation_frames = multi_tile_config.is_animated;

	if (multi_tile_config.door_state == 1)
	{
		animation_ticker++;
		if (animation_ticker >= max_animation_ticker) animation_ticker = max_animation_ticker -1;

		current_clip.x = (1+ animation_clip_offset_x*(animation_ticker / (max_animation_ticker / animation_frames)));
	}

	else if (multi_tile_config.door_state == 2 && animation_ticker > 0)
	{
		animation_ticker--;
		if (animation_ticker <= 0) animation_ticker = 0;
		current_clip.x = (1 + animation_clip_offset_x*(animation_ticker / (max_animation_ticker / animation_frames)));
	}

	if (animation_ticker > max_animation_ticker/2)
	{
		multi_tile_config.is_collidable = 0;
	}
	else multi_tile_config.is_collidable = 1;
}

void Tile::handle_smooth_tiles(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	switch (multi_tile_config.tile_type)
	{
		case TILE_TYPE_CONSTRUCTION_TUBING_WALL:
			handle_wall_tiling(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			break;
		case TILE_TYPE_CONSTRUCTION_TUBING_DOOR:
			handle_door_orientation(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			break;
		case TILE_TYPE_CONSTRUCTION_TUBING_FLOOR:
			handle_floor_tiling(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			break;
		case TILE_TYPE_FRENZEL:
			handle_frenzel_tiling(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			break;
	}
}

void Tile::handle_wall_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	multi_clip.clear();

	int x = multi_tile_config.sprite_specs.sprite_column;
	int y = multi_tile_config.sprite_specs.sprite_row;

	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) left_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) right_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) top_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) bottom_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) top_left_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) top_right_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) bottom_right_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	if (bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_DOOR) bottom_left_edge = TILE_TYPE_CONSTRUCTION_TUBING_WALL;
	
	// FLAT UNBROKEN WALL PIECES
	// VERTICAL EXTERIOR
	if (left_edge == VACUUM && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	if (left_edge == VACUUM && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_VERTICAL));
	if (right_edge == VACUUM && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_HORIZONTAL));
	if (right_edge == VACUUM && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 180, SDL_FLIP_NONE));

	// VERTICAL INTERIOR
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_VERTICAL));
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_HORIZONTAL));
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 180, SDL_FLIP_NONE));

	// HORIZONTAL EXTERIOR
	if (bottom_edge == VACUUM && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 1, 0, SDL_FLIP_NONE));
	if (bottom_edge == VACUUM && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 1, 0, SDL_FLIP_HORIZONTAL));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));

	if ((top_edge == VACUUM || top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_HORIZONTAL));
	if ((top_edge == VACUUM || top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_NONE));


	// CORNER PIECES
	// EXTERIOR
	if (bottom_edge == VACUUM && left_edge == VACUUM && (bottom_left_edge == VACUUM || bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL))
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 0, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 0, SDL_FLIP_NONE));
	}
	if (bottom_edge == VACUUM && right_edge == VACUUM && (bottom_right_edge == VACUUM || bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL))
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 0, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 0, SDL_FLIP_HORIZONTAL));
	}
	if (top_edge == VACUUM && left_edge == VACUUM && (top_left_edge == VACUUM || top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL))
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_VERTICAL));
	}
	if (top_edge == VACUUM && right_edge == VACUUM && (top_right_edge == VACUUM || top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL))
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 180, SDL_FLIP_NONE));
	}
	// INTERIOR
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && (top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 1, 90, SDL_FLIP_NONE));
	}
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && (top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 1, 90, SDL_FLIP_VERTICAL));
	}
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && (bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 0, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
	}
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && (bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 0, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));
	}
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_HORIZONTAL));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_NONE));

	// T-BARS
	if ((top_edge == VACUUM || top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_VERTICAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 180, SDL_FLIP_NONE));
	}
	if ((bottom_edge == VACUUM || bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_HORIZONTAL));
	}

	// MISC CORNERS
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && (bottom_right_edge == VACUUM || bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 180, SDL_FLIP_NONE));
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && (bottom_left_edge == VACUUM || bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_VERTICAL));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_VERTICAL));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 180, SDL_FLIP_NONE));

	// OVERLAY ACCOUTREMENT
	if ((left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) && bottom_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	}

	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 2, 0, SDL_FLIP_NONE));

	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL && (right_edge != VACUUM && left_edge != VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
	if ((left_edge == VACUUM && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 2, 0, SDL_FLIP_NONE));
	if ((right_edge == VACUUM && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 2, 0, SDL_FLIP_NONE));
	if (top_edge == VACUUM && left_edge == VACUUM && (top_left_edge == VACUUM || top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 2, 0, SDL_FLIP_NONE));
	if (top_edge == VACUUM && right_edge == VACUUM && (top_right_edge == VACUUM || top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 2, 0, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 2, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 2, 0, SDL_FLIP_NONE));
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 2, 0, SDL_FLIP_NONE));

	// SOLO TILES
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	}
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	}

	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	}

}

void Tile::handle_floor_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	multi_clip.clear();

	int x = multi_tile_config.sprite_specs.sprite_column;
	int y = multi_tile_config.sprite_specs.sprite_row;

	for (int i = 0; i < 4; i++)
	{
		int offset_x = rand() % 2;
		int offset_y = rand() % 2;
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, offset_x, offset_y, i*90, SDL_FLIP_NONE));

	}

	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_VERTICAL));

}

void Tile::handle_door_orientation(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		tile_orientation = 1;
	}
	else if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		tile_orientation = 0;
	}
}

void Tile::handle_frenzel_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	int x = multi_tile_config.sprite_specs.sprite_column;
	int y = multi_tile_config.sprite_specs.sprite_row;

	if (left_edge != TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL && bottom_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 1, 0, SDL_FLIP_NONE));
	if (left_edge == TILE_TYPE_FRENZEL && right_edge == TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 2, 0, SDL_FLIP_NONE));

	// SINGLE FRONDS
	else if (left_edge == TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL && bottom_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 2, 0, SDL_FLIP_NONE));
	else if (right_edge == TILE_TYPE_FRENZEL && left_edge != TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL && bottom_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 3, 0, SDL_FLIP_NONE));
	else if (top_edge == TILE_TYPE_FRENZEL && left_edge != TILE_TYPE_FRENZEL && bottom_edge != TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
	else if (bottom_edge == TILE_TYPE_FRENZEL && left_edge != TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_NONE));

	// CORNERS
	else if (left_edge != TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL && right_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 0, SDL_FLIP_NONE));
	else if (right_edge != TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL && left_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_NONE));
	else if (bottom_edge != TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL && left_edge == TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 3, 0, SDL_FLIP_NONE));
	else if (bottom_edge != TILE_TYPE_FRENZEL && left_edge != TILE_TYPE_FRENZEL && right_edge == TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 3, 0, SDL_FLIP_NONE));

	// STRAIGHT EDGES
	else if (left_edge != TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 0, SDL_FLIP_NONE));
	else if (top_edge != TILE_TYPE_FRENZEL && bottom_edge != TILE_TYPE_FRENZEL && left_edge == TILE_TYPE_FRENZEL && right_edge == TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 0, 0, SDL_FLIP_NONE));
	
	// T-BARS
	else if (right_edge == TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL && left_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
	else if (left_edge == TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL && right_edge != TILE_TYPE_FRENZEL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));

	else if (left_edge == TILE_TYPE_FRENZEL && bottom_edge == TILE_TYPE_FRENZEL && right_edge == TILE_TYPE_FRENZEL && top_edge != TILE_TYPE_FRENZEL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	else if (left_edge == TILE_TYPE_FRENZEL && top_edge == TILE_TYPE_FRENZEL && right_edge == TILE_TYPE_FRENZEL && bottom_edge != TILE_TYPE_FRENZEL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 3, 0, SDL_FLIP_NONE));
}

clip_and_rotation Tile::Create_Clip_And_Rotation(int base_sprite_x, int base_sprite_y, int offset_tile_x, int offset_tile_y, int component_x, int component_y, double rotation, SDL_RendererFlip flip, int render_layer)
{
	clip_and_rotation new_clip_rotate = { {dot_rect.x + offset_tile_x*TILE_WIDTH,dot_rect.y + offset_tile_y*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT}, {base_sprite_x*SPRITESHEET_W + component_x*SPRITESHEET_W + 1, base_sprite_y*SPRITESHEET_H + component_y*SPRITESHEET_H + 1,TILE_WIDTH,TILE_HEIGHT}, rotation, flip,render_layer };
	return new_clip_rotate;
}


// PLAYER AND NPC DOTS

class NPC_Dot : public Dot
{
public:
	NPC_Dot(SDL_Renderer* gRenderer, LTexture* dot_spritesheet_array[], int x_pos, int y_pos, dot_composite_config dot_makeup) :Dot(gRenderer, dot_spritesheet_array[0], x_pos, y_pos)
	{
		dot_spritesheet[0] = dot_spritesheet_array[0];
		dot_spritesheet[1] = dot_spritesheet_array[1];
		dot_spritesheet[2] = dot_spritesheet_array[2];
		dot_spritesheet[3] = dot_spritesheet_array[3];
		dot_spritesheet[4] = dot_spritesheet_array[4];
		dot_spritesheet[5] = dot_spritesheet_array[5];

		create_sprite(dot_makeup.leg_type,dot_makeup.arm_type,dot_makeup.torso_type, dot_makeup.head_type, dot_makeup.spacesuit_type);

		change_sprite_direction(3);
		
		dot_config[DOT_TYPE] = DOT_NPC;
		npc_dot_config.dot_last_name = Create_Name();
		npc_dot_config.dot_first_name = Create_Name();
		npc_dot_config.dot_full_name = npc_dot_config.dot_last_name + ", " + npc_dot_config.dot_first_name;

		dot_rect.w = TILE_WIDTH * 3 / 4;
		dot_rect.h = TILE_HEIGHT * 2 / 4;
		rect_offset_x = -5;
		rect_offset_y = -20;

		Create_Default_Dot_Priorities();

		for (int i = 0; i < tile_vector.size(); i++)
		{
			npc_dot_config.craftable_items.push_back(Dot_Inventory_Slot{ tile_vector[i].inventory_pointer,1 });
		}
	}

	void render(SDL_Renderer* gRenderer, Camera* camera);
	void render_component(SDL_Renderer* gRenderer, Camera* camera, int component);
	void increment_animation();
	void create_sprite(int leg_type, int arm_type, int torso_type, int head_type, int spacesuit_type);
	void change_sprite_direction(int direction);
	void animate_movement(int previous_mPosX, int previous_mPosY);
	void set_velocity();
	void set_direction();

	struct dot_multi_clip
	{
		int animation_row = 0;
		int animation_column = 0;
		int max_frames = 1;
		int current_frame = 0;
		SDL_Rect sprite_specs = { 0,0,32,32 };
		float sprite_scale_x = 1;
		float sprite_scale_y = 1;
		int current_frame_delay = 0;
		int max_frame_delay = 10;
	};

	SDL_Rect clip_rect;
	SDL_Rect render_rect;
	int rect_offset_x;
	int rect_offset_y;
	unordered_map <int, dot_multi_clip> dot_composite;

	Dot_Job dot_current_job;
	Dot_Job dot_personal_ai;

	void set_player_velocity(bool x_or_y, int quantity);
	int texture_change_distance_x = 2;
	int texture_change_distance_y = 2;

	int bounce_delay = 0;
	int max_bounce_delay = 2;
	int bounce = 0;
	int bounce_direction = 1;

	int shadow_offset = 0;

private:
	LTexture* dot_spritesheet[6];

};

void NPC_Dot::set_player_velocity(bool x_or_y, int quantity)
{
	if (x_or_y)
	{
		mVelX = quantity;
	}
	else
	{
		mVelY = quantity;
	}
}

void NPC_Dot::create_sprite(int leg_type, int arm_type, int torso_type, int head_type, int spacesuit_type)
{
	dot_composite.insert({ DOT_COMPOSITE_LEGS, { 0,leg_type*5,5,0,{0,0,32,32},1,1,0,5 } });
	dot_composite.insert({ DOT_COMPOSITE_ARMS,{ 0,arm_type*5,5,0,{ 0,0,32,32 },1,1,0,5 } });
	dot_composite.insert({ DOT_COMPOSITE_TORSO, { 0,torso_type,1,0,{ 0,0,32,32 },1,1,0,5} });
	dot_composite.insert({ DOT_COMPOSITE_HEAD,{0,head_type,1,0,{ 0,0,32,32 },1,1,0,5 } });
	dot_composite.insert({ DOT_COMPOSITE_SPACESUIT,{ 0,spacesuit_type*5,5,0,{ 0,0,32,32 },1,1,0,5 } });
}

void NPC_Dot::change_sprite_direction(int direction)
{
	dot_composite[DOT_COMPOSITE_LEGS].animation_row = direction;
	dot_composite[DOT_COMPOSITE_ARMS].animation_row = direction;
	dot_composite[DOT_COMPOSITE_TORSO].animation_row = direction;
	dot_composite[DOT_COMPOSITE_HEAD].animation_row = direction;
	dot_composite[DOT_COMPOSITE_SPACESUIT].animation_row = direction;
}

void NPC_Dot::render(SDL_Renderer* gRenderer, Camera* camera)
{
	dot_spritesheet[0]->setColor(npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);
	dot_spritesheet[1]->setColor(npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);
	dot_spritesheet[2]->setColor(npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);
	dot_spritesheet[3]->setColor(npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);
	dot_spritesheet[4]->setColor(npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);
	
	dot_spritesheet[5]->render(gRenderer, new SDL_Rect{ dot_rect.x + rect_offset_x - camera->camera_box.x, dot_rect.y + rect_offset_y - camera->camera_box.y + bounce + shadow_offset, TILE_WIDTH, TILE_HEIGHT }, new SDL_Rect{ 0,0,32,32 });

	if (npc_dot_config.dot_equipment_config.Spacesuit.item_number == 1) render_component(gRenderer, camera, DOT_COMPOSITE_SPACESUIT);
	else
	{
		render_component(gRenderer, camera, DOT_COMPOSITE_LEGS);
		render_component(gRenderer, camera, DOT_COMPOSITE_TORSO);
		render_component(gRenderer, camera, DOT_COMPOSITE_ARMS);
		render_component(gRenderer, camera, DOT_COMPOSITE_HEAD);
	}

	dot_spritesheet[0]->setColor(255, 255, 255);
	dot_spritesheet[1]->setColor(255, 255, 255);
	dot_spritesheet[2]->setColor(255, 255, 255);
	dot_spritesheet[3]->setColor(255, 255, 255);
	dot_spritesheet[4]->setColor(255, 255, 255);

	Dot::render(gRenderer, camera);

	if (npc_dot_config.bounce == 1)
	{
		bounce_delay++;
		if (bounce_delay > max_bounce_delay) bounce_delay = 0;
		if (bounce_delay == 0)
		{
			bounce += bounce_direction;
			if (bounce > 3) bounce_direction = -1;
			if (bounce < -3) bounce_direction = 1;
		}
	}
}

void NPC_Dot::render_component(SDL_Renderer* gRenderer, Camera* camera, int component)
{
	SDL_Rect sprite_specs = dot_composite[component].sprite_specs;
	int current_frame = dot_composite[component].current_frame;
	int animation_row = dot_composite[component].animation_row;
	int animation_column = dot_composite[component].animation_column;

	clip_rect = { sprite_specs.x + (animation_column + current_frame)*sprite_specs.w, sprite_specs.y + animation_row*sprite_specs.h, sprite_specs.w, sprite_specs.h };
	render_rect = { dot_rect.x + rect_offset_x - camera->camera_box.x, dot_rect.y + rect_offset_y- camera->camera_box.y + bounce, TILE_WIDTH, TILE_HEIGHT };
	dot_spritesheet[component]->render(gRenderer, &render_rect, &clip_rect,npc_dot_config.dot_angle);
}

void NPC_Dot::increment_animation()
{
	for (int i = 0; i < dot_composite.size(); i++)
	{
		if (dot_composite[i].current_frame_delay == 0)
		{
			dot_composite[i].current_frame++;
			if (dot_composite[i].current_frame >= dot_composite[i].max_frames) dot_composite[i].current_frame = 0;
		}
		
		dot_composite[i].current_frame_delay++;
		if (dot_composite[i].current_frame_delay >= dot_composite[i].max_frame_delay) dot_composite[i].current_frame_delay = 0;
	}
}

void NPC_Dot::animate_movement(int previous_mPosX, int previous_mPosY)
{
	delta_x += (dot_rect.x - previous_mPosX);
	delta_y += (dot_rect.y - previous_mPosY);

	if (abs(delta_x) > abs(delta_y))
	{
		if (delta_x > 0)
		{
			change_sprite_direction(0);
		}
		if (delta_x < 0)
		{
			change_sprite_direction(1);
		}
	}

	if (abs(delta_y) > abs(delta_x))
	{
		if (delta_y > 0)
		{
			change_sprite_direction(2);
		}
		if (delta_y < 0)
		{
			change_sprite_direction(3);
		}
	}

	if (abs(delta_x) > texture_change_distance_x)
	{
		increment_animation();
		delta_x = 0;
	}

	if (abs(delta_y) > texture_change_distance_y)
	{
		increment_animation();
		delta_y = 0;
	}
}

void NPC_Dot::set_velocity()
{
	distance_x = targetPosX - (dot_rect.x + dot_rect.w / 2);
	distance_y = targetPosY - (dot_rect.y + dot_rect.h / 2);

	if (distance_x == 0)
	{
		mVelX = 0;
	}
	else if (distance_x > 3)
	{
		mVelX = npc_dot_config.dot_stat_speed;
	}
	else if (distance_x < -3)
	{
		mVelX = -npc_dot_config.dot_stat_speed;
	}
	else if ((distance_x) < 3 && (distance_x) > 0)
	{
		mVelX = 1;
	}
	else if ((distance_x) > -3 && (distance_x) < 0)
	{
		mVelX = -1;
	}
	else if (distance_x)
	{
		mVelX = 0;
	}

	if (distance_y == 0)
	{
		mVelY = 0;
	}
	else if (distance_y > 3)
	{
		mVelY = npc_dot_config.dot_stat_speed;
	}
	else if (distance_y < -3)
	{
		mVelY = -npc_dot_config.dot_stat_speed;
	}
	else if ((distance_y) < 3 && (distance_y) > 0)
	{
		mVelY = 1;
	}
	else if ((distance_y) > -3 && (distance_y) < 0)
	{
		mVelY = -1;
	}
}

void NPC_Dot::set_direction()
{
	distance_x = targetPosX - (dot_rect.x + dot_rect.w / 2);
	distance_y = targetPosY - (dot_rect.y + dot_rect.h / 2);

	if (abs(distance_x) > abs(distance_y))
	{
		if (distance_x >= 0)
		{
			change_sprite_direction(0);
		}
		else if (distance_x < 0)
		{
			change_sprite_direction(1);
		}
	}
	else if (abs(distance_y) > abs(distance_x))
	{
		if (distance_y >= 0)
		{
			change_sprite_direction(2);
		}
		else if (distance_y < 0)
		{
			change_sprite_direction(3);
		}
	}
}



// CONTAINER DOTS

class Container : public Dot
{
public: 
	Container(SDL_Renderer* gRenderer, LTexture* container_spritesheet, int x_pos, int y_pos, int column_number, int row_number = 0) :Dot(gRenderer, container_spritesheet, x_pos, y_pos)
	{
		spritesheet = container_spritesheet;
		current_clip = { 1+column_number*SPRITESHEET_W,1+row_number*SPRITESHEET_H,TILE_WIDTH, TILE_HEIGHT };
		dot_config[DOT_TYPE] = DOT_CONTAINER;
	}

	void render(SDL_Renderer* gRenderer, Camera* camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int bounce = 0;
	int bounce_direction = 1;
	int delay = 0;
	int max_delay = 2;
	SDL_Rect current_clip;

private:
	LTexture* spritesheet;
};

void Container::render(SDL_Renderer* gRenderer, Camera* camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (is_onscreen(camera))
	{
		SDL_Rect renderQuad = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y + bounce, TILE_WIDTH, TILE_HEIGHT };
		spritesheet->render(gRenderer, &renderQuad, &current_clip);

		delay++;
		if (delay > max_delay) delay = 0;
		if (delay == 0)
		{
			bounce += bounce_direction;
			if (bounce > 3) bounce_direction = -1;
			if (bounce < -3) bounce_direction = 1;
		}
	}
}

// ASTEROID DOTS

class Asteroid : public Dot
{
public:
	Asteroid(SDL_Renderer* gRenderer, LTexture* asteroid_spritesheet, int x_pos, int y_pos, int row_num) :Dot(gRenderer, asteroid_spritesheet, x_pos, y_pos)
	{
		spritesheet = asteroid_spritesheet;

		dot_config[DOT_IS_COLLIDABLE] = 1;
		dot_config[DOT_TYPE] = DOT_ASTEROID;

		mVelX = 0;
		mVelY = 0;

		asteroid_num = rand() % 1000;

		if (asteroid_rarity <= 850)
		{
			multi_tile_config = Return_Tile_By_Name(TILE_IRON_ORE);
			random_clip_row = 0;
		}
		else if (asteroid_rarity > 850 && asteroid_rarity <= 950)
		{
			multi_tile_config = Return_Tile_By_Name(TILE_COBALT_ORE);
			random_clip_row = 1;
		}
		else if (asteroid_rarity > 950)
		{
			multi_tile_config = Return_Tile_By_Name(TILE_NICKEL_ORE);
			random_clip_row = 2;
		};

		npc_dot_config.inventory_slots[0].inventory_item_code = multi_tile_config.inventory_pointer;
		npc_dot_config.inventory_slots[0].item_number = 1;
	}

	void render(SDL_Renderer* gRenderer, Camera* camera);
	int angle = rand() % 100;
	int direction = rand() % 100;
	int spin_speed = rand() % 2 - 1;

	int asteroid_num;
	int random_clip_column = rand() % 7;
	int asteroid_rarity = rand() % 1000;
	
	int random_clip_row;


private:
	LTexture* spritesheet;

};

void Asteroid::render(SDL_Renderer* gRenderer, Camera* camera)
{
	if (is_onscreen(camera))
	{
		if (direction >= 50)
		{
			angle += spin_speed;
		}
		else
		{
			angle -= spin_speed;
		}

		
		SDL_Rect currentClip = { random_clip_column * 34,random_clip_row*34,dot_rect.w, dot_rect.h };

		SDL_Rect renderQuad = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, TILE_WIDTH, TILE_HEIGHT };

		spritesheet->render(gRenderer, &renderQuad, &currentClip, angle);
	}


	if (npc_dot_config.dot_stat_health < npc_dot_config.dot_stat_max_health)
	{
		render_status_bar(gRenderer, camera, npc_dot_config.dot_stat_health);
	}
}

// SHIP DOTS

class Ship_Dot: public Dot
{
public:
	Ship_Dot(SDL_Renderer* gRenderer, LTexture* enemy_ship_spritesheet, int x_pos, int y_pos) :Dot(gRenderer, enemy_ship_spritesheet, x_pos, y_pos)
	{
		spritesheet = enemy_ship_spritesheet;
		dot_rect = { x_pos, y_pos, 64,64 };
		ship_clip = { 0,0,64,64 };
		dot_config[DOT_TYPE] = DOT_ENEMY_SHIP;
	}
	void render(SDL_Renderer* gRenderer, Camera* camera);

	bool target_within_range();
	void turn_towards_target();
	void set_velocity();
	double get_angle();
	SDL_Rect ship_clip;

	int ship_max_velocity = 2;
	int ship_projectile_speed = 10;
	double engagement_distance = 500;
	int cooldown_time = 50;
	int firing_cooldown = 0;

private:
	LTexture* spritesheet;
	double angle = 0.0;
	int frame = 0;
	bool moving = false;


};

bool Ship_Dot::target_within_range()
{
	if (pow(distance_x, 2.0) + pow(distance_y, 2.0) <= pow(engagement_distance, 2.0)) return true;
	else return false;
}

double Ship_Dot::get_angle() 
{
	return angle;
}

void Ship_Dot::render(SDL_Renderer* gRenderer, Camera* camera)
{
	SDL_Rect offset_rect = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, dot_rect.w, dot_rect.h };
	SDL_Rect frame_clip = { frame/4*64,0, dot_rect.w, dot_rect.h };
	spritesheet->render(gRenderer, &offset_rect, &frame_clip, angle);

	if (moving == true)
	{
		frame++;
		if (frame > 12) frame = 5;
	}
	else frame = 0;

	if (npc_dot_config.dot_stat_health < npc_dot_config.dot_stat_max_health)
	{
		render_status_bar(gRenderer, camera, npc_dot_config.dot_stat_health);
	}
}

void Ship_Dot::set_velocity()
{
	distance_x = targetPosX - (dot_rect.x + dot_rect.w / 2);
	distance_y = targetPosY - (dot_rect.y + dot_rect.h / 2);

	if (distance_x == 0)
	{
		mVelX = 0;
	}
	else if (distance_x > 3)
	{
		mVelX = ship_max_velocity;
	}
	else if (distance_x < -3)
	{
		mVelX = -ship_max_velocity;
	}
	else if ((distance_x) < 3 && (distance_x) > 0)
	{
		mVelX = 1;
	}
	else if ((distance_x) > -3 && (distance_x) < 0)
	{
		mVelX = -1;
	}
	else if (distance_x == 0)
	{
		mVelX = 0;
	}

	if (distance_y == 0)
	{
		mVelY = 0;
	}
	else if (distance_y > 3)
	{
		mVelY = ship_max_velocity;
	}
	else if (distance_y < -3)
	{
		mVelY = -ship_max_velocity;
	}
	else if ((distance_y) < 3 && (distance_y) > 0)
	{
		mVelY = 1;
	}
	else if ((distance_y) > -3 && (distance_y) < 0)
	{
		mVelY = -1;
	}

	if (target_within_range()) {
		mVelX = 0;
		mVelY = 0;
	}

	if (mVelY > 0 || mVelX > 0) moving = true;
	else(moving = false);
}

void Ship_Dot::turn_towards_target()
{
	double vector_x = targetPosX - dot_rect.x;
	double vector_y = targetPosY - dot_rect.y;
	double new_angle = atan(vector_y / vector_x)*(180.0 / 3.141592653589793238463);

	if (vector_x >= 0 && vector_y >= 0) new_angle = -90 + new_angle;
	else if (vector_x < 0 && vector_y >= 0) new_angle = 90 + new_angle;
	else if (vector_x < 0 && vector_y < 0) new_angle = 90 + new_angle;
	else if (vector_x >= 0 && vector_y < 0) new_angle = -90 + new_angle;

	angle = new_angle + 180;
}

// BOLT DOTS

class Bolt : public Dot 
{
public:
	Bolt(SDL_Renderer* gRenderer, LTexture* texture, int owners_faction, int sprite_row, int start_location_x, int start_location_y, int projectile_speed, float projectile_angle, bool explosion = false) :Dot(gRenderer, texture, start_location_x, start_location_y)
	{
		bolt_texture = texture;

		npc_dot_config.dot_stat_faction = owners_faction;

		fire_angle = projectile_angle;
		speed = projectile_speed;

		animation_clip = { 1, 1 + sprite_row*(TILE_HEIGHT + 2), 32, 32 };

		mVelX = -sin(fire_angle) * speed;
		mVelY = cos(fire_angle) * speed;

		dot_config[DOT_TYPE] = DOT_BOLT;
		
		is_explosion = explosion;
	}

	void render(SDL_Renderer* gRenderer, Camera* camera);

	int mVelX, mVelY;

	int bolt_radius = 32;
	int bolt_damage = 10;
	int bolt_range = 0;
	int bolt_max_range = 50;

	bool is_explosion;
	int frame = 0;

private:
	SDL_Rect animation_clip;

	float fire_angle;
	double speed;


	int animation_delay = 0;
	int max_animation_delay = 1;

	LTexture* bolt_texture;
};

void Bolt::render(SDL_Renderer* gRenderer, Camera* camera)
{
	animation_clip.x = 1 + frame*(TILE_WIDTH + 2);
	SDL_Rect renderQuad = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, dot_rect.w, dot_rect.h };

	bolt_texture->render(gRenderer, &renderQuad, &animation_clip, fire_angle*(180.0 / 3.141592653589793238463) + 90);

	animation_delay++;

	if (animation_delay > max_animation_delay)
	{
		frame++;
		if (frame > 7)
		{
			frame = 0;
		}
		animation_delay = 0;
	}
}

#endif