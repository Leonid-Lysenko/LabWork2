/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file status_effect.h
 * @brief Класс для эффектов статуса
 */

#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

#include "effect.h"

// Типы статусных эффектов
enum class StatusType {
    Stun,    ///< Оглушение (невозможность действовать)
    Poison,  ///< Отравление (периодический урон)
    Shield   ///< Щит (увеличение защиты)
};

/**
 * @class StatusEffect
 * @brief Представляет статусный эффект в игре
 */
class StatusEffect : public Effect {
protected:
    StatusType m_type;  ///< Тип статусного эффекта

public:
    /**
     * @brief Конструктор для StatusEffect
     * @param id Уникальный идентификатор эффекта
     * @param name Название эффекта
     * @param description Описание эффекта
     * @param duration Длительность эффекта (в ходах)
     * @param type Тип статусного эффекта
     */
    StatusEffect(int id, std::string name, std::string description,
                int duration, StatusType type);

    /**
     * @brief Получить тип статусного эффекта
     * @return Тип статуса
     */
    StatusType getStatusType() const {
        return m_type;
    }
    
    /**
     * @brief Применить статусный эффект к персонажу
     * @param target Целевой персонаж
     */
    void apply(Character* target) override;
    
    /**
     * @brief Удалить статусный эффект с персонажа
     * @param target Целевой персонаж
     */
    void remove(Character* target) override;
    
    /**
     * @brief Применяется ли эффект каждый ход
     * @return True, если эффект применяется каждый ход, false в противном случае
     */
    bool isPeriodicEffect() const override {
        return m_type == StatusType::Poison;  // Только яд действует каждый ход
    }
    
    /**
     * @brief Преобразовать статусный эффект в строковое представление
     * @return Строковое представление эффекта
     */
    std::string toString() const override {
        std::string typeStr;
        switch (m_type) {
            case StatusType::Stun: typeStr = "Оглушение"; break;
            case StatusType::Poison: typeStr = "Отравление"; break;
            case StatusType::Shield: typeStr = "Щит"; break;
            default: typeStr = "Неизвестно";
        }
        return typeStr + ": " + Effect::toString();
    }
};

// Удобное определение типа
using StatusEffectPtr = std::shared_ptr<StatusEffect>;

#endif // STATUS_EFFECT_H
