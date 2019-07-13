#pragma once
#include "pch.h"
#include "location.h"
#include <iostream>

using namespace std;

extern player* me;

/*This location.cpp file contains the implementation of the location class declared in location.h
*/

/*Implementation of the constructor of the location class.
Pass a parameter called inName and indesc which contains the name and description of the location object */
location::location(string inName,string indesc)
{
	name = inName;
	desc = indesc;
}

/*Implmentation of the destructor of the location class*/
location::~location()
{
}

/*Implementation of the look function of the location class.
This function will print a short description of the location object to the screen.*/
void location::look()
{
	if (name == "SEWER") {
		cout << "";
	}
	else {
		cout << desc << endl;
		showInventory();
		showPlayer();
	}
}

/*Implementation of the addObject function of the location class.
This function will add an object to the location.*/
void location::addObject(item* myItem)
{
	objectlist.push_back(myItem);
}

/*Implementation of the getLocationName function of the location class.
This function will return the name of the location object.*/
string location::getLocationName() const
{
	return name;
}

/*Implementation of the getObject function of the location class.
Pass a parameter called objectnme and the function will return the object
whose name matches the input parameter.*/
item* location::getObject(string objectnme)
{
	item* retItem = NULL;
	list<item*>::iterator myIter;
	for (myIter = objectlist.begin(); myIter != objectlist.end(); myIter++)
	{	
	
		if ((*myIter)->getName() == objectnme)
		{
			if ((*myIter)->isUsable())
			{
				retItem = *myIter;
			}
		} 
	}
	return retItem;
}

/*Implementation of the showInventory function of the location class.
This function will print all the objects in the location to the screen.*/
void location::showInventory()
{
	item* myItem;
	string name;
	list<item*>::iterator theiter;
	if (objectlist.empty()) {
		cout << "There are no items in this room that can be taken or used." << endl;
			return;
	}
	cout << "These are the items available in this room: " << endl;
	for (theiter = objectlist.begin(); theiter != objectlist.end(); theiter++) {
	    myItem = *theiter;
		if (myItem->isVisible()) 
		{
			name = myItem->getName();
			cout << name << ": " << myItem->look() << endl;
		}
	}
}

/*Implementation of the useObject function of the location class.
Pass a parameter called objectName to this function, the function will return true
if the object can be used in the location; otherwise, the function will return false.*/
bool location::useObject(item* itemName)
{
	
	if (itemName-> isUsableInLocation(this)) {
		return true;
	}
	else {
		return false;
	}
}
/*Implementation of the addplayer function.
This function allows the addition of a new player called alien.
*/
void location::addplayer(string alienName)
{
	alien = new player(alienName);
	
}

/*Implementation of the showPlayer function of the location class.
This function tells the player if there is an alien in the location.
If there is an alien then the alien will attack.
*/
void location::showPlayer()
{
	if (alien) {
		cout << "There is an alien in this room. He is attacking you.\n";
		attackPlayer();
	}
}


/*Implementation of the removeObject function of the location class.
This function will remove an object from the location.*/
void location::removeObject(item* myItem) {
	objectlist.remove(myItem);
}

/*Implementation of the checkAlien function.
Boolean to check if alien or not, returns true or false.
*/
bool location::checkAlien() {
	if (alien) {
		return true;
	}
	else {
		return false;
	}
}

/*Implementation of the attackAlien function.
This function allows to attack the alien at locations.
*/
bool location::attackAlien(int attackPoints) 
{
	bool ret = false;
	if (alien)
	{
		alien->decreaseHealth(attackPoints);
		if (!alien->isPlayerAlive())
		{
			cout << " Alien is dead.\n";
			cout << "Congratulations you have beaten the Big Baddie.\n";
			cout << "You won.\n";
			delete alien;
			alien = NULL;
			ret = true;
		}
	}
	return ret;
}

/*Implementation of the attackPlayer function.
This function allows the alien to attack the player default damage is set to 30.
*/
void location::attackPlayer() {
	if (me) 
	{
		me->decreaseHealth(30);
	}
}
