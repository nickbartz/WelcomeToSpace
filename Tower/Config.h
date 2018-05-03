#ifndef CONFIG_H
#define CONFIG_H



//Screen dimension constants
const int TILE_HEIGHT = 32;
const int TILE_WIDTH = 32;

struct Tile_Queue
{
	int x_tile;
	int y_tile;
	int order;
};

const int SPRITESHEET_W = 34;
const int SPRITESHEET_H = 34;

const int TILE_NUM_X = 300;
const int TILE_NUM_Y = 300;
const int TOTAL_LEVEL_TILES = TILE_NUM_X*TILE_NUM_Y;

const int SEARCH_WIDTH = TILE_NUM_X;
const int SEARCH_HEIGHT = TILE_NUM_Y;

//The dimensions of the level
const int LEVEL_WIDTH = TILE_WIDTH * TILE_NUM_X;
const int LEVEL_HEIGHT = TILE_HEIGHT * TILE_NUM_Y;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

//TEXTURE 

const int BASIC_TILESHEET_WIDTH = 8;
const int BASIC_TILESHEET_HEIGHT = 20;

const int NUM_TILESHEETS = 9; // Change this when adding or subtracting spritesheets

enum Spritesheets
{
	TILESHEET,
	ITEM_SPRITES,
	CONSOLE_BACKGROUND,
	BOLT_SPRITES,
	DOT_SPRITESHEET,
	ASTEROID_SPRITESHEET,
	INVENTORY_SPRITESHEET,
	ENEMY_SHIP_SPRITESHEET,
	CONTAINER_SPRITESHEET
};

// ANIMATION FRAMES
const int MAX_ANIMATION_FRAMES = 4;
const int DOOR_OPEN_PAUSE = 32;

//PHYSICS CONSTANTS

const int COLLISION_CHECK_RADIUS = 50;

//PROJECTILES
const int MAX_PROJECTILES = 40;

//ASTEROIDS 
const int ASTEROID_DESPAWN_RADIUS = 1920;
const int MAX_NUM_ASTEROIDS = 200;
const float GLOBAL_BOUNCE_DECAY = 0.75;
const int MAX_ASTEROID_SPEED = 1;

//Key press surfaces constants

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

// Console Configuration 
const int MAX_CONSOLE_BUTTONS = 24;
const int MAX_CONSOLE_DIAGNOSTICS = 12;

enum Console_Buttons
{
	BUTTON_ACTION_ACTION,
	BUTTON_ACTION_REMOVE_TILE,
	BUTTON_ACTION_ATTACK,
	BUTTON_ACTION_MINING_LASER,
	BUTTON_ACTION_DO_NOTHING,
	BUTTON_ACTION_CREATE_ITEM,
	BUTTON_ACTION_PLACE_ITEM,
	BUTTON_ACTION_PICKUP_ITEM,
	BUTTON_ACTION_PLACE_SCAFFOLD,
	BUTTON_ACTION_INSPECT,
	BUTTON_ACTION_INVENTORY_BUTTON,
	BUTTON_ACTION_SWITCH_PANEL,
	BUTTON_ACTION_CRAFT_ITEM,
	BUTTON_ACTION_DELETE_TILE,
	BUTTON_ACTION_RESTART_GAME,
	BUTTON_ACTION_QUIT_GAME
};

enum Console_Windows
{
	NULL_WINDOW,
	WINDOW_DOT_DIAGNOSTIC,
	WINDOW_PLAYER_DIAGNOSTIC,
	WINDOW_OPTIONS
};

enum Console_Window_Panels
{
	PANEL_NO_PANEL,
	PANEL_CONSOLE_WINDOW_BUTTONS,
	PANEL_DOT_INVENTORY,
	PANEL_DOT_DIAGNOSTIC,
	PANEL_EQUIPMENT_LOADOUT,
	PANEL_CRAFTABLE_ITEMS,
	PANEL_OPTIONS_RESTART
};

enum TILE_LAYERS
{
	BASE_TILE,
	ITEM_TILE,
	ROOF_TILE
};

