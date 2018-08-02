#ifndef CONSOLE_H
#define CONSOLE_H


bool check_if_point_in_rect(SDL_Rect target_rect, int x_point, int y_point)
{
	bool in_rect = true;

	if (x_point < target_rect.x || x_point >(target_rect.x + target_rect.w))
	{
		in_rect = false;
	}
	if (y_point < target_rect.y || y_point >(target_rect.y + target_rect.h))
	{
		in_rect = false;
	}
	return in_rect;
}

/// Diagnostic Class

class Console_Diagnostic {
public:
	Console_Diagnostic::Console_Diagnostic(int x_offset = 0, int y_offset = 0, TTF_Font* gFont = NULL, int* diagnostic_value = NULL, bool do_not_render_if_zero = false, bool shaded_background = false);
	void free();
	void render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect);

private:
	int* linked_value;
	bool dont_render_if_zero;
	bool background_shaded;

	int current_delay;
	int max_delay;

	SDL_Rect offset_rect;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Color background_color = { 0,0,255,50 };
	SDL_Color border_highlight = { 200,200,255,255 };
	TTF_Font* diagnostic_font;

	LTexture diagnostic_value_texture;

};

Console_Diagnostic::Console_Diagnostic(int x_offset, int y_offset, TTF_Font* gFont, int* diagnostic_value, bool do_not_render_if_zero, bool shaded_background)
{
	diagnostic_font = gFont;
	linked_value = diagnostic_value;
	dont_render_if_zero = do_not_render_if_zero;
	background_shaded = shaded_background;

	current_delay = 0;
	max_delay = 30;

	offset_rect = { x_offset, y_offset, 0, 0 };
}

void Console_Diagnostic::render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect)
{
	if (linked_value != NULL && *linked_value != 0 || dont_render_if_zero == false)
	{
		if (current_delay == 0)
		{
			diagnostic_value_texture.loadFromRenderedText(std::to_string(*linked_value), textColor, diagnostic_font, gRenderer);
		}

		SDL_Rect diagnostic_value_rect = { pos_rect->x + offset_rect.x, pos_rect->y + offset_rect.y, diagnostic_value_texture.getWidth(), diagnostic_value_texture.getHeight() };
		SDL_Rect diagnostic_value_clip = { 0,0, diagnostic_value_rect.w, diagnostic_value_rect.h };
		
		if (background_shaded)
		{
			SDL_SetRenderDrawColor(gRenderer, background_color.r, background_color.g, background_color.b, background_color.a);
			SDL_RenderFillRect(gRenderer, &diagnostic_value_rect);
			SDL_SetRenderDrawColor(gRenderer, border_highlight.r, border_highlight.g, border_highlight.b, border_highlight.a);
			SDL_RenderDrawRect(gRenderer, &diagnostic_value_rect);
		}

		diagnostic_value_texture.render(gRenderer, &diagnostic_value_rect, &diagnostic_value_clip);

		current_delay++;
		if (current_delay >= max_delay) current_delay = 0;
	}
}

void Console_Diagnostic::free()
{
	diagnostic_value_texture.free();
	linked_value = NULL;
}

class Console_Stat_Bar
{
public:
	Console_Stat_Bar::Console_Stat_Bar(SDL_Renderer* gRenderer = NULL, int x_offset = 0, int y_offset = 0, TTF_Font* gFont = NULL, int* diagnostic_value = NULL, int* diagnostic_value_max = NULL);
	void free();
	void render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect);

private:
	int* linked_value;
	int* linked_value_max;
	SDL_Color bar_color;

	SDL_Rect offset_rect;
};

Console_Stat_Bar::Console_Stat_Bar(SDL_Renderer* gRenderer, int x_offset, int y_offset, TTF_Font* gFont, int* diagnostic_value, int* diagnostic_value_max)
{
	linked_value = diagnostic_value;
	linked_value_max = diagnostic_value_max;
	offset_rect = { x_offset, y_offset, 0, 0 };
	bar_color = { 255,0,0,200 };
}

void Console_Stat_Bar::free()
{
	linked_value = NULL;
	linked_value_max = NULL;
}

void Console_Stat_Bar::render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect)
{
	int max_value = 100;
	if (linked_value_max != NULL) max_value = *linked_value_max;
	
	SDL_Rect bar_rect = { pos_rect->x + offset_rect.x, pos_rect->y + offset_rect.y, (*linked_value)*(pos_rect->w-offset_rect.x -3)/(*linked_value_max),15 };
	
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, bar_color.r, bar_color.g, bar_color.b, bar_color.a);
	SDL_RenderFillRect(gRenderer, &bar_rect);
}

class Console_Label
{
public:
	Console_Label::Console_Label(SDL_Color text_color = { 255,255,255,255 }, bool string_is_pointer = false, string* pointer_to_string = NULL, string actual_string = "Test", int offset_x = 0, int offset_y = 0);
	void render(SDL_Rect* pos_rect);
	void free();
	void Update_Texture(string new_string);
	int get_width();

private: 
	SDL_Color Console_Label_Color;
	SDL_Texture* Console_Label_Texture;
	TTF_Font* Console_Label_Font;
	bool pointer;
	string* string_pointer;
	string diagnostic_label_string;
	SDL_Rect offset_rect;
	SDL_Rect text_box_size;
};

Console_Label::Console_Label(SDL_Color text_color, bool string_is_pointer, string* pointer_to_string, string actual_string, int offset_x, int offset_y)
{
	Console_Label_Color = text_color;
	Console_Label_Font = gFont;
	pointer = string_is_pointer;
	string_pointer = pointer_to_string;
	diagnostic_label_string = actual_string;
	offset_rect = { offset_x, offset_y, 0,0 };

	if (pointer == true && string_pointer != NULL) Update_Texture(*string_pointer);
	else Update_Texture(diagnostic_label_string);
}

