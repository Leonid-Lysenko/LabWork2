/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#include "card_factory.h"

CardFactory& CardFactory::getInstance() {
    static CardFactory instance;
    return instance;
}

void CardFactory::initialize() {
    // Регистрируем базовые карты
    registerBasicCards();
    registerCharacterCards(); 
    registerSpellCards();
    registerItemCards();
}

CardPtr CardFactory::createCard(int id) {
    auto it = m_cardPrototypes.find(id);
    if (it != m_cardPrototypes.end()) {
        return it->second->clone();
    }
    return nullptr;
}

void CardFactory::registerBasicCards() {
    // Регистрируем простые карты
    registerCard(std::make_shared<CharacterCard>(
        1, "Воин", "Базовый воин", 2, CharacterClass::Warrior, 2, 3));
    registerCard(std::make_shared<SpellCard>(
        2, "Удар молнии", "Наносит 3 урона", 1, SpellType::Damage, 3));
    registerCard(std::make_shared<ItemCard>(
        3, "Зелье здоровья", "Восстанавливает 5 HP", 2, ItemType::Potion, 5));
}

// Для тестирования и режима медитации
Cards CardFactory::createFullCollection() {
    Cards collection;
    for (const auto& pair : m_cardPrototypes) {
        collection.push_back(pair.second->clone());
    }
    return collection;
}
