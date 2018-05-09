//Using SDL, SDL_image, standard IO, and strings

#include <SDL.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <memory>
#include <iomanip>
#include <queue>
#include <string>
#include <ctime>
#include <unordered_map>
#include <iostream>
using namespace std;


#include <Config.h>
#include <Camera.h>
#include <LTexture.h>
#include <Shared_Draw_Functions.h>
#include <Dot.h>

#include <Cursor.h>
#include <World.h>
#include <A_Star.h>
#include <Intelligence.h>
#include <Timer.h>
#include <Console.h>
#include <Save_Load.h>



//Starts up SDL and creates window
bool init();
void load_save_from_disk(char* path, Save_File* save);
void save_data_to_disk(char* path, Save_File* save);
void load_textures();
void unload_textures();


//Frees media and shuts down SDL
void close();

// Functions for handling events
void handle_event(SDL_Event* e, Camera* camera, Cursor* cursor, Intelligence* intelligence, Console* console);
void process_current_input_state(Camera* camera, Cursor* cursor, Intelligence* intelligence, Console* console);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Rect* tilesheet_clips[BASIC_TILESHEET_WIDTH][BASIC_TILESHEET_HEIGHT];

LTexture texture_array[NUM_TILESHEETS];

int mouse_click_state[2][2];
bool mouse_motion = false;

int current_mouse_pos_x;
int current_mouse_pos_y;

//Globally used font and font scene texture
TTF_Font* gFont = NULL;

bool new_game;
bool debug = false;
bool pause = false;

void print(string print_string)
{
	cout << print_string << endl;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Tower Arcade", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void load_save_from_disk(char* path, Save_File* save)
{
	new_game = true;

	//Open file for reading in binary
	SDL_RWops* file = SDL_RWFromFile(path, "r+b");

	//File does not exist
	if (file == NULL)
	{
		printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

		//Create file for writing
		file = SDL_RWFromFile(path, "w+b");
		if (file != NULL)
		{
			printf("New file created!\n");

			SDL_RWwrite(file, save , sizeof(Save_File), 1);

			//Close file handler
			SDL_RWclose(file);
		}
		else
		{
			printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
		}
		new_game = true;
	}
	//File exists
	else
	{
		//Load data
		printf("Reading file...!\n");
		
		SDL_RWread(file, save, sizeof(Save_File), 1);
	
		//Close file handler
		SDL_RWclose(file);

		new_game = false;
	}
}

void save_data_to_disk(char* path, Save_File* save)
{
	//Open data for writing
	SDL_RWops* file = SDL_RWFromFile(path, "w+b");
	if (file != NULL)
	{
		//Save data
		SDL_RWwrite(file, save, sizeof(Save_File), 1);

		//Close file handler
		SDL_RWclose(file);
	}
	else
	{
		printf("Error: Unable to save file! %s\n", SDL_GetError());
	}
}

void load_textures()
{
	texture_array[BOLT_SPRITES].loadFromFile(gRenderer, "Sprites/Animated_Items/projectiles_spritesheet_1.png");
	texture_array[ITEM_SPRITES].loadFromFile(gRenderer, "Sprites/Animated_Items/animated_items_spritesheet_1.png");
	texture_array[TILESHEET].loadFromFile(gRenderer, "Sprites/Tilesheets/tilesheet_1.png");
	texture_array[CONSOLE_BACKGROUND].loadFromFile(gRenderer, "Sprites/Console/console_1.png");
	texture_array[DOT_SPRITESHEET].loadFromFile(gRenderer, "Sprites/Player/player_spritesheet.png");
	texture_array[MULTI_DOT_SPRITESHEET].loadFromFile(gRenderer, "Sprites/Player/multi_dot_spritesheet.png");
	texture_array[ASTEROID_SPRITESHEET].loadFromFile(gRenderer, "Sprites/Animated_Items/asteroid_spritesheet_1.png");
	texture_array[INVENTORY_SPRITESHEET].loadFromFile(gRenderer, "Sprites/Inventory_Items/Inventory_Spritesheet_1.png");
	texture_array[ENEMY_SHIP_SPRITESHEET].loadFromFile(gRenderer, "Sprites/Enemies/Enemy_Ships_1.png");
	texture_array[CONTAINER_SPRITESHEET].loadFromFile(gRenderer, "Sprites/Inventory_Items/Container_Spritesheet.png");


	int row = 0;
	int column = 0;

	for (int p = 0; p < BASIC_TILESHEET_HEIGHT; ++p)
	{
		for (int i = 0; i < BASIC_TILESHEET_WIDTH; i++)
		{
			tilesheet_clips[i][p] = new SDL_Rect();
			tilesheet_clips[i][p]->x = 1 + 34 * i;
			tilesheet_clips[i][p]->y = 1 + 34 * p;
			tilesheet_clips[i][p]->w = 32;
			tilesheet_clips[i][p]->h = 32;
		}
	}

	//Open the font
	gFont = TTF_OpenFont("lazy.ttf", 12);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

}

void unload_textures()
{
	for (int p = 0; p < NUM_TILESHEETS; ++p)
	{
		texture_array[p].free();
	}
}

void close()
{
	// free loaded textures
	unload_textures();
	
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void handle_event(SDL_Event* e, Camera* camera, Cursor* cursor, Intelligence* intelligence, Console* console)
{
	if (e->type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&current_mouse_pos_x, &current_mouse_pos_y);
		mouse_motion = true;
	}
	else mouse_motion = false;

	// HANDLE MOUSE CLICKS AND HOLDS
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT) mouse_click_state[0][0] = 1, mouse_click_state[0][1] = 0;
		else if (e->button.button == SDL_BUTTON_RIGHT) mouse_click_state[1][0] = 1, mouse_click_state[1][1] = 0;
	}
	else if (e->type == SDL_MOUSEBUTTONUP)
	{
		if (e->button.button == SDL_BUTTON_LEFT) mouse_click_state[0][0] = 0, mouse_click_state[0][1] = 1;
		else if (e->button.button == SDL_BUTTON_RIGHT) mouse_click_state[1][0] = 0, mouse_click_state[1][1] = 1;
	}

	// HANDLE KEYBOARD INPUT

	if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP)
	{
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_p)
		{
			if (pause) pause = false;
			else pause = true;
		}
		intelligence->Handle_Keyboard_Input(e);
	}
}

