#pragma once

class Dot_Job
{
public:
	Dot_Job(
		int type = DOT_JOB_NO_ASSIGNED_JOB, 
		float priority = 1.0, 
		Dot* secondary_dot = NULL, 
		Dot* tertiary_dot = NULL, 
		Multi_Tile_Type primary_item = null_tile, 
		int primary_quantity = 0,
		int secondary_quantity = 0,
		int* primary_quantity_pointer = NULL);

	int job_type;
	float job_priority;
	vector<Dot*> currently_assigned_dots;

	Dot* second_dot;
	Dot* third_dot;
	Multi_Tile_Type first_item;
	int first_quantity;
	int second_quantity;
	int* first_quantity_pointer;

	void Push_Alert(Dot* dot, string alert_text);
	void Run_Job(Dot* dot);

	// DOT ROUTINES
	void Routine_Move_Container_To_Storage(Dot* dot, Dot* container, Dot* storage_tile);
	void Routine_Put_Container_Items_In_Inventory(Dot* dot, Dot* container);
	void Routine_Take_Items_To_Dot(Dot* dot, Dot* project_dot, Dot* dot_with_item, Multi_Tile_Type item_to_grab, int quantity);
	void Routine_Run_Project(Dot* dot, Dot* project_dot, int* dot_quantity_pointer, int increment, int finished_quantity, bool get_inside_project);
	void Routine_Take_Items_From_Dot(Dot* dot, Dot* dot_to_take_items_from, Multi_Tile_Type item_to_grab, int quantity_to_grab);

	// ITEM ROUTINES
	void Routine_Oxygenate(Dot* dot);
	void Routine_Tile_Streamline(Dot* dot);
	void Routine_Tile_Door(Dot* dot);
	void Routine_Grow_Frenzel(Dot* dot);
	void Routine_Create_Soylent(Dot* dot);
	void Routine_Create_Soylent_Meal(Dot* dot);

	void Subroutine_Manage_Item_Production(Dot* dot, Multi_Tile_Type tile_type);
	
	bool debug = true;
};

Dot_Job::Dot_Job(int type, float priority, Dot* secondary_dot, Dot* tertiary_dot, Multi_Tile_Type primary_item, int primary_quantity, int secondary_quantity, int* primary_quanty_pointer)
{
	job_type = type;
	job_priority = priority;

	second_dot = secondary_dot;
	third_dot = tertiary_dot;
	first_item = primary_item;
	first_quantity = primary_quantity;
	second_quantity = secondary_quantity;
	first_quantity_pointer = primary_quanty_pointer;
}

void Dot_Job::Push_Alert(Dot* dot, string alert_text)
{
	dot->dot_alerts.push_back({ alert_text,0 });
} 

void Dot_Job::Run_Job(Dot* dot)
{
	switch (job_type)
	{
	case DOT_JOB_NO_ASSIGNED_JOB:
		break;
	case DOT_HEALTH_JOB_GO_FIND_OXYGENATED_TILE:
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ON_SPECIFIC_DOT,0,0,0,0,null_tile,1,false,second_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT, 0,0,0,0,null_tile,1,false,second_dot });
		break;
	case DOT_HEALTH_JOB_GO_GET_SPACESUIT:
		Routine_Take_Items_From_Dot(dot, second_dot, first_item, first_quantity);
		break;
	case DOT_HEALTH_JOB_GO_TO_BED:
		Routine_Run_Project(dot, second_dot, first_quantity_pointer, first_quantity, second_quantity, true);
		break;
	case DOT_HEALTH_JOB_GO_FIND_FOOD:
		Routine_Take_Items_From_Dot(dot, second_dot, first_item, first_quantity	);
		break;
	case DOT_HEALTH_JOB_GO_EAT_FOOD:
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_REMOVE_ITEM_FROM_DOT_INVENTORY, 0,0,0,0,first_item,1,false,dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_NOT_CARRY_ITEM, 0,0,0,0,first_item,0,false,third_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_GET_OUT_OF_ANOTHER_DOT,0,0,0,0,null_tile,0,false,second_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHANGE_DOT_QUANTITY,0,0,0,0,null_tile,first_quantity,false,second_dot, first_quantity_pointer, second_quantity });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_CARRY_ITEM, 0,0,0,0,first_item,0,false,third_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_NOT_CARRY_ITEM, 0,0,0,0,first_item,0,false,dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_GET_INSIDE_ANOTHER_DOT,0,0,0,0,null_tile,0,false,second_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,0,0,0,0,null_tile,1,false,second_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,0,0,0,0,null_tile,0,false,second_dot });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_CARRY_ITEM, 0,0,0,0,first_item,0,false,dot });
		break;
	case SPECIFIC_DOT_JOB_STORE_CONTAINER:
		Routine_Move_Container_To_Storage(dot, second_dot, third_dot);
		break;
	case SPECIFIC_DOT_JOB_SHUTTLE_ITEM_TO_PROJECT:
		Routine_Take_Items_To_Dot(dot, second_dot, third_dot, first_item, first_quantity);
		break;
	case SPECIFIC_DOT_JOB_BUILD_SCAFFOLD:
		Routine_Run_Project(dot, second_dot, first_quantity_pointer, first_quantity, second_quantity, false);
		break;
	case SPECIFIC_DOT_JOB_COMPILE_PROJECT:
		Routine_Run_Project(dot, second_dot, first_quantity_pointer, first_quantity, second_quantity, false);
		break;
	case SPECIFIC_DOT_JOB_HARVEST_FRENZEL:
		Routine_Run_Project(dot, second_dot, first_quantity_pointer, first_quantity, second_quantity, false);
		break;
	case SPECIFIC_DOT_JOB_TAKE_ITEM_FROM_DOT:
		Routine_Take_Items_From_Dot(dot, second_dot, first_item, first_quantity);
		break;
	case ITEM_JOB_OXYGENATE:
		Routine_Oxygenate(dot);
		break;
	case ITEM_JOB_DOOR:
		Routine_Tile_Door(dot);
		break;
	case ITEM_JOB_GROW_FRENZEL:
		Routine_Grow_Frenzel(dot);
		break;
	case ITEM_JOB_CREATE_SOYLENT:
		Routine_Create_Soylent(dot);
		break;
	case ITEM_JOB_CREATE_SOYLENT_MEAL:
		Routine_Create_Soylent_Meal(dot);
		break;
	}
}


