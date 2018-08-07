#ifndef CONFIG_H
#define CONFIG_H

void print(string print_string);

const int DEBUG_CONSOLE = 0;
const int DEBUG_MAIN_FUNCTION = 0;
const int DEBUG_INTELLIGENCE = 0;
const int DEBUG_AI = 0;
const int DEBUG_DOT_JOB = 0;
const int DEBUG_PLAYER_DOT = 0;
const int DEBUG_RENDER = 0;
const int DEBUG_ADVANCED_DOT_DIAGNOSTICS = 0;

//Screen dimension constants
const int TILE_HEIGHT = 32;
const int TILE_WIDTH = 32;

const int SCROLL_SPEED = 5;

struct Tile_Queue
{
	int x_tile;
	int y_tile;
	int order;
};

const int SPRITESHEET_W = 34;
const int SPRITESHEET_H = 34;
const int LIGHT_SPRITE_W = 128;
const int LIGHT_SPRITE_H = 128;

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

const int NUM_TILESHEETS = 20; // Change this when adding or subtracting spritesheets

enum Spritesheets
{
	TILESHEET,
	ITEM_SPRITES,
	CONSOLE_BACKGROUND,
	BOLT_SPRITES,
	DOT_SPRITESHEET,
	DOT_SPRITESHEET_LEGS,
	DOT_SPRITESHEET_ARMS,
	DOT_SPRITESHEET_TORSOS,
	DOT_SPRITESHEET_HEADS,
	DOT_SPRITESHEET_EQUIPMENT,
	DOT_SPRITESHEET_MISC,
	ASTEROID_SPRITESHEET,
	INVENTORY_SPRITESHEET,
	ENEMY_SHIP_SPRITESHEET,
	CONTAINER_SPRITESHEET,
	SPRITESHEET_LIGHTS,
	SPRITESHEET_BACKGROUND
};

// ANIMATION FRAMES
const int MAX_ANIMATION_FRAMES = 4;
const int DOOR_OPEN_PAUSE = 64;

//PHYSICS CONSTANTS

const int COLLISION_CHECK_RADIUS = 50;

//PROJECTILES
const int MAX_PROJECTILES = 40;

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
	BUTTON_ACTION_MINE_ASTEROID,
	BUTTON_ACTION_REMOVE_TILE,
	BUTTON_ACTION_ATTACK,
	BUTTON_ACTION_DO_NOTHING,
	BUTTON_ACTION_PLACE_SCAFFOLD,
	BUTTON_ACTION_INVENTORY_BUTTON,
	BUTTON_ACTION_SWITCH_PANEL,
	BUTTON_ACTION_CRAFT_ITEM,
	BUTTON_ACTION_RESTART_GAME,
	BUTTON_ACTION_QUIT_GAME,
	BUTTON_ACTION_CREATE_PRODUCTION_ORDER,
	BUTTON_ACTION_CLEAR_DOT_GOALS,
	BUTTON_ACTION_SPAWN_ENEMY,
	BUTTON_ACTION_CLOSE_CONSOLE_WINDOW,
	BUTTON_ACTION_MOVE_CONSOLE_WINDOW
};

enum Console_Windows
{
	NULL_WINDOW,
	WINDOW_PLAYER_DIAGNOSTIC,
	WINDOW_OPTIONS,
	WINDOW_ACTION_BUTTONS,

	// MAKE SURE THIS GOES LAST //
	WINDOW_DOT_DIAGNOSTIC,
};

enum Console_Window_Panels
{
	PANEL_NO_PANEL,
	PANEL_CONSOLE_WINDOW_BUTTONS,
	PANEL_DOT_INVENTORY,
	PANEL_DOT_DIAGNOSTIC,
	PANEL_EQUIPMENT_LOADOUT,
	PANEL_CRAFTABLE_ITEMS,
	PANEL_OPTIONS_RESTART,
	PANEL_ACTION_BUTTONS,
	PANEL_PRODUCTION_ORDERS,
	PANEL_JOB_DIAGNOSTIC, 
	PANEL_CLOSE_CONSOLE_WINDOW
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
	TILE_FRENZEL_MEAT_1,
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
	TILE_MINING_LASER_1,
	TILE_LASER_PISTOL_1,
	TILE_CONSTRUCTION_TUBE_WALL_1,
	TILE_CONSTRUCTION_TUBE_FLOOR_1,
	TILE_ASTEROID_IRON,
	TILE_ASTEROID_COBALT,
	TILE_ASTEROID_NICKEL,
	TILE_SMELTER_1,
	TILE_WATER_CANISTER_1,
	TILE_LASER_TURRET_GREEN,
	TILE_INTERIOR_LIGHT_1
};

