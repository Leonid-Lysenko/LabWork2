/**
 * @file effect.h
 * @brief Базовый класс для эффектов
 */

#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <memory>

// Предварительное объявление
class CharacterCard;

// Используем для совместимости с исходным кодом
using Character = CharacterCard;

/**
 * @class Effect
 * @brief Базовый класс для всех эффектов в игре
 */
class Effect {
protected:
    int m_id;                   ///< Уникальный идентификатор эффекта
    std::string m_name;         ///< Название эффекта
    std::string m_description;  ///< Описание эффекта
    int m_duration;             ///< Длительность эффекта (в ходах)

public:
    /**
     * @brief Конструктор для Effect
     * @param id Уникальный идентификатор эффекта
     * @param name Название эффекта
     * @param description Описание эффекта
     * @param duration Длительность эффекта (в ходах)
     */
    Effect(int id, std::string name, std::string description, int duration);
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Effect() = default;

    /**
     * @brief Получить уникальный идентификатор эффекта
     * @return Идентификатор эффекта
     */
    int getId() const {
        return m_id;
    }
    
    /**
     * @brief Получить название эффекта
     * @return Название эффекта
     */
    const std::string& getName() const {
        return m_name;
    }
    
    /**
     * @brief Получить описание эффекта
     * @return Описание эффекта
     */
    const std::string& getDescription() const {
        return m_description;
    }
    
    /**
     * @brief Получить длительность эффекта
     * @return Длительность эффекта (в ходах)
     */
    int getDuration() const {
        return m_duration;
    }
    
    /**
     * @brief Обновить состояние эффекта (вызывается в конце каждого хода)
     * @return True, если эффект все еще активен, false если он закончился
     */
    virtual bool update();
    
    /**
     * @brief Применить эффект к персонажу
     * @param target Целевой персонаж
     */
    virtual void apply(Character* target) = 0;
    
    /**
     * @brief Удалить эффект с персонажа
     * @param target Целевой персонаж
     */
    virtual void remove(Character* target) {
        // Базовая реализация ничего не делает
    }
    
    /**
     * @brief Применяется ли эффект каждый ход
     * @return True, если эффект применяется каждый ход, false в противном случае
     */
    virtual bool isPeriodicEffect() const {
        return false;
    }
    
    /**
     * @brief Преобразовать эффект в строковое представление
     * @return Строковое представление эффекта
     */
    virtual std::string toString() const {
        return m_name + " (" + std::to_string(m_duration) + " ходов): " + m_description;
    }
};

// Удобное определение типа
using EffectPtr = std::shared_ptr<Effect>;

#endif // EFFECT_H