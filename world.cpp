#pragma once
#include "pch.h"
#include "world.h"
#include <iostream>

using namespace std;

/*This world.cpp file contains the implementation of the world class declared in world.h
*/

/*Initialize class statics and declare global variables used.*/
location* world::currLoc = NULL;

/*Implementation of the getLoc function of the world class.
This function takes an input inLocName and an input direction
and determines the name of the next location in the game.*/
string world::getLoc(string inLocName, string dir)
{
	string locName = "NOTHING THERE";
	map<string, map<string, string>>::iterator diriter;

	map<string, string>::iterator mapiter;
	diriter = gamedir.find(upper(inLocName));

	if (diriter != gamedir.end()) {
		mapiter = diriter->second.find(upper(dir));
		if (mapiter != diriter->second.end()) {
			locName = mapiter->second;
		}
	}
	return locName;
}

/*Implementation of the default constructor of the world class.*/
world::world()
{
	addLoc();
	currLoc = gamelocs.find("FARMHOUSE")->second;
}

/*Implementation of the default destructor of the world class.*/
world::~world()
{
}

/*Implementation of the getCurrentLocation function of the world class.
This function will return the current location of the player in the game world.*/
location* world::getCurrentLocation() {
	return currLoc;
}



location* world::makeLocation(string locationName, string description) {
	location* loc = new location(locationName, description);
	gamelocs[locationName] = loc;
	return loc;
}

/*Implementation of the addLoc function of the world class.
This function will create locations using a map in the game world and add objects to these locations.*/

