#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "globals.h"
#include "world.h"

using namespace std;

#define BACKSPACE "\033[D\033[K"

#define WHITE_ "\033[1;36m"
#define _WHITE "\033[0m"

// -------------------------------------------------
int main()
{
	char key;
	string player_input;
	vector<string> args;
	args.reserve(10);

	cout << WHITE_ "Welcome to MyOwnZork!\n" _WHITE;
	cout << "In this text mode conversational adventure you will incarnate a bounty hunter in his battles in a medieval fantasy world. You could find a guide on how to play and how to beat the game in the 'README' file of the repository at 'https://github.com/Pacasasgar/myOwnZork-game'. Have fun!\n";
	cout << "---------------------\n";
	cout << "\nAn evil Necromancer ravages these lands. There are rumors among the villagers... Undeads walking around Vladimir's Manor. Some ensure the Manor is haunted, others that Vladimir's corpse is alive again and walking around without flesh... This evil Necromancer is practicing dark arts and has to be stopped. It is your job as a renowned Bounty Hunter to claim your trophy by hunting him down. You need to be the villager's hero that they deserve... As you approach your destination, you feel a terrible magic in the air... You are close.";

	World my_world;

	args.push_back("look");

	while(1)
	{
		if(_kbhit() != 0)
		{
			key = _getch();
			if(key == '\b') // backspace
			{
				if(player_input.length() > 0)
				{
					player_input.pop_back();
					//cout << BACKSPACE;
					cout << '\b';
					cout << " ";
					cout << '\b';
				}
			}
			else if(key != '\r') // return
			{
				player_input += key;
				cout << key;
			}
			else
				Tokenize(player_input, args);
		}

		if(args.size() > 0 && (Same(args[0], "quit") || Same(args[0], "q")))
			break;

		if(my_world.Tick(args) == false)
			cout << "\nSorry, I do not understand your command.\n";

		if(args.size() > 0)
		{
			args.clear();
			player_input = "";
			cout << "> ";
		}
	}

	cout << "\n\n---------------------\n";
	cout << WHITE_ "Thanks for playing, see you soon!\n" _WHITE;
	return 0;
}