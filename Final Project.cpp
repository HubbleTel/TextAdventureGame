
#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <Windows.h>
#include "location.h"
#include "world.h"
#include "utils.h"
#include "player.h"

using namespace std;

world* myWorld = new world();

location* current = myWorld->getCurrentLocation();

player* me = new player(current);

/*This function will parse the input given by the user
and determine the next action in the game.*/
void parser()
{
	bool done = false;
	bool result = false;

	while (!done)
	{
		std::string line;
		std::cout << "Type the action that you want to take (\"quit\" to exit): ";
		std::getline(std::cin, line);
		line = trim(line);

		if (line.empty())
		{
			continue;
		}

		// This is from https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
		std::istringstream iss(line);
		std::vector<std::string> tokens;
		std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		back_inserter(tokens));

		if (upper(tokens[0]) == upper("quit"))
		{
			done = true;
			break;
		}
		else if ((upper(tokens[0]) == upper("go")) || (upper(tokens[0]) == upper("move"))) 
		{

			if (tokens.size() == 1) 
			{
				cout << "Invalid command need direction to " << tokens[0] << endl;
				continue;
			}
			else if (tokens.size() > 2) 
			{
				cout << "Invalid command move takes only one direction" << endl;
				continue;
			}

			std::string dir = tokens[1];

			 me->moveLoc(dir);

		}
		else if (upper(tokens[0]) == upper("take")) 
		{
			if (tokens.size() == 1) 
			{
				cout << "Invalid command need object to " << tokens[0] << endl;
				continue;
			}
			else if (tokens.size() > 2) 
			{
				cout << "Invalid command, take takes only one object" << endl;
				continue;
			}
			std::string objectname = upper(tokens[1]);
			me->take(objectname);
		}
		else if (upper(tokens[0]) == upper("use"))
		{
			if ((tokens.size() == 1) || (tokens.size() == 3))
			{
				cout << "Invalid command need object to " << tokens[0] << endl;
				cout << "Valid usage: 'use object' or 'use object1 on object2'.\n";
				continue;
			}
			else if (tokens.size() > 4)
			{
				cout << "Invalid command, use takes only one object" << endl;
				continue;
			}
			else
			{
				std::string objectname  = upper(tokens[1]);
				std::string objectname2;
				if (tokens.size() == 4)
				{
					if(upper(tokens[2]) == "ON")
					{
						objectname2 = upper(tokens[3]);
					}
					else {
						cout << "Unrecognized keyword.\n";
							continue;
					}
				}
				me->use(objectname,objectname2);
			}
		}
		else if (upper(tokens[0]) == upper("look"))
		{
			if (tokens.size() == 1)
			{
				me->look();
			}
			else if (tokens.size() > 2)
			{
				cout << "Invalid command, look cannot take more than one object" << endl;
				continue;
			}
			else
			{
				std::string objectName = upper(tokens[1]);
				me->look(objectName);
			}
		}
		else if (upper(tokens[0]) == upper("drop")) 
		{
			if (tokens.size() == 1) 
			{
				cout << "Invalid command need object to " << tokens[0] << endl;
				continue;
			}
			else if (tokens.size() > 2) 
			{
				cout << "Invalid command, drop takes only one object" << endl;
				continue;
			}
			else
			{
				std::string objectname = upper(tokens[1]);
				item *myItem = myWorld->getItem(objectname);
				if (myItem != NULL)
				{
					me->drop(myItem);
				}
				else
				{
					cout << "Invalid item, cannot be dropped." << endl;
				}
			}
		}
		else if (tokens[0] == "inventory") 
		{
			if (tokens.size() != 1) 
			{
				cout << "Invalid command, inventory has no parameters " << tokens[0] << endl;
				continue;
			}
			me->showInventory();
		}
		else if (tokens[0] == "fight")
		{
			result = me->fight();
		}
		else if (tokens[0] == "help") 
		{
			cout << "MENU OPTIONS: " << endl;
			cout << "Move - Move the player, need to specify direction" << endl;
			cout << "Take - Take an object, need to specify the name of the object to be taken" << endl;
			cout << "Use  - Use object, need to specify name of object to be used" << endl;
			cout << "Drop - Drop an object, need to specify name of object to be used" << endl;
			cout << "Inventory - Shows Inventory" << endl; 
			cout << "Fight - Player fights the enemy" << endl;
		}
		else 
		{
			cout << "You don't understand the command \"" << tokens[0] << "\""<< endl;
		}

		if ((!me->isPlayerAlive())||(result == true))
		{
			cout << "Game over.";
			done = true;
			break;
		}
	}
	
}

/*This function will display the game introduction background.*/
void intro()
{
		Sleep(2000);
		cout << "Welcome to the war, you are chosen to partake in a mission." << endl;
		cout << "\n";
		Sleep(500);
		cout << "This is the year 2250. The galaxy war seems to have caused chaos in the universe" << endl;
		cout << "\n";
		Sleep(500);
		cout << "and the resulting war has caused dark times to the humans that have outlived the nuclear wars," << endl;
		cout << "\n";
		Sleep(500);
		cout << "which has caused damage to our Earth. " << endl;
		cout << "\n";
		Sleep(500);
		cout << "The superpower leaders wanted more power to help survive and have made a deal with the aliens. " << endl;
		cout << "\n";
		Sleep(500);
		cout << "This negotiation lead to the enhancement of technology and started with human gene experimentation" << endl;
		cout << "\n";
		Sleep(500);
		cout << "Experimentation led to human gene splicing with different species to fight in the galaxy wars." << endl;
		cout << "\n";
		Sleep(500);
		cout << "The aliens have full control of Earth including choosing who can keep living." << endl;
		cout << "\n";
		Sleep(500);
		cout << "Cyborgs were used to control the people on earth." << endl;
		cout << "\n";
		Sleep(500);
		cout << "There was a prophecy that someone will be born to save the humans." << endl;
		cout << "\n";
		Sleep(500);
		cout << "There is no privacy to humans and they are always monitored and through their control devices" << endl;
		cout << "\n";
		Sleep(500);
		cout << "Human children are used as soldiers in the galaxy wars.The new world consist of learning alien language and education." << endl;
		Sleep(500);
		cout << "\n";
		cout << "\n";
		Sleep(500);
		cout << "You are at home, in a farmhouse in the future, there is a computer in front of you with a usb device in it. You are currently working on finding ways to get rid of the aliens." << endl;
		cout << "\n";
		Sleep(500);
		cout << "The aliens have heard you and have arrived outside your house, there is a window to escape, be sure to take the usb as well" << endl;
		cout << "\n";
		Sleep(1000);
		return;
	}

void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	return;
}

/*This function will delete the global variables in the game.*/
void delGlobals()
{
	delete current;
	

	delete myWorld;
	

	delete me;	

}


int main()
{
	setTextColor(5);
	cout << R"(                         
					 _______ _______ _______ 
					|\     /|\     /|\     /|
					| +---+ | +---+ | +---+ |
					| |   | | |   | | |   | |
					| |T  | | |L  | | |C  | |
					| +---+ | +---+ | +---+ |
					|/_____\|/_____\|/_____\|
                         

)"<<"\n";	


	intro();
	setTextColor(1);
	parser();
	delGlobals();
}
