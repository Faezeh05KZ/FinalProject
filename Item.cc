#include "Item.hpp"
#include <utility>

using namespace std;

Item::Item(string name, ItemColor color, int strength, string originalLocation)
    : name(move(name)), color(color), strength(strength), originalLocation(move(originalLocation)) {}

string Item::getName() const
{ return name; }

ItemColor Item::getColor() const
{ return color; }

int Item::getStrength() const
 { return strength; }

string Item::getOriginalLocation() const
{ return originalLocation; }
