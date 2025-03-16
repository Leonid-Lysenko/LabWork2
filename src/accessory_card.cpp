// accessory_card.cpp
#include "accessory_card.h"

AccessoryCard::AccessoryCard(int id, std::string name, std::string description,
                           int manaCost, AccessoryType type, int bonus,
                           CardRarity rarity)
: Card(id, name, description, manaCost, CardType::Accessory, rarity)
, m_type(type), m_bonus(bonus) {}

bool AccessoryCard::play(Player* source, CharacterCard* target) {
    if (!canPlay(source) || !target) return false;
    source->modifyMana(-m_manaCost);
    
    switch(m_type) {
        case AccessoryType::Ring:
            target->modifyHealth(m_bonus);
            break;
        case AccessoryType::Amulet:
            target->modifyMana(m_bonus);
            break;
        case AccessoryType::Belt:
            target->modifySpeed(m_bonus);
            break;
    }
    return true;
}