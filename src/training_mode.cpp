/**
 * @file training_mode.cpp
 * @brief Реализация режима тренировки
 */

#include "trainingmode.h"
#include "ai_player.h"
#include <iostream>

TrainingMode::TrainingMode()
    : GameMode(2, "Тренировка", "Режим для изучения механик игры", 1, 1)
    , m_currentLesson(0)
    , m_totalLessons(5)
    , m_lessonCompleted(false) {
    initializeLessons();
    
    // Инициализация целей
    m_objectives = {false, false, false, false, false, false, false, false, false, false};
}

TrainingMode::TrainingMode(int id, const std::string& name, const std::string& description)
    : GameMode(id, name, description, 1, 1)
    , m_currentLesson(0)
    , m_totalLessons(5)
    , m_lessonCompleted(false) {
    initializeLessons();
    
    // Инициализация целей
    m_objectives = {false, false, false, false, false, false, false, false, false, false};
}

void TrainingMode::initializeLessons() {
    // Инициализируем уроки
    m_lessons = {
        {"Основы", "Изучение базовых механик игры"},
        {"Карты существ", "Изучение механик существ и боя"},
        {"Магия", "Изучение магических карт и заклинаний"},
        {"Эффекты", "Изучение эффектов и статусов"},
        {"Продвинутые тактики", "Изучение сложных игровых механик"}
    };
}

bool TrainingMode::start() {
    onGameStart();

    while (!m_isFinished && m_currentLesson < m_totalLessons) {
        // Отображаем текущий урок
        displayCurrentLesson();

        // Создаем тренировочного противника если нужно
        setupTrainingOpponent();

        // Выполняем урок
        executeLesson();

        // Проверяем выполнение урока
        if (checkLessonCompletion()) {
            m_currentLesson++;
        }
    }

    onGameEnd();
    return true;
}

void TrainingMode::displayCurrentLesson() const {
    const auto& lesson = m_lessons[m_currentLesson];
    
    std::cout << "\n=== Урок " << (m_currentLesson + 1) << "/" << m_totalLessons 
              << ": " << lesson.first << " ===\n"
              << lesson.second << "\n\n";

    // Выводим конкретные инструкции для каждого урока
    switch (m_currentLesson) {
        case 0:
            std::cout << "Базовые действия:\n"
                      << "1. Возьмите карту\n"
                      << "2. Используйте ману для розыгрыша карт\n"
                      << "3. Изучите интерфейс\n";
            break;

        case 1:
            std::cout << "Механики существ:\n"
                      << "1. Выставите существо на поле\n"
                      << "2. Научитесь атаковать\n"
                      << "3. Изучите характеристики существ\n";
            break;

        case 2:
            std::cout << "Магические карты:\n"
                      << "1. Используйте заклинание урона\n"
                      << "2. Используйте заклинание лечения\n"
                      << "3. Комбинируйте заклинания\n";
            break;

        case 3:
            std::cout << "Эффекты и статусы:\n"
                      << "1. Наложите положительный эффект\n"
                      << "2. Наложите отрицательный эффект\n"
                      << "3. Изучите длительность эффектов\n";
            break;

        case 4:
            std::cout << "Продвинутые тактики:\n"
                      << "1. Используйте комбо карт\n"
                      << "2. Примените особые способности\n"
                      << "3. Выполните сложную боевую задачу\n";
            break;
    }
}

void TrainingMode::setupTrainingOpponent() {
    // Создаем ИИ противника для конкретных уроков
    if (m_currentLesson >= 1 && m_players.size() == 1) {
        auto aiPlayer = std::make_shared<AIPlayer>(
            999, "Тренер", DifficultyLevel::Easy, 20, 10, 100
        );
        
        // Настраиваем специальную колоду для тренировки
        setupTrainingDeck(aiPlayer);
        m_players.push_back(aiPlayer);
    }
}

void TrainingMode::setupTrainingDeck(PlayerPtr player) {
    auto& factory = CardFactory::getInstance();
    Cards trainingDeck;

    // Формируем специальную колоду в зависимости от урока
    switch (m_currentLesson) {
        case 1: { // Урок существ
            // Добавляем базовых существ для обучения
            trainingDeck.push_back(factory.createCharacterCard("Тренировочный воин", 2, 2, 2));
            trainingDeck.push_back(factory.createCharacterCard("Тренировочный лучник", 1, 3, 1));
            break;
        }
        case 2: { // Урок магии
            // Добавляем простые заклинания
            trainingDeck.push_back(factory.createSpellCard("Тренировочный удар", 1, 2));
            trainingDeck.push_back(factory.createSpellCard("Тренировочное лечение", 1, 2, SpellType::Healing));
            break;
        }
        case 3: { // Урок эффектов
            // Добавляем карты с эффектами
            trainingDeck.push_back(factory.createMagicCard("Тренировочное усиление", 2, "Бафф атаки", MagicType::Enhancement));
            trainingDeck.push_back(factory.createMagicCard("Тренировочное ослабление", 2, "Дебафф защиты", MagicType::Curse));
            break;
        }
        case 4: { // Урок продвинутых тактик
            // Добавляем сложные карты для комбо
            trainingDeck.push_back(factory.createCharacterCard("Тренировочный маг", 3, 2, 3));
            trainingDeck.push_back(factory.createSpellCard("Тренировочный взрыв", 3, 4));
            break;
        }
    }

    // Дублируем карты для обеспечения стабильности колоды
    Cards fullDeck;
    for (int i = 0; i < 5; ++i) {
        fullDeck.insert(fullDeck.end(), trainingDeck.begin(), trainingDeck.end());
    }

    player->setDeck(fullDeck);
}

