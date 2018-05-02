#pragma once

typedef int32_t s32;

void DrawCircle(SDL_Renderer* gRenderer, s32 _x, s32 _y, s32 radius)
{
	s32 x = radius - 1;
	s32 y = 0;
	s32 tx = 1;
	s32 ty = 1;
	s32 err = tx - (radius << 1); // shifting bits left by 1 effectively
								  // doubles the value. == tx - diameter
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(gRenderer, _x + x, _y - y);
		SDL_RenderDrawPoint(gRenderer, _x + x, _y + y);
		SDL_RenderDrawPoint(gRenderer, _x - x, _y - y);
		SDL_RenderDrawPoint(gRenderer, _x - x, _y + y);
		SDL_RenderDrawPoint(gRenderer, _x + y, _y - x);
		SDL_RenderDrawPoint(gRenderer, _x + y, _y + x);
		SDL_RenderDrawPoint(gRenderer, _x - y, _y - x);
		SDL_RenderDrawPoint(gRenderer, _x - y, _y + x);

		//SDL_RenderDrawLine(gRenderer, _x - x, _y - y, _x + x, _y - y);
		//SDL_RenderDrawLine(gRenderer, _x - y, _y + x, _x + y, _y + x);
		//SDL_RenderDrawLine(gRenderer, _x - y, _y - x, _x + y, _y - x);
		//SDL_RenderDrawLine(gRenderer, _x - x, _y + y, _x + x, _y + y);

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		else if (err > 0)
		{
			x--;
			tx += 2;
			err += tx - (radius << 1);
		}
	}
}

void Draw_Laser(SDL_Renderer* gRenderer, Camera* camera, SDL_Rect* firing_dot, SDL_Rect* target_dot, SDL_Color laser_color)
{
	SDL_Rect* firing_rect = firing_dot;
	SDL_Rect* target_rect = target_dot;

	int x_1 = firing_rect->x + firing_rect->w / 2;
	int y_1 = firing_rect->y + firing_rect->h / 2;
	int x_2 = target_rect->x + target_rect->w / 2;
	int y_2 = target_rect->y + target_rect->h / 2;

	SDL_SetRenderDrawColor(gRenderer, laser_color.r, laser_color.g, laser_color.b, laser_color.a);
	SDL_RenderDrawLine(gRenderer, x_1 - camera->camera_box.x, y_1 - camera->camera_box.y, x_2 - camera->camera_box.x, y_2 - camera->camera_box.y);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

}