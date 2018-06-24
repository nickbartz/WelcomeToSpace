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
	Console_Diagnostic::Console_Diagnostic(SDL_Renderer* gRenderer = NULL, int x_offset = 0, int y_offset = 0, TTF_Font* gFont = NULL, int* diagnostic_value = NULL, bool do_not_render_if_zero = false);
	void free();
	void render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect);

private:
	int* linked_value;
	bool dont_render_if_zero;

	SDL_Rect offset_rect;
	SDL_Color textColor = { 255, 255, 255, 255 };
	TTF_Font* diagnostic_font;

	LTexture diagnostic_value_texture;

};

Console_Diagnostic::Console_Diagnostic(SDL_Renderer* gRenderer, int x_offset, int y_offset, TTF_Font* gFont, int* diagnostic_value, bool do_not_render_if_zero)
{
	diagnostic_font = gFont;
	linked_value = diagnostic_value;
	dont_render_if_zero = do_not_render_if_zero;

	offset_rect = { x_offset, y_offset, 0, 0 };
}

void Console_Diagnostic::render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect)
{
	if (*linked_value != 0 || dont_render_if_zero == false)
	{
		string diagnostic_value = std::to_string(*linked_value);

		diagnostic_value_texture.loadFromRenderedText(diagnostic_value, textColor, diagnostic_font, gRenderer);
		SDL_Rect diagnostic_value_rect = { pos_rect->x + offset_rect.x, pos_rect->y + offset_rect.y, diagnostic_value_texture.getWidth(), diagnostic_value_texture.getHeight() };
		SDL_Rect diagnostic_value_clip = { 0,0, diagnostic_value_rect.w, diagnostic_value_rect.h };
		diagnostic_value_texture.render(gRenderer, &diagnostic_value_rect, &diagnostic_value_clip);
	}
}

void Console_Diagnostic::free()
{
	diagnostic_value_texture.free();
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
	Console_Label::Console_Label(TTF_Font* gFont = NULL, SDL_Color text_color = { 255,255,255,255 }, bool string_is_pointer = false, string* pointer_to_string = NULL, string actual_string = "", int offset_x = 0, int offset_y = 0);
	void render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect);

	SDL_Color Console_Label_Color;
	LTexture Console_Label_Texture;
	TTF_Font* Console_Label_Font;
	bool pointer;
	string* string_pointer;
	string diagnostic_label_string;
	SDL_Rect offset_rect;

};

Console_Label::Console_Label(TTF_Font* gFont, SDL_Color text_color, bool string_is_pointer, string* pointer_to_string, string actual_string, int offset_x, int offset_y)
{
	Console_Label_Color = text_color;
	Console_Label_Font = gFont;
	pointer = string_is_pointer;
	string_pointer = pointer_to_string;
	diagnostic_label_string = actual_string;
	offset_rect = { offset_x, offset_y, 0,0 };
}

void Console_Label::render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect)
{
	if (pointer) Console_Label_Texture.loadFromRenderedText(*string_pointer, Console_Label_Color, Console_Label_Font, gRenderer);
	else Console_Label_Texture.loadFromRenderedText(diagnostic_label_string, Console_Label_Color, Console_Label_Font, gRenderer);
	
	SDL_Rect text_clip = { 0,0,Console_Label_Texture.getWidth(), Console_Label_Texture.getHeight() };
	SDL_Rect text_rect = { pos_rect->x + offset_rect.x,pos_rect->y + offset_rect.y, Console_Label_Texture.getWidth(),  Console_Label_Texture.getHeight() };
	Console_Label_Texture.render(gRenderer, &text_rect, &text_clip);
}

class Console_Sprite {
public:
	Console_Sprite::Console_Sprite(LTexture* spritesheet = NULL, SDL_Rect spritesheet_clip = { 0,0,0,0 }, int offset_x = 0, int offset_y = 0);
	void render(SDL_Renderer* gRenderer, SDL_Rect* pos_rect);

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

// BUTTON CLASS

class Button {
public:
	Button::Button(SDL_Renderer* gRenderer = NULL, int action = BUTTON_ACTION_DO_NOTHING, SDL_Rect button_rect = { 0,0,0,0 }, bool button_background = false, int panel_name = PANEL_NO_PANEL, int button_config = 0);
	
	void free();
	void render(SDL_Renderer* gRenderer);
	void toggle_button_clicked();
	void Add_Button_Sprite(LTexture* spritesheet, SDL_Rect spritesheet_clip,  int offset_x, int offset_y);
	void Add_Button_Label(string button_label_text, TTF_Font* gFont, bool is_pointer_to_string, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y);
	void Add_Button_Diagnostic(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, bool dont_render_if_zero = false);
	void Add_Button_Stat_Bar(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, int* diagnostic_value_max = NULL);
	void Add_Button_String_Diagnostic(TTF_Font* gFont, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y);
	void Change_Slot_Tint(SDL_Color new_tint_color);
	void Change_Slot_Highlight(SDL_Color new_highlight_color);

	
	int button_action;
	int button_group;
	int button_config_num;

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

	Dot_Inventory_Slot* slot_item_pointer;

	bool button_has_label;
	bool button_has_sprite;
	bool button_has_diagnostic;
	bool button_has_string_diagnostic;
	bool button_has_stat_bar;

