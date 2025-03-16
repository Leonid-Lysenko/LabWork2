/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file item_card.h
 * @brief Класс карт предметов
 */

#ifndef ITEM_CARD_H
#define ITEM_CARD_H

#include "card.h"
#include <memory>

// Предварительные объявления
class Player;
class CharacterCard;

// Типы предметов
enum class ItemType {
    Potion,   ///< Зелье (восстановление здоровья)
    Scroll,   ///< Свиток (взятие карт)
    Armor     ///< Броня (временная защита)
};

/**
 * @class ItemCard
 * @brief Представляет карту предмета в игре
 */
class ItemCard : public Card {
protected:
    ItemType m_itemType;  ///< Тип предмета
    int m_power;          ///< Сила эффекта предмета

public:
    /**
     * @brief Конструктор для ItemCard
     * @param id Уникальный идентификатор карты
     * @param name Название карты
     * @param description Описание карты
     * @param manaCost Стоимость маны для разыгрывания карты
     * @param type Тип предмета
     * @param power Сила эффекта предмета
     */
    ItemCard(int id, std::string name, std::string description,
             int manaCost, ItemType type, int power,
             CardRarity rarity = CardRarity::Common);

    /**
     * @brief Получить тип предмета
     * @return Тип предмета
     */
    ItemType getItemType() const {
        return m_itemType;
    }
    
    /**
     * @brief Получить силу эффекта предмета
     * @return Значение силы эффекта
     */
    int getPower() const {
        return m_power;
    }
    
    /**
     * @brief Проверить, может ли карта предмета быть разыграна
     * @param source Игрок, который хочет разыграть карту
     * @param target Целевой игрок (опционально)
     * @return True, если карта может быть разыграна, false в противном случае
     */
    bool canPlay(const Player* source, const Player* target = nullptr) const override {
        return Card::canPlay(source, target) && (target != nullptr || m_itemType == ItemType::Scroll);
    }
    
    /**
     * @brief Разыграть карту предмета
     * @param source Игрок, который разыгрывает карту
     * @param target Целевой игрок
     * @return True, если карта была успешно разыграна, false в противном случае
     */
    bool play(Player* source, Player* target = nullptr) override;
    
    /**
     * @brief Преобразовать карту предмета в строковое представление
     * @return Строковое представление карты предмета
     */
    std::string toString() const override {
        std::string typeStr;
        switch (m_itemType) {
            case ItemType::Potion: typeStr = "Зелье"; break;
            case ItemType::Scroll: typeStr = "Свиток"; break;
            case ItemType::Armor: typeStr = "Броня"; break;
            default: typeStr = "Неизвестно";
        }
        return typeStr + ": " + m_name + " [Сила: " + std::to_string(m_power) + "] - " + m_description;
    }
    
    /**
     * @brief Создать копию карты предмета
     * @return Shared pointer на новую копию карты предмета
     */
    std::shared_ptr<Card> clone() const override {
        return std::make_shared<ItemCard>(*this);
    }
};

// Удобное определение типа
using ItemCardPtr = std::shared_ptr<ItemCard>;

#endif // ITEM_CARD_H
