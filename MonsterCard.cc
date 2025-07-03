#include "MonsterCard.hpp"
#include "GameManager.hpp" 
#include "Monster.hpp"

#include <iostream>
#include <utility>

using namespace std;

MonsterCard::MonsterCard(string name, int items, vector<MonsterStrike> strikes)
    : Card(move(name), CardType::MONSTER), itemsToSpawn(items), strikes(move(strikes)) {}

void MonsterCard::applyEffect(GameManager& engine) 
{
    engine.drawAndPlaceItems(getItemsToSpawn());
    
  
    engine.applyMonsterEvent(getCardName());
    
    engine.resolveStrikes(getStrikes());
}

string MonsterCard::getDescription() const 
{
    string desc = "Items: " + to_string(itemsToSpawn) + ". Event: " + getCardName();
    return desc;
}

int MonsterCard::getItemsToSpawn() const 
{
    return itemsToSpawn;
}

const vector<MonsterStrike>& MonsterCard::getStrikes() const 
{
    return strikes;
}