	bool button_filled;
	bool button_is_pressed = false;

private:
};

Button::Button(SDL_Renderer* gRenderer, int action, SDL_Rect pos_rect, bool button_background, int button_set, int button_config)
{
	button_action = action;
	button_rect = pos_rect;
	button_clip = { 0,0,button_rect.w,button_rect.h };

	button_group = button_set;
	button_config_num = button_config;

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

void Button::render(SDL_Renderer* gRenderer)
{	
	toggle_button_clicked();

	if (slot_item_pointer != NULL)
	{
		button_sprite.console_sprite_clip.x = Fetch_Inventory(slot_item_pointer->inventory_item_code).clip_rect_x * SPRITESHEET_W;
		button_sprite.console_sprite_clip.y = Fetch_Inventory(slot_item_pointer->inventory_item_code).clip_rect_y * SPRITESHEET_H;
	}

	if (button_filled)
	{

		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(gRenderer, slot_tint.r, slot_tint.g, slot_tint.b, slot_tint.a);
		SDL_RenderFillRect(gRenderer, &button_rect);
		SDL_SetRenderDrawColor(gRenderer, slot_highlight.r, slot_highlight.g, slot_highlight.b, slot_highlight.a);
		SDL_RenderDrawRect(gRenderer, &button_rect);
	}
	
	if (button_has_label) button_label.render(gRenderer, &button_rect);
	if (button_has_sprite) button_sprite.render(gRenderer, &button_rect);
	if (button_has_diagnostic) button_diagnostic.render(gRenderer, &button_rect);
	if (button_has_string_diagnostic) button_string_diagnostic.render(gRenderer, &button_rect);
	if (button_has_stat_bar) button_stat_bar.render(gRenderer, &button_rect);
}

void Button::toggle_button_clicked()
{
	if (button_is_pressed)
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

void Button::Add_Button_Diagnostic(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, bool dont_render_if_zero)
{
	button_diagnostic = Console_Diagnostic(gRenderer, offset_x, offset_y, gFont, diagnostic_value, dont_render_if_zero);
	button_has_diagnostic = true;
}

void Button::Add_Button_Stat_Bar(SDL_Renderer* gRenderer, int offset_x, int offset_y, TTF_Font* gFont, int* diagnostic_value, int* diagnostic_value_max)
{
	button_stat_bar = Console_Stat_Bar(gRenderer, offset_x, offset_y, gFont, diagnostic_value, diagnostic_value_max);
	button_has_stat_bar = true;
}

void Button::Add_Button_Label(string button_label_text, TTF_Font* gFont, bool is_pointer_to_string, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y )
{
	button_label = Console_Label(gFont, button_label_color, is_pointer_to_string, pointer, button_label_text, offset_x, offset_y);
	button_has_label = true;
}

void Button::Add_Button_String_Diagnostic(TTF_Font* gFont, string* pointer, SDL_Color button_label_color, int offset_x, int offset_y)
{
	button_string_diagnostic = Console_Label(gFont, button_label_color, true, pointer, "", offset_x, offset_y);
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

}

class Console_Window {
public:
	Console_Window::Console_Window(int window_name = NULL_WINDOW, SDL_Renderer* gRenderer = NULL, Dot* focus_dot = NULL, LTexture* inventory_spritesheet = NULL, TTF_Font* gFont = NULL, SDL_Rect window_size = { 0,0,0,0 }, bool active = true);
	map <int, vector<Button>> console_window_panels;
	vector<Button> console_window_buttons;
	
	Button Create_Dot_Inventory_Slot(SDL_Renderer* gRenderer, SDL_Rect pos_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name);
	Button Create_Crafting_Button(SDL_Renderer* gRenderer, SDL_Rect pos_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name);
	Button Create_Label(SDL_Renderer* gRenderer, TTF_Font* gFont, string Label, SDL_Rect* ref_rect, int x_offset, int y_offset, int panel_name, int button_action = BUTTON_ACTION_DO_NOTHING, bool filled = false);
	Button Create_String_Diagnostic(SDL_Renderer* gRenderer, TTF_Font* gFont, string label, string* string_pointer, SDL_Rect* ref_rect, int x_offset, int y_offset, int panel_name);
	Button Create_Number_Diagnostic(SDL_Renderer* gRenderer, TTF_Font* gFont, string label, int* value_pointer, SDL_Rect* ref_rect, int x_offset, int y_offset, int panel_name, bool stat_bar = false, int* value_pointer_max = NULL);
	Button Create_Simple_Linked_Number(SDL_Renderer* gRenderer, TTF_Font* gFont, int* value_pointer, SDL_Rect* ref_rect, SDL_Rect offset, int panel_name);

	void Create_Dot_Inventory(SDL_Renderer* gRenderer, Dot* focus_dot, LTexture* spritesheet, TTF_Font* gFont, int offset_x, int offset_y, int columns, int rows, int panel_name, string panel_label = "Inventory");
	void Create_Dot_Diagnostic(SDL_Renderer* gRenderer, Dot* focus_dot, int dot_type, int offset_x, int offset_y, TTF_Font* gFont, int panel_name);
	void Create_Dot_Equipment_Loadout(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name);
	void Create_Dot_Crafting_Window(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name, int offset_x, int offset_y, int rows, int columns, string window_name);
	void Update_Dot_Crafting_Window(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name, int offset_x, int offset_y, int rows, int columns, string window_name);
	void Create_Item_Production_Window(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name);
	void Create_Dot_Job_Window(TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name);

	void Create_Options_Restart_Window(SDL_Rect* reference_rect);
	void Create_Panel_Button(string button_name, int panel_name, int offset_x, int offset_y);
	void Adjust_Panel_Button_Size();
	
	void render(SDL_Renderer* gRenderer);
	
	Button* Check_For_Click(int mouse_x_pos, int mouse_y_pos);
	void Create_Dot_Diagnostic_Window(Dot* new_focus_dot);
	void Create_Player_Diagnostic_Window(Dot* player_dot, int panel_name);
	void Create_Action_Button_Window(SDL_Rect* reference_rect, LTexture* spritesheet);
	
	int console_window_name;
	bool console_window_active;
	int active_panel = PANEL_NO_PANEL;
	Dot* focus_dot;

	SDL_Rect base_window_rect;
	SDL_Color base_window_tint;
	SDL_Color base_window_highlight;

private:
	SDL_Renderer* gRenderer = gRenderer;
	LTexture* spritesheet;
	TTF_Font* console_font;
};

Console_Window::Console_Window(int window_name, SDL_Renderer* gRenderer, Dot* focus_dot, LTexture* inventory_spritesheet, TTF_Font* gFont, SDL_Rect window_size, bool active)
{
	spritesheet = inventory_spritesheet;
	console_font = gFont;
	console_window_name = window_name;
	console_window_active = active;

	base_window_rect = window_size;
	base_window_tint = { 100,100,100,50 };
	base_window_highlight = { 255,255,255,255 };
}

Button Console_Window::Create_Dot_Inventory_Slot(SDL_Renderer* gRenderer, SDL_Rect pos_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name)
{
	Button new_inventory_button = Button(gRenderer, BUTTON_ACTION_INVENTORY_BUTTON, pos_rect, true, panel_name);
	new_inventory_button.slot_item_pointer = slot_pointer;
	new_inventory_button.Add_Button_Diagnostic(gRenderer, 0, 0, gFont, &slot_pointer->item_number, true);
	new_inventory_button.Add_Button_Sprite(spritesheet, { Fetch_Inventory(slot_pointer->inventory_item_code).clip_rect_x * SPRITESHEET_W, Fetch_Inventory(slot_pointer->inventory_item_code).clip_rect_y*SPRITESHEET_H, SPRITESHEET_W, SPRITESHEET_H }, 0, 0);
	return new_inventory_button;
}

Button Console_Window::Create_Crafting_Button(SDL_Renderer* gRenderer, SDL_Rect pos_rect, LTexture* spritesheet, TTF_Font* gFont, Dot_Inventory_Slot* slot_pointer, int panel_name)
{
	Button new_crafting_button = Button(gRenderer, BUTTON_ACTION_PLACE_SCAFFOLD, pos_rect, true, panel_name);
	new_crafting_button.slot_item_pointer = slot_pointer;
	new_crafting_button.Add_Button_Diagnostic(gRenderer, 0, 0, gFont, &slot_pointer->item_number, true);
	new_crafting_button.Add_Button_Sprite(spritesheet, { Fetch_Inventory(slot_pointer->inventory_item_code).clip_rect_x * SPRITESHEET_W, Fetch_Inventory(slot_pointer->inventory_item_code).clip_rect_y*SPRITESHEET_H, SPRITESHEET_W, SPRITESHEET_H }, 0, 0);
	return new_crafting_button;
}

Button Console_Window::Create_Label(SDL_Renderer* gRenderer, TTF_Font* gFont, string Label, SDL_Rect* ref_rect, int x_offset, int y_offset, int panel_name, int button_action, bool filled)
{
	SDL_Rect pos_rect = { ref_rect->x + x_offset, ref_rect->y + y_offset, ref_rect->w,TILE_HEIGHT*3/4 };
	Button new_button = Button(gRenderer, button_action, pos_rect, filled, panel_name);
	new_button.Add_Button_Label(Label, gFont, false, NULL, { 255,255,255,255 }, 5, 5);
	return new_button;
}

Button Console_Window::Create_String_Diagnostic(SDL_Renderer* gRenderer, TTF_Font* gFont, string label, string* string_pointer, SDL_Rect* ref_rect, int x_offset, int y_offset, int panel_name)
{
	SDL_Rect pos_rect = { ref_rect->x + x_offset, ref_rect->y + y_offset, ref_rect->w,TILE_HEIGHT * 3 / 4 };
	Button new_button = Button(gRenderer, BUTTON_ACTION_DO_NOTHING, pos_rect, true, panel_name);
	new_button.Add_Button_Label(label, gFont, false, NULL, { 255,255,255,255 }, 5, 5);
	new_button.Add_Button_String_Diagnostic(gFont, string_pointer, { 255,255,255,255 }, 100, 5);
	return new_button;
}

Button Console_Window::Create_Number_Diagnostic(SDL_Renderer* gRenderer, TTF_Font* gFont, string label, int* value_pointer, SDL_Rect* ref_rect, int x_offset, int y_offset, int panel_name, bool stat_bar, int* value_pointer_max)
{
	SDL_Rect pos_rect = { ref_rect->x + x_offset, ref_rect->y + y_offset, ref_rect->w,TILE_HEIGHT * 3 / 4 };
	Button new_button = Button(gRenderer, BUTTON_ACTION_DO_NOTHING, pos_rect, true, panel_name);
	new_button.Add_Button_Label(label, gFont, false, NULL, { 255,255,255,255 }, 5, 5);
	
	if (stat_bar == false) new_button.Add_Button_Diagnostic(gRenderer, 100, 5, gFont, value_pointer);
	else new_button.Add_Button_Stat_Bar(gRenderer, 100, 5, gFont, value_pointer, value_pointer_max);

	return new_button;
}

Button Console_Window::Create_Simple_Linked_Number(SDL_Renderer* gRenderer, TTF_Font* gFont, int* value_pointer, SDL_Rect* ref_rect, SDL_Rect offset, int panel_name)
{
	SDL_Rect pos_rect = { ref_rect->x + offset.x, ref_rect->y + offset.y, offset.w,offset.h };
	Button new_button = Button(gRenderer, BUTTON_ACTION_DO_NOTHING, pos_rect, true, panel_name);
	
	new_button.Add_Button_Diagnostic(gRenderer, offset.w/3, offset.h/3, gFont, value_pointer);
	
	return new_button;
}

// PANEL CREATING TOOLS

void Console_Window::Create_Dot_Inventory(SDL_Renderer* gRenderer, Dot* focus_dot, LTexture* spritesheet, TTF_Font* gFont, int offset_x, int offset_y, int columns, int rows, int panel_name, string panel_label)
{
	int slot_num = 0;

	SDL_Rect ref_rect = { base_window_rect.x + offset_x, base_window_rect.y + offset_y, TILE_WIDTH,TILE_HEIGHT };
	vector<Button> panel_buttons;
	for (int i = 0; i < rows; i++)
	{
		for (int p = 0; p < columns; p++)
		{
			ref_rect.y = base_window_rect.y + offset_y + i * TILE_HEIGHT;
			ref_rect.x = base_window_rect.x + offset_x + p * TILE_WIDTH;
			panel_buttons.push_back(Create_Dot_Inventory_Slot(gRenderer, ref_rect, spritesheet, gFont, &focus_dot->npc_dot_config.inventory_slots[slot_num], panel_name));
			slot_num++;
		}
	}
	console_window_panels.insert(pair <int, vector<Button>>(panel_name, panel_buttons));

	Create_Panel_Button(panel_label, PANEL_DOT_INVENTORY, 0, -25);
}

void Console_Window::Create_Dot_Diagnostic(SDL_Renderer* gRenderer, Dot* focus_dot, int dot_type, int offset_x, int offset_y, TTF_Font* gFont, int panel_name)
{
	int num_diagnostics = 0;
	int diagnostic_spacer = TILE_HEIGHT*3/4;

	vector<Button> panel_buttons;

	if (focus_dot->dot_config[DOT_TYPE] == DOT_NPC || focus_dot->dot_config[DOT_TYPE] == DOT_PLAYER)
	{
		panel_buttons.push_back(Create_String_Diagnostic(gRenderer, gFont, "Dot Name", &focus_dot->npc_dot_config.dot_full_name, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Dot Health", &focus_dot->npc_dot_config.dot_stat_health, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, false));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Oxygen Need", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_OXYGEN_NEED].max_level));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Hunger", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HUNGER_NEED].max_level));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Tiredness", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SLEEP_NEED].max_level));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Ennui", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_ENNUI].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_ENNUI].max_level));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Happiness", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HAPPINESS].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_HAPPINESS].max_level));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Sanity", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SANITY].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SANITY].max_level));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Suit Oxygen", &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].current_level, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->npc_dot_config.dot_priority_map[DOT_PRIORITY_SPACESUIT_OXYGEN].max_level));
		num_diagnostics++;
	}
	else if (focus_dot->dot_config[DOT_TYPE] == DOT_TILE)
	{
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Tile Type", &focus_dot->multi_tile_config.tile_type, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Tile Name", &focus_dot->multi_tile_config.tile_name, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Current Health", &focus_dot->multi_tile_config.current_health, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, true, &focus_dot->multi_tile_config.max_health));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "X Coord", &focus_dot->x_tile, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, false));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, gFont, "Y Coord", &focus_dot->y_tile, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, false));
		num_diagnostics++;
	}

	console_window_panels.insert(pair <int, vector<Button>>(panel_name, panel_buttons));
	Create_Panel_Button("Stats", PANEL_DOT_DIAGNOSTIC, 0, -25);
}

