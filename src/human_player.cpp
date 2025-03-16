/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#include "human_player.h"

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
