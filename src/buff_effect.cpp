/**
 * @file buff_effect.cpp
 * @brief Реализация класса эффектов усиления
 */

#include "buff_effect.h"
#include "character_card.h"

BuffEffect::BuffEffect(int id, std::string name, std::string description,
                      int duration, int power)
    : Effect(id, name, description, duration), m_power(power) {
}

void BuffEffect::apply(Character* target) {
    if (target) {
        // Применяем усиление
        target->modifyAttack(m_power);
        
        // Некоторые баффы также влияют на защиту (половина эффекта)
        target->modifyDefense(m_power / 2);
        
        // Устанавливаем флаг наличия эффекта
        target->setStatusEffect(true);
    }
}

void BuffEffect::remove(Character* target) {
    if (target) {
        // Удаляем эффекты усиления (обратное применение)
        target->modifyAttack(-m_power);
        target->modifyDefense(-m_power / 2);
        
        // Проверяем, есть ли еще эффекты на персонаже
        // Этот код предполагает наличие соответствующего метода у персонажа
        // При полной реализации нужно добавить проверку наличия других эффектов
        target->setStatusEffect(false);
    }
}