void Console_Window::Create_Dot_Equipment_Loadout(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name)
{
	vector<Button> panel_buttons;
	SDL_Rect ref_rect = { base_window_rect.x, base_window_rect.y, TILE_WIDTH, TILE_HEIGHT };
	panel_buttons.push_back(Create_Dot_Inventory_Slot(gRenderer, ref_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Spacesuit, panel_name));
	panel_buttons.push_back(Create_Label(gRenderer, console_font, "Spacesuit", &ref_rect, TILE_WIDTH, 0, panel_name));
	ref_rect.y = ref_rect.y + TILE_HEIGHT;
	panel_buttons.push_back(Create_Dot_Inventory_Slot(gRenderer, ref_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Oxygen_Tank, panel_name));
	panel_buttons.push_back(Create_Label(gRenderer, console_font, "Oxygen Tank", &ref_rect, TILE_WIDTH, 0, panel_name));
	ref_rect.y = ref_rect.y + TILE_HEIGHT;
	panel_buttons.push_back(Create_Dot_Inventory_Slot(gRenderer, ref_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Weapon, panel_name));
	panel_buttons.push_back(Create_Label(gRenderer, console_font, "Weapon", &ref_rect, TILE_WIDTH, 0, panel_name));
	ref_rect.y = ref_rect.y + TILE_HEIGHT;
	panel_buttons.push_back(Create_Dot_Inventory_Slot(gRenderer, ref_rect, spritesheet, console_font, &focus_dot->npc_dot_config.dot_equipment_config.Mining_Laser, panel_name));
	panel_buttons.push_back(Create_Label(gRenderer, console_font, "Mining Laser", &ref_rect, TILE_WIDTH, 0, panel_name));

	console_window_panels.insert(pair <int, vector<Button>>(panel_name, panel_buttons));
	Create_Panel_Button("Gear", PANEL_EQUIPMENT_LOADOUT, 0, -25);
}

