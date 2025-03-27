/**
 * @file buff_effect.h
 * @brief Класс для эффектов усиления
 */

#ifndef BUFF_EFFECT_H
#define BUFF_EFFECT_H

#include "effect.h"

/**
 * @class BuffEffect
 * @brief Представляет эффект усиления в игре
 */
class BuffEffect : public Effect {
protected:
    int m_power;  ///< Сила эффекта усиления

public:
    /**
     * @brief Конструктор для BuffEffect
     * @param id Уникальный идентификатор эффекта
     * @param name Название эффекта
     * @param description Описание эффекта
     * @param duration Длительность эффекта (в ходах)
     * @param power Сила эффекта усиления
     */
    BuffEffect(int id, std::string name, std::string description,
              int duration, int power);

    /**
     * @brief Получить силу эффекта усиления
     * @return Значение силы
     */
    int getPower() const {
        return m_power;
    }
    
    /**
     * @brief Применить эффект усиления к персонажу
     * @param target Целевой персонаж
     */
    void apply(Character* target) override;
    
    /**
     * @brief Удалить эффект усиления с персонажа
     * @param target Целевой персонаж
     */
    void remove(Character* target) override;
    
    /**
     * @brief Преобразовать эффект усиления в строковое представление
     * @return Строковое представление эффекта
     */
    std::string toString() const override {
        return "Усиление: " + Effect::toString() + " (+" + std::to_string(m_power) + ")";
    }
};

// Удобное определение типа
using BuffEffectPtr = std::shared_ptr<BuffEffect>;

#endif // BUFF_EFFECT_H