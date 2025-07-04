#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <memory>
#include "Hero.hpp"

class Player 
{
    public:

        Player(std::string name);
        std::string getName() const;
        void assignHero(std::shared_ptr<Hero> hero);
        std::shared_ptr<Hero> getHero();

    private:

        std::string name;
        std::shared_ptr<Hero> hero;
};

#endif 
