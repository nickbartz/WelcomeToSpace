#pragma once

class Save_File 
{
public:
	Save_File();
	Tile_Init saved_world_tiles[TILE_NUM_X][TILE_NUM_Y];


	void Save_Current_State(World* save_world, Intelligence* intelligence);
	void Load_Current_State(World* save_world, Intelligence* intelligence);
	void Save_World_Tiles(World* save_world);
	void Load_World_Tiles(World* save_world);

private:
};

Save_File::Save_File()
{

}

void Save_File::Save_Current_State(World* save_world, Intelligence* intelligence)
{
	cout << "world tiles" << endl;
	Save_World_Tiles(save_world);

}

void Save_File::Load_Current_State(World* save_world, Intelligence* intelligence)
{
	Load_World_Tiles(save_world);

}

void Save_File::Save_World_Tiles(World* save_world)
{
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			saved_world_tiles[i][p] = save_world->Save_Tile(i, p);
		}
	}
}

void Save_File::Load_World_Tiles(World* save_world)
{
	for (int p = 0; p < TILE_NUM_Y; p++)
	{
		for (int i = 0; i < TILE_NUM_X; i++)
		{
			
			save_world->Load_Tile(saved_world_tiles[i][p]);
		}
	}
}

