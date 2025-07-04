#include "GameManager.hpp"
#include "TUI.hpp"
#include <memory>
#include <iostream>

using namespace std ; 

int main() {
    try {
        auto gameManager = make_shared<GameManager>();
        TUI tui(gameManager);
        
        tui.run();
        
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}