void Console_Window::Create_Dot_Crafting_Window(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name, int offset_x, int offset_y, int rows, int columns, string window_name)
{
	int row = 0;
	int column = 0;

	SDL_Rect ref_rect = { base_window_rect.x + offset_x, base_window_rect.y + offset_y, TILE_WIDTH,TILE_HEIGHT };
	vector<Button> panel_buttons;

	for (int i = 0; i < focus_dot->npc_dot_config.craftable_items.size(); i++)
	{
		ref_rect.y = base_window_rect.y + offset_y + row * TILE_HEIGHT;
		ref_rect.x = base_window_rect.x + offset_x + column * TILE_WIDTH;
		panel_buttons.push_back(Create_Crafting_Button(gRenderer, ref_rect, spritesheet, console_font, &focus_dot->npc_dot_config.craftable_items[i], panel_name));
		column++;
		if (column >= columns) column = 0, row++;
		if (row >= rows) break;
	}

	console_window_panels.insert(pair <int, vector<Button>>(panel_name, panel_buttons));
	Create_Panel_Button(window_name, PANEL_CRAFTABLE_ITEMS, 0, -25);
}

void Console_Window::Update_Dot_Crafting_Window(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name, int offset_x, int offset_y, int rows, int columns, string window_name)
{
	console_window_panels[panel_name].clear();

	int row = 0;
	int column = 0;

	SDL_Rect ref_rect = { base_window_rect.x + offset_x, base_window_rect.y + offset_y, TILE_WIDTH,TILE_HEIGHT };

	for (int i = 0; i < focus_dot->npc_dot_config.craftable_items.size(); i++)
	{
		ref_rect.y = base_window_rect.y + offset_y + row * TILE_HEIGHT;
		ref_rect.x = base_window_rect.x + offset_x + column * TILE_WIDTH;
		console_window_panels[panel_name].push_back(Create_Crafting_Button(gRenderer, ref_rect, spritesheet, console_font, &focus_dot->npc_dot_config.craftable_items[i], panel_name));
		column++;
		if (column >= columns) column = 0, row++;
		if (row >= rows) break;
	}
}