enum TILE_AND_ITEM_IDENTIFIERS
{
	TILE_NULL,
	TILE_GENERIC_TILE,
	TILE_GENERIC_ITEM,
	TILE_OXYGEN_MACHINE,
	TILE_SOLAR_ARRAY_1,
	TILE_FLOOR_TILE_1,
	TILE_STORAGE_TILE_1,
	TILE_WALL_TILE_1,
	TILE_WALL_TILE_2,
	TILE_FRENZEL_1,
	TILE_FRENZEL_2,
	TILE_DOOR_1,
	TILE_DOOR_2,
	TILE_IRON_ORE,
	TILE_COBALT_ORE,
	TILE_NICKEL_ORE,
	TILE_PROCESSED_IRON,
	TILE_PROCESSED_COBALT,
	TILE_PROCESSED_NICKEL,
	TILE_VACUUM,
	TILE_VACUUM_2,
	TILE_BED_1,
	TILE_BED_2,
	TILE_SCAFFOLD_1,
	TILE_TREE_1,
	TILE_CONSOLE_1,
	TILE_LOCKER_1,
	TILE_PLANT_1,
	TILE_EMITTER_1,
	TILE_SOYLENT_MACHINE_1,
	TILE_SOYLENT_1,
	TILE_SOYLENT_MEAL_1,
	TILE_SPACESUIT_1,
	TILE_OXYGEN_TANK,
	TILE_MICROWAVE_1,
	TILE_CHAIR_1,
	TILE_TABLE_1,
	TILE_SPACEDOCK_1,
	TILE_MINING_LASER_1,
	TILE_LASER_PISTOL_1,
	TILE_CONSTRUCTION_TUBE_WALL_1,
	TILE_CONSTRUCTION_TUBE_FLOOR_1
};

enum TILE_TYPES_AND_ITEM_TYPES
{
	VACUUM,
	FLOOR_TILE_1,
	WALL_TILE,
	DOOR_TILE,
	RESOURCE_1,
	OXYGEN_MACHINE,
	ITEM_TYPE_ORE,
	ITEM_TYPE_PROCESSED_ORE,
	EMPTY_SLOT,
	SOLAR_ARRAY,
	ITEM_TYPE_BED,
	STORAGE_TILE_1,
	SCAFFOLD_1,
	TREE,
	CONSOLE,
	LOCKER,
	TILE_TYPE_PLANT,
	TILE_TYPE_FRENZEL,
	ITEM_TYPE_FRENZEL,
	ITEM_TYPE_EMITTER,
	ITEM_TYPE_SOYLENT_MACHINE,
	ITEM_TYPE_FOOD,
	ITEM_TYPE_CHAIR,
	INVENTORY_TYPE_SUIT,
	ITEM_TYPE_OXYGEN_TANK,
	ITEM_TYPE_FOOD_PREPARATION,
	ITEM_TYPE_TABLE,
	ITEM_TYPE_SPACEDOCK,
	ITEM_TYPE_MINING_LASER,
	ITEM_TYPE_WEAPON,
	TILE_TYPE_CONSTRUCTION_TUBING_WALL,
	TILE_TYPE_CONSTRUCTION_TUBING_FLOOR
};

enum TILE_RENDER_LAYERS
{
	RENDER_TILES,
	RENDER_UNDER_PLAYER_ITEMS,
	RENDER_ITEMS,
	RENDER_ABOVE_PLAYER,
	RENDER_ROOF
};

enum INVENTORY_ITEM_TYPES
{
	INVENTORY_NULL_ITEM,
	INVENTORY_FLOOR_TILE_1,
	INVENTORY_WALL_TILE_1,
	INVENTORY_WALL_TILE_2,
	INVENTORY_FRENZEL_1,
	INVENTORY_FRENZEL_2,
	INVENTORY_DOOR_TILE_1,
	INVENTORY_DOOR_TILE_2,
	INVENTORY_RESOURCE_1,
	INVENTORY_OXYGEN_MACHINE,
	INVENTORY_IRON_ORE,
	INVENTORY_COBALT_ORE,
	INVENTORY_NICKEL_ORE,
	INVENTORY_PROCESSED_IRON,
	INVENTORY_PROCESSED_COBALT,
	INVENTORY_PROCESSED_NICKEL,
	INVENTORY_EMPTY_SLOT,
	INVENTORY_SOLAR_ARRAY_1,
	INVENTORY_BED_1,
	INVENTORY_BED_2,
	INVENTORY_STORAGE_1,
	INVENTORY_TREE_1,
	INVENTORY_CONSOLE_1,
	INVENTORY_LOCKER_1,
	INVENTORY_PLANT_1,
	INVENTORY_EMITTER_1,
	INVENTORY_SOYLENT_MACHINE_1,
	INVENTORY_SOYLENT_1,
	INVENTORY_SOYLENT_MEAL_1,
	INVENTORY_SPACESUIT_1,
	INVENTORY_OXYGEN_TANK,
	INVENTORY_MICROWAVE_1,
	INVENTORY_CHAIR_1,
	INVENTORY_TABLE_1,
	INVENTORY_SPACEDOCK_1,
	INVENTORY_MINING_LASER_1,
	INVENTORY_LASER_PISTOL_1,
	INVENTORY_CONSTRUCTION_TUBING_FLOOR_1,
	INVENTORY_CONSTRUCTION_TUBING_WALL_1
};

