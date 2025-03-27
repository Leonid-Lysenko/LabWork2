#include "human_player.h"
#include <iostream>

bool HumanPlayer::takeTurn(Player* opponent) {
    displayStatus();
    
    while (true) {
        std::cout << "\nВаш ход (help для помощи): ";
        std::string cmd;
        std::getline(std::cin, cmd);
        
        if (cmd == "end") break;
        else if (cmd == "help") displayHelp();
        else if (cmd.substr(0,4) == "play") {
            int index = std::stoi(cmd.substr(5));
            playCard(index, opponent);
        }
        // ... другие команды
    }
    return true;
}

void HumanPlayer::displayHelp() const {
    // Реализация метода
    std::cout << "=== Human Player Help ===\n";
    // ... ваш код помощи для игрока
}