void Console_Window::Create_Item_Production_Window(LTexture* spritesheet, TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name)
{
	vector<Button> panel_buttons;

	SDL_Rect production_item_1_rect = { base_window_rect.x, base_window_rect.y, TILE_WIDTH, TILE_HEIGHT };
	Inventory_Item production_1_item = Fetch_Inventory(Return_Tile_By_Name(focus_dot->npc_dot_config.production_status_array[0].slot_tile_name).inventory_pointer);
	Button production_item_1 = { gRenderer, BUTTON_ACTION_CREATE_PRODUCTION_ORDER, production_item_1_rect,true, PANEL_PRODUCTION_ORDERS,0 };
	production_item_1.Add_Button_Sprite(spritesheet, { production_1_item.clip_rect_x*SPRITESHEET_W,production_1_item.clip_rect_y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W },0,0);
	panel_buttons.push_back(Create_Simple_Linked_Number(gRenderer, console_font, &focus_dot->npc_dot_config.production_status_array[0].slot_requests, &production_item_1_rect, { TILE_WIDTH,0,TILE_WIDTH,TILE_HEIGHT },panel_name));

	SDL_Rect production_item_2_rect = { base_window_rect.x, base_window_rect.y+TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	Inventory_Item production_2_item = Fetch_Inventory(Return_Tile_By_Name(focus_dot->npc_dot_config.production_status_array[1].slot_tile_name).inventory_pointer);
	Button production_item_2 = { gRenderer, BUTTON_ACTION_CREATE_PRODUCTION_ORDER, production_item_2_rect,true, PANEL_PRODUCTION_ORDERS,1 };
	production_item_2.Add_Button_Sprite(spritesheet, { production_2_item.clip_rect_x*SPRITESHEET_W,production_2_item.clip_rect_y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W }, 0, 0);
	panel_buttons.push_back(Create_Simple_Linked_Number(gRenderer, console_font, &focus_dot->npc_dot_config.production_status_array[1].slot_requests, &production_item_1_rect, { TILE_WIDTH,TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT }, panel_name));

	SDL_Rect production_item_3_rect = { base_window_rect.x, base_window_rect.y+2*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	Inventory_Item production_3_item = Fetch_Inventory(Return_Tile_By_Name(focus_dot->npc_dot_config.production_status_array[2].slot_tile_name).inventory_pointer);
	Button production_item_3 = { gRenderer, BUTTON_ACTION_CREATE_PRODUCTION_ORDER, production_item_3_rect,true, PANEL_PRODUCTION_ORDERS,2 };
	production_item_3.Add_Button_Sprite(spritesheet, { production_3_item.clip_rect_x*SPRITESHEET_W,production_3_item.clip_rect_y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W }, 0, 0);
	panel_buttons.push_back(Create_Simple_Linked_Number(gRenderer, console_font, &focus_dot->npc_dot_config.production_status_array[2].slot_requests, &production_item_1_rect, { TILE_WIDTH,2*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT }, panel_name));

	SDL_Rect production_item_4_rect = { base_window_rect.x, base_window_rect.y + 3 * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	Inventory_Item production_4_item = Fetch_Inventory(Return_Tile_By_Name(focus_dot->npc_dot_config.production_status_array[3].slot_tile_name).inventory_pointer);
	Button production_item_4 = { gRenderer, BUTTON_ACTION_CREATE_PRODUCTION_ORDER, production_item_4_rect,true, PANEL_PRODUCTION_ORDERS,3 };
	production_item_4.Add_Button_Sprite(spritesheet, { production_4_item.clip_rect_x*SPRITESHEET_W,production_4_item.clip_rect_y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W }, 0, 0);
	panel_buttons.push_back(Create_Simple_Linked_Number(gRenderer, console_font, &focus_dot->npc_dot_config.production_status_array[3].slot_requests, &production_item_1_rect, { TILE_WIDTH,3 * TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT }, panel_name));

	SDL_Rect production_item_5_rect = { base_window_rect.x, base_window_rect.y + 4 * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	Inventory_Item production_5_item = Fetch_Inventory(Return_Tile_By_Name(focus_dot->npc_dot_config.production_status_array[4].slot_tile_name).inventory_pointer);
	Button production_item_5 = { gRenderer, BUTTON_ACTION_CREATE_PRODUCTION_ORDER, production_item_5_rect,true, PANEL_PRODUCTION_ORDERS,4 };
	production_item_5.Add_Button_Sprite(spritesheet, { production_5_item.clip_rect_x*SPRITESHEET_W,production_5_item.clip_rect_y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W }, 0, 0);
	panel_buttons.push_back(Create_Simple_Linked_Number(gRenderer, console_font, &focus_dot->npc_dot_config.production_status_array[4].slot_requests, &production_item_1_rect, { TILE_WIDTH,4 * TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT }, panel_name));

	SDL_Rect production_item_6_rect = { base_window_rect.x, base_window_rect.y + 5 * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
	Inventory_Item production_6_item = Fetch_Inventory(Return_Tile_By_Name(focus_dot->npc_dot_config.production_status_array[5].slot_tile_name).inventory_pointer);
	Button production_item_6 = { gRenderer, BUTTON_ACTION_CREATE_PRODUCTION_ORDER, production_item_6_rect,true, PANEL_PRODUCTION_ORDERS,5 };
	production_item_6.Add_Button_Sprite(spritesheet, { production_6_item.clip_rect_x*SPRITESHEET_W,production_6_item.clip_rect_y*SPRITESHEET_H,SPRITESHEET_W, SPRITESHEET_W }, 0, 0);
	panel_buttons.push_back(Create_Simple_Linked_Number(gRenderer, console_font, &focus_dot->npc_dot_config.production_status_array[5].slot_requests, &production_item_1_rect, { TILE_WIDTH,5 * TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT }, panel_name));

	panel_buttons.push_back(production_item_1);
	panel_buttons.push_back(production_item_2);
	panel_buttons.push_back(production_item_3);
	panel_buttons.push_back(production_item_4);
	panel_buttons.push_back(production_item_5);
	panel_buttons.push_back(production_item_6);

	console_window_panels.insert(pair <int, vector<Button>>(panel_name, panel_buttons));
	Create_Panel_Button("Production", PANEL_PRODUCTION_ORDERS, 0, -25);
}

void Console_Window::Create_Dot_Job_Window(TTF_Font* console_font, SDL_Renderer* gRenderer, Dot* focus_dot, int panel_name)
{
	int num_diagnostics = 0;
	int diagnostic_spacer = TILE_HEIGHT * 3 / 4;

	vector<Button> panel_buttons;

	if (focus_dot->dot_config[DOT_TYPE] == DOT_NPC)
	{
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, console_font, "Job Type", &focus_dot->npc_dot_config.current_dot_job, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, false));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, console_font, "Goal Action", &focus_dot->npc_dot_config.current_dot_goal, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, false));
		num_diagnostics++;
		panel_buttons.push_back(Create_Number_Diagnostic(gRenderer, console_font, "Dot Focus Type", &focus_dot->npc_dot_config.current_dot_focus_type, &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, false));
		num_diagnostics++;
	}

	panel_buttons.push_back(Create_Label(gRenderer, console_font, "Clear Goals", &base_window_rect, 0, diagnostic_spacer*num_diagnostics, panel_name, BUTTON_ACTION_CLEAR_DOT_GOALS, true));

	console_window_panels.insert(pair <int, vector<Button>>(panel_name, panel_buttons));
	Create_Panel_Button("Jobs", PANEL_JOB_DIAGNOSTIC, 0, -25);
}

void Console_Window::Create_Panel_Button(string button_name, int panel_name, int offset_x, int offset_y)
{
	SDL_Rect panel_button_rect = { base_window_rect.x + offset_x, base_window_rect.y + offset_y, 15, 25};
	Button new_panel_button = Button(gRenderer, BUTTON_ACTION_SWITCH_PANEL, panel_button_rect, true, panel_name);
	new_panel_button.Add_Button_Label(button_name, console_font, false, NULL, { 255,255,255,255 },5, 5);
	console_window_buttons.push_back(new_panel_button);
	Adjust_Panel_Button_Size();
}

void Console_Window::Adjust_Panel_Button_Size()
{
	int num_buttons = console_window_buttons.size();
	int width = base_window_rect.w / num_buttons;
	
	for (int i = 0; i < console_window_buttons.size(); i++)
	{
		console_window_buttons[i].button_rect.x = i*width;
		console_window_buttons[i].button_rect.w = width;
	}
}

// WINDOW CREATING FUNCTIONS

void Console_Window::Create_Dot_Diagnostic_Window(Dot* new_focus_dot)
{
	focus_dot = new_focus_dot;
	console_window_panels.clear();
	console_window_buttons.clear();
	Create_Dot_Inventory(gRenderer, new_focus_dot, spritesheet, console_font, 0, 0, 8, 3, PANEL_DOT_INVENTORY);
	Create_Dot_Diagnostic(gRenderer, new_focus_dot, DOT_PLAYER, 0, 0, console_font, PANEL_DOT_DIAGNOSTIC);
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_NPC) Create_Dot_Equipment_Loadout(spritesheet, console_font, gRenderer, new_focus_dot, PANEL_EQUIPMENT_LOADOUT);
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_NPC) Create_Dot_Job_Window(console_font, gRenderer, new_focus_dot, PANEL_JOB_DIAGNOSTIC);
	if (new_focus_dot->dot_config[DOT_TYPE] == DOT_TILE) Create_Item_Production_Window(spritesheet, console_font, gRenderer, new_focus_dot, PANEL_PRODUCTION_ORDERS);
	active_panel = PANEL_DOT_DIAGNOSTIC;
}