void Console_Label::Update_Texture(string new_string)
{
	if (new_string != "" && new_string != "Test")
	{
		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, new_string.c_str(), Console_Label_Color);
		if (textSurface != NULL)
		{
			//Create texture from surface pixels

			Console_Label_Texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
			if (Console_Label_Texture == NULL)
			{
				cout << "Alternate function trying to create text: " << new_string << endl;
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get image dimensions
				text_box_size.w = textSurface->w;
				text_box_size.h = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}
		else
		{
			printf("Unable to render text  surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}
}

void Console_Label::render(SDL_Rect* pos_rect)
{	
	if (Console_Label_Texture != NULL)
	{
		SDL_Rect text_clip = { 0,0,text_box_size.w, text_box_size.h };
		SDL_Rect text_rect = { pos_rect->x + offset_rect.x,pos_rect->y + offset_rect.y, text_box_size.w,  text_box_size.h };
		SDL_RenderCopyEx(gRenderer, Console_Label_Texture, &text_clip, &text_rect, 0, NULL, SDL_FLIP_NONE);
	}
}

int Console_Label::get_width()
{
	return text_box_size.w;
}

void Console_Label::free()
{
	SDL_DestroyTexture(Console_Label_Texture);
	Console_Label_Texture = NULL;
	string_pointer = NULL;
	Console_Label_Font = NULL;
}

class Console_Sprite {
public:
	Console_Sprite::Console_Sprite(LTexture* spritesheet = NULL, SDL_Rect spritesheet_clip = { 0,0,0,0 }, int offset_x = 0, int offset_y = 0);
	void render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect);
	void free();

	SDL_Rect console_sprite_clip;
	SDL_Rect offset_rect;

private:
	LTexture* console_spritesheet;
};

Console_Sprite::Console_Sprite(LTexture* spritesheet, SDL_Rect spritesheet_clip, int offset_x, int offset_y)
{
	console_spritesheet = spritesheet;
	console_sprite_clip = spritesheet_clip;
	offset_rect = { offset_x, offset_y, 0, 0 };
};

void Console_Sprite::render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect)
{
	console_spritesheet->render(gRenderer, pos_rect, &console_sprite_clip);
}

void Console_Sprite::free()
{
	console_spritesheet = NULL;
}

// BUTTON CLASS

class Button {
public:
	Button::Button(int action = BUTTON_ACTION_DO_NOTHING, SDL_Rect button_rect = { 0,0,0,0 }, bool button_background = false, int panel_name = PANEL_NO_PANEL, int button_config = 0, int window_num = 0);
	
	void free();
	void render();
	void toggle_button_clicked();
	void Add_Button_Sprite(LTexture* spritesheet, SDL_Rect spritesheet_clip,  int offset_x, int offset_y);
	void Add_Button_Label(string button_label_text, TTF_Font* gFont, bool is_pointer_to_string, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y);
	void Add_Button_Diagnostic(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, bool dont_render_if_zero = false, bool shaded_background = false);
	void Add_Button_Stat_Bar(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, int* diagnostic_value_max = NULL);
	void Add_Button_String_Diagnostic(TTF_Font* gFont, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y);
	void Change_Slot_Tint(SDL_Color new_tint_color);
	void Change_Slot_Highlight(SDL_Color new_highlight_color);

	int button_action;
	int button_panel_type;
	int button_config_num;
	int button_window_num;

	SDL_Rect button_rect;
	SDL_Rect button_clip;
	SDL_Color slot_tint;
	SDL_Color slot_highlight;
	SDL_Color original_slot_tint;
	SDL_Color original_slot_highlight;

	Console_Label button_label;
	Console_Sprite button_sprite;
	Console_Diagnostic button_diagnostic;
	Console_Label button_string_diagnostic;
	Console_Stat_Bar button_stat_bar;

	Dot_Inventory_Slot* slot_item_pointer = NULL;

	bool button_has_label;
	bool button_has_sprite;
	bool button_has_diagnostic;
	bool button_has_string_diagnostic;
	bool button_has_stat_bar;

	bool button_filled;
	bool button_is_pressed = false;

private:
};

Button::Button(int action, SDL_Rect pos_rect, bool button_background, int panel_name, int button_config, int window_num)
{
	button_action = action;
	button_rect = pos_rect;
	button_clip = { 0,0,button_rect.w,button_rect.h };

	button_panel_type = panel_name;
	button_config_num = button_config;
	button_window_num = button_window_num;

	button_has_label = false;
	button_has_sprite = false;
	button_has_diagnostic = false;
	button_has_string_diagnostic = false;
	button_has_stat_bar = false;

	slot_highlight = { 200,200,255,255 };
	slot_tint = { 0,0,255,50 };
	original_slot_highlight = { 200,200,255,255 };
	original_slot_tint = { 0,0,255,50 };

	button_filled = button_background;
}

void Button::render()
{	
	toggle_button_clicked();

	if (slot_item_pointer != NULL)
	{
		button_sprite.console_sprite_clip.x = Fetch_Inventory_Item_Template(slot_item_pointer->inventory_item_code).sprite_config.x * SPRITESHEET_W;
		button_sprite.console_sprite_clip.y = Fetch_Inventory_Item_Template(slot_item_pointer->inventory_item_code).sprite_config.y * SPRITESHEET_H;
	}

	if (button_filled)
	{
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(gRenderer, slot_tint.r, slot_tint.g, slot_tint.b, slot_tint.a);
		SDL_RenderFillRect(gRenderer, &button_rect);
		SDL_SetRenderDrawColor(gRenderer, slot_highlight.r, slot_highlight.g, slot_highlight.b, slot_highlight.a);
		SDL_RenderDrawRect(gRenderer, &button_rect);
	}
	
	if (button_has_label) button_label.render(&button_rect);
	if (button_has_sprite) button_sprite.render(gRenderer, &button_rect);
	if (button_has_diagnostic) button_diagnostic.render(gRenderer, &button_rect);
	if (button_has_string_diagnostic) button_string_diagnostic.render(&button_rect);
	if (button_has_stat_bar) button_stat_bar.render(gRenderer, &button_rect);
}

void Button::toggle_button_clicked()
{
	if (button_is_pressed == true)
	{
		SDL_Color new_tint = { slot_tint.r - 20, slot_tint.g - 20, slot_tint.b - 20, slot_tint.a };
		SDL_Color new_highlight = { slot_highlight.r - 20, slot_highlight.g - 20, slot_highlight.b - 20, slot_highlight.a };
		Change_Slot_Tint(new_tint);
		Change_Slot_Highlight(new_highlight);
	}
	else
	{
		slot_highlight = original_slot_highlight;
		slot_tint = original_slot_tint;
	}
}

void Button::Add_Button_Diagnostic(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, bool dont_render_if_zero, bool shaded_background)
{
	button_diagnostic = Console_Diagnostic(offset_x, offset_y, gFont, diagnostic_value, dont_render_if_zero, shaded_background);
	button_has_diagnostic = true;
}

void Button::Add_Button_Stat_Bar(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, int* diagnostic_value_max)
{
	button_stat_bar = Console_Stat_Bar(gRenderer, offset_x, offset_y, gFont, diagnostic_value, diagnostic_value_max);
	button_has_stat_bar = true;
}

void Button::Add_Button_Label(string button_label_text, TTF_Font* gFont, bool is_pointer_to_string, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y )
{
	if (DEBUG_CONSOLE) cout << "creating console label" << endl;
	button_label = Console_Label(button_label_color, is_pointer_to_string, pointer, button_label_text, offset_x, offset_y);
	button_has_label = true;
	if (DEBUG_CONSOLE) cout << "finished creating console label" << endl;
}

void Button::Add_Button_String_Diagnostic(TTF_Font* gFont, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y)
{
	button_string_diagnostic = Console_Label(button_label_color, true, pointer, "", offset_x, offset_y);
	button_has_string_diagnostic = true;
}

void Button::Add_Button_Sprite(LTexture* spritesheet, SDL_Rect spritesheet_clip, int offset_x, int offset_y)
{
	button_sprite = Console_Sprite(spritesheet, spritesheet_clip);
	button_has_sprite = true;
}

void Button::Change_Slot_Tint(SDL_Color new_slot_tint)
{
	slot_tint = new_slot_tint;
}

void Button::Change_Slot_Highlight(SDL_Color new_slot_highlight)
{
	slot_highlight = new_slot_highlight;
}

void Button::free()
{
	if (button_has_label) button_label.free();
	if (button_has_sprite) button_sprite.free();
	if (button_has_diagnostic) button_diagnostic.free();
	if (button_has_string_diagnostic) button_string_diagnostic.free();
	if (button_has_stat_bar) button_stat_bar.free();
}

// CONSOLE PANELS CLASS, THESE FIT INSIDE WINDOWS 

class Console_Panel {
public:
	Console_Panel::Console_Panel(string panel_name = "Test", int panel_number = PANEL_NO_PANEL, int window_number = 0, SDL_Rect* base_window_rect = NULL);
	vector<Button> console_panel_buttons;

	string name;
	int panel_num;
	int window_num;
	SDL_Rect panel_rect;
	SDL_Rect header_offset; 
	bool selected;

	void render();
	void free();
	Button* Check_For_Click(int mouse_x_pos, int mouse_y_pos);

	// Button Creation Functions
	void Add_Dot_Inventory_Slot_To_Panel(SDL_Rect offset_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name);
	void Add_Dot_Crafting_Slot_To_Panel(SDL_Rect offset_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name);
	void Add_Label_To_Panel(string Label, SDL_Rect offset_rect, int panel_name, int button_action, bool filled);
	void Add_String_Diagnostic_To_Panel(string label, string* string_pointer, SDL_Rect offset_rect, int panel_name);
	void Add_Number_Diagnostic_To_Panel(string label, int* value_pointer, SDL_Rect offset_rect, int panel_name, bool stat_bar, int* value_pointer_max);
	void Add_Simple_Linked_Number_To_Panel(int* value_pointer, SDL_Rect offset_rect, int panel_name);
	void Add_Production_Slot_To_Panel(SDL_Rect offset_rect, Dot* focus_dot, int production_array_num, LTexture* spritesheet, int panel_name);
	void Add_Simple_Button_With_Action(int action, bool is_icon = false, string button_text = "", SDL_Rect spritesheet_clip = { 0,0,0,0 }, LTexture* spritesheet = NULL, SDL_Rect offset_rect = { 0,0,0,0 }, int panel_name = 0);
};

Console_Panel::Console_Panel(string panel_name,int panel_number, int window_number, SDL_Rect* base_window_rect)
{
	name = panel_name;
	panel_num = panel_number;
	window_num = window_number;
	panel_rect = *base_window_rect;
	selected = false;
}

Button* Console_Panel::Check_For_Click(int mouse_x_pos, int mouse_y_pos)
{
	for (int i = 0; i < console_panel_buttons.size(); i++)
	{
		if (check_if_point_in_rect(console_panel_buttons[i].button_rect, mouse_x_pos, mouse_y_pos))
		{
			return &console_panel_buttons[i];
		}
	}
	return NULL;
}

void Console_Panel::render()
{
	if (DEBUG_CONSOLE) cout << "starting to render panel : " << panel_num << endl;
	
	for (int p = 0; p < console_panel_buttons.size(); p++)
	{
		console_panel_buttons[p].render();
	}


}

void Console_Panel::free()
{
	for (int p = 0; p < console_panel_buttons.size(); p++)
	{
		console_panel_buttons[p].free();
	}
}

// Create Buttons;

void Console_Panel::Add_Dot_Inventory_Slot_To_Panel(SDL_Rect offset_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, TILE_WIDTH, TILE_HEIGHT };
	
	Button new_inventory_button = Button(BUTTON_ACTION_INVENTORY_BUTTON, pos_rect, true, panel_name);
	new_inventory_button.slot_item_pointer = slot_pointer;
	new_inventory_button.Add_Button_Diagnostic(gRenderer, 0, 0, gFont_small, &slot_pointer->item_number,true, true);
	new_inventory_button.Add_Button_Sprite(spritesheet, { Fetch_Inventory_Item_Template(slot_pointer->inventory_item_code).sprite_config.x* SPRITESHEET_W, Fetch_Inventory_Item_Template(slot_pointer->inventory_item_code).sprite_config.y*SPRITESHEET_H, SPRITESHEET_W, SPRITESHEET_H }, 0, 0);
	console_panel_buttons.push_back(new_inventory_button);
}

