/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

/**
 * @file card.cpp
 * @brief Implementation of the base Card class
 */

#include "card.h"
#include "player.h"
#include <sstream>

Card::Card(int id, const std::string& name, const std::string& description,
           int manaCost, CardType type, CardRarity rarity)
    : m_id(id)
    , m_name(name)
    , m_description(description)
    , m_manaCost(manaCost)
    , m_type(type)
    , m_rarity(rarity) {
}

int Card::getId() const {
    return m_id;
}

const std::string& Card::getName() const {
    return m_name;
}

const std::string& Card::getDescription() const {
    return m_description;
}

int Card::getManaCost() const {
    return m_manaCost;
}

CardType Card::getType() const {
    return m_type;
}

CardRarity Card::getRarity() const {
    return m_rarity;
}

bool Card::canPlay(const Player* source, const Player* target) const {
    if (!source) {
        return false;
    }
    
    // Basic check - player must have enough mana
    return source->getMana() >= m_manaCost;
}

std::string Card::toString() const {
    std::stringstream ss;
    ss << getTypeString() << " Card: " << m_name 
       << " [" << getRarityString() << "] - "
       << m_manaCost << " mana - " << m_description;
    return ss.str();
}

std::string Card::getTypeString() const {
    switch (m_type) {
        case CardType::Character: return "Character";
        case CardType::Magic: return "Magic";
        case CardType::Weapon: return "Weapon";
        case CardType::Spell: return "Spell";
        case CardType::Armor: return "Armor";
        case CardType::Accessory: return "Accessory";
        case CardType::Item: return "Item";
        default: return "Unknown";
    }
}

std::string Card::getRarityString() const {
    switch (m_rarity) {
        case CardRarity::Common: return "Common";
        case CardRarity::Uncommon: return "Uncommon";
        case CardRarity::Rare: return "Rare";
        case CardRarity::Epic: return "Epic";
        case CardRarity::Legendary: return "Legendary";
        default: return "Unknown";
    }
}
