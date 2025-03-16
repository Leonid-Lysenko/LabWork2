/* Leonid Lysenko st128618@student.spbu.ru
   Lab2
*/

#include "item_card.h"

ItemCard::ItemCard(int id, std::string name, std::string description,
                 int manaCost, ItemType type, int power,
                 CardRarity rarity)
: Card(id, name, description, manaCost, CardType::Item, rarity)
, m_itemType(type), m_power(power) {}

bool ItemCard::play(Player* source, Player* target) {
    if (!canPlay(source, target)) return false;
    
    source->modifyMana(-m_manaCost);
    switch(m_itemType) {
        case ItemType::Potion:
            target->modifyHealth(m_power);
            break;
        case ItemType::Scroll:
            target->drawCard(m_power);
            break;
        case ItemType::Armor:
            if (auto character = target->getSelectedCharacter()) {
                character->modifyDefense(m_power);
            }
            break;
    }
    return true;
}
