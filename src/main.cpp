/**
 * @file main.cpp
 * @brief Main entry point for the Card Heroes Battle game
 */

#include <iostream>
#include <memory>
#include <vector>
#include "game_mode.h"
#include "duelmmode.h"
#include "trainingmode.h"
#include "meditatiomode.h"
#include "human_player.h"
#include "ai_player.h"
#include "card_factory.h"
#include "tutorial.h"
#include "bazaar.h"

void displayMenu() {
    std::cout << "\nCard Heroes Battle\n";
    std::cout << "==================\n";
    std::cout << "1. Duel Mode\n";
    std::cout << "2. Training Mode\n";
    std::cout << "3. Meditation Mode\n";
    std::cout << "4. Tutorial\n";
    std::cout << "5. Bazaar\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose your option (1-6): ";
}

int main() {
    // Initialize card factory
    CardFactory::getInstance().initialize();

    // Create player
    std::shared_ptr<HumanPlayer> humanPlayer = std::make_shared<HumanPlayer>(
        1, "Player", 30, 10, 100
    );

    // Create AI opponent with medium difficulty
    std::shared_ptr<AIPlayer> aiPlayer = std::make_shared<AIPlayer>(
        2, "AI", DifficultyLevel::Medium, 30, 10, 100
    );

    bool running = true;
    while (running) {
        displayMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        std::shared_ptr<GameMode> gameMode;
        std::vector<PlayerPtr> players;

        switch (choice) {
            case 1: { // Duel Mode
                players = {humanPlayer, aiPlayer};
                gameMode = std::make_shared<DuelMode>();
                break;
            }
            case 2: { // Training Mode
                players = {humanPlayer};
                gameMode = std::make_shared<TrainingMode>();
                break;
            }
            case 3: { // Meditation Mode
                players = {humanPlayer};
                gameMode = std::make_shared<MeditationMode>();
                break;
            }
            case 4: { // Tutorial
                Tutorial tutorial(humanPlayer);
                tutorial.start();
                continue;
            }
            case 5: { // Bazaar
                Bazaar bazaar(humanPlayer);
                bazaar.enter();
                continue;
            }
            case 6: // Exit
                running = false;
                break;
            default:
                std::cout << "Invalid choice!\n";
                continue;
        }

        if (gameMode) {
            // Initialize and start the game mode
            if (gameMode->initialize(players)) {
                gameMode->start();
                gameMode->onGameEnd();
            }
        }
    }

    std::cout << "Thanks for playing Card Heroes Battle!\n";
    return 0;
}