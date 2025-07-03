#include "Player.hpp"
#include <utility>

using namespace std;

Player::Player(string name) : name(move(name)) {}

string Player::getName() const 
{
    return name;
}

void Player::assignHero(shared_ptr<Hero> assignedHero) 
{
    hero = assignedHero;
}

shared_ptr<Hero> Player::getHero() 
{
    return hero;
}