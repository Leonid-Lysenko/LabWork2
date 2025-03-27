#include "card_factory.h"
#include "character_card.h"
#include "spell_card.h"
#include "item_card.h"
#include "accessory_card.h"  // Добавляем недостающий заголовочный файл
#include <random>

CardFactory& CardFactory::getInstance() {
    static CardFactory instance;
    return instance;
}

void CardFactory::initialize() {
    registerBasicCards();
    registerCharacterCards();
    registerSpellCards();
    registerItemCards();
}

// Удаляем повторное определение registerCard, так как оно уже есть в заголовочном файле

void CardFactory::registerBasicCards() {
    registerCard(std::make_shared<CharacterCard>(
        1, "Воин", "Базовый воин", 2, CharacterClass::Warrior, 2, 3));
    registerCard(std::make_shared<SpellCard>(
        2, "Удар молнии", "Наносит 3 урона", 1, SpellType::Damage, 3));
    registerCard(std::make_shared<ItemCard>(
        3, "Зелье здоровья", "Восстанавливает 5 HP", 2, ItemType::Potion, 5));
}

void CardFactory::registerCharacterCards() {
    // Регистрация различных типов персонажей
    registerCard(std::make_shared<CharacterCard>(
        101, "Лучник", "Дальний бой", 3, CharacterClass::Hunter, 3, 2));
    registerCard(std::make_shared<CharacterCard>(
        102, "Маг", "Мощные заклинания", 4, CharacterClass::Mage, 1, 4));
}

void CardFactory::registerSpellCards() {
    // Исправляем SpellType::Heal на SpellType::Healing
    registerCard(std::make_shared<SpellCard>(
        201, "Лечение", "Восстанавливает 5 HP", 2, SpellType::Healing, 5));
    registerCard(std::make_shared<SpellCard>(
        202, "Щит", "Дает +2 защиты", 1, SpellType::Buff, 2));
}

void CardFactory::registerItemCards() {
    // Удаляем регистрацию Weapon, так как его нет в ItemType (используем только Potion, Scroll, Armor)
    registerCard(std::make_shared<ItemCard>(
        301, "Меч", "+2 к атаке", 3, ItemType::Armor, 2));  // Используем Armor вместо Weapon
    registerCard(std::make_shared<ItemCard>(
        302, "Доспех", "+3 к защите", 4, ItemType::Armor, 3));
}

CardPtr CardFactory::createCard(int id) {
    auto it = m_cardPrototypes.find(id);
    if (it != m_cardPrototypes.end()) {
        return it->second->clone();
    }
    return nullptr;
}

CardPtr CardFactory::createRandomCard() {
    if (m_cardPrototypes.empty()) {
        return nullptr;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, m_cardPrototypes.size() - 1);

    auto it = m_cardPrototypes.begin();
    std::advance(it, dis(gen));
    return it->second->clone();
}

// Исправляем сигнатуры методов в соответствии с объявлениями в заголовочном файле
CharacterCardPtr CardFactory::createCharacterCard(
    const std::string& name, int attack, int health, int manaCost,
    CharacterClass characterClass, int defense) {
    return std::make_shared<CharacterCard>(
        getNextCardId(), name, "", manaCost, characterClass, attack, health, defense);
}

SpellCardPtr CardFactory::createSpellCard(
    const std::string& name, int manaCost, int power,
    SpellType spellType, int duration) {
    return std::make_shared<SpellCard>(
        getNextCardId(), name, "", manaCost, spellType, power, duration);
}

MagicCardPtr CardFactory::createMagicCard(
    const std::string& name, int manaCost, const std::string& description,
    MagicType magicType, int power, int duration, CardRarity rarity)
{
    return std::make_shared<MagicCard>(
        getNextCardId(), name, description, manaCost, 
        rarity, magicType, power, duration);
}

Cards CardFactory::createFullCollection() {
    Cards collection;
    for (const auto& pair : m_cardPrototypes) {
        collection.push_back(pair.second->clone());
    }
    return collection;
}
