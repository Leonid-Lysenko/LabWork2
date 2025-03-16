/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

/**
 * @file accessory_card.h
 * @brief Класс карт аксессуаров
 */

#ifndef ACCESSORY_CARD_H
#define ACCESSORY_CARD_H

#include "card.h"
#include <memory>

// Предварительные объявления
class Player;
class CharacterCard;

// Типы аксессуаров
enum class AccessoryType {
    Ring,    ///< Кольцо (здоровье)
    Amulet,  ///< Амулет (мана)
    Belt     ///< Пояс (скорость)
};

/**
 * @class AccessoryCard
 * @brief Представляет карту аксессуара в игре
 */
class AccessoryCard : public Card {
protected:
    AccessoryType m_type;  ///< Тип аксессуара
    int m_bonus;           ///< Бонус, предоставляемый аксессуаром

public:
    /**
     * @brief Конструктор для AccessoryCard
     * @param id Уникальный идентификатор карты
     * @param name Название карты
     * @param description Описание карты
     * @param manaCost Стоимость маны для разыгрывания карты
     * @param type Тип аксессуара
     * @param bonus Бонус, предоставляемый аксессуаром
     */
    AccessoryCard(int id, std::string name, std::string description,
                 int manaCost, AccessoryType type, int bonus,
                 CardRarity rarity = CardRarity::Common);

    /**
     * @brief Получить тип аксессуара
     * @return Тип аксессуара
     */
    AccessoryType getType() const {
        return m_type;
    }
    
    /**
     * @brief Получить бонус, предоставляемый аксессуаром
     * @return Значение бонуса
     */
    int getBonus() const {
        return m_bonus;
    }
    
    /**
     * @brief Проверить, может ли карта аксессуара быть разыграна
     * @param source Игрок, который хочет разыграть карту
     * @param target Целевой персонаж (опционально)
     * @return True, если карта может быть разыграна, false в противном случае
     */
    bool canPlay(const Player* source, CharacterCard* target = nullptr) const {
        return Card::canPlay(source) && target != nullptr;
    }
    
    /**
     * @brief Разыграть карту аксессуара на персонаже
     * @param source Игрок, который разыгрывает карту
     * @param target Целевой персонаж
     * @return True, если карта была успешно разыграна, false в противном случае
     */
    bool play(Player* source, CharacterCard* target) override;
    
    /**
     * @brief Разыграть карту аксессуара (стандартная реализация)
     * @param source Игрок, который разыгрывает карту
     * @param target Целевой игрок (опционально)
     * @return True, если карта была успешно разыграна, false в противном случае
     */
    bool play(Player* source, Player* target = nullptr) override {
        // Стандартная реализация требует цель-персонажа
        return false;
    }
    
    /**
     * @brief Преобразовать карту аксессуара в строковое представление
     * @return Строковое представление карты аксессуара
     */
    std::string toString() const override {
        std::string typeStr;
        switch (m_type) {
            case AccessoryType::Ring: typeStr = "Кольцо"; break;
            case AccessoryType::Amulet: typeStr = "Амулет"; break;
            case AccessoryType::Belt: typeStr = "Пояс"; break;
            default: typeStr = "Неизвестно";
        }
        return typeStr + ": " + m_name + " [+" + std::to_string(m_bonus) + "] - " + m_description;
    }
    
    /**
     * @brief Создать копию карты аксессуара
     * @return Shared pointer на новую копию карты аксессуара
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<AccessoryCard>(*this);
    }
};

// Удобное определение типа
using AccessoryCardPtr = std::shared_ptr<AccessoryCard>;

#endif // ACCESSORY_CARD_H