enum TILE_TYPES_AND_ITEM_TYPES
{
	VACUUM,
	TILE_TYPE_GENERIC,
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
	TILE_TYPE_STORAGE_TILE,
	SCAFFOLD_1,
	TREE,
	CONSOLE,
	LOCKER,
	TILE_TYPE_PLANT,
	TILE_TYPE_FRENZEL,
	TILE_TYPE_ASTEROID,
	ITEM_TYPE_FRENZEL,
	ITEM_TYPE_EMITTER,
	ITEM_TYPE_SOYLENT_MACHINE,
	ITEM_TYPE_FOOD,
	ITEM_TYPE_CHAIR,
	INVENTORY_TYPE_SUIT,
	ITEM_TYPE_OXYGEN_TANK,
	ITEM_TYPE_FOOD_PREPARATION,
	ITEM_TYPE_TABLE,
	ITEM_TYPE_MINING_LASER,
	ITEM_TYPE_WEAPON,
	TILE_TYPE_CONSTRUCTION_TUBING_WALL,
	TILE_TYPE_CONSTRUCTION_TUBING_FLOOR,
	TILE_TYPE_CONSTRUCTION_TUBING_DOOR,
	TILE_TYPE_SMELTER,
	TILE_TYPE_TURRET,
	TILE_TYPE_LIGHT
};

enum TILE_RENDER_LAYERS
{
	RENDER_TILES,
	RENDER_UNDER_PLAYER_ITEMS,
	RENDER_ITEMS,
	RENDER_ABOVE_PLAYER,
	RENDER_ROOF,
	RENDER_LIGHTS
};

enum INVENTORY_ITEM_CODES
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
	INVENTORY_FRENZEL_MEAT_1,
	INVENTORY_SOYLENT_MEAL_1,
	INVENTORY_SPACESUIT_1,
	INVENTORY_OXYGEN_TANK,
	INVENTORY_MICROWAVE_1,
	INVENTORY_CHAIR_1,
	INVENTORY_TABLE_1,
	INVENTORY_MINING_LASER_1,
	INVENTORY_LASER_PISTOL_1,
	INVENTORY_CONSTRUCTION_TUBING_FLOOR_1,
	INVENTORY_CONSTRUCTION_TUBING_WALL_1,
	INVENTORY_SMELTER_1,
	INVENTORY_WATER_CANISTER_1,
	INVENTORY_LASER_TURRET_GREEN
};

enum INVENTORY_ITEM_TYPES
{
	INVENTORY_TYPE_EMPTY,
	INVENTORY_TYPE_WEAPON,
	INVENTORY_TYPE_MINING_LASER,
	INVENTORY_TYPE_SPACESUIT,
	INVENTORY_TYPE_BUILDING_TILE,
	INVENTORY_TYPE_ITEM,
	INVENTORY_TYPE_FOOD,
	INVENTORY_TYPE_OXYGEN_TANK,
	INVENTORY_TYPE_ORE,
	INVENTORY_TYPE_TURRET
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
	DOT_PRIORITY_SANITY,
	DOT_PRIORITY_WEAPON_COOLDOWN,
	DOT_PRIORITY_PATH_CHECK_COOLDOWN
};

enum DOT_TYPES
{
	DOT_GENERIC,
	DOT_PLAYER,
	DOT_NPC,
	DOT_ENEMY_SHIP,
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
	DOT_HEALTH_MOVE_AWAY_FROM_DANGER,
	DOT_HEALTH_JOB_GO_FIND_OXYGENATED_TILE,
	DOT_HEALTH_JOB_GO_GET_SPACESUIT,
	DOT_HEALTH_JOB_GO_TO_BED,
	DOT_HEALTH_JOB_GO_EAT_FOOD,
	DOT_HEALTH_JOB_GO_FIND_FOOD,
	DOT_HEALTH_JOB_ELIMINATE_DOT,
	DOT_HEALTH_JOB_DUMP_STORAGE,

	// NON DOT-HEALTH JOBS DO NOT CURRENTLY PULL PRIORITY IN THE SAME WAY
	SPECIFIC_DOT_JOB_COLLECT_CONTAINER,
	SPECIFIC_DOT_JOB_SHUTTLE_ITEM_TO_PROJECT,
	SPECIFIC_DOT_JOB_COMPILE_PROJECT,
	SPECIFIC_DOT_JOB_BUILD_SCAFFOLD,
	SPECIFIC_DOT_JOB_TAKE_ITEM_FROM_DOT,
	SPECIFIC_DOT_JOB_MINE_ASTEROID,
	ITEM_JOB_OXYGENATE,
	ITEM_JOB_TILE_STREAMLINE,
	ITEM_JOB_DOOR,
	ITEM_JOB_GROW_FRENZEL,
	ITEM_JOB_PRODUCE_ITEM,
	ITEM_JOB_POPULATE_INVENTORY,
	ITEM_JOB_TURRET,
	ITEM_JOB_LIGHT_SURROUNDING_TILES,

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
	ACTION_CHECK_IF_DOT_IS_IN_RANGE_OF_SPECIFIC_DOT,
	ACTION_CHECK_IF_DOT_IS_AT_SPECIFIED_RANGE,
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
	ACTION_GET_OUT_OF_ANOTHER_DOT,
	ACTION_FIRE_AT_ANOTHER_DOT,
	ACTION_FIRE_LASER_AT_DOT,
	ACTION_STOP_FIRING_LASER_AT_DOT,
	ACTION_STOP_MOVING,
	ACTION_LIGHT_SURROUNDING_TILES,
	ACTION_TURN_TOWARDS_DOT

};

