#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "player.h"
#include "utils.h"


extern world* myWorld;

using namespace std;

/*This player.cpp file contains the implementation of the player class declared in player.h
*/

/*The Implementation of the player constructor
This is the default player class.
*/
player::player()
{
}

player::player(string playerName)
{
	name = playerName;
	healthPoints = 200;
	life = true;
 
}

/*Implementation of the constructor of the player class.
*/
player::player(location* playerLocation)
{
	name = "john doe";
	loc = playerLocation;
	healthPoints = 100;
	life = true;
	useObject  = false;
	moveLadder = false;
	useComputer = false;
	checkDocuments = false;
	puzzle  = true;
}

/*Implementation of the getName function.
Returns the name of the player.
*/
string player::getName()
{
	return name;
}

/*Implementation of the default destructor of the player class*/
player::~player() {

}

/*Implementation of the look function of the player class.
This function will take a parameter containing the object name
and if the object is present in the player's inventory or the
player's current location, display a detailed description of the object.*/
void player::look(const string objectName)
{
	bool inInventory = false;
	item* myItem = NULL;
	loc->showPlayer();
	list<item*>::iterator theiter;
	for (theiter = inventory.begin(); theiter != inventory.end(); theiter++) {
		if (objectName == (*theiter)->getName())
		{
			cout << (*theiter)->getDeets();
			inInventory = true;
		}
	}

	if (inInventory == false)
	{
		myItem = loc->getObject(objectName);
	   	if (myItem == NULL)
		{
			cout << "Item not in Inventory or Location." << endl;
		}
		else
		{
			cout << myItem->getDeets();
		}
	}
	
}

/*Implementation of the take object of the player class.
Pass a parameter containing the name of the object the player should take.
The function will take the object if it is present in the current location.*/
void player::take(const string object) {

	if (object == "USB")
	{
		if (!useComputer) {
			cout << "Empty USB, copy documents from the Computer.\n";
			return;
		}
	}
	if (object == "DOCUMENTS")
	{
		if (!checkDocuments) {
			cout << "Got the documents.\n";
			checkDocuments = true;
			return;
		}
	}
	item* myItem = loc->getObject(object);
	if (myItem != NULL) {
		inventory.push_back(myItem);
		loc->removeObject(myItem);
		cout << "Took the " << object << endl;
	}
	else {
		cout << "Cannot take " << object << endl;
	}
}

/*Implementation of the drop function of the player class.
Pass a parameter containing the item to be dropped, the function 
will drop the item from the inventory if present.*/
void player::drop(item *myItem) {
	if (inventory.empty()) {
		cout << "Nothing to drop inventory is empty. " << endl;
	}
	else if (checkInventory(myItem->getName())) {
		loc->addObject(myItem);
		inventory.remove(myItem);
		cout << "dropped " << myItem->getName() << endl;
	}
	else  {
		cout << "object cannot be dropped." << endl;
	}
}

/*Implementation of the showInventory function of the player class.
This functin will display all the objects in the player's inventory.*/
void player::showInventory()
{
	list<item*>::iterator theiter;
	if (inventory.empty()) {
		cout << "Your inventory is empty, start hoarding" << endl;
	}
	else {
		cout << "You have the below items: " << endl;
		for (theiter = inventory.begin(); theiter != inventory.end(); theiter++) {
			string itemname = (*theiter)->getName();
			cout << itemname << endl;
		}
	}
}

/*Implementation of the checkInventory function of the player class.
This function will take an input objectName which contains the name of the 
object and will check if the object is present in the player's inventory.*/
bool player::checkInventory(string objectName)
{
	list<item*>::iterator theiter;
	for (theiter = inventory.begin(); theiter != inventory.end(); theiter++)
	{
		if ((*theiter)->getName() == objectName)
		{
			return true;
		}
	}
	return false;
}