void world::addLoc()
{
	map<string, string> tempMap;

	string locationName = "FARMHOUSE";
	string indesc = "You're at home. You can hear noises outside. You quietly peek through the windows of your house. \nThere are aliens in the street infront of your house. They are making their way towards your house.\nYou need to escape. Quick.\nThere is a window on the south side you can escape from. Any other directions, aliens will catch you.\n";
	
	location*loc = makeLocation(locationName,indesc);

	addObject(loc, "USB", "MY USB", true, "This is your USB, it's in blue in color with my name in Silver.\nIt can store upto 10TB of memory.\n");
	addObject(loc, "COMPUTER", "MY COMPUTER", true, "Your trusy rundown computer that has a lifetimes worth of documents about alien eradication.\n ");
	addObject(loc, "MIRROR", "MY MIRROR", true, "You look into the mirror and stare at your reflection\n You look at yourself for a long time.\n Do you like what you see?\n");
	
	tempMap["SOUTH"] = "STREET BEHIND HOUSE";

	gamedir["FARMHOUSE"] = tempMap;
	tempMap.clear();
	
	locationName = "STREET BEHIND HOUSE";
	indesc = "You are in the street behind your house. There is an alley to the east and west.\n";
	loc = makeLocation(locationName, indesc);

	tempMap["NORTH"] = "FARMHOUSE";
	tempMap["WEST"] = "ALLEY";
	tempMap["EAST"] = "TRASH ALLEY";

	gamedir["STREET BEHIND HOUSE"] = tempMap;
	tempMap.clear();

	map<string, map<string, string>>::iterator diriter;
	map<string, string>::iterator mapiter;

	locationName = "TRASH ALLEY";
	indesc = "You see a trash can, you can hide in there if need be. \nThere is nothing else in this alley but there is a way back to the street.\n";
	loc = makeLocation(locationName, indesc);
	addObject(loc, "TRASH", "It's trash", true, "Look at you actually looking at trash\n. If you take this you will have a -99 debuff to hygiene.\n");
	tempMap["WEST"] = "STREET BEHIND HOUSE";

	gamedir["TRASH ALLEY"] = tempMap;
	tempMap.clear();


	locationName = "ALLEY";
	indesc = "You are in the alley, there is sewer here with a ladder that you can go down.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["ALLEY"] = loc;
	addObject(loc, "BRICK", "Something from a forgotten time period.\n", true, "No one likes this brick, it's been left here for ages, you should take it with me as a souvenir. \nThe brick doesn't have any special effects\n");
	addObject(loc, "LADDER", "A ladder that can be used to go down.\nOnce you move forward you can't return", true, "This ladder will take me away from the nasty aliens, \nyou need to hide somewhere real quick. \nIt is very smelly here.\n");

	tempMap["EAST"]  = "STREET BEHIND HOUSE";
	tempMap["DOWN"]  = "SEWER";

	gamedir["ALLEY"] = tempMap;
	tempMap.clear();

	locationName = "SEWER";
	indesc = "You are in a smelly sewer.You wonder if there are rats...\nYou see a blue light to the east.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["SEWER"] = loc;
	addObject(loc, "FLASHLIGHT", "A flashlight that can be used to see in the dark.", true, "It's a flashlight, it works, congratulations you found a flashlight in the future.\n stop reading and start playing the game.\n");
	tempMap["EAST"] = "UC";

	gamedir["SEWER"] = tempMap;
	tempMap.clear();

	locationName = "UC";
	indesc = "You are in the underground city, there are a lot of people here, \nit seems like the beginning of the resistance against the aliens.\nKeep going north to reach the plaza.\n";
	loc = makeLocation(locationName, indesc);
	gamelocs["UC"] = loc;

	tempMap["NORTH"] = "PLAZA";
	tempMap["WEST"] = "SEWER";

	gamedir["UC"] = tempMap;
	tempMap.clear();


	locationName = "PLAZA";
	indesc = "There are more people here than in the city, \nthere are some stairs going up, and an alley to the east and west.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["PLAZA"] = loc;

	tempMap["UP"]   = "HQ";
	tempMap["WEST"] = "ALLEY A";
	tempMap["EAST"] = "ALLEY B";

	gamedir["PLAZA"] = tempMap;
	tempMap.clear();

	locationName = "ALLEY A";
	indesc = "An alley with a bunch of rundown buildings,\nthis is where the plebians live. The plaza is to the west.\n";
	loc = makeLocation(locationName, indesc);

	loc = new location("ALLEY A", "An alley with a bunch of rundown buildings, \nthis is where the plebians live. The plaza is to the west.\n");
	gamelocs["ALLEY A"] = loc;

	tempMap["EAST"] = "PLAZA";

	gamedir["ALLEY A"] = tempMap;
	tempMap.clear();

	locationName = "ALLEY B";
	indesc = "An alley that looks a bit more modern and there are some large statues, too bad you don't have any money to live here.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["ALLEY B"] = loc;
	addObject(loc, "BATTERY", "A battery", true, "This could be useful, it might power something.\n");

	tempMap["WEST"] = "PLAZA";

	gamedir["ALLEY B"] = tempMap;
	tempMap.clear();

	locationName = "HQ";
	indesc = "The leaders of the resistance are looking down at you from a platform. \nGo north to the office\nThere is a teleporter that can only be used after you go north.If you have the documents type \"go teleporter\".\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["HQ"] = loc;

	tempMap["DOWN"] = "PLAZA";
	tempMap["NORTH"] = "OFFICE";
	tempMap["TELEPORTER"] = "INFORMATION ROOM";
	gamedir["HQ"] = tempMap;
	tempMap.clear();

	locationName = "OFFICE";
	indesc = "The mission is to steal some important documents for the resistance, you see a Blue door to the east\nand a Green door to the west.\nGo south to go back to HQ\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["OFFICE"] = loc;

	tempMap["WEST"]  = "BLUE ROOM";
	tempMap["EAST"]  = "GREEN ROOM";
	tempMap["SOUTH"] = "HQ";

	gamedir["OFFICE"] = tempMap;
	tempMap.clear();

	locationName = "BLUE ROOM";
	indesc = "There are a bunch of desks in the office.Go east to go back\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["BLUE ROOM"] = loc;
	addObject(loc, "DOCUMENTS", "Contains the detailed plans of the aliens.", true,"You don't understand any of these technical plans better to just take them. \n");
	tempMap["EAST"]       = "OFFICE";

	gamedir["BLUE ROOM"]  = tempMap;
	tempMap.clear();

	locationName = "GREEN ROOM";
	indesc = "There are just some desks and nothing else.\nMaybe go to the BLUE ROOM?";
	loc = makeLocation(locationName, indesc);

	gamelocs["GREEN ROOM"] = loc;
	addObject(loc,"FIGURINE","It looks like someone you know.",true,"After looking at it for a while, you figure out it's a figurine of yourself.\nHow is it there?\nWho made it\nHave you been here before?\nIs this the future or the past?\n");

	tempMap["WEST"]        = "OFFICE";

	gamedir["GREEN ROOM"]  = tempMap;
	tempMap.clear();

	locationName = "INFORMATION ROOM";
	indesc = "There is a pink door to the east and a yellow door to the west.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["INFORMATION ROOM"] = loc;

	tempMap["TELEPORTER"]  = "HQ";
	tempMap["EAST"]        = "PINK DOOR";
	tempMap["WEST"]        = "YELLOW DOOR";
	addObject(loc, "PAPER", "A useless piece of paper.", true, "The alien leader lives on the planet VULCAN, it is a vile planet, the door to the leader's room is not easy to open.\n");
	gamedir["INFORMATION ROOM"]  = tempMap;
	tempMap.clear();

	locationName = "YELLOW DOOR";
	indesc = "There are some trophies of alien annilation.\n Go East to go back to the information room.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["YELLOW DOOR"] = loc;

	addObject(loc,"HEAD", "This is the head of the alien Darth Maul.\n", true, "He was an alien that was killed by the people of Earth.\n");
	addObject(loc,"LIGHTSABER", "This is the lightsaber of Anakin Skywalker.\n", true, "It is just a prop, it doesn't actually work because you haven't awakened the force.\n");
	addObject(loc,"TOY", "This is a toy Ferrari.\n", true, "Not sure why this is here, it doesn't have anything to do with aliens.\n");
	addObject(loc,"WAND", "Belongs to a Mr. Harry Potter.\n", true, "There is no magic in this world, wait how is Harry Potter an alien?\n");
	tempMap["EAST"] = "INFORMATION ROOM";

	gamedir["YELLOW DOOR"] = tempMap;
	tempMap.clear();

	locationName = "PINK DOOR";
	indesc = "All the weapons the chosen one requires.\nGo west to the Information Room and north to the Runway.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["PINK DOOR"] = loc;
	addObject(loc, "GRENADE", "You can blow stuff up\n", true, "Make sure to aim or else you will be splattered\n");
	addObject(loc, "GUN", "You can shoot imaginary bullets, need actual bullets for it to work.\n", true, "Too bad you can't use it.");
	addObject(loc, "NOTE", "Welcome to the armory, take anything you like.\n", true, "Please take this note.\n");
	tempMap["WEST"] = "INFORMATION ROOM";
	tempMap["NORTH"] = "RUNWAY";

	gamedir["PINK DOOR"] = tempMap;
	tempMap.clear();

	locationName = "RUNWAY";
	indesc = "This is the walkway, there are some pictures of various heroes.\nNorth takes you to the Spaceship and south leads you back to the pink door.\n";
	loc = makeLocation(locationName, indesc);

	gamelocs["RUNWAY"] = loc;
	addObject(loc, "CHEST", "Why is there a chest in the runway?", true, "It is probably a trap.\n");
	addLocationToObject("FIGURINE", loc);
	addObject(loc, "PAPER", "This is an important document.\n", true, "The last three numbers for the code are 868.",false);
	tempMap["NORTH"] = "SPACESHIP";
	tempMap["SOUTH"] = "PINK DOOR";

	gamedir["RUNWAY"] = tempMap;
	tempMap.clear();

	locationName = "SPACESHIP";
	indesc = "A huge spaceship, it is called the SPACEFORCE-XVII.\nIt was made from the best element GALATONIUM, discovered by the scientist Galatanium who was also a space explorer.\nGo south to go to walkway and up to go to space.";
	loc = makeLocation(locationName, indesc);

	gamelocs["SPACESHIP"] = loc;
	addObject(loc, "MAP", "A map that reveals the way to the planet of VULCAN, where the alien leader that controls Earth resides.", true, "You must be real lucky to find a space map....");

	tempMap["SOUTH"] = "RUNWAY";
	tempMap["UP"] = "SPACE";

	gamedir["SPACESHIP"] = tempMap;
	tempMap.clear();

	locationName = "SPACE";
	indesc = "Space is vast, you can't see much but there might be something to the east.\n";
	loc = makeLocation(locationName, indesc);
	gamelocs["SPACE"] = loc;
	addObject(loc, "ROCK", "Look you found a space rock in space.You can obtain the rock through some advanced feature of the SPACEFORCE-XVII.\n", true, "It doesn't have any special effects.\n");
	tempMap["EAST"] = "VULCAN";

	gamedir["SPACE"] = tempMap;
	tempMap.clear();

	locationName = "VULCAN";
	indesc = "VULCAN is a planet without any vegetation, you have arrived in NewVULCANland.\nNewVULCANland is the main city where the aliens live, it is surrounded by an arid desert in every direction.\nThere are massive structures that look like buildings in NewVULCANland there are many alien species walking around.\nYou see some small and weak aliens being beaten by other huge and enormous aliens, all of the aliens look like humongous cochroaches.\nYou walk away from the main city and go further into the desert.\nAfter traveling for 2 days on foot you have arrived in front of a massive building.\nThis is where the alien leader Big Baddie lives.\nFortunately there are no guards right now and he is by himself.There are two ways to enter the building.\nFirst you can blow up the door, second sneak inside the back entrance.\nIf you forgot to get the grenade you can't go back since there is no fuel to leave VULCAN.Go north to fight the boss or go south to use the back entrance.\n";
	loc = makeLocation(locationName, indesc);
	gamelocs["VULCAN"] = loc;
	addLocationToObject("GRENADE", loc);
	tempMap["NORTH"] = "FINAL BATTLE";
	tempMap["SOUTH"] = "BACK ENTRANCE";

	gamedir["VULCAN"] = tempMap;
	tempMap.clear();

	locationName = "FINAL BATTLE";
	indesc = "The boss room, it is a fight to the end, you hear battle music.\nYou can't go back.\nThe Big Baddie has seen you and is preparing to attack.\n";
	loc = makeLocation(locationName, indesc);
	gamelocs["FINAL BATTLE"] = loc;
	addLocationToObject("GRENADE", loc);
	loc->addplayer("Big Baddie");
	gamedir["FINAL BATTLE"] = tempMap;
	tempMap.clear();

	locationName = "BACK ENTRANCE";
	indesc = "The back entrance, you went through the back door, but you see some aliens. It turns out that this place is a trap. You can't fight them all and you die.";
	loc = makeLocation(locationName, indesc);

	gamelocs["BACK ENTRANCE"] = loc;
	gamedir["BACK ENTRANCE"] = tempMap;
	tempMap.clear();
}

