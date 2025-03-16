/**
 * @file duel_mode.cpp 
 * @brief Реализация режима дуэли
 */

#include "duel_mode.h"
#include <iostream>
#include <random>
#include <chrono>

DuelMode::DuelMode()
    : GameMode(1, "Дуэль", "Режим поединка один на один", 2, 2)
    , m_winner(nullptr) {
}

bool DuelMode::initialize(const std::vector<PlayerPtr>& players) {
    if (!GameMode::initialize(players)) {
        return false;
    }

    // Случайно определяем, кто ходит первым
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<unsigned int>(seed));
    std::uniform_int_distribution<> dis(0, 1);
    
    m_currentTurn = dis(gen);
    
    std::cout << "Первым ходит: " << getCurrentPlayer()->getName() << "\n";
    
    return true;
}

bool DuelMode::start() {
    onGameStart();

    while (!m_isFinished) {
        // Получаем текущего игрока и противника
        PlayerPtr currentPlayer = getCurrentPlayer();
        PlayerPtr opponent = getOpponent();

        if (!currentPlayer || !opponent) {
            std::cerr << "Ошибка: неверное состояние игроков\n";
            break;
        }

        // Отображаем состояние игры
        displayGameState();

        // Игрок делает ход
        if (!executeTurn(currentPlayer, opponent)) {
            break;
        }

        // Проверяем условия завершения
        if (checkEndCondition()) {
            break;
        }

        // Переходим к следующему ходу
        nextTurn();
    }

    onGameEnd();
    return true;
}

bool DuelMode::executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) {
    // Выполняем ход игрока
    if (!currentPlayer->takeTurn(opponent.get())) {
        std::cerr << "Ошибка: не удалось выполнить ход игрока " 
                  << currentPlayer->getName() << "\n";
        return false;
    }

    return true;
}

PlayerPtr DuelMode::getOpponent() const {
    if (m_players.size() != 2) {
        return nullptr;
    }

    // Возвращаем противника текущего игрока
    int opponentIndex = (m_currentTurn % 2 == 0) ? 1 : 0;
    return m_players[opponentIndex];
}

bool DuelMode::checkEndCondition() {
    // Проверяем, остался ли только один живой игрок
    int aliveCount = 0;
    PlayerPtr lastAlive = nullptr;

    for (const auto& player : m_players) {
        if (player->isAlive()) {
            aliveCount++;
            lastAlive = player;
        }
    }

    // Если остался только один живой игрок, он победитель
    if (aliveCount == 1) {
        m_winner = lastAlive;
        m_isFinished = true;
        return true;
    }

    // Если все игроки мертвы (ничья)
    if (aliveCount == 0) {
        m_winner = nullptr;
        m_isFinished = true;
        return true;
    }

    // Проверяем лимит ходов
    const int MAX_TURNS = 50;
    if (m_currentTurn >= MAX_TURNS) {
        // В случае лимита ходов победителем считается игрок с большим здоровьем
        if (m_players[0]->getHealth() > m_players[1]->getHealth()) {
            m_winner = m_players[0];
        }
        else if (m_players[1]->getHealth() > m_players[0]->getHealth()) {
            m_winner = m_players[1];
        }
        else {
            m_winner = nullptr; // Ничья
        }
        m_isFinished = true;
        return true;
    }

    return false;
}

void DuelMode::displayResults() const {
    std::cout << "\n=== Результаты дуэли ===\n";
    
    if (m_winner) {
        std::cout << "Победитель: " << m_winner->getName() << "\n";
    }
    else {
        std::cout << "Ничья!\n";
    }

    GameMode::displayResults();
}

void DuelMode::displayHelp() const {
    GameMode::displayHelp();
    std::cout << "Дополнительные команды режима дуэли:\n"
              << "attack <index> <target> - атаковать персонажем\n"
              << "play <index> <target> - сыграть карту\n"
              << "end - закончить ход\n\n";
}