const int NUM_TILE_STATES = 20;

enum TILE_STATES
{
	TILE_TYPE,
	IS_COLLIDABLE,
	IS_OCCUPIED,
	IS_RESOURCE,
	OXYGENATION_CHECK,
	IS_OXYGENATED,
	LEAK_CHECK,
	IS_DOOR,
	DOOR_CLOSED,
	HEALTH,
	MAX_HEALTH,
	CAN_BE_PICKED_UP,
	INVENTORY_POINTER
};

enum TILE_ORIENTATION
{
	ALL_EDGE,
	TOP_OR_BOTTOM_EDGE,
	LEFT_OR_RIGHT_EDGE,

	UPSIDE_DOWN_T,
	UPRIGHT_T,
	T_BAR_ON_LEFT,
	T_BAR_ON_RIGHT,

	TOP_LEFT_CORNER,
	TOP_RIGHT_CORNER,
	BOTTOM_LEFT_CORNER,
	BOTTOM_RIGHT_CORNER,

	NO_EDGE,

	JUST_LEFT_EDGE,
	JUST_RIGHT_EDGE,
	JUST_TOP_EDGE,
	JUST_BOTTOM_EDGE,

};


// DOT ATTRIBUTEs 

const int NUM_DOT_STATS = 20;

enum DOT_STATS
{
	FPS,
	DOT_IS_COLLIDABLE,
	DOT_TYPE,
	IS_NOT_NULL,
};

enum DOT_PRIORITIES
{
	DOT_PRIORITY_SLEEP_NEED,
	DOT_PRIORITY_HUNGER_NEED,
	DOT_PRIORITY_OXYGEN_NEED,
	DOT_PRIORITY_SPACESUIT_OXYGEN,
	DOT_PRIORITY_ENNUI,
	DOT_PRIORITY_HAPPINESS,
	DOT_PRIORITY_SANITY
};

enum DOT_TYPES
{
	DOT_GENERIC,
	DOT_PLAYER,
	DOT_NPC,
	DOT_ENEMY_SHIP,
	DOT_ASTEROID,
	DOT_CONTAINER,
	DOT_BOLT,
	DOT_SCAFFOLD,
	DOT_TILE
};

enum DOT_FOCUS_TYPES
{
	DOT_FOCUS_DOT_TYPE,
	DOT_FOCUS_TILE_TYPE,
	DOT_FOCUS_INVENTORY_TYPE
};

enum DOT_JOB_TYPE
{
	// DOT HEALTH JOBS ARE IN DESCENDING ORDER OF IMPORTANCE, LOWER JOBS WILL PULL PRIORITY FROM HIGHER JOBS
	DOT_HEALTH_JOB_STOP,
	DOT_HEALTH_JOB_GO_FIND_OXYGENATED_TILE,
	DOT_HEALTH_JOB_GO_GET_SPACESUIT,
	DOT_HEALTH_JOB_GO_TO_BED,
	DOT_HEALTH_JOB_GO_EAT_FOOD,
	DOT_HEALTH_JOB_GO_FIND_FOOD,

	// NON DOT-HEALTH JOBS DO NOT CURRENTLY PULL PRIORITY IN THE SAME WAY
	SPECIFIC_DOT_JOB_STORE_CONTAINER,
	SPECIFIC_DOT_JOB_SHUTTLE_ITEM_TO_PROJECT,
	SPECIFIC_DOT_JOB_COMPILE_PROJECT,
	SPECIFIC_DOT_JOB_BUILD_SCAFFOLD,
	SPECIFIC_DOT_JOB_HARVEST_FRENZEL,
	SPECIFIC_DOT_JOB_TAKE_ITEM_FROM_DOT,
	ITEM_JOB_OXYGENATE,
	ITEM_JOB_TILE_STREAMLINE,
	ITEM_JOB_DOOR,
	ITEM_JOB_GROW_FRENZEL,
	ITEM_JOB_CREATE_SOYLENT,
	ITEM_JOB_CREATE_SOYLENT_MEAL,
	DOT_JOB_NO_ASSIGNED_JOB
};

