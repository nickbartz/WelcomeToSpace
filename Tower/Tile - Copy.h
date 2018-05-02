#pragma once

class Tile
{
public:
	//Initializes the variables
	Tile(SDL_Renderer* gRenderer = NULL, LTexture* tile_texture = NULL, int x_coordinate = NULL, int y_coordinate = NULL, Multi_Tile_Type multi_config = Tile_Vacuum);

	void free();

	//Shows the Tile on the screen
	bool is_onscreen(Camera* camera);
	void update_texture_clip(int clip_row_x, int clip_row_y);
	virtual void render(SDL_Renderer* gRenderer, Camera* camera);
	void Tile::render_status_bar(SDL_Renderer* gRenderer, Camera* camera);
	void Tile::change_door_orientation();
	void Tile::handle_door_animation();
	void Tile::handle_animation(int stage_of_animation);
	void Tile::Set_Color(Uint8 R, Uint8 G, Uint8 B);

		// The tile's position on the screen
	SDL_Rect* Tile::get_tile_rect(bool camera_rect = false);
	int getTileX();
	int getTileY();


	SDL_Rect tile_rect;
	SDL_Rect current_clip;
	SDL_Rect status_bar;

	// the tile_positions of the tile
	int x_tile_coord, y_tile_coord;

	Multi_Tile_Type multi_tile_config;

	// set initially not as an animated item
	int total_frames;
	int current_frame = 0;
	int animation_delay = 0;


private:

	SDL_Rect tile_rect_camera;

	//Set Texture Color Mods
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;

	//The tile's hardware texture and clip from sprite_sheet
	LTexture* mTexture;

};

Tile::Tile(SDL_Renderer* gRenderer, LTexture* tile_texture, int x_coordinate, int y_coordinate, Multi_Tile_Type multi_config)
{
	multi_tile_config = multi_config;
	tile_rect = { x_coordinate * TILE_WIDTH,y_coordinate * TILE_HEIGHT,TILE_WIDTH*multi_config.spritesheet_columns,TILE_HEIGHT*multi_config.spritesheet_rows };
	mTexture = tile_texture;
	current_clip = { (multi_tile_config.spritesheet_column*SPRITESHEET_W + 1),(multi_tile_config.spritesheet_row*SPRITESHEET_H + 1), (TILE_WIDTH*multi_tile_config.spritesheet_columns), (TILE_HEIGHT*multi_tile_config.spritesheet_rows) };
	total_frames = multi_tile_config.is_animated;
}

void Tile::update_texture_clip(int clip_column, int clip_row)
{
	current_clip.x = 1 + clip_column*SPRITESHEET_W;
	current_clip.y = 1 + clip_row*SPRITESHEET_H;
}

SDL_Rect* Tile::get_tile_rect(bool camera_rect)
{
	if (!camera_rect)
	{
		return &tile_rect;
	}
	else
	{
		return &tile_rect_camera;
	}
}

int Tile::getTileX()
{
	return (tile_rect.x / TILE_WIDTH);
}

int Tile::getTileY()
{
	return (tile_rect.y / TILE_HEIGHT);
}

void Tile::change_door_orientation()
{

}

void Tile::free()
{
}

bool Tile::is_onscreen(Camera* camera)
{
	bool onscreen = true;
	if (tile_rect.x < (camera->camera_box.x - TILE_WIDTH) )
	{
		onscreen = false;
	}
	if (tile_rect.x >(camera->camera_box.x + camera->camera_box.w + TILE_WIDTH))
	{
		onscreen = false;
	}
	if (tile_rect.y < (camera->camera_box.y - TILE_HEIGHT))
	{
		onscreen = false;
	}
	if (tile_rect.y > (camera->camera_box.y + camera->camera_box.h + TILE_HEIGHT))
	{
		onscreen = false;
	}
	return onscreen;
}

void Tile::render_status_bar(SDL_Renderer* gRenderer, Camera* camera)
{
	SDL_Rect* camera_rect = get_tile_rect(true);
	status_bar = { camera_rect->x, camera_rect->y,multi_tile_config.current_health,2 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &status_bar);
}

void Tile::render(SDL_Renderer* gRenderer, Camera* camera)
{
	handle_animation(0);
	
	tile_rect_camera.x = tile_rect.x - camera->camera_box.x;
	tile_rect_camera.y = tile_rect.y - camera->camera_box.y;
	tile_rect_camera.w = tile_rect.w;
	tile_rect_camera.h = tile_rect.h;

	//Render to screen

	mTexture->setColor(r, g, b);

	SDL_Rect render_clip = { current_clip.x, current_clip.y + 34*multi_tile_config.orientation , current_clip.w, current_clip.h };

	mTexture->render(gRenderer, &tile_rect_camera, &render_clip);

	handle_animation(1);
	handle_animation(2);
}

void Tile::Set_Color(Uint8 R, Uint8 G, Uint8 B)
{
	r = R;
	g = G;
	b = B;
}

void Tile::handle_animation(int stage_of_animation)
{
	if (stage_of_animation == 0)
	{
		if (multi_tile_config.door_state < 1)
		{
			if (current_frame == total_frames) { current_frame = 0; }
			if (total_frames != 0 && animation_delay == 11) current_clip.x = 34 * current_frame;
			current_frame++;
		}
		else
		{
			handle_door_animation();
		}
	}

	if (stage_of_animation == 1)
	{
		if (total_frames != 0) animation_delay++;
		if (total_frames != 0 && animation_delay == 12)
		{
			animation_delay = 0;
		}
	}
	
}

void Tile::handle_door_animation()
{
	if (multi_tile_config.door_state == 1 && current_frame < total_frames)
	{
		if (animation_delay == 11)
		{
			current_frame++;
			current_clip.x = 1 + 34 * current_frame;
		}
	}
	else if (multi_tile_config.door_state == 2 && current_frame > 0)
	{
		if (animation_delay == 11)
		{
			current_frame--;
			current_clip.x = 1 + 34 * current_frame;
		}
	}
	if (current_frame > 3)
	{
		multi_tile_config.is_collidable = 0;
	}
	else multi_tile_config.is_collidable = 1;
}


// Definitions for Tile Sub-Classes

class Multi_Tile : public Tile
{
public:
	Multi_Tile(SDL_Renderer* gRenderer, LTexture* textures[], int x_coordinate, int y_coordinate, Multi_Tile_Type multi_tile) :Tile(gRenderer, textures[multi_tile.spritesheet_num],x_coordinate, y_coordinate, multi_tile)
	{

	}

	SDL_Rect multi_tile_clip;
};