void Console_Window::Create_Player_Diagnostic_Window(Dot* player_dot, int panel_name)
{
	console_window_panels.clear();
	console_window_buttons.clear();
	Create_Dot_Inventory(gRenderer, player_dot, spritesheet, console_font, 0, 0, 8, 3, PANEL_DOT_INVENTORY, "Storage");
	Create_Dot_Crafting_Window(spritesheet, console_font, gRenderer, player_dot, PANEL_CRAFTABLE_ITEMS, 0, 0, 6, 8, "Buildable Items");
	active_panel = panel_name;
}

void Console_Window::Create_Options_Restart_Window(SDL_Rect* reference_rect)
{
	vector<Button> panel_buttons;

	SDL_Rect restart_button_rect = { reference_rect->x + TILE_WIDTH, reference_rect->y + TILE_HEIGHT, reference_rect->w * 2 / 3, TILE_HEIGHT };
	SDL_Rect quit_button_rect = { reference_rect->x + TILE_WIDTH, reference_rect->y + TILE_HEIGHT*2, reference_rect->w * 2 / 3, TILE_HEIGHT };

	Button restart_text = { gRenderer, BUTTON_ACTION_DO_NOTHING, *reference_rect,false, PANEL_OPTIONS_RESTART };
	restart_text.Add_Button_Label("You were murdered by space. How galling.", console_font, false, NULL, { 255,255,255,255 }, TILE_WIDTH * 1 * 2/3, TILE_HEIGHT/3);

	Button restart_button = { gRenderer, BUTTON_ACTION_RESTART_GAME, restart_button_rect,true, PANEL_OPTIONS_RESTART };
	restart_button.Add_Button_Label("Restart", console_font, false, NULL, { 255,255,255,255 }, 5, 8);

	Button quit_button = { gRenderer, BUTTON_ACTION_QUIT_GAME, quit_button_rect,true, PANEL_OPTIONS_RESTART };
	quit_button.Add_Button_Label("Quit", console_font, false, NULL, { 255,255,255,255 }, 5, 8);

	panel_buttons.push_back(restart_text);
	panel_buttons.push_back(restart_button);
	panel_buttons.push_back(quit_button);

	console_window_panels.insert(pair <int, vector<Button>>(PANEL_OPTIONS_RESTART, panel_buttons));
}

void Console_Window::Create_Action_Button_Window(SDL_Rect* reference_rect, LTexture* spritesheet)
{
	vector<Button> panel_buttons;

	SDL_Rect mark_for_mining_rect = { reference_rect->x, reference_rect->y, TILE_WIDTH, TILE_HEIGHT };
	Button mark_for_mining_button = { gRenderer, BUTTON_ACTION_MINE_ASTEROID, mark_for_mining_rect,true, PANEL_ACTION_BUTTONS };
	mark_for_mining_button.Add_Button_Sprite(spritesheet, { 2 * SPRITESHEET_W, 2 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H }, 0, 0);

	SDL_Rect inspect_rect = { reference_rect->x + TILE_WIDTH, reference_rect->y, TILE_WIDTH, TILE_HEIGHT };
	Button inspect_button = { gRenderer, BUTTON_ACTION_INSPECT, inspect_rect,true, PANEL_ACTION_BUTTONS };
	inspect_button.Add_Button_Sprite(spritesheet, { 3 * SPRITESHEET_W, 3 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H }, 0, 0);

	SDL_Rect delete_rect = { reference_rect->x + 2*TILE_WIDTH, reference_rect->y, TILE_WIDTH, TILE_HEIGHT };
	Button delete_button = { gRenderer, BUTTON_ACTION_REMOVE_TILE, delete_rect,true, PANEL_ACTION_BUTTONS };
	delete_button.Add_Button_Sprite(spritesheet, { 2 * SPRITESHEET_W, 1 * SPRITESHEET_H,SPRITESHEET_W,SPRITESHEET_H }, 0, 0);

	panel_buttons.push_back(mark_for_mining_button);
	panel_buttons.push_back(inspect_button);
	panel_buttons.push_back(delete_button);

	console_window_panels.insert(pair <int, vector<Button>>(PANEL_ACTION_BUTTONS, panel_buttons));

	active_panel = PANEL_ACTION_BUTTONS;
}

