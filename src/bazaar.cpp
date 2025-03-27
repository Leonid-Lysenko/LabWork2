#include "bazaar.h"
#include "card_factory.h"
#include <iostream>
#include <limits>

Bazaar::Bazaar() : m_gold(0) {
    refreshStock();
}

void Bazaar::refreshStock() {
    m_stock.clear();
    auto& factory = CardFactory::getInstance();
    
    // Добавляем 6 случайных карт в магазин
    for(int i = 0; i < 6; i++) {
        if (auto card = factory.createRandomCard()) {
            m_stock.push_back(card);
        }
    }
}

bool Bazaar::buyCard(Player* player, int index) {
    if (index < 0 || static_cast<size_t>(index) >= m_stock.size()) {
        std::cout << "Invalid card index!\n";
        return false;
    }

    auto card = m_stock[index];
    if (!card) {
        std::cout << "Selected card is invalid!\n";
        return false;
    }

    if (player->getGold() >= card->getCost()) {
        player->modifyGold(-card->getCost());
        player->addCardToDeck(card);
        m_stock.erase(m_stock.begin() + index);
        m_gold += card->getCost();
        std::cout << "Card purchased successfully!\n";
        return true;
    }

    std::cout << "Not enough gold to buy this card!\n";
    return false;
}

bool Bazaar::sellCard(Player* player, int index) {
    if (auto card = player->removeCardFromDeck(index)) {
        int value = card->getCost() / 2;
        player->modifyGold(value);
        m_gold -= value;
        std::cout << "Card sold for " << value << " gold!\n";
        return true;
    }
    
    std::cout << "Failed to sell card!\n";
    return false;
}

void Bazaar::displayWelcomeMessage() const {
    std::cout << "\n=== Welcome to the Bazaar! ===\n";
    std::cout << "Your gold: " << (m_player ? m_player->getGold() : 0) << "\n";
    std::cout << "Bazaar gold: " << m_gold << "\n\n";
}

void Bazaar::displayMenu() const {
    std::cout << "1. View available cards\n";
    std::cout << "2. Buy a card\n";
    std::cout << "3. Sell a card\n";
    std::cout << "4. View your deck\n";
    std::cout << "5. Exit bazaar\n";
    std::cout << "Enter your choice: ";
}

int Bazaar::getMenuChoice() const {
    int choice;
    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    return choice;
}

bool Bazaar::processMenuChoice(int choice) {
    if (!m_player) return false;

    switch (choice) {
        case 1: { // View cards
            std::cout << "\n=== Available Cards ===\n";
            for (size_t i = 0; i < m_stock.size(); ++i) {
                std::cout << i << ". " << m_stock[i]->getName() 
                          << " (Cost: " << m_stock[i]->getCost() << ")\n";
            }
            std::cout << "\n";
            break;
        }
        case 2: { // Buy card
            std::cout << "\n=== Available Cards ===\n";
            for (size_t i = 0; i < m_stock.size(); ++i) {
                std::cout << i << ". " << m_stock[i]->getName() 
                          << " (Cost: " << m_stock[i]->getCost() << ")\n";
            }
            std::cout << "Enter card number to buy (or -1 to cancel): ";
            int index = getMenuChoice();
            
            if (index != -1) {
                buyCard(m_player.get(), index);
            }
            break;
        }
        case 3: { // Sell card
            const auto& deck = m_player->getDeck();
            if (deck.empty()) {
                std::cout << "Your deck is empty!\n";
                break;
            }

            std::cout << "\n=== Your Deck ===\n";
            for (size_t i = 0; i < deck.size(); ++i) {
                std::cout << i << ". " << deck[i]->getName() 
                          << " (Value: " << deck[i]->getCost() / 2 << ")\n";
            }

            std::cout << "Enter card number to sell (or -1 to cancel): ";
            int index = getMenuChoice();
            
            if (index != -1) {
                sellCard(m_player.get(), index);
            }
            break;
        }
        case 4: { // View deck
            if (!m_player) break;

            const auto& deck = m_player->getDeck();
            std::cout << "\n=== Your Deck (" << deck.size() << " cards) ===\n";
            
            for (const auto& card : deck) {
                std::cout << "- " << card->getName() << "\n";
            }
            std::cout << "\n";
            break;
        }
        case 5: // Exit
            return false;
        default:
            std::cout << "Invalid choice!\n";
    }
    return true;
}
