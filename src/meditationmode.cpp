/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file meditation_mode.cpp
 * @brief Реализация режима медитации для экспериментов с картами
 */

#include "meditation_mode.h"
#include <iostream>
#include <sstream>
#include "card_factory.h"

MeditationMode::MeditationMode()
    : GameMode(3, "Медитация", "Режим для спокойной тренировки и экспериментов", 1, 1)
    , m_infiniteMana(false)
    , m_infiniteHealth(false)
    , m_unlimitedCards(false) {
}

bool MeditationMode::initialize(const std::vector<PlayerPtr>& players) {
    if (!GameMode::initialize(players)) {
        return false;
    }

    // Спрашиваем игрока о желаемых настройках режима
    setupModeOptions();
    
    return true;
}

void MeditationMode::setupModeOptions() {
    std::cout << "\n=== Настройки режима медитации ===\n";
    
    char choice;
    
    std::cout << "Включить бесконечную ману? (y/n): ";
    std::cin >> choice;
    m_infiniteMana = (choice == 'y' || choice == 'Y');
    
    std::cout << "Включить бесконечное здоровье? (y/n): ";
    std::cin >> choice;
    m_infiniteHealth = (choice == 'y' || choice == 'Y');
    
    std::cout << "Включить неограниченные карты? (y/n): ";
    std::cin >> choice;
    m_unlimitedCards = (choice == 'y' || choice == 'Y');
    
    std::cin.ignore();

    // Применяем настройки к игроку
    applyModeSettings();
}

void MeditationMode::applyModeSettings() {
    if (m_players.empty()) {
        return;
    }

    PlayerPtr player = m_players[0];

    if (m_infiniteMana) {
        player->setMaxMana(999);
        player->modifyMana(999);
    }

    if (m_infiniteHealth) {
        player->setMaxHealth(999);
        player->modifyHealth(999);
    }

    if (m_unlimitedCards) {
        // Создаем расширенную колоду со всеми доступными картами
        auto& factory = CardFactory::getInstance();
        Cards fullCollection = factory.createFullCollection();
        player->setDeck(fullCollection);
        
        // Даем возможность взять больше карт в руку
        player->drawCard(10);
    }
}

bool MeditationMode::start() {
    onGameStart();

    while (!m_isFinished) {
        // Отображаем текущее состояние
        displayGameState();

        // Обрабатываем команду игрока
        std::string command = getPlayerCommand();
        if (!handleCommand(command)) {
            continue;
        }

        // Обновляем состояние игры
        update();

        // В режиме медитации автоматически восстанавливаем ресурсы
        refreshResources();
    }

    onGameEnd();
    return true;
}

void MeditationMode::refreshResources() {
    if (m_players.empty()) {
        return;
    }

    PlayerPtr player = m_players[0];

    if (m_infiniteMana) {
        player->modifyMana(999);
    }

    if (m_infiniteHealth) {
        player->modifyHealth(999);
    }

    if (m_unlimitedCards && player->getHand().size() < 10) {
        player->drawCard(10 - player->getHand().size());
    }
}

bool MeditationMode::handleCommand(const std::string& command) {
    // Сначала проверяем базовые команды
    if (GameMode::handleCommand(command)) {
        return true;
    }

    // Специальные команды режима медитации
    if (command == "refresh") {
        refreshResources();
        std::cout << "Ресурсы восстановлены.\n";
        return true;
    }
    else if (command == "draw") {
        m_players[0]->drawCard(1);
        std::cout << "Взята карта.\n";
        return true;
    }
    else if (command == "reset") {
        resetGameState();
        std::cout << "Состояние игры сброшено.\n";
        return true;
    }
    else if (command.substr(0, 4) == "test") {
        // Разбираем команду тестирования
        handleTestCommand(command.substr(5));
        return true;
    }

    return false;
}

void MeditationMode::handleTestCommand(const std::string& args) {
    std::istringstream iss(args);
    std::string testType;
    iss >> testType;

    if (testType == "combo") {
        // Тестирование комбинации карт
        testCardCombo();
    }
    else if (testType == "effect") {
        // Тестирование эффектов
        int effectId;
        if (iss >> effectId) {
            testEffect(effectId);
        }
    }
    else if (testType == "damage") {
        // Тестирование урона
        int damage;
        if (iss >> damage) {
            testDamage(damage);
        }
    }
}

void MeditationMode::testCardCombo() {
    std::cout << "Тестирование комбинации карт...\n";
    // Здесь логика тестирования комбо
}

void MeditationMode::testEffect(int effectId) {
    std::cout << "Тестирование эффекта #" << effectId << "...\n";
    // Здесь логика тестирования эффекта
}

void MeditationMode::testDamage(int damage) {
    std::cout << "Тестирование урона " << damage << "...\n";
    // Здесь логика тестирования урона
}

void MeditationMode::resetGameState() {
    // Сбрасываем состояние игры к начальному
    if (!m_players.empty()) {
        PlayerPtr player = m_players[0];
        
        // Очищаем поле
                // Очищаем поле
        player->clearBoard();
        
        // Сбрасываем здоровье и ману
        player->setHealth(20);
        player->setMana(0);
        
        // Очищаем руку и колоду
        player->clearHand();
        player->clearDeck();
        
        // Если включены настройки бесконечных ресурсов, применяем их снова
        if (m_infiniteMana) {
            player->setMaxMana(999);
            player->modifyMana(999);
        }
        
        if (m_infiniteHealth) {
            player->setMaxHealth(999);
            player->modifyHealth(999);
        }
        
        if (m_unlimitedCards) {
            // Восстанавливаем полную коллекцию карт
            CardFactory& factory = CardFactory::getInstance();
            Cards fullCollection = factory.createFullCollection();
            player->setDeck(fullCollection);
            player->drawCard(10);
        }
    }
    
    std::cout << "Состояние игры сброшено.\n";
}