// MAIN FUNCTIONS

Button* Console_Window::Check_For_Click(int mouse_x_pos, int mouse_y_pos)
{
	for (int p = 0; p < console_window_buttons.size(); p++)
	{
		if (check_if_point_in_rect(console_window_buttons[p].button_rect, mouse_x_pos, mouse_y_pos))
		{
			return &console_window_buttons[p];
		}
	}
	
	for (int i = 0; i < console_window_panels[active_panel].size(); i++)
	{
		if (check_if_point_in_rect(console_window_panels[active_panel][i].button_rect, mouse_x_pos, mouse_y_pos))
		{
			return &console_window_panels[active_panel][i];
		}
	}
	return NULL;
}

void Console_Window::render(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, base_window_tint.r, base_window_tint.g, base_window_tint.b, base_window_tint.a);
	SDL_RenderFillRect(gRenderer, &base_window_rect);
	SDL_SetRenderDrawColor(gRenderer, base_window_highlight.r, base_window_highlight.g, base_window_highlight.b, base_window_highlight.a);
	SDL_RenderDrawRect(gRenderer, &base_window_rect);
	
	for (int p = 0; p < console_window_buttons.size(); p++)
	{
		console_window_buttons[p].render(gRenderer);
	}
	
	for (int p = 0; p < console_window_panels[active_panel].size(); p++)
	{
		console_window_panels[active_panel][p].render(gRenderer);
	}
}


/// Console Class

class Console {
public:
	Console::Console(SDL_Renderer* gRenderer, TTF_Font* gFont, Intelligence* intelligence, LTexture textures[]);
	void render(SDL_Renderer* gRenderer, Camera* camera);
	void free();
	void Change_Current_Focus_Dot(SDL_Renderer* gRenderer, Dot* new_focus_dot);

	// HELPERS
	bool check_console_for_clicks(int mouse_x_pos, int mouse_y_pos);
	Button* return_clicked_button(int mouse_x_pos, int mouse_y_pos);
	void Handle_Console_Clicks();
	void Pull_Up_Restart_Screen();
	void Update_Console(SDL_Renderer* gRenderer);

	int current_action = BUTTON_ACTION_MINE_ASTEROID;
	int current_selected_inventory_item;

	Intelligence* current_intelligence;
	Dot* currently_selected_dot;

	map <int, Console_Window> console_windows;

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

	dot_focus_window_rect = { 0,25,8*TILE_WIDTH,6*TILE_HEIGHT + 3 * TILE_HEIGHT / 4 };
	Console_Window dot_focus_window = Console_Window{ WINDOW_DOT_DIAGNOSTIC, gRenderer, currently_selected_dot, inventory_spritesheet, gFont, dot_focus_window_rect,false };
	dot_focus_window.Create_Dot_Diagnostic_Window(currently_selected_dot);
	console_windows.insert(pair <int, Console_Window>(WINDOW_DOT_DIAGNOSTIC, dot_focus_window));

	player_focus_window_rect = { 0,SCREEN_HEIGHT-6*TILE_HEIGHT - 3*TILE_HEIGHT/4,8 * TILE_WIDTH,6 * TILE_HEIGHT + 3* TILE_HEIGHT/4};
	Console_Window player_focus_window = Console_Window{ WINDOW_PLAYER_DIAGNOSTIC, gRenderer, intelligence->player_dot, inventory_spritesheet, gFont, player_focus_window_rect };
	player_focus_window.Create_Player_Diagnostic_Window(intelligence->player_dot, PANEL_DOT_INVENTORY);
	console_windows.insert(pair <int, Console_Window>(WINDOW_PLAYER_DIAGNOSTIC, player_focus_window));

	fps_diagnostic = Console_Diagnostic(gRenderer, 0, 0, console_font, &intelligence->player_dot->dot_config[FPS], false);

	action_buttons_window_rect = { 8*TILE_WIDTH,SCREEN_HEIGHT - TILE_HEIGHT,TILE_WIDTH*4,TILE_HEIGHT };
	Console_Window action_button_window = Console_Window{ WINDOW_ACTION_BUTTONS, gRenderer, intelligence->player_dot, inventory_spritesheet, gFont, action_buttons_window_rect };
	action_button_window.Create_Action_Button_Window(&action_buttons_window_rect,inventory_spritesheet);
	console_windows.insert(pair <int, Console_Window>(WINDOW_ACTION_BUTTONS, action_button_window));

	options_window_rect = { SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3,10 * TILE_WIDTH, 4* TILE_HEIGHT };
	Console_Window options_window = Console_Window{ WINDOW_OPTIONS,gRenderer, NULL, NULL, console_font, options_window_rect,false };
	options_window.Create_Options_Restart_Window(&options_window_rect);
	console_windows.insert(pair <int, Console_Window> (WINDOW_OPTIONS, options_window));
}

void Console::free()
{
}

