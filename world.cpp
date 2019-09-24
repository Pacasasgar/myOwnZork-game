#include <iostream>
#include "globals.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

// ----------------------------------------------------
World::World()
{
	tick_timer = clock();

	// Rooms ----
	Room* forest = new Room("Forest", "You are surrounded by tall trees. It feels like a huge forest someone could get lost easily.");
	Room* house = new Room("House", "You are inside a beautiful but small white house.");
	Room* basement = new Room("Basement", "The basement features old furniture and dim light.");
	
	Room* road = new Room("Old Road", "This is the Old Road");
	Room* graveyard = new Room("Graveyard", "This is the Graveyard");
	Room* blackForest = new Room("Black Forest", "This is the Black Forest");
	Room* manor = new Room("Haunted Manor", "This is the Haunted Manor");
	Room* crypt = new Room("Crypt", "This is the Crypt");
	Room* vault = new Room("Vault", "This is the Vault");

	//Exits
	/*Exit* ex1 = new Exit("west", "east", "Little path", house, forest);
	Exit* ex2 = new Exit("down", "up", "Stairs", house, basement);
	ex2->locked = true;*/

	/*entities.push_back(forest);
	entities.push_back(house);
	entities.push_back(basement);

	entities.push_back(ex1);
	entities.push_back(ex2);*/

	Exit* exit1 = new Exit("south", "north", "Graveyard Path", graveyard, road);
	Exit* exit2 = new Exit("west", "east", "Forest Path", blackForest, graveyard);
	Exit* exit3 = new Exit("south", "north", "Manor Path", manor, graveyard);
	Exit* exit4 = new Exit("east", "west", "Crypt Path", crypt, graveyard);
	Exit* exit5 = new Exit("up", "down", "Trapdoor", vault, crypt);
	exit5->locked = true;

	entities.push_back(road);
	entities.push_back(graveyard);
	entities.push_back(blackForest);
	entities.push_back(manor);
	entities.push_back(crypt);
	entities.push_back(vault);

	entities.push_back(exit1);
	entities.push_back(exit2);
	entities.push_back(exit3);
	entities.push_back(exit4);
	entities.push_back(exit5);

	// Creatures ----
	Creature* butler = new Creature("Butler", "It's James, the house Butler.", house);
	butler->hit_points = 10;

	Creature* zombie = new Creature("Zombie", "It's a pestilent zombie", graveyard);
	zombie->hit_points = 10;
	Creature* wolf = new Creature("Wolf", "It's a fierce wolf", blackForest);
	wolf->hit_points = 10;
	Creature* skeleton = new Creature("Skeleton", "It's an old live skeleton!", manor);
	skeleton->hit_points = 10;
	Creature* necromancer = new Creature("Necromancer", "It's an evil human being", vault);
	necromancer->hit_points = 10;

	//entities.push_back(butler);
	entities.push_back(zombie);
	entities.push_back(wolf);
	entities.push_back(skeleton);
	entities.push_back(necromancer);

	// Items -----
	Item* mailbox = new Item("Mailbox", "Looks like it might contain something.", house);
	Item* key = new Item("Key", "Old iron key.", mailbox);
	//ex2->key = key;

	Item* sword = new Item("Sword", "A simple old and rusty sword.", forest, WEAPON);
	sword->min_value = 2;
	sword->max_value = 6;

	Item* sword2(sword);
	sword2->parent = butler;

	Item* shield = new Item("Shield", "An old wooden shield.", butler, ARMOUR);
	shield->min_value = 1;
	shield->max_value = 3;
	butler->AutoEquip();

	entities.push_back(mailbox);
	entities.push_back(sword);
	entities.push_back(shield);

	// Player ----
	//player = new Player("Hero", "You are an awesome adventurer!", forest);
	player = new Player("Bounty Hunter", "You are an awesome adventurer!", road);
	player->hit_points = 25;
	entities.push_back(player);
}

// ----------------------------------------------------
World::~World()
{
	for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		delete *it;

	entities.clear();
}

// ----------------------------------------------------
bool World::Tick(vector<string>& args)
{
	bool ret = true;

	if(args.size() > 0 && args[0].length() > 0)
		ret = ParseCommand(args);

	GameLoop();

	return ret;
}

// ----------------------------------------------------
void World::GameLoop()
{
	clock_t now = clock();

	if((now - tick_timer) / CLOCKS_PER_SEC > TICK_FREQUENCY)
	{
		for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
			(*it)->Tick();

		tick_timer = now;
	}
}

// ----------------------------------------------------
bool World::ParseCommand(vector<string>& args)
{
	bool ret = true;

	switch(args.size())
	{
		case 1: // commands with no arguments ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "north") || Same(args[0], "n"))
			{
				(args.size() == 1) ? args.push_back("north") : args[1] = "north";
				player->Go(args);
			}
			else if(Same(args[0], "south") || Same(args[0], "s"))
			{
				(args.size() == 1) ? args.push_back("south") : args[1] = "south";
				player->Go(args);
			}
			else if(Same(args[0], "east") || Same(args[0], "e"))
			{
				(args.size() == 1) ? args.push_back("east") : args[1] = "east";
				player->Go(args);
			}
			else if(Same(args[0], "west") || Same(args[0], "w"))
			{
				(args.size() == 1) ? args.push_back("west") : args[1] = "west";
				player->Go(args);
			}
			else if(Same(args[0], "up") || Same(args[0], "u"))
			{
				(args.size() == 1) ? args.push_back("up") : args[1] = "up";
				player->Go(args);
			}
			else if(Same(args[0], "down") || Same(args[0], "d"))
			{
				(args.size() == 1) ? args.push_back("down") : args[1] = "down";
				player->Go(args);
			}
			else if(Same(args[0], "stats") || Same(args[0], "st"))
			{
				player->Stats();
			}
			else if(Same(args[0], "inventory") || Same(args[0], "i"))
			{
				player->Inventory();
			}
			else
				ret = false;
			break;
		}
		case 2: // commands with one argument ------------------------------
		{
			if(Same(args[0], "look") || Same(args[0], "l"))
			{
				player->Look(args);
			}
			else if(Same(args[0], "go"))
			{
				player->Go(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else if(Same(args[0], "equip") || Same(args[0], "eq"))
			{
				player->Equip(args);
			}
			else if(Same(args[0], "unequip") || Same(args[0], "uneq"))
			{
				player->UnEquip(args);
			}
			else if(Same(args[0], "examine") || Same(args[0], "ex"))
			{
				player->Examine(args);
			}
			else if(Same(args[0], "attack") || Same(args[0], "at"))
			{
				player->Attack(args);
			}
			else if(Same(args[0], "loot") || Same(args[0], "lt"))
			{
				player->Loot(args);
			}
			else
				ret = false;
			break;
		}
		case 3: // commands with two arguments ------------------------------
		{
			ret = false;
			break;
		}
		case 4: // commands with three arguments ------------------------------
		{
			if(Same(args[0], "unlock") || Same(args[0], "unlk"))
			{
				player->UnLock(args);
			}
			else if(Same(args[0], "lock") || Same(args[0], "lk"))
			{
				player->Lock(args);
			}
			else if(Same(args[0], "take") || Same(args[0], "pick"))
			{
				player->Take(args);
			}
			else if(Same(args[0], "drop") || Same(args[0], "put"))
			{
				player->Drop(args);
			}
			else
				ret = false;
			break;
		}
		default:
		ret =  false;
	}

	return ret;
}