void Console_Panel::Add_Dot_Crafting_Slot_To_Panel(SDL_Rect offset_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, TILE_WIDTH, TILE_HEIGHT };

	Button new_crafting_button = Button(BUTTON_ACTION_PLACE_SCAFFOLD, pos_rect, true, panel_name);
	new_crafting_button.slot_item_pointer = slot_pointer;
	new_crafting_button.Add_Button_Diagnostic(gRenderer, 0, 0, gFont_small, &slot_pointer->item_number, true,true);
	new_crafting_button.Add_Button_Sprite(spritesheet, { Fetch_Inventory_Item_Template(slot_pointer->inventory_item_code).sprite_config.x * SPRITESHEET_W, Fetch_Inventory_Item_Template(slot_pointer->inventory_item_code).sprite_config.y*SPRITESHEET_H, SPRITESHEET_W, SPRITESHEET_H }, 0, 0);
	console_panel_buttons.push_back(new_crafting_button);
}

void Console_Panel::Add_Production_Slot_To_Panel(SDL_Rect offset_rect, Dot* focus_dot, int production_array_num, LTexture* spritesheet, int panel_name)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, offset_rect.w, offset_rect.h };

	Inventory_Item_Template production_item = Fetch_Inventory_Item_Template(Return_Tile_Template_By_Identifier(focus_dot->npc_dot_config.production_status_array[production_array_num].slot_tile_name).inventory_pointer);

	Button production_item_button = { BUTTON_ACTION_CREATE_PRODUCTION_ORDER, pos_rect,true, PANEL_PRODUCTION_ORDERS,0 };

	production_item_button.Add_Button_Sprite(spritesheet, { production_item.sprite_config.x*SPRITESHEET_W,production_item.sprite_config.y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W }, 0, 0);

	console_panel_buttons.push_back(production_item_button);
}

void Console_Panel::Add_Label_To_Panel(string Label, SDL_Rect offset_rect, int panel_name, int button_action, bool filled)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, offset_rect.w , offset_rect.h };

	Button new_button = Button(button_action, pos_rect, filled, panel_name);
	new_button.Add_Button_Label(Label, gFont, false, NULL, { 255,255,255,255 }, 5, 5);
	console_panel_buttons.push_back(new_button);
}

void Console_Panel::Add_String_Diagnostic_To_Panel(string label, string* string_pointer, SDL_Rect offset_rect, int panel_name)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, offset_rect.w , offset_rect.h };

	Button new_button = Button(BUTTON_ACTION_DO_NOTHING, pos_rect, true, panel_name);
	new_button.Add_Button_Label(label, gFont, false, NULL, { 255,255,255,255 }, 5, 5);
	new_button.Add_Button_String_Diagnostic(gFont, string_pointer, { 255,255,255,255 }, 100, 5);
	console_panel_buttons.push_back(new_button);
}

void Console_Panel::Add_Number_Diagnostic_To_Panel(string label, int* value_pointer, SDL_Rect offset_rect, int panel_name, bool stat_bar, int* value_pointer_max)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, offset_rect.w , offset_rect.h };

	Button new_button = Button(BUTTON_ACTION_DO_NOTHING, pos_rect, true, panel_name);
	new_button.Add_Button_Label(label, gFont, false, NULL, { 255,255,255,255 }, 5, 5);

	if (stat_bar == false) new_button.Add_Button_Diagnostic(gRenderer, 100, 5, gFont, value_pointer);
	else new_button.Add_Button_Stat_Bar(gRenderer, 100, 5, gFont, value_pointer, value_pointer_max);

	console_panel_buttons.push_back(new_button);
}

void Console_Panel::Add_Simple_Linked_Number_To_Panel(int* value_pointer, SDL_Rect offset_rect, int panel_name)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, offset_rect.w , offset_rect.h };
	Button new_button = Button(BUTTON_ACTION_DO_NOTHING, pos_rect, true, panel_name);
	new_button.Add_Button_Diagnostic(gRenderer, offset_rect.w / 3, offset_rect.h / 3, gFont, value_pointer);
	console_panel_buttons.push_back(new_button);
}

void Console_Panel::Add_Simple_Button_With_Action(int action, bool is_icon, string button_text, SDL_Rect spritesheet_clip, LTexture* spritesheet, SDL_Rect offset_rect, int panel_name)
{
	SDL_Rect pos_rect = { panel_rect.x + offset_rect.x, panel_rect.y + offset_rect.y, offset_rect.w, offset_rect.h };

	Button action_button = Button(action, pos_rect, true, panel_name, 0, 0);
	if (is_icon == false) action_button.Add_Button_Label(button_text, gFont, false, NULL, { 255,255,255,255 }, 5, 5);
	else action_button.Add_Button_Sprite(spritesheet, spritesheet_clip, 0, 0);
	console_panel_buttons.push_back(action_button);
}

// CONSOLE WINDOWS CLASS, THESE CAN BE OPEN AND CLOSED AND YOU CAN CUSTOMIZE WHICH PANELS ARE ATTACHED TO EACH WINDOW

