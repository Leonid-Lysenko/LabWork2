/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file game_mode.cpp
 * @brief Реализация базового класса игровых режимов
 */

#include "game_mode.h"
#include <iostream>
#include <algorithm>

GameMode::GameMode(int id, const std::string& name, const std::string& description,
                   int minPlayers, int maxPlayers)
    : m_id(id)
    , m_name(name)
    , m_description(description)
    , m_minPlayers(minPlayers)
    , m_maxPlayers(maxPlayers)
    , m_isFinished(false)
    , m_currentTurn(0) {
}

bool GameMode::initialize(const std::vector<PlayerPtr>& players) {
    // Проверяем количество игроков
    if (players.size() < m_minPlayers || players.size() > m_maxPlayers) {
        std::cerr << "Ошибка: неверное количество игроков для режима " 
                  << m_name << std::endl;
        return false;
    }

    // Инициализируем список игроков
    m_players = players;
    m_currentTurn = 0;
    m_isFinished = false;

    // Инициализируем состояние каждого игрока
    for (auto& player : m_players) {
        // Перемешиваем колоду
        player->shuffleDeck();
        
        // Раздаем начальные карты
        player->drawCard(getInitialHandSize());
        
        // Сбрасываем характеристики
        player->resetStats();
    }

    return true;
}

bool GameMode::update() {
    // Проверяем условия завершения режима
    if (checkEndCondition()) {
        m_isFinished = true;
    }

    // Обновляем состояние всех игроков
    for (auto& player : m_players) {
        player->update();
    }

    return true;
}

const std::vector<PlayerPtr>& GameMode::getPlayers() const {
    return m_players;
}

bool GameMode::addPlayer(PlayerPtr player) {
    // Проверяем возможность добавления игрока
    if (!player || m_players.size() >= m_maxPlayers) {
        return false;
    }

    // Проверяем, не добавлен ли уже этот игрок
    auto it = std::find_if(m_players.begin(), m_players.end(),
        [&player](const PlayerPtr& p) { return p->getId() == player->getId(); });
    
    if (it != m_players.end()) {
        return false;
    }

    m_players.push_back(player);
    return true;
}

bool GameMode::removePlayer(int index) {
    if (index < 0 || index >= static_cast<int>(m_players.size())) {
        return false;
    }

    m_players.erase(m_players.begin() + index);
    return true;
}

PlayerPtr GameMode::getCurrentPlayer() const {
    if (m_players.empty()) {
        return nullptr;
    }
    return m_players[m_currentTurn % m_players.size()];
}

void GameMode::nextTurn() {
    // Завершаем текущий ход
    if (auto currentPlayer = getCurrentPlayer()) {
        currentPlayer->endTurn();
    }

    // Переходим к следующему ходу
    m_currentTurn++;

    // Начинаем новый ход
    if (auto nextPlayer = getCurrentPlayer()) {
        nextPlayer->startTurn();
    }
}

int GameMode::getCurrentTurn() const {
    return m_currentTurn;
}

bool GameMode::isFinished() const {
    return m_isFinished;
}

int GameMode::getInitialHandSize() const {
    // По умолчанию игроки начинают с 3 картами
    return 3;
}

std::string GameMode::getName() const {
    return m_name;
}

std::string GameMode::getDescription() const {
    return m_description;
}

void GameMode::displayGameState() const {
    std::cout << "\n=== Ход " << m_currentTurn + 1 << " ===\n";
    std::cout << "Текущий режим: " << m_name << "\n";
    
    for (const auto& player : m_players) {
        std::cout << "\nИгрок: " << player->getName() 
                  << " [HP: " << player->getHealth() << "/" << player->getMaxHealth()
                  << ", Мана: " << player->getMana() << "/" << player->getMaxMana() 
                  << "]\n";
        
        std::cout << "Карт в колоде: " << player->getDeck().size() 
                  << ", в руке: " << player->getHand().size() 
                  << ", на поле: " << player->getField().size() << "\n";
    }
    std::cout << "\n";
}

bool GameMode::handleCommand(const std::string& command) {
    // Базовая обработка общих команд
    if (command == "help") {
        displayHelp();
        return true;
    }
    else if (command == "status") {
        displayGameState();
        return true;
    }
    else if (command == "quit") {
        m_isFinished = true;
        return true;
    }
    
    return false; // Неизвестная команда
}

void GameMode::displayHelp() const {
    std::cout << "\nДоступные команды:\n"
              << "help - показать это сообщение\n"
              << "status - показать текущее состояние игры\n"
              << "quit - завершить игру\n\n";
}

void GameMode::onGameStart() {
    // Вызывается при начале игры
    std::cout << "\n=== Начало игры: " << m_name << " ===\n"
              << m_description << "\n\n";
}

void GameMode::onGameEnd() {
    // Вызывается при завершении игры
    std::cout << "\n=== Игра завершена ===\n"
              << "Режим: " << m_name << "\n"
              << "Количество ходов: " << m_currentTurn << "\n\n";
    
    displayResults();
}

void GameMode::displayResults() const {
    // Базовая реализация вывода результатов
    std::cout << "Итоговое состояние игроков:\n";
    for (const auto& player : m_players) {
        std::cout << player->getName() << ": "
                  << (player->isAlive() ? "Жив" : "Погиб")
                  << " (HP: " << player->getHealth() << ")\n";
    }
}