/*Implementation of the use function of the player class.
This function will tell the description of each object and print it.*/
bool player::use(const string object, const string object2) {
	bool ret = false;

	item* itemToBeUsed = NULL;
	bool check2ndobjectUsage = false;
	
	item* itemToBeFound = myWorld->getItem(object);
	if (!object2.empty())
	{
		itemToBeUsed = myWorld->getItem(object2);
		if(itemToBeUsed)
		{
			check2ndobjectUsage = loc->useObject(itemToBeUsed);
		}
	}

	if (itemToBeFound)
	{
		bool locUsage = loc->useObject(itemToBeFound);
		if (locUsage)
		{
			if (object2.empty())
			{
				if (object == "USB")
				{
					if (useComputer)
					{
						cout << "Retrieved documents from computer.\n";
					}
					else
					{
						cout << "Empty USB, use computer to copy documents.\n";
					}
				}
				else if (object == "COMPUTER")
				{
					useComputer = true;
					cout << "My computer\n";
				}
				else if (object == "LADDER")
				{
					moveLadder = true;
					cout << "You have positioned the ladder correctly. Go down\n";
				}
				else if (object == "FLASHLIGHT")
				{
					useObject = true;
					cout << "Using Flashlight. Now there is light.\n";
				}
				else if (object == "GRENADE")
				{
					if (loc->getLocationName() == "VULCAN") 
					{
						cout << "The door has been blasted open. The boss is straight ahead.\n";
						ret = true;
					}

					if ((loc->checkAlien()) && (loc->getLocationName() == "FINAL BATTLE"))
					{
						loc->attackAlien(150);
						cout << "Grenade was super effective.\n";
					}
					
				}
				else
				{
					cout << "Nothing happens.\n";
				}
			}
			else
			{
				if (object == "FIGURINE")
				{
					if (object2 != "CHEST")
					{
						cout << "Cannot use figurine.\n";
					}
					else
					{
						if (check2ndobjectUsage)
						{
							cout << "The chest opens and a paper falls out.\n";
							item* theItem = myWorld->getItem("PAPER");
							theItem->setVisibility(true);
						}
						else
						{
							cout << object2 << " not usable in this location.\n";
							return false;
						}
					}
				}
				if (object == "USB")
				{
					if (object2 != "COMPUTER") 
					{
						cout << "Cannot use USB.\n";
					}
					else
					{
						if (check2ndobjectUsage)
						{
							cout << "Retrieved documents from computer.\n";
						}
					}
				}
				else if ((object == "GRENADE") && (object2 == "DOOR"))
				{
					
					cout << "The door has been blasted open. The boss is straight ahead.\n";
					ret = true;
				}
				else
				{
					cout << "Wrong usage.\n";
				}
			}
		}
		else 
		{
			cout << object <<"is not usable in location, nothing happens.\n" << endl;
		}
	}
	else
	{
		cout << "Item does not exist.\n";
	}
	return ret;
}


/*Implementation of the getCurrentLocation function of the player.
This function will return the current location of the player.*/
location* player::getCurrentLocation() {
	
	return loc;
}

/*Implementation of the moveLoc funtion of the player.
The player will get the current location and the check if the player can move to a new location.*/
void player::moveLoc(string dir) {
	std::string curLocName = loc->getLocationName();
	std::string line;
	if (curLocName == "FARMHOUSE")
	{
		if (checkInventory("MIRROR")) {
			checkPuzzle();
		}
		else {
			cout << "You don't have the mirror in your inventory.\nA mirror is important at this location.\n";
		}
	}

	if ((curLocName == "VULCAN") && (upper(dir) == "NORTH"))
	{	
		cout << "There is a locked door, you need a code to enter, or use something to destroy it.\n";
		bool ret = moveToFinalLoc();
		if (!ret)
		{
			return;
		}
		
	}
	if ((curLocName == "HQ") && (upper(dir) == "TELEPORTER") && (!checkDocuments)) {
		cout << "Need the documents to use the teleporter.\n" << endl;
		return;
	}
	 if ((curLocName == "ALLEY") && (upper(dir) == "DOWN") && (!moveLadder)) {
		cout << "You can't move in that direction, use an object.\n" << endl;
	}
	else {
		std::string dest = myWorld->getLoc(curLocName, dir);

		cout << dest << endl;

		if ((curLocName != dest) && (dest != "NOTHING THERE")) {
			loc = myWorld->updateLocation(dest);
			if (loc) {
				loc->look();
				if (dest == "BACK ENTRANCE")
				{
					healthPoints = 0;
					life = false;
					cout << "Good try, don't take the easy way out.\n";
				}
			}
			else {
				cout << "Error Location not found." << endl;
			}
		}
		if (moveLadder) {
			moveLadder = false;
		}	
		
	}

}
/*Implementation of the look function.
Checks if player is in a specific location if they are then there is a condition
Else uses the location look to tell the player what is in the location.*/
void player::look() {
	
	if (loc->getLocationName() == "SEWER") {
		if (useObject) {
			cout << "You can see a path ahead to the east.";
			loc->look();
			useObject = false;
		}
		else {
			cout << "It's too dark to see anything, use a flashlight." << endl;
		}

	}
	else {
		loc->look();
	}
}

