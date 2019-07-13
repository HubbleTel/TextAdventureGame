#pragma once
#include <string>	
#include <list>
#include "item.h"
#include "location.h"
#include "world.h"

using namespace std;

/**
 * This player.h file contains the declaration of the player class.
 * The player class represents a player in the game.
 */
class player {

protected:
	string name;
	// show players current location.
	location* loc;
	list <item*> inventory;
	bool useObject;
	bool moveLadder;
	bool useComputer;
	bool checkDocuments;
	bool life;
	bool puzzle;
	int healthPoints;

public:
	player();
	player(string playerName);
	/*Parameterized Constructor*/
	player(location* playerLoc);

	string getName();
	/*Default destructor*/
	~player();

	/*Show description of the object*/
	void look(const string objName); 

	/*Take an object*/
	void take(const string obj);

	/*Drop an object*/
	void drop(item* myItem);

	/*Display the players inventory*/
	void showInventory();

	/*Check if an object is in the players inventory*/
	bool checkInventory(string objName);

	/*Use an object*/
	bool use(const string obj,const string obj2);

	/*Get player location*/
	location* getCurrentLocation();
	/*move from a location*/

	void moveLoc(string dir);

	void look();
	
	bool fight();

	void checkPuzzle();

	void decreaseHealth(int attackPoints);

	bool isPlayerAlive();

	bool moveToFinalLoc();
};

