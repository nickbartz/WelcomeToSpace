#ifndef CURSOR_H
#define CURSOR_H

#include <LTexture.h>
#include <Camera.h>

#include <iostream>
using namespace std;

class Cursor {
public:

	// Inititalize the cursor
	Cursor(SDL_Renderer* gRenderer, LTexture textures[]);

	// Render the cursor
	void Render(SDL_Renderer* gRenderer, Camera* camera);

	void free();

	void Set_Coords(int x, int y, Camera* camera);
	void Cursor::Set_Type(int current_action, Multi_Tile_Type* currently_selected_item);

private:
	LTexture* texture_array[NUM_TILESHEETS];

	SDL_Rect cursor_rect;
	SDL_Rect render_rect;
	SDL_Rect current_clip;

	LTexture* cTexture;

	int render_offset_x;
	int render_offset_y;

};

Cursor::Cursor(SDL_Renderer* gRenderer, LTexture textures[])
{
	for (int p = 0; p < NUM_TILESHEETS; ++p) { texture_array[p] = &textures[p]; }
	
	cursor_rect = { 0,0,TILE_WIDTH,TILE_HEIGHT };
	current_clip = { 3*SPRITESHEET_W,0,SPRITESHEET_W,SPRITESHEET_H };
	cTexture = texture_array[TILESHEET];
}

void Cursor::Set_Type(int current_action, Multi_Tile_Type* currently_selected_item)
{
	render_offset_y = 0;
	cursor_rect.w = TILE_WIDTH;
	cursor_rect.h = TILE_HEIGHT;
	current_clip.w = TILE_WIDTH;
	current_clip.h = TILE_HEIGHT;

	switch (current_action)
	{
	case BUTTON_ACTION_ACTION:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 3*SPRITESHEET_W;
		current_clip.y = 0*SPRITESHEET_H;
		current_clip.w = 0;
		current_clip.h = 0;
		break;
	case BUTTON_ACTION_REMOVE_TILE:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 3 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_ATTACK:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 9 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_MINING_LASER:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 9 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_DO_NOTHING:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 3 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_CREATE_ITEM:
		if (currently_selected_item->sprite_specs.sprite_rows == -2) render_offset_y = -1;
		cTexture = texture_array[currently_selected_item->spritesheet_num];
		cursor_rect.w = currently_selected_item->sprite_specs.rect_columns*TILE_WIDTH;
		cursor_rect.h = currently_selected_item->sprite_specs.rect_rows*TILE_HEIGHT;
		current_clip.x = currently_selected_item->sprite_specs.sprite_column*SPRITESHEET_W;
		current_clip.y = currently_selected_item->sprite_specs.sprite_row*SPRITESHEET_H;
		current_clip.w = abs(currently_selected_item->sprite_specs.sprite_columns*SPRITESHEET_W);
		current_clip.h = abs(currently_selected_item->sprite_specs.sprite_rows*SPRITESHEET_W);
		break;
	case BUTTON_ACTION_PLACE_ITEM:
		if (currently_selected_item->sprite_specs.sprite_rows == -2) render_offset_y = -1;
		cTexture = texture_array[currently_selected_item->spritesheet_num];
		cursor_rect.w = currently_selected_item->sprite_specs.rect_columns*TILE_WIDTH;
		cursor_rect.h = currently_selected_item->sprite_specs.rect_rows*TILE_HEIGHT;
		current_clip.x = currently_selected_item->sprite_specs.sprite_column*SPRITESHEET_W;
		current_clip.y = currently_selected_item->sprite_specs.sprite_row*SPRITESHEET_H;
		current_clip.w = abs(currently_selected_item->sprite_specs.sprite_columns*SPRITESHEET_W);
		current_clip.h = abs(currently_selected_item->sprite_specs.sprite_rows*SPRITESHEET_W);
		break;
	case BUTTON_ACTION_PICKUP_ITEM:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 3 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_PLACE_SCAFFOLD:
		if (currently_selected_item->sprite_specs.sprite_rows == -2) render_offset_y = -1;
		cTexture = texture_array[currently_selected_item->spritesheet_num];
		cursor_rect.w = currently_selected_item->sprite_specs.rect_columns*TILE_WIDTH;
		cursor_rect.h = currently_selected_item->sprite_specs.rect_rows*TILE_HEIGHT;
		current_clip.x = currently_selected_item->sprite_specs.sprite_column*SPRITESHEET_W;
		current_clip.y = currently_selected_item->sprite_specs.sprite_row*SPRITESHEET_H;
		current_clip.w = abs(currently_selected_item->sprite_specs.sprite_columns*SPRITESHEET_W);
		current_clip.h = abs(currently_selected_item->sprite_specs.sprite_rows*SPRITESHEET_W);
		break;
	case BUTTON_ACTION_INSPECT:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 3 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		current_clip.w = 0;
		current_clip.h = 0;
		break;
	}
}

void Cursor::Render(SDL_Renderer* gRenderer, Camera* camera)
{
	render_rect = { cursor_rect.x, cursor_rect.y + render_offset_y*TILE_HEIGHT, current_clip.w, current_clip.h };
	cTexture->render(gRenderer, &render_rect, &current_clip);
}

void Cursor::Set_Coords(int x, int y, Camera* camera)
{
	int limit_x = (x + camera->camera_box.x) / TILE_WIDTH;
	int limit_y = (y + camera->camera_box.y) / TILE_HEIGHT;

	cursor_rect.x = ((limit_x)* TILE_WIDTH - camera->camera_box.x);
	cursor_rect.y = ((limit_y)* TILE_WIDTH - camera->camera_box.y);
}

void Cursor::free()
{
}

#endif