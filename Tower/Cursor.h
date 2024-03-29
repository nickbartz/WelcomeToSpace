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
	void Cursor::Set_Type(int current_action, Tile_Template* currently_selected_item);

	int current_action_type;
	bool over_console = false;

private:
	LTexture* texture_array[NUM_TILESHEETS];

	SDL_Rect cursor_rect;
	SDL_Rect render_rect;
	SDL_Rect current_clip;
	SDL_Rect basic_clip;

	LTexture* cTexture;
	LTexture* basic_mouse;

	int render_offset_x;
	int render_offset_y;

};

Cursor::Cursor(SDL_Renderer* gRenderer, LTexture textures[])
{
	for (int p = 0; p < NUM_TILESHEETS; ++p) { texture_array[p] = &textures[p]; }
	
	cursor_rect = { 0,0,TILE_WIDTH,TILE_HEIGHT };
	basic_clip = { 6 * SPRITESHEET_W,5 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H };
	current_clip = { 6*SPRITESHEET_W,5*SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H };
	cTexture = texture_array[INVENTORY_SPRITESHEET];
	basic_mouse = texture_array[INVENTORY_SPRITESHEET];
}

void Cursor::Set_Type(int current_action, Tile_Template* currently_selected_item)
{
	render_offset_y = 0;
	cursor_rect.w = TILE_WIDTH;
	cursor_rect.h = TILE_HEIGHT;
	current_clip.w = TILE_WIDTH;
	current_clip.h = TILE_HEIGHT;
	cTexture = texture_array[INVENTORY_SPRITESHEET];
	current_clip.x = 6 * SPRITESHEET_W;
	current_clip.y = 5 * SPRITESHEET_H;
	current_action_type = current_action;

	switch (current_action)
	{
	case BUTTON_ACTION_REMOVE_TILE:
		cTexture = texture_array[TILESHEET];
		current_clip.x = 3 * SPRITESHEET_W;
		current_clip.y = 0 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_DO_NOTHING:
		cTexture = texture_array[INVENTORY_SPRITESHEET];
		current_clip.x = 6 * SPRITESHEET_W;
		current_clip.y = 5 * SPRITESHEET_H;
		break;
	case BUTTON_ACTION_PLACE_SCAFFOLD:
		if (currently_selected_item->sprite_specs.sprite_rows == -2) render_offset_y = -1;
		if (currently_selected_item->is_smooth == 0)
		{
			cTexture = texture_array[currently_selected_item->spritesheet_num];
			cursor_rect.w = currently_selected_item->sprite_specs.rect_columns*TILE_WIDTH;
			cursor_rect.h = currently_selected_item->sprite_specs.rect_rows*TILE_HEIGHT;
			current_clip.x = currently_selected_item->sprite_specs.sprite_column*SPRITESHEET_W;
			current_clip.y = currently_selected_item->sprite_specs.sprite_row*SPRITESHEET_H;
			current_clip.w = abs(currently_selected_item->sprite_specs.sprite_columns*SPRITESHEET_W);
			current_clip.h = abs(currently_selected_item->sprite_specs.sprite_rows*SPRITESHEET_W);
		}
		else
		{
			cTexture = texture_array[INVENTORY_SPRITESHEET];
			cursor_rect.w = TILE_WIDTH;
			cursor_rect.h = TILE_HEIGHT;
			Inventory_Item_Template new_item = inventory_item_template_map[currently_selected_item->inventory_pointer];
			current_clip.x = new_item.sprite_config.x*SPRITESHEET_W;
			current_clip.y = new_item.sprite_config.y*SPRITESHEET_H;
			current_clip.w = SPRITESHEET_W;
			current_clip.h = SPRITESHEET_H;
		}
		break;
	case BUTTON_ACTION_INVENTORY_BUTTON:
		if (inventory_item_template_map[currently_selected_item->inventory_pointer].item_code != INVENTORY_EMPTY_SLOT)
		{
			cTexture = texture_array[INVENTORY_SPRITESHEET];
			cursor_rect.w = TILE_WIDTH;
			cursor_rect.h = TILE_HEIGHT;
			Inventory_Item_Template new_item = inventory_item_template_map[currently_selected_item->inventory_pointer];
			current_clip.x = new_item.sprite_config.x*SPRITESHEET_W;
			current_clip.y = new_item.sprite_config.y*SPRITESHEET_H;
			current_clip.w = SPRITESHEET_W;
			current_clip.h = SPRITESHEET_H;
		}
		break;
	}
}

void Cursor::Render(SDL_Renderer* gRenderer, Camera* camera)
{
	render_rect = { cursor_rect.x, cursor_rect.y + render_offset_y*TILE_HEIGHT, current_clip.w, current_clip.h };

	if (over_console == true)
	{
		basic_mouse->render(gRenderer, &render_rect, &basic_clip);
	}
	else
	{
		cTexture->render(gRenderer, &render_rect, &current_clip);
	}

}

void Cursor::Set_Coords(int x, int y, Camera* camera)
{
	if (over_console == false && (current_action_type == BUTTON_ACTION_PLACE_SCAFFOLD || current_action_type == BUTTON_ACTION_REMOVE_TILE))
	{
		int limit_x = (x + camera->camera_box.x) / TILE_WIDTH;
		int limit_y = (y + camera->camera_box.y) / TILE_HEIGHT;

		cursor_rect.x = ((limit_x)* TILE_WIDTH - camera->camera_box.x);
		cursor_rect.y = ((limit_y)* TILE_WIDTH - camera->camera_box.y);
	}
	else
	{
		cursor_rect.x = x;
		cursor_rect.y = y;
	}
}

void Cursor::free()
{
}

#endif