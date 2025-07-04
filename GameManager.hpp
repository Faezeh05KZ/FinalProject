#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <vector>
#include <memory>
#include <string>
#include <map>

class Hero;
class Monster;
class GameMap;
class Item;
class Villager;
class Player;
class MonsterCard;
class PerkCard;
struct MonsterStrike;
enum class TargetType;  
struct TargetInfo;

class GameManager {
    public:
    GameManager();
    
    Hero* getHeroAtLocation(const std::string& location) const;
    std::shared_ptr<Hero> getHeroByName(const std::string& name) const;
    std::shared_ptr<Monster> getMonsterByName(const std::string& name) const;
    std::shared_ptr<Villager> getVillagerByName(const std::string& name) const;

    
    void initializeGame();
    void startGame(const std::vector<std::string>& playerNames);
    void startNextTurn(); //شروع نوبت بعدی 
    void monsterPhase();
    
    bool isGameOver() const { return gameOver; }
    bool checkWinConditions() const; // بررسی شرایط برد 
    bool checkLoseConditions(); // برسی شرایط باخت 

    bool moveHero(const std::string& heroName, const std::string& destination);
    bool guideVillager(const std::string& heroName, const std::string& villagerName, const std::string& destination);
    bool pickUpItems(const std::string& heroName, const std::vector<std::string>& itemNames);
    bool useSpecialAbility(const std::string& heroName, const std::string& optionalTarget = "");
    bool usePerkCard(const std::string& heroName, const std::string& cardName);
    bool advanceTask(const std::string& heroName, const std::string& monsterName);
    bool defeatMonster(const std::string& heroName, const std::string& monsterName); // شکست هیولا
    bool defendAttack(const std::shared_ptr<Hero>& hero); // دفاع در برابر حمله
    
    int getTerrorLevel() const { return terrorLevel; }
    const std::vector<std::shared_ptr<Hero>>& getHeroes() const { return heroes; }
    const std::vector<std::shared_ptr<Monster>>& getMonsters() const { return monsters; }
    const std::vector<std::shared_ptr<Player>>& getPlayers() const { return players; }
    std::string getCurrentPlayerName() const;
    std::shared_ptr<Hero> getCurrentHero() const;   
    std::shared_ptr<GameMap> getGameMap() const { return gameMap; }
    std::vector<std::shared_ptr<Item>> getItemsAtLocation(const std::string& location) const;
    std::vector<std::shared_ptr<Villager>> getVillagersAtLocation(const std::string& location) const;
    
    void increaseTerrorLevel(int amount = 1); // افزایش سطح ترس
    void drawAndPlaceItems(int count); // کشیدن و قرار دادن ایتم ها 
    void overstockItems(); // توزیع ایتم بین بازیکنان
    void setSkipMonsterPhase(bool skip) { skipNextMonsterPhase = skip; } // رد کردن فاز هیولا
    void placeMonster(const std::string& monsterName, const std::string& location); // قرار دادن هیولا
    void placeVillagerOnBoard(const std::string& villagerName, const std::string& location); // قرار دادن روستایی
    void moveMonsterToHero(const std::string& monsterName); // حرکت هیولا به سمت قهرمان
    void resolveStrikes(const std::vector<MonsterStrike>& strikes); 
    
    void applyMonsterEvent(const std::string& cardName); // اعمال رویداد هیولا
    void thiefEvent();
    void hypnoticGazeEvent(); 
    void onTheMoveEvent(); 
    
    void promptAndPlaceMonster(const std::string& monsterName); // درخواست قرار دادن هیولا
    void promptAndMoveMonster(const std::string& monsterName, int steps); // درخواست حرکت هیولا 
    void promptAndMoveHero(const std::string& heroName, int steps);  // درخواست حرکت قهرمان 
    
    void moveMonsterTowardsTarget(const std::shared_ptr<Monster>& monster, int steps); // حرکت هیولا به سمت هدف
    TargetInfo findNearestTarget(const std::string& fromLocation) const; // یافتن نزدیک ترین هدف
    void handleAttack(const std::shared_ptr<Monster>& monster, int diceCount); 
    void rescueVillager(const std::string& villagerName, const std::string& heroName); // نجات روستایی
    void drawPerkCard(const std::string& heroName); // کشیدن perk card 
    void updateFrenzyOrder(bool forceNext = false); 
    
private:

    int terrorLevel;
    int turnCount;
    bool gameOver;
    bool skipNextMonsterPhase;
    int currentPlayerIndex;
    std::string frenziedMonster;

    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Hero>> heroes;
    std::vector<std::shared_ptr<Monster>> monsters;
    std::shared_ptr<GameMap> gameMap;
    std::vector<std::shared_ptr<Villager>> villagers;
    
    std::vector<std::shared_ptr<Item>> itemPool;
    std::vector<std::shared_ptr<PerkCard>> perkCardDeck;
    std::vector<std::shared_ptr<MonsterCard>> monsterCardDeck;
    
    void initializeHeroes();
    void initializeMonsters();
    void initializeItems();
    void initializeVillagers();
    void initializeCards();
    void distributeInitialPerkCards();


};

#endif
