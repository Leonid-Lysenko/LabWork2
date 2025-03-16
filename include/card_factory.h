/**
 * @file card_factory.h
 * @brief Фабрика карт
 */

#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <map>
#include <memory>
#include <string>
#include "card.h"
#include "character_card.h"
#include "spell_card.h"
#include "magic_card.h"
#include "weapon_card.h"
#include "armor_card.h"
#include "accessory_card.h"
#include "item_card.h"

/**
 * @class CardFactory
 * @brief Фабрика для создания карт разных типов
 */
class CardFactory {
private:
    std::map<int, CardPtr> m_cardPrototypes;  ///< Прототипы карт

    /**
     * @brief Приватный конструктор (для паттерна Singleton)
     */
    CardFactory() {}
    
    /**
     * @brief Зарегистрировать основные карты
     */
    void registerBasicCards();
    
    /**
     * @brief Зарегистрировать карты персонажей
     */
    void registerCharacterCards();
    
    /**
     * @brief Зарегистрировать карты заклинаний
     */
    void registerSpellCards();
    
    /**
     * @brief Зарегистрировать карты предметов
     */
    void registerItemCards();

public:
    /**
     * @brief Получить экземпляр фабрики (для паттерна Singleton)
     * @return Ссылка на экземпляр фабрики
     */
    static CardFactory& getInstance();
    
    /**
     * @brief Инициализировать фабрику
     */
    void initialize();
    
    /**
     * @brief Создать карту по идентификатору
     * @param id Идентификатор карты
     * @return Указатель на созданную карту или nullptr
     */
    CardPtr createCard(int id);
    
    /**
     * @brief Создать случайную карту
     * @return Указатель на созданную карту
     */
    CardPtr createRandomCard();
    
    /**
     * @brief Создать карту персонажа
     * @param name Имя персонажа
     * @param attack Значение атаки
     * @param health Значение здоровья
     * @param manaCost Стоимость маны
     * @param characterClass Класс персонажа (по умолчанию Warrior)
     * @param defense Значение защиты (по умолчанию 0)
     * @return Указатель на созданную карту персонажа
     */
    CharacterCardPtr createCharacterCard(
        const std::string& name, int attack, int health, int manaCost,
        CharacterClass characterClass = CharacterClass::Warrior, int defense = 0);
    
    /**
     * @brief Создать карту заклинания
     * @param name Имя заклинания
     * @param manaCost Стоимость маны
     * @param power Сила заклинания
     * @param spellType Тип заклинания (по умолчанию Damage)
     * @param duration Длительность эффекта (по умолчанию 0)
     * @return Указатель на созданную карту заклинания
     */
    SpellCardPtr createSpellCard(
        const std::string& name, int manaCost, int power,
        SpellType spellType = SpellType::Damage, int duration = 0);
    
    /**
     * @brief Создать карту магии
     * @param name Имя магической карты
     * @param manaCost Стоимость маны
     * @param description Описание
     * @param magicType Тип магии
     * @param power Сила магии (по умолчанию 0)
     * @param duration Длительность эффекта (по умолчанию 0)
     * @return Указатель на созданную карту магии
     */
    MagicCardPtr createMagicCard(
        const std::string& name, int manaCost, const std::string& description,
        MagicType magicType, int power = 0, int duration = 0);
    
    /**
     * @brief Создать полную коллекцию карт
     * @return Вектор со всеми доступными картами
     */
    Cards createFullCollection();
    
    /**
     * @brief Зарегистрировать карту в фабрике
     * @param card Указатель на карту
     */
    void registerCard(CardPtr card) {
        if (card) {
            m_cardPrototypes[card->getId()] = card;
        }
    }
    
    /**
     * @brief Получить следующий доступный идентификатор карты
     * @return Идентификатор
     */
    int getNextCardId() const {
        return m_cardPrototypes.empty() ? 1 : m_cardPrototypes.rbegin()->first + 1;
    }
};

#endif // CARD_FACTORY_H