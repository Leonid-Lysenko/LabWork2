/**
 * @file magic_card.cpp
 * @brief Реализация класса магических карт
 */

#include "magic_card.h"
#include "player.h"
#include <sstream>
#include <iostream>
#include "buff_effect.h"
#include "debuff_effect.h"
#include "buff_effect.h"
#include "debuff_effect.h"

MagicCard::MagicCard(int id, const std::string& name, const std::string& description,
                     int manaCost, CardRarity rarity, MagicType magicType,
                     int power, int duration)
    : Card(id, name, description, manaCost, CardType::Magic, rarity)
    , m_magicType(magicType)
    , m_power(power)
    , m_duration(duration) {
}

MagicType MagicCard::getMagicType() const {
    return m_magicType;
}

int MagicCard::getPower() const {
    return m_power;
}

int MagicCard::getDuration() const {
    return m_duration;
}

bool MagicCard::play(Player* source, Player* target) {
    // Проверяем базовые условия для разыгрывания карты
    if (!source || !canPlay(source, target)) {
        return false;
    }

    // Если цель не указана, заклинание применяется к самому игроку
    if (!target) {
        target = source;
    }

    // Тратим ману игрока
    source->modifyMana(-m_manaCost);

    // Применяем эффект заклинания
    return applyMagicEffect(source, target);
}

bool MagicCard::canPlay(const Player* source, const Player* target) const {
    // Базовая проверка из родительского класса Card
    if (!Card::canPlay(source, target)) {
        return false;
    }

    // Дополнительные проверки для магических карт
    if (target && !target->isAlive()) {
        return false;
    }

    // Проверки в зависимости от типа магии
    switch (m_magicType) {
        case MagicType::Healing:
            // Нельзя лечить противника
            if (target && target != source) {
                return false;
            }
            break;

        case MagicType::DamageSpell:
            // Нельзя наносить урон себе
            if (target && target == source) {
                return false;
            }
            break;

        default:
            break;
    }

    return true;
}

bool MagicCard::applyMagicEffect(Player* source, Player* target) {
    if (!source || !target) {
        return false;
    }

    switch (m_magicType) {
        case MagicType::DamageSpell: {
            // Наносим магический урон цели
            int damage = -m_power;
            std::cout << source->getName() << " применяет " << m_name
                     << " и наносит " << -damage << " урона " 
                     << target->getName() << std::endl;
            target->modifyHealth(damage);
            return true;
        }

        case MagicType::Healing: {
            // Лечим цель
            std::cout << source->getName() << " применяет " << m_name
                     << " и восстанавливает " << m_power << " здоровья "
                     << target->getName() << std::endl;
            target->modifyHealth(m_power);
            return true;
        }

        case MagicType::Enhancement: {
            // Создаем усиливающий эффект
            auto effect = std::make_shared<BuffEffect>(
            m_id, m_name, m_description,
            m_duration, m_power
            );
            target->addEffect(effect);
            return true;
        }

        case MagicType::Curse: {
            // Создаем проклятие
            auto effect = std::make_shared<DebuffEffect>(
            m_id, m_name, m_description,
            m_duration, m_power
            );
            target->addEffect(effect);
            return true;
        }

        case MagicType::AreaEffect: {
            // Эффект по области применяется ко всем персонажам на поле
            const auto& field = target->getField();
            for (const auto& character : field) {
                character->modifyHealth(-m_power);
            }
            return true;
        }

        default:
            return false;
    }
}

std::string MagicCard::toString() const {
    std::stringstream ss;
    ss << "Магическая карта: " << m_name 
       << " [" << getRarityString() << "] - "
       << m_manaCost << " маны - " 
       << getMagicTypeString() 
       << " (Сила: " << m_power;
    
    if (m_duration > 0) {
        ss << ", Длительность: " << m_duration;
    }
    
    ss << ")\nОписание: " << m_description;
    return ss.str();
}

std::string MagicCard::getMagicTypeString() const {
    switch (m_magicType) {
        case MagicType::DamageSpell: return "Урон";
        case MagicType::Healing: return "Исцеление";
        case MagicType::Enhancement: return "Усиление";
        case MagicType::Curse: return "Проклятие";
        case MagicType::AreaEffect: return "Эффект по области";
        default: return "Неизвестно";
    }
}