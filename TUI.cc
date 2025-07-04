#include "TUI.hpp"
#include "GameUtils.hpp"
#include "Constants.hpp"
#include "Hero.hpp"
#include "Archaeologist.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <stdexcept>
#include <typeinfo>

using namespace std;

TUI::TUI(shared_ptr<GameManager> manager) : gameManager(manager), mapDisplayedInCurrentTurn(false) {
    try {
        mapLayout = {
            "                                                                     ",
            "                  ---------------------------------------                  ",
            "                  |                                     |            ",
            "  [Cave] ----- [Camp]---------------[Precinct] ----- [Inn]    [Barn] ",
            "                  |                  |                  |          |  ",
            "                  |                  |     |-------------          |    ",
            "  [Abbey] ---- [Mansion]-----------------[Theatre] -----------------    ",
            "    |            |     |           |     |     |                      ",
            "  [Crypt]        |  [Museum] ---- [ Shop ] ----[Tower] -----[Duncron]           ",
            "                 |                |    |            |                  ",
            " [Graveyard]---[Church]------------  [Laboratory]  [Docks]            ",
            "                 |                     |                              ",
            "             [Hospital]           [Institute]                        ",
            "                                                                      "
        };
    } catch (const exception& e) {
        cerr << "Failed to initialize map layout: " << e.what() << endl;
        throw runtime_error("TUI initialization failed");
    }
}

void TUI::run() {
    try {
        setupPhase();
        while (!gameManager->isGameOver()) {
            try {
                heroPhase();
                if (!gameManager->isGameOver()) {
                    gameManager->monsterPhase();
                }
            } catch (const exception& e) {
                cerr << "Error during game phase: " << e.what() << endl;
                cout << "Attempting to continue game..." << endl;
                cout << "\nPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        cout << "\n================ GAME OVER ================" << endl;
        if (gameManager->checkWinConditions()) {
            cout << "CONGRATULATIONS! You have saved the town!" << endl;
        } else {
            cout << "The monsters have won... The town is lost." << endl;
        }
    } catch (const exception& e) {
        cerr << "Fatal error occurred: " << e.what() << endl;
        cerr << "The game must terminate." << endl;
        exit(EXIT_FAILURE);
    }
}

void TUI::setupPhase() {
    try {
        clearScreen();
        displayHeader();
        cout << "Welcome to Horrified! Let's set up the game." << endl;
        
        vector<string> playerNames;
        cout << "Enter name for Player 1: ";
        string name1;
        if (!getline(cin, name1)) {
            throw runtime_error("Failed to read player 1 name");
        }
        playerNames.push_back(name1);

        cout << "Enter name for Player 2: ";
        string name2;
        if (!getline(cin, name2)) {
            throw runtime_error("Failed to read player 2 name");
        }
        playerNames.push_back(name2);

        gameManager->initializeGame();
        gameManager->startGame(playerNames);
    } catch (const exception& e) {
        cerr << "Setup failed: " << e.what() << endl;
        throw;
    }
}

void TUI::heroPhase() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero for current player");
        }

        displayHeader();
        displayTerrorLevel();

        while (hero->getActionsLeft() > 0 && !gameManager->isGameOver()) {
            try {
                clearScreen();
                displayMonstersInfo();
                displayHeroesInfo();
                displayCurrentPlayerActions();

                cout << "\n" << hero->getName() << ", choose an action:" << endl;
                cout << "1. Move" << endl;
                cout << "2. Guide" << endl;
                cout << "3. Pick Up" << endl;
                cout << "4. Advance Task" << endl;
                cout << "5. Defeat Monster" << endl;
                cout << "6. Special Ability" << endl;
                cout << "7. Use Perk" << endl;
                cout << "8. Show Map & Items" << endl; 
                cout << "0. Exit Game" << endl;
                cout << "> ";

                int choice;
                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Invalid input - please enter a number");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice) {
                    case 1: handleMove(); break;
                    case 2: handleGuide(); break;
                    case 3: handlePickUp(); break;
                    case 4: handleAdvance(); break;
                    case 5: handleDefeat(); break;
                    case 6: handleSpecialAction(); break;
                    case 7: handleUsePerk(); break;
                    case 8: {
                        clearScreen();
                        displayFullMapInfo();
                        displayHelp();  
                        cout << "\nPress Enter to continue...";
                        cin.get();
                        break;
                    }
                    case 0: {
                        handleExit();
                        return;
                    }
                    default: {
                        cout << "Invalid choice. Please try again." << endl;
                        cout << "\nPress Enter to continue...";
                        cin.get();
                        break;
                    }
                }
            } catch (const exception& e) {
                cerr << "Action error: " << e.what() << endl;
                cout << "\nPress Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    } catch (const exception& e) {
        cerr << "Hero phase error: " << e.what() << endl;
        throw;
    }
}

