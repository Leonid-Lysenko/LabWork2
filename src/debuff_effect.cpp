/**
 * @file debuff_effect.cpp
 * @brief Реализация класса эффектов ослабления
 */

#include "debuff_effect.h"
#include "character_card.h"

DebuffEffect::DebuffEffect(int id, std::string name, std::string description,
                          int duration, int power)
    : Effect(id, name, description, duration), m_power(power) {
}

void DebuffEffect::apply(Character* target) {
    if (target) {
        // Применяем ослабление
        target->modifyAttack(-m_power);
        
        // Дебаффы уменьшают и защиту
        target->modifyDefense(-m_power);
        
        // Устанавливаем флаг наличия эффекта
        target->setStatusEffect(true);
    }
}

void DebuffEffect::remove(Character* target) {
    if (target) {
        // Восстанавливаем оригинальные характеристики
        target->modifyAttack(m_power);
        target->modifyDefense(m_power);
        
        // Проверяем, есть ли еще эффекты на персонаже
        // При полной реализации нужно добавить проверку наличия других эффектов
        target->setStatusEffect(false);
    }
}