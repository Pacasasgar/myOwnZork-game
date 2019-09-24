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
	Room* road = new Room("Old Road", "This is the Old Road");
	Room* graveyard = new Room("Graveyard", "This is the Graveyard");
	Room* blackForest = new Room("Black Forest", "This is the Black Forest");
	Room* manor = new Room("Haunted Manor", "This is the Haunted Manor");
	Room* crypt = new Room("Crypt", "This is the Crypt");
	Room* vault = new Room("Vault", "This is the Vault");

	//Exits
	Exit* exit1 = new Exit("south", "north", "Graveyard Path", graveyard, road);
	Exit* exit2 = new Exit("west", "east", "Forest Path", blackForest, graveyard);
	Exit* exit3 = new Exit("south", "north", "Manor Path", manor, graveyard);
	exit3->locked = true;
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
	Creature* zombie = new Creature("Zombie", "It's a pestilent zombie.", graveyard);
	zombie->hit_points = 6;
	zombie->min_damage = 1;
	zombie->max_damage = 2;
	zombie->max_protection = 1;
	Creature* wolf = new Creature("Wolf", "It's a fierce wolf", blackForest);
	wolf->hit_points = 10;
	wolf->min_damage = 2;
	wolf->max_damage = 3;
	wolf->min_protection = 1;
	wolf->max_protection = 2;
	Creature* skeleton = new Creature("Skeleton", "It's an old live skeleton!", manor);
	skeleton->hit_points = 20;
	skeleton->min_damage = 1;
	skeleton->max_damage = 5;
	Creature* necromancer = new Creature("Necromancer", "It's an evil human being.", vault);
	necromancer->hit_points = 45;
	necromancer->min_damage = 45;
	necromancer->max_damage = 50;
	necromancer->min_protection = 1;
	necromancer->max_protection = 2;

	entities.push_back(zombie);
	entities.push_back(wolf);
	entities.push_back(skeleton);
	entities.push_back(necromancer);

	// Items -----
	Item* shortSword = new Item("Shortsword", "An old short sword, it looks a little weak to defeat evil humans...", road, WEAPON);
	shortSword->min_value = 1;
	shortSword->max_value = 3;
	Item* broadSword = new Item("Broadsword", "A big broadsword! It looks heavy but painful...", manor, WEAPON);
	broadSword->min_value = 4;
	broadSword->max_value = 6;
	Item* shield = new Item("Shield", "A broken wooden shield. Soon it will be two halves of it...", skeleton, ARMOUR);
	shield->min_value = 0;
	shield->max_value = 2;
	skeleton->AutoEquip();
	Item* leatherArmour = new Item("Armour", "A leather armour. Your skill as a leatherworker pays off, you created this using just a wolf's leather...", wolf, ARMOUR);
	leatherArmour->min_value = 1;
	leatherArmour->max_value = 4;
	Item* locket = new Item("Locket", "This ornament seems bigger than other lockets. It looks like it could be opened...", crypt);
	Item* note = new Item("Note", "It says:\n'Remember that the Manor's key is inside the locket. Regards, Vladimir'", zombie);
	Item* key1 = new Item("Vault-Key", "Vault's key. This key seems to be existing for more than a thousand years...", skeleton);
	exit5->key = key1;
	Item* key2 = new Item("Manor-Key", "Manor's key. Surprisingly, this key is very small and square.", locket);
	exit3->key = key2;

	entities.push_back(shortSword);
	entities.push_back(broadSword);
	entities.push_back(shield);
	entities.push_back(leatherArmour);
	entities.push_back(locket);
	entities.push_back(note);
	entities.push_back(key1);
	entities.push_back(key2);

	// Player ----
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