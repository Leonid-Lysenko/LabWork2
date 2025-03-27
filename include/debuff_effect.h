/**
 * @file debuff_effect.h
 * @brief Класс для эффектов ослабления
 */

#ifndef DEBUFF_EFFECT_H
#define DEBUFF_EFFECT_H

#include "effect.h"

/**
 * @class DebuffEffect
 * @brief Представляет эффект ослабления в игре
 */
class DebuffEffect : public Effect {
protected:
    int m_power;  ///< Сила эффекта ослабления

public:
    /**
     * @brief Конструктор для DebuffEffect
     * @param id Уникальный идентификатор эффекта
     * @param name Название эффекта
     * @param description Описание эффекта
     * @param duration Длительность эффекта (в ходах)
     * @param power Сила эффекта ослабления
     */
    DebuffEffect(int id, std::string name, std::string description,
                int duration, int power);

    /**
     * @brief Получить силу эффекта ослабления
     * @return Значение силы
     */
    int getPower() const {
        return m_power;
    }
    
    /**
     * @brief Применить эффект ослабления к персонажу
     * @param target Целевой персонаж
     */
    void apply(Character* target) override;
    
    /**
     * @brief Удалить эффект ослабления с персонажа
     * @param target Целевой персонаж
     */
    void remove(Character* target) override;
    
    /**
     * @brief Применяется ли эффект каждый ход
     * @return True, если эффект применяется каждый ход, false в противном случае
     */
    bool isPeriodicEffect() const override {
        return false;  // Ослабление применяется один раз
    }
    
    /**
     * @brief Преобразовать эффект ослабления в строковое представление
     * @return Строковое представление эффекта
     */
    std::string toString() const override {
        return "Ослабление: " + Effect::toString() + " (-" + std::to_string(m_power) + ")";
    }
};

// Удобное определение типа
using DebuffEffectPtr = std::shared_ptr<DebuffEffect>;

#endif // DEBUFF_EFFECT_H