/*Implementation of the checkPuzzle function of the player class.
checkPuzzle is used to check if the puzzle has been solved or not.
*/
void player::checkPuzzle(){
	std::string line;
	int count = 0;

	if (!puzzle) {
		return;
	}

	do 
	{
		cout << "Look in the mirror who do you see? Hint - There are 3 letters\n";
		std::getline(std::cin, line);
		line = trim(line);
		if (upper(line) == upper("YOU")) {
			cout << "Aliens like the number 7, it might help you in the future.\n";
			puzzle = false;
		}
		else 
		{ 
			count++; 
		}
	} 
	while ((puzzle) && (count < 2));
		
}

/*Implementation of the fight function of the player class.
Allows the player to fight.
*/
bool player::fight()
{
	bool ret = false;
	if (loc->checkAlien()) 
	{
		ret = loc->attackAlien(30);
		if(!ret)
		{
			loc->attackPlayer();
		}
		cout << "Your attack removed 30 points of health\n";
	}
	else 
	{
		cout << "There are no aliens to fight.\n";
	}
	return ret;
}

/*Implementation of the decreaseHealth function of the player class.
The decreaseHealth function allows hp to be reduced.
*/
void player::decreaseHealth(int attackPoints) {
	healthPoints = healthPoints - attackPoints;
	if (healthPoints <= 0) 
	{
		healthPoints = 0;
		life = false;
	}
	if (!life) 
	{
		cout << name << " is dead.";
	}
	else 
	{
		cout << name << " Healthpoints - " << healthPoints << ".";
	}
}

/*Implementation of the isPlayerAlive function.
Tells if player is alive or dead.
*/
bool player::isPlayerAlive()
{ 
	return life;
}

/*Implementation of the moveToFinalLoc function
This function helps to make the logic of the final boss battle.
*/
bool player::moveToFinalLoc()
{
	
	string objectName1;
	string objectName2;
	bool ret = false;
	int count = 0;
	std::string line;

	do
	{
		cout << "Enter door code: \n";
		std::getline(std::cin, line);
		count++;
		line = trim(line);
		if (line == "7868")
		{
			cout << "Door opens.The boss is just ahead.\n";
			ret = true;
			break;
		}
		else if (upper(line).find("USE") != string::npos)
		{
			std::istringstream iss(line);
			std::vector<std::string> tokens;
			std::copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				back_inserter(tokens));

			if (upper(tokens[0]) == upper("use"))
			{
				if (tokens.size() == 2)
				{
					objectName1 = upper(tokens[1]);
					if (use(objectName1, objectName2))
					{
						ret = true;
						break;
					}
				}
				else if (tokens.size() == 4)
				{
					if ((upper(tokens[2]) == "ON") ||
						(upper(tokens[2]) == "AT"))
					{
						objectName1 = upper(tokens[1]);
						objectName2 = upper(tokens[3]);

						if (use(objectName1, objectName2))
						{
							ret = true;
							break;
						}
					}
					else
					{
						cout << "Wrong code.\n";
					}
				}
				else
				{
					cout << "Wrong code.You have " << 3 - count << " tries left.\n";
				}
			}
			else
			{
				cout << "Wrong code.You have " << 3 - count << " tries left.\n";
			}
		}
		else
		{
			cout << "Wrong code.You have " << 3 - count << " tries left.\n";
		}
	} while (count <= 15);
	if (!ret)
	{
		cout << "You entered the wrong code too many times. You have triggered an alarm, the cyborgs have arrived behind you. There are a lot of them, they open fire. You try your best but you still die.";
		healthPoints = 0;
		life = false;
	}
	return ret;
}