void TUI::displayFullMapInfo() const {
    try {
        cout << "\nMAP & ITEMS INFORMATION:\n";
        cout << "-----------------------------------------------------------------------\n";
        
        for (const auto& line : mapLayout) {
            cout << line << endl;
        }
        cout << "-----------------------------------------------------------------------\n";
        
        cout << "\nITEMS IN LOCATIONS:\n";
        cout << "-----------------------------------------------------------------------\n";
        
        auto allLocations = gameManager->getGameMap()->getAllLocations();
        for (const auto& loc : allLocations) {
            auto items = gameManager->getItemsAtLocation(loc);
            if (!items.empty()) {
                cout << "  > " << loc << ": ";
                for (const auto& item : items) {
                    cout << item->getName() << "(" << item->getStrength() << ")       ";
                }
                cout << "\n";
            }
        }
        cout << "-----------------------------------------------------------------------\n";
    } catch (const exception& e) {
        cerr << "Failed to display map information: " << e.what() << endl;
        throw;
    }
}

void TUI::handleExit() {
    try {
        confirmExit();
    } catch (const exception& e) {
        cerr << "Exit handling failed: " << e.what() << endl;
        throw;
    }
}

void TUI::confirmExit() {
    try {
        clearScreen();
        displayHeader();
        cout << "Are you sure you want to exit the game? (y/n): ";
        
        char choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (tolower(choice) == 'y') {
            cout << "\nExiting game... Thank you for playing!\n";
            exit(0);
        }
    } catch (const exception& e) {
        cerr << "Exit confirmation failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handleMove() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }

        auto connected = gameManager->getGameMap()->getConnectedLocations(hero->getCurrentLocation());
        if (connected.empty()) {
            throw runtime_error("No connected locations available");
        }
        
        cout << "Choose a destination:" << endl;
        for (size_t i = 0; i < connected.size(); ++i) {
            cout << i + 1 << ". " << connected[i] << endl;
        }
        cout << "> ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice < 1 || choice > static_cast<int>(connected.size())) {
            throw runtime_error("Invalid destination choice");
        }

        string dest = connected[choice - 1];
        if (!gameManager->moveHero(hero->getName(), dest)) {
            throw runtime_error("Cannot move to " + dest + " - locations not connected or hero is damaged");
        }
        hero->useAction();
    } catch (const exception& e) {
        cerr << "Move failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handlePickUp() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }

        auto items = gameManager->getItemsAtLocation(hero->getCurrentLocation());
        if (items.empty()) {
            throw runtime_error("No items to pick up at current location");
        }

        cout << "Choose an item to pick up:" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }
        cout << "> ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice < 1 || choice > static_cast<int>(items.size())) {
            throw runtime_error("Invalid item choice");
        }

        string itemName = items[choice - 1]->getName();
        if (!gameManager->pickUpItems(hero->getName(), {itemName})) {
            throw runtime_error("Cannot pick up " + itemName + " - item not found or hero's inventory is full");
        }
        hero->useAction();
    } catch (const exception& e) {
        cerr << "Pick up failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handleAdvance() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }

        auto monsters = gameManager->getMonsters();
        vector<string> activeMonsters;

        for (const auto& monster : monsters) {
            if (!monster->isDefeated()) {
                activeMonsters.push_back(monster->getName());
            }
        }

        if (activeMonsters.empty()) {
            throw runtime_error("No active monsters to advance tasks for");
        }

        cout << "Choose a monster to advance task:" << endl;
        for (size_t i = 0; i < activeMonsters.size(); ++i) {
            cout << i + 1 << ". " << activeMonsters[i] << endl;
        }
        cout << "> ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice < 1 || choice > static_cast<int>(activeMonsters.size())) {
            throw runtime_error("Invalid monster choice");
        }

        string monsterName = activeMonsters[choice - 1];
        if (!gameManager->advanceTask(hero->getName(), monsterName)) {
            throw runtime_error("Cannot advance task for " + monsterName + " - requirements not met or wrong location");
        }
        hero->useAction();
    } catch (const exception& e) {
        cerr << "Task advancement failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handleDefeat() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }

        auto monsters = gameManager->getMonsters();
        vector<string> activeMonsters;

        for (const auto& monster : monsters) {
            if (!monster->isDefeated()) {
                activeMonsters.push_back(monster->getName());
            }
        }

        if (activeMonsters.empty()) {
            throw runtime_error("No active monsters to defeat");
        }

        cout << "Choose a monster to defeat:" << endl;
        for (size_t i = 0; i < activeMonsters.size(); ++i) {
            cout << i + 1 << ". " << activeMonsters[i] << endl;
        }
        cout << "> ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice < 1 || choice > static_cast<int>(activeMonsters.size())) {
            throw runtime_error("Invalid monster choice");
        }

        string monsterName = activeMonsters[choice - 1];
        if (!gameManager->defeatMonster(hero->getName(), monsterName)) {
            throw runtime_error("Cannot defeat " + monsterName + " - requirements not met, wrong location, or insufficient items");
        }
        hero->useAction();
    } catch (const exception& e) {
        cerr << "Monster defeat failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handleUsePerk() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }

        auto perkCards = hero->getPerkCards();
        if (perkCards.empty()) {
            throw runtime_error("No perk cards available");
        }

        cout << "Choose a perk card to use:" << endl;
        for (size_t i = 0; i < perkCards.size(); ++i) {
            cout << i + 1 << ". " << perkCards[i]->getCardName() << endl;
        }
        cout << "> ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice < 1 || choice > static_cast<int>(perkCards.size())) {
            throw runtime_error("Invalid perk card choice");
        }

        string cardName = perkCards[choice - 1]->getCardName();
        if (!gameManager->usePerkCard(hero->getName(), cardName)) {
            throw runtime_error("Cannot use perk card " + cardName + " - card effect failed or conditions not met");
        }
    } catch (const exception& e) {
        cerr << "Perk card usage failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handleGuide() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }

        auto villagers = gameManager->getVillagersAtLocation(hero->getCurrentLocation());
        if (villagers.empty()) {
            throw runtime_error("No villagers at current location");
        }

        cout << "Choose a villager to guide:" << endl;
        for (size_t i = 0; i < villagers.size(); ++i) {
            cout << i + 1 << ". " << villagers[i]->getName() << endl;
        }
        cout << "> ";

        int villagerChoice;
        if (!(cin >> villagerChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (villagerChoice < 1 || villagerChoice > static_cast<int>(villagers.size())) {
            throw runtime_error("Invalid villager choice");
        }

        string villagerName = villagers[villagerChoice - 1]->getName();
        auto connected = gameManager->getGameMap()->getConnectedLocations(hero->getCurrentLocation());
        if (connected.empty()) {
            throw runtime_error("No connected locations available");
        }

        cout << "Choose a destination:" << endl;
        for (size_t i = 0; i < connected.size(); ++i) {
            cout << i + 1 << ". " << connected[i] << endl;
        }
        cout << "> ";

        int destChoice;
        if (!(cin >> destChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (destChoice < 1 || destChoice > static_cast<int>(connected.size())) {
            throw runtime_error("Invalid destination choice");
        }

        string dest = connected[destChoice - 1];
        if (!gameManager->guideVillager(hero->getName(), villagerName, dest)) {
            throw runtime_error("Cannot guide villager to " + dest + " - locations not connected or villager cannot be moved");
        }
        hero->useAction();
    } catch (const exception& e) {
        cerr << "Villager guiding failed: " << e.what() << endl;
        throw;
    }
}

void TUI::handleSpecialAction() {
    try {
        auto hero = gameManager->getCurrentHero();
        if (!hero) {
            throw runtime_error("No active hero");
        }
        
        auto* archaeologist = dynamic_cast<Archaeologist*>(hero.get());
        if (!archaeologist) {
            throw runtime_error("This hero has no special ability");
        }

        auto neighbors = gameManager->getGameMap()->getConnectedLocations(hero->getCurrentLocation());
        if (neighbors.empty()) {
            throw runtime_error("No neighboring locations available");
        }
        
        cout << "Choose a location to pick up from:" << endl;
        for (size_t i = 0; i < neighbors.size(); ++i) {
            cout << i + 1 << ". " << neighbors[i] << endl;
        }
        cout << "> ";

        int locChoice;
        if (!(cin >> locChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (locChoice < 1 || locChoice > static_cast<int>(neighbors.size())) {
            throw runtime_error("Invalid location choice");
        }

        string loc = neighbors[locChoice - 1];
        auto items = gameManager->getItemsAtLocation(loc);
        if (items.empty()) {
            throw runtime_error("No items at selected location");
        }

        cout << "Choose an item to pick up:" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }
        cout << "> ";

        int itemChoice;
        if (!(cin >> itemChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid input - please enter a number");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (itemChoice < 1 || itemChoice > static_cast<int>(items.size())) {
            throw runtime_error("Invalid item choice");
        }

        string itemName = items[itemChoice - 1]->getName();
        if (!gameManager->useSpecialAbility(hero->getName(), itemName)) {
            throw runtime_error("Cannot pick up " + itemName + " from adjacent location - item not found or hero's inventory is full");
        }
        hero->useAction();
    } catch (const exception& e) {
        cerr << "Special action failed: " << e.what() << endl;
        throw;
    }
}

void TUI::displayHeader() const {
    cout << "=======================================================================\n";
    cout << "                          H O R R I F I E D\n";
    cout << "=======================================================================\n";
}

void TUI::displayTerrorLevel() const {
    cout << "TERROR LEVEL: " << gameManager->getTerrorLevel() << "/" << Constants::MAX_TERROR_LEVEL << "   ";
    cout << "[";
    for (int i = 0; i < Constants::MAX_TERROR_LEVEL; ++i) {
        cout << (i < gameManager->getTerrorLevel() ? "X" : "-");
    }
    cout << "]\n";
    cout << "-----------------------------------------------------------------------\n";
}

void TUI::displayMonstersInfo() const {
    cout << "MONSTERS:\n";
    for (const auto& monster : gameManager->getMonsters()) {
        cout << "  - " << monster->getName() << " at " << monster->getCurrentLocation();
        if (monster->isDefeated()) {
            cout << " (DEFEATED)";
        } else {
            cout << " | Task: " << monster->getTaskProgress() << "/" << monster->getRequiredTaskProgress();
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------\n";
}

void TUI::displayHeroesInfo() const {
    cout << "HEROES:\n";
    for (const auto& hero : gameManager->getHeroes()) {
        hero->displayInfo();
        cout << "\n";
    }
}

void TUI::displayCurrentPlayerActions() const {
    auto hero = gameManager->getCurrentHero();
    cout << "=======================================================================\n";
    cout << "Current Player: " << gameManager->getCurrentPlayerName() 
         << " (" << hero->getName() << ") | Actions Left: " << hero->getActionsLeft() << "\n";
    cout << "Available commands: move, guide, pickup, advance, defeat, special, perk, help, exit\n";
}

void TUI::displayHelp() const {
    cout << "\n--- HELP ---\n"
         << "move:      Move to a connected location.\n"
         << "guide:     Guide a villager.\n"
         << "pickup:    Pick up an item from your location.\n"
         << "advance:   Advance a monster's task.\n"
         << "defeat:    Attempt to defeat a monster.\n"
         << "special:   Use your hero's special ability.\n"
         << "perk:      Use a perk card from your hand.\n"
         << "map:       Show full map information (items and layout)\n"
         << "help:      Show this help text.\n"
         << "exit:      Quit the game.\n" 
         << "----------------\n";
}

void TUI::clearScreen() const {
    try {
        #ifdef _WIN32
            system("cls");
        #else
            cout << "\033[2J\033[1;1H"; 
        #endif
        cout << flush;
    } catch (const exception& e) {
        cerr << "Failed to clear screen: " << e.what() << endl;
    }
}