#pragma once
// ITEM DOTS

class Item
{
public:
	Item(Inventory_Item_Template item_template, SDL_Renderer* gRenderer, LTexture* inventory_spritesheet, int x_pos, int y_pos, bool custom = false)
	{
		base_template = item_template;
		item_code = item_template.item_code;
		item_name = item_template.item_name;
		tile_or_item = item_template.tile_or_item;
		item_type = item_template.item_type;
		weapon_config = item_template.weapon_config;
		sprite_clip = { item_template.sprite_config.x*SPRITESHEET_W, item_template.sprite_config.y*SPRITESHEET_H, item_template.sprite_config.w, item_template.sprite_config.h };
		render_rect = { x_pos, y_pos, sprite_clip.w, sprite_clip.h };
		spritesheet = inventory_spritesheet;

		is_custom = custom;
	}

	int item_code;
	string item_name;
	int tile_or_item;
	int item_type;
	Inventory_Item_Weapon_Config weapon_config;
	SDL_Rect render_rect;
	SDL_Rect sprite_clip;
	Inventory_Item_Template base_template;
	bool is_custom;

	bool is_onscreen(Camera* camera, int buffer = TILE_WIDTH);
	void render(SDL_Renderer* gRenderer, Camera* camera, double angle, SDL_Point* center, SDL_RendererFlip flip);

private:
	LTexture* spritesheet;

};

bool Item::is_onscreen(Camera* camera, int buffer)
{
	bool onscreen = true;
	if (render_rect.x < (camera->camera_box.x - TILE_WIDTH - buffer))
	{
		onscreen = false;
	}
	if (render_rect.x >(camera->camera_box.x + camera->camera_box.w + TILE_WIDTH + buffer))
	{
		onscreen = false;
	}
	if (render_rect.y < (camera->camera_box.y - TILE_HEIGHT - buffer))
	{
		onscreen = false;
	}
	if (render_rect.y >(camera->camera_box.y + camera->camera_box.h + TILE_HEIGHT + buffer))
	{
		onscreen = false;
	}
	return onscreen;
}

void Item::render(SDL_Renderer* gRenderer, Camera* camera, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if (is_onscreen(camera))
	{
		SDL_Rect renderQuad = { render_rect.x - camera->camera_box.x, render_rect.y - camera->camera_box.y, TILE_WIDTH, TILE_HEIGHT };
		spritesheet->render(gRenderer, &renderQuad, &sprite_clip);

	}
}