void process_current_input_state(Camera* camera, Cursor* cursor, Intelligence* intelligence, Console* console)
{
	cursor->Set_Coords(current_mouse_pos_x, current_mouse_pos_y, camera);
	cursor->Set_Type(console->current_action, &Return_Tile_By_Inventory_Item(console->current_selected_inventory_item));

	int x_pos = (current_mouse_pos_x + camera->camera_box.x);
	int y_pos = (current_mouse_pos_y + camera->camera_box.y);
	int x_tile = (x_pos / TILE_WIDTH);
	int y_tile = (y_pos / TILE_HEIGHT);

	intelligence->Test_Cursor_Position(x_pos, y_pos, x_tile, y_tile);
	

	//SITUATION WHERE YOU CLICK ONCE AND DON'T HOLD
	if (mouse_click_state[0][0] == 1)
	{
		
		if (mouse_click_state[0][1] == 0)
		{
			mouse_click_state[0][1] = 1;
			if (console->check_console_for_clicks(current_mouse_pos_x, current_mouse_pos_y) == false)
			{
				intelligence->Handle_Non_Console_Click(console->current_action, x_tile, y_tile, x_pos, y_pos, console->current_selected_inventory_item);
			}
			else
			{
				console->Handle_Console_Clicks();
			}
		}
		else 
		{
			if (console->check_console_for_clicks(current_mouse_pos_x, current_mouse_pos_y) == false)
			{
				intelligence->Handle_Non_Console_Click_And_Hold(console->current_action, x_tile, y_tile, x_pos, y_pos, console->current_selected_inventory_item);
			}
			else
			{
				// ADD CODE FOR CLICK AND HOLD ON CONSOLE HERE
			}
		}
	}

	// SITUATION WHERE YOU UNCLICK
	if (mouse_click_state[0][0] == 0 && mouse_click_state[0][1] == 1)
	{
		intelligence->Handle_Non_Console_Unclick(console->current_action, x_tile, y_tile, x_pos, y_pos, console->current_selected_inventory_item);
	}

	// SITUATION WHERE YOU RIGHT CLICK 
	if (mouse_click_state[1][0] == 1)
	{
		// IF YOU CLICK AND DO NOT HOLD
		if (mouse_click_state[1][1] == 0)
		{
			mouse_click_state[1][1] = 1;
			Dot* dot_focus = intelligence->Return_Clicked_Dot(x_pos, y_pos);
			if (dot_focus != NULL) console->Change_Current_Focus_Dot(gRenderer, dot_focus);	
		}
		else
		{
			// FUNCTION FOR IF YOU RIGHT CLICK AND HOLD 
		}
	}

	if (mouse_click_state[0][0] == 0 && mouse_click_state[0][1] == 1) mouse_click_state[0][1] = 0;
	if (mouse_click_state[1][0] == 0 && mouse_click_state[1][1] == 1) mouse_click_state[1][1] = 0;

}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (debug) cout << "Loading Textures" << endl;
		
		load_textures();
		Load_Tiles();
		Load_Inventory_Items();

		//if (debug) cout << "Creating Save" << endl;
		//Save_File* current_save_state = new Save_File();

		//if (debug) cout << "Loading Save from Disk" << endl;
		////load_save_from_disk("Save/nums.bin", current_save_state);

		//Create the world
		if (debug) cout << "Loading Camera" << endl;
		Camera camera;

		if (debug) cout << "Loading World" << endl;
		World world(gRenderer, texture_array, tilesheet_clips, new_game);

		if (debug) cout << "Loading Intelligence" << endl;
		Intelligence intelligence(&world, gRenderer, &camera, texture_array, new_game);

		if (debug) cout << "Loading Cursor" << endl;
		Cursor cursor(gRenderer,&texture_array[TILESHEET]);

		//cout << "save stating" << endl;
		//current_save_state->Load_Current_State(&world, &intelligence);

		// Create the Console
		if (debug) cout << "Loading Console" << endl;

		Console console(gRenderer, gFont, &intelligence, texture_array);

		if (debug) cout << "Loading Timer" << endl;

		// Create the Timer
		LTimer fpsTimer;

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//Start counting frames per second
		int countedFrames = 0;
		fpsTimer.start();

		if (debug) cout << "starting main loop" << endl;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			if (debug) cout << "polling for events" << endl;
			
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				if (e.type == SDL_KEYDOWN)
				{
					//Select surfaces based on key press
					switch (e.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						quit = true;
						break;
					}
				}
				handle_event(&e, &camera, &cursor, &intelligence, &console);
			}

			if (debug) cout << "processing current input state" << endl;
			//if (debug) cout << "processing current input state" << endl;
			process_current_input_state(&camera, &cursor, &intelligence, &console);

			//Calculate and correct fps
			if (debug) cout << "calculating fps" << endl;
			int avgFPS = countedFrames / (fpsTimer.getTicks() / 10000.f);
			if (avgFPS > 2000000) avgFPS = 0;
			if (debug) cout << "updating camera" << endl;
			
			// Update Camera
			camera.updatecamera(intelligence.player_dot->getCamera_x(), intelligence.player_dot->getCamera_y());

			//Clear screen
			if (debug) cout << "clearing screen" << endl;
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render Objects
			if (debug) cout << "rendering objects" << endl;
			intelligence.render();
			if (console.current_action == BUTTON_ACTION_PLACE_ITEM || BUTTON_ACTION_REMOVE_TILE || BUTTON_ACTION_CREATE_ITEM) cursor.Render(gRenderer, &camera);
			console.render(gRenderer);

			if (debug) cout << "updating screen" << endl;
			//Update screen
			SDL_RenderPresent(gRenderer);
			++countedFrames;
			if (debug) cout << "advancing time" << endl;

			if (!pause)
			{
				intelligence.Advance_Time(avgFPS);
				if (intelligence.player_dot->npc_dot_config.dot_stat_health <= 0)
				{
					pause = true;
					console.Pull_Up_Restart_Screen();
				}
			}

			console.Update_Console(gRenderer);
		}

		//if (debug) cout << "Saving World to Save_State" << endl;
		//current_save_state->Save_Current_State(&world, &intelligence);

		//if (debug) cout << "Saving Save State to Disk" << endl;
		//save_data_to_disk("Save/nums.bin", current_save_state);

		if (debug) cout << "Freeing Assets" << endl;
		//delete current_save_state;
		world.Free();
		intelligence.free();
		cursor.free();
		console.free();
		fpsTimer.free();
	}

	//Free resources and close SDL
	if (debug) cout << "Closing App" << endl;
	close();

	return 0;
}