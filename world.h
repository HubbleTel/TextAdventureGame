#pragma once
#include "pch.h"
#include "player.h"
#include "location.h"
#include <vector>
#include <string>
#include "utils.h"
#include <map>

using namespace std;

/**
 * This world.h file contains the declaration of the world class.
 * The world class represents the game world with all it's locations and objects.
 */
class item;
class location;
class world {

protected:
	map<string, item*> gameobjects;
	map<string, location*> gamelocs;
	static location* currLoc;
	map<string, map<string, string>> gamedir;

public:

	/*Default constructor*/
	world();

	/*Default destructor.*/
	~world();

	/*Return the player's current location.*/
	location* getCurrentLocation();

	/*Add an object to the world.*/
	void addObject(location* loc, string objectname, string describe, bool eqp, string inDeets,bool visible = true);

	void addLocationToObject(string itemName, location *loc);

	/*Get an item from the world class.*/
	item* getItem(string itemName);

	/*Add a location to the game world.*/
	void addLoc();
	
	/*Get the location from the world.*/
	string getLoc(string inLocName, string dir);

	/*Update the player's current location in the world.*/
	location* updateLocation(string locName);

	location* makeLocation(string locationName,string description);
};