class Console_Window {
public:
	Console_Window::Console_Window(int window_type = NULL_WINDOW, int window_number = 0, Dot* focus_dot = NULL, LTexture* inventory_spritesheet = NULL, SDL_Rect window_size = { 0,0,0,0 }, bool active = true);
	map <int, Console_Panel> console_window_panels;
	vector<Button> console_panel_headers;

	void Create_Dot_Inventory_Panel(Dot* focus_dot, LTexture* spritesheet, int columns, int rows);
	void Create_Dot_Status_Panel(Dot* focus_dot);
	void Create_Dot_Equipment_Panel(LTexture* spritesheet, Dot* focus_dot);
	void Create_Dot_Crafting_Panel(LTexture* spritesheet, Dot* focus_dot,int rows, int columns);
	void Update_Dot_Crafting_Panel(LTexture* spritesheet, Dot* focus_dot, int rows, int columns);
	void Create_Dot_Production_Panel(LTexture* spritesheet, Dot* focus_dot);
	void Create_Dot_Job_Status_Panel(Dot* focus_dot);
	void Console_Window::Create_Action_Buttons();

	void Create_Close_Window_Panel();
	void Create_Panel_Header(int panel_type, string label_text);
	void Adjust_Panel_Button_Size();
	void Console_Window::Change_Active_Panel(int panel_type);
	
	void render();
	void free();
	
	Button* Check_For_Click(int mouse_x_pos, int mouse_y_pos);

	int console_window_type;
	int console_window_number;
	bool console_window_active;

	int menu_bar_height;
	Dot* window_focus_dot;

	SDL_Rect base_window_rect;
	SDL_Rect base_panel_rect;
	SDL_Color base_window_tint;
	SDL_Color base_window_highlight;

private:
	SDL_Renderer* console_window_renderer;
	LTexture* spritesheet;
	TTF_Font* console_font;
};

Console_Window::Console_Window(int window_type, int window_number, Dot* focus_dot, LTexture* inventory_spritesheet, SDL_Rect window_size, bool active)
{
	spritesheet = inventory_spritesheet;
	console_font = gFont;
	console_window_type = window_type;
	console_window_number = window_number;
	console_window_active = active;
	console_window_renderer = gRenderer;
	window_focus_dot = focus_dot;

	base_window_rect = window_size;
	menu_bar_height = TILE_HEIGHT * 4 / 5;
	base_panel_rect = { base_window_rect.x, base_window_rect.y + menu_bar_height, base_window_rect.w, base_window_rect.h - menu_bar_height };
	base_window_tint = { 100,100,100,100 };
	base_window_highlight = { 255,255,255,255 };

}

void Console_Window::Create_Panel_Header(int panel_type, string label_text)
{
	SDL_Rect header_offset = { 5,5,5,0 }; // first two are x,y offsets from top-left, last two are x-y, offsets from bottom right
	SDL_Rect panel_button_rect = { base_window_rect.x, base_window_rect.y, 15, menu_bar_height };
	
	Button console_panel_header = Button(BUTTON_ACTION_SWITCH_PANEL, panel_button_rect, true, panel_type, 0, 0);

	if (panel_type != PANEL_CLOSE_CONSOLE_WINDOW) console_panel_header.button_action = BUTTON_ACTION_SWITCH_PANEL;
	else console_panel_header.button_action = BUTTON_ACTION_CLOSE_CONSOLE_WINDOW;
	
	console_panel_header.Add_Button_Label(label_text, gFont, false, NULL, { 255,255,255,255 }, header_offset.x, header_offset.y);
	console_panel_header.button_rect.w = console_panel_header.button_label.get_width() + header_offset.w + header_offset.x;

	console_panel_headers.push_back(console_panel_header);
	Adjust_Panel_Button_Size();
}

void Console_Window::Adjust_Panel_Button_Size()
{
	int current_x = base_window_rect.x;
	int num_buttons = console_panel_headers.size();
	int total_button_width = 0;

	for (int i = 0; i < console_panel_headers.size(); i++)
	{
		total_button_width += console_panel_headers[i].button_label.get_width();
	}

	int extra_width_for_buttons = (base_window_rect.w - total_button_width)/num_buttons;

	for (int i = 0; i < console_panel_headers.size(); i++)
	{
		console_panel_headers[i].button_rect.x = current_x;
		console_panel_headers[i].button_rect.w = console_panel_headers[i].button_label.get_width() + extra_width_for_buttons;
		current_x += console_panel_headers[i].button_rect.w;
	}
}

void Console_Window::Change_Active_Panel(int panel_type)
{
	for (std::map<int, Console_Panel>::iterator it = console_window_panels.begin(); it != console_window_panels.end(); ++it)
	{
		if (it->second.panel_num == panel_type) it->second.selected = true;
		else it->second.selected = false;
	}
}

// Create Panels

void Console_Window::Create_Dot_Inventory_Panel(Dot* focus_dot, LTexture* spritesheet, int columns, int rows)
{
	int slot_num = 0;
	Console_Panel dot_inventory_panel = Console_Panel("Inventory", PANEL_DOT_INVENTORY, console_window_number, &base_panel_rect);
	for (int i = 0; i < rows; i++)
	{
		for (int p = 0; p < columns; p++)
		{
			SDL_Rect offset_rect;
			offset_rect.y = i * TILE_HEIGHT;
			offset_rect.x = p * TILE_WIDTH;

			dot_inventory_panel.Add_Dot_Inventory_Slot_To_Panel(offset_rect, spritesheet, gFont, &focus_dot->npc_dot_config.inventory_slots[slot_num], PANEL_DOT_INVENTORY);
			slot_num++;
		}
	}
	if (DEBUG_CONSOLE) cout << "adding dot inventory panel to window" << endl;
	console_window_panels.insert(pair <int, Console_Panel> (PANEL_DOT_INVENTORY,dot_inventory_panel));
	if (DEBUG_CONSOLE) cout << "adding header for dot inventory panel" << endl;
	Create_Panel_Header(PANEL_DOT_INVENTORY, "Inventory");
}

void Console_Window::Create_Dot_Status_Panel(Dot* focus_dot)
{
	int diagnostic_spacer = TILE_HEIGHT * 3 / 4;
	SDL_Rect offset_rect = { 0,0,base_panel_rect.w, diagnostic_spacer };
	Console_Panel dot_status_panel = Console_Panel("Stats", PANEL_DOT_DIAGNOSTIC, console_window_number, &base_panel_rect);

	if (focus_dot->dot_config[DOT_TYPE] == DOT_NPC || focus_dot->dot_config[DOT_TYPE] == DOT_PLAYER)
	{
		dot_status_panel.Add_String_Diagnostic_To_Panel("Dot Name", &focus_dot->npc_dot_config.dot_full_name,offset_rect, PANEL_DOT_DIAGNOSTIC);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Dot Health", &focus_dot->npc_dot_config.dot_stat_health, offset_rect, PANEL_DOT_DIAGNOSTIC, false, NULL);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Oxygen Need", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].max_level);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Hunger", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].max_level);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Tiredness", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].max_level);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Ennui", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_ENNUI].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_ENNUI].max_level);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Happiness", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HAPPINESS].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HAPPINESS].max_level);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Sanity", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SANITY].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SANITY].max_level);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Suit Oxygen", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].max_level);
		offset_rect.y += diagnostic_spacer;
	}
	else if (focus_dot->dot_config[DOT_TYPE] == DOT_TILE)
	{
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Tile Type", &focus_dot->multi_tile_config.tile_type, offset_rect, PANEL_DOT_DIAGNOSTIC,false,NULL);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Tile Name", &focus_dot->multi_tile_config.tile_name, offset_rect, PANEL_DOT_DIAGNOSTIC,false,NULL);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Current Health", &focus_dot->multi_tile_config.current_health, offset_rect, PANEL_DOT_DIAGNOSTIC, true, &focus_dot->multi_tile_config.max_health);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("X Coord", &focus_dot->x_tile, offset_rect, PANEL_DOT_DIAGNOSTIC, false,NULL);
		offset_rect.y += diagnostic_spacer;
		dot_status_panel.Add_Number_Diagnostic_To_Panel("Y Coord", &focus_dot->y_tile, offset_rect, PANEL_DOT_DIAGNOSTIC, false, NULL);
		offset_rect.y += diagnostic_spacer;
	}

	console_window_panels.insert(pair <int, Console_Panel>(PANEL_DOT_DIAGNOSTIC, dot_status_panel));
	Create_Panel_Header(PANEL_DOT_DIAGNOSTIC, "Stats");
}

