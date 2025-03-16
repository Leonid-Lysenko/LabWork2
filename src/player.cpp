/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


#include "player.h"
#include <iostream>

Player::Player(int id, std::string name, int maxHealth, int maxMana, int gold)
: m_id(id), m_name(name), m_health(maxHealth), m_maxHealth(maxHealth),
  m_mana(maxMana), m_maxMana(maxMana), m_gold(gold) {}

void Player::drawCard(int count) {
    for (int i = 0; i < count && !m_deck.empty(); i++) {
        m_hand.push_back(m_deck.back());
        m_deck.pop_back();
    }
}

bool Player::playCard(int index, Player* target) {
    if (index >= 0 && index < m_hand.size()) {
        auto card = m_hand[index];
        if (card->play(this, target)) {
            m_hand.erase(m_hand.begin() + index);
            return true;
        }
    }
    return false;
}

void Player::updateEffects() {
    // Обновляем эффекты и удаляем истекшие
    auto it = m_effects.begin();
    while (it != m_effects.end()) {
        if (!(*it)->update()) {
            // Эффект закончился, удаляем его
            (*it)->remove(nullptr);
            it = m_effects.erase(it);
        } else {
            // Применяем периодические эффекты
            if ((*it)->isPeriodicEffect()) {
                (*it)->apply(nullptr);
            }
            ++it;
        }
    }
}

void Player::startTurn() {
    // Увеличиваем ману в начале хода
    modifyMana(1);
    
    // Берем карту
    drawCard(1);
    
    // Активируем все карты на поле
    for (auto& character : m_field) {
        character->onTurnStart();
    }
    
    // Обновляем эффекты
    updateEffects();
    
    std::cout << m_name << " начинает ход!" << std::endl;
}

void Player::endTurn() {
    // Завершающие действия для всех карт на поле
    for (auto& character : m_field) {
        character->onTurnEnd();
    }
    
    // Обновляем эффекты в конце хода
    updateEffects();
    
    std::cout << m_name << " заканчивает ход." << std::endl;
}

bool Player::update() {
    // Обновление состояния игрока
    updateEffects();
    
    // Проверка, жив ли игрок
    return isAlive();
}

void Player::displayStatus() const {
    std::cout << "=== Игрок: " << m_name << " ===\n";
    std::cout << "Здоровье: " << m_health << "/" << m_maxHealth << "\n";
    std::cout << "Мана: " << m_mana << "/" << m_maxMana << "\n";
    std::cout << "Золото: " << m_gold << "\n";
    
    std::cout << "Карты в руке (" << m_hand.size() << "):\n";
    for (size_t i = 0; i < m_hand.size(); ++i) {
        std::cout << i + 1 << ". " << m_hand[i]->toString() << "\n";
    }
    
    std::cout << "Карты на поле (" << m_field.size() << "):\n";
    for (size_t i = 0; i < m_field.size(); ++i) {
        std::cout << i + 1 << ". " << m_field[i]->toString() << "\n";
    }
    
    std::cout << "Карт в колоде: " << m_deck.size() << "\n";
}