enum DOT_GOAL_ACTIONS
{
	ACTION_NONE,
	ACTION_SET_DOT_FOCUS_TO_NEAREST_DOT_OF_TYPE,
	ACTION_SET_TILE_FOCUS_TO_NEAREST_TILE_OF_TYPE,
	ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,
	ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,
	ACTION_CHECK_IF_DOT_IS_ON_SPECIFIC_DOT,
	ACTION_CHANGE_DOT_QUANTITY,
	ACTION_GIVE_INVENTORY_TO_ANOTHER_DOT,
	ACTION_TAKE_INVENTORY_FROM_ANOTHER_DOT,
	ACTION_SET_DOT_TO_CARRY_ITEM,
	ACTION_SET_DOT_TO_NOT_CARRY_ITEM,
	ACTION_DROP_ENTIRE_DOT_INVENTORY,
	ACTION_DROP_ALL_INVENTORY_ITEM_OF_TYPE,
	ACTION_ADD_ITEM_TO_DOT_INVENTORY,
	ACTION_REMOVE_ITEM_FROM_DOT_INVENTORY,
	ACTION_REMOVE_BUILDING_ITEMS_FROM_DOT_INVENTORY,
	ACTION_CHANGE_DOT_CONFIG_ATTRIBUTE,
	ACTION_OXYGENATE_AIR,
	ACTION_TILE_STREAMLINE,
	ACTION_DOOR_UPDATE,
	ACTION_GROW_FRENZEL,
	ACTION_GET_INSIDE_ANOTHER_DOT,
	ACTION_GET_OUT_OF_ANOTHER_DOT
};

// DOT INVENTORY

const int MAX_DOT_INVENTORY = 24;
const int MAX_CONSOLE_INVENTORY = 24;
const int NUM_INVENTORY_ROWS = 6;
const int NUM_INVENTORY_COLUMNS = 4;

const int MAX_CONSOLE_CRAFTING_SLOTS = 24;
const int NUM_CONSOLE_CRAFTING_ROWS = 6;
const int NUM_CONSOLE_CRAFTING_COLUMNS = 4;

struct Inventory_Item
{
	int item_code;
	int clip_rect_x;
	int clip_rect_y;
	int tile_or_item;
};

Inventory_Item Inventory_Empty_Slot{ INVENTORY_EMPTY_SLOT,7,0,0 };
Inventory_Item Inventory_Null_Item{ INVENTORY_NULL_ITEM,0,0 };
Inventory_Item Inventory_Iron_Ore{ INVENTORY_IRON_ORE,2,4,1 };
Inventory_Item Inventory_Cobalt_Ore{ INVENTORY_COBALT_ORE,3,4,1 };
Inventory_Item Inventory_Nickel_Ore{ INVENTORY_NICKEL_ORE,4,4,1 };
Inventory_Item Inventory_Oxygen_Machine{ INVENTORY_OXYGEN_MACHINE,3,0,1 };
Inventory_Item Inventory_Door_1{ INVENTORY_DOOR_TILE_1,4,0,1 };
Inventory_Item Inventory_Door_2{ INVENTORY_DOOR_TILE_2,7,1,1 };
Inventory_Item Inventory_Wall_1{ INVENTORY_WALL_TILE_1,5,0,0 };
Inventory_Item Inventory_Wall_2{ INVENTORY_WALL_TILE_2,6,1,0 };
Inventory_Item Inventory_Frenzel_1{ INVENTORY_FRENZEL_1,6,2,0 };
Inventory_Item Inventory_Frenzel_2{ INVENTORY_FRENZEL_2,6,2,0 };
Inventory_Item Inventory_Floor_1{ INVENTORY_FLOOR_TILE_1,6,0,0 };
Inventory_Item Inventory_Solar_Array_1{ INVENTORY_SOLAR_ARRAY_1,3,1,1 };
Inventory_Item Inventory_Bed_1{ INVENTORY_BED_1,4,1,1 };
Inventory_Item Inventory_Bed_2{ INVENTORY_BED_2,5,1,1 };
Inventory_Item Inventory_Storage_1{ INVENTORY_STORAGE_1,0,2,1 };
Inventory_Item Inventory_Tree_Tile_1{ INVENTORY_TREE_1, 1,2,1 };
Inventory_Item Inventory_Console_Tile_1{ INVENTORY_CONSOLE_1, 3,2,1 };
Inventory_Item Inventory_Locker_Tile_1{ INVENTORY_LOCKER_1, 4,2,1 };
Inventory_Item Inventory_Plant_1{ INVENTORY_PLANT_1, 5,2,1 };
Inventory_Item Inventory_Emitter_1{ INVENTORY_EMITTER_1,7,2,1 };
Inventory_Item Inventory_Soylent_Machine_1{ INVENTORY_SOYLENT_MACHINE_1,2,3,1 };
Inventory_Item Inventory_Soylent_1{ INVENTORY_SOYLENT_1,1,3,1 };
Inventory_Item Inventory_Soylent_Meal_1{ INVENTORY_SOYLENT_MEAL_1,5,3,1 };
Inventory_Item Inventory_Spacesuit_1{ INVENTORY_SPACESUIT_1, 0,4,1 };
Inventory_Item Inventory_Oxygen_Tank{ INVENTORY_OXYGEN_TANK,5,4,1};
Inventory_Item Inventory_Microwave_1{ INVENTORY_MICROWAVE_1, 4,3,1 };
Inventory_Item Inventory_Chair_1{ INVENTORY_CHAIR_1, 6,3,1 };
Inventory_Item Inventory_Table_1{ INVENTORY_TABLE_1, 7,3,1 };
Inventory_Item Inventory_Spacedock_1{ INVENTORY_SPACEDOCK_1, 1,4,1 };
Inventory_Item Inventory_Processed_Iron{ INVENTORY_PROCESSED_IRON, 0,0,1 };
Inventory_Item Inventory_Processed_Cobalt{ INVENTORY_PROCESSED_COBALT, 1,0,1 };
Inventory_Item Inventory_Processed_Nickel{ INVENTORY_PROCESSED_NICKEL, 2,0,1 };
Inventory_Item Inventory_Mining_Laser_1{ INVENTORY_MINING_LASER_1, 6,4,1 };
Inventory_Item Inventory_Laser_Pistol_1{ INVENTORY_LASER_PISTOL_1,7,4,1 };
Inventory_Item Inventory_Construction_Tubing_Floor_1{ INVENTORY_CONSTRUCTION_TUBING_FLOOR_1,5,1,0 };
Inventory_Item Inventory_Construction_Tubing_Wall_1{ INVENTORY_CONSTRUCTION_TUBING_WALL_1,5,1,0 };

