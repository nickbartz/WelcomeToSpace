#ifndef DOT_H
#define DOT_H

class Carried_Multi_Tile
{
public:
	Carried_Multi_Tile(SDL_Renderer* gRenderer = NULL, LTexture* inventory_spritesheet = NULL, int* linked_x_coordinate = NULL, int* linked_y_coordinate = NULL, int inventory_item = INVENTORY_EMPTY_SLOT);

	LTexture* spritesheet;
	Inventory_Item_Template carried_item;
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
	carried_item = Fetch_Inventory_Item_Template(inventory_item);
	spritesheet = inventory_spritesheet;
	linked_x_coord = linked_x_coordinate;
	linked_y_coord = linked_y_coordinate;
	sprite_clip_x = carried_item.sprite_config.x;
	sprite_clip_y = carried_item.sprite_config.y;
	item_clip = {  sprite_clip_x*SPRITESHEET_W, sprite_clip_y * SPRITESHEET_H, carried_item.sprite_config.w , carried_item.sprite_config.h };
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

	struct Simple_Dot_Animation_Struct
	{
		int current_delay;
		int max_delay;
		int current_frame;
		int max_frames;
	};

	//Shows the dot on the screen
	virtual void Dot::render(SDL_Renderer* gRenderer, Camera* camera, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render_status_bar(SDL_Renderer* gRenderer, Camera* camera, int quantity_of_interest, SDL_Color bar_color = { 255,0,0,255 });
	void render_circle(SDL_Renderer* gRenderer, Camera* camera, int tile_x, int tile_y, int radius, int R, int G, int B, int alpha);
	void Simple_Increment_Animation(Simple_Dot_Animation_Struct* animation_struct);
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
	void Dot::respond_to_collision(Dot* colliding_dot);

	// DOT BASIC PLACEMENT AND MOVEMENT
	SDL_Rect dot_rect;
	double angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int bounce = 0;
	int bounce_direction = 1;
	int delay = 0;
	int max_delay = 5;
	double spin = 0.0;

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

	//Color functions
	void Dot::toggle_highlight(bool on_or_off);
	void Dot::light_dot_with_light_specs(SDL_Color lighting_specs);

	// Structs


	struct Dot_Goal
	{
		int goal_action = ACTION_NONE;

		int x_tile = 0;
		int y_tile = 0;
		int tile_or_item = 0;

		int goal_dot_type = NULL;
		Tile_Template tile_type;
		Inventory_Item_Template inventory_item;

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
		Dot* related_dot = NULL;
		int relationship_type;
		int relationship_value;
		int current_search_delay = 0;
		int max_search_delay = 0;
	};

	struct Mining_Laser_Config
	{
		SDL_Rect target_rect = { 0,0,0,0 };
		bool laser_on = false;
		int animation_delay = 0;
		SDL_Color laser_color = { 255, 0, 0, 255 };
	};

	struct NPC_Dot_Equipment_Slot
	{
		int dot_equipment_slot_type;
		int item_name;
		int quantity;
		bool is_equipped;
	};

	struct NPC_Dot_Equipment_Struct
	{
		Dot_Inventory_Slot Spacesuit = { INVENTORY_EMPTY_SLOT,0 };
		Dot_Inventory_Slot Weapon = { INVENTORY_EMPTY_SLOT,0 };
		Dot_Inventory_Slot Oxygen_Tank = { INVENTORY_EMPTY_SLOT,0 };
		Dot_Inventory_Slot Mining_Laser = { INVENTORY_EMPTY_SLOT,0 };
	};

	struct Item_Production_Status
	{
		int slot_tile_name = TILE_GENERIC_TILE;
		int slot_requests = 0;
		int slot_production_current = 0;
	};

	struct NPC_Dot_Config_Struct
	{
		string dot_last_name = "";
		string dot_first_name = "";
		string dot_full_name = "";
		
		int tile_built_level = 100;
		int dot_stat_health = 100;
		int dot_stat_max_health = 100;
		int dot_stat_speed = 3;
		int dot_stat_faction = 0;
		int dot_sprite_row = 1;
		
		vector<Dot_Relationship> dot_relationships;
		vector<Dot_Inventory_Slot> dot_starting_inventory; // not the dot's actual inventory, just a template

		map <int, Dot_Inventory_Slot> dot_equipment_map;
		map <int, Dot_Priority> dot_priority_map;
		unordered_map<int, Dot_Relationship> functional_relationship_map;

		int frenzel_rhomb = 0;
		Mining_Laser_Config dot_mining_config;
		NPC_Dot_Equipment_Struct dot_equipment_config;
		Carried_Multi_Tile* dot_carried_item = NULL;
		Dot* current_storage_tile = NULL;
		int dot_init = 1;
		SDL_Color dot_color = { 255,255,255,255 };
		SDL_Color dot_light = { 0,0,0,0 };
		int dot_angle = 0;
		Dot_Inventory_Slot inventory_slots[MAX_DOT_INVENTORY];
		vector<Dot_Inventory_Slot> craftable_items;
		int bounce = 0;
		int search_radius = 20;
		int marked_for_mining = 0;
		int hit_by_bolt = 0;
		bool is_currently_in_a_dot;

		// Job focused configs
		Dot* current_dot_focus;
		vector<Tile_Queue> current_goal_path;
		vector<Dot_Goal> current_goal_list;
		vector<Dot_Inventory_Slot> tile_parts_list;
		int number_of_jobs_requested = 0;
		Item_Production_Status production_status_array[6];

		// dummy's for the console, have no function other than reporting
		int console_current_dot_job = DOT_JOB_NO_ASSIGNED_JOB;
		int console_current_dot_goal = ACTION_NONE;
		int console_current_dot_focus_type = DOT_GENERIC;
	};

	//Set Dot Configuration
	int dot_config[NUM_DOT_STATS];
	NPC_Dot_Config_Struct npc_dot_config;
	Tile_Template multi_tile_config;

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
	void Set_Carried_item(LTexture* inventory_spritesheet, int inventory_item_code);
	int Check_Inventory_For_Item(int inventory_item_code);
	Inventory_Item_Template Check_Inventory_For_Item_Type(int item_type);
	void Create_Default_Dot_Priorities();
	void Check_Craftable_Items();
	void Return_Parts_List(Tile_Template tile_type);
	bool Check_If_Tile_Needs_Parts(Tile_Template tile_type);
	bool Check_if_Dot_Has_All_Needed_Scaffold_Parts(Dot* dot, Tile_Template tile_type);
	int Check_How_Much_Dot_Can_Craft_Of_Item(Tile_Template tile_type);
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
		render_status_bar(gRenderer, camera, npc_dot_config.dot_stat_health*TILE_WIDTH/npc_dot_config.dot_stat_max_health);
	}