// RESOURCE SHUTTLING ROUTINES

void Dot_Job::Routine_Move_Container_To_Storage(Dot* dot, Dot* container, Dot* storage_tile)
{	
	vector<Dot_Inventory_Slot> container_inventory = container->return_inventory_as_vector();

	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_NOT_CARRY_ITEM, 0,0,0,0,Return_Tile_By_Inventory_Item(container_inventory.back().item_type),0,false,storage_tile });
	for (int i = 0; i < container_inventory.size(); i++)
	{
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_GIVE_INVENTORY_TO_ANOTHER_DOT, 0,0,0,0,Return_Tile_By_Inventory_Item(container_inventory[i].item_type),container_inventory[i].item_number,false,storage_tile });
	}

	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,0,0,0,0,null_tile,1,false,storage_tile });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,	0,0,0,0,null_tile,0,false,storage_tile });

	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_CARRY_ITEM, 0,0,0,0,Return_Tile_By_Inventory_Item(container_inventory.back().item_type),0,false,container });
	for (int i = 0; i < container_inventory.size(); i++)
	{
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_TAKE_INVENTORY_FROM_ANOTHER_DOT, 0,0,0,0,Return_Tile_By_Inventory_Item(container_inventory[i].item_type),container_inventory[i].item_number,false,container });
	}

	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,0,0,0,0,null_tile,1,false,container });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,	0,0,0,0,null_tile,0,false,container });
}

void Dot_Job::Routine_Put_Container_Items_In_Inventory(Dot* dot, Dot* container)
{
	vector<Dot_Inventory_Slot> container_inventory = container->return_inventory_as_vector();
	
	for (int i = 0; i < container_inventory.size(); i++)
	{
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_TAKE_INVENTORY_FROM_ANOTHER_DOT, 0,0,0,0,Return_Tile_By_Inventory_Item(container_inventory[i].item_type),container_inventory[i].item_number,false,container });
	}
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,0,0,0,0,null_tile,1,false,container });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,	0,0,0,0,null_tile,0,false,container });
}

void Dot_Job::Routine_Take_Items_To_Dot(Dot* dot, Dot* project_dot, Dot* dot_with_item, Multi_Tile_Type item_to_grab, int quantity)
{	
	dot->npc_dot_config.tile_parts_list.erase(dot->npc_dot_config.tile_parts_list.begin(), dot->npc_dot_config.tile_parts_list.begin() + dot->npc_dot_config.tile_parts_list.size());

	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_NOT_CARRY_ITEM,							0,0,0,0,item_to_grab,0,false,project_dot });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_GIVE_INVENTORY_TO_ANOTHER_DOT,						0,0,0,0,item_to_grab,quantity,false,project_dot });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,				0,0,0,0,null_tile,0,true,project_dot });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,							0,0,0,0,null_tile,0,false,project_dot });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_TO_CARRY_ITEM,								0,0,0,0,item_to_grab,0,false,project_dot });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_TAKE_INVENTORY_FROM_ANOTHER_DOT,						0,0,0,0,item_to_grab,quantity,false,dot_with_item });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,				0,0,0,0,null_tile,0,true,dot_with_item });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,							0,0,0,0,null_tile,0,false,dot_with_item });
}