void Console_Window::Create_Dot_Equipment_Panel(LTexture* spritesheet, Dot* focus_dot)
{
	Console_Panel dot_equipment_panel = Console_Panel("Equipment", PANEL_EQUIPMENT_LOADOUT, console_window_number, &base_panel_rect);

	SDL_Rect offset_rect = { 0, 0, base_panel_rect.w, TILE_HEIGHT };

	dot_equipment_panel.Add_Dot_Inventory_Slot_To_Panel(offset_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Spacesuit, PANEL_EQUIPMENT_LOADOUT);
	offset_rect.x += TILE_WIDTH;
	dot_equipment_panel.Add_Label_To_Panel("Spacesuit", offset_rect, PANEL_EQUIPMENT_LOADOUT, 0, false);

	offset_rect.x -= TILE_WIDTH;
	offset_rect.y += TILE_HEIGHT;
	dot_equipment_panel.Add_Dot_Inventory_Slot_To_Panel(offset_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Oxygen_Tank, PANEL_EQUIPMENT_LOADOUT);
	offset_rect.x += TILE_WIDTH;
	dot_equipment_panel.Add_Label_To_Panel("Oxygen Tank", offset_rect, PANEL_EQUIPMENT_LOADOUT, 0, false);

	offset_rect.x -= TILE_WIDTH;
	offset_rect.y += TILE_HEIGHT;
	dot_equipment_panel.Add_Dot_Inventory_Slot_To_Panel(offset_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Weapon, PANEL_EQUIPMENT_LOADOUT);
	offset_rect.x += TILE_WIDTH;
	dot_equipment_panel.Add_Label_To_Panel("Weapon", offset_rect, PANEL_EQUIPMENT_LOADOUT, 0 ,false);

	offset_rect.x -= TILE_WIDTH;
	offset_rect.y += TILE_HEIGHT;
	dot_equipment_panel.Add_Dot_Inventory_Slot_To_Panel(offset_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Mining_Laser, PANEL_EQUIPMENT_LOADOUT);
	offset_rect.x += TILE_WIDTH;
	dot_equipment_panel.Add_Label_To_Panel("Mining Laser", offset_rect, PANEL_EQUIPMENT_LOADOUT, 0, false);

	console_window_panels.insert(pair <int, Console_Panel>(PANEL_EQUIPMENT_LOADOUT, dot_equipment_panel));
	Create_Panel_Header(PANEL_EQUIPMENT_LOADOUT, "Equipment");
}

void Console_Window::Create_Dot_Crafting_Panel(LTexture* spritesheet, Dot* focus_dot, int rows, int columns)
{
	Console_Panel dot_crafting_panel = Console_Panel("Crafting", PANEL_CRAFTABLE_ITEMS, console_window_number, &base_panel_rect);

	int row = 0;
	int column = 0;

	for (int i = 0; i < focus_dot->npc_dot_config.craftable_items.size(); i++)
	{
		SDL_Rect offset_rect = { 0,0,TILE_WIDTH,TILE_HEIGHT };
		offset_rect.y = row * TILE_HEIGHT;
		offset_rect.x = column * TILE_WIDTH;
		dot_crafting_panel.Add_Dot_Crafting_Slot_To_Panel(offset_rect, spritesheet, gFont, &focus_dot->npc_dot_config.craftable_items[i], PANEL_CRAFTABLE_ITEMS);
			
		column++;
		if (column >= columns) column = 0, row++;
		if (row >= rows) break;
	}

	console_window_panels.insert(pair <int, Console_Panel>(PANEL_CRAFTABLE_ITEMS, dot_crafting_panel));
	Create_Panel_Header(PANEL_CRAFTABLE_ITEMS, "Build");
}

void Console_Window::Update_Dot_Crafting_Panel(LTexture* spritesheet, Dot* focus_dot, int rows, int columns)
{
	console_window_panels[PANEL_CRAFTABLE_ITEMS].console_panel_buttons.clear();

	int row = 0;
	int column = 0;

	for (int i = 0; i < focus_dot->npc_dot_config.craftable_items.size(); i++)
	{
		SDL_Rect offset_rect = { 0,0,TILE_WIDTH,TILE_HEIGHT };
		offset_rect.y = row * TILE_HEIGHT;
		offset_rect.x = column * TILE_WIDTH;
		console_window_panels[PANEL_CRAFTABLE_ITEMS].Add_Dot_Crafting_Slot_To_Panel(offset_rect, spritesheet, gFont, &focus_dot->npc_dot_config.craftable_items[i], PANEL_CRAFTABLE_ITEMS);

		column++;
		if (column >= columns) column = 0, row++;
		if (row >= rows) break;
	}
}

void Console_Window::Create_Dot_Production_Panel(LTexture* spritesheet, Dot* focus_dot)
{
	Console_Panel dot_production_panel = Console_Panel("Production", PANEL_PRODUCTION_ORDERS, console_window_number, &base_panel_rect);

	SDL_Rect offset_rect = {0,0,TILE_WIDTH,TILE_HEIGHT};

	for (int i = 0; i < 6; i++)
	{
		dot_production_panel.Add_Production_Slot_To_Panel(offset_rect, focus_dot, i, spritesheet,PANEL_PRODUCTION_ORDERS);
		offset_rect.x += TILE_WIDTH;
		dot_production_panel.Add_Simple_Linked_Number_To_Panel(&focus_dot->npc_dot_config.production_status_array[i].slot_requests, offset_rect, PANEL_PRODUCTION_ORDERS);
		offset_rect.x -= TILE_WIDTH;
		offset_rect.y += TILE_HEIGHT;
	}
	
	console_window_panels.insert(pair <int, Console_Panel>(PANEL_PRODUCTION_ORDERS, dot_production_panel));
	Create_Panel_Header(PANEL_PRODUCTION_ORDERS, "Production");
}

void Console_Window::Create_Dot_Job_Status_Panel(Dot* focus_dot)
{
	int diagnostic_spacer = TILE_HEIGHT * 3 / 4;
	SDL_Rect offset_rect = { 0,0,base_window_rect.w,diagnostic_spacer };
	Console_Panel dot_job_status_panel = Console_Panel("Jobs", PANEL_JOB_DIAGNOSTIC, console_window_number, &base_panel_rect);

	if (focus_dot->dot_config[DOT_TYPE] == DOT_NPC)
	{
		dot_job_status_panel.Add_Number_Diagnostic_To_Panel("Job Type", &focus_dot->npc_dot_config.console_current_dot_job, offset_rect, PANEL_JOB_DIAGNOSTIC, false, NULL);
		offset_rect.y += diagnostic_spacer;
		dot_job_status_panel.Add_Number_Diagnostic_To_Panel("Goal Action", &focus_dot->npc_dot_config.console_current_dot_goal, offset_rect, PANEL_JOB_DIAGNOSTIC, false, NULL);
		offset_rect.y += diagnostic_spacer;
		dot_job_status_panel.Add_Number_Diagnostic_To_Panel("Dot Focus Type", &focus_dot->npc_dot_config.console_current_dot_focus_type, offset_rect, PANEL_JOB_DIAGNOSTIC, false, NULL);
		offset_rect.y += diagnostic_spacer;
		dot_job_status_panel.Add_Simple_Button_With_Action(BUTTON_ACTION_CLEAR_DOT_GOALS, false, "Clear dot goals", { 0,0,0,0 }, NULL, offset_rect, PANEL_JOB_DIAGNOSTIC);
	}

	console_window_panels.insert(pair <int, Console_Panel>(PANEL_JOB_DIAGNOSTIC, dot_job_status_panel));
	Create_Panel_Header(PANEL_JOB_DIAGNOSTIC, "Job");
}