	if (npc_dot_config.tile_built_level < multi_tile_config.build_time)
	{
		render_status_bar(gRenderer, camera, npc_dot_config.tile_built_level*TILE_WIDTH / multi_tile_config.build_time, { 0,0,255,255 });
	}

}

void Dot::render_status_bar(SDL_Renderer* gRenderer, Camera* camera, int quantity_of_interest, SDL_Color bar_color)
{
	SDL_Rect status_bar = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y -5, quantity_of_interest, 2 };
	SDL_SetRenderDrawColor(gRenderer, bar_color.r, bar_color.g, bar_color.b, bar_color.a);
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

void Dot::light_dot_with_light_specs(SDL_Color lighting_specs)
{
	int dot_light_r = npc_dot_config.dot_light.r;
	int dot_light_g = npc_dot_config.dot_light.g;
	int dot_light_b = npc_dot_config.dot_light.b;

	int lighting_specs_r = lighting_specs.r;
	int lighting_specs_g = lighting_specs.g;
	int lighting_specs_b = lighting_specs.b;

	if (dot_light_r + lighting_specs_r > 255) npc_dot_config.dot_light.r = 255;
	else npc_dot_config.dot_light.r += lighting_specs.r;

	if (dot_light_g + lighting_specs_g > 255) npc_dot_config.dot_light.g = 255;
	else npc_dot_config.dot_light.g += lighting_specs.g;
	
	if (dot_light_b + lighting_specs_b > 255) npc_dot_config.dot_light.b = 255;
	else npc_dot_config.dot_light.b += lighting_specs.b;

	int num = npc_dot_config.dot_light.a;

	if (multi_tile_config.tile_name = TILE_LOCKER_1) cout << num << endl;
	
}