const int MAX_BUILDING_REQUIREMENTS = 6;

struct Building_Spec
{
	Inventory_Item Requirement_1 = Inventory_Empty_Slot;
	int Requirement_1_Quantity = 0;
	Inventory_Item Requirement_2 = Inventory_Empty_Slot;
	int Requirement_2_Quantity = 0;
	Inventory_Item Requirement_3 = Inventory_Empty_Slot;
	int Requirement_3_Quantity = 0;
	Inventory_Item Requirement_4 = Inventory_Empty_Slot;
	int Requirement_4_Quantity = 0;
	Inventory_Item Requirement_5 = Inventory_Empty_Slot;
	int Requirement_5_Quantity = 0;
	Inventory_Item Requirement_6 = Inventory_Empty_Slot;
	int Requirement_6_Quantity = 0;
};

Building_Spec no_requirements;
Building_Spec cannot_build = { Inventory_Null_Item, 1 };
Building_Spec Wall_and_Floor_Specs = { Inventory_Processed_Iron, 1 };
Building_Spec Oxygen_Machine_1_Specs = { Inventory_Processed_Cobalt, 1 };
Building_Spec Solar_Array_Specs_1 = { Inventory_Processed_Cobalt, 1, Inventory_Processed_Iron, 2 };
Building_Spec Soylent_Machine_Specs = { Inventory_Processed_Iron, 5 };
Building_Spec Soylent_Specs_1 = { Inventory_Frenzel_1,1 };
Building_Spec Soylent_Meal_Specs_1 = { Inventory_Soylent_1,1 };
Building_Spec Specs_Processed_Iron = { Inventory_Iron_Ore, 2 };
Building_Spec Specs_Processed_Cobalt = { Inventory_Cobalt_Ore, 2 };
Building_Spec Specs_Processed_Nickel = { Inventory_Nickel_Ore, 2 };

struct Sprite_Specs
{
	int sprite_column = 0;
	int sprite_row = 0;
	int sprite_columns = 0;
	int sprite_rows = 0;
	int rect_columns = 0;
	int rect_rows = 0;
};

