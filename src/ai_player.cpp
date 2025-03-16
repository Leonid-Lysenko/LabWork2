/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#include "ai_player.h"
#include "spell_card.h"
bool AIPlayer::takeTurn(Player* opponent) {
    // Простая ИИ логика:
    
    // 1. Пытаемся разыграть существ по мане
    for (int i = 0; i < m_hand.size(); i++) {
        auto card = m_hand[i];
        if (card->getType() == CardType::Character && 
            card->getManaCost() <= m_mana) {
            playCard(i, this);
        }
    }
    
    // 2. Атакуем существами противника
    for (auto& character : m_field) {
        if (character->canAttack()) {
            // Выбираем лучшую цель
            auto target = selectBestTarget(opponent);
            if (target)
                character->attack(target.get());
        }
    }
    
    // 3. Используем заклинания
    for (int i = 0; i < m_hand.size(); i++) {
        auto card = m_hand[i];
        if (card->getType() == CardType::Spell && 
            card->getManaCost() <= m_mana) {
            playCard(i, opponent);
        }
    }
    
    return true;
}

CharacterCardPtr AIPlayer::selectBestTarget(Player* opponent) {
    // Простой выбор цели - атакуем самого слабого
    CharacterCardPtr best = nullptr;
    int minHealth = 999;
    
    for (auto& target : opponent->getField()) {
        if (target->getHealth() < minHealth) {
            minHealth = target->getHealth();
            best = target;
        }
    }
    
    return best;
}

int AIPlayer::selectBestCard() const {
    // Простой алгоритм выбора карты - выбираем карту с максимальной силой/стоимостью
    int bestIndex = -1;
    float bestValue = 0.0f;
    
    for (int i = 0; i < m_hand.size(); i++) {
        auto card = m_hand[i];
        
        // Если не хватает маны на карту, пропускаем
        if (card->getManaCost() > m_mana) {
            continue;
        }
        
        float value = 0.0f;
        
        // Оцениваем карту в зависимости от типа
        if (card->getType() == CardType::Character) {
            // Для существ учитываем атаку и здоровье
            auto character = std::dynamic_pointer_cast<CharacterCard>(card);
            if (character) {
                value = (float)(character->getAttack() + character->getHealth()) / 
                        (float)card->getManaCost();
            }
        }
        else if (card->getType() == CardType::Spell) {
            // Для заклинаний просто берем базовую оценку
            auto spell = std::dynamic_pointer_cast<SpellCard>(card);
            if (spell) {
                value = (float)spell->getPower() / (float)card->getManaCost();
            }
        }
        
        // Выбираем карту с лучшим соотношением сила/стоимость
        if (value > bestValue) {
            bestValue = value;
            bestIndex = i;
        }
    }
    
    return bestIndex;
}

int AIPlayer::makeDecision(Player* opponent) {
    // В зависимости от сложности ИИ, выбираем стратегию
    switch (m_difficulty) {
        case DifficultyLevel::Easy:
            // Для легкого уровня просто случайный выбор
            if (!m_hand.empty()) {
                return rand() % m_hand.size();
            }
            break;
            
        case DifficultyLevel::Medium:
        case DifficultyLevel::Hard:
            // Для среднего и сложного уровня используем более умную стратегию
            return selectBestCard();
    }
    
    return -1; // Нет подходящей карты
}