void Console::render(SDL_Renderer* gRenderer, Camera* camera)
{
	fps_diagnostic.render(gRenderer, new SDL_Rect{ SCREEN_WIDTH - TILE_WIDTH,0,TILE_WIDTH,TILE_HEIGHT });
	for (int i = 0; i < console_windows.size(); i++)
	{
		if (console_windows[i].console_window_active == true) console_windows[i].render(gRenderer);
		
	}

	// ADVANCED DIAGNOSTICS
	if (debug)
	{

		if (currently_selected_dot != NULL)
		{
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 50);
			
			// RENDER DOTS CURRENT PATH
			for (int i = 0; i < currently_selected_dot->npc_dot_config.current_goal_path.size(); i++)
			{
				SDL_Rect path_box = {	currently_selected_dot->npc_dot_config.current_goal_path[i].x_tile*TILE_WIDTH - camera->camera_box.x,
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


// HELPER FUNCTIONS

void Console::Pull_Up_Restart_Screen()
{
	console_windows[WINDOW_OPTIONS].console_window_active = true;
	console_windows[WINDOW_OPTIONS].active_panel = PANEL_OPTIONS_RESTART;
}

bool Console::check_console_for_clicks(int mouse_x_pos, int mouse_y_pos)
{
	for (int i = 0; i < console_windows.size(); i++)
	{
		if (console_windows[i].console_window_active == true)
		{
			Button* clicked_button = console_windows[i].Check_For_Click(mouse_x_pos, mouse_y_pos);
			if (clicked_button != NULL)
			{
				// IF YOU CLICK A PANEL SWITCH BUTTON, SWITCH PANELS
				if (clicked_button->button_action == BUTTON_ACTION_SWITCH_PANEL) console_windows[i].active_panel = clicked_button->button_group;

				clicked_button->button_is_pressed = true;

				if (last_clicked_button != NULL && last_clicked_button != clicked_button) last_clicked_button->button_is_pressed = false;

				last_clicked_button = clicked_button;
				last_clicked_window = console_windows[i].console_window_name;
				
				//
				return true;
			}
		}
	}

	return false;
}

void Console::Handle_Console_Clicks()
{
	switch (last_clicked_window)
	{
	case WINDOW_ACTION_BUTTONS:
		switch (last_clicked_button->button_group)
		{
		case PANEL_ACTION_BUTTONS:
			current_action = last_clicked_button->button_action;
			break;
		}
		break;
	case WINDOW_PLAYER_DIAGNOSTIC:
		switch (last_clicked_button->button_group)
		{
		case PANEL_CRAFTABLE_ITEMS:
			if (last_clicked_button->button_action == BUTTON_ACTION_PLACE_SCAFFOLD)
			{
				current_selected_inventory_item = last_clicked_button->slot_item_pointer->inventory_item_code;
				current_action = BUTTON_ACTION_PLACE_SCAFFOLD;
			}
			break;
		case PANEL_DOT_INVENTORY:
			if (last_clicked_button->button_action == BUTTON_ACTION_INVENTORY_BUTTON)
			{
				current_selected_inventory_item = last_clicked_button->slot_item_pointer->inventory_item_code;
				current_action = BUTTON_ACTION_PLACE_ITEM;
			}
			break;
		//case PANEL_EQUIPMENT_LOADOUT:
		//	if (last_clicked_button->button_action == BUTTON_ACTION_INVENTORY_BUTTON)
		//	{
		//		if (Return_Tile_By_Inventory_Item(last_clicked_button->slot_item_pointer->inventory_item_code).tile_type == ITEM_TYPE_MINING_LASER)
		//		{
		//			current_action = BUTTON_ACTION_MINING_LASER;
		//		}
		//		else if (Return_Tile_By_Inventory_Item(last_clicked_button->slot_item_pointer->inventory_item_code).tile_type == ITEM_TYPE_WEAPON)
		//		{
		//			current_action = BUTTON_ACTION_ATTACK;
		//		}
		//	}
		//	break;
		}
		break;
	case WINDOW_DOT_DIAGNOSTIC:
		switch (last_clicked_button->button_group)
		{
		case PANEL_DOT_INVENTORY:
			if (last_clicked_button->button_action == BUTTON_ACTION_INVENTORY_BUTTON)
			{
				if (current_action == BUTTON_ACTION_PLACE_ITEM)
				{
					//current_intelligence->Dot_Give_Inventory_To_Another_Dot(current_intelligence->player_dot, currently_selected_dot, current_selected_inventory_item, 1);
				}
				//else current_intelligence->Dot_Give_Inventory_To_Another_Dot(currently_selected_dot, current_intelligence->player_dot, last_clicked_button->slot_item_pointer->inventory_item_code, 1);
			}
			break;
		case PANEL_CRAFTABLE_ITEMS:
			if (last_clicked_button->button_action == BUTTON_ACTION_CRAFT_ITEM)
			{
				current_selected_inventory_item = last_clicked_button->slot_item_pointer->inventory_item_code;
				current_action = BUTTON_ACTION_PLACE_SCAFFOLD;
			}
			break;
		case PANEL_DOT_DIAGNOSTIC:
			break;
		case PANEL_PRODUCTION_ORDERS:
			if (last_clicked_button->button_action == BUTTON_ACTION_CREATE_PRODUCTION_ORDER)
			{
				if (console_windows[last_clicked_window].focus_dot->npc_dot_config.production_status_array[last_clicked_button->button_config_num].slot_tile_name != TILE_GENERIC_TILE)
				{
					console_windows[last_clicked_window].focus_dot->npc_dot_config.production_status_array[last_clicked_button->button_config_num].slot_requests++;
				}
			}
			break;
		case PANEL_JOB_DIAGNOSTIC:
			if (last_clicked_button->button_action == BUTTON_ACTION_CLEAR_DOT_GOALS)
			{
				console_windows[last_clicked_window].focus_dot->dot_wipe_all_job_tasks();
			}
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

void Console::Change_Current_Focus_Dot(SDL_Renderer* gRenderer, Dot* new_focus_dot)
{
	if (new_focus_dot->multi_tile_config.tile_type != VACUUM)
	{
		currently_selected_dot = new_focus_dot;
		console_windows[WINDOW_DOT_DIAGNOSTIC].console_window_active = true;
		console_windows[WINDOW_DOT_DIAGNOSTIC].Create_Dot_Diagnostic_Window(new_focus_dot);
	}
}

void Console::Update_Console(SDL_Renderer* gRenderer)
{
	current_intelligence->player_dot->Check_Craftable_Items();
	console_windows[WINDOW_PLAYER_DIAGNOSTIC].Update_Dot_Crafting_Window(inventory_spritesheet,console_font,gRenderer,current_intelligence->player_dot, PANEL_CRAFTABLE_ITEMS, 0, 0, 6, 8, "Craft");
}

#endif