#include "Mayor.hpp"
#include <utility>
#include <iostream>

using namespace std;

Mayor::Mayor(string name, string startingLocation)
    : Hero(move(name), HeroType::MAYOR, 5, move(startingLocation)) {}

bool Mayor::hasSpecialAction() const 
{
    return false;
}