void Dot::Simple_Increment_Animation(Simple_Dot_Animation_Struct* animation_struct)
{
	if (animation_struct->current_delay == 0)
	{
		animation_struct->current_frame++;
	}

	if (animation_struct->current_frame >= animation_struct->max_frames)
	{
		animation_struct->current_frame = 0;
	}

	animation_struct->current_delay++;

	if (animation_struct->current_delay >= animation_struct->max_delay)
	{
		animation_struct->current_delay = 0;
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

void Dot::respond_to_collision(Dot* colliding_dot)
{
	// MANAGE DOOR COLLISIONS
	if (multi_tile_config.door_state == 2) multi_tile_config.door_state = 1;
	else if (multi_tile_config.door_state == 1) multi_tile_config.door_open_length = 0;

	if (colliding_dot->dot_config[DOT_TYPE] == DOT_BOLT && dot_config[DOT_TYPE] == DOT_NPC)
	{
		npc_dot_config.hit_by_bolt = 1;
		npc_dot_config.functional_relationship_map[DOT_FUNCTIONAL_RELATIONSHIP_MOST_RECENT_ATTACKER].related_dot = colliding_dot->npc_dot_config.functional_relationship_map[DOT_FUNCTIONAL_RELATIONSHIP_FIRING_DOT].related_dot;
	}
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

void Dot::Set_Carried_item(LTexture* inventory_spritesheet, int inventory_item_code)
{
	npc_dot_config.dot_carried_item = new Carried_Multi_Tile(gRenderer, inventory_spritesheet, &dot_rect.x, &dot_rect.y, inventory_item_code);
}

void Dot::Create_Default_Dot_Priorities()
{
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_WEAPON_COOLDOWN, { DOT_PRIORITY_WEAPON_COOLDOWN,0,0,0,1,0,20 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_OXYGEN_NEED, { DOT_PRIORITY_OXYGEN_NEED, 0,0,1,100,0,1 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_SLEEP_NEED, { DOT_PRIORITY_SLEEP_NEED, 0,0,50,100,0,500 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_HUNGER_NEED, { DOT_PRIORITY_HUNGER_NEED, 0,0,50,100,0,500 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_SPACESUIT_OXYGEN, { DOT_PRIORITY_SPACESUIT_OXYGEN, 100,0,50,100,0,100 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_ENNUI, { DOT_PRIORITY_ENNUI, 0,0,50,100,0,200 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_HAPPINESS, { DOT_PRIORITY_HAPPINESS, 100,0,50,100,0,100 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_SANITY, { DOT_PRIORITY_SANITY, 100,0,50,100,0,100 }));
	npc_dot_config.dot_priority_map.insert(pair <int, Dot_Priority>(DOT_PRIORITY_PATH_CHECK_COOLDOWN, { DOT_PRIORITY_PATH_CHECK_COOLDOWN,0,0,0,1,0,20000 }));
}

// CRAFTING COMMANDS

void Dot::Check_Craftable_Items()
{
	npc_dot_config.craftable_items.clear();
	
	for (int i = 0; i < tile_template_vector.size(); i++)
	{
		if (tile_template_vector[i].can_be_scaffold == 1)
		{
			int craftable_amount = Check_How_Much_Dot_Can_Craft_Of_Item(tile_template_vector[i]);
			if (craftable_amount > 0)
			{
				npc_dot_config.craftable_items.push_back(Dot_Inventory_Slot{ tile_template_vector[i].inventory_pointer,craftable_amount });
			}
		}
	}
}

int Dot::Check_How_Much_Dot_Can_Craft_Of_Item(Tile_Template tile_type)
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

Inventory_Item_Template Dot::Check_Inventory_For_Item_Type(int item_type)
{
	for (int i = 0; i < MAX_DOT_INVENTORY; i++)
	{		
		if (Fetch_Inventory_Item_Template(npc_dot_config.inventory_slots[i].inventory_item_code).item_type == item_type)
		{
			return Fetch_Inventory_Item_Template(npc_dot_config.inventory_slots[i].inventory_item_code);
		}
	}
	return Fetch_Inventory_Item_Template(INVENTORY_NULL_ITEM);
}

void Dot::Return_Parts_List(Tile_Template tile_type)
{
	if (tile_type.building_specs.Requirement_1.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_1.inventory_requirement, tile_type.building_specs.Requirement_1.requirement_quantity});
	if (tile_type.building_specs.Requirement_2.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_2.inventory_requirement, tile_type.building_specs.Requirement_2.requirement_quantity});
	if (tile_type.building_specs.Requirement_3.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_3.inventory_requirement, tile_type.building_specs.Requirement_3.requirement_quantity});
	if (tile_type.building_specs.Requirement_4.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_4.inventory_requirement, tile_type.building_specs.Requirement_3.requirement_quantity});
	if (tile_type.building_specs.Requirement_5.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_5.inventory_requirement, tile_type.building_specs.Requirement_4.requirement_quantity});
	if (tile_type.building_specs.Requirement_6.requirement_quantity > 0) npc_dot_config.tile_parts_list.push_back(Dot_Inventory_Slot{ tile_type.building_specs.Requirement_6.inventory_requirement, tile_type.building_specs.Requirement_5.requirement_quantity});
}

bool Dot::Check_If_Tile_Needs_Parts(Tile_Template tile_type)
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

bool Dot::Check_if_Dot_Has_All_Needed_Scaffold_Parts(Dot* dot, Tile_Template tile_type)
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
		npc_dot_config.current_goal_list.clear();
	}
}

void Dot::dot_wipe_current_path()
{
	if (npc_dot_config.current_goal_path.size() != 0) npc_dot_config.current_goal_path.clear();
}

void Dot::dot_wipe_all_job_tasks()
{
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
	Tile(SDL_Renderer* gRenderer = NULL, LTexture* tile_texture = NULL, int x_coordinate = NULL, int y_coordinate = NULL, Tile_Template multi_config = Return_Tile_Template_By_Identifier(TILE_GENERIC_TILE), int tile_built_level = 0) :Dot(gRenderer, tile_texture, x_coordinate, y_coordinate)
	{
		tile_renderer = gRenderer;
		multi_tile_config = multi_config;
		dot_rect = { x_coordinate * TILE_WIDTH,y_coordinate * TILE_HEIGHT,TILE_WIDTH*multi_config.sprite_specs.rect_columns, TILE_HEIGHT*multi_config.sprite_specs.rect_rows };
		mTexture = tile_texture;

		int render_offset_x = 0;
		int render_offset_y = 0;
		

		if (multi_config.sprite_specs.sprite_rows < 0)  render_offset_y = multi_config.sprite_specs.sprite_rows/2;
		if (multi_config.sprite_specs.sprite_columns < 0)  render_offset_x = multi_config.sprite_specs.sprite_columns/2;

		if (multi_tile_config.is_smooth == 1) handle_smooth_tiles(2, 2, 2, 2, 2, 2, 2, 2);
		if (multi_tile_config.tile_type == TILE_TYPE_ASTEROID)
		{
			spin = (rand() % 40)/100.0 - 0.2;
			angle = rand() % 360;
			multi_tile_config.sprite_specs.sprite_column = rand() % 8;
			populate_tile_inventory();
		}
		if (multi_tile_config.tile_type == TILE_TYPE_TURRET)
		{
			angle = rand() % 360;
		}

		render_rect =  { (x_coordinate + render_offset_x)*TILE_WIDTH,(y_coordinate + render_offset_y)*TILE_HEIGHT, (TILE_WIDTH*abs(multi_tile_config.sprite_specs.sprite_columns)), (TILE_HEIGHT*abs(multi_tile_config.sprite_specs.sprite_rows)) };
		current_clip = { (1 + multi_tile_config.sprite_specs.sprite_column*SPRITESHEET_W),(1 + multi_tile_config.sprite_specs.sprite_row*SPRITESHEET_H) + SPRITESHEET_H * door_offset_y, (TILE_WIDTH*abs(multi_tile_config.sprite_specs.sprite_columns)), (TILE_HEIGHT*abs(multi_tile_config.sprite_specs.sprite_rows)) };
		
		dot_config[DOT_TYPE] = DOT_TILE;
		npc_dot_config.dot_stat_health = multi_config.max_health;
		npc_dot_config.dot_stat_max_health = multi_config.max_health;

		item_job_type = multi_config.item_job_type;
		item_job = Dot_Job{ item_job_type };

		x_tile = getTileX();
		y_tile = getTileY();

		npc_dot_config.tile_built_level = tile_built_level;

		if (npc_dot_config.tile_built_level < multi_config.build_time) Return_Parts_List(multi_config);

		populate_tile_production_config();
	}

	//Shows the Tile on the screen
	bool is_onscreen(Camera* camera);
	void update_texture_clip(int clip_row_x, int clip_row_y);
	virtual void render(SDL_Renderer* gRenderer, Camera* camera, int render_layer);
	void Tile::create_multitexture_from_multiclip();
	void Tile::handle_door_animation();
	void Tile::handle_animation();
	void Tile::handle_floor_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_smooth_tiles(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_wall_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_door_orientation(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::handle_frenzel_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge);
	void Tile::populate_tile_inventory();
	void Tile::populate_tile_production_config();
	
	void Tile::Tint_Tile_Before_Render();

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
	int door_offset_y = 0;
	int door_offset_x = 0;

	// Item Jobs
	int item_job_type;
	Dot_Job item_job;

	// Scaffold
	Tile* scaffold_on_tile = NULL;

private:
	SDL_Renderer* tile_renderer;
	SDL_Texture* multi_texture;
	SDL_Rect dot_rect_camera;

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

	dot_rect_camera = { render_rect.x - camera->camera_box.x, render_rect.y - camera->camera_box.y + bounce, render_rect.w, render_rect.h };
	SDL_Rect render_clip = { current_clip.x + door_offset_x, current_clip.y + door_offset_y*SPRITESHEET_H, current_clip.w, current_clip.h };

	// Change colors or alpha of tile before render
	Tint_Tile_Before_Render();

	SDL_Point rotate_angle{ 16,16 };

	if (multi_tile_config.render_layer == render_layer)
	{
		if ((multi_tile_config.is_smooth == 0 || multi_tile_config.door_state >= 1)) mTexture->render(gRenderer, &dot_rect_camera, &render_clip, angle, NULL, flip);
		else if (multi_texture != NULL) SDL_RenderCopyEx(gRenderer, multi_texture, new SDL_Rect{ 0,0,TILE_WIDTH,TILE_HEIGHT }, &dot_rect_camera, 0, NULL, flip);
	}
	
	if (scaffold_on_tile != NULL) scaffold_on_tile->render(gRenderer, camera, render_layer);
	if (multi_tile_config.tile_type == TILE_TYPE_ASTEROID) angle += spin;
	
	Dot::render(gRenderer, camera);
	//if (npc_dot_config.production_current > 0) render_status_bar(gRenderer, camera, npc_dot_config.production_current);

	mTexture->setAlpha(255);
	mTexture->setColor(255, 255, 255);

	// RESET CYCLICAL TILE PROPERTIES
	multi_tile_config.leak_check = 0;
	multi_tile_config.oxygenation_check = 0;
	multi_tile_config.is_oxygenated = 0;
	npc_dot_config.dot_light = { 0,0,0,0 };
	npc_dot_config.dot_color = { 255,255,255,255 };

}

void Tile::Tint_Tile_Before_Render()
{
	npc_dot_config.dot_color = { 255,255,255,255 };
	if (multi_tile_config.tile_type == TILE_TYPE_LIGHT) npc_dot_config.dot_color = multi_tile_config.light_specs.light_color;
	npc_dot_config.dot_color.a = 255;

	// Mark tiles when they're flagged 
	if (npc_dot_config.marked_for_mining == 1) npc_dot_config.dot_color.g -= 100, npc_dot_config.dot_color.b -= 100;
	
	// Tint tiles blue when they're oxygenated
	npc_dot_config.dot_color.r -= multi_tile_config.is_oxygenated * 10;
	npc_dot_config.dot_color.g -= multi_tile_config.is_oxygenated * 10;

	// Make tiles transparent and blue when they're scaffolds
	if (npc_dot_config.tile_built_level < multi_tile_config.build_time)
	{
		npc_dot_config.dot_color.a -= 155;
		npc_dot_config.dot_color.r -= 55;
		npc_dot_config.dot_color.g -= 55;
	}

	mTexture->setAlpha(npc_dot_config.dot_color.a);
	mTexture->setColor(npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);

	if (multi_texture != NULL)
	{
		SDL_SetTextureAlphaMod(multi_texture,npc_dot_config.dot_color.a);
		SDL_SetTextureColorMod(multi_texture,npc_dot_config.dot_color.r, npc_dot_config.dot_color.g, npc_dot_config.dot_color.b);
	}
}

void Tile::create_multitexture_from_multiclip()
{
	multi_texture = SDL_CreateTexture(tile_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TILE_WIDTH, TILE_HEIGHT);;

	SDL_SetRenderTarget(tile_renderer, multi_texture);
	SDL_RenderClear(tile_renderer);

	for (vector<clip_and_rotation>::iterator it = multi_clip.begin(); it != multi_clip.end(); ++it)
	{
		SDL_Rect draw_rect = { 0,0,TILE_WIDTH,TILE_HEIGHT };
		mTexture->render(tile_renderer, &draw_rect, &it->clip, it->angle, 0, it->flip);
	}

	SDL_SetRenderTarget(tile_renderer, NULL);
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
			create_multitexture_from_multiclip();
			break;
		case TILE_TYPE_CONSTRUCTION_TUBING_DOOR:
			handle_door_orientation(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			break;
		case TILE_TYPE_CONSTRUCTION_TUBING_FLOOR:
			handle_floor_tiling(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			create_multitexture_from_multiclip();
			break;
		case TILE_TYPE_FRENZEL:
			handle_frenzel_tiling(left_edge, right_edge, top_edge, bottom_edge, top_left_edge, top_right_edge, bottom_right_edge, bottom_left_edge);
			create_multitexture_from_multiclip();
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

	// TOP_LEFT QUAD
	if (left_edge == VACUUM)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 0, SDL_FLIP_NONE));
	else if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_NONE));
	}
	else multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 0, 0, SDL_FLIP_NONE));

	if (right_edge == VACUUM && top_edge == VACUUM)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 1, 0, SDL_FLIP_HORIZONTAL));
	else if (right_edge == VACUUM && bottom_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 0, 0, SDL_FLIP_HORIZONTAL));
	
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 0, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_NONE));

	if (top_edge == VACUUM || (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_left_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_NONE));

	// TOP_RIGHT QUAD
	if (right_edge == VACUUM)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 0, SDL_FLIP_HORIZONTAL));
	else if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 0, 0, SDL_FLIP_NONE));
	}
	else multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 0, 0, SDL_FLIP_HORIZONTAL));
	
	if (left_edge == VACUUM && top_edge == VACUUM)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 1, 0, SDL_FLIP_NONE));
	else if (left_edge == VACUUM && bottom_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 0, 0, SDL_FLIP_NONE));
	
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_HORIZONTAL));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 0, 0, SDL_FLIP_HORIZONTAL));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_HORIZONTAL));

	if (top_edge == VACUUM || (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_right_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 1, 0, SDL_FLIP_HORIZONTAL));


	// BOTTOM_LEFT QUAD
	if (left_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 0, SDL_FLIP_VERTICAL));
	else if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 0, SDL_FLIP_VERTICAL));
	else multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 0, 0, SDL_FLIP_VERTICAL));

	if (bottom_edge == VACUUM && left_edge != VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	else if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_left_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	else if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_NONE));
	
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_left_edge != VACUUM && right_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_VERTICAL));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && (right_edge == VACUUM || bottom_right_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 0, 0, SDL_FLIP_VERTICAL));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_VERTICAL));

	if (bottom_edge == VACUUM && right_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));

	// BOTTOM_RIGHT QUAD
	if (right_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 1, 180, SDL_FLIP_NONE));
	else if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 0, 180, SDL_FLIP_NONE));
	else multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 0, 180, SDL_FLIP_NONE));

	if (bottom_edge == VACUUM && right_edge != VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_HORIZONTAL));
	else if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_right_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_HORIZONTAL));
	else if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_HORIZONTAL));

	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_right_edge != VACUUM && left_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 180, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && (left_edge == VACUUM || bottom_left_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 0, 180, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 180, SDL_FLIP_NONE));

	if (bottom_edge == VACUUM && left_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));


	// OVERLAY ACCOUTREMENT - NEED TO FIX THIS A LITTLE
	if ((left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) && bottom_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
	if ((left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge != VACUUM) || (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge != VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 4, 2, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 2, 0, SDL_FLIP_NONE));
	
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL && (right_edge != VACUUM && left_edge != VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 0, 2, 0, SDL_FLIP_NONE));
	if ((left_edge == VACUUM && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 1, 2, 0, SDL_FLIP_NONE));
	if ((right_edge == VACUUM && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == VACUUM)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 2, 0, SDL_FLIP_NONE));
	if (top_edge == VACUUM && left_edge == VACUUM && (top_left_edge == VACUUM || top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 2, 0, SDL_FLIP_NONE));
	if (top_edge == VACUUM && right_edge == VACUUM && (top_right_edge == VACUUM || top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 2, 0, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 2, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)  multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 6, 0, 0, SDL_FLIP_NONE));

	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge != VACUUM && right_edge != VACUUM && bottom_left_edge != VACUUM && bottom_right_edge != VACUUM) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_NONE));

	

}