void Console_Window::Create_Action_Buttons()
{
	Console_Panel player_action_button_panel = Console_Panel("", PANEL_ACTION_BUTTONS, console_window_number, &base_panel_rect);

	SDL_Rect offset_rect = { 0, 0, TILE_WIDTH, TILE_HEIGHT };
	player_action_button_panel.Add_Simple_Button_With_Action(BUTTON_ACTION_MINE_ASTEROID, true, "", { 2 * SPRITESHEET_W, 2 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H }, spritesheet, offset_rect, PANEL_ACTION_BUTTONS);
	offset_rect.y += TILE_HEIGHT;
	player_action_button_panel.Add_Simple_Button_With_Action(BUTTON_ACTION_REMOVE_TILE, true, "", { 2 * SPRITESHEET_W, 1 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H }, spritesheet, offset_rect, PANEL_ACTION_BUTTONS);
	offset_rect.y += TILE_HEIGHT;
	player_action_button_panel.Add_Simple_Button_With_Action(BUTTON_ACTION_SPAWN_ENEMY, true, "", { 0 * SPRITESHEET_W, 3 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H }, spritesheet, offset_rect, PANEL_ACTION_BUTTONS);
	offset_rect.y += TILE_HEIGHT;

	player_action_button_panel.selected = true;
	console_window_panels.insert(pair <int, Console_Panel>(PANEL_ACTION_BUTTONS, player_action_button_panel));
}

void Console_Window::Create_Close_Window_Panel()
{
	Console_Panel close_window_panel = Console_Panel("Close", PANEL_CLOSE_CONSOLE_WINDOW, console_window_number, &base_panel_rect);
	
	console_window_panels.insert(pair <int, Console_Panel>(PANEL_CLOSE_CONSOLE_WINDOW, close_window_panel));
	Create_Panel_Header(PANEL_CLOSE_CONSOLE_WINDOW, "Close");
}

// MAIN FUNCTIONS

Button* Console_Window::Check_For_Click(int mouse_x_pos, int mouse_y_pos)
{
	for (int i = 0; i < console_panel_headers.size(); i++)
	{
		if (check_if_point_in_rect(console_panel_headers[i].button_rect, mouse_x_pos, mouse_y_pos))
		{
			return &console_panel_headers[i];
		}
	}
	
	for (std::map<int, Console_Panel>::iterator it = console_window_panels.begin(); it != console_window_panels.end(); ++it)
	{
		if (it->second.selected == true)
		{
			Button* clicked_button = it->second.Check_For_Click(mouse_x_pos, mouse_y_pos);
			if (clicked_button != NULL) return clicked_button;
		}
	}

	return NULL;
}

void Console_Window::render()
{
	if (DEBUG_CONSOLE) cout << "rendering window: " << console_window_type << endl;
	
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, base_window_tint.r, base_window_tint.g, base_window_tint.b, base_window_tint.a);
	SDL_RenderFillRect(gRenderer, &base_window_rect);
	SDL_SetRenderDrawColor(gRenderer, base_window_highlight.r, base_window_highlight.g, base_window_highlight.b, base_window_highlight.a);
	SDL_RenderDrawRect(gRenderer, &base_window_rect);
	
	for (int i = 0; i < console_panel_headers.size(); i++)
	{
		console_panel_headers[i].render();
	}
	for (std::map<int, Console_Panel>::iterator it = console_window_panels.begin(); it != console_window_panels.end(); ++it)
	{
		if (it->second.selected == true) it->second.render();
	}
}

void Console_Window::free()
{
	for (int i = 0; i < console_panel_headers.size(); i++)
	{
		console_panel_headers[i].free();
	}
	for (std::map<int, Console_Panel>::iterator it = console_window_panels.begin(); it != console_window_panels.end(); ++it)
	{
		if (it->second.selected == true) it->second.free();
	}
}


/// Console Class

class Console {
public:
	Console::Console(SDL_Renderer* gRenderer, TTF_Font* gFont, Intelligence* intelligence, LTexture textures[]);
	void render(Camera* camera);
	void render_advanced_diagnostics(SDL_Renderer* gRenderer, Camera* camera);
	void free();
	void Open_Diagnostic_On_Clicked_Dot(Dot* new_focus_dot);

	// WINDOW CREATION FUNCTIONS
	void Create_Dot_Diagnostic_Window(Dot* new_focus_dot);
	void Create_Player_Diagnostic_Window(Dot* player_dot);
	void Create_Options_Restart_Window(SDL_Rect* reference_rect);
	void Create_Action_Button_Window();

	// HELPERS
	bool check_console_for_clicks(int mouse_x_pos, int mouse_y_pos);
	bool check_if_mouse_is_over_console(int mouse_x_pos, int mouse_y_pos);
	Button* return_clicked_button(int mouse_x_pos, int mouse_y_pos);
	void Handle_Console_Clicks();
	void Handle_Console_Click_And_Hold();
	void Handle_Console_Unclick();

	void Pull_Up_Restart_Screen();
	void Update_Console(SDL_Renderer* gRenderer);

	int current_action = BUTTON_ACTION_MINE_ASTEROID;
	int current_selected_inventory_item;

	Intelligence* current_intelligence;
	Dot* currently_selected_dot;
	Dot* dot_to_transfer_from; // for interactions between dots
	Dot* dot_to_transfer_to;

	map <int, Console_Window> console_windows;
	int num_open_windows = 0;
	int dot_diagnostic_window_width = 9 * TILE_WIDTH;
	int dot_diagnostic_window_height = 9 * TILE_WIDTH;

	Button* last_clicked_button;
	int last_clicked_window;
	
	bool first_click = false;

	SDL_Rect dot_focus_window_rect;
	SDL_Rect player_focus_window_rect;
	SDL_Rect options_window_rect;
	SDL_Rect action_buttons_window_rect;

	Console_Diagnostic fps_diagnostic;

	bool debug = false;


private:
	TTF_Font* console_font;
	LTexture* texture_array[NUM_TILESHEETS];
	LTexture* bolt_sprites;
	LTexture* dot_spritesheet;
	LTexture* asteroid_spritesheet;
	LTexture* enemy_ship_spritesheet;
	LTexture* container_spritesheet;
	LTexture* inventory_spritesheet;
	LTexture* standard_tilesheet;
};

Console::Console(SDL_Renderer* gRenderer, TTF_Font* gFont, Intelligence* intelligence, LTexture textures[])
{
	// MAIN CONSOLE INIT
	console_font = gFont;

	for (int p = 0; p < NUM_TILESHEETS; ++p) { texture_array[p] = &textures[p]; };
	bolt_sprites = texture_array[BOLT_SPRITES];
	dot_spritesheet = texture_array[DOT_SPRITESHEET];
	asteroid_spritesheet = texture_array[ASTEROID_SPRITESHEET];
	enemy_ship_spritesheet = texture_array[ENEMY_SHIP_SPRITESHEET];
	container_spritesheet = texture_array[CONTAINER_SPRITESHEET];
	inventory_spritesheet = texture_array[INVENTORY_SPRITESHEET];
	standard_tilesheet = texture_array[TILESHEET];

	current_selected_inventory_item = INVENTORY_EMPTY_SLOT;
	
	current_intelligence = intelligence;
	currently_selected_dot = intelligence->lifepod;
	dot_to_transfer_from = NULL;
	dot_to_transfer_to = NULL;


	if (DEBUG_CONSOLE) cout << "creating fps diagnostic" << endl;
	fps_diagnostic = Console_Diagnostic(0, 0, console_font, &intelligence->player_dot->dot_config[FPS], false);

	if (DEBUG_CONSOLE) cout << "creating player diagnostic window" << endl;
	Create_Player_Diagnostic_Window(intelligence->player_dot);

	if (DEBUG_CONSOLE) cout << "creating action button" << endl;
	Create_Action_Button_Window();
}

