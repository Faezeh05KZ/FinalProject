#include "Item.hpp"
#include <iostream>

#include <utility> 
#include <string>

using namespace std;

Item::Item(string name, ItemColor color, int strength, string location)
    : Name(move(name)), Color(color), Strength(strength), Location(move(location)) {}

string Item::getName() const 
{
    return Name;
}

ItemColor Item::getColor() const 
{
    return Color;
}

int Item::getStrength() const 
{
    return Strength;
}

string Item::getLocation() const 
{
    return Location;
}

void Item::displayInfo() const
{
    cout << "Item: " << Name
              << " | Color: " << itemColorToString(Color)
              << " | Power: " << Strength
              << " | Location: " << Location << endl;
}