enum DOT_FACTION
{
	DOT_FACTION_PLAYER,
	DOT_FACTION_ENEMY,
	DOT_FACTION_FRIEND,
	DOT_FACTION_NO_FACTION
};

enum DOT_COMPOSITE_PARTS
{
	DOT_COMPOSITE_LEGS,
	DOT_COMPOSITE_ARMS,
	DOT_COMPOSITE_TORSO,
	DOT_COMPOSITE_HEAD,
	DOT_COMPOSITE_SPACESUIT,
	DOT_COMPOSITE_SHADOW
};

enum DOT_FUNCTIONAL_RELATIONSHIP_TYPES
{
	DOT_FUNCTIONAL_RELATIONSHIP_CURRENT_STORAGE_TILE,
	DOT_FUNCTIONAL_RELATIONSHIP_CLOSEST_FRENZEL_EMITTER,
	DOT_FUNCTIONAL_RELATIONSHIP_FIRING_DOT,
	DOT_FUNCTIONAL_RELATIONSHIP_MOST_RECENT_ATTACKER,
	DOT_FUNCTIONAL_RELATIONSHIP_MOST_RECENT_TARGET
};

enum DOT_EQUIPMENT_SLOTS
{
	DOT_EQUIPMENT_SPACESUIT,
	DOT_EQUIPMENT_WEAPON,
	DOT_EQUIPMENT_OXYGEN_TANK,
	DOT_EQUIPMNET_MINING_LASER
};

struct dot_composite_config
{
	int leg_type = 0;
	int arm_type = 0;
	int torso_type = 0;
	int head_type = 0;
	int spacesuit_type = 0;
};

struct dot_faction_relationship {
	int faction_one;
	int faction_two; 
	int relationship_index = 0;
};

const int MAX_DOT_INVENTORY = 24;
const int MAX_CONSOLE_INVENTORY = 24;
const int NUM_INVENTORY_ROWS = 6;
const int NUM_INVENTORY_COLUMNS = 4;

const int MAX_CONSOLE_CRAFTING_SLOTS = 24;
const int NUM_CONSOLE_CRAFTING_ROWS = 6;
const int NUM_CONSOLE_CRAFTING_COLUMNS = 4;

// ITEM AND INVENTORY CONFIG

struct Inventory_Item_Weapon_Config
{
	int weapon_range;
};

Inventory_Item_Weapon_Config default_config = { 128 };

struct Inventory_Item_Template
{
	int item_code;
	string item_name;
	SDL_Rect sprite_config;
	int tile_or_item;
	int item_type;
	Inventory_Item_Weapon_Config weapon_config = default_config;
};

struct Dot_Inventory_Slot
{
	int inventory_item_code;
	int item_number = 0;
};

// BUILDING REQUIREMENTS 

const int MAX_BUILDING_REQUIREMENTS = 6;

struct Building_Spec_Requirement
{
	int inventory_requirement = INVENTORY_EMPTY_SLOT;
	int requirement_quantity = 0;
};

struct Building_Spec
{
	Building_Spec_Requirement Requirement_1 = { INVENTORY_EMPTY_SLOT,0 };
	Building_Spec_Requirement Requirement_2 = { INVENTORY_EMPTY_SLOT,0 };
	Building_Spec_Requirement Requirement_3 = { INVENTORY_EMPTY_SLOT,0 };
	Building_Spec_Requirement Requirement_4 = { INVENTORY_EMPTY_SLOT,0 };
	Building_Spec_Requirement Requirement_5 = { INVENTORY_EMPTY_SLOT,0 };
	Building_Spec_Requirement Requirement_6 = { INVENTORY_EMPTY_SLOT,0 };
};

Building_Spec no_requirements;
Building_Spec Specs_Frenzel_Meat = { {INVENTORY_WATER_CANISTER_1,1} };
Building_Spec cannot_build = { {INVENTORY_NULL_ITEM, 1} };
Building_Spec Wall_and_Floor_Specs = { {INVENTORY_PROCESSED_IRON, 1} };
Building_Spec Oxygen_Machine_1_Specs = { {INVENTORY_PROCESSED_COBALT, 1} };
Building_Spec Solar_Array_Specs_1 = { {INVENTORY_PROCESSED_COBALT, 1}, {INVENTORY_PROCESSED_IRON, 2} };
Building_Spec Soylent_Machine_Specs = { {INVENTORY_PROCESSED_IRON, 5} };
Building_Spec Soylent_Specs_1 = { {INVENTORY_FRENZEL_MEAT_1,1} };
Building_Spec Soylent_Meal_Specs_1 = { {INVENTORY_SOYLENT_1,1} };
Building_Spec Specs_Processed_Iron = { {INVENTORY_IRON_ORE, 2} };
Building_Spec Specs_Processed_Cobalt = { {INVENTORY_COBALT_ORE, 2} };
Building_Spec Specs_Processed_Nickel = { {INVENTORY_NICKEL_ORE, 2} };
Building_Spec Specs_Frenzel_Farm = { {INVENTORY_FRENZEL_1, 1} };
Building_Spec Specs_Frenzel_Beacon = { {INVENTORY_PROCESSED_IRON, 1},{INVENTORY_PROCESSED_COBALT,1} };
Building_Spec Microwave_Specs = { {INVENTORY_PROCESSED_COBALT, 2} };

