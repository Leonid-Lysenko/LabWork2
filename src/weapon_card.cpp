/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/


/**
 * @file weapon_card.cpp
 * @brief Реализация класса карт оружия
 */

#include "weapon_card.h"
#include "player.h"
#include "character_card.h"
#include <sstream>

WeaponCard::WeaponCard(int id, const std::string& name, const std::string& description,
                       int manaCost, CardRarity rarity, WeaponType weaponType,
                       int attack, int durability)
    : Card(id, name, description, manaCost, CardType::Weapon, rarity)
    , m_weaponType(weaponType)
    , m_attack(attack)
    , m_durability(durability)
    , m_maxDurability(durability)
    , m_equippedCharacter(nullptr) {
}

WeaponType WeaponCard::getWeaponType() const {
    return m_weaponType;
}

int WeaponCard::getAttack() const {
    return m_attack;
}

int WeaponCard::getDurability() const {
    return m_durability;
}

int WeaponCard::getMaxDurability() const {
    return m_maxDurability;
}

CharacterCardPtr WeaponCard::getEquippedCharacter() const {
    return m_equippedCharacter;
}

bool WeaponCard::play(Player* source, Player* target, int characterIndex) {
    // Проверяем базовые условия
    if (!source || !canPlay(source, target)) {
        return false;
    }

    // Проверяем индекс целевого персонажа
    const auto& field = source->getField();
    if (characterIndex < 0 || characterIndex >= static_cast<int>(field.size())) {
        return false;
    }

    // Получаем персонажа
    CharacterCardPtr character = field[characterIndex];
    if (!character || !character->isAlive()) {
        return false;
    }

    // Проверяем совместимость типа оружия с классом персонажа
    if (!isCompatibleWithCharacter(character)) {
        return false;
    }

    // Тратим ману
    source->modifyMana(-m_manaCost);

    // Снимаем текущее оружие, если есть
    if (character->getWeapon()) {
        character->unequipWeapon();
    }

    // Экипируем новое оружие
    m_equippedCharacter = character;
    character->equipWeapon(std::static_pointer_cast<WeaponCard>(shared_from_this()));

    // Применяем бонусы оружия
    character->modifyAttack(m_attack);

    return true;
}

bool WeaponCard::canPlay(const Player* source, const Player* target) const {
    // Базовая проверка
    if (!Card::canPlay(source, target)) {
        return false;
    }

    // Проверяем наличие персонажей на поле
    return !source->getField().empty();
}

void WeaponCard::onAttackUsed() {
    // Уменьшаем прочность оружия при использовании
    if (m_durability > 0) {
        m_durability--;

        // Если прочность закончилась, оружие ломается
        if (m_durability == 0 && m_equippedCharacter) {
            m_equippedCharacter->modifyAttack(-m_attack);
            m_equippedCharacter->unequipWeapon();
            m_equippedCharacter = nullptr;
        }
    }
}

bool WeaponCard::isCompatibleWithCharacter(const CharacterCardPtr& character) const {
    if (!character) {
        return false;
    }

    // Проверяем совместимость типа оружия с классом персонажа
    switch (m_weaponType) {
        case WeaponType::Sword:
            return character->getCharacterClass() == CharacterClass::Warrior ||
                   character->getCharacterClass() == CharacterClass::Paladin;

        case WeaponType::Bow:
            return character->getCharacterClass() == CharacterClass::Hunter;

        case WeaponType::Staff:
            return character->getCharacterClass() == CharacterClass::Mage ||
                   character->getCharacterClass() == CharacterClass::Priest;

        case WeaponType::Dagger:
            return character->getCharacterClass() == CharacterClass::Rogue;

        default:
            return false;
    }
}

std::string WeaponCard::toString() const {
    std::stringstream ss;
    ss << "Оружие: " << m_name 
       << " [" << getRarityString() << "] - "
       << m_manaCost << " маны - "
       << getWeaponTypeString()
       << " (Атака: " << m_attack
       << ", Прочность: " << m_durability << "/" << m_maxDurability << ")"
       << "\nОписание: " << m_description;
    return ss.str();
}

std::string WeaponCard::getWeaponTypeString() const {
    switch (m_weaponType) {
        case WeaponType::Sword: return "Меч";
        case WeaponType::Bow: return "Лук";
        case WeaponType::Staff: return "Посох";
        case WeaponType::Dagger: return "Кинжал";
        default: return "Неизвестно";
    }
}
