#ifndef TUI_HPP
#define TUI_HPP

#include "GameManager.hpp"
#include <memory>
#include <vector>

class TUI {
public:
    TUI(std::shared_ptr<GameManager> manager);
    void run();

private:
    std::shared_ptr<GameManager> gameManager;
    std::vector<std::string> mapLayout;
    bool mapDisplayedInCurrentTurn;

    void displayHeader() const;
    void displayTerrorLevel() const;
    void displayHeroesInfo() const;
    void displayMonstersInfo() const;
     void displayFullMapInfo() const; 
    void displayCurrentPlayerActions() const;
    void displayHelp() const;
    void clearScreen() const;

    void setupPhase();
    void heroPhase();

    void handleMove();
    void handleGuide();
    void handlePickUp();
    void handleAdvance();
    void handleDefeat();
    void handleSpecialAction();
    void handleUsePerk();
    void handleExit();
    void confirmExit();
};

#endif