// PRODUCTION REQUIREMENTS

struct Production_Items
{
	int tile_name_1 = TILE_GENERIC_TILE;
	int tile_name_2 = TILE_GENERIC_TILE;
	int tile_name_3 = TILE_GENERIC_TILE;
	int tile_name_4 = TILE_GENERIC_TILE;
	int tile_name_5 = TILE_GENERIC_TILE;
	int tile_name_6 = TILE_GENERIC_TILE;
};

Production_Items no_produced_items;
Production_Items smelter_1 = { TILE_PROCESSED_IRON, TILE_PROCESSED_COBALT,TILE_PROCESSED_NICKEL };
Production_Items frenzel_1 = { TILE_FRENZEL_MEAT_1 };
Production_Items soylent_1 = { TILE_SOYLENT_1 };
Production_Items soylent_meal_1 = { TILE_SOYLENT_MEAL_1 };

struct Sprite_Specs
{
	int sprite_column = 0;
	int sprite_row = 0;
	int sprite_columns = 0;
	int sprite_rows = 0;
	int rect_columns = 0;
	int rect_rows = 0;
};

struct Light_Specs
{
	int is_light_source = 0;
	SDL_Color light_color = { 0,0,0,0 };
	int radius = 0;
	int attenuation = 0;
	int brightness = 0;
};

Light_Specs no_light = { 0,{0,0,0,0},0,0 };
Light_Specs interior_light_soft_yellow = { 1,{255,255,150,0},200,1,200 };
Light_Specs laser_turret_green_light_1 = { 1,{ 100,255,100,0 },50,1,100 };
Light_Specs frenzel_beacon_light_1 = { 1,{255,100,100,0},100,1,255 };
Light_Specs smelter_light_1 = { 1,{ 255,150,100,0 },50,1,100 };

struct Tile_Template
{
	string tile_descriptor = "Null Tile";
	int tile_name = TILE_NULL;
	int spritesheet_num = TILESHEET;
	Sprite_Specs sprite_specs;
	int tile_type = 99;
	int tile_or_item = 0; // 0 is tile, 1 is item
	int is_collidable = 0;
	int can_be_placed_in_vacuum = 0;
	int oxygenation_check = 0;
	float is_oxygenated = 0.0;
	int leak_check = 0;
	int door_state = 0; // 0 is not door, 1 is open, 2 is closed
	int door_open_length = 0;
	int current_health = 34;
	int max_health = 34;
	int empty_config_slot = 0; 
	int inventory_pointer = INVENTORY_EMPTY_SLOT;
	int is_animated = 0; // 0 is no, anything greater than zero is number of frames
	int is_smooth = 0; 
	Building_Spec building_specs = no_requirements;
	int build_time = 100;
	int item_job_type = DOT_JOB_NO_ASSIGNED_JOB;
	int render_layer = RENDER_TILES;
	Production_Items dot_produced_items = no_produced_items;
	int can_be_scaffold = 1;
	Light_Specs light_specs = no_light;
};

unordered_map <int, Inventory_Item_Template> inventory_item_template_map;
vector<Tile_Template> tile_template_vector;
Tile_Template null_tile; 
Inventory_Item_Template null_item;

// GLOBAL SCOPE FUNCTIONS

// LOAD TILE AND INVENTORY TEMPLATE

