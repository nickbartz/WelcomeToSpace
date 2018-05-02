#pragma once

// BIG THINGS THAT RUN EVERY CYCLE

// 1. rendering world tiles -- PARTLY SOLVED
// 2. checking for the number of scaffolds;
// 3. Assigning items jobs - PARTLY SOLVED BY RETURNING TO LOOP OVER ARRAY, BUT NEED TO CHANGE ARRAY TO VECTOR ULTIMATELY
// 4. checking for the number of items 


// THINGS THAT COULD POTENTIALY CAUSE PROBLEMS LATER ON DOWN THE LINE
// 1. Finite Dot Inventory
// 2. Using tile_list for construction parts as well as project parts 

// UNSOLVED BUGS 

// You can place the bed so that part of it goes into a wall and this causes the game to freeze. 
// Dot did not stop looking for scaffolds when all scaffolds were built. 

// Probably a lot of these problems are stemming from the fact that things are deleted after their pointer has been assigned to something else 

// NOTES

// TO-DO

// NEW FUNCTIONALITY
// 2. Dot Arrival In Spaceship
// 3. PARTLY DONE - Need the functionality for a dot to physically interact with an item
// 4. Roof tiles
// 5. Different colored dot's automagically
// 6. Dot's can fire weapons
// 7. Exterior guns
// 8. Floaty space movement

// AI
// 1. Intelligence needs to send out Asteroid Mining jobs according to whether there's a need for a certain type of ore
// 3. Dots need to be assigned a bed and cannot sleep in a bed that is owned
// 4. PARTLY COMPLETED - items or scaffolds that use other items need to delete them when they're used
// 5. Dot's need some way to distinguish between health priorities when they clash

// NEW ASSETS
// 1. Spaceport
// 3. Glass Roof 
// 4. Diagonal walking
// 5. Guns
// 6. Exterior guns

// INTERFACE 
// 1. Need to be able to delete things without deleting everything on that tile
// 5. Separate out crafting items by category