struct Multi_Tile_Type
{
	int tile_name = TILE_NULL;
	int spritesheet_num = TILESHEET;
	Sprite_Specs sprite_specs;
	int tile_type = 99;
	int tile_or_item = 0; // 0 is tile, 1 is item
	int is_collidable = 0;
	int can_be_placed_in_vacuum = 0;
	int oxygenation_check = 0;
	int is_oxygenated = 0;
	int leak_check = 0;
	int door_state = 0; // 0 is not door, 1 is open, 2 is closed
	int door_open_length = 0;
	int current_health = 34;
	int max_health = 34;
	int is_passively_picked_up = 0; // for things like ore etc - 0 is no, 1 is yes
	Inventory_Item inventory_pointer = Inventory_Empty_Slot;
	int is_animated = 0; // 0 is no, anything greater than zero is number of frames
	int is_smooth = 0; 
	Building_Spec building_specs = no_requirements;
	int built_percent = 100;
	int item_job_type = DOT_JOB_NO_ASSIGNED_JOB;
	int render_layer = RENDER_TILES;
};

vector<Multi_Tile_Type> tile_vector;
Multi_Tile_Type null_tile; 

void Load_Tiles()
{
	tile_vector.push_back({ TILE_IRON_ORE, CONTAINER_SPRITESHEET,{ 0,0,1,1,1,1 },ITEM_TYPE_ORE,1,1,0,0,0,0,0,0,34,34,1,Inventory_Iron_Ore,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_COBALT_ORE, CONTAINER_SPRITESHEET,{ 0,1,1,1,1,1 }, ITEM_TYPE_ORE,1,1,0,0,0,0,0,0,34,34,1,Inventory_Cobalt_Ore,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_NICKEL_ORE, CONTAINER_SPRITESHEET,{ 0,2,1,1,1,1 },ITEM_TYPE_ORE,1,1,0,0,0,0,0,0,34,34,1,Inventory_Nickel_Ore,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_vector.push_back({ TILE_PROCESSED_IRON, TILESHEET,{ 0,0,1,1,1,1 },ITEM_TYPE_PROCESSED_ORE,1,1,0,0,0,0,0,0,34,34,1,Inventory_Processed_Iron,0,0, Specs_Processed_Iron,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_PROCESSED_COBALT, TILESHEET,{ 0,1,1,1,1,1 }, ITEM_TYPE_PROCESSED_ORE,1,1,0,0,0,0,0,0,34,34,1,Inventory_Processed_Cobalt,0,0, Specs_Processed_Cobalt,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_PROCESSED_NICKEL, TILESHEET,{ 0,2,1,1,1,1 },ITEM_TYPE_PROCESSED_ORE,1,1,0,0,0,0,0,0,34,34,1,Inventory_Processed_Nickel,0,0, Specs_Processed_Nickel,100,0,RENDER_UNDER_PLAYER_ITEMS });
	
	tile_vector.push_back({ TILE_GENERIC_TILE,TILESHEET,{ 3,0,1,1,1,1 },VACUUM,0,0,1,0,0,0,0,0,34,34,0,Inventory_Empty_Slot,0,0,cannot_build,100,0,RENDER_TILES });

	tile_vector.push_back({ TILE_GENERIC_ITEM,TILESHEET,{ 3,0,1,1,1,1 },VACUUM, 1, 0,1, 0, 0, 0, 0, 0, 34, 34, 0, Inventory_Empty_Slot, 0, 0, cannot_build, 100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_OXYGEN_MACHINE, ITEM_SPRITES,{ 0,0,1,1,1,1 },OXYGEN_MACHINE,1,1,0,0,0,0,0,0,34,34,0,Inventory_Oxygen_Machine,8,0, Oxygen_Machine_1_Specs,100,ITEM_JOB_OXYGENATE,RENDER_ITEMS });
	tile_vector.push_back({ TILE_SOLAR_ARRAY_1, ITEM_SPRITES,{ 0,5,1,1,1,1 },SOLAR_ARRAY,1,1,1,0,0,0,0,0,34,34,0,Inventory_Solar_Array_1,8,0 , Solar_Array_Specs_1,100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_FLOOR_TILE_1, TILESHEET,{ 0,0,1,1,1,1 },FLOOR_TILE_1,0,0,1,0,0,0,0,0,34,34,0,Inventory_Floor_1,0,0, Wall_and_Floor_Specs,100,0,RENDER_TILES });
	tile_vector.push_back({ TILE_STORAGE_TILE_1, TILESHEET,{ 7,0,1,1,1,1 },STORAGE_TILE_1,0,0,0,0,0,0,0,0,34,34,0,Inventory_Storage_1,0,0, Wall_and_Floor_Specs,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_vector.push_back({ TILE_WALL_TILE_1, TILESHEET,{ 5,2,1,1,1,1 },WALL_TILE,1,1,1,0,0,0,0,0,34,34,0,Inventory_Wall_1,0,0, Wall_and_Floor_Specs,100,ITEM_JOB_TILE_STREAMLINE,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_WALL_TILE_2, TILESHEET,{ 1,2,1,1,1,1 },WALL_TILE,1,1,1,0,0,0,0,0,34,34,0,Inventory_Wall_2,0,0, Wall_and_Floor_Specs,100,ITEM_JOB_TILE_STREAMLINE,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_FRENZEL_1, TILESHEET,{ 5,6,1,1,1,1 },TILE_TYPE_FRENZEL,0,0,1,0,0,0,0,0,34,34,0,Inventory_Frenzel_1,0,0, cannot_build,100,ITEM_JOB_GROW_FRENZEL,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_FRENZEL_2, ITEM_SPRITES,{ 0,10,1,1,1,1 },ITEM_TYPE_FRENZEL,1,1,1,0,0,0,0,0,34,34,0,Inventory_Frenzel_2,8,0, cannot_build,100,0,RENDER_TILES });



	tile_vector.push_back({ TILE_VACUUM, TILESHEET,{ 5,0,1,1,1,1 },VACUUM,0,0,1,0,0,0,0,0,34,34,0,Inventory_Empty_Slot,0,0, cannot_build,100,0,RENDER_TILES });
	tile_vector.push_back({ TILE_VACUUM_2, TILESHEET,{ 4,0,1,1,1,1 },VACUUM,0,0,1,0,0,0,0,0,34,34,0,Inventory_Empty_Slot,0,0, cannot_build,100,0,RENDER_TILES });

	tile_vector.push_back({ TILE_BED_1, TILESHEET,{ 0,11,2,1,2,1 }, ITEM_TYPE_BED,1,1,0,0,0,0,0,0,34,34,0,Inventory_Bed_1,0,0, no_requirements,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_vector.push_back({ TILE_TREE_1, TILESHEET,{ 0,9,1,-2,1,1 },TREE,1,1,0,0,0,0,0,0,34,34,0,Inventory_Tree_Tile_1,0,0, no_requirements,100,0,RENDER_ITEMS });
	tile_vector.push_back({ TILE_CONSOLE_1, ITEM_SPRITES,{ 0,3,2,-2,2,1 },CONSOLE,1,1,0,0,0,0,0,0,34,34,0,Inventory_Console_Tile_1,4,0, no_requirements,100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_LOCKER_1, TILESHEET,{ 1,9,1,-2,1,1 },STORAGE_TILE_1,1,1,0,0,0,0,0,0,34,34,0,Inventory_Locker_Tile_1,0,0, no_requirements,100,0,RENDER_ITEMS });
	tile_vector.push_back({ TILE_SPACESUIT_1, TILESHEET,{ 1,1,1,1,1,1 },INVENTORY_TYPE_SUIT,1,1,0,0,0,0,0,0,34,34,0,Inventory_Spacesuit_1,0,0, cannot_build,100,0,RENDER_ITEMS });
	tile_vector.push_back({ TILE_OXYGEN_TANK, TILESHEET,{ 3,9,1,1,1,1 },ITEM_TYPE_OXYGEN_TANK,1,1,0,0,0,0,0,0,34,34,0,Inventory_Oxygen_Tank,0,0, cannot_build,100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_PLANT_1, ITEM_SPRITES,{ 0,8,1,-2,1,1 },TILE_TYPE_PLANT,1,1,0,0,0,0,0,0,34,34,0,Inventory_Plant_1,8,0, cannot_build,100,0,RENDER_ITEMS });
	tile_vector.push_back({ TILE_EMITTER_1, ITEM_SPRITES,{ 0,11,1,-2,1,1 },ITEM_TYPE_EMITTER,1,1,1,0,0,0,0,0,34,34,0,Inventory_Emitter_1,8,0, cannot_build,100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_SOYLENT_MACHINE_1, ITEM_SPRITES,{ 0,13,1,-2,1,1 },ITEM_TYPE_SOYLENT_MACHINE,1,1,1,0,0,0,0,0,34,34,0,Inventory_Soylent_Machine_1,8,0, Soylent_Machine_Specs,100,ITEM_JOB_CREATE_SOYLENT,RENDER_ITEMS });
	tile_vector.push_back({ TILE_SOYLENT_1, TILESHEET,{ 2,9,1,1,1,1 },ITEM_TYPE_FOOD,1,0,1,0,0,0,0,0,34,34,0,Inventory_Soylent_1,0,0, Soylent_Specs_1,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_SOYLENT_MEAL_1, TILESHEET,{ 2,10,1,1,1,1 },ITEM_TYPE_FOOD,1,0,1,0,0,0,0,0,34,34,0,Inventory_Soylent_Meal_1,0,0, Soylent_Meal_Specs_1,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_vector.push_back({ TILE_MICROWAVE_1, ITEM_SPRITES,{ 0,15,1,-2,1,1 },ITEM_TYPE_FOOD_PREPARATION,1,1,1,0,0,0,0,0,34,34,0,Inventory_Microwave_1,8,0, cannot_build,100,ITEM_JOB_CREATE_SOYLENT_MEAL,RENDER_ITEMS });
	tile_vector.push_back({ TILE_CHAIR_1, TILESHEET,{ 2,11,1,1,1,1 },ITEM_TYPE_CHAIR,1,1,0,0,0,0,0,0,34,34,0,Inventory_Chair_1,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_vector.push_back({ TILE_TABLE_1, TILESHEET,{ 5,10,1,1,1,1 },ITEM_TYPE_TABLE,1,1,0,0,0,0,0,0,34,34,0,Inventory_Table_1,0,0, cannot_build,100,ITEM_JOB_TILE_STREAMLINE,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_SPACEDOCK_1, ITEM_SPRITES,{ 0,17,1,-2,1,1 },ITEM_TYPE_SPACEDOCK,1,1,0,0,0,0,0,0,34,34,0,Inventory_Spacedock_1,0,0, cannot_build,100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_MINING_LASER_1, TILESHEET,{ 3,10,1,1,1,1 },ITEM_TYPE_MINING_LASER,1,1,0,0,0,0,0,0,34,34,0,Inventory_Mining_Laser_1,0,0, cannot_build,100,0,RENDER_ITEMS });
	tile_vector.push_back({ TILE_LASER_PISTOL_1, TILESHEET,{ 3,11,1,1,1,1 },ITEM_TYPE_WEAPON,1,1,0,0,0,0,0,0,34,34,0,Inventory_Laser_Pistol_1,0,0, cannot_build,100,0,RENDER_ITEMS });

	tile_vector.push_back({ TILE_CONSTRUCTION_TUBE_FLOOR_1, TILESHEET,{ 5,13,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_FLOOR,0,0,1,0,0,0,0,0,34,34,0,Inventory_Construction_Tubing_Floor_1,0,1, no_requirements,100 });
	tile_vector.push_back({ TILE_CONSTRUCTION_TUBE_WALL_1, TILESHEET,{ 0,13,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_WALL,0,1,1,0,0,0,0,0,34,34,0,Inventory_Construction_Tubing_Wall_1,0,1, no_requirements,100 });
	tile_vector.push_back({ TILE_DOOR_1,ITEM_SPRITES,{ 0,1,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_WALL,0,1,0,0,0,0,2,0,34,34,0,Inventory_Door_1,7,0, Wall_and_Floor_Specs,100,ITEM_JOB_DOOR,RENDER_UNDER_PLAYER_ITEMS });
	tile_vector.push_back({ TILE_DOOR_2,ITEM_SPRITES,{ 0,6,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_WALL,0,1,0,0,0,0,2,0,34,34,0,Inventory_Door_2,7,0, Wall_and_Floor_Specs,100,ITEM_JOB_DOOR,RENDER_UNDER_PLAYER_ITEMS });
}

Multi_Tile_Type Return_Tile_By_Name(int tile_identifier)
{
	for (int i = 0; i < tile_vector.size(); i++)
	{
		if (tile_vector[i].tile_name == tile_identifier) return tile_vector[i];
	}
	cout << "couldn't find tile by that identifier" << endl;
}

Multi_Tile_Type Return_Tile_By_Inventory_Item(Inventory_Item inventory_item)
{
	for (int i = 0; i < tile_vector.size(); i++)
	{
		if (tile_vector[i].inventory_pointer.item_code == inventory_item.item_code) return tile_vector[i];
	}
	cout << "couldn't find tile by that inventory_item: " << inventory_item.item_code << endl;
}

struct Dot_Inventory_Slot
{
	Inventory_Item item_type;
	int item_number = 0;
};

struct Tile_Init
{
	int tile_x_num = 0;
	int tile_y_num = 0;
	Multi_Tile_Type world_tile_type;
	bool item_on_tile = false;
	Multi_Tile_Type item_tile_type;
};

struct Asteroid_Init
{
	bool initialized;
	int x_pos;
	int y_pos;
	int angle;
	int spin_direction;
	int spin_speed;
	int health;
};



#endif