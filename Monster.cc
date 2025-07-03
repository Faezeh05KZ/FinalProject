#include "Monster.hpp"
#include "GameManager.hpp"
#include "GameUtils.hpp"
#include "Hero.hpp"
#include <algorithm>
#include <cmath>

Monster::Monster(const std::string& name, MonsterType type,
    const std::string& startingLocation, int frenzyOrder): 
    name(name), type(type), currentLocation(startingLocation), 
    frenzyOrder(frenzyOrder) {}

Monster::~Monster() = default; 

void Monster::move(int steps, const GameManager& gameManager) {
    if (isDefeated_ || steps <= 0) 
        return;
    
    auto connected = gameManager.getGameMap()->getConnectedLocations(currentLocation);
    if (!connected.empty()) {
        currentLocation = connected[0]; 
    }
}

void Monster::attack(GameManager& gameManager) {
    if (isDefeated_) 
        return;
    
    auto targets = getTargetsAtLocation(gameManager);
    if (targets.empty()) 
        return;
    
    if (targets[0].type == TargetType::HERO) {
        auto hero = gameManager.getHeroByName(targets[0].name);
        if (hero && !hero->isDamaged()) {
            if (!gameManager.defendAttack(hero)) {
                hero->takeDamage();
                hero->setCurrentLocation("Hospital");
                gameManager.increaseTerrorLevel();
            }
        }
    } else {
        auto villager = gameManager.getVillagerByName(targets[0].name);
        if (villager && villager->isInPlay()) {
            villager->setDead(true);
            gameManager.increaseTerrorLevel();
        }
    }
}

std::string Monster::monsterTypeToString(MonsterType type) {
    static const std::map<MonsterType, std::string> monsterNames = {
        {MonsterType::DRACULA, "Dracula"},
        {MonsterType::INVISIBLE_MAN, "Invisible Man"}
    };
    return monsterNames.at(type);
}

std::vector<TargetInfo> Monster::getTargetsAtLocation(const GameManager& gameManager) const {
    std::vector<TargetInfo> targets;
    
    for (const auto& hero : gameManager.getHeroes()) {
        if (hero->getCurrentLocation() == currentLocation && !hero->isDamaged()) {
            targets.push_back({hero->getName(), TargetType::HERO, currentLocation, 0});
        }
    }
    
    auto villagers = gameManager.getVillagersAtLocation(currentLocation);
    for (const auto& villager : villagers) {
        if (villager->isInPlay()) {
            targets.push_back({villager->getName(), TargetType::VILLAGER, currentLocation, 0});
        }
    }
    
    return targets;
}