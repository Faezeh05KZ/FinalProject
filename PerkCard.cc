#include "PerkCard.hpp"
#include "GameManager.hpp"
#include "Hero.hpp"
#include "Player.hpp"

#include <iostream>
#include <utility>

using namespace std;

PerkCard::PerkCard(string name, PerkEffectType effect, string description)
    : Card(move(name), CardType::PERK), effectType(effect), description(move(description)) {}

string PerkCard::getDescription() const 
{
    return description;
}

void PerkCard::applyEffect(GameManager& engine) 
{
    cout << "Perk Card Activated: '" << cardName << "' - " << description << endl;

    switch (effectType) 
    {
        //  قرار دادن مرد نامرئی در مکان دلخواه 
        case PerkEffectType::VISIT_FROM_THE_DETECTIVE:
            engine.promptAndPlaceMonster("Invisible Man");
            break;

        //  رد شدن از فاز هیولا و کشیدن ۲ آیتم جدید
        case PerkEffectType::BREAK_OF_DAWN:
            engine.setSkipMonsterPhase(true);
            engine.drawAndPlaceItems(2);
            break;

        //  هر قهرمان یک آیتم جدید دریافت می‌کند
        case PerkEffectType::OVERSTOCK:
            engine.overstockItems();
            break;

        // بازیکن فعلی ۲ اکشن اضافه دریافت می‌کند
        case PerkEffectType::LATE_INTO_THE_NIGHT: 
        {
            shared_ptr<Hero> currentHero = engine.getCurrentHero();
            if (currentHero) {
                currentHero->addActions(2);
                cout << currentHero->getName() << " gets 2 extra actions!" << endl;
            }
            break;
        }

        // هر هیولا تا ۲ خانه جابجا می‌شود
        case PerkEffectType::REPEL:

            engine.promptAndMoveMonster("Dracula", 2);
            engine.promptAndMoveMonster("Invisible Man", 2);
            break;

        //  هر قهرمان تا ۲ خانه جابجا می‌شود
        case PerkEffectType::HURRY:
        {
            const auto& players = engine.getPlayers();

            if (!players.empty()) 
            {
                for (const auto& player : players)
                {
                     engine.promptAndMoveHero(player->getHero()->getName(), 2);
                }
            }
            
            break;
        }
    }
}
