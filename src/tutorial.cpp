/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#include "tutorial.h"
#include <iostream>

Tutorial::Tutorial() {
    initializeLessons();
}

void Tutorial::initializeLessons() {
    m_lessons = {
        {"Основы", [](Player* p) { return basicLesson(p); }},
        {"Бой", [](Player* p) { return combatLesson(p); }},
        {"Эффекты", [](Player* p) { return effectsLesson(p); }}
    };
}

bool Tutorial::start() {
    for (const auto& lesson : m_lessons) {
        std::cout << "\n=== " << lesson.first << " ===\n";
       if (!lesson.second(m_player.get())) {
            return false;
        }
    }
    return true;
}

bool Tutorial::basicLesson(Player* player) {
    std::cout << "Урок 1: Базовые механики\n";
    std::cout << "- Каждый ход вы получаете ману\n";
    std::cout << "- Используйте ману для розыгрыша карт\n";
    
    // Даем простую карту и просим разыграть
    auto card = CardFactory::getInstance().createCard(1);
    player->addCardToHand(card);
    
    return true;
}

bool Tutorial::combatLesson(Player* player) {
    std::cout << "Урок 2: Боевые механики\n";
    std::cout << "- Существа могут атаковать после хода разыгрывания\n";
    std::cout << "- Атакуйте существ противника или самого противника\n";
    
    return true;
}

bool Tutorial::effectsLesson(Player* player) {
    std::cout << "Урок 3: Эффекты\n";
    std::cout << "- Карты могут накладывать эффекты\n";
    std::cout << "- Эффекты действуют определенное количество ходов\n";
    
    return true;
}