void Console::free()
{
	fps_diagnostic.free();
	
	for (std::map<int, Console_Window>::iterator it = console_windows.begin(); it != console_windows.end(); ++it)
	{
		it->second.free();
	}
}

void Console::render(Camera* camera)
{
	
	if (DEBUG_CONSOLE) cout << "rendering fps" << endl;
	fps_diagnostic.render(gRenderer, new SDL_Rect{ SCREEN_WIDTH - TILE_WIDTH,0,TILE_WIDTH,TILE_HEIGHT });
	
	if (DEBUG_CONSOLE) cout << "starting to render windows" << endl;
	for (std::map<int, Console_Window>::iterator it = console_windows.begin(); it != console_windows.end(); ++it)
	{
		if (DEBUG_CONSOLE) cout << "rendering a window" << endl;
		it->second.render();
	}

	if (DEBUG_ADVANCED_DOT_DIAGNOSTICS == 1) render_advanced_diagnostics(gRenderer, camera);
}

void Console::render_advanced_diagnostics(SDL_Renderer* gRenderer, Camera* camera)
{
	// ADVANCED DIAGNOSTICS
	if (debug)
	{

		if (currently_selected_dot != NULL)
		{
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 50);

			// RENDER DOTS CURRENT PATH
			for (int i = 0; i < currently_selected_dot->npc_dot_config.current_goal_path.size(); i++)
			{
				SDL_Rect path_box = { currently_selected_dot->npc_dot_config.current_goal_path[i].x_tile*TILE_WIDTH - camera->camera_box.x,
					currently_selected_dot->npc_dot_config.current_goal_path[i].y_tile*TILE_WIDTH - camera->camera_box.y,
					TILE_WIDTH,
					TILE_HEIGHT };

				SDL_RenderFillRect(gRenderer, &path_box);
			}

			// RENDER A LINE TO DOTS CURRENT TARGET

			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			if (currently_selected_dot->npc_dot_config.current_goal_list.size() != 0 && currently_selected_dot->npc_dot_config.current_goal_list.back().pointer_to_dot_pointer != NULL)
			{
				Dot* current_focus = currently_selected_dot->npc_dot_config.current_goal_list.back().pointer_to_dot_pointer;
				int x1 = currently_selected_dot->dot_rect.x + currently_selected_dot->dot_rect.w / 2 - camera->camera_box.x;
				int y1 = currently_selected_dot->dot_rect.y + currently_selected_dot->dot_rect.h / 2 - camera->camera_box.y;
				int x2 = current_focus->dot_rect.x + currently_selected_dot->dot_rect.w / 2 - camera->camera_box.x;
				int y2 = current_focus->dot_rect.y + currently_selected_dot->dot_rect.h / 2 - camera->camera_box.y;

				SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
			}
		}
	}
}

// WINDOW CREATION FUNCTIONS

void Console::Create_Dot_Diagnostic_Window(Dot* new_focus_dot)
{
	dot_focus_window_rect = { (num_open_windows-2)*dot_diagnostic_window_width,0,dot_diagnostic_window_width,dot_diagnostic_window_height };
	Console_Window dot_focus_window = Console_Window{ WINDOW_DOT_DIAGNOSTIC, num_open_windows, new_focus_dot, inventory_spritesheet, dot_focus_window_rect };

	if (DEBUG_CONSOLE) cout << "creating dot status panel" << endl;
	dot_focus_window.Create_Dot_Status_Panel(new_focus_dot);
	if (DEBUG_CONSOLE) cout << "creating dot inventory panel" << endl;
	dot_focus_window.Create_Dot_Inventory_Panel(new_focus_dot, inventory_spritesheet, 8, 3);
	if (DEBUG_CONSOLE) cout << "creating misc panels" << endl;
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_NPC) dot_focus_window.Create_Dot_Equipment_Panel(inventory_spritesheet, new_focus_dot);
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_NPC) dot_focus_window.Create_Dot_Job_Status_Panel(new_focus_dot);
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_TILE) dot_focus_window.Create_Dot_Production_Panel(inventory_spritesheet, new_focus_dot);

	dot_focus_window.console_window_panels[PANEL_DOT_DIAGNOSTIC].selected = true;
	dot_focus_window.Create_Close_Window_Panel();
	console_windows.insert(pair <int, Console_Window>(num_open_windows, dot_focus_window));

	num_open_windows++;
}

void Console::Create_Player_Diagnostic_Window(Dot* player_dot)
{
	player_focus_window_rect = { 0,SCREEN_HEIGHT - 6 * TILE_HEIGHT - 3 * TILE_HEIGHT / 4,8 * TILE_WIDTH,6 * TILE_HEIGHT + 3 * TILE_HEIGHT / 4 };
	Console_Window player_focus_window = Console_Window{ WINDOW_PLAYER_DIAGNOSTIC, num_open_windows, player_dot, inventory_spritesheet, player_focus_window_rect };
	
	if (DEBUG_CONSOLE) cout << "creating player inventory panel" << endl;
	player_focus_window.Create_Dot_Inventory_Panel(player_dot, inventory_spritesheet, 8, 3);

	if (DEBUG_CONSOLE) cout << "creating player crafting panel" << endl;
	player_focus_window.Create_Dot_Crafting_Panel(inventory_spritesheet, player_dot, 3, 8);

	player_focus_window.console_window_panels[PANEL_DOT_INVENTORY].selected = true;
	console_windows.insert(pair <int, Console_Window>(num_open_windows, player_focus_window));

	num_open_windows++;
}

void Console::Create_Options_Restart_Window(SDL_Rect* reference_rect)
{
	//vector<Button> panel_buttons;

	//SDL_Rect restart_button_rect = { reference_rect->x + TILE_WIDTH, reference_rect->y + TILE_HEIGHT, reference_rect->w * 2 / 3, TILE_HEIGHT };
	//SDL_Rect quit_button_rect = { reference_rect->x + TILE_WIDTH, reference_rect->y + TILE_HEIGHT*2, reference_rect->w * 2 / 3, TILE_HEIGHT };

	//Button restart_text = { gRenderer, BUTTON_ACTION_DO_NOTHING, *reference_rect,false, PANEL_OPTIONS_RESTART };
	//restart_text.Add_Button_Label("You were murdered by space. How galling.", console_font, false, NULL, { 255,255,255,255 }, TILE_WIDTH * 1 * 2/3, TILE_HEIGHT/3);

	//Button restart_button = { gRenderer, BUTTON_ACTION_RESTART_GAME, restart_button_rect,true, PANEL_OPTIONS_RESTART };
	//restart_button.Add_Button_Label("Restart", console_font, false, NULL, { 255,255,255,255 }, 5, 8);

	//Button quit_button = { gRenderer, BUTTON_ACTION_QUIT_GAME, quit_button_rect,true, PANEL_OPTIONS_RESTART };
	//quit_button.Add_Button_Label("Quit", console_font, false, NULL, { 255,255,255,255 }, 5, 8);

	//panel_buttons.push_back(restart_text);
	//panel_buttons.push_back(restart_button);
	//panel_buttons.push_back(quit_button);

	//console_window_panels.insert(pair <int, vector<Button>>(PANEL_OPTIONS_RESTART, panel_buttons));
}

