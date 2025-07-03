#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include <memory>
#include <vector>
#include "Item.hpp"
class GameManager; 

enum class TargetType {
    HERO,
    VILLAGER
}; 

enum class MonsterType {
    DRACULA,
    INVISIBLE_MAN
};


struct TargetInfo {
    std::string name;
    TargetType type;
    std::string location;
    int distance;
};

class Monster {
public:
    Monster(const std::string& name, MonsterType type, 
    const std::string& startingLocation, int frenzyOrder);

    virtual ~Monster();


    
    std::string getName() const { return name; }
    MonsterType getType() const { return type; }
    std::string getCurrentLocation() const { return currentLocation; }
    bool isDefeated() const { return isDefeated_; } 
    int getFrenzyOrder() const { return frenzyOrder; }
    
    void setCurrentLocation(const std::string& location) { currentLocation = location; }
    void setDefeated(bool defeated) { isDefeated_ = defeated; }    
    void setFrenzied(bool frenzied) { isFrenzied_ = frenzied; }
    bool isFrenzied() const { return isFrenzied_; }
    
    virtual void usePower(GameManager& gameManager) = 0;
    virtual void move(int steps, const GameManager& gameManager);
    virtual void attack(GameManager& gameManager);
    virtual bool canBeDefeated(const GameManager& gameManager) const = 0;
    virtual std::vector<TargetInfo> getTargetsAtLocation(const GameManager& gameManager) const;
    
    virtual int getTaskProgress() const = 0;
    virtual int getRequiredTaskProgress() const = 0;
    std::string monsterTypeToString(MonsterType type); 

protected:
    std::string name;
    MonsterType type;
    std::string currentLocation;


    bool isDefeated_ = false;
    bool isFrenzied_ = false;
    int frenzyOrder;
};

#endif 