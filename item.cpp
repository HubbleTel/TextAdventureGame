#pragma once
#include "pch.h"
#include "item.h"

using namespace std;
/* 
 * This item.cpp file contains the implementation of the item class declared in item.h
 */

/*Implementation of the item class constructor
Pass a parameter called inName which contains the name of the item,
a parameter called description which contains the description of the item,
a bool called usable which specifies if the item can be used
and a string inDeets which contains the detailed description of the item.
*/
item::item(string inName, string description,bool usable, string inDeets,bool visible) {
	descr = description;
	name = inName;
	use = usable;
	deets = inDeets;
	visibility = visible;
}

/*Implementation of the destructor of the item class.*/
item::~item()
{
}

/*Implementation of the look function of class item
Returns the short description of the item.*/
string item::look()
{
	return descr;
}

/*Implementation of the isUsable function of item class.
Returns whether a particular item can be used in the game.*/
bool item::isUsable() {
	return use;
}

bool item::isUsableInLocation(location * loc) const
{
	for (auto iter = itemUsability.begin(); iter != itemUsability.end(); iter++)
	{
		if (*iter == loc) {
			return true;
		}
	}
	return false;
}

/*Implementation of the getName function of item class.
Returns the name of the item.*/
string item::getName() {
	return name;
}
/*Implementation of the getDeets function of item class.
Returns the detailed description of the item.*/
string item::getDeets()
{
	return deets;
}

void item::usability(location * loc)
{   
	if (loc) {
		itemUsability.push_back(loc);
	}
}

bool item::isVisible() {
	return visibility;
}

void item::setVisibility(bool visible) {
	visibility = visible;
}