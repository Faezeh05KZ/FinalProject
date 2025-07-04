#ifndef MAYOR_HPP
#define MAYOR_HPP

#include "Hero.hpp"

class Mayor : public Hero 
{
    public:

        Mayor(std::string name, std::string startingLocation);
        bool hasSpecialAction() const;

};

#endif