void Tile::handle_floor_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
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

	for (int i = 0; i < 4; i++)
	{
		int offset_x = rand() % 2;
		int offset_y = rand() % 2;
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, offset_x, offset_y, 0, SDL_FLIP_NONE));
	}

	// TOP LEFT CORNERS GUTTERS
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_NONE));
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 0, SDL_FLIP_HORIZONTAL));
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 180, SDL_FLIP_NONE));
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 0, 270, SDL_FLIP_NONE));
	
	// LEFT EDGE GUTTERS
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_NONE));
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_VERTICAL));
	
	// RIGHT EDGE GUTTERS
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 0, SDL_FLIP_HORIZONTAL));
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 2, 1, 180, SDL_FLIP_NONE));

	// TOP EDGE GUTTERS
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_NONE));
	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_HORIZONTAL));

	// BOTTOM EDGE GUTTERS
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 0, SDL_FLIP_VERTICAL));
	if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 0, 180, SDL_FLIP_NONE));

	// BOTTOM RIGHT CORNERS GUTTERS
	if (top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_HORIZONTAL));
	if (top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_NONE));
	if (bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 180, SDL_FLIP_NONE));
	if (bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 3, 1, 0, SDL_FLIP_VERTICAL));

	// WALL OCCLUSION
	if (left_edge != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 1, 0, SDL_FLIP_NONE));
	if (right_edge != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 1, 0, SDL_FLIP_HORIZONTAL));
	if (top_edge != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 0, 0, SDL_FLIP_NONE));
	if (bottom_edge != TILE_TYPE_CONSTRUCTION_TUBING_FLOOR) multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 7, 0, 0, SDL_FLIP_VERTICAL));

	// GUTTER OCCLUSION
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_NONE));
	}
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_VERTICAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_VERTICAL));
	}
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_HORIZONTAL));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_HORIZONTAL));
	}
	if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL)
	{
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 180, SDL_FLIP_NONE));
		multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 180, SDL_FLIP_NONE));
	}

	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_NONE));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_HORIZONTAL));
		}
		if (bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 180, SDL_FLIP_NONE));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 180, SDL_FLIP_HORIZONTAL));
		}
		if (bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_VERTICAL));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 90, SDL_FLIP_HORIZONTAL));
		}
		if (top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_NONE));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 0, SDL_FLIP_HORIZONTAL));
		}
	}


	if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR && bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && right_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_NONE));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_VERTICAL));
		}
		if (right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && left_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 90, SDL_FLIP_NONE));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 90, SDL_FLIP_HORIZONTAL));
		}
		if (top_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_left_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_right_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_right_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_VERTICAL));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 0, 0, SDL_FLIP_NONE));
		}
		if (top_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_right_edge == TILE_TYPE_CONSTRUCTION_TUBING_WALL && top_left_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL && bottom_left_edge != TILE_TYPE_CONSTRUCTION_TUBING_WALL)
		{
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 90, SDL_FLIP_NONE));
			multi_clip.push_back(Create_Clip_And_Rotation(x, y, 0, 0, 5, 1, 90, SDL_FLIP_HORIZONTAL));
		}

	}





}

