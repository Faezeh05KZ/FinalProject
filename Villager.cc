#include "Villager.hpp"
#include <iostream>
#include <utility>

using namespace std;


Villager::Villager(string name, string safeLocation)
    : name(move(name)), safeLocation(move(safeLocation)), currentLocation(""), rescued(false), dead(false) {}

string Villager::getName() const
{ return name; }


string Villager::getCurrentLocation() const 
{ return currentLocation; }


string Villager::getSafeLocation() const 
{ return safeLocation; }


bool Villager::isRescued() const 
{ return rescued; }


bool Villager::isDead() const 
{ return dead; }


bool Villager::isInPlay() const 
{ return !currentLocation.empty() && !rescued && !dead; }

void Villager::enterPlay(std::string location) {
    currentLocation = location;
}

void Villager::moveTo(string new_location)
{
    currentLocation = move(new_location);
}

void Villager::setRescued(bool is_rescued)
{
    rescued = is_rescued;
    if (rescued)
    {
        currentLocation = ""; 
    }
}

void Villager::setDead(bool is_dead)
{
    dead = is_dead;
    if (is_dead)
    {
       currentLocation = ""; 
    }
}

void Villager::displayInfo() const
{
    cout << "  - Villager: " << name << ", Safe At: " << safeLocation;
    if(rescued) 
    {
        cout << " (Rescued)";
    }

    else if(dead)
    {
         cout << " (Dead)";
    }

    else if (isInPlay())
    {
        cout << " (In Danger at " << currentLocation << ")";
    }

    else
    {
        cout << " (Not in play)";
    }

    cout << endl;
}