#ifndef VILLAGER_HPP
#define VILLAGER_HPP

#include <string>

class Villager
{
    public:

        Villager(std::string name, std::string safeLocation);
        std::string getName() const;
        std::string getCurrentLocation() const;
        std::string getSafeLocation() const;
        bool isRescued() const;
        bool isDead() const;
        bool isInPlay() const;

        void enterPlay(std::string location);
        void moveTo(std::string new_location);
        void setRescued(bool rescued);
        void setDead(bool dead);
        void displayInfo() const;

    private:
    
        std::string name;
        std::string currentLocation;
        std::string safeLocation;
        bool rescued;
        bool dead;
};

#endif