/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#include "armor_card.h"

ArmorCard::ArmorCard(int id, std::string name, std::string description,
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