bool TrainingMode::executeLesson() {
    // Получаем игрока
    PlayerPtr player = m_players[0];
    
    // Выполняем специфичные для урока действия
    switch (m_currentLesson) {
        case 0: { // Базовые механики
            // Показываем обучающие подсказки
            std::cout << "\nОбучающая подсказка:\n";
            std::cout << "Для розыгрыша карты введите 'play <номер_карты>'\n";
            
            // Даем игроку выполнить базовые действия
            while (!m_lessonCompleted) {
                displayGameState();
                if (handleCommand(getPlayerCommand())) {
                    checkLessonObjectives();
                }
            }
            break;
        }

        case 1: { // Урок существ
            // Показываем механики боя
            std::cout << "\nОбучающая подсказка:\n";
            std::cout << "Для атаки введите 'attack <номер_существа> <цель>'\n";
            
            while (!m_lessonCompleted) {
                displayGameState();
                if (handleCommand(getPlayerCommand())) {
                    checkLessonObjectives();
                }
            }
            break;
        }

        case 2: // Урок магии
        case 3: // Урок эффектов
        case 4: { // Продвинутые тактики
            // Более сложные уроки с полноценными боями
            while (!m_lessonCompleted && !m_isFinished) {
                // Ход игрока
                displayGameState();
                if (!executeTurn(player, m_players[1])) {
                    break;
                }

                // Проверяем выполнение целей урока
                checkLessonObjectives();

                // Ход ИИ (если урок требует противника)
                if (m_players.size() > 1 && !m_lessonCompleted) {
                    if (!executeTurn(m_players[1], player)) {
                        break;
                    }
                }
            }
            break;
        }
    }

    return true;
}

bool TrainingMode::checkLessonCompletion() {
    // Проверяем выполнение целей урока
    switch (m_currentLesson) {
        case 0: // Базовые механики
            return m_objectives.hasPlayedCard && 
                   m_objectives.hasViewedHelp;

        case 1: // Урок существ
            return m_objectives.hasPlayedCreature && 
                   m_objectives.hasAttackedWithCreature;

        case 2: // Урок магии
            return m_objectives.hasUsedDamageSpell && 
                   m_objectives.hasUsedHealingSpell;

        case 3: // Урок эффектов
            return m_objectives.hasAppliedBuff && 
                   m_objectives.hasAppliedDebuff;

        case 4: // Продвинутые тактики
            return m_objectives.hasCompletedCombo && 
                   m_objectives.hasWonTrainingBattle;

        default:
            return false;
    }
}

void TrainingMode::checkLessonObjectives() {
    // В зависимости от текущего урока проверяем различные цели
    switch (m_currentTurn) {
        case 0: // Проверяем цели базового урока
            if (!m_objectives.hasPlayedCard && !m_players[0]->getHand().empty()) {
                m_objectives.hasPlayedCard = true;
            }
            break;

        case 1: // Проверяем цели урока существ
            if (!m_objectives.hasPlayedCreature && !m_players[0]->getField().empty()) {
                m_objectives.hasPlayedCreature = true;
            }
            break;

        // ... другие проверки целей ...
    }

    // Обновляем состояние завершения урока
    m_lessonCompleted = checkLessonCompletion();
}

std::string TrainingMode::getPlayerCommand() {
    std::string command;
    std::cout << "\nВведите команду (help для списка команд): ";
    std::getline(std::cin, command);
    return command;
}

bool TrainingMode::handleCommand(const std::string& command) {
    // Сначала проверяем базовые команды
    if (GameMode::handleCommand(command)) {
        return true;
    }
    
    // Специальные команды режима тренировки
    if (command == "next") {
        if (m_lessonCompleted) {
            m_currentLesson++;
            return true;
        }
        std::cout << "Сначала нужно завершить текущий урок!\n";
        return false;
    }
    else if (command == "repeat") {
        m_lessonCompleted = false;
        setupTrainingOpponent();
        return true;
    }
    else if (command == "hint") {
        displayCurrentLesson();
        return true;
    }
    
    // Обработка игровых команд
    return false;
}

void TrainingMode::displayHelp() const {
    GameMode::displayHelp();
    std::cout << "\nКоманды обучения:\n"
              << "next - перейти к следующему уроку\n"
              << "repeat - повторить текущий урок\n"
              << "hint - получить подсказку\n";
}

bool TrainingMode::executeTurn(PlayerPtr currentPlayer, PlayerPtr opponent) {
    // Выполняем ход в зависимости от типа игрока
    return currentPlayer->takeTurn(opponent.get());
}

bool TrainingMode::checkEndCondition() {
    // Проверяем условия завершения режима
    return m_currentLesson >= m_totalLessons || m_isFinished;
}

void TrainingMode::onGameEnd() {
    if (m_currentLesson >= m_totalLessons) {
        std::cout << "\n=== Поздравляем! ===\n"
                  << "Вы успешно завершили все уроки обучения!\n"
                  << "Теперь вы готовы к настоящим сражениям.\n\n";
    }
    else {
        std::cout << "\n=== Обучение прервано ===\n"
                  << "Вы можете вернуться к обучению в любое время.\n\n";
    }
}