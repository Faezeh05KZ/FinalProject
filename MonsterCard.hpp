#ifndef MONSTERCARD_HPP
#define MONSTERCARD_HPP

#include "Card.hpp"

#include <iostream>
#include <vector>
#include <string>

class Monster;

struct MonsterStrike
{
    std::string targetMonster;
    int moves;
    
    int dice;
};

class MonsterCard : public Card
{
    public:

        MonsterCard(std::string name, int items, std::vector<MonsterStrike> strikes);

        void applyEffect(GameManager& engine) override;

        std::string getDescription() const override;

        int getItemsToSpawn() const;
        const std::vector<MonsterStrike>& getStrikes() const;
        
    private:
    
        int itemsToSpawn;
        std::vector<MonsterStrike> strikes;
};

#endif