/*Implementation of the addObject function of the game world.
This function adds an object to the game location.
Pass a parameter locName containing the location name,
a parameter objectname containing the name of the object to be added to the location,
a parameter describe containing a short description of the object,
a boolean parameter eqp specifying if the object can be used and
a parameter inDeets containing the detailed description of the object.*/
void world::addObject(location *loc, string objectname, string describe, bool eqp, string inDeets,bool visible) {

	item* g = new item(objectname, describe, eqp, inDeets,visible);
	gameobjects[objectname] = g;
	g->usability(loc);
	
	
	if(loc)
	{
		loc->addObject(g);
	}

}

void world::addLocationToObject(string itemName, location *loc) 
{
	item *theItem = getItem(itemName);
	theItem->usability(loc);
}

/*Implementation of the getItem function of the game class.
This function returns an item from the game world.
Pass an input itemName containing the name of the item to be retrieved from the game.*/
item* world::getItem(string itemName)
{
	item* myItem = NULL;
	std::map<string, item*>::iterator it;

	it = gameobjects.find(itemName);

	if (it != gameobjects.end())
	{
		myItem = it->second;
		
	}
	return myItem;
}

/*Implementation of the updateLocation function of the game class.
This function updates the player's current location in the game.
Pass an input parameter locName containing the player's current location.*/
location* world::updateLocation(string locName)
{
	location* newloc = NULL;
	std::map<string, location*>::iterator it;
	it = gamelocs.find(locName);
	if (it != gamelocs.end())
	{
		newloc = it->second;
	}
	return newloc;
}
