#pragma once
#include "pch.h"
#include <string>
#include <list>
#include "location.h"


using namespace std;

/**
 * This item.h file contains the declaration of the item class.
 * The item class represents an object in the game.
 */
class location;
class item {


private:
	string descr;
	string name;
	string deets;
	bool use;
	list <location * > itemUsability;
	bool visibility;
public:
	/* Parameterized constructor for initializing a newly created item object.*/
	item(string inName, string description, bool usable, string inDeets,bool visible = true);

	/*Destructor for item class*/
	~item();
	
	/*Return the short description of the object.*/
	string look();
	
	/*Return the name of the object.*/
	string getName();

	/*Return the longer description of the object.*/
	string getDeets();

	void usability(location* loc);

	/*Return whether the item can be used.*/
	bool isUsable();
	
	bool isUsableInLocation(location *loc) const;

	bool isVisible();

	void setVisibility(bool visible);
};