void Console::Create_Action_Button_Window()
{
	SDL_Rect action_button_window_rect = { 8*TILE_WIDTH,SCREEN_HEIGHT - 6 * TILE_HEIGHT - 3 * TILE_HEIGHT / 4,TILE_WIDTH,6 * TILE_HEIGHT + 3 * TILE_HEIGHT / 4 };
	Console_Window action_button_window = Console_Window{ WINDOW_ACTION_BUTTONS, num_open_windows, current_intelligence->player_dot, inventory_spritesheet, action_button_window_rect };
	action_button_window.base_panel_rect.y -= action_button_window.menu_bar_height;

	action_button_window.Create_Action_Buttons();
	console_windows.insert(pair <int, Console_Window>(num_open_windows, action_button_window));

	num_open_windows++;
}


// HELPER FUNCTIONS

void Console::Pull_Up_Restart_Screen()
{
	//console_windows[WINDOW_OPTIONS].console_window_active = true;
	//console_windows[WINDOW_OPTIONS].active_panel = PANEL_OPTIONS_RESTART;
}

bool Console::check_console_for_clicks(int mouse_x_pos, int mouse_y_pos)
{
	for (std::map<int, Console_Window>::iterator it = console_windows.begin(); it != console_windows.end(); ++it)
	{
		Button* clicked_button = it->second.Check_For_Click(mouse_x_pos, mouse_y_pos);
		if (clicked_button != NULL)
		{	
			if (clicked_button->button_action == BUTTON_ACTION_CLOSE_CONSOLE_WINDOW)
			{
				console_windows.erase(it);
				num_open_windows--;
				return false;
			}
			else
			{
				clicked_button->button_is_pressed = true;
				if (last_clicked_button!= NULL && last_clicked_button != clicked_button) last_clicked_button->button_is_pressed = false;
				last_clicked_button = clicked_button;
				last_clicked_window = it->second.console_window_number;
				return true;
			}
		}
	}

	return false;
}

bool Console::check_if_mouse_is_over_console(int mouse_x_pos, int mouse_y_pos)
{
	for (std::map<int, Console_Window>::iterator it = console_windows.begin(); it != console_windows.end(); ++it)
	{
		if (check_if_point_in_rect(it->second.base_window_rect, mouse_x_pos, mouse_y_pos) == true) return true;
	}
	return false;
}

void Console::Handle_Console_Clicks()
{
	if (last_clicked_button->button_action == BUTTON_ACTION_SWITCH_PANEL) console_windows[last_clicked_window].Change_Active_Panel(last_clicked_button->button_panel_type);

	switch (console_windows[last_clicked_window].console_window_type)
	{
	case WINDOW_ACTION_BUTTONS:
		switch (last_clicked_button->button_panel_type)
		{
		case PANEL_ACTION_BUTTONS:
			current_action = last_clicked_button->button_action;
			break;
		}
		break;
	case WINDOW_PLAYER_DIAGNOSTIC:
		switch (last_clicked_button->button_panel_type)
		{
		case PANEL_CRAFTABLE_ITEMS:
			if (last_clicked_button->button_action == BUTTON_ACTION_PLACE_SCAFFOLD)
			{
				current_selected_inventory_item = last_clicked_button->slot_item_pointer->inventory_item_code;
				current_action = BUTTON_ACTION_PLACE_SCAFFOLD;
			}
			break;
		case PANEL_DOT_INVENTORY:
			if (last_clicked_button->button_action == BUTTON_ACTION_INVENTORY_BUTTON && last_clicked_button->slot_item_pointer != NULL)
			{
				dot_to_transfer_from = console_windows[last_clicked_window].window_focus_dot;
				current_selected_inventory_item = last_clicked_button->slot_item_pointer->inventory_item_code;
				current_action = BUTTON_ACTION_INVENTORY_BUTTON;
			}
			break;
		}
		break;
	case WINDOW_DOT_DIAGNOSTIC:
		switch (last_clicked_button->button_panel_type)
		{
		case PANEL_DOT_INVENTORY:
			if (last_clicked_button->button_action == BUTTON_ACTION_INVENTORY_BUTTON && last_clicked_button->slot_item_pointer != NULL)
			{
				dot_to_transfer_from = console_windows[last_clicked_window].window_focus_dot;
				current_selected_inventory_item = last_clicked_button->slot_item_pointer->inventory_item_code;
				current_action = BUTTON_ACTION_INVENTORY_BUTTON;
			}
			break;
		case PANEL_DOT_DIAGNOSTIC:
			break;
		case PANEL_PRODUCTION_ORDERS:
			if (last_clicked_button->button_action == BUTTON_ACTION_CREATE_PRODUCTION_ORDER)
			{
				if (console_windows[last_clicked_window].window_focus_dot->npc_dot_config.production_status_array[last_clicked_button->button_config_num].slot_tile_name != TILE_GENERIC_TILE)
				{
					console_windows[last_clicked_window].window_focus_dot->npc_dot_config.production_status_array[last_clicked_button->button_config_num].slot_requests++;
				}
			}
			break;
		case PANEL_JOB_DIAGNOSTIC:
			if (last_clicked_button->button_action == BUTTON_ACTION_CLEAR_DOT_GOALS)
			{
				console_windows[last_clicked_window].window_focus_dot->dot_wipe_all_job_tasks();
			}
			break;
		}
		break;
	}
}

void Console::Handle_Console_Click_And_Hold()
{

}

void Console::Handle_Console_Unclick()
{
	switch (console_windows[last_clicked_window].console_window_type)
	{
	case WINDOW_PLAYER_DIAGNOSTIC:
		switch (last_clicked_button->button_panel_type)
		{
		case PANEL_DOT_INVENTORY:
			dot_to_transfer_to = console_windows[last_clicked_window].window_focus_dot;
			if (dot_to_transfer_from != NULL && dot_to_transfer_to != NULL && dot_to_transfer_from != dot_to_transfer_to)
			{
				current_intelligence->Create_Job_To_Transfer_Item_From_Dot_to_Dot(dot_to_transfer_from, dot_to_transfer_to, current_selected_inventory_item,1);
				current_action = BUTTON_ACTION_DO_NOTHING;
				dot_to_transfer_from = NULL;
			}
			break;
		}
		break;
	case WINDOW_DOT_DIAGNOSTIC:
		switch (last_clicked_button->button_panel_type)
		{
		case PANEL_DOT_INVENTORY:
			dot_to_transfer_to = console_windows[last_clicked_window].window_focus_dot;
			if (dot_to_transfer_from != NULL && dot_to_transfer_to != NULL && dot_to_transfer_from != dot_to_transfer_to)
			{
				current_intelligence->Create_Job_To_Transfer_Item_From_Dot_to_Dot(dot_to_transfer_from, dot_to_transfer_to, current_selected_inventory_item,1);
				current_action = BUTTON_ACTION_DO_NOTHING;
				dot_to_transfer_from = NULL;
			}
			break;
		}
		break;
	}
}

Button* Console::return_clicked_button(int mouse_x_pos, int mouse_y_pos)
{
	if (last_clicked_button != NULL)
	{
		return last_clicked_button;
	}
	else return NULL;
}

void Console::Open_Diagnostic_On_Clicked_Dot(Dot* new_focus_dot) 
{
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_NPC) Create_Dot_Diagnostic_Window(new_focus_dot);
	else if (new_focus_dot->dot_config[DOT_TYPE] == DOT_TILE && new_focus_dot->multi_tile_config.tile_type != VACUUM) Create_Dot_Diagnostic_Window(new_focus_dot);
}

void Console::Update_Console(SDL_Renderer* gRenderer)
{
	current_intelligence->player_dot->Check_Craftable_Items();
	current_intelligence->current_action = current_action;
	console_windows[0].Update_Dot_Crafting_Panel(inventory_spritesheet,current_intelligence->player_dot, 3,8);
}

#endif