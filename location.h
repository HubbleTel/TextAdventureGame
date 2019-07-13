#pragma once
#include "pch.h"
#include <string>
#include <list>
#include <Windows.h>
#include "item.h"
#include "player.h"

using namespace std;

/**
 * This location.h file contains the declaration of the location class.
 * The location class represents a location/room in the game.
 */
class item;
class player;

class location
{

private:
	string desc;
	string name;
	list <item*> objectlist;
	player* alien;
	
public: 
	
	/*Parameterized constructor, takes the name of the location*/
	location(string inName,string indesc);

	/*Destructor for the location class*/
	~location();
	
	/*Return the short description of the location and show all objects in the location*/
	void look();

	/*Return the name of the location*/
	string getLocationName() const;

	/*Add an object to the location*/
	void addObject(item* myItem);

	/*Remove an object from the location*/
	void removeObject(item* myItem);

	/*Get an object from the location*/
	item* getObject(string objnme);

	/*Show all objects in the location*/
	void showInventory();
	
	/*Use an object from the location*/
	bool useObject(item* itemName);

	void addplayer(string alienName);
	
	void showPlayer();

	bool checkAlien();

	bool attackAlien(int attackPoints);

	void attackPlayer();

};


