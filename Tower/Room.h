#ifndef ROOM_H
#define ROOM_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include <Tile.h>
#include <Config.h>
#include <LTexture.h>
#include <Camera.h>

#include <iostream>
using namespace std;

class Room {
public:

	Room(SDL_Renderer* gRenderer, Tile* scene_tiles[], LTexture* tile_texture, int room_w, int room_h, int tile_offset_x, int tile_offset_y);

	void free();

	Tile* get_tile(int tile_num);

	int get_room_tile_count();

private:
	// Room size and shape
	int room_width = 0;
	int room_height = 0;
	int room_tile_count = 0;

	int tile_offset_x;
	int tile_offset_y;

	Tile* room_tiles[MAX_TILES_PER_ROOM];

};

Room::Room(SDL_Renderer* gRenderer, Tile* scene_tiles[], LTexture* tile_texture, int room_w, int room_h, int tile_offset_x, int tile_offset_y) 
{
	// create the tiles
	room_width = room_w;
	room_height = room_h;
	room_tile_count = room_width * room_height;

	int tile_count = 0;

	for (int p = 0; p < room_height; ++p)
	{
		for (int i = 0; i < room_width; ++i)
		{
			int x_offset = TILE_WIDTH * i;
			int y_offset = TILE_HEIGHT * p;

			Tile room_tile(gRenderer, tile_texture, tile_offset_x + x_offset, tile_offset_y + y_offset);

			room_tiles[tile_count] = &room_tile;
			//scene_tiles[*current_scene_tile_count] = &room_tile;

			tile_count++;
			//*current_scene_tile_count++;

			if (tile_count > room_tile_count)
			{
				tile_count = 0;
			}
		}
	}
}

Tile* Room::get_tile(int tile_num)
{
	return room_tiles[tile_num];
}

int Room::get_room_tile_count()
{
	return room_tile_count;
}

void Room::free()
{
	for (int i = 0; i < room_tile_count; ++i)
	{
		room_tiles[i]->free();
	}
}

#endif