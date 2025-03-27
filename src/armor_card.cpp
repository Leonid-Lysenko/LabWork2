// armor_card.cpp
#include "armor_card.h"
#include "player.h"
#include "character_card.h"

ArmorCard::ArmorCard(int id, const std::string& name, const std::string& description,
                   int manaCost, int defense, int durability,
                   CardRarity rarity)
: Card(id, name, description, manaCost, CardType::Armor, rarity)
, m_defense(defense), m_durability(durability) {}

bool ArmorCard::play(Player* source, CharacterCard* target) {
    if (!canPlay(source) || !target) return false;
    source->modifyMana(-m_manaCost);
    target->modifyDefense(m_defense);
    return true;
}
