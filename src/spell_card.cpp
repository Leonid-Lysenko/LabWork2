/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file spell_card.cpp
 * @brief Реализация класса карт заклинаний
 */

#include "spell_card.h"
#include "player.h"
#include "character_card.h"
#include "buff_effect.h"
#include "debuff_effect.h"
#include <iostream>
#include <sstream>

SpellCard::SpellCard(int id, const std::string& name, const std::string& description,
                     int manaCost, SpellType spellType, int power, 
                     int duration, CardRarity rarity)
    : Card(id, name, description, manaCost, CardType::Spell, rarity),
      m_spellType(spellType),
      m_power(power),
      m_duration(duration) {
}

SpellType SpellCard::getSpellType() const {
    return m_spellType;
}

int SpellCard::getPower() const {
    return m_power;
}

int SpellCard::getDuration() const {
    return m_duration;
}

bool SpellCard::canPlay(const Player* source, const Player* target) const {
    // Базовая проверка из родительского класса Card
    if (!Card::canPlay(source, target)) {
        return false;
    }
    
    // Проверки в зависимости от типа заклинания
    switch (m_spellType) {
        case SpellType::Healing:
            // Для заклинаний лечения цель должна быть жива
            if (target && !target->isAlive()) {
                return false;
            }
            break;
            
        case SpellType::Damage:
            // Для заклинаний урона цель должна быть жива
            if (target && !target->isAlive()) {
                return false;
            }
            break;
            
        default:
            break;
    }
    
    return true;
}

bool SpellCard::play(Player* source, Player* target) {
    if (!canPlay(source, target)) {
        return false;
    }
    
    // Если цель не указана, используем источник в качестве цели
    if (!target) {
        target = source;
    }
    
    // Тратим ману источника
    source->modifyMana(-m_manaCost);
    
    // Применяем эффект заклинания в зависимости от типа
    switch (m_spellType) {
        case SpellType::Damage:
            // Наносим урон цели
            target->modifyHealth(-m_power);
            std::cout << source->getName() << " применяет заклинание " 
                      << m_name << " и наносит " << m_power 
                      << " урона игроку " << target->getName() << std::endl;
            break;
            
        case SpellType::Healing:
            // Лечим цель
            target->modifyHealth(m_power);
            std::cout << source->getName() << " применяет заклинание " 
                      << m_name << " и восстанавливает " << m_power 
                      << " здоровья игроку " << target->getName() << std::endl;
            break;
            
        case SpellType::Draw:
            // Цель берет карты
            target->drawCard(m_power);
            std::cout << source->getName() << " применяет заклинание " 
                      << m_name << " и " << target->getName() 
                      << " берет " << m_power << " карт" << std::endl;
            break;
            
        case SpellType::Buff:
            // Создаем эффект усиления (если это заклинание с длительностью)
            if (m_duration > 0) {
                auto effect = std::make_shared<BuffEffect>(
                    getId(), m_name, m_description, m_duration, m_power);
                target->addEffect(effect);
                std::cout << source->getName() << " применяет заклинание " 
                          << m_name << " и усиливает " 
                          << target->getName() << std::endl;
            }
            break;
            
        case SpellType::Debuff:
            // Создаем эффект ослабления (если это заклинание с длительностью)
            if (m_duration > 0) {
                auto effect = std::make_shared<DebuffEffect>(
                    getId(), m_name, m_description, m_duration, m_power);
                target->addEffect(effect);
                std::cout << source->getName() << " применяет заклинание " 
                          << m_name << " и ослабляет " 
                          << target->getName() << std::endl;
            }
            break;
            
        case SpellType::AoE:
            // Применяем эффект по области (всем существам на поле противника)
            for (const auto& character : target->getField()) {
                character->modifyHealth(-m_power);
            }
            std::cout << source->getName() << " применяет заклинание " 
                      << m_name << " и наносит " << m_power 
                      << " урона всем существам " << target->getName() << std::endl;
            break;
            
        default:
            std::cerr << "Неизвестный тип заклинания!" << std::endl;
            return false;
    }
    
    return true;
}

bool SpellCard::play(Player* source, CharacterCard* target) {
    if (!source || !target || !canPlay(source)) {
        return false;
    }
    
    // Тратим ману источника
    source->modifyMana(-m_manaCost);
    
    // Применяем эффект заклинания на персонажа в зависимости от типа
    switch (m_spellType) {
        case SpellType::Damage:
            // Наносим урон цели
            target->modifyHealth(-m_power);
            std::cout << source->getName() << " применяет заклинание " 
                      << m_name << " и наносит " << m_power 
                      << " урона существу " << target->getName() << std::endl;
            break;
            
        case SpellType::Healing:
            // Лечим цель
            target->modifyHealth(m_power);
            std::cout << source->getName() << " применяет заклинание " 
                      << m_name << " и восстанавливает " << m_power 
                      << " здоровья существу " << target->getName() << std::endl;
            break;
            
        case SpellType::Buff:
            // Создаем эффект усиления (если это заклинание с длительностью)
            if (m_duration > 0) {
                auto effect = std::make_shared<BuffEffect>(
                    getId(), m_name, m_description, m_duration, m_power);
                target->addEffect(effect);
                std::cout << source->getName() << " применяет заклинание " 
                          << m_name << " и усиливает существо " 
                          << target->getName() << std::endl;
            } else {
                // Или просто повышаем атаку, если нет длительности
                target->modifyAttack(m_power);
                std::cout << source->getName() << " применяет заклинание " 
                          << m_name << " и увеличивает атаку существа " 
                          << target->getName() << " на " << m_power << std::endl;
            }
            break;
            
        case SpellType::Debuff:
            // Создаем эффект ослабления (если это заклинание с длительностью)
            if (m_duration > 0) {
                auto effect = std::make_shared<DebuffEffect>(
                    getId(), m_name, m_description, m_duration, m_power);
                target->addEffect(effect);
                std::cout << source->getName() << " применяет заклинание " 
                          << m_name << " и ослабляет существо " 
                          << target->getName() << std::endl;
            } else {
                // Или просто снижаем атаку, если нет длительности
                target->modifyAttack(-m_power);
                std::cout << source->getName() << " применяет заклинание " 
                          << m_name << " и уменьшает атаку существа " 
                          << target->getName() << " на " << m_power << std::endl;
            }
            break;
            
        default:
            std::cerr << "Этот тип заклинания не может быть применен к существу!" << std::endl;
            return false;
    }
    
    return true;
}

std::string SpellCard::toString() const {
    std::stringstream ss;
    ss << "Заклинание: " << m_name
       << " [" << getRarityString() << "] - "
       << m_manaCost << " маны - "
       << getSpellTypeString()
       << " (Сила: " << m_power;
    
    if (m_duration > 0) {
        ss << ", Длительность: " << m_duration;
    }
    
    ss << ")\nОписание: " << m_description;
    return ss.str();
}

std::string SpellCard::getSpellTypeString() const {
    switch (m_spellType) {
        case SpellType::Damage: return "Урон";
        case SpellType::Healing: return "Лечение";
        case SpellType::Buff: return "Усиление";
        case SpellType::Debuff: return "Ослабление";
        case SpellType::Draw: return "Взятие карт";
        case SpellType::AoE: return "Урон по области";
        default: return "Неизвестно";
    }
}