void Tile::handle_door_orientation(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	if (left_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || right_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		door_offset_y = 2;
		if (right_edge == VACUUM || left_edge == VACUUM)
		{
			door_offset_y = 1;
			if (right_edge == VACUUM) flip = SDL_FLIP_HORIZONTAL;
		}
	}
	else if (top_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR || bottom_edge == TILE_TYPE_CONSTRUCTION_TUBING_FLOOR)
	{
		door_offset_y = 0;
	}

}

void Tile::handle_frenzel_tiling(int left_edge, int right_edge, int top_edge, int bottom_edge, int top_left_edge, int top_right_edge, int bottom_right_edge, int bottom_left_edge)
{
	multi_clip.clear();
	
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

void Tile::populate_tile_inventory()
{
	npc_dot_config.inventory_slots[0].inventory_item_code = multi_tile_config.inventory_pointer;
	npc_dot_config.inventory_slots[0].item_number = 1;
}

void Tile::populate_tile_production_config()
{
	if (multi_tile_config.dot_produced_items.tile_name_1 != TILE_NULL) npc_dot_config.production_status_array[0].slot_tile_name = multi_tile_config.dot_produced_items.tile_name_1;
	if (multi_tile_config.dot_produced_items.tile_name_2 != TILE_NULL) npc_dot_config.production_status_array[1].slot_tile_name = multi_tile_config.dot_produced_items.tile_name_2;
	if (multi_tile_config.dot_produced_items.tile_name_3 != TILE_NULL) npc_dot_config.production_status_array[2].slot_tile_name = multi_tile_config.dot_produced_items.tile_name_3;
	if (multi_tile_config.dot_produced_items.tile_name_4 != TILE_NULL) npc_dot_config.production_status_array[3].slot_tile_name = multi_tile_config.dot_produced_items.tile_name_4;
	if (multi_tile_config.dot_produced_items.tile_name_5 != TILE_NULL) npc_dot_config.production_status_array[4].slot_tile_name = multi_tile_config.dot_produced_items.tile_name_5;
	if (multi_tile_config.dot_produced_items.tile_name_6 != TILE_NULL) npc_dot_config.production_status_array[5].slot_tile_name = multi_tile_config.dot_produced_items.tile_name_6;
}

// PLAYER AND NPC DOTS

class NPC_Dot : public Dot
{
public:
	NPC_Dot(SDL_Renderer* gRenderer, LTexture* dot_spritesheet_array[], TTF_Font* gFont_small, int x_pos, int y_pos, dot_composite_config dot_makeup) :Dot(gRenderer, dot_spritesheet_array[0], x_pos, y_pos)
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

		for (int i = 0; i < tile_template_vector.size(); i++) npc_dot_config.craftable_items.push_back(Dot_Inventory_Slot{ tile_template_vector[i].inventory_pointer,1 });
	}

	void set_dot_render_color(SDL_Color color);
	void render(SDL_Renderer* gRenderer, Camera* camera, TTF_Font* gFont_small, int faction_relationship);
	void render_component(SDL_Renderer* gRenderer, Camera* camera, int component);
	void render_name(SDL_Renderer* gRenderer, Camera* camera, TTF_Font* gFont_small, int faction_relationship);
	void increment_animation();
	void create_sprite(int leg_type, int arm_type, int torso_type, int head_type, int spacesuit_type);
	void change_sprite_direction(int direction);
	void animate_movement(int previous_mPosX, int previous_mPosY);
	void set_velocity();
	void set_direction();
	void increment_bounce();

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
	LTexture dot_name;

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

void NPC_Dot::set_dot_render_color(SDL_Color color)
{
	for (int i = 0; i < 5; i++)
	{
		dot_spritesheet[i]->setColor(color.r, color.g, color.b);
	}
}

void NPC_Dot::render(SDL_Renderer* gRenderer, Camera* camera, TTF_Font* gFont_small, int faction_relationship)
{
	set_dot_render_color(npc_dot_config.dot_color);
	
	// RENDER SHADOW
	dot_spritesheet[DOT_COMPOSITE_SHADOW]->render(gRenderer, new SDL_Rect{ dot_rect.x + rect_offset_x - camera->camera_box.x, dot_rect.y + rect_offset_y - camera->camera_box.y + bounce + shadow_offset, TILE_WIDTH, TILE_HEIGHT }, new SDL_Rect{ 0,0,32,32 });

	// IF WEARING A SPACESUIT, RENDER SPACESUIT, IF NOT RENDER COMPONENTS
	if (npc_dot_config.dot_equipment_config.Spacesuit.item_number == 1) NPC_Dot::render_component(gRenderer, camera, DOT_COMPOSITE_SPACESUIT);
	else
	{
		render_component(gRenderer, camera, DOT_COMPOSITE_LEGS);
		render_component(gRenderer, camera, DOT_COMPOSITE_TORSO);
		render_component(gRenderer, camera, DOT_COMPOSITE_ARMS);
		render_component(gRenderer, camera, DOT_COMPOSITE_HEAD);
	}

	set_dot_render_color({ 255,255,255,255 });

	NPC_Dot::render_name(gRenderer, camera, gFont_small, faction_relationship);

	Dot::render(gRenderer, camera);

	if (npc_dot_config.bounce == 1) increment_bounce();
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

void NPC_Dot::render_name(SDL_Renderer* gRenderer, Camera* camera, TTF_Font* gFont_small, int faction_relationship)
{
	SDL_Color faction_color = { 0,0,0,255 };
	if (npc_dot_config.dot_stat_faction == DOT_FACTION_PLAYER) faction_color = { 255,255,255,255 };
	else if (faction_relationship < 0) faction_color.r = 255;
	else if (faction_relationship > 0) faction_color.g = 255;
	else if (faction_relationship == 0) faction_color.b = 255;
	dot_name.loadFromRenderedText(npc_dot_config.dot_first_name, faction_color, gFont_small, gRenderer);

	SDL_Rect dot_name_rect = { dot_rect.x - camera->camera_box.x + dot_rect.w / 2 - dot_name.getWidth() / 2,dot_rect.y - camera->camera_box.y + dot_rect.h,dot_name.getWidth(),dot_name.getHeight() };
	SDL_Rect dot_name_clip = { 0,0,dot_name.getWidth(),dot_name.getHeight() };
	dot_name.render(gRenderer, &dot_name_rect, &dot_name_clip);
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

void NPC_Dot::increment_bounce()
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

// ALIEN DOTS (i.e. Dots without Animation but no Directionality) 

class Alien_Dot : public Dot {
public:
	Alien_Dot(SDL_Renderer* gRenderer, LTexture* dot_spritesheet, int x_pos, int y_pos, int row) :Dot(gRenderer, dot_spritesheet, x_pos, y_pos)
	{
		spritesheet = dot_spritesheet;
		spritesheet_row = row;

		alien_animation.max_delay = 3;
		alien_animation.max_frames = 8;
	}

	void render(SDL_Renderer* gRenderer, Camera* camera);

	Simple_Dot_Animation_Struct alien_animation;

private:
	LTexture* spritesheet;
	int spritesheet_row;
};

void Alien_Dot::render(SDL_Renderer* gRenderer, Camera* camera)
{
	Dot::Simple_Increment_Animation(&alien_animation);
	
	SDL_Rect render_rect = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, dot_rect.w, dot_rect.h };
	SDL_Rect clip_rect = { alien_animation.current_frame*SPRITESHEET_W ,spritesheet_row * SPRITESHEET_H, SPRITESHEET_W, SPRITESHEET_H };

	spritesheet->render(gRenderer, &render_rect, &clip_rect);
	
	Dot::render(gRenderer, camera);
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

// SHIP DOTS

class Ship_Dot: public Dot
{
public:
	Ship_Dot(SDL_Renderer* gRenderer, LTexture* enemy_ship_spritesheet, SDL_Rect ship_dot_rect, SDL_Rect ship_clip_rect, int num_frames) :Dot(gRenderer, enemy_ship_spritesheet, ship_dot_rect.x, ship_dot_rect.y)
	{
		spritesheet = enemy_ship_spritesheet;
		dot_rect = { ship_dot_rect.x, ship_dot_rect.y, ship_dot_rect.w,ship_dot_rect.h };
		ship_clip = { ship_clip_rect.x,ship_clip_rect.y,ship_clip_rect.w,ship_clip_rect.h };
		dot_config[DOT_TYPE] = DOT_ENEMY_SHIP;

		ship_animation.max_delay = 10;
		ship_animation.max_frames = num_frames;
	}
	void render(SDL_Renderer* gRenderer, Camera* camera);

	bool target_within_range();
	void turn_towards_target();
	void set_velocity();
	double get_angle();

	SDL_Rect ship_clip;
	Simple_Dot_Animation_Struct ship_animation;

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

void Ship_Dot::render(SDL_Renderer* gRenderer, Camera* camera)
{
	SDL_Rect offset_rect = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, dot_rect.w, dot_rect.h };
	SDL_Rect clip_rect = {ship_clip.x + ship_animation.current_frame*ship_clip.w,ship_clip.y, ship_clip.w, ship_clip.h };
	spritesheet->render(gRenderer, &offset_rect, &clip_rect, angle);

	Dot::render(gRenderer, camera);
}

bool Ship_Dot::target_within_range()
{
	if (pow(distance_x, 2.0) + pow(distance_y, 2.0) <= pow(engagement_distance, 2.0)) return true;
	else return false;
}

double Ship_Dot::get_angle() 
{
	return angle;
}

void Ship_Dot::set_velocity()
{
	distance_x = targetPosX - (dot_rect.x + dot_rect.w / 2);
	distance_y = targetPosY - (dot_rect.y + dot_rect.h / 2);

	if (target_within_range()) {
		mVelX = 0;
		mVelY = 0;
	}
	else
	{
		if (distance_x > 3*TILE_WIDTH)
		{
			mVelX = ship_max_velocity;
			Dot::Simple_Increment_Animation(&ship_animation);
			Dot::Simple_Increment_Animation(&ship_animation);
		}
		else if (distance_x < -3*TILE_WIDTH)
		{
			mVelX = -ship_max_velocity;
			Dot::Simple_Increment_Animation(&ship_animation);
			Dot::Simple_Increment_Animation(&ship_animation);
		}
		else if ((distance_x) < 3 * TILE_WIDTH && (distance_x) > 0)
		{
			mVelX = 1;
			Dot::Simple_Increment_Animation(&ship_animation);
		}
		else if ((distance_x) > 3 * TILE_WIDTH && (distance_x) < 0)
		{
			mVelX = -1;
			Dot::Simple_Increment_Animation(&ship_animation);
		}

		if (distance_y > 3 * TILE_HEIGHT)
		{
			mVelY = ship_max_velocity;
		}
		else if (distance_y < -3*TILE_HEIGHT)
		{
			mVelY = -ship_max_velocity;
		}
		else if ((distance_y) < 3*TILE_HEIGHT && (distance_y) > 0)
		{
			mVelY = 1;
		}
		else if ((distance_y) > -3*TILE_HEIGHT && (distance_y) < 0)
		{
			mVelY = -1;
		}
	}

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

// LIGHT DOTS

class Light:public Dot {
public: 
	Light(SDL_Renderer* gRenderer, LTexture* texture, int start_location_x, int start_location_y, SDL_Color color, int radius, int brightness, int attenuation, bool screen_shadow = false) :Dot(gRenderer, texture, start_location_x, start_location_y)
	{
		light_texture = texture;
		light_attenuation = attenuation;
		light_color = color;
		light_brightness = brightness;
		light_radius = radius;

		draw_clip = {attenuation*128,0,128,128};

	}

	SDL_Rect draw_clip;
	SDL_Color light_color;

	int light_radius;
	int light_brightness;
	int light_attenuation;
	int pulse = 0;
	int pulse_direction = 1;
	int max_pulse = 10;

	void render(SDL_Renderer* gRenderer, Camera* camera);

private: 
	LTexture* light_texture;
};

void Light::render(SDL_Renderer* gRenderer, Camera* camera)
{
	pulse += pulse_direction;
	if (pulse >= max_pulse || pulse <= 0)
	{
		pulse_direction *= -1;
	}

	if (is_onscreen(camera))
	{		
		SDL_Rect renderQuad = { dot_rect.x +TILE_WIDTH/2 - (light_radius + pulse) - camera->camera_box.x, dot_rect.y + TILE_HEIGHT/2 - (light_radius + pulse) - camera->camera_box.y, (light_radius + pulse)*2, (light_radius + pulse)*2 };
		light_texture->setColor(light_color.r, light_color.g, light_color.b);
		light_texture->setAlpha(255);
		
		light_texture->setBlendMode(SDL_BLENDMODE_ADD);
		light_texture->render(gRenderer, &renderQuad, &draw_clip);
	}

}


// BOLT DOTS

class Bolt : public Dot 
{
public:
	Bolt(Dot* firing_dot, SDL_Renderer* gRenderer, LTexture* texture, int sprite_row, int start_location_x, int start_location_y, int projectile_speed, float projectile_angle, bool explosion = false) :Dot(gRenderer, texture, start_location_x, start_location_y)
	{
		bolt_texture = texture;

		npc_dot_config.dot_stat_faction = firing_dot->npc_dot_config.dot_stat_faction;

		fire_angle = projectile_angle;
		speed = projectile_speed;

		animation_clip = { 1, 1 + sprite_row*(TILE_HEIGHT + 2), 32, 32 };

		mVelX = -sin(fire_angle) * speed;
		mVelY = cos(fire_angle) * speed;

		dot_config[DOT_TYPE] = DOT_BOLT;

		is_explosion = explosion;

		dot_rect.w = TILE_WIDTH/3;
		dot_rect.h = TILE_HEIGHT/3;

		npc_dot_config.functional_relationship_map[DOT_FUNCTIONAL_RELATIONSHIP_FIRING_DOT].related_dot = firing_dot;
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
	SDL_Rect renderQuad = { dot_rect.x - camera->camera_box.x, dot_rect.y - camera->camera_box.y, SPRITESHEET_W, SPRITESHEET_H };

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

// STAR DOTS
class Dot_Star :public Dot {
public: 
	Dot_Star(SDL_Renderer* gRenderer, LTexture* texture, int start_location_x, int start_location_y, int rand_depth, int star_type) :Dot(gRenderer, texture, start_location_x, start_location_y)
	{
		star_rect = { start_location_x, start_location_y, TILE_WIDTH, TILE_HEIGHT };
		star_clip = { 0,18*SPRITESHEET_H,TILE_WIDTH,TILE_HEIGHT };
		star_texture = texture;
		depth = rand_depth;
	}

	SDL_Rect star_rect;
	SDL_Rect star_clip;
	LTexture* star_texture;
	int depth;

	void render(SDL_Renderer* gRenderer, Camera* camera);
};

void Dot_Star::render(SDL_Renderer* gRenderer, Camera* camera)
{
	int star_depth = depth;
	SDL_Rect camera_rect = { star_rect.x - camera->camera_box.x/star_depth, star_rect.y - camera->camera_box.y/star_depth, TILE_WIDTH, TILE_HEIGHT };
	star_texture->render(gRenderer, &camera_rect, &star_clip);
}

#endif