void Dot_Job::Routine_Run_Project(Dot* dot, Dot* project_dot, int* dot_quantity_pointer, int increment, int finished_quantity, bool get_inside_project)
{
	dot->npc_dot_config.current_dot_focus = project_dot;
	if (get_inside_project) dot->npc_dot_config.current_goal_list.push_back({ ACTION_GET_OUT_OF_ANOTHER_DOT,0,0,0,0,null_tile,increment,false,dot->npc_dot_config.current_dot_focus });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHANGE_DOT_QUANTITY,0,0,0,0,null_tile,increment,false,dot->npc_dot_config.current_dot_focus, dot_quantity_pointer, finished_quantity });
	if (get_inside_project) dot->npc_dot_config.current_goal_list.push_back({ ACTION_GET_INSIDE_ANOTHER_DOT,0,0,0,0,null_tile,increment,false,dot->npc_dot_config.current_dot_focus });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,0,0,0,0,null_tile,1,false,dot->npc_dot_config.current_dot_focus });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,0,0,0,0,null_tile,0,false,dot->npc_dot_config.current_dot_focus });
}

void Dot_Job::Routine_Take_Items_From_Dot(Dot* dot, Dot* dot_to_take_items_from, Multi_Tile_Type item_to_grab, int quantity_to_grab)
{
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_TAKE_INVENTORY_FROM_ANOTHER_DOT,						0,0,0,0,item_to_grab,quantity_to_grab,false,dot_to_take_items_from });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_CHECK_IF_DOT_IS_ADJACENT_TO_SPECIFIC_DOT,				0,0,0,0,null_tile,0,true,dot_to_take_items_from });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_SET_DOT_PATH_TO_SPECIFIC_DOT,							0,0,0,0,null_tile,0,true,dot_to_take_items_from });
}


// ITEM ROUTINES

void Dot_Job::Routine_Oxygenate(Dot* dot)
{
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_OXYGENATE_AIR,0,0,0,0,null_tile,0,false,NULL });
}

void Dot_Job::Routine_Tile_Door(Dot* dot)
{
	if (dot->multi_tile_config.door_state == 1)
	{
		dot->multi_tile_config.door_open_length++;
		if (dot->multi_tile_config.door_open_length > DOOR_OPEN_PAUSE)
		{
			dot->multi_tile_config.door_state = 2;
			dot->multi_tile_config.door_open_length = 0;
		}
	}
}

void Dot_Job::Routine_Grow_Frenzel(Dot* dot)
{
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_GROW_FRENZEL,0,0,0,0,null_tile,0,false,NULL });
	dot->npc_dot_config.current_goal_list.push_back({ ACTION_TILE_STREAMLINE,0,0,0,0,null_tile,0,false,NULL });
	if (dot->Check_Inventory_For_Item(Inventory_Frenzel_1) <= 0)
	{
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_ADD_ITEM_TO_DOT_INVENTORY,0,0,0,0,Return_Tile_By_Inventory_Item(Inventory_Frenzel_1),1,false,dot });
	}
}

void Dot_Job::Routine_Create_Soylent(Dot* dot)
{
	if (dot->multi_tile_config.built_percent >= 100)
	{
		if (dot->npc_dot_config.dot_produced_item.tile_name == TILE_NULL)
		{
			dot->npc_dot_config.dot_produced_item = Return_Tile_By_Name(TILE_SOYLENT_1);
			dot->Return_Parts_List(dot->npc_dot_config.dot_produced_item);
		}
		Subroutine_Manage_Item_Production(dot, dot->npc_dot_config.dot_produced_item);
	}
}

void Dot_Job::Routine_Create_Soylent_Meal(Dot* dot)
{
	if (dot->multi_tile_config.built_percent >= 100)
	{
		if (dot->npc_dot_config.dot_produced_item.tile_name == TILE_NULL)
		{
			dot->npc_dot_config.dot_produced_item = Return_Tile_By_Name(TILE_SOYLENT_MEAL_1);
			dot->Return_Parts_List(dot->npc_dot_config.dot_produced_item);
		}
		Subroutine_Manage_Item_Production(dot, dot->npc_dot_config.dot_produced_item);
	}
}

void Dot_Job::Subroutine_Manage_Item_Production(Dot* dot, Multi_Tile_Type tile_type)
{
	dot->Check_if_Dot_Can_Pop_Tile_List_Items();
	if (dot->npc_dot_config.production_current >= tile_type.built_percent)
	{
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_DROP_ALL_INVENTORY_ITEM_OF_TYPE,0,0,0,0,tile_type,0,false,NULL });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_REMOVE_BUILDING_ITEMS_FROM_DOT_INVENTORY,0,0,0,0,tile_type,1,false,NULL });
		dot->npc_dot_config.current_goal_list.push_back({ ACTION_ADD_ITEM_TO_DOT_INVENTORY,0,0,0,0,tile_type,1,false,dot });
		dot->npc_dot_config.production_current = 0;
		dot->Return_Parts_List(tile_type);
	}
}
