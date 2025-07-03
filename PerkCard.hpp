#ifndef PERK_CARD_HPP
#define PERK_CARD_HPP

#include "Card.hpp"

#include <iostream>
#include <string>

class PerkCard : public Card 
{
    public:

        enum class PerkEffectType 
        {
            VISIT_FROM_THE_DETECTIVE, 
            BREAK_OF_DAWN,          
            OVERSTOCK,              
            LATE_INTO_THE_NIGHT,    
            REPEL,                 
            HURRY                   
        };

        PerkCard(std::string name, PerkEffectType effect, std::string description);

        void applyEffect(GameManager& engine) override;

        std::string getDescription() const override;

    private:

        PerkEffectType effectType;
        std::string description;
};

#endif