void Load_Tile_Templates()
{
	tile_template_vector.push_back({ "Iron Asteroid", TILE_ASTEROID_IRON, TILESHEET,{ 0,1,1,1,1,1 },TILE_TYPE_ASTEROID,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_IRON_ORE,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_template_vector.push_back({ "Cobalt Asteroid",TILE_ASTEROID_COBALT, TILESHEET,{ 0,2,1,1,1,1 },TILE_TYPE_ASTEROID,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_COBALT_ORE,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_template_vector.push_back({ "Nickel Asteroid",TILE_ASTEROID_NICKEL, TILESHEET,{ 0,3,1,1,1,1 },TILE_TYPE_ASTEROID,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_NICKEL_ORE,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_template_vector.push_back({ "Iron Ore", TILE_IRON_ORE, CONTAINER_SPRITESHEET,{ 0,0,1,1,1,1 },ITEM_TYPE_ORE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_IRON_ORE,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_template_vector.push_back({ "Cobalt Ore",TILE_COBALT_ORE, CONTAINER_SPRITESHEET,{ 0,1,1,1,1,1 }, ITEM_TYPE_ORE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_COBALT_ORE,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_template_vector.push_back({ "Nickel Ore",TILE_NICKEL_ORE, CONTAINER_SPRITESHEET,{ 0,2,1,1,1,1 },ITEM_TYPE_ORE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_NICKEL_ORE,0,0, cannot_build,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_template_vector.push_back({ "Processed Iron",TILE_PROCESSED_IRON, TILESHEET,{ 0,0,1,1,1,1 },ITEM_TYPE_PROCESSED_ORE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_PROCESSED_IRON,0,0, Specs_Processed_Iron,100,0,RENDER_UNDER_PLAYER_ITEMS, no_produced_items,0 });
	tile_template_vector.push_back({ "Processed Cobalt",TILE_PROCESSED_COBALT, TILESHEET,{ 0,1,1,1,1,1 }, ITEM_TYPE_PROCESSED_ORE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_PROCESSED_COBALT,0,0, Specs_Processed_Cobalt,100,0,RENDER_UNDER_PLAYER_ITEMS,no_produced_items,0 });
	tile_template_vector.push_back({ "Processed Nickel",TILE_PROCESSED_NICKEL, TILESHEET,{ 0,2,1,1,1,1 },ITEM_TYPE_PROCESSED_ORE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_PROCESSED_NICKEL,0,0, Specs_Processed_Nickel,100,0,RENDER_UNDER_PLAYER_ITEMS,no_produced_items,0 });
	
	tile_template_vector.push_back({ "Generic Tile",TILE_GENERIC_TILE,TILESHEET,{ 4,0,1,1,1,1 },VACUUM,0,0,1,0,0,0,0,0,34,34,0,INVENTORY_EMPTY_SLOT,0,0,cannot_build,100,0,RENDER_TILES });

	tile_template_vector.push_back({ "Generic Item",TILE_GENERIC_ITEM,TILESHEET,{ 4,0,1,1,1,1 },VACUUM, 1, 0,1, 0, 0, 0, 0, 0, 34, 34, 0, INVENTORY_EMPTY_SLOT, 0, 0, cannot_build, 100,0,RENDER_ITEMS });

	tile_template_vector.push_back({ "Oxygen Pump",TILE_OXYGEN_MACHINE, ITEM_SPRITES,{ 0,0,1,1,1,1 },OXYGEN_MACHINE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_OXYGEN_MACHINE,8,0, Oxygen_Machine_1_Specs,100,ITEM_JOB_OXYGENATE,RENDER_ITEMS });
	tile_template_vector.push_back({ "Solar Panel",TILE_SOLAR_ARRAY_1, TILESHEET,{ 1,0,1,1,1,1 },SOLAR_ARRAY,1,1,1,0,0,0,0,0,34,34,0,INVENTORY_SOLAR_ARRAY_1,0,0 , Solar_Array_Specs_1,100,0,RENDER_ITEMS });

	tile_template_vector.push_back({ "",TILE_STORAGE_TILE_1, TILESHEET,{ 7,0,1,1,1,1 },TILE_TYPE_STORAGE_TILE,1,0,0,0,0,0,0,0,34,34,0,INVENTORY_STORAGE_1,0,0, Wall_and_Floor_Specs,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_template_vector.push_back({ "Frenzel",TILE_FRENZEL_1, TILESHEET,{ 4,5,1,1,1,1 },TILE_TYPE_FRENZEL,0,0,1,0,0,0,0,0,34,34,0,INVENTORY_FRENZEL_1,0,1, Specs_Frenzel_Farm,100,ITEM_JOB_GROW_FRENZEL,RENDER_TILES,frenzel_1 });
	tile_template_vector.push_back({ "Frenzel Meat",TILE_FRENZEL_MEAT_1, ITEM_SPRITES,{ 0,10,1,1,1,1 },ITEM_TYPE_FRENZEL,1,1,1,0,0,0,0,0,34,34,0,INVENTORY_FRENZEL_MEAT_1,8,0, Specs_Frenzel_Meat,1000,0,RENDER_TILES, no_produced_items,0 });

	tile_template_vector.push_back({ "Vacuum",TILE_VACUUM, TILESHEET,{ 5,0,1,1,1,1 },VACUUM,0,0,1,0,0,0,0,0,34,34,0,INVENTORY_EMPTY_SLOT,0,0, cannot_build,100,0,RENDER_TILES });
	tile_template_vector.push_back({ "More Vacuum",TILE_VACUUM_2, TILESHEET,{ 4,0,1,1,1,1 },VACUUM,0,0,1,0,0,0,0,0,34,34,0,INVENTORY_EMPTY_SLOT,0,0, cannot_build,100,0,RENDER_TILES });

	tile_template_vector.push_back({ "Standard Bed",TILE_BED_1, TILESHEET,{ 0,11,2,1,2,1 }, ITEM_TYPE_BED,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_BED_1,0,0, no_requirements,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_template_vector.push_back({ "Standard Tree",TILE_TREE_1, TILESHEET,{ 0,9,1,-2,1,1 },TREE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_TREE_1,0,0, cannot_build,100,0,RENDER_ITEMS });
	tile_template_vector.push_back({ "Console",TILE_CONSOLE_1, ITEM_SPRITES,{ 0,3,2,-2,2,1 },CONSOLE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_CONSOLE_1,4,0, no_requirements,100,0,RENDER_ITEMS });

	tile_template_vector.push_back({ "Locker",TILE_LOCKER_1, TILESHEET,{ 3,18,1,1,1,1 },TILE_TYPE_STORAGE_TILE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_LOCKER_1,0,0, cannot_build,100,0,RENDER_ITEMS });
	tile_template_vector.push_back({ "Spacesuit",TILE_SPACESUIT_1, TILESHEET,{ 1,1,1,1,1,1 },INVENTORY_TYPE_SUIT,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_SPACESUIT_1,0,0, cannot_build,100,0,RENDER_ITEMS });
	tile_template_vector.push_back({ "Oxygen Tank",TILE_OXYGEN_TANK, TILESHEET,{ 3,9,1,1,1,1 },ITEM_TYPE_OXYGEN_TANK,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_OXYGEN_TANK,0,0, cannot_build,100,0,RENDER_ITEMS });

	tile_template_vector.push_back({ "Standard Plant",TILE_PLANT_1, ITEM_SPRITES,{ 0,8,1,-2,1,1 },TILE_TYPE_PLANT,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_PLANT_1,8,0, cannot_build,100,0,RENDER_ITEMS });
	tile_template_vector.push_back({ "Frenzel Emitter",TILE_EMITTER_1, ITEM_SPRITES,{ 0,11,1,-2,1,1 },ITEM_TYPE_EMITTER,1,1,1,0,0,0,0,0,34,34,0,INVENTORY_EMITTER_1,8,0, Specs_Frenzel_Beacon,100,0,RENDER_ITEMS,no_produced_items,1,frenzel_beacon_light_1 });

	tile_template_vector.push_back({ "Soylent Converter",TILE_SOYLENT_MACHINE_1, ITEM_SPRITES,{ 0,13,1,-2,1,1 },ITEM_TYPE_SOYLENT_MACHINE,1,1,1,0,0,0,0,0,34,34,0,INVENTORY_SOYLENT_MACHINE_1,8,0, Soylent_Machine_Specs,100,ITEM_JOB_PRODUCE_ITEM,RENDER_ITEMS, soylent_1 });
	tile_template_vector.push_back({ "Soylent Canister",TILE_SOYLENT_1, TILESHEET,{ 2,9,1,1,1,1 },ITEM_TYPE_FOOD,1,0,1,0,0,0,0,0,34,34,0,INVENTORY_SOYLENT_1,0,0, Soylent_Specs_1,100,0,RENDER_UNDER_PLAYER_ITEMS,no_produced_items,0 });
	tile_template_vector.push_back({ "Soylent Meal",TILE_SOYLENT_MEAL_1, TILESHEET,{ 2,10,1,1,1,1 },ITEM_TYPE_FOOD,1,0,1,0,0,0,0,0,34,34,0,INVENTORY_SOYLENT_MEAL_1,0,0, Soylent_Meal_Specs_1,100,0,RENDER_UNDER_PLAYER_ITEMS });
	tile_template_vector.push_back({ "Water Canister",TILE_WATER_CANISTER_1, TILESHEET,{ 2,18,1,1,1,1 },ITEM_TYPE_FOOD,1,0,1,0,0,0,0,0,34,34,0,INVENTORY_WATER_CANISTER_1,0,0, no_requirements,100,0,RENDER_UNDER_PLAYER_ITEMS,no_produced_items,0 });

	tile_template_vector.push_back({ "Soylent-Energizer",TILE_MICROWAVE_1, ITEM_SPRITES,{ 0,15,1,-2,1,1 },ITEM_TYPE_FOOD_PREPARATION,1,1,1,0,0,0,0,0,34,34,0,INVENTORY_MICROWAVE_1,8,0, Microwave_Specs,100,ITEM_JOB_PRODUCE_ITEM,RENDER_ITEMS, soylent_meal_1 });
	tile_template_vector.push_back({ "Standard Chair",TILE_CHAIR_1, TILESHEET,{ 2,11,1,1,1,1 },ITEM_TYPE_CHAIR,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_CHAIR_1,0,0, no_requirements,100,0,RENDER_UNDER_PLAYER_ITEMS });

	tile_template_vector.push_back({ "Standard Table",TILE_TABLE_1, TILESHEET,{ 5,10,1,1,1,1 },ITEM_TYPE_TABLE,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_TABLE_1,0,0, no_requirements,100,ITEM_JOB_TILE_STREAMLINE,RENDER_UNDER_PLAYER_ITEMS });

	tile_template_vector.push_back({ "Red Mining Laser",TILE_MINING_LASER_1, TILESHEET,{ 3,10,1,1,1,1 },ITEM_TYPE_MINING_LASER,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_MINING_LASER_1,0,0, cannot_build,100,0,RENDER_ITEMS });
	tile_template_vector.push_back({ "Standard Laser Pistol",TILE_LASER_PISTOL_1, TILESHEET,{ 3,11,1,1,1,1 },ITEM_TYPE_WEAPON,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_LASER_PISTOL_1,0,0, cannot_build,100,0,RENDER_ITEMS });

	tile_template_vector.push_back({ "Standard Floor Tile",TILE_CONSTRUCTION_TUBE_FLOOR_1, TILESHEET,{ 0,13,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_FLOOR,0,0,1,0,0,0,0,0,255,255,0,INVENTORY_CONSTRUCTION_TUBING_FLOOR_1,0,1, Wall_and_Floor_Specs,100 });
	tile_template_vector.push_back({ "Standard Wall Tile",TILE_CONSTRUCTION_TUBE_WALL_1, TILESHEET,{ 0,15,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_WALL,0,1,1,0,0,0,0,0,255,255,0,INVENTORY_CONSTRUCTION_TUBING_WALL_1,0,1, Wall_and_Floor_Specs,100 });
	tile_template_vector.push_back({ "Standard Door Tile",TILE_DOOR_1,ITEM_SPRITES,{ 0,19,1,1,1,1 },TILE_TYPE_CONSTRUCTION_TUBING_DOOR,0,1,0,0,0,0,2,0,34,34,0,INVENTORY_DOOR_TILE_1,6,1, Wall_and_Floor_Specs,100,ITEM_JOB_DOOR,RENDER_TILES });

	tile_template_vector.push_back({ "Ore Smelter",TILE_SMELTER_1,TILESHEET,{ 1,18,1,-2,1,1 },TILE_TYPE_SMELTER,1,1,0,0,0,0,0,0,34,34,0,INVENTORY_SMELTER_1,0,0, no_requirements,100,ITEM_JOB_PRODUCE_ITEM,RENDER_ITEMS,smelter_1,1,smelter_light_1 });

	tile_template_vector.push_back({ "Green Laser Turret",TILE_LASER_TURRET_GREEN,TILESHEET,{ 4,18,1,1,1,1 },TILE_TYPE_TURRET,1,1,1,0,0,0,0,0,34,34,1,INVENTORY_LASER_TURRET_GREEN,0,0, no_requirements,100,0,RENDER_ITEMS,no_produced_items,1,laser_turret_green_light_1 });

	tile_template_vector.push_back({ "Standard Light",TILE_INTERIOR_LIGHT_1,TILESHEET,{ 3,19,1,1,1,1 },TILE_TYPE_LIGHT,1,1,1,0,0,0,0,0,34,34,1,INVENTORY_NULL_ITEM,0,0, no_requirements,100,0,RENDER_ITEMS,no_produced_items,1,interior_light_soft_yellow });
}

void Load_Inventory_Item_Templates()
{
	inventory_item_template_map.insert({ INVENTORY_EMPTY_SLOT, { INVENTORY_EMPTY_SLOT, "Empty Slot", {7,0,SPRITESHEET_W,SPRITESHEET_H},0,INVENTORY_TYPE_EMPTY,default_config }});
	inventory_item_template_map.insert({ INVENTORY_NULL_ITEM, { INVENTORY_NULL_ITEM, "Null Item", {7,0,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_EMPTY,default_config } });
	inventory_item_template_map.insert({ INVENTORY_IRON_ORE, { INVENTORY_IRON_ORE, "Iron Ore", {2,4,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ORE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_COBALT_ORE, { INVENTORY_COBALT_ORE, "Cobalt Ore", {3,4,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ORE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_NICKEL_ORE, { INVENTORY_NICKEL_ORE, "Nickel Ore",{4,4,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ORE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_OXYGEN_MACHINE, { INVENTORY_OXYGEN_MACHINE, "Oxygen Machine",{3,0,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_DOOR_TILE_1, { INVENTORY_DOOR_TILE_1, "Auto-Door",{4,0,SPRITESHEET_W,SPRITESHEET_H }, 1, INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_FRENZEL_1, { INVENTORY_FRENZEL_1, "Frenzel Crop", {6,2,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_FRENZEL_2, { INVENTORY_FRENZEL_2, "Living Frenzel",{ 6,2,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_SOLAR_ARRAY_1, { INVENTORY_SOLAR_ARRAY_1, "Solar Array",{ 3,1,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_BED_1, { INVENTORY_BED_1, "Blue Bed",{ 4,1,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_STORAGE_1, { INVENTORY_STORAGE_1, "Storage Tile",{ 0,2,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_TREE_1, { INVENTORY_TREE_1, "Tree", { 1,2,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_CONSOLE_1, { INVENTORY_CONSOLE_1, "Console",{   3,2,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_LOCKER_1, { INVENTORY_LOCKER_1, "Locker",{ 4,5,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_PLANT_1, { INVENTORY_PLANT_1, "Plant", { 5,2,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_EMITTER_1, { INVENTORY_EMITTER_1, "Frenzel Emitter",{ 7,2,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_SOYLENT_MACHINE_1, { INVENTORY_SOYLENT_MACHINE_1, "Soylent Machine",{ 2,3,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_SOYLENT_MEAL_1, { INVENTORY_SOYLENT_MEAL_1, "Soylent Meal",{ 5,3,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_FOOD,default_config } });
	inventory_item_template_map.insert({ INVENTORY_SOYLENT_1, { INVENTORY_SOYLENT_1, "Soylent Farm",{ 1,3,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ITEM,default_config } });
	inventory_item_template_map.insert({ INVENTORY_FRENZEL_MEAT_1,{ INVENTORY_FRENZEL_MEAT_1, "Frenzel Meat",{ 3,5,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ITEM,default_config } });
	inventory_item_template_map.insert({ INVENTORY_SPACESUIT_1, { INVENTORY_SPACESUIT_1, "Spacesuit",{  0,4,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_SPACESUIT,default_config } });
	inventory_item_template_map.insert({ INVENTORY_OXYGEN_TANK, { INVENTORY_OXYGEN_TANK, "Oxygen Tank",{ 5,4,SPRITESHEET_W,SPRITESHEET_H },1, INVENTORY_TYPE_OXYGEN_TANK,default_config } });
	inventory_item_template_map.insert({ INVENTORY_MICROWAVE_1, { INVENTORY_MICROWAVE_1, "Soylent Microwave",{  4,3,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE ,default_config } });
	inventory_item_template_map.insert({ INVENTORY_PROCESSED_IRON, { INVENTORY_PROCESSED_IRON, "Processed Iron",{  0,0,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ORE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_PROCESSED_COBALT, { INVENTORY_PROCESSED_COBALT, "Processed Cobalt",{  1,0,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ORE ,default_config } });
	inventory_item_template_map.insert({ INVENTORY_CHAIR_1, { INVENTORY_CHAIR_1, "Chair",{  6,3,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_TABLE_1, { INVENTORY_TABLE_1, "Table",{  7,3,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_PROCESSED_NICKEL, { INVENTORY_PROCESSED_NICKEL, "Processed Nickel",{  2,0,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_ORE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_MINING_LASER_1, { INVENTORY_MINING_LASER_1, "Mining Laser",{  6,4,SPRITESHEET_W,SPRITESHEET_H },1,INVENTORY_TYPE_MINING_LASER,default_config } });
	inventory_item_template_map.insert({ INVENTORY_LASER_PISTOL_1, { INVENTORY_LASER_PISTOL_1, "Laser Pistol",{ 7,4,SPRITESHEET_W,SPRITESHEET_H },1, INVENTORY_TYPE_WEAPON,default_config }});
	inventory_item_template_map.insert({ INVENTORY_CONSTRUCTION_TUBING_FLOOR_1, { INVENTORY_CONSTRUCTION_TUBING_FLOOR_1, "Floor",{ 6,0,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_CONSTRUCTION_TUBING_WALL_1, { INVENTORY_CONSTRUCTION_TUBING_WALL_1, "Wall",{ 6,1,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_BUILDING_TILE,default_config } });
	inventory_item_template_map.insert({ INVENTORY_SMELTER_1,{ INVENTORY_SMELTER_1, "Smelter",{ 1,5,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_ITEM,default_config } });
	inventory_item_template_map.insert({ INVENTORY_WATER_CANISTER_1,{ INVENTORY_WATER_CANISTER_1, "Water Canister",{ 2,5,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_FOOD,default_config } });
	inventory_item_template_map.insert({ INVENTORY_LASER_TURRET_GREEN,{ INVENTORY_LASER_TURRET_GREEN, "Tesla Tower",{ 5,5,SPRITESHEET_W,SPRITESHEET_H },0,INVENTORY_TYPE_TURRET,default_config } });
}

// Return Inventory Functions 

Inventory_Item_Template Fetch_Inventory_Item_Template(int inventory_identifier)
{
	return inventory_item_template_map[inventory_identifier];
}

Tile_Template Return_Tile_Template_By_Identifier(int tile_identifier)
{
	for (int i = 0; i < tile_template_vector.size(); i++)
	{
		if (tile_template_vector[i].tile_name == tile_identifier) return tile_template_vector[i];
	}
	cout << "couldn't find tile by that identifier" << endl;
}

Tile_Template Return_Tile_By_Linked_Inventory_Item(int inventory_item_code)
{
	for (int i = 0; i < tile_template_vector.size(); i++)
	{
		if (tile_template_vector[i].inventory_pointer == inventory_item_code) return tile_template_vector[i];
	}
	cout << "couldn't find tile by that inventory_item: " << inventory_item_code << endl;
}


struct Tile_Init
{
	int tile_x_num = 0;
	int tile_y_num = 0;
	Tile_Template world_tile_type;
	bool item_on_tile = false;
	Tile